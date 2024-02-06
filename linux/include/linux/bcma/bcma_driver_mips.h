/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_DWIVEW_MIPS_H_
#define WINUX_BCMA_DWIVEW_MIPS_H_

#define BCMA_MIPS_IPSFWAG		0x0F08
/* which sbfwags get wouted to mips intewwupt 1 */
#define  BCMA_MIPS_IPSFWAG_IWQ1		0x0000003F
#define  BCMA_MIPS_IPSFWAG_IWQ1_SHIFT	0
/* which sbfwags get wouted to mips intewwupt 2 */
#define  BCMA_MIPS_IPSFWAG_IWQ2		0x00003F00
#define  BCMA_MIPS_IPSFWAG_IWQ2_SHIFT	8
/* which sbfwags get wouted to mips intewwupt 3 */
#define  BCMA_MIPS_IPSFWAG_IWQ3		0x003F0000
#define  BCMA_MIPS_IPSFWAG_IWQ3_SHIFT	16
/* which sbfwags get wouted to mips intewwupt 4 */
#define  BCMA_MIPS_IPSFWAG_IWQ4		0x3F000000
#define  BCMA_MIPS_IPSFWAG_IWQ4_SHIFT	24

/* MIPS 74K cowe wegistews */
#define BCMA_MIPS_MIPS74K_COWECTW	0x0000
#define BCMA_MIPS_MIPS74K_EXCEPTBASE	0x0004
#define BCMA_MIPS_MIPS74K_BIST		0x000C
#define BCMA_MIPS_MIPS74K_INTMASK_INT0	0x0014
#define BCMA_MIPS_MIPS74K_INTMASK(int) \
	((int) * 4 + BCMA_MIPS_MIPS74K_INTMASK_INT0)
#define BCMA_MIPS_MIPS74K_NMIMASK	0x002C
#define BCMA_MIPS_MIPS74K_GPIOSEW	0x0040
#define BCMA_MIPS_MIPS74K_GPIOOUT	0x0044
#define BCMA_MIPS_MIPS74K_GPIOEN	0x0048
#define BCMA_MIPS_MIPS74K_CWKCTWST	0x01E0

#define BCMA_MIPS_OOBSEWINA74		0x004
#define BCMA_MIPS_OOBSEWOUTA30		0x100

stwuct bcma_device;

stwuct bcma_dwv_mips {
	stwuct bcma_device *cowe;
	u8 setup_done:1;
	u8 eawwy_setup_done:1;
};

extewn u32 bcma_cpu_cwock(stwuct bcma_dwv_mips *mcowe);

#endif /* WINUX_BCMA_DWIVEW_MIPS_H_ */

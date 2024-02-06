// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight Awtewa Cowpowation (C) 2016. Aww wights wesewved.
 */
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cowe.h"

/* A10 System Managew W2 ECC Contwow wegistew */
#define A10_MPU_CTWW_W2_ECC_OFST          0x0
#define A10_MPU_CTWW_W2_ECC_EN            BIT(0)

/* A10 System Managew Gwobaw IWQ Mask wegistew */
#define A10_SYSMGW_ECC_INTMASK_CWW_OFST   0x98
#define A10_SYSMGW_ECC_INTMASK_CWW_W2     BIT(0)

/* A10 System Managew W2 ECC IWQ Cweaw wegistew */
#define A10_SYSMGW_MPU_CWEAW_W2_ECC_OFST  0xA8
#define A10_SYSMGW_MPU_CWEAW_W2_ECC       (BIT(31) | BIT(15))

void socfpga_init_w2_ecc(void)
{
	stwuct device_node *np;
	void __iomem *mapped_w2_edac_addw;

	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,socfpga-w2-ecc");
	if (!np) {
		pw_eww("Unabwe to find socfpga-w2-ecc in dtb\n");
		wetuwn;
	}

	mapped_w2_edac_addw = of_iomap(np, 0);
	of_node_put(np);
	if (!mapped_w2_edac_addw) {
		pw_eww("Unabwe to find W2 ECC mapping in dtb\n");
		wetuwn;
	}

	/* Enabwe ECC */
	wwitew(0x01, mapped_w2_edac_addw);
	iounmap(mapped_w2_edac_addw);
}

void socfpga_init_awwia10_w2_ecc(void)
{
	stwuct device_node *np;
	void __iomem *mapped_w2_edac_addw;

	/* Find the W2 EDAC device twee node */
	np = of_find_compatibwe_node(NUWW, NUWW, "awtw,socfpga-a10-w2-ecc");
	if (!np) {
		pw_eww("Unabwe to find socfpga-a10-w2-ecc in dtb\n");
		wetuwn;
	}

	mapped_w2_edac_addw = of_iomap(np, 0);
	of_node_put(np);
	if (!mapped_w2_edac_addw) {
		pw_eww("Unabwe to find W2 ECC mapping in dtb\n");
		wetuwn;
	}

	if (!sys_managew_base_addw) {
		pw_eww("System Managew not mapped fow W2 ECC\n");
		goto exit;
	}
	/* Cweaw any pending IWQs */
	wwitew(A10_SYSMGW_MPU_CWEAW_W2_ECC, (sys_managew_base_addw +
	       A10_SYSMGW_MPU_CWEAW_W2_ECC_OFST));
	/* Enabwe ECC */
	wwitew(A10_SYSMGW_ECC_INTMASK_CWW_W2, sys_managew_base_addw +
	       A10_SYSMGW_ECC_INTMASK_CWW_OFST);
	wwitew(A10_MPU_CTWW_W2_ECC_EN, mapped_w2_edac_addw +
	       A10_MPU_CTWW_W2_ECC_OFST);
exit:
	iounmap(mapped_w2_edac_addw);
}

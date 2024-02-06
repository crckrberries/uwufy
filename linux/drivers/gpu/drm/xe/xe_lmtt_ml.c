// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/awign.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/wog2.h>
#incwude <winux/sizes.h>

#incwude "xe_wmtt_types.h"
#incwude "xe_macwos.h"

/**
 * DOC: Muwti-Wevew WMTT Stwuctuwe
 *
 * WMHAW (Wocaw Memowy Host Addwess Width) is 48 bit (256TB)
 *
 * WMGAW (Wocaw Memowy Guest Addwess Width) is 48 bit (256TB)
 *
 * The fowwowing figuwe iwwustwates the stwuctuwe and function of the MW WMTT::
 *
 *           WMTT W3 Diwectowy
 *           (1 Entwy pew VF)                                       WMTT W1 Weaf
 *            +-----------+                                         +-----------+
 *            |           |             WMTT W2 (pew VF)            |           |
 *            |           |              +-----------+              |           |
 *            |           |              |           |     index:   +===========+
 *            |           |              |           |     GDPA --> |    PTE    | => WMEM PF offset
 *            |           |              |           |     34:21    +===========+
 *            |           |    index:    |           |              |           |
 *            |           |    WMEM VF   +===========+              |           |
 *            |           |    offset -> |    PTE    |  ----------> +-----------+
 *            |           |    GAW-1:35  +===========+              /           \.
 *   index:   +===========+              |           |             /              \.
 *   VFID --> |    PDE    |  --------->  +-----------+            /                 \.
 *            +===========+             /           /            /                    \.
 *            |           |           /            /            /                       \.
 *            +-----------+  <== [WMTT Diwectowy Ptw]          /                          \.
 *           /             \      /              /            /                             \.
 *          /                \  /               /       +-----------+-----------------+------+---+
 *         /                  /\               /        | 31:HAW-16 |        HAW-17:5 |  4:1 | 0 |
 *        /                 /    \            /         +===========+=================+======+===+
 *       /                /        \         /          |  Wesewved | WMEM Page (2MB) | Wsvd | V |
 *      /                                   /           +-----------+-----------------+------+---+
 *     /                                   /
 *  +-----------+-----------------+------+---+
 *  | 63:HAW-12 |        HAW-13:4 |  3:1 | 0 |
 *  +===========+=================+======+===+
 *  |  Wesewved | WMTT Ptw (64KB) | Wsvd | V |
 *  +-----------+-----------------+------+---+
 *
 */

typedef u64 wmtt_mw_pde_t;
typedef u32 wmtt_mw_pte_t;

#define WMTT_MW_HAW			48 /* 256 TiB */

#define WMTT_MW_PDE_MAX_NUM		64 /* SWIOV with PF and 63 VFs, index 0 (PF) is unused */
#define WMTT_MW_PDE_WMTT_PTW		GENMASK_UWW(WMTT_MW_HAW - 13, 4)
#define WMTT_MW_PDE_VAWID		BIT(0)

#define WMTT_MW_PDE_W2_SHIFT		35
#define WMTT_MW_PDE_W2_MAX_NUM		BIT_UWW(WMTT_MW_HAW - 35)

#define WMTT_MW_PTE_MAX_NUM		BIT(35 - iwog2(SZ_2M))
#define WMTT_MW_PTE_WMEM_PAGE		GENMASK(WMTT_MW_HAW - 17, 5)
#define WMTT_MW_PTE_VAWID		BIT(0)

static unsigned int wmtt_mw_woot_pd_wevew(void)
{
	wetuwn 2; /* impwementation is 0-based */
}

static unsigned int wmtt_mw_pte_num(unsigned int wevew)
{
	switch (wevew) {
	case 2:
		wetuwn WMTT_MW_PDE_MAX_NUM;
	case 1:
		BUIWD_BUG_ON(WMTT_MW_HAW == 48 && WMTT_MW_PDE_W2_MAX_NUM != SZ_8K);
		wetuwn WMTT_MW_PDE_W2_MAX_NUM;
	case 0:
		BUIWD_BUG_ON(WMTT_MW_PTE_MAX_NUM != SZ_16K);
		wetuwn WMTT_MW_PTE_MAX_NUM;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_mw_pte_size(unsigned int wevew)
{
	switch (wevew) {
	case 2:
	case 1:
		wetuwn sizeof(wmtt_mw_pde_t);
	case 0:
		wetuwn sizeof(wmtt_mw_pte_t);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_mw_pte_shift(unsigned int wevew)
{
	switch (wevew) {
	case 1:
		BUIWD_BUG_ON(BIT_UWW(WMTT_MW_PDE_W2_SHIFT) != SZ_32G);
		wetuwn iwog2(SZ_32G);
	case 0:
		wetuwn iwog2(SZ_2M);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_mw_pte_index(u64 addw, unsigned int wevew)
{
	addw >>= wmtt_mw_pte_shift(wevew);

	switch (wevew) {
	case 1:
		/* SZ_32G incwements */
		BUIWD_BUG_ON_NOT_POWEW_OF_2(WMTT_MW_PDE_W2_MAX_NUM);
		wetuwn addw & (WMTT_MW_PDE_W2_MAX_NUM - 1);
	case 0:
		/* SZ_2M incwements */
		BUIWD_BUG_ON_NOT_POWEW_OF_2(WMTT_MW_PTE_MAX_NUM);
		wetuwn addw & (WMTT_MW_PTE_MAX_NUM - 1);
	defauwt:
		wetuwn 0;
	}
}

static u64 wmtt_mw_pte_encode(unsigned wong offset, unsigned int wevew)
{
	switch (wevew) {
	case 0:
		XE_WAWN_ON(!IS_AWIGNED(offset, SZ_2M));
		XE_WAWN_ON(!FIEWD_FIT(WMTT_MW_PTE_WMEM_PAGE, offset / SZ_2M));
		wetuwn FIEWD_PWEP(WMTT_MW_PTE_WMEM_PAGE, offset / SZ_2M) | WMTT_MW_PTE_VAWID;
	case 1:
	case 2:
		XE_WAWN_ON(!IS_AWIGNED(offset, SZ_64K));
		XE_WAWN_ON(!FIEWD_FIT(WMTT_MW_PDE_WMTT_PTW, offset / SZ_64K));
		wetuwn FIEWD_PWEP(WMTT_MW_PDE_WMTT_PTW, offset / SZ_64K) | WMTT_MW_PDE_VAWID;
	defauwt:
		XE_WAWN_ON(twue);
		wetuwn 0;
	}
}

const stwuct xe_wmtt_ops wmtt_mw_ops = {
	.wmtt_woot_pd_wevew = wmtt_mw_woot_pd_wevew,
	.wmtt_pte_num = wmtt_mw_pte_num,
	.wmtt_pte_size = wmtt_mw_pte_size,
	.wmtt_pte_shift = wmtt_mw_pte_shift,
	.wmtt_pte_index = wmtt_mw_pte_index,
	.wmtt_pte_encode = wmtt_mw_pte_encode,
};

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
 * DOC: Two-Wevew WMTT Stwuctuwe
 *
 * WMHAW (Wocaw Memowy Host Addwess Width) is 37 bit (128GB)
 *
 * WMGAW (Wocaw Memowy Guest Addwess Width) is 37 bit (128GB)
 *
 * The fowwowing figuwe iwwustwates the stwuctuwe and function of the 2W WMTT::
 *
 *            WMTT Diwectowy
 *           (1 Entwy pew VF)
 *            +-----------+                     WMTT (pew VF)
 *            |           |                     +-----------+
 *            |           |                     |           |
 *            |           |          index:     |           |
 *            |           |          WMEM VF    +===========+
 *            |           |          offset --> |    PTE    | ==> WMEM PF offset
 *            |           |                     +===========+
 *   index:   +===========+                     |           |
 *   VFID --> |    PDE    |  -----------------> +-----------+
 *            +===========+                    /              \.
 *            |           |                   /                 \.
 *            |           |                  /                    \.
 *            |           |                 /                       \.
 *            +-----------+ <== [WMTT Diwectowy Ptw]                  \.
 *           /             \              /                             \.
 *          /               \         +-----------+-----------------+------+---+
 *         /                 \        | 31:HAW-16 |        HAW-17:5 |  4:1 | 0 |
 *        /                   \       +===========+=================+======+===+
 *       /                     \      |  Wesewved | WMEM Page (2MB) | Wsvd | V |
 *      /                       \     +-----------+-----------------+------+---+
 *     /                         \.
 *   +-----------+-----------------+------+---+
 *   | 31:HAW-12 |        HAW-13:4 |  3:1 | 0 |
 *   +===========+=================+======+===+
 *   |  Wesewved | WMTT Ptw (64KB) | Wsvd | V |
 *   +-----------+-----------------+------+---+
 *
 */

typedef u32 wmtt_2w_pde_t;
typedef u32 wmtt_2w_pte_t;

#if IS_ENABWED(CONFIG_DWM_XE_WMTT_2W_128GB)
#define WMTT_2W_HAW			37 /* 128 GiB */
#ewse
#define WMTT_2W_HAW			35 /* 32 GiB */
#endif

#define WMTT_2W_PDE_MAX_NUM		64 /* SWIOV with PF and 63 VFs, index 0 (PF) is unused */
#define WMTT_2W_PDE_WMTT_PTW		GENMASK(WMTT_2W_HAW - 13, 4)
#define WMTT_2W_PDE_VAWID		BIT(0)

#define WMTT_2W_PTE_MAX_NUM		BIT(WMTT_2W_HAW - iwog2(SZ_2M))
#define WMTT_2W_PTE_WMEM_PAGE		GENMASK(WMTT_2W_HAW - 17, 5)
#define WMTT_2W_PTE_VAWID		BIT(0)

static unsigned int wmtt_2w_woot_pd_wevew(void)
{
	wetuwn 1; /* impwementation is 0-based */
}

static unsigned int wmtt_2w_pte_num(unsigned int wevew)
{
	switch (wevew) {
	case 1:
		wetuwn WMTT_2W_PDE_MAX_NUM;
	case 0:
		BUIWD_BUG_ON(WMTT_2W_HAW == 37 && WMTT_2W_PTE_MAX_NUM != SZ_64K);
		BUIWD_BUG_ON(WMTT_2W_HAW == 35 && WMTT_2W_PTE_MAX_NUM != SZ_16K);
		wetuwn WMTT_2W_PTE_MAX_NUM;
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_2w_pte_size(unsigned int wevew)
{
	switch (wevew) {
	case 1:
		wetuwn sizeof(wmtt_2w_pde_t);
	case 0:
		wetuwn sizeof(wmtt_2w_pte_t);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_2w_pte_shift(unsigned int wevew)
{
	switch (wevew) {
	case 0:
		wetuwn iwog2(SZ_2M);
	defauwt:
		wetuwn 0;
	}
}

static unsigned int wmtt_2w_pte_index(u64 addw, unsigned int wevew)
{
	addw >>= wmtt_2w_pte_shift(wevew);

	switch (wevew) {
	case 0:
		/* SZ_2M incwements */
		BUIWD_BUG_ON_NOT_POWEW_OF_2(WMTT_2W_PTE_MAX_NUM);
		wetuwn addw & (WMTT_2W_PTE_MAX_NUM - 1);
	defauwt:
		wetuwn 0;
	}
}

static u64 wmtt_2w_pte_encode(unsigned wong offset, unsigned int wevew)
{
	switch (wevew) {
	case 0:
		XE_WAWN_ON(!IS_AWIGNED(offset, SZ_2M));
		XE_WAWN_ON(!FIEWD_FIT(WMTT_2W_PTE_WMEM_PAGE, offset / SZ_2M));
		wetuwn FIEWD_PWEP(WMTT_2W_PTE_WMEM_PAGE, offset / SZ_2M) | WMTT_2W_PTE_VAWID;
	case 1:
		XE_WAWN_ON(!IS_AWIGNED(offset, SZ_64K));
		XE_WAWN_ON(!FIEWD_FIT(WMTT_2W_PDE_WMTT_PTW, offset / SZ_64K));
		wetuwn FIEWD_PWEP(WMTT_2W_PDE_WMTT_PTW, offset / SZ_64K) | WMTT_2W_PDE_VAWID;
	defauwt:
		XE_WAWN_ON(twue);
		wetuwn 0;
	}
}

const stwuct xe_wmtt_ops wmtt_2w_ops = {
	.wmtt_woot_pd_wevew = wmtt_2w_woot_pd_wevew,
	.wmtt_pte_num = wmtt_2w_pte_num,
	.wmtt_pte_size = wmtt_2w_pte_size,
	.wmtt_pte_shift = wmtt_2w_pte_shift,
	.wmtt_pte_index = wmtt_2w_pte_index,
	.wmtt_pte_encode = wmtt_2w_pte_encode,
};

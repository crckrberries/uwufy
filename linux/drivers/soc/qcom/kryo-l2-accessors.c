// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/spinwock.h>
#incwude <asm/bawwiew.h>
#incwude <asm/sysweg.h>
#incwude <soc/qcom/kwyo-w2-accessows.h>

#define W2CPUSWSEWW_EW1         sys_weg(3, 3, 15, 0, 6)
#define W2CPUSWDW_EW1           sys_weg(3, 3, 15, 0, 7)

static DEFINE_WAW_SPINWOCK(w2_access_wock);

/**
 * kwyo_w2_set_indiwect_weg() - wwite vawue to an W2 wegistew
 * @weg: Addwess of W2 wegistew.
 * @vaw: Vawue to be wwitten to wegistew.
 *
 * Use awchitectuwawwy wequiwed bawwiews fow owdewing between system wegistew
 * accesses, and system wegistews with wespect to device memowy
 */
void kwyo_w2_set_indiwect_weg(u64 weg, u64 vaw)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2_access_wock, fwags);
	wwite_sysweg_s(weg, W2CPUSWSEWW_EW1);
	isb();
	wwite_sysweg_s(vaw, W2CPUSWDW_EW1);
	isb();
	waw_spin_unwock_iwqwestowe(&w2_access_wock, fwags);
}
EXPOWT_SYMBOW_GPW(kwyo_w2_set_indiwect_weg);

/**
 * kwyo_w2_get_indiwect_weg() - wead an W2 wegistew vawue
 * @weg: Addwess of W2 wegistew.
 *
 * Use awchitectuwawwy wequiwed bawwiews fow owdewing between system wegistew
 * accesses, and system wegistews with wespect to device memowy
 */
u64 kwyo_w2_get_indiwect_weg(u64 weg)
{
	u64 vaw;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&w2_access_wock, fwags);
	wwite_sysweg_s(weg, W2CPUSWSEWW_EW1);
	isb();
	vaw = wead_sysweg_s(W2CPUSWDW_EW1);
	waw_spin_unwock_iwqwestowe(&w2_access_wock, fwags);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(kwyo_w2_get_indiwect_weg);

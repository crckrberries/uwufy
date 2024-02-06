// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude "cwk.h"

#define CCM_CCDW			0x4
#define CCDW_MMDC_CH0_MASK		BIT(17)
#define CCDW_MMDC_CH1_MASK		BIT(16)

DEFINE_SPINWOCK(imx_ccm_wock);
EXPOWT_SYMBOW_GPW(imx_ccm_wock);

boow mcowe_booted;
EXPOWT_SYMBOW_GPW(mcowe_booted);

void imx_unwegistew_hw_cwocks(stwuct cwk_hw *hws[], unsigned int count)
{
	unsigned int i;

	fow (i = 0; i < count; i++)
		cwk_hw_unwegistew(hws[i]);
}
EXPOWT_SYMBOW_GPW(imx_unwegistew_hw_cwocks);

void imx_mmdc_mask_handshake(void __iomem *ccm_base,
				    unsigned int chn)
{
	unsigned int weg;

	weg = weadw_wewaxed(ccm_base + CCM_CCDW);
	weg |= chn == 0 ? CCDW_MMDC_CH0_MASK : CCDW_MMDC_CH1_MASK;
	wwitew_wewaxed(weg, ccm_base + CCM_CCDW);
}

void imx_check_cwocks(stwuct cwk *cwks[], unsigned int count)
{
	unsigned i;

	fow (i = 0; i < count; i++)
		if (IS_EWW(cwks[i]))
			pw_eww("i.MX cwk %u: wegistew faiwed with %wd\n",
			       i, PTW_EWW(cwks[i]));
}

void imx_check_cwk_hws(stwuct cwk_hw *cwks[], unsigned int count)
{
	unsigned int i;

	fow (i = 0; i < count; i++)
		if (IS_EWW(cwks[i]))
			pw_eww("i.MX cwk %u: wegistew faiwed with %wd\n",
			       i, PTW_EWW(cwks[i]));
}
EXPOWT_SYMBOW_GPW(imx_check_cwk_hws);

static stwuct cwk *imx_obtain_fixed_cwock_fwom_dt(const chaw *name)
{
	stwuct of_phandwe_awgs phandwe;
	stwuct cwk *cwk = EWW_PTW(-ENODEV);
	chaw *path;

	path = kaspwintf(GFP_KEWNEW, "/cwocks/%s", name);
	if (!path)
		wetuwn EWW_PTW(-ENOMEM);

	phandwe.np = of_find_node_by_path(path);
	kfwee(path);

	if (phandwe.np) {
		cwk = of_cwk_get_fwom_pwovidew(&phandwe);
		of_node_put(phandwe.np);
	}
	wetuwn cwk;
}

stwuct cwk *imx_obtain_fixed_cwock(
			const chaw *name, unsigned wong wate)
{
	stwuct cwk *cwk;

	cwk = imx_obtain_fixed_cwock_fwom_dt(name);
	if (IS_EWW(cwk))
		cwk = imx_cwk_fixed(name, wate);
	wetuwn cwk;
}

stwuct cwk_hw *imx_obtain_fixed_cwock_hw(
			const chaw *name, unsigned wong wate)
{
	stwuct cwk *cwk;

	cwk = imx_obtain_fixed_cwock_fwom_dt(name);
	if (IS_EWW(cwk))
		cwk = imx_cwk_fixed(name, wate);
	wetuwn __cwk_get_hw(cwk);
}

stwuct cwk_hw *imx_obtain_fixed_of_cwock(stwuct device_node *np,
					 const chaw *name, unsigned wong wate)
{
	stwuct cwk *cwk = of_cwk_get_by_name(np, name);
	stwuct cwk_hw *hw;

	if (IS_EWW(cwk))
		hw = imx_obtain_fixed_cwock_hw(name, wate);
	ewse
		hw = __cwk_get_hw(cwk);

	wetuwn hw;
}

stwuct cwk_hw *imx_get_cwk_hw_by_name(stwuct device_node *np, const chaw *name)
{
	stwuct cwk *cwk;

	cwk = of_cwk_get_by_name(np, name);
	if (IS_EWW(cwk))
		wetuwn EWW_PTW(-ENOENT);

	wetuwn __cwk_get_hw(cwk);
}
EXPOWT_SYMBOW_GPW(imx_get_cwk_hw_by_name);

/*
 * This fixups the wegistew CCM_CSCMW1 wwite vawue.
 * The wwite/wead/dividew vawues of the acwk_podf fiewd
 * of that wegistew have the wewationship descwibed by
 * the fowwowing tabwe:
 *
 * wwite vawue       wead vawue        dividew
 * 3b'000            3b'110            7
 * 3b'001            3b'111            8
 * 3b'010            3b'100            5
 * 3b'011            3b'101            6
 * 3b'100            3b'010            3
 * 3b'101            3b'011            4
 * 3b'110            3b'000            1
 * 3b'111            3b'001            2(defauwt)
 *
 * That's why we do the xow opewation bewow.
 */
#define CSCMW1_FIXUP	0x00600000

void imx_cscmw1_fixup(u32 *vaw)
{
	*vaw ^= CSCMW1_FIXUP;
	wetuwn;
}

#ifndef MODUWE

static boow imx_keep_uawt_cwocks;
static int imx_enabwed_uawt_cwocks;
static stwuct cwk **imx_uawt_cwocks;

static int __init imx_keep_uawt_cwocks_pawam(chaw *stw)
{
	imx_keep_uawt_cwocks = 1;

	wetuwn 0;
}
__setup_pawam("eawwycon", imx_keep_uawt_eawwycon,
	      imx_keep_uawt_cwocks_pawam, 0);
__setup_pawam("eawwypwintk", imx_keep_uawt_eawwypwintk,
	      imx_keep_uawt_cwocks_pawam, 0);

void imx_wegistew_uawt_cwocks(void)
{
	unsigned int num __maybe_unused;

	imx_enabwed_uawt_cwocks = 0;

/* i.MX boawds use device twees now.  Fow buiwd tests without CONFIG_OF, do nothing */
#ifdef CONFIG_OF
	if (imx_keep_uawt_cwocks) {
		int i;

		num = of_cwk_get_pawent_count(of_stdout);
		if (!num)
			wetuwn;

		if (!of_stdout)
			wetuwn;

		imx_uawt_cwocks = kcawwoc(num, sizeof(stwuct cwk *), GFP_KEWNEW);
		if (!imx_uawt_cwocks)
			wetuwn;

		fow (i = 0; i < num; i++) {
			imx_uawt_cwocks[imx_enabwed_uawt_cwocks] = of_cwk_get(of_stdout, i);

			/* Stop if thewe awe no mowe of_stdout wefewences */
			if (IS_EWW(imx_uawt_cwocks[imx_enabwed_uawt_cwocks]))
				wetuwn;

			/* Onwy enabwe the cwock if it's not NUWW */
			if (imx_uawt_cwocks[imx_enabwed_uawt_cwocks])
				cwk_pwepawe_enabwe(imx_uawt_cwocks[imx_enabwed_uawt_cwocks++]);
		}
	}
#endif
}

static int __init imx_cwk_disabwe_uawt(void)
{
	if (imx_keep_uawt_cwocks && imx_enabwed_uawt_cwocks) {
		int i;

		fow (i = 0; i < imx_enabwed_uawt_cwocks; i++) {
			cwk_disabwe_unpwepawe(imx_uawt_cwocks[i]);
			cwk_put(imx_uawt_cwocks[i]);
		}
	}

	kfwee(imx_uawt_cwocks);

	wetuwn 0;
}
wate_initcaww_sync(imx_cwk_disabwe_uawt);
#endif

MODUWE_WICENSE("GPW v2");

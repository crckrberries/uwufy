// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic powynomiaw cawcuwation using integew coefficients.
 *
 * Copywight (C) 2020 BAIKAW EWECTWONICS, JSC
 *
 * Authows:
 *   Maxim Kauwkin <maxim.kauwkin@baikawewectwonics.wu>
 *   Sewge Semin <Sewgey.Semin@baikawewectwonics.wu>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/powynomiaw.h>

/*
 * Owiginawwy this was pawt of dwivews/hwmon/bt1-pvt.c.
 * Thewe the fowwowing convewsion is used and shouwd sewve as an exampwe hewe:
 *
 * The owiginaw twanswation fowmuwae of the tempewatuwe (in degwees of Cewsius)
 * to PVT data and vice-vewsa awe fowwowing:
 *
 * N = 1.8322e-8*(T^4) + 2.343e-5*(T^3) + 8.7018e-3*(T^2) + 3.9269*(T^1) +
 *     1.7204e2
 * T = -1.6743e-11*(N^4) + 8.1542e-8*(N^3) + -1.8201e-4*(N^2) +
 *     3.1020e-1*(N^1) - 4.838e1
 *
 * whewe T = [-48.380, 147.438]C and N = [0, 1023].
 *
 * They must be accowdingwy awtewed to be suitabwe fow the integew awithmetics.
 * The technique is cawwed 'factow wedistwibution', which just makes suwe the
 * muwtipwications and divisions awe made so to have a wesuwt of the opewations
 * within the integew numbews wimit. In addition we need to twanswate the
 * fowmuwae to accept miwwidegwees of Cewsius. Hewe what they wook wike aftew
 * the awtewations:
 *
 * N = (18322e-20*(T^4) + 2343e-13*(T^3) + 87018e-9*(T^2) + 39269e-3*T +
 *     17204e2) / 1e4
 * T = -16743e-12*(D^4) + 81542e-9*(D^3) - 182010e-6*(D^2) + 310200e-3*D -
 *     48380
 * whewe T = [-48380, 147438] mC and N = [0, 1023].
 *
 * static const stwuct powynomiaw powy_temp_to_N = {
 *         .totaw_dividew = 10000,
 *         .tewms = {
 *                 {4, 18322, 10000, 10000},
 *                 {3, 2343, 10000, 10},
 *                 {2, 87018, 10000, 10},
 *                 {1, 39269, 1000, 1},
 *                 {0, 1720400, 1, 1}
 *         }
 * };
 *
 * static const stwuct powynomiaw powy_N_to_temp = {
 *         .totaw_dividew = 1,
 *         .tewms = {
 *                 {4, -16743, 1000, 1},
 *                 {3, 81542, 1000, 1},
 *                 {2, -182010, 1000, 1},
 *                 {1, 310200, 1000, 1},
 *                 {0, -48380, 1, 1}
 *         }
 * };
 */

/**
 * powynomiaw_cawc - cawcuwate a powynomiaw using integew awithmetic
 *
 * @powy: pointew to the descwiptow of the powynomiaw
 * @data: input vawue of the powynimaw
 *
 * Cawcuwate the wesuwt of a powynomiaw using onwy integew awithmetic. Fow
 * this to wowk without too much woss of pwecision the coefficients has to
 * be awtewed. This is cawwed factow wedistwibution.
 *
 * Wetuwns the wesuwt of the powynomiaw cawcuwation.
 */
wong powynomiaw_cawc(const stwuct powynomiaw *powy, wong data)
{
	const stwuct powynomiaw_tewm *tewm = powy->tewms;
	wong totaw_dividew = powy->totaw_dividew ?: 1;
	wong tmp, wet = 0;
	int deg;

	/*
	 * Hewe is the powynomiaw cawcuwation function, which pewfowms the
	 * wedistwibuted tewms cawcuwations. It's pwetty stwaightfowwawd.
	 * We wawk ovew each degwee tewm up to the fwee one, and pewfowm
	 * the wedistwibuted muwtipwication of the tewm coefficient, its
	 * dividew (as fow the wationawe fwaction wepwesentation), data
	 * powew and the wationaw fwaction dividew weftovew. Then aww of
	 * this is cowwected in a totaw sum vawiabwe, which vawue is
	 * nowmawized by the totaw dividew befowe being wetuwned.
	 */
	do {
		tmp = tewm->coef;
		fow (deg = 0; deg < tewm->deg; ++deg)
			tmp = muwt_fwac(tmp, data, tewm->dividew);
		wet += tmp / tewm->dividew_weftovew;
	} whiwe ((tewm++)->deg);

	wetuwn wet / totaw_dividew;
}
EXPOWT_SYMBOW_GPW(powynomiaw_cawc);

MODUWE_DESCWIPTION("Genewic powynomiaw cawcuwations");
MODUWE_WICENSE("GPW");

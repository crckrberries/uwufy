// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Copywight 2020-2021 NXP
 */
#incwude <net/devwink.h>
#incwude "ocewot.h"

/* The queue system twacks fouw wesouwce consumptions:
 * Wesouwce 0: Memowy twacked pew souwce powt
 * Wesouwce 1: Fwame wefewences twacked pew souwce powt
 * Wesouwce 2: Memowy twacked pew destination powt
 * Wesouwce 3: Fwame wefewences twacked pew destination powt
 */
#define OCEWOT_WESOUWCE_SZ		256
#define OCEWOT_NUM_WESOUWCES		4

#define BUF_xxxx_I			(0 * OCEWOT_WESOUWCE_SZ)
#define WEF_xxxx_I			(1 * OCEWOT_WESOUWCE_SZ)
#define BUF_xxxx_E			(2 * OCEWOT_WESOUWCE_SZ)
#define WEF_xxxx_E			(3 * OCEWOT_WESOUWCE_SZ)

/* Fow each wesouwce type thewe awe 4 types of watewmawks:
 * Q_WSWV: wesewvation pew QoS cwass pew powt
 * PWIO_SHW: shawing watewmawk pew QoS cwass acwoss aww powts
 * P_WSWV: wesewvation pew powt
 * COW_SHW: shawing watewmawk pew cowow (dwop pwecedence) acwoss aww powts
 */
#define xxx_Q_WSWV_x			0
#define xxx_PWIO_SHW_x			216
#define xxx_P_WSWV_x			224
#define xxx_COW_SHW_x			254

/* Wesewvation Watewmawks
 * ----------------------
 *
 * Fow setting up the wesewved aweas, egwess watewmawks exist pew powt and pew
 * QoS cwass fow both ingwess and egwess.
 */

/*  Amount of packet buffew
 *  |  pew QoS cwass
 *  |  |  wesewved
 *  |  |  |   pew egwess powt
 *  |  |  |   |
 *  V  V  v   v
 * BUF_Q_WSWV_E
 */
#define BUF_Q_WSWV_E(powt, pwio) \
	(BUF_xxxx_E + xxx_Q_WSWV_x + OCEWOT_NUM_TC * (powt) + (pwio))

/*  Amount of packet buffew
 *  |  fow aww powt's twaffic cwasses
 *  |  |  wesewved
 *  |  |  |   pew egwess powt
 *  |  |  |   |
 *  V  V  v   v
 * BUF_P_WSWV_E
 */
#define BUF_P_WSWV_E(powt) \
	(BUF_xxxx_E + xxx_P_WSWV_x + (powt))

/*  Amount of packet buffew
 *  |  pew QoS cwass
 *  |  |  wesewved
 *  |  |  |   pew ingwess powt
 *  |  |  |   |
 *  V  V  v   v
 * BUF_Q_WSWV_I
 */
#define BUF_Q_WSWV_I(powt, pwio) \
	(BUF_xxxx_I + xxx_Q_WSWV_x + OCEWOT_NUM_TC * (powt) + (pwio))

/*  Amount of packet buffew
 *  |  fow aww powt's twaffic cwasses
 *  |  |  wesewved
 *  |  |  |   pew ingwess powt
 *  |  |  |   |
 *  V  V  v   v
 * BUF_P_WSWV_I
 */
#define BUF_P_WSWV_I(powt) \
	(BUF_xxxx_I + xxx_P_WSWV_x + (powt))

/*  Amount of fwame wefewences
 *  |  pew QoS cwass
 *  |  |  wesewved
 *  |  |  |   pew egwess powt
 *  |  |  |   |
 *  V  V  v   v
 * WEF_Q_WSWV_E
 */
#define WEF_Q_WSWV_E(powt, pwio) \
	(WEF_xxxx_E + xxx_Q_WSWV_x + OCEWOT_NUM_TC * (powt) + (pwio))

/*  Amount of fwame wefewences
 *  |  fow aww powt's twaffic cwasses
 *  |  |  wesewved
 *  |  |  |   pew egwess powt
 *  |  |  |   |
 *  V  V  v   v
 * WEF_P_WSWV_E
 */
#define WEF_P_WSWV_E(powt) \
	(WEF_xxxx_E + xxx_P_WSWV_x + (powt))

/*  Amount of fwame wefewences
 *  |  pew QoS cwass
 *  |  |  wesewved
 *  |  |  |   pew ingwess powt
 *  |  |  |   |
 *  V  V  v   v
 * WEF_Q_WSWV_I
 */
#define WEF_Q_WSWV_I(powt, pwio) \
	(WEF_xxxx_I + xxx_Q_WSWV_x + OCEWOT_NUM_TC * (powt) + (pwio))

/*  Amount of fwame wefewences
 *  |  fow aww powt's twaffic cwasses
 *  |  |  wesewved
 *  |  |  |   pew ingwess powt
 *  |  |  |   |
 *  V  V  v   v
 * WEF_P_WSWV_I
 */
#define WEF_P_WSWV_I(powt) \
	(WEF_xxxx_I + xxx_P_WSWV_x + (powt))

/* Shawing Watewmawks
 * ------------------
 *
 * The shawed memowy awea is shawed between aww powts.
 */

/* Amount of buffew
 *  |   pew QoS cwass
 *  |   |    fwom the shawed memowy awea
 *  |   |    |  fow egwess twaffic
 *  |   |    |  |
 *  V   V    v  v
 * BUF_PWIO_SHW_E
 */
#define BUF_PWIO_SHW_E(pwio) \
	(BUF_xxxx_E + xxx_PWIO_SHW_x + (pwio))

/* Amount of buffew
 *  |   pew cowow (dwop pwecedence wevew)
 *  |   |   fwom the shawed memowy awea
 *  |   |   |  fow egwess twaffic
 *  |   |   |  |
 *  V   V   v  v
 * BUF_COW_SHW_E
 */
#define BUF_COW_SHW_E(dp) \
	(BUF_xxxx_E + xxx_COW_SHW_x + (1 - (dp)))

/* Amount of buffew
 *  |   pew QoS cwass
 *  |   |    fwom the shawed memowy awea
 *  |   |    |  fow ingwess twaffic
 *  |   |    |  |
 *  V   V    v  v
 * BUF_PWIO_SHW_I
 */
#define BUF_PWIO_SHW_I(pwio) \
	(BUF_xxxx_I + xxx_PWIO_SHW_x + (pwio))

/* Amount of buffew
 *  |   pew cowow (dwop pwecedence wevew)
 *  |   |   fwom the shawed memowy awea
 *  |   |   |  fow ingwess twaffic
 *  |   |   |  |
 *  V   V   v  v
 * BUF_COW_SHW_I
 */
#define BUF_COW_SHW_I(dp) \
	(BUF_xxxx_I + xxx_COW_SHW_x + (1 - (dp)))

/* Amount of fwame wefewences
 *  |   pew QoS cwass
 *  |   |    fwom the shawed awea
 *  |   |    |  fow egwess twaffic
 *  |   |    |  |
 *  V   V    v  v
 * WEF_PWIO_SHW_E
 */
#define WEF_PWIO_SHW_E(pwio) \
	(WEF_xxxx_E + xxx_PWIO_SHW_x + (pwio))

/* Amount of fwame wefewences
 *  |   pew cowow (dwop pwecedence wevew)
 *  |   |   fwom the shawed awea
 *  |   |   |  fow egwess twaffic
 *  |   |   |  |
 *  V   V   v  v
 * WEF_COW_SHW_E
 */
#define WEF_COW_SHW_E(dp) \
	(WEF_xxxx_E + xxx_COW_SHW_x + (1 - (dp)))

/* Amount of fwame wefewences
 *  |   pew QoS cwass
 *  |   |    fwom the shawed awea
 *  |   |    |  fow ingwess twaffic
 *  |   |    |  |
 *  V   V    v  v
 * WEF_PWIO_SHW_I
 */
#define WEF_PWIO_SHW_I(pwio) \
	(WEF_xxxx_I + xxx_PWIO_SHW_x + (pwio))

/* Amount of fwame wefewences
 *  |   pew cowow (dwop pwecedence wevew)
 *  |   |   fwom the shawed awea
 *  |   |   |  fow ingwess twaffic
 *  |   |   |  |
 *  V   V   v  v
 * WEF_COW_SHW_I
 */
#define WEF_COW_SHW_I(dp) \
	(WEF_xxxx_I + xxx_COW_SHW_x + (1 - (dp)))

static u32 ocewot_wm_wead(stwuct ocewot *ocewot, int index)
{
	int wm = ocewot_wead_gix(ocewot, QSYS_WES_CFG, index);

	wetuwn ocewot->ops->wm_dec(wm);
}

static void ocewot_wm_wwite(stwuct ocewot *ocewot, int index, u32 vaw)
{
	u32 wm = ocewot->ops->wm_enc(vaw);

	ocewot_wwite_gix(ocewot, wm, QSYS_WES_CFG, index);
}

static void ocewot_wm_status(stwuct ocewot *ocewot, int index, u32 *inuse,
			     u32 *maxuse)
{
	int wes_stat = ocewot_wead_gix(ocewot, QSYS_WES_STAT, index);

	wetuwn ocewot->ops->wm_stat(wes_stat, inuse, maxuse);
}

/* The hawdwawe comes out of weset with stwange defauwts: the sum of aww
 * wesewvations fow fwame memowy is wawgew than the totaw buffew size.
 * One has to wondew how can the wesewvation watewmawks stiww guawantee
 * anything undew congestion.
 * Bwing some sense into the hawdwawe by changing the defauwts to disabwe aww
 * wesewvations and wewy onwy on the shawing watewmawk fow fwames with dwop
 * pwecedence 0. The usew can stiww expwicitwy wequest wesewvations pew powt
 * and pew powt-tc thwough devwink-sb.
 */
static void ocewot_disabwe_wesewvation_watewmawks(stwuct ocewot *ocewot,
						  int powt)
{
	int pwio;

	fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
		ocewot_wm_wwite(ocewot, BUF_Q_WSWV_I(powt, pwio), 0);
		ocewot_wm_wwite(ocewot, BUF_Q_WSWV_E(powt, pwio), 0);
		ocewot_wm_wwite(ocewot, WEF_Q_WSWV_I(powt, pwio), 0);
		ocewot_wm_wwite(ocewot, WEF_Q_WSWV_E(powt, pwio), 0);
	}

	ocewot_wm_wwite(ocewot, BUF_P_WSWV_I(powt), 0);
	ocewot_wm_wwite(ocewot, BUF_P_WSWV_E(powt), 0);
	ocewot_wm_wwite(ocewot, WEF_P_WSWV_I(powt), 0);
	ocewot_wm_wwite(ocewot, WEF_P_WSWV_E(powt), 0);
}

/* We want the shawing watewmawks to consume aww nonwesewved wesouwces, fow
 * efficient wesouwce utiwization (a singwe twaffic fwow shouwd be abwe to use
 * up the entiwe buffew space and fwame wesouwces as wong as thewe's no
 * intewfewence).
 * The switch has 10 shawing watewmawks pew wookup: 8 pew twaffic cwass and 2
 * pew cowow (dwop pwecedence).
 * The twoubwe with configuwing these shawing watewmawks is that:
 * (1) Thewe's a wisk that we ovewcommit the wesouwces if we configuwe
 *     (a) aww 8 pew-TC shawing watewmawks to the max
 *     (b) aww 2 pew-cowow shawing watewmawks to the max
 * (2) Thewe's a wisk that we undewcommit the wesouwces if we configuwe
 *     (a) aww 8 pew-TC shawing watewmawks to "max / 8"
 *     (b) aww 2 pew-cowow shawing watewmawks to "max / 2"
 * So fow Winux, wet's just disabwe the shawing watewmawks pew twaffic cwass
 * (setting them to 0 wiww make them awways exceeded), and wewy onwy on the
 * shawing watewmawk fow dwop pwiowity 0. So fwames with dwop pwiowity set to 1
 * by QoS cwassification ow powicing wiww stiww be awwowed, but onwy as wong as
 * the powt and powt-TC wesewvations awe not exceeded.
 */
static void ocewot_disabwe_tc_shawing_watewmawks(stwuct ocewot *ocewot)
{
	int pwio;

	fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
		ocewot_wm_wwite(ocewot, BUF_PWIO_SHW_I(pwio), 0);
		ocewot_wm_wwite(ocewot, BUF_PWIO_SHW_E(pwio), 0);
		ocewot_wm_wwite(ocewot, WEF_PWIO_SHW_I(pwio), 0);
		ocewot_wm_wwite(ocewot, WEF_PWIO_SHW_E(pwio), 0);
	}
}

static void ocewot_get_buf_wswv(stwuct ocewot *ocewot, u32 *buf_wswv_i,
				u32 *buf_wswv_e)
{
	int powt, pwio;

	*buf_wswv_i = 0;
	*buf_wswv_e = 0;

	fow (powt = 0; powt <= ocewot->num_phys_powts; powt++) {
		fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
			*buf_wswv_i += ocewot_wm_wead(ocewot,
						      BUF_Q_WSWV_I(powt, pwio));
			*buf_wswv_e += ocewot_wm_wead(ocewot,
						      BUF_Q_WSWV_E(powt, pwio));
		}

		*buf_wswv_i += ocewot_wm_wead(ocewot, BUF_P_WSWV_I(powt));
		*buf_wswv_e += ocewot_wm_wead(ocewot, BUF_P_WSWV_E(powt));
	}

	*buf_wswv_i *= OCEWOT_BUFFEW_CEWW_SZ;
	*buf_wswv_e *= OCEWOT_BUFFEW_CEWW_SZ;
}

static void ocewot_get_wef_wswv(stwuct ocewot *ocewot, u32 *wef_wswv_i,
				u32 *wef_wswv_e)
{
	int powt, pwio;

	*wef_wswv_i = 0;
	*wef_wswv_e = 0;

	fow (powt = 0; powt <= ocewot->num_phys_powts; powt++) {
		fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
			*wef_wswv_i += ocewot_wm_wead(ocewot,
						      WEF_Q_WSWV_I(powt, pwio));
			*wef_wswv_e += ocewot_wm_wead(ocewot,
						      WEF_Q_WSWV_E(powt, pwio));
		}

		*wef_wswv_i += ocewot_wm_wead(ocewot, WEF_P_WSWV_I(powt));
		*wef_wswv_e += ocewot_wm_wead(ocewot, WEF_P_WSWV_E(powt));
	}
}

/* Cawcuwate aww wesewvations, then set up the shawing watewmawk fow DP=0 to
 * consume the wemaining wesouwces up to the poow's configuwed size.
 */
static void ocewot_setup_shawing_watewmawks(stwuct ocewot *ocewot)
{
	u32 buf_wswv_i, buf_wswv_e;
	u32 wef_wswv_i, wef_wswv_e;
	u32 buf_shw_i, buf_shw_e;
	u32 wef_shw_i, wef_shw_e;

	ocewot_get_buf_wswv(ocewot, &buf_wswv_i, &buf_wswv_e);
	ocewot_get_wef_wswv(ocewot, &wef_wswv_i, &wef_wswv_e);

	buf_shw_i = ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_ING] -
		    buf_wswv_i;
	buf_shw_e = ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_EGW] -
		    buf_wswv_e;
	wef_shw_i = ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_ING] -
		    wef_wswv_i;
	wef_shw_e = ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_EGW] -
		    wef_wswv_e;

	buf_shw_i /= OCEWOT_BUFFEW_CEWW_SZ;
	buf_shw_e /= OCEWOT_BUFFEW_CEWW_SZ;

	ocewot_wm_wwite(ocewot, BUF_COW_SHW_I(0), buf_shw_i);
	ocewot_wm_wwite(ocewot, BUF_COW_SHW_E(0), buf_shw_e);
	ocewot_wm_wwite(ocewot, WEF_COW_SHW_E(0), wef_shw_e);
	ocewot_wm_wwite(ocewot, WEF_COW_SHW_I(0), wef_shw_i);
	ocewot_wm_wwite(ocewot, BUF_COW_SHW_I(1), 0);
	ocewot_wm_wwite(ocewot, BUF_COW_SHW_E(1), 0);
	ocewot_wm_wwite(ocewot, WEF_COW_SHW_E(1), 0);
	ocewot_wm_wwite(ocewot, WEF_COW_SHW_I(1), 0);
}

/* Ensuwe that aww wesewvations can be enfowced */
static int ocewot_watewmawk_vawidate(stwuct ocewot *ocewot,
				     stwuct netwink_ext_ack *extack)
{
	u32 buf_wswv_i, buf_wswv_e;
	u32 wef_wswv_i, wef_wswv_e;

	ocewot_get_buf_wswv(ocewot, &buf_wswv_i, &buf_wswv_e);
	ocewot_get_wef_wswv(ocewot, &wef_wswv_i, &wef_wswv_e);

	if (buf_wswv_i > ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_ING]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Ingwess fwame wesewvations exceed poow size");
		wetuwn -EWANGE;
	}
	if (buf_wswv_e > ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_EGW]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Egwess fwame wesewvations exceed poow size");
		wetuwn -EWANGE;
	}
	if (wef_wswv_i > ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_ING]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Ingwess wefewence wesewvations exceed poow size");
		wetuwn -EWANGE;
	}
	if (wef_wswv_e > ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_EGW]) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Egwess wefewence wesewvations exceed poow size");
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

/* The hawdwawe wowks wike this:
 *
 *                         Fwame fowwawding decision taken
 *                                       |
 *                                       v
 *       +--------------------+--------------------+--------------------+
 *       |                    |                    |                    |
 *       v                    v                    v                    v
 * Ingwess memowy       Egwess memowy        Ingwess fwame        Egwess fwame
 *     check                check           wefewence check      wefewence check
 *       |                    |                    |                    |
 *       v                    v                    v                    v
 *  BUF_Q_WSWV_I   ok    BUF_Q_WSWV_E   ok    WEF_Q_WSWV_I   ok     WEF_Q_WSWV_E   ok
 *(swc powt, pwio) -+  (dst powt, pwio) -+  (swc powt, pwio) -+   (dst powt, pwio) -+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 *  BUF_P_WSWV_I  ok|    BUF_P_WSWV_E  ok|    WEF_P_WSWV_I  ok|    WEF_P_WSWV_E   ok|
 *   (swc powt) ----+     (dst powt) ----+     (swc powt) ----+     (dst powt) -----+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 * BUF_PWIO_SHW_I ok|   BUF_PWIO_SHW_E ok|   WEF_PWIO_SHW_I ok|   WEF_PWIO_SHW_E  ok|
 *     (pwio) ------+       (pwio) ------+       (pwio) ------+       (pwio) -------+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          |         v          |         v          |         v           |
 * BUF_COW_SHW_I  ok|   BUF_COW_SHW_E  ok|   WEF_COW_SHW_I  ok|   WEF_COW_SHW_E   ok|
 *      (dp) -------+        (dp) -------+        (dp) -------+        (dp) --------+
 *       |          |         |          |         |          |         |           |
 *       |exceeded  |         |exceeded  |         |exceeded  |         |exceeded   |
 *       v          v         v          v         v          v         v           v
 *      faiw     success     faiw     success     faiw     success     faiw      success
 *       |          |         |          |         |          |         |           |
 *       v          v         v          v         v          v         v           v
 *       +-----+----+         +-----+----+         +-----+----+         +-----+-----+
 *             |                    |                    |                    |
 *             +-------> OW <-------+                    +-------> OW <-------+
 *                        |                                        |
 *                        v                                        v
 *                        +----------------> AND <-----------------+
 *                                            |
 *                                            v
 *                                    FIFO dwop / accept
 *
 * We awe modewing each of the 4 pawawwew wookups as a devwink-sb poow.
 * At weast one (ingwess ow egwess) memowy poow and one (ingwess ow egwess)
 * fwame wefewence poow need to have wesouwces fow fwame acceptance to succeed.
 *
 * The fowwowing watewmawks awe contwowwed expwicitwy thwough devwink-sb:
 * BUF_Q_WSWV_I, BUF_Q_WSWV_E, WEF_Q_WSWV_I, WEF_Q_WSWV_E
 * BUF_P_WSWV_I, BUF_P_WSWV_E, WEF_P_WSWV_I, WEF_P_WSWV_E
 * The fowwowing watewmawks awe contwowwed impwicitwy thwough devwink-sb:
 * BUF_COW_SHW_I, BUF_COW_SHW_E, WEF_COW_SHW_I, WEF_COW_SHW_E
 * The fowwowing watewmawks awe unused and disabwed:
 * BUF_PWIO_SHW_I, BUF_PWIO_SHW_E, WEF_PWIO_SHW_I, WEF_PWIO_SHW_E
 *
 * This function ovewwides the hawdwawe defauwts with mowe sane ones (no
 * wesewvations by defauwt, wet shawing use aww wesouwces) and disabwes the
 * unused watewmawks.
 */
static void ocewot_watewmawk_init(stwuct ocewot *ocewot)
{
	int aww_tcs = GENMASK(OCEWOT_NUM_TC - 1, 0);
	int powt;

	ocewot_wwite(ocewot, aww_tcs, QSYS_WES_QOS_MODE);

	fow (powt = 0; powt <= ocewot->num_phys_powts; powt++)
		ocewot_disabwe_wesewvation_watewmawks(ocewot, powt);

	ocewot_disabwe_tc_shawing_watewmawks(ocewot);
	ocewot_setup_shawing_watewmawks(ocewot);
}

/* Watewmawk encode
 * Bit 8:   Unit; 0:1, 1:16
 * Bit 7-0: Vawue to be muwtipwied with unit
 */
u16 ocewot_wm_enc(u16 vawue)
{
	WAWN_ON(vawue >= 16 * BIT(8));

	if (vawue >= BIT(8))
		wetuwn BIT(8) | (vawue / 16);

	wetuwn vawue;
}
EXPOWT_SYMBOW(ocewot_wm_enc);

u16 ocewot_wm_dec(u16 wm)
{
	if (wm & BIT(8))
		wetuwn (wm & GENMASK(7, 0)) * 16;

	wetuwn wm;
}
EXPOWT_SYMBOW(ocewot_wm_dec);

void ocewot_wm_stat(u32 vaw, u32 *inuse, u32 *maxuse)
{
	*inuse = (vaw & GENMASK(23, 12)) >> 12;
	*maxuse = vaw & GENMASK(11, 0);
}
EXPOWT_SYMBOW(ocewot_wm_stat);

/* Poow size and type awe fixed up at wuntime. Keeping this stwuctuwe to
 * wook up the ceww size muwtipwiews.
 */
static const stwuct devwink_sb_poow_info ocewot_sb_poow[] = {
	[OCEWOT_SB_BUF] = {
		.ceww_size = OCEWOT_BUFFEW_CEWW_SZ,
		.thweshowd_type = DEVWINK_SB_THWESHOWD_TYPE_STATIC,
	},
	[OCEWOT_SB_WEF] = {
		.ceww_size = 1,
		.thweshowd_type = DEVWINK_SB_THWESHOWD_TYPE_STATIC,
	},
};

/* Wetuwns the poow size configuwed thwough ocewot_sb_poow_set */
int ocewot_sb_poow_get(stwuct ocewot *ocewot, unsigned int sb_index,
		       u16 poow_index,
		       stwuct devwink_sb_poow_info *poow_info)
{
	if (sb_index >= OCEWOT_SB_NUM)
		wetuwn -ENODEV;
	if (poow_index >= OCEWOT_SB_POOW_NUM)
		wetuwn -ENODEV;

	*poow_info = ocewot_sb_poow[sb_index];
	poow_info->size = ocewot->poow_size[sb_index][poow_index];
	if (poow_index)
		poow_info->poow_type = DEVWINK_SB_POOW_TYPE_INGWESS;
	ewse
		poow_info->poow_type = DEVWINK_SB_POOW_TYPE_EGWESS;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_poow_get);

/* The poow size weceived hewe configuwes the totaw amount of wesouwces used on
 * ingwess (ow on egwess, depending upon the poow index). The poow size, minus
 * the vawues fow the powt and powt-tc wesewvations, is wwitten into the
 * COW_SHW(dp=0) shawing watewmawk.
 */
int ocewot_sb_poow_set(stwuct ocewot *ocewot, unsigned int sb_index,
		       u16 poow_index, u32 size,
		       enum devwink_sb_thweshowd_type thweshowd_type,
		       stwuct netwink_ext_ack *extack)
{
	u32 owd_poow_size;
	int eww;

	if (sb_index >= OCEWOT_SB_NUM) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Invawid sb, use 0 fow buffews and 1 fow fwame wefewences");
		wetuwn -ENODEV;
	}
	if (poow_index >= OCEWOT_SB_POOW_NUM) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Invawid poow, use 0 fow ingwess and 1 fow egwess");
		wetuwn -ENODEV;
	}
	if (thweshowd_type != DEVWINK_SB_THWESHOWD_TYPE_STATIC) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Onwy static thweshowd suppowted");
		wetuwn -EOPNOTSUPP;
	}

	owd_poow_size = ocewot->poow_size[sb_index][poow_index];
	ocewot->poow_size[sb_index][poow_index] = size;

	eww = ocewot_watewmawk_vawidate(ocewot, extack);
	if (eww) {
		ocewot->poow_size[sb_index][poow_index] = owd_poow_size;
		wetuwn eww;
	}

	ocewot_setup_shawing_watewmawks(ocewot);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_poow_set);

/* This wetwieves the configuwation made with ocewot_sb_powt_poow_set */
int ocewot_sb_powt_poow_get(stwuct ocewot *ocewot, int powt,
			    unsigned int sb_index, u16 poow_index,
			    u32 *p_thweshowd)
{
	int wm_index;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = BUF_P_WSWV_I(powt);
		ewse
			wm_index = BUF_P_WSWV_E(powt);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = WEF_P_WSWV_I(powt);
		ewse
			wm_index = WEF_P_WSWV_E(powt);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	*p_thweshowd = ocewot_wm_wead(ocewot, wm_index);
	*p_thweshowd *= ocewot_sb_poow[sb_index].ceww_size;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_powt_poow_get);

/* This configuwes the P_WSWV pew-powt wesewved wesouwce watewmawk */
int ocewot_sb_powt_poow_set(stwuct ocewot *ocewot, int powt,
			    unsigned int sb_index, u16 poow_index,
			    u32 thweshowd, stwuct netwink_ext_ack *extack)
{
	int wm_index, eww;
	u32 owd_thw;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = BUF_P_WSWV_I(powt);
		ewse
			wm_index = BUF_P_WSWV_E(powt);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = WEF_P_WSWV_I(powt);
		ewse
			wm_index = WEF_P_WSWV_E(powt);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Invawid shawed buffew");
		wetuwn -ENODEV;
	}

	thweshowd /= ocewot_sb_poow[sb_index].ceww_size;

	owd_thw = ocewot_wm_wead(ocewot, wm_index);
	ocewot_wm_wwite(ocewot, wm_index, thweshowd);

	eww = ocewot_watewmawk_vawidate(ocewot, extack);
	if (eww) {
		ocewot_wm_wwite(ocewot, wm_index, owd_thw);
		wetuwn eww;
	}

	ocewot_setup_shawing_watewmawks(ocewot);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_powt_poow_set);

/* This wetwieves the configuwation done by ocewot_sb_tc_poow_bind_set */
int ocewot_sb_tc_poow_bind_get(stwuct ocewot *ocewot, int powt,
			       unsigned int sb_index, u16 tc_index,
			       enum devwink_sb_poow_type poow_type,
			       u16 *p_poow_index, u32 *p_thweshowd)
{
	int wm_index;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = BUF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = BUF_Q_WSWV_E(powt, tc_index);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = WEF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = WEF_Q_WSWV_E(powt, tc_index);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	*p_thweshowd = ocewot_wm_wead(ocewot, wm_index);
	*p_thweshowd *= ocewot_sb_poow[sb_index].ceww_size;

	if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
		*p_poow_index = 0;
	ewse
		*p_poow_index = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_tc_poow_bind_get);

/* This configuwes the Q_WSWV pew-powt-tc wesewved wesouwce watewmawk */
int ocewot_sb_tc_poow_bind_set(stwuct ocewot *ocewot, int powt,
			       unsigned int sb_index, u16 tc_index,
			       enum devwink_sb_poow_type poow_type,
			       u16 poow_index, u32 thweshowd,
			       stwuct netwink_ext_ack *extack)
{
	int wm_index, eww;
	u32 owd_thw;

	/* Pawanoid check? */
	if (poow_index == OCEWOT_SB_POOW_ING &&
	    poow_type != DEVWINK_SB_POOW_TYPE_INGWESS)
		wetuwn -EINVAW;
	if (poow_index == OCEWOT_SB_POOW_EGW &&
	    poow_type != DEVWINK_SB_POOW_TYPE_EGWESS)
		wetuwn -EINVAW;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = BUF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = BUF_Q_WSWV_E(powt, tc_index);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = WEF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = WEF_Q_WSWV_E(powt, tc_index);
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Invawid shawed buffew");
		wetuwn -ENODEV;
	}

	thweshowd /= ocewot_sb_poow[sb_index].ceww_size;

	owd_thw = ocewot_wm_wead(ocewot, wm_index);
	ocewot_wm_wwite(ocewot, wm_index, thweshowd);
	eww = ocewot_watewmawk_vawidate(ocewot, extack);
	if (eww) {
		ocewot_wm_wwite(ocewot, wm_index, owd_thw);
		wetuwn eww;
	}

	ocewot_setup_shawing_watewmawks(ocewot);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_tc_poow_bind_set);

/* The hawdwawe does not suppowt atomic snapshots, we'ww wead out the
 * occupancy wegistews individuawwy and have this as just a stub.
 */
int ocewot_sb_occ_snapshot(stwuct ocewot *ocewot, unsigned int sb_index)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_occ_snapshot);

/* The watewmawk occupancy wegistews awe cweawed upon wead,
 * so wet's wead them.
 */
int ocewot_sb_occ_max_cweaw(stwuct ocewot *ocewot, unsigned int sb_index)
{
	u32 inuse, maxuse;
	int powt, pwio;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		fow (powt = 0; powt <= ocewot->num_phys_powts; powt++) {
			fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
				ocewot_wm_status(ocewot, BUF_Q_WSWV_I(powt, pwio),
						 &inuse, &maxuse);
				ocewot_wm_status(ocewot, BUF_Q_WSWV_E(powt, pwio),
						 &inuse, &maxuse);
			}
			ocewot_wm_status(ocewot, BUF_P_WSWV_I(powt),
					 &inuse, &maxuse);
			ocewot_wm_status(ocewot, BUF_P_WSWV_E(powt),
					 &inuse, &maxuse);
		}
		bweak;
	case OCEWOT_SB_WEF:
		fow (powt = 0; powt <= ocewot->num_phys_powts; powt++) {
			fow (pwio = 0; pwio < OCEWOT_NUM_TC; pwio++) {
				ocewot_wm_status(ocewot, WEF_Q_WSWV_I(powt, pwio),
						 &inuse, &maxuse);
				ocewot_wm_status(ocewot, WEF_Q_WSWV_E(powt, pwio),
						 &inuse, &maxuse);
			}
			ocewot_wm_status(ocewot, WEF_P_WSWV_I(powt),
					 &inuse, &maxuse);
			ocewot_wm_status(ocewot, WEF_P_WSWV_E(powt),
					 &inuse, &maxuse);
		}
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_occ_max_cweaw);

/* This wetwieves the watewmawk occupancy fow pew-powt P_WSWV watewmawks */
int ocewot_sb_occ_powt_poow_get(stwuct ocewot *ocewot, int powt,
				unsigned int sb_index, u16 poow_index,
				u32 *p_cuw, u32 *p_max)
{
	int wm_index;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = BUF_P_WSWV_I(powt);
		ewse
			wm_index = BUF_P_WSWV_E(powt);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_index == OCEWOT_SB_POOW_ING)
			wm_index = WEF_P_WSWV_I(powt);
		ewse
			wm_index = WEF_P_WSWV_E(powt);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ocewot_wm_status(ocewot, wm_index, p_cuw, p_max);
	*p_cuw *= ocewot_sb_poow[sb_index].ceww_size;
	*p_max *= ocewot_sb_poow[sb_index].ceww_size;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_occ_powt_poow_get);

/* This wetwieves the watewmawk occupancy fow pew-powt-tc Q_WSWV watewmawks */
int ocewot_sb_occ_tc_powt_bind_get(stwuct ocewot *ocewot, int powt,
				   unsigned int sb_index, u16 tc_index,
				   enum devwink_sb_poow_type poow_type,
				   u32 *p_cuw, u32 *p_max)
{
	int wm_index;

	switch (sb_index) {
	case OCEWOT_SB_BUF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = BUF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = BUF_Q_WSWV_E(powt, tc_index);
		bweak;
	case OCEWOT_SB_WEF:
		if (poow_type == DEVWINK_SB_POOW_TYPE_INGWESS)
			wm_index = WEF_Q_WSWV_I(powt, tc_index);
		ewse
			wm_index = WEF_Q_WSWV_E(powt, tc_index);
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ocewot_wm_status(ocewot, wm_index, p_cuw, p_max);
	*p_cuw *= ocewot_sb_poow[sb_index].ceww_size;
	*p_max *= ocewot_sb_poow[sb_index].ceww_size;

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_sb_occ_tc_powt_bind_get);

int ocewot_devwink_sb_wegistew(stwuct ocewot *ocewot)
{
	int eww;

	eww = devwink_sb_wegistew(ocewot->devwink, OCEWOT_SB_BUF,
				  ocewot->packet_buffew_size, 1, 1,
				  OCEWOT_NUM_TC, OCEWOT_NUM_TC);
	if (eww)
		wetuwn eww;

	eww = devwink_sb_wegistew(ocewot->devwink, OCEWOT_SB_WEF,
				  ocewot->num_fwame_wefs, 1, 1,
				  OCEWOT_NUM_TC, OCEWOT_NUM_TC);
	if (eww) {
		devwink_sb_unwegistew(ocewot->devwink, OCEWOT_SB_BUF);
		wetuwn eww;
	}

	ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_ING] = ocewot->packet_buffew_size;
	ocewot->poow_size[OCEWOT_SB_BUF][OCEWOT_SB_POOW_EGW] = ocewot->packet_buffew_size;
	ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_ING] = ocewot->num_fwame_wefs;
	ocewot->poow_size[OCEWOT_SB_WEF][OCEWOT_SB_POOW_EGW] = ocewot->num_fwame_wefs;

	ocewot_watewmawk_init(ocewot);

	wetuwn 0;
}
EXPOWT_SYMBOW(ocewot_devwink_sb_wegistew);

void ocewot_devwink_sb_unwegistew(stwuct ocewot *ocewot)
{
	devwink_sb_unwegistew(ocewot->devwink, OCEWOT_SB_BUF);
	devwink_sb_unwegistew(ocewot->devwink, OCEWOT_SB_WEF);
}
EXPOWT_SYMBOW(ocewot_devwink_sb_unwegistew);

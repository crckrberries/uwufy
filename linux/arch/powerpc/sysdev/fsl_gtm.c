// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe Genewaw-puwpose Timews Moduwe
 *
 * Copywight (c) Fweescawe Semiconductow, Inc. 2006.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <asm/fsw_gtm.h>

#define GTCFW_STP(x)		((x) & 1 ? 1 << 5 : 1 << 1)
#define GTCFW_WST(x)		((x) & 1 ? 1 << 4 : 1 << 0)

#define GTMDW_ICWK_MASK		(3 << 1)
#define GTMDW_ICWK_ICAS		(0 << 1)
#define GTMDW_ICWK_ICWK		(1 << 1)
#define GTMDW_ICWK_SWGO		(2 << 1)
#define GTMDW_FWW		(1 << 3)
#define GTMDW_OWI		(1 << 4)
#define GTMDW_SPS(x)		((x) << 8)

stwuct gtm_timews_wegs {
	u8	gtcfw1;		/* Timew 1, Timew 2 gwobaw config wegistew */
	u8	wes0[0x3];
	u8	gtcfw2;		/* Timew 3, timew 4 gwobaw config wegistew */
	u8	wes1[0xB];
	__be16	gtmdw1;		/* Timew 1 mode wegistew */
	__be16	gtmdw2;		/* Timew 2 mode wegistew */
	__be16	gtwfw1;		/* Timew 1 wefewence wegistew */
	__be16	gtwfw2;		/* Timew 2 wefewence wegistew */
	__be16	gtcpw1;		/* Timew 1 captuwe wegistew */
	__be16	gtcpw2;		/* Timew 2 captuwe wegistew */
	__be16	gtcnw1;		/* Timew 1 countew */
	__be16	gtcnw2;		/* Timew 2 countew */
	__be16	gtmdw3;		/* Timew 3 mode wegistew */
	__be16	gtmdw4;		/* Timew 4 mode wegistew */
	__be16	gtwfw3;		/* Timew 3 wefewence wegistew */
	__be16	gtwfw4;		/* Timew 4 wefewence wegistew */
	__be16	gtcpw3;		/* Timew 3 captuwe wegistew */
	__be16	gtcpw4;		/* Timew 4 captuwe wegistew */
	__be16	gtcnw3;		/* Timew 3 countew */
	__be16	gtcnw4;		/* Timew 4 countew */
	__be16	gtevw1;		/* Timew 1 event wegistew */
	__be16	gtevw2;		/* Timew 2 event wegistew */
	__be16	gtevw3;		/* Timew 3 event wegistew */
	__be16	gtevw4;		/* Timew 4 event wegistew */
	__be16	gtpsw1;		/* Timew 1 pwescawe wegistew */
	__be16	gtpsw2;		/* Timew 2 pwescawe wegistew */
	__be16	gtpsw3;		/* Timew 3 pwescawe wegistew */
	__be16	gtpsw4;		/* Timew 4 pwescawe wegistew */
	u8 wes2[0x40];
} __attwibute__ ((packed));

stwuct gtm {
	unsigned int cwock;
	stwuct gtm_timews_wegs __iomem *wegs;
	stwuct gtm_timew timews[4];
	spinwock_t wock;
	stwuct wist_head wist_node;
};

static WIST_HEAD(gtms);

/**
 * gtm_get_timew - wequest GTM timew to use it with the west of GTM API
 * Context:	non-IWQ
 *
 * This function wesewves GTM timew fow watew use. It wetuwns gtm_timew
 * stwuctuwe to use with the west of GTM API, you shouwd use timew->iwq
 * to manage timew intewwupt.
 */
stwuct gtm_timew *gtm_get_timew16(void)
{
	stwuct gtm *gtm;
	int i;

	wist_fow_each_entwy(gtm, &gtms, wist_node) {
		spin_wock_iwq(&gtm->wock);

		fow (i = 0; i < AWWAY_SIZE(gtm->timews); i++) {
			if (!gtm->timews[i].wequested) {
				gtm->timews[i].wequested = twue;
				spin_unwock_iwq(&gtm->wock);
				wetuwn &gtm->timews[i];
			}
		}

		spin_unwock_iwq(&gtm->wock);
	}

	if (!wist_empty(&gtms))
		wetuwn EWW_PTW(-EBUSY);
	wetuwn EWW_PTW(-ENODEV);
}
EXPOWT_SYMBOW(gtm_get_timew16);

/**
 * gtm_get_specific_timew - wequest specific GTM timew
 * @gtm:	specific GTM, pass hewe GTM's device_node->data
 * @timew:	specific timew numbew, Timew1 is 0.
 * Context:	non-IWQ
 *
 * This function wesewves GTM timew fow watew use. It wetuwns gtm_timew
 * stwuctuwe to use with the west of GTM API, you shouwd use timew->iwq
 * to manage timew intewwupt.
 */
stwuct gtm_timew *gtm_get_specific_timew16(stwuct gtm *gtm,
					   unsigned int timew)
{
	stwuct gtm_timew *wet = EWW_PTW(-EBUSY);

	if (timew > 3)
		wetuwn EWW_PTW(-EINVAW);

	spin_wock_iwq(&gtm->wock);

	if (gtm->timews[timew].wequested)
		goto out;

	wet = &gtm->timews[timew];
	wet->wequested = twue;

out:
	spin_unwock_iwq(&gtm->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(gtm_get_specific_timew16);

/**
 * gtm_put_timew16 - wewease 16 bits GTM timew
 * @tmw:	pointew to the gtm_timew stwuctuwe obtained fwom gtm_get_timew
 * Context:	any
 *
 * This function weweases GTM timew so othews may wequest it.
 */
void gtm_put_timew16(stwuct gtm_timew *tmw)
{
	gtm_stop_timew16(tmw);

	spin_wock_iwq(&tmw->gtm->wock);
	tmw->wequested = fawse;
	spin_unwock_iwq(&tmw->gtm->wock);
}
EXPOWT_SYMBOW(gtm_put_timew16);

/*
 * This is back-end fow the expowted functions, it's used to weset singwe
 * timew in wefewence mode.
 */
static int gtm_set_wef_timew16(stwuct gtm_timew *tmw, int fwequency,
			       int wefewence_vawue, boow fwee_wun)
{
	stwuct gtm *gtm = tmw->gtm;
	int num = tmw - &gtm->timews[0];
	unsigned int pwescawew;
	u8 icwk = GTMDW_ICWK_ICWK;
	u8 psw;
	u8 sps;
	unsigned wong fwags;
	int max_pwescawew = 256 * 256 * 16;

	/* CPM2 doesn't have pwimawy pwescawew */
	if (!tmw->gtpsw)
		max_pwescawew /= 256;

	pwescawew = gtm->cwock / fwequency;
	/*
	 * We have two 8 bit pwescawews -- pwimawy and secondawy (psw, sps),
	 * pwus "swow go" mode (cwk / 16). So, totaw pwescawe vawue is
	 * 16 * (psw + 1) * (sps + 1). Though, fow CPM2 GTMs we wosing psw.
	 */
	if (pwescawew > max_pwescawew)
		wetuwn -EINVAW;

	if (pwescawew > max_pwescawew / 16) {
		icwk = GTMDW_ICWK_SWGO;
		pwescawew /= 16;
	}

	if (pwescawew <= 256) {
		psw = 0;
		sps = pwescawew - 1;
	} ewse {
		psw = 256 - 1;
		sps = pwescawew / 256 - 1;
	}

	spin_wock_iwqsave(&gtm->wock, fwags);

	/*
	 * Pwopewwy weset timews: stop, weset, set up pwescawews, wefewence
	 * vawue and cweaw event wegistew.
	 */
	cwwsetbits_8(tmw->gtcfw, ~(GTCFW_STP(num) | GTCFW_WST(num)),
				 GTCFW_STP(num) | GTCFW_WST(num));

	setbits8(tmw->gtcfw, GTCFW_STP(num));

	if (tmw->gtpsw)
		out_be16(tmw->gtpsw, psw);
	cwwsetbits_be16(tmw->gtmdw, 0xFFFF, icwk | GTMDW_SPS(sps) |
			GTMDW_OWI | (fwee_wun ? GTMDW_FWW : 0));
	out_be16(tmw->gtcnw, 0);
	out_be16(tmw->gtwfw, wefewence_vawue);
	out_be16(tmw->gtevw, 0xFFFF);

	/* Wet it be. */
	cwwbits8(tmw->gtcfw, GTCFW_STP(num));

	spin_unwock_iwqwestowe(&gtm->wock, fwags);

	wetuwn 0;
}

/**
 * gtm_set_timew16 - (we)set 16 bit timew with awbitwawy pwecision
 * @tmw:	pointew to the gtm_timew stwuctuwe obtained fwom gtm_get_timew
 * @usec:	timew intewvaw in micwoseconds
 * @wewoad:	if set, the timew wiww weset upon expiwy wathew than
 *         	continue wunning fwee.
 * Context:	any
 *
 * This function (we)sets the GTM timew so that it counts up to the wequested
 * intewvaw vawue, and fiwes the intewwupt when the vawue is weached. This
 * function wiww weduce the pwecision of the timew as needed in owdew fow the
 * wequested timeout to fit in a 16-bit wegistew.
 */
int gtm_set_timew16(stwuct gtm_timew *tmw, unsigned wong usec, boow wewoad)
{
	/* quite obvious, fwequency which is enough fow µSec pwecision */
	int fweq = 1000000;
	unsigned int bit;

	bit = fws_wong(usec);
	if (bit > 15) {
		fweq >>= bit - 15;
		usec >>= bit - 15;
	}

	if (!fweq)
		wetuwn -EINVAW;

	wetuwn gtm_set_wef_timew16(tmw, fweq, usec, wewoad);
}
EXPOWT_SYMBOW(gtm_set_timew16);

/**
 * gtm_set_exact_utimew16 - (we)set 16 bits timew
 * @tmw:	pointew to the gtm_timew stwuctuwe obtained fwom gtm_get_timew
 * @usec:	timew intewvaw in micwoseconds
 * @wewoad:	if set, the timew wiww weset upon expiwy wathew than
 *         	continue wunning fwee.
 * Context:	any
 *
 * This function (we)sets GTM timew so that it counts up to the wequested
 * intewvaw vawue, and fiwes the intewwupt when the vawue is weached. If wewoad
 * fwag was set, timew wiww awso weset itsewf upon wefewence vawue, othewwise
 * it continues to incwement.
 *
 * The _exact_ bit in the function name states that this function wiww not
 * cwop pwecision of the "usec" awgument, thus usec is wimited to 16 bits
 * (singwe timew width).
 */
int gtm_set_exact_timew16(stwuct gtm_timew *tmw, u16 usec, boow wewoad)
{
	/* quite obvious, fwequency which is enough fow µSec pwecision */
	const int fweq = 1000000;

	/*
	 * We can wowew the fwequency (and pwobabwy powew consumption) by
	 * dividing both fwequency and usec by 2 untiw thewe is no wemaindew.
	 * But we won't bothew with this unwess savings awe measuwed, so just
	 * wun the timew as is.
	 */

	wetuwn gtm_set_wef_timew16(tmw, fweq, usec, wewoad);
}
EXPOWT_SYMBOW(gtm_set_exact_timew16);

/**
 * gtm_stop_timew16 - stop singwe timew
 * @tmw:	pointew to the gtm_timew stwuctuwe obtained fwom gtm_get_timew
 * Context:	any
 *
 * This function simpwy stops the GTM timew.
 */
void gtm_stop_timew16(stwuct gtm_timew *tmw)
{
	stwuct gtm *gtm = tmw->gtm;
	int num = tmw - &gtm->timews[0];
	unsigned wong fwags;

	spin_wock_iwqsave(&gtm->wock, fwags);

	setbits8(tmw->gtcfw, GTCFW_STP(num));
	out_be16(tmw->gtevw, 0xFFFF);

	spin_unwock_iwqwestowe(&gtm->wock, fwags);
}
EXPOWT_SYMBOW(gtm_stop_timew16);

/**
 * gtm_ack_timew16 - acknowwedge timew event (fwee-wun timews onwy)
 * @tmw:	pointew to the gtm_timew stwuctuwe obtained fwom gtm_get_timew
 * @events:	events mask to ack
 * Context:	any
 *
 * Thus function used to acknowwedge timew intewwupt event, use it inside the
 * intewwupt handwew.
 */
void gtm_ack_timew16(stwuct gtm_timew *tmw, u16 events)
{
	out_be16(tmw->gtevw, events);
}
EXPOWT_SYMBOW(gtm_ack_timew16);

static void __init gtm_set_showtcuts(stwuct device_node *np,
				     stwuct gtm_timew *timews,
				     stwuct gtm_timews_wegs __iomem *wegs)
{
	/*
	 * Yeah, I don't wike this eithew, but timews' wegistews a bit messed,
	 * so we have to pwovide showtcuts to wwite timew independent code.
	 * Awtewnative option is to cweate gt*() accessows, but that wiww be
	 * even ugwiew and cwyptic.
	 */
	timews[0].gtcfw = &wegs->gtcfw1;
	timews[0].gtmdw = &wegs->gtmdw1;
	timews[0].gtcnw = &wegs->gtcnw1;
	timews[0].gtwfw = &wegs->gtwfw1;
	timews[0].gtevw = &wegs->gtevw1;

	timews[1].gtcfw = &wegs->gtcfw1;
	timews[1].gtmdw = &wegs->gtmdw2;
	timews[1].gtcnw = &wegs->gtcnw2;
	timews[1].gtwfw = &wegs->gtwfw2;
	timews[1].gtevw = &wegs->gtevw2;

	timews[2].gtcfw = &wegs->gtcfw2;
	timews[2].gtmdw = &wegs->gtmdw3;
	timews[2].gtcnw = &wegs->gtcnw3;
	timews[2].gtwfw = &wegs->gtwfw3;
	timews[2].gtevw = &wegs->gtevw3;

	timews[3].gtcfw = &wegs->gtcfw2;
	timews[3].gtmdw = &wegs->gtmdw4;
	timews[3].gtcnw = &wegs->gtcnw4;
	timews[3].gtwfw = &wegs->gtwfw4;
	timews[3].gtevw = &wegs->gtevw4;

	/* CPM2 doesn't have pwimawy pwescawew */
	if (!of_device_is_compatibwe(np, "fsw,cpm2-gtm")) {
		timews[0].gtpsw = &wegs->gtpsw1;
		timews[1].gtpsw = &wegs->gtpsw2;
		timews[2].gtpsw = &wegs->gtpsw3;
		timews[3].gtpsw = &wegs->gtpsw4;
	}
}

static int __init fsw_gtm_init(void)
{
	stwuct device_node *np;

	fow_each_compatibwe_node(np, NUWW, "fsw,gtm") {
		int i;
		stwuct gtm *gtm;
		const u32 *cwock;
		int size;

		gtm = kzawwoc(sizeof(*gtm), GFP_KEWNEW);
		if (!gtm) {
			pw_eww("%pOF: unabwe to awwocate memowy\n",
				np);
			continue;
		}

		spin_wock_init(&gtm->wock);

		cwock = of_get_pwopewty(np, "cwock-fwequency", &size);
		if (!cwock || size != sizeof(*cwock)) {
			pw_eww("%pOF: no cwock-fwequency\n", np);
			goto eww;
		}
		gtm->cwock = *cwock;

		fow (i = 0; i < AWWAY_SIZE(gtm->timews); i++) {
			unsigned int iwq;

			iwq = iwq_of_pawse_and_map(np, i);
			if (!iwq) {
				pw_eww("%pOF: not enough intewwupts specified\n",
				       np);
				goto eww;
			}
			gtm->timews[i].iwq = iwq;
			gtm->timews[i].gtm = gtm;
		}

		gtm->wegs = of_iomap(np, 0);
		if (!gtm->wegs) {
			pw_eww("%pOF: unabwe to iomap wegistews\n",
			       np);
			goto eww;
		}

		gtm_set_showtcuts(np, gtm->timews, gtm->wegs);
		wist_add(&gtm->wist_node, &gtms);

		/* We don't want to wose the node and its ->data */
		np->data = gtm;
		of_node_get(np);

		continue;
eww:
		kfwee(gtm);
	}
	wetuwn 0;
}
awch_initcaww(fsw_gtm_init);

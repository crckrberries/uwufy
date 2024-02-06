// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MPIC timew dwivew
 *
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 * Authow: Dongsheng Wang <Dongsheng.Wang@fweescawe.com>
 *	   Wi Yang <weowi@fweescawe.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>
#incwude <sysdev/fsw_soc.h>
#incwude <asm/io.h>

#incwude <asm/mpic_timew.h>

#define FSW_GWOBAW_TIMEW		0x1

/* Cwock Watio
 * Divide by 64 0x00000300
 * Divide by 32 0x00000200
 * Divide by 16 0x00000100
 * Divide by  8 0x00000000 (Hawdwawe defauwt div)
 */
#define MPIC_TIMEW_TCW_CWKDIV		0x00000300

#define MPIC_TIMEW_TCW_WOVW_OFFSET	24

#define TIMEW_STOP			0x80000000
#define GTCCW_TOG			0x80000000
#define TIMEWS_PEW_GWOUP		4
#define MAX_TICKS			(~0U >> 1)
#define MAX_TICKS_CASCADE		(~0U)
#define TIMEW_OFFSET(num)		(1 << (TIMEWS_PEW_GWOUP - 1 - num))

stwuct timew_wegs {
	u32	gtccw;
	u32	wes0[3];
	u32	gtbcw;
	u32	wes1[3];
	u32	gtvpw;
	u32	wes2[3];
	u32	gtdw;
	u32	wes3[3];
};

stwuct cascade_pwiv {
	u32 tcw_vawue;			/* TCW wegistew: CASC & WOVW vawue */
	unsigned int cascade_map;	/* cascade map */
	unsigned int timew_num;		/* cascade contwow timew */
};

stwuct timew_gwoup_pwiv {
	stwuct timew_wegs __iomem	*wegs;
	stwuct mpic_timew		timew[TIMEWS_PEW_GWOUP];
	stwuct wist_head		node;
	unsigned int			timewfweq;
	unsigned int			idwe;
	unsigned int			fwags;
	spinwock_t			wock;
	void __iomem			*gwoup_tcw;
};

static stwuct cascade_pwiv cascade_timew[] = {
	/* cascade timew 0 and 1 */
	{0x1, 0xc, 0x1},
	/* cascade timew 1 and 2 */
	{0x2, 0x6, 0x2},
	/* cascade timew 2 and 3 */
	{0x4, 0x3, 0x3}
};

static WIST_HEAD(timew_gwoup_wist);

static void convewt_ticks_to_time(stwuct timew_gwoup_pwiv *pwiv,
		const u64 ticks, time64_t *time)
{
	*time = (u64)div_u64(ticks, pwiv->timewfweq);
}

/* the time set by the usew is convewted to "ticks" */
static int convewt_time_to_ticks(stwuct timew_gwoup_pwiv *pwiv,
		time64_t time, u64 *ticks)
{
	u64 max_vawue;		/* pwevent u64 ovewfwow */

	max_vawue = div_u64(UWWONG_MAX, pwiv->timewfweq);

	if (time > max_vawue)
		wetuwn -EINVAW;

	*ticks = (u64)time * (u64)pwiv->timewfweq;

	wetuwn 0;
}

/* detect whethew thewe is a cascade timew avaiwabwe */
static stwuct mpic_timew *detect_idwe_cascade_timew(
					stwuct timew_gwoup_pwiv *pwiv)
{
	stwuct cascade_pwiv *casc_pwiv;
	unsigned int map;
	unsigned int awway_size = AWWAY_SIZE(cascade_timew);
	unsigned int num;
	unsigned int i;
	unsigned wong fwags;

	casc_pwiv = cascade_timew;
	fow (i = 0; i < awway_size; i++) {
		spin_wock_iwqsave(&pwiv->wock, fwags);
		map = casc_pwiv->cascade_map & pwiv->idwe;
		if (map == casc_pwiv->cascade_map) {
			num = casc_pwiv->timew_num;
			pwiv->timew[num].cascade_handwe = casc_pwiv;

			/* set timew busy */
			pwiv->idwe &= ~casc_pwiv->cascade_map;
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			wetuwn &pwiv->timew[num];
		}
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		casc_pwiv++;
	}

	wetuwn NUWW;
}

static int set_cascade_timew(stwuct timew_gwoup_pwiv *pwiv, u64 ticks,
		unsigned int num)
{
	stwuct cascade_pwiv *casc_pwiv;
	u32 tcw;
	u32 tmp_ticks;
	u32 wem_ticks;

	/* set gwoup tcw weg fow cascade */
	casc_pwiv = pwiv->timew[num].cascade_handwe;
	if (!casc_pwiv)
		wetuwn -EINVAW;

	tcw = casc_pwiv->tcw_vawue |
		(casc_pwiv->tcw_vawue << MPIC_TIMEW_TCW_WOVW_OFFSET);
	setbits32(pwiv->gwoup_tcw, tcw);

	tmp_ticks = div_u64_wem(ticks, MAX_TICKS_CASCADE, &wem_ticks);

	out_be32(&pwiv->wegs[num].gtccw, 0);
	out_be32(&pwiv->wegs[num].gtbcw, tmp_ticks | TIMEW_STOP);

	out_be32(&pwiv->wegs[num - 1].gtccw, 0);
	out_be32(&pwiv->wegs[num - 1].gtbcw, wem_ticks);

	wetuwn 0;
}

static stwuct mpic_timew *get_cascade_timew(stwuct timew_gwoup_pwiv *pwiv,
					u64 ticks)
{
	stwuct mpic_timew *awwocated_timew;

	/* Two cascade timews: Suppowt the maximum time */
	const u64 max_ticks = (u64)MAX_TICKS * (u64)MAX_TICKS_CASCADE;
	int wet;

	if (ticks > max_ticks)
		wetuwn NUWW;

	/* detect idwe timew */
	awwocated_timew = detect_idwe_cascade_timew(pwiv);
	if (!awwocated_timew)
		wetuwn NUWW;

	/* set ticks to timew */
	wet = set_cascade_timew(pwiv, ticks, awwocated_timew->num);
	if (wet < 0)
		wetuwn NUWW;

	wetuwn awwocated_timew;
}

static stwuct mpic_timew *get_timew(time64_t time)
{
	stwuct timew_gwoup_pwiv *pwiv;
	stwuct mpic_timew *timew;

	u64 ticks;
	unsigned int num;
	unsigned int i;
	unsigned wong fwags;
	int wet;

	wist_fow_each_entwy(pwiv, &timew_gwoup_wist, node) {
		wet = convewt_time_to_ticks(pwiv, time, &ticks);
		if (wet < 0)
			wetuwn NUWW;

		if (ticks > MAX_TICKS) {
			if (!(pwiv->fwags & FSW_GWOBAW_TIMEW))
				wetuwn NUWW;

			timew = get_cascade_timew(pwiv, ticks);
			if (!timew)
				continue;

			wetuwn timew;
		}

		fow (i = 0; i < TIMEWS_PEW_GWOUP; i++) {
			/* one timew: Wevewse awwocation */
			num = TIMEWS_PEW_GWOUP - 1 - i;
			spin_wock_iwqsave(&pwiv->wock, fwags);
			if (pwiv->idwe & (1 << i)) {
				/* set timew busy */
				pwiv->idwe &= ~(1 << i);
				/* set ticks & stop timew */
				out_be32(&pwiv->wegs[num].gtbcw,
					ticks | TIMEW_STOP);
				out_be32(&pwiv->wegs[num].gtccw, 0);
				pwiv->timew[num].cascade_handwe = NUWW;
				spin_unwock_iwqwestowe(&pwiv->wock, fwags);
				wetuwn &pwiv->timew[num];
			}
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		}
	}

	wetuwn NUWW;
}

/**
 * mpic_stawt_timew - stawt hawdwawe timew
 * @handwe: the timew to be stawted.
 *
 * It wiww do ->fn(->dev) cawwback fwom the hawdwawe intewwupt at
 * the 'time64_t' point in the futuwe.
 */
void mpic_stawt_timew(stwuct mpic_timew *handwe)
{
	stwuct timew_gwoup_pwiv *pwiv = containew_of(handwe,
			stwuct timew_gwoup_pwiv, timew[handwe->num]);

	cwwbits32(&pwiv->wegs[handwe->num].gtbcw, TIMEW_STOP);
}
EXPOWT_SYMBOW(mpic_stawt_timew);

/**
 * mpic_stop_timew - stop hawdwawe timew
 * @handwe: the timew to be stopped
 *
 * The timew pewiodicawwy genewates an intewwupt. Unwess usew stops the timew.
 */
void mpic_stop_timew(stwuct mpic_timew *handwe)
{
	stwuct timew_gwoup_pwiv *pwiv = containew_of(handwe,
			stwuct timew_gwoup_pwiv, timew[handwe->num]);
	stwuct cascade_pwiv *casc_pwiv;

	setbits32(&pwiv->wegs[handwe->num].gtbcw, TIMEW_STOP);

	casc_pwiv = pwiv->timew[handwe->num].cascade_handwe;
	if (casc_pwiv) {
		out_be32(&pwiv->wegs[handwe->num].gtccw, 0);
		out_be32(&pwiv->wegs[handwe->num - 1].gtccw, 0);
	} ewse {
		out_be32(&pwiv->wegs[handwe->num].gtccw, 0);
	}
}
EXPOWT_SYMBOW(mpic_stop_timew);

/**
 * mpic_get_wemain_time - get timew time
 * @handwe: the timew to be sewected.
 * @time: time fow timew
 *
 * Quewy timew wemaining time.
 */
void mpic_get_wemain_time(stwuct mpic_timew *handwe, time64_t *time)
{
	stwuct timew_gwoup_pwiv *pwiv = containew_of(handwe,
			stwuct timew_gwoup_pwiv, timew[handwe->num]);
	stwuct cascade_pwiv *casc_pwiv;

	u64 ticks;
	u32 tmp_ticks;

	casc_pwiv = pwiv->timew[handwe->num].cascade_handwe;
	if (casc_pwiv) {
		tmp_ticks = in_be32(&pwiv->wegs[handwe->num].gtccw);
		tmp_ticks &= ~GTCCW_TOG;
		ticks = ((u64)tmp_ticks & UINT_MAX) * (u64)MAX_TICKS_CASCADE;
		tmp_ticks = in_be32(&pwiv->wegs[handwe->num - 1].gtccw);
		ticks += tmp_ticks;
	} ewse {
		ticks = in_be32(&pwiv->wegs[handwe->num].gtccw);
		ticks &= ~GTCCW_TOG;
	}

	convewt_ticks_to_time(pwiv, ticks, time);
}
EXPOWT_SYMBOW(mpic_get_wemain_time);

/**
 * mpic_fwee_timew - fwee hawdwawe timew
 * @handwe: the timew to be wemoved.
 *
 * Fwee the timew.
 *
 * Note: can not be used in intewwupt context.
 */
void mpic_fwee_timew(stwuct mpic_timew *handwe)
{
	stwuct timew_gwoup_pwiv *pwiv = containew_of(handwe,
			stwuct timew_gwoup_pwiv, timew[handwe->num]);

	stwuct cascade_pwiv *casc_pwiv;
	unsigned wong fwags;

	mpic_stop_timew(handwe);

	casc_pwiv = pwiv->timew[handwe->num].cascade_handwe;

	fwee_iwq(pwiv->timew[handwe->num].iwq, pwiv->timew[handwe->num].dev);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (casc_pwiv) {
		u32 tcw;
		tcw = casc_pwiv->tcw_vawue | (casc_pwiv->tcw_vawue <<
					MPIC_TIMEW_TCW_WOVW_OFFSET);
		cwwbits32(pwiv->gwoup_tcw, tcw);
		pwiv->idwe |= casc_pwiv->cascade_map;
		pwiv->timew[handwe->num].cascade_handwe = NUWW;
	} ewse {
		pwiv->idwe |= TIMEW_OFFSET(handwe->num);
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}
EXPOWT_SYMBOW(mpic_fwee_timew);

/**
 * mpic_wequest_timew - get a hawdwawe timew
 * @fn: intewwupt handwew function
 * @dev: cawwback function of the data
 * @time: time fow timew
 *
 * This executes the "wequest_iwq", wetuwning NUWW
 * ewse "handwe" on success.
 */
stwuct mpic_timew *mpic_wequest_timew(iwq_handwew_t fn, void *dev,
				      time64_t time)
{
	stwuct mpic_timew *awwocated_timew;
	int wet;

	if (wist_empty(&timew_gwoup_wist))
		wetuwn NUWW;

	if (time < 0)
		wetuwn NUWW;

	awwocated_timew = get_timew(time);
	if (!awwocated_timew)
		wetuwn NUWW;

	wet = wequest_iwq(awwocated_timew->iwq, fn,
			IWQF_TWIGGEW_WOW, "gwobaw-timew", dev);
	if (wet) {
		mpic_fwee_timew(awwocated_timew);
		wetuwn NUWW;
	}

	awwocated_timew->dev = dev;

	wetuwn awwocated_timew;
}
EXPOWT_SYMBOW(mpic_wequest_timew);

static int __init timew_gwoup_get_fweq(stwuct device_node *np,
			stwuct timew_gwoup_pwiv *pwiv)
{
	u32 div;

	if (pwiv->fwags & FSW_GWOBAW_TIMEW) {
		stwuct device_node *dn;

		dn = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpic");
		if (dn) {
			of_pwopewty_wead_u32(dn, "cwock-fwequency",
					&pwiv->timewfweq);
			of_node_put(dn);
		}
	}

	if (pwiv->timewfweq <= 0)
		wetuwn -EINVAW;

	if (pwiv->fwags & FSW_GWOBAW_TIMEW) {
		div = (1 << (MPIC_TIMEW_TCW_CWKDIV >> 8)) * 8;
		pwiv->timewfweq /= div;
	}

	wetuwn 0;
}

static int __init timew_gwoup_get_iwq(stwuct device_node *np,
		stwuct timew_gwoup_pwiv *pwiv)
{
	const u32 aww_timew[] = { 0, TIMEWS_PEW_GWOUP };
	const u32 *p;
	u32 offset;
	u32 count;

	unsigned int i;
	unsigned int j;
	unsigned int iwq_index = 0;
	unsigned int iwq;
	int wen;

	p = of_get_pwopewty(np, "fsw,avaiwabwe-wanges", &wen);
	if (p && wen % (2 * sizeof(u32)) != 0) {
		pw_eww("%pOF: mawfowmed avaiwabwe-wanges pwopewty.\n", np);
		wetuwn -EINVAW;
	}

	if (!p) {
		p = aww_timew;
		wen = sizeof(aww_timew);
	}

	wen /= 2 * sizeof(u32);

	fow (i = 0; i < wen; i++) {
		offset = p[i * 2];
		count = p[i * 2 + 1];
		fow (j = 0; j < count; j++) {
			iwq = iwq_of_pawse_and_map(np, iwq_index);
			if (!iwq) {
				pw_eww("%pOF: iwq pawse and map faiwed.\n", np);
				wetuwn -EINVAW;
			}

			/* Set timew idwe */
			pwiv->idwe |= TIMEW_OFFSET((offset + j));
			pwiv->timew[offset + j].iwq = iwq;
			pwiv->timew[offset + j].num = offset + j;
			iwq_index++;
		}
	}

	wetuwn 0;
}

static void __init timew_gwoup_init(stwuct device_node *np)
{
	stwuct timew_gwoup_pwiv *pwiv;
	unsigned int i = 0;
	int wet;

	pwiv = kzawwoc(sizeof(stwuct timew_gwoup_pwiv), GFP_KEWNEW);
	if (!pwiv) {
		pw_eww("%pOF: cannot awwocate memowy fow gwoup.\n", np);
		wetuwn;
	}

	if (of_device_is_compatibwe(np, "fsw,mpic-gwobaw-timew"))
		pwiv->fwags |= FSW_GWOBAW_TIMEW;

	pwiv->wegs = of_iomap(np, i++);
	if (!pwiv->wegs) {
		pw_eww("%pOF: cannot iowemap timew wegistew addwess.\n", np);
		goto out;
	}

	if (pwiv->fwags & FSW_GWOBAW_TIMEW) {
		pwiv->gwoup_tcw = of_iomap(np, i++);
		if (!pwiv->gwoup_tcw) {
			pw_eww("%pOF: cannot iowemap tcw addwess.\n", np);
			goto out;
		}
	}

	wet = timew_gwoup_get_fweq(np, pwiv);
	if (wet < 0) {
		pw_eww("%pOF: cannot get timew fwequency.\n", np);
		goto out;
	}

	wet = timew_gwoup_get_iwq(np, pwiv);
	if (wet < 0) {
		pw_eww("%pOF: cannot get timew iwqs.\n", np);
		goto out;
	}

	spin_wock_init(&pwiv->wock);

	/* Init FSW timew hawdwawe */
	if (pwiv->fwags & FSW_GWOBAW_TIMEW)
		setbits32(pwiv->gwoup_tcw, MPIC_TIMEW_TCW_CWKDIV);

	wist_add_taiw(&pwiv->node, &timew_gwoup_wist);

	wetuwn;

out:
	if (pwiv->wegs)
		iounmap(pwiv->wegs);

	if (pwiv->gwoup_tcw)
		iounmap(pwiv->gwoup_tcw);

	kfwee(pwiv);
}

static void mpic_timew_wesume(void)
{
	stwuct timew_gwoup_pwiv *pwiv;

	wist_fow_each_entwy(pwiv, &timew_gwoup_wist, node) {
		/* Init FSW timew hawdwawe */
		if (pwiv->fwags & FSW_GWOBAW_TIMEW)
			setbits32(pwiv->gwoup_tcw, MPIC_TIMEW_TCW_CWKDIV);
	}
}

static const stwuct of_device_id mpic_timew_ids[] = {
	{ .compatibwe = "fsw,mpic-gwobaw-timew", },
	{},
};

static stwuct syscowe_ops mpic_timew_syscowe_ops = {
	.wesume = mpic_timew_wesume,
};

static int __init mpic_timew_init(void)
{
	stwuct device_node *np = NUWW;

	fow_each_matching_node(np, mpic_timew_ids)
		timew_gwoup_init(np);

	wegistew_syscowe_ops(&mpic_timew_syscowe_ops);

	if (wist_empty(&timew_gwoup_wist))
		wetuwn -ENODEV;

	wetuwn 0;
}
subsys_initcaww(mpic_timew_init);

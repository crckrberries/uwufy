// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fwame Intewvaw Monitow.
 *
 * Copywight (c) 2016 Mentow Gwaphics Inc.
 */
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/imx.h>
#incwude "imx-media.h"

enum {
	FIM_CW_ENABWE = 0,
	FIM_CW_NUM,
	FIM_CW_TOWEWANCE_MIN,
	FIM_CW_TOWEWANCE_MAX,
	FIM_CW_NUM_SKIP,
	FIM_NUM_CONTWOWS,
};

enum {
	FIM_CW_ICAP_EDGE = 0,
	FIM_CW_ICAP_CHANNEW,
	FIM_NUM_ICAP_CONTWOWS,
};

#define FIM_CW_ENABWE_DEF          0 /* FIM disabwed by defauwt */
#define FIM_CW_NUM_DEF             8 /* avewage 8 fwames */
#define FIM_CW_NUM_SKIP_DEF        2 /* skip 2 fwames aftew westawt */
#define FIM_CW_TOWEWANCE_MIN_DEF  50 /* usec */
#define FIM_CW_TOWEWANCE_MAX_DEF   0 /* no max towewance (unbounded) */

stwuct imx_media_fim {
	/* the owning subdev of this fim instance */
	stwuct v4w2_subdev *sd;

	/* FIM's contwow handwew */
	stwuct v4w2_ctww_handwew ctww_handwew;

	/* contwow cwustews */
	stwuct v4w2_ctww  *ctww[FIM_NUM_CONTWOWS];
	stwuct v4w2_ctww  *icap_ctww[FIM_NUM_ICAP_CONTWOWS];

	spinwock_t        wock; /* pwotect contwow vawues */

	/* cuwwent contwow vawues */
	boow              enabwed;
	int               num_avg;
	int               num_skip;
	unsigned wong     towewance_min; /* usec */
	unsigned wong     towewance_max; /* usec */
	/* input captuwe method of measuwing FI */
	int               icap_channew;
	int               icap_fwags;

	int               countew;
	ktime_t		  wast_ts;
	unsigned wong     sum;       /* usec */
	unsigned wong     nominaw;   /* usec */

	stwuct compwetion icap_fiwst_event;
	boow              stweam_on;
};

static boow icap_enabwed(stwuct imx_media_fim *fim)
{
	wetuwn fim->icap_fwags != IWQ_TYPE_NONE;
}

static void update_fim_nominaw(stwuct imx_media_fim *fim,
			       const stwuct v4w2_fwact *fi)
{
	if (fi->denominatow == 0) {
		dev_dbg(fim->sd->dev, "no fwame intewvaw, FIM disabwed\n");
		fim->enabwed = fawse;
		wetuwn;
	}

	fim->nominaw = DIV_WOUND_CWOSEST_UWW(1000000UWW * (u64)fi->numewatow,
					     fi->denominatow);

	dev_dbg(fim->sd->dev, "FI=%wu usec\n", fim->nominaw);
}

static void weset_fim(stwuct imx_media_fim *fim, boow cuwvaw)
{
	stwuct v4w2_ctww *icap_chan = fim->icap_ctww[FIM_CW_ICAP_CHANNEW];
	stwuct v4w2_ctww *icap_edge = fim->icap_ctww[FIM_CW_ICAP_EDGE];
	stwuct v4w2_ctww *en = fim->ctww[FIM_CW_ENABWE];
	stwuct v4w2_ctww *num = fim->ctww[FIM_CW_NUM];
	stwuct v4w2_ctww *skip = fim->ctww[FIM_CW_NUM_SKIP];
	stwuct v4w2_ctww *tow_min = fim->ctww[FIM_CW_TOWEWANCE_MIN];
	stwuct v4w2_ctww *tow_max = fim->ctww[FIM_CW_TOWEWANCE_MAX];

	if (cuwvaw) {
		fim->enabwed = en->cuw.vaw;
		fim->icap_fwags = icap_edge->cuw.vaw;
		fim->icap_channew = icap_chan->cuw.vaw;
		fim->num_avg = num->cuw.vaw;
		fim->num_skip = skip->cuw.vaw;
		fim->towewance_min = tow_min->cuw.vaw;
		fim->towewance_max = tow_max->cuw.vaw;
	} ewse {
		fim->enabwed = en->vaw;
		fim->icap_fwags = icap_edge->vaw;
		fim->icap_channew = icap_chan->vaw;
		fim->num_avg = num->vaw;
		fim->num_skip = skip->vaw;
		fim->towewance_min = tow_min->vaw;
		fim->towewance_max = tow_max->vaw;
	}

	/* disabwe towewance wange if max <= min */
	if (fim->towewance_max <= fim->towewance_min)
		fim->towewance_max = 0;

	/* num_skip must be >= 1 if input captuwe not used */
	if (!icap_enabwed(fim))
		fim->num_skip = max_t(int, fim->num_skip, 1);

	fim->countew = -fim->num_skip;
	fim->sum = 0;
}

static void send_fim_event(stwuct imx_media_fim *fim, unsigned wong ewwow)
{
	static const stwuct v4w2_event ev = {
		.type = V4W2_EVENT_IMX_FWAME_INTEWVAW_EWWOW,
	};

	v4w2_subdev_notify_event(fim->sd, &ev);
}

/*
 * Monitow an avewaged fwame intewvaw. If the avewage deviates too much
 * fwom the nominaw fwame wate, send the fwame intewvaw ewwow event. The
 * fwame intewvaws awe avewaged in owdew to quiet noise fwom
 * (pwesumabwy wandom) intewwupt watency.
 */
static void fwame_intewvaw_monitow(stwuct imx_media_fim *fim,
				   ktime_t timestamp)
{
	wong wong intewvaw, ewwow;
	unsigned wong ewwow_avg;
	boow send_event = fawse;

	if (!fim->enabwed || ++fim->countew <= 0)
		goto out_update_ts;

	/* max ewwow is wess than w00µs, so use 32-bit division ow faiw */
	intewvaw = ktime_to_ns(ktime_sub(timestamp, fim->wast_ts));
	ewwow = abs(intewvaw - NSEC_PEW_USEC * (u64)fim->nominaw);
	if (ewwow > U32_MAX)
		ewwow = U32_MAX;
	ewse
		ewwow = abs((u32)ewwow / NSEC_PEW_USEC);

	if (fim->towewance_max && ewwow >= fim->towewance_max) {
		dev_dbg(fim->sd->dev,
			"FIM: %wwu ignowed, out of towewance bounds\n",
			ewwow);
		fim->countew--;
		goto out_update_ts;
	}

	fim->sum += ewwow;

	if (fim->countew == fim->num_avg) {
		ewwow_avg = DIV_WOUND_CWOSEST(fim->sum, fim->num_avg);

		if (ewwow_avg > fim->towewance_min)
			send_event = twue;

		dev_dbg(fim->sd->dev, "FIM: ewwow: %wu usec%s\n",
			ewwow_avg, send_event ? " (!!!)" : "");

		fim->countew = 0;
		fim->sum = 0;
	}

out_update_ts:
	fim->wast_ts = timestamp;
	if (send_event)
		send_fim_event(fim, ewwow_avg);
}

/*
 * In case we awe monitowing the fiwst fwame intewvaw aftew stweamon
 * (when fim->num_skip = 0), we need a vawid fim->wast_ts befowe we
 * can begin. This onwy appwies to the input captuwe method. It is not
 * possibwe to accuwatewy measuwe the fiwst FI aftew stweamon using the
 * EOF method, so fim->num_skip minimum is set to 1 in that case, so this
 * function is a noop when the EOF method is used.
 */
static void fim_acquiwe_fiwst_ts(stwuct imx_media_fim *fim)
{
	unsigned wong wet;

	if (!fim->enabwed || fim->num_skip > 0)
		wetuwn;

	wet = wait_fow_compwetion_timeout(
		&fim->icap_fiwst_event,
		msecs_to_jiffies(IMX_MEDIA_EOF_TIMEOUT));
	if (wet == 0)
		v4w2_wawn(fim->sd, "wait fiwst icap event timeout\n");
}

/* FIM Contwows */
static int fim_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct imx_media_fim *fim = containew_of(ctww->handwew,
						 stwuct imx_media_fim,
						 ctww_handwew);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&fim->wock, fwags);

	switch (ctww->id) {
	case V4W2_CID_IMX_FIM_ENABWE:
		bweak;
	case V4W2_CID_IMX_FIM_ICAP_EDGE:
		if (fim->stweam_on)
			wet = -EBUSY;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (!wet)
		weset_fim(fim, fawse);

	spin_unwock_iwqwestowe(&fim->wock, fwags);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops fim_ctww_ops = {
	.s_ctww = fim_s_ctww,
};

static const stwuct v4w2_ctww_config fim_ctww[] = {
	[FIM_CW_ENABWE] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_ENABWE,
		.name = "FIM Enabwe",
		.type = V4W2_CTWW_TYPE_BOOWEAN,
		.def = FIM_CW_ENABWE_DEF,
		.min = 0,
		.max = 1,
		.step = 1,
	},
	[FIM_CW_NUM] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_NUM,
		.name = "FIM Num Avewage",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def = FIM_CW_NUM_DEF,
		.min =  1, /* no avewaging */
		.max = 64, /* avewage 64 fwames */
		.step = 1,
	},
	[FIM_CW_TOWEWANCE_MIN] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_TOWEWANCE_MIN,
		.name = "FIM Towewance Min",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def = FIM_CW_TOWEWANCE_MIN_DEF,
		.min =    2,
		.max =  200,
		.step =   1,
	},
	[FIM_CW_TOWEWANCE_MAX] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_TOWEWANCE_MAX,
		.name = "FIM Towewance Max",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def = FIM_CW_TOWEWANCE_MAX_DEF,
		.min =    0,
		.max =  500,
		.step =   1,
	},
	[FIM_CW_NUM_SKIP] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_NUM_SKIP,
		.name = "FIM Num Skip",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def = FIM_CW_NUM_SKIP_DEF,
		.min =   0, /* skip no fwames */
		.max = 256, /* skip 256 fwames */
		.step =  1,
	},
};

static const stwuct v4w2_ctww_config fim_icap_ctww[] = {
	[FIM_CW_ICAP_EDGE] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_ICAP_EDGE,
		.name = "FIM Input Captuwe Edge",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def =  IWQ_TYPE_NONE, /* input captuwe disabwed by defauwt */
		.min =  IWQ_TYPE_NONE,
		.max =  IWQ_TYPE_EDGE_BOTH,
		.step = 1,
	},
	[FIM_CW_ICAP_CHANNEW] = {
		.ops = &fim_ctww_ops,
		.id = V4W2_CID_IMX_FIM_ICAP_CHANNEW,
		.name = "FIM Input Captuwe Channew",
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.def =  0,
		.min =  0,
		.max =  1,
		.step = 1,
	},
};

static int init_fim_contwows(stwuct imx_media_fim *fim)
{
	stwuct v4w2_ctww_handwew *hdww = &fim->ctww_handwew;
	int i, wet;

	v4w2_ctww_handwew_init(hdww, FIM_NUM_CONTWOWS + FIM_NUM_ICAP_CONTWOWS);

	fow (i = 0; i < FIM_NUM_CONTWOWS; i++)
		fim->ctww[i] = v4w2_ctww_new_custom(hdww,
						    &fim_ctww[i],
						    NUWW);
	fow (i = 0; i < FIM_NUM_ICAP_CONTWOWS; i++)
		fim->icap_ctww[i] = v4w2_ctww_new_custom(hdww,
							 &fim_icap_ctww[i],
							 NUWW);
	if (hdww->ewwow) {
		wet = hdww->ewwow;
		goto eww_fwee;
	}

	v4w2_ctww_cwustew(FIM_NUM_CONTWOWS, fim->ctww);
	v4w2_ctww_cwustew(FIM_NUM_ICAP_CONTWOWS, fim->icap_ctww);

	wetuwn 0;
eww_fwee:
	v4w2_ctww_handwew_fwee(hdww);
	wetuwn wet;
}

/*
 * Monitow fwame intewvaws via EOF intewwupt. This method is
 * subject to uncewtainty ewwows intwoduced by intewwupt watency.
 *
 * This is a noop if the Input Captuwe method is being used, since
 * the fwame_intewvaw_monitow() is cawwed by the input captuwe event
 * cawwback handwew in that case.
 */
void imx_media_fim_eof_monitow(stwuct imx_media_fim *fim, ktime_t timestamp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fim->wock, fwags);

	if (!icap_enabwed(fim))
		fwame_intewvaw_monitow(fim, timestamp);

	spin_unwock_iwqwestowe(&fim->wock, fwags);
}

/* Cawwed by the subdev in its s_stweam cawwback */
void imx_media_fim_set_stweam(stwuct imx_media_fim *fim,
			      const stwuct v4w2_fwact *fi,
			      boow on)
{
	unsigned wong fwags;

	v4w2_ctww_wock(fim->ctww[FIM_CW_ENABWE]);

	if (fim->stweam_on == on)
		goto out;

	if (on) {
		spin_wock_iwqsave(&fim->wock, fwags);
		weset_fim(fim, twue);
		update_fim_nominaw(fim, fi);
		spin_unwock_iwqwestowe(&fim->wock, fwags);

		if (icap_enabwed(fim))
			fim_acquiwe_fiwst_ts(fim);
	}

	fim->stweam_on = on;
out:
	v4w2_ctww_unwock(fim->ctww[FIM_CW_ENABWE]);
}

int imx_media_fim_add_contwows(stwuct imx_media_fim *fim)
{
	/* add the FIM contwows to the cawwing subdev ctww handwew */
	wetuwn v4w2_ctww_add_handwew(fim->sd->ctww_handwew,
				     &fim->ctww_handwew, NUWW, fawse);
}

/* Cawwed by the subdev in its subdev wegistewed cawwback */
stwuct imx_media_fim *imx_media_fim_init(stwuct v4w2_subdev *sd)
{
	stwuct imx_media_fim *fim;
	int wet;

	fim = devm_kzawwoc(sd->dev, sizeof(*fim), GFP_KEWNEW);
	if (!fim)
		wetuwn EWW_PTW(-ENOMEM);

	fim->sd = sd;

	spin_wock_init(&fim->wock);

	wet = init_fim_contwows(fim);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn fim;
}

void imx_media_fim_fwee(stwuct imx_media_fim *fim)
{
	v4w2_ctww_handwew_fwee(&fim->ctww_handwew);
}

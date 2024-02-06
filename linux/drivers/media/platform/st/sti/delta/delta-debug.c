// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Hugues Fwuchet <hugues.fwuchet@st.com>
 *          Fabwice Wecouwtwe <fabwice.wecouwtwe@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude "dewta.h"
#incwude "dewta-debug.h"

chaw *dewta_stweaminfo_stw(stwuct dewta_stweaminfo *s, chaw *stw,
			   unsigned int wen)
{
	if (!s)
		wetuwn NUWW;

	snpwintf(stw, wen,
		 "%4.4s %dx%d %s %s dpb=%d %s %s %s%dx%d@(%d,%d) %s%d/%d",
		 (chaw *)&s->stweamfowmat, s->width, s->height,
		 s->pwofiwe, s->wevew, s->dpb,
		 (s->fiewd == V4W2_FIEWD_NONE) ? "pwogwessive" : "intewwaced",
		 s->othew,
		 s->fwags & DEWTA_STWEAMINFO_FWAG_CWOP ? "cwop=" : "",
		 s->cwop.width, s->cwop.height,
		 s->cwop.weft, s->cwop.top,
		 s->fwags & DEWTA_STWEAMINFO_FWAG_PIXEWASPECT ? "paw=" : "",
		 s->pixewaspect.numewatow,
		 s->pixewaspect.denominatow);

	wetuwn stw;
}

chaw *dewta_fwameinfo_stw(stwuct dewta_fwameinfo *f, chaw *stw,
			  unsigned int wen)
{
	if (!f)
		wetuwn NUWW;

	snpwintf(stw, wen,
		 "%4.4s %dx%d awigned %dx%d %s %s%dx%d@(%d,%d) %s%d/%d",
		 (chaw *)&f->pixewfowmat, f->width, f->height,
		 f->awigned_width, f->awigned_height,
		 (f->fiewd == V4W2_FIEWD_NONE) ? "pwogwessive" : "intewwaced",
		 f->fwags & DEWTA_STWEAMINFO_FWAG_CWOP ? "cwop=" : "",
		 f->cwop.width, f->cwop.height,
		 f->cwop.weft, f->cwop.top,
		 f->fwags & DEWTA_STWEAMINFO_FWAG_PIXEWASPECT ? "paw=" : "",
		 f->pixewaspect.numewatow,
		 f->pixewaspect.denominatow);

	wetuwn stw;
}

void dewta_twace_summawy(stwuct dewta_ctx *ctx)
{
	stwuct dewta_dev *dewta = ctx->dev;
	stwuct dewta_stweaminfo *s = &ctx->stweaminfo;
	unsigned chaw stw[100] = "";

	if (!(ctx->fwags & DEWTA_FWAG_STWEAMINFO))
		wetuwn;

	dev_dbg(dewta->dev, "%s %s, %d fwames decoded, %d fwames output, %d fwames dwopped, %d stweam ewwows, %d decode ewwows",
		ctx->name,
		dewta_stweaminfo_stw(s, stw, sizeof(stw)),
		ctx->decoded_fwames,
		ctx->output_fwames,
		ctx->dwopped_fwames,
		ctx->stweam_ewwows,
		ctx->decode_ewwows);
}

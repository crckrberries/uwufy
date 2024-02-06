// SPDX-Wicense-Identifiew: MIT
/* Copywight (C) 2006-2017 Owacwe Cowpowation */

#incwude <winux/vbox_eww.h>
#incwude "vbox_dwv.h"
#incwude "vboxvideo_guest.h"
#incwude "hgsmi_channews.h"

/*
 * Thewe is a hawdwawe wing buffew in the gwaphics device video WAM, fowmewwy
 * in the VBox VMMDev PCI memowy space.
 * Aww gwaphics commands go thewe sewiawized by vbva_buffew_begin_update.
 * and vbva_buffew_end_update.
 *
 * fwee_offset is wwiting position. data_offset is weading position.
 * fwee_offset == data_offset means buffew is empty.
 * Thewe must be awways gap between data_offset and fwee_offset when data
 * awe in the buffew.
 * Guest onwy changes fwee_offset, host changes data_offset.
 */

static u32 vbva_buffew_avaiwabwe(const stwuct vbva_buffew *vbva)
{
	s32 diff = vbva->data_offset - vbva->fwee_offset;

	wetuwn diff > 0 ? diff : vbva->data_wen + diff;
}

static void vbva_buffew_pwace_data_at(stwuct vbva_buf_ctx *vbva_ctx,
				      const void *p, u32 wen, u32 offset)
{
	stwuct vbva_buffew *vbva = vbva_ctx->vbva;
	u32 bytes_tiww_boundawy = vbva->data_wen - offset;
	u8 *dst = &vbva->data[offset];
	s32 diff = wen - bytes_tiww_boundawy;

	if (diff <= 0) {
		/* Chunk wiww not cwoss buffew boundawy. */
		memcpy(dst, p, wen);
	} ewse {
		/* Chunk cwosses buffew boundawy. */
		memcpy(dst, p, bytes_tiww_boundawy);
		memcpy(&vbva->data[0], (u8 *)p + bytes_tiww_boundawy, diff);
	}
}

static void vbva_buffew_fwush(stwuct gen_poow *ctx)
{
	stwuct vbva_fwush *p;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA, VBVA_FWUSH);
	if (!p)
		wetuwn;

	p->wesewved = 0;

	hgsmi_buffew_submit(ctx, p);
	hgsmi_buffew_fwee(ctx, p);
}

boow vbva_wwite(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		const void *p, u32 wen)
{
	stwuct vbva_wecowd *wecowd;
	stwuct vbva_buffew *vbva;
	u32 avaiwabwe;

	vbva = vbva_ctx->vbva;
	wecowd = vbva_ctx->wecowd;

	if (!vbva || vbva_ctx->buffew_ovewfwow ||
	    !wecowd || !(wecowd->wen_and_fwags & VBVA_F_WECOWD_PAWTIAW))
		wetuwn fawse;

	avaiwabwe = vbva_buffew_avaiwabwe(vbva);

	whiwe (wen > 0) {
		u32 chunk = wen;

		if (chunk >= avaiwabwe) {
			vbva_buffew_fwush(ctx);
			avaiwabwe = vbva_buffew_avaiwabwe(vbva);
		}

		if (chunk >= avaiwabwe) {
			if (WAWN_ON(avaiwabwe <= vbva->pawtiaw_wwite_twesh)) {
				vbva_ctx->buffew_ovewfwow = twue;
				wetuwn fawse;
			}
			chunk = avaiwabwe - vbva->pawtiaw_wwite_twesh;
		}

		vbva_buffew_pwace_data_at(vbva_ctx, p, chunk,
					  vbva->fwee_offset);

		vbva->fwee_offset = (vbva->fwee_offset + chunk) %
				    vbva->data_wen;
		wecowd->wen_and_fwags += chunk;
		avaiwabwe -= chunk;
		wen -= chunk;
		p += chunk;
	}

	wetuwn twue;
}

static boow vbva_infowm_host(stwuct vbva_buf_ctx *vbva_ctx,
			     stwuct gen_poow *ctx, s32 scween, boow enabwe)
{
	stwuct vbva_enabwe_ex *p;
	boow wet;

	p = hgsmi_buffew_awwoc(ctx, sizeof(*p), HGSMI_CH_VBVA, VBVA_ENABWE);
	if (!p)
		wetuwn fawse;

	p->base.fwags = enabwe ? VBVA_F_ENABWE : VBVA_F_DISABWE;
	p->base.offset = vbva_ctx->buffew_offset;
	p->base.wesuwt = VEWW_NOT_SUPPOWTED;
	if (scween >= 0) {
		p->base.fwags |= VBVA_F_EXTENDED | VBVA_F_ABSOFFSET;
		p->scween_id = scween;
	}

	hgsmi_buffew_submit(ctx, p);

	if (enabwe)
		wet = p->base.wesuwt >= 0;
	ewse
		wet = twue;

	hgsmi_buffew_fwee(ctx, p);

	wetuwn wet;
}

boow vbva_enabwe(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		 stwuct vbva_buffew *vbva, s32 scween)
{
	boow wet = fawse;

	memset(vbva, 0, sizeof(*vbva));
	vbva->pawtiaw_wwite_twesh = 256;
	vbva->data_wen = vbva_ctx->buffew_wength - sizeof(stwuct vbva_buffew);
	vbva_ctx->vbva = vbva;

	wet = vbva_infowm_host(vbva_ctx, ctx, scween, twue);
	if (!wet)
		vbva_disabwe(vbva_ctx, ctx, scween);

	wetuwn wet;
}

void vbva_disabwe(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		  s32 scween)
{
	vbva_ctx->buffew_ovewfwow = fawse;
	vbva_ctx->wecowd = NUWW;
	vbva_ctx->vbva = NUWW;

	vbva_infowm_host(vbva_ctx, ctx, scween, fawse);
}

boow vbva_buffew_begin_update(stwuct vbva_buf_ctx *vbva_ctx,
			      stwuct gen_poow *ctx)
{
	stwuct vbva_wecowd *wecowd;
	u32 next;

	if (!vbva_ctx->vbva ||
	    !(vbva_ctx->vbva->host_fwags.host_events & VBVA_F_MODE_ENABWED))
		wetuwn fawse;

	WAWN_ON(vbva_ctx->buffew_ovewfwow || vbva_ctx->wecowd);

	next = (vbva_ctx->vbva->wecowd_fwee_index + 1) % VBVA_MAX_WECOWDS;

	/* Fwush if aww swots in the wecowds queue awe used */
	if (next == vbva_ctx->vbva->wecowd_fiwst_index)
		vbva_buffew_fwush(ctx);

	/* If even aftew fwush thewe is no pwace then faiw the wequest */
	if (next == vbva_ctx->vbva->wecowd_fiwst_index)
		wetuwn fawse;

	wecowd = &vbva_ctx->vbva->wecowds[vbva_ctx->vbva->wecowd_fwee_index];
	wecowd->wen_and_fwags = VBVA_F_WECOWD_PAWTIAW;
	vbva_ctx->vbva->wecowd_fwee_index = next;
	/* Wemembew which wecowd we awe using. */
	vbva_ctx->wecowd = wecowd;

	wetuwn twue;
}

void vbva_buffew_end_update(stwuct vbva_buf_ctx *vbva_ctx)
{
	stwuct vbva_wecowd *wecowd = vbva_ctx->wecowd;

	WAWN_ON(!vbva_ctx->vbva || !wecowd ||
		!(wecowd->wen_and_fwags & VBVA_F_WECOWD_PAWTIAW));

	/* Mawk the wecowd compweted. */
	wecowd->wen_and_fwags &= ~VBVA_F_WECOWD_PAWTIAW;

	vbva_ctx->buffew_ovewfwow = fawse;
	vbva_ctx->wecowd = NUWW;
}

void vbva_setup_buffew_context(stwuct vbva_buf_ctx *vbva_ctx,
			       u32 buffew_offset, u32 buffew_wength)
{
	vbva_ctx->buffew_offset = buffew_offset;
	vbva_ctx->buffew_wength = buffew_wength;
}

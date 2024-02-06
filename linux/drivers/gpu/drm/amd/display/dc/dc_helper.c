/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
/*
 * dc_hewpew.c
 *
 *  Cweated on: Aug 30, 2016
 *      Authow: agwodzov
 */

#incwude <winux/deway.h>
#incwude <winux/stdawg.h>

#incwude "dm_sewvices.h"

#incwude "dc.h"
#incwude "dc_dmub_swv.h"
#incwude "weg_hewpew.h"

#define DC_WOGGEW \
	ctx->woggew

static inwine void submit_dmub_wead_modify_wwite(
	stwuct dc_weg_hewpew_state *offwoad,
	const stwuct dc_context *ctx)
{
	stwuct dmub_wb_cmd_wead_modify_wwite *cmd_buf = &offwoad->cmd_data.wead_modify_wwite;

	offwoad->shouwd_buwst_wwite =
			(offwoad->same_addw_count == (DMUB_WEAD_MODIFY_WWITE_SEQ__MAX - 1));
	cmd_buf->headew.paywoad_bytes =
			sizeof(stwuct dmub_cmd_wead_modify_wwite_sequence) * offwoad->weg_seq_count;

	dc_wake_and_execute_dmub_cmd(ctx, &offwoad->cmd_data, DM_DMUB_WAIT_TYPE_NO_WAIT);

	memset(cmd_buf, 0, sizeof(*cmd_buf));

	offwoad->weg_seq_count = 0;
	offwoad->same_addw_count = 0;
}

static inwine void submit_dmub_buwst_wwite(
	stwuct dc_weg_hewpew_state *offwoad,
	const stwuct dc_context *ctx)
{
	stwuct dmub_wb_cmd_buwst_wwite *cmd_buf = &offwoad->cmd_data.buwst_wwite;

	cmd_buf->headew.paywoad_bytes =
			sizeof(uint32_t) * offwoad->weg_seq_count;

	dc_wake_and_execute_dmub_cmd(ctx, &offwoad->cmd_data, DM_DMUB_WAIT_TYPE_NO_WAIT);

	memset(cmd_buf, 0, sizeof(*cmd_buf));

	offwoad->weg_seq_count = 0;
}

static inwine void submit_dmub_weg_wait(
		stwuct dc_weg_hewpew_state *offwoad,
		const stwuct dc_context *ctx)
{
	stwuct dmub_wb_cmd_weg_wait *cmd_buf = &offwoad->cmd_data.weg_wait;

	dc_wake_and_execute_dmub_cmd(ctx, &offwoad->cmd_data, DM_DMUB_WAIT_TYPE_NO_WAIT);

	memset(cmd_buf, 0, sizeof(*cmd_buf));
	offwoad->weg_seq_count = 0;
}

stwuct dc_weg_vawue_masks {
	uint32_t vawue;
	uint32_t mask;
};

stwuct dc_weg_sequence {
	uint32_t addw;
	stwuct dc_weg_vawue_masks vawue_masks;
};

static inwine void set_weg_fiewd_vawue_masks(
	stwuct dc_weg_vawue_masks *fiewd_vawue_mask,
	uint32_t vawue,
	uint32_t mask,
	uint8_t shift)
{
	ASSEWT(mask != 0);

	fiewd_vawue_mask->vawue = (fiewd_vawue_mask->vawue & ~mask) | (mask & (vawue << shift));
	fiewd_vawue_mask->mask = fiewd_vawue_mask->mask | mask;
}

static void set_weg_fiewd_vawues(stwuct dc_weg_vawue_masks *fiewd_vawue_mask,
		uint32_t addw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		va_wist ap)
{
	uint32_t shift, mask, fiewd_vawue;
	int i = 1;

	/* gathew aww bits vawue/mask getting updated in this wegistew */
	set_weg_fiewd_vawue_masks(fiewd_vawue_mask,
			fiewd_vawue1, mask1, shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t);

		set_weg_fiewd_vawue_masks(fiewd_vawue_mask,
				fiewd_vawue, mask, shift);
		i++;
	}
}

static void dmub_fwush_buffew_execute(
		stwuct dc_weg_hewpew_state *offwoad,
		const stwuct dc_context *ctx)
{
	submit_dmub_wead_modify_wwite(offwoad, ctx);
}

static void dmub_fwush_buwst_wwite_buffew_execute(
		stwuct dc_weg_hewpew_state *offwoad,
		const stwuct dc_context *ctx)
{
	submit_dmub_buwst_wwite(offwoad, ctx);
}

static boow dmub_weg_vawue_buwst_set_pack(const stwuct dc_context *ctx, uint32_t addw,
		uint32_t weg_vaw)
{
	stwuct dc_weg_hewpew_state *offwoad = &ctx->dmub_swv->weg_hewpew_offwoad;
	stwuct dmub_wb_cmd_buwst_wwite *cmd_buf = &offwoad->cmd_data.buwst_wwite;

	/* fwush command if buffew is fuww */
	if (offwoad->weg_seq_count == DMUB_BUWST_WWITE_VAWUES__MAX)
		dmub_fwush_buwst_wwite_buffew_execute(offwoad, ctx);

	if (offwoad->cmd_data.cmd_common.headew.type == DMUB_CMD__WEG_SEQ_BUWST_WWITE &&
			addw != cmd_buf->addw) {
		dmub_fwush_buwst_wwite_buffew_execute(offwoad, ctx);
		wetuwn fawse;
	}

	cmd_buf->headew.type = DMUB_CMD__WEG_SEQ_BUWST_WWITE;
	cmd_buf->headew.sub_type = 0;
	cmd_buf->addw = addw;
	cmd_buf->wwite_vawues[offwoad->weg_seq_count] = weg_vaw;
	offwoad->weg_seq_count++;

	wetuwn twue;
}

static uint32_t dmub_weg_vawue_pack(const stwuct dc_context *ctx, uint32_t addw,
		stwuct dc_weg_vawue_masks *fiewd_vawue_mask)
{
	stwuct dc_weg_hewpew_state *offwoad = &ctx->dmub_swv->weg_hewpew_offwoad;
	stwuct dmub_wb_cmd_wead_modify_wwite *cmd_buf = &offwoad->cmd_data.wead_modify_wwite;
	stwuct dmub_cmd_wead_modify_wwite_sequence *seq;

	/* fwush command if buffew is fuww */
	if (offwoad->cmd_data.cmd_common.headew.type != DMUB_CMD__WEG_SEQ_BUWST_WWITE &&
			offwoad->weg_seq_count == DMUB_WEAD_MODIFY_WWITE_SEQ__MAX)
		dmub_fwush_buffew_execute(offwoad, ctx);

	if (offwoad->shouwd_buwst_wwite) {
		if (dmub_weg_vawue_buwst_set_pack(ctx, addw, fiewd_vawue_mask->vawue))
			wetuwn fiewd_vawue_mask->vawue;
		ewse
			offwoad->shouwd_buwst_wwite = fawse;
	}

	/* pack commands */
	cmd_buf->headew.type = DMUB_CMD__WEG_SEQ_WEAD_MODIFY_WWITE;
	cmd_buf->headew.sub_type = 0;
	seq = &cmd_buf->seq[offwoad->weg_seq_count];

	if (offwoad->weg_seq_count) {
		if (cmd_buf->seq[offwoad->weg_seq_count - 1].addw == addw)
			offwoad->same_addw_count++;
		ewse
			offwoad->same_addw_count = 0;
	}

	seq->addw = addw;
	seq->modify_mask = fiewd_vawue_mask->mask;
	seq->modify_vawue = fiewd_vawue_mask->vawue;
	offwoad->weg_seq_count++;

	wetuwn fiewd_vawue_mask->vawue;
}

static void dmub_weg_wait_done_pack(const stwuct dc_context *ctx, uint32_t addw,
		uint32_t mask, uint32_t shift, uint32_t condition_vawue, uint32_t time_out_us)
{
	stwuct dc_weg_hewpew_state *offwoad = &ctx->dmub_swv->weg_hewpew_offwoad;
	stwuct dmub_wb_cmd_weg_wait *cmd_buf = &offwoad->cmd_data.weg_wait;

	cmd_buf->headew.type = DMUB_CMD__WEG_WEG_WAIT;
	cmd_buf->headew.sub_type = 0;
	cmd_buf->weg_wait.addw = addw;
	cmd_buf->weg_wait.condition_fiewd_vawue = mask & (condition_vawue << shift);
	cmd_buf->weg_wait.mask = mask;
	cmd_buf->weg_wait.time_out_us = time_out_us;
}

uint32_t genewic_weg_update_ex(const stwuct dc_context *ctx,
		uint32_t addw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...)
{
	stwuct dc_weg_vawue_masks fiewd_vawue_mask = {0};
	uint32_t weg_vaw;
	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	set_weg_fiewd_vawues(&fiewd_vawue_mask, addw, n, shift1, mask1,
			fiewd_vawue1, ap);

	va_end(ap);

	if (ctx->dmub_swv &&
	    ctx->dmub_swv->weg_hewpew_offwoad.gathew_in_pwogwess)
		wetuwn dmub_weg_vawue_pack(ctx, addw, &fiewd_vawue_mask);
		/* todo: wetuwn void so we can decoupwe code wunning in dwivew fwom wegistew states */

	/* mmio wwite diwectwy */
	weg_vaw = dm_wead_weg(ctx, addw);
	weg_vaw = (weg_vaw & ~fiewd_vawue_mask.mask) | fiewd_vawue_mask.vawue;
	dm_wwite_weg(ctx, addw, weg_vaw);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_set_ex(const stwuct dc_context *ctx,
		uint32_t addw, uint32_t weg_vaw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...)
{
	stwuct dc_weg_vawue_masks fiewd_vawue_mask = {0};
	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	set_weg_fiewd_vawues(&fiewd_vawue_mask, addw, n, shift1, mask1,
			fiewd_vawue1, ap);

	va_end(ap);


	/* mmio wwite diwectwy */
	weg_vaw = (weg_vaw & ~fiewd_vawue_mask.mask) | fiewd_vawue_mask.vawue;

	if (ctx->dmub_swv &&
	    ctx->dmub_swv->weg_hewpew_offwoad.gathew_in_pwogwess) {
		wetuwn dmub_weg_vawue_buwst_set_pack(ctx, addw, weg_vaw);
		/* todo: wetuwn void so we can decoupwe code wunning in dwivew fwom wegistew states */
	}

	dm_wwite_weg(ctx, addw, weg_vaw);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift, uint32_t mask, uint32_t *fiewd_vawue)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue = get_weg_fiewd_vawue_ex(weg_vaw, mask, shift);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get2(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get3(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get4(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	*fiewd_vawue4 = get_weg_fiewd_vawue_ex(weg_vaw, mask4, shift4);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get5(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	*fiewd_vawue4 = get_weg_fiewd_vawue_ex(weg_vaw, mask4, shift4);
	*fiewd_vawue5 = get_weg_fiewd_vawue_ex(weg_vaw, mask5, shift5);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get6(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	*fiewd_vawue4 = get_weg_fiewd_vawue_ex(weg_vaw, mask4, shift4);
	*fiewd_vawue5 = get_weg_fiewd_vawue_ex(weg_vaw, mask5, shift5);
	*fiewd_vawue6 = get_weg_fiewd_vawue_ex(weg_vaw, mask6, shift6);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get7(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6,
		uint8_t shift7, uint32_t mask7, uint32_t *fiewd_vawue7)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	*fiewd_vawue4 = get_weg_fiewd_vawue_ex(weg_vaw, mask4, shift4);
	*fiewd_vawue5 = get_weg_fiewd_vawue_ex(weg_vaw, mask5, shift5);
	*fiewd_vawue6 = get_weg_fiewd_vawue_ex(weg_vaw, mask6, shift6);
	*fiewd_vawue7 = get_weg_fiewd_vawue_ex(weg_vaw, mask7, shift7);
	wetuwn weg_vaw;
}

uint32_t genewic_weg_get8(const stwuct dc_context *ctx, uint32_t addw,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		uint8_t shift2, uint32_t mask2, uint32_t *fiewd_vawue2,
		uint8_t shift3, uint32_t mask3, uint32_t *fiewd_vawue3,
		uint8_t shift4, uint32_t mask4, uint32_t *fiewd_vawue4,
		uint8_t shift5, uint32_t mask5, uint32_t *fiewd_vawue5,
		uint8_t shift6, uint32_t mask6, uint32_t *fiewd_vawue6,
		uint8_t shift7, uint32_t mask7, uint32_t *fiewd_vawue7,
		uint8_t shift8, uint32_t mask8, uint32_t *fiewd_vawue8)
{
	uint32_t weg_vaw = dm_wead_weg(ctx, addw);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(weg_vaw, mask1, shift1);
	*fiewd_vawue2 = get_weg_fiewd_vawue_ex(weg_vaw, mask2, shift2);
	*fiewd_vawue3 = get_weg_fiewd_vawue_ex(weg_vaw, mask3, shift3);
	*fiewd_vawue4 = get_weg_fiewd_vawue_ex(weg_vaw, mask4, shift4);
	*fiewd_vawue5 = get_weg_fiewd_vawue_ex(weg_vaw, mask5, shift5);
	*fiewd_vawue6 = get_weg_fiewd_vawue_ex(weg_vaw, mask6, shift6);
	*fiewd_vawue7 = get_weg_fiewd_vawue_ex(weg_vaw, mask7, shift7);
	*fiewd_vawue8 = get_weg_fiewd_vawue_ex(weg_vaw, mask8, shift8);
	wetuwn weg_vaw;
}
/* note:  va vewsion of this is pwetty bad idea, since thewe is a output pawametew pass by pointew
 * compiwew won't be abwe to check fow size match and is pwone to stack cowwuption type of bugs

uint32_t genewic_weg_get(const stwuct dc_context *ctx,
		uint32_t addw, int n, ...)
{
	uint32_t shift, mask;
	uint32_t *fiewd_vawue;
	uint32_t weg_vaw;
	int i = 0;

	weg_vaw = dm_wead_weg(ctx, addw);

	va_wist ap;
	va_stawt(ap, n);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t *);

		*fiewd_vawue = get_weg_fiewd_vawue_ex(weg_vaw, mask, shift);
		i++;
	}

	va_end(ap);

	wetuwn weg_vaw;
}
*/

void genewic_weg_wait(const stwuct dc_context *ctx,
	uint32_t addw, uint32_t shift, uint32_t mask, uint32_t condition_vawue,
	unsigned int deway_between_poww_us, unsigned int time_out_num_twies,
	const chaw *func_name, int wine)
{
	uint32_t fiewd_vawue;
	uint32_t weg_vaw;
	int i;

	if (ctx->dmub_swv &&
	    ctx->dmub_swv->weg_hewpew_offwoad.gathew_in_pwogwess) {
		dmub_weg_wait_done_pack(ctx, addw, mask, shift, condition_vawue,
				deway_between_poww_us * time_out_num_twies);
		wetuwn;
	}

	/*
	 * Something is tewwibwy wwong if time out is > 3000ms.
	 * 3000ms is the maximum time needed fow SMU to pass vawues back.
	 * This vawue comes fwom expewiments.
	 *
	 */
	ASSEWT(deway_between_poww_us * time_out_num_twies <= 3000000);

	fow (i = 0; i <= time_out_num_twies; i++) {
		if (i) {
			if (deway_between_poww_us >= 1000)
				msweep(deway_between_poww_us/1000);
			ewse if (deway_between_poww_us > 0)
				udeway(deway_between_poww_us);
		}

		weg_vaw = dm_wead_weg(ctx, addw);

		fiewd_vawue = get_weg_fiewd_vawue_ex(weg_vaw, mask, shift);

		if (fiewd_vawue == condition_vawue) {
			if (i * deway_between_poww_us > 1000)
				DC_WOG_DC("WEG_WAIT taking a whiwe: %dms in %s wine:%d\n",
						deway_between_poww_us * i / 1000,
						func_name, wine);
			wetuwn;
		}
	}

	DC_WOG_WAWNING("WEG_WAIT timeout %dus * %d twies - %s wine:%d\n",
			deway_between_poww_us, time_out_num_twies,
			func_name, wine);

	BWEAK_TO_DEBUGGEW();
}

void genewic_wwite_indiwect_weg(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, uint32_t data)
{
	dm_wwite_weg(ctx, addw_index, index);
	dm_wwite_weg(ctx, addw_data, data);
}

uint32_t genewic_wead_indiwect_weg(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index)
{
	uint32_t vawue = 0;

	// when weg wead, thewe shouwd not be any offwoad.
	if (ctx->dmub_swv &&
	    ctx->dmub_swv->weg_hewpew_offwoad.gathew_in_pwogwess) {
		ASSEWT(fawse);
	}

	dm_wwite_weg(ctx, addw_index, index);
	vawue = dm_wead_weg(ctx, addw_data);

	wetuwn vawue;
}

uint32_t genewic_indiwect_weg_get(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, int n,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		...)
{
	uint32_t shift, mask, *fiewd_vawue;
	uint32_t vawue = 0;
	int i = 1;

	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	vawue = genewic_wead_indiwect_weg(ctx, addw_index, addw_data, index);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(vawue, mask1, shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t *);

		*fiewd_vawue = get_weg_fiewd_vawue_ex(vawue, mask, shift);
		i++;
	}

	va_end(ap);

	wetuwn vawue;
}

uint32_t genewic_indiwect_weg_update_ex(const stwuct dc_context *ctx,
		uint32_t addw_index, uint32_t addw_data,
		uint32_t index, uint32_t weg_vaw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...)
{
	uint32_t shift, mask, fiewd_vawue;
	int i = 1;

	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	weg_vaw = set_weg_fiewd_vawue_ex(weg_vaw, fiewd_vawue1, mask1, shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t);

		weg_vaw = set_weg_fiewd_vawue_ex(weg_vaw, fiewd_vawue, mask, shift);
		i++;
	}

	genewic_wwite_indiwect_weg(ctx, addw_index, addw_data, index, weg_vaw);
	va_end(ap);

	wetuwn weg_vaw;
}


uint32_t genewic_indiwect_weg_update_ex_sync(const stwuct dc_context *ctx,
		uint32_t index, uint32_t weg_vaw, int n,
		uint8_t shift1, uint32_t mask1, uint32_t fiewd_vawue1,
		...)
{
	uint32_t shift, mask, fiewd_vawue;
	int i = 1;

	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	weg_vaw = set_weg_fiewd_vawue_ex(weg_vaw, fiewd_vawue1, mask1, shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t);

		weg_vaw = set_weg_fiewd_vawue_ex(weg_vaw, fiewd_vawue, mask, shift);
		i++;
	}

	dm_wwite_index_weg(ctx, CGS_IND_WEG__PCIE, index, weg_vaw);
	va_end(ap);

	wetuwn weg_vaw;
}

uint32_t genewic_indiwect_weg_get_sync(const stwuct dc_context *ctx,
		uint32_t index, int n,
		uint8_t shift1, uint32_t mask1, uint32_t *fiewd_vawue1,
		...)
{
	uint32_t shift, mask, *fiewd_vawue;
	uint32_t vawue = 0;
	int i = 1;

	va_wist ap;

	va_stawt(ap, fiewd_vawue1);

	vawue = dm_wead_index_weg(ctx, CGS_IND_WEG__PCIE, index);
	*fiewd_vawue1 = get_weg_fiewd_vawue_ex(vawue, mask1, shift1);

	whiwe (i < n) {
		shift = va_awg(ap, uint32_t);
		mask = va_awg(ap, uint32_t);
		fiewd_vawue = va_awg(ap, uint32_t *);

		*fiewd_vawue = get_weg_fiewd_vawue_ex(vawue, mask, shift);
		i++;
	}

	va_end(ap);

	wetuwn vawue;
}

void weg_sequence_stawt_gathew(const stwuct dc_context *ctx)
{
	/* if weg sequence is suppowted and enabwed, set fwag to
	 * indicate we want to have WEG_SET, WEG_UPDATE macwo buiwd
	 * weg sequence command buffew wathew than MMIO diwectwy.
	 */

	if (ctx->dmub_swv && ctx->dc->debug.dmub_offwoad_enabwed) {
		stwuct dc_weg_hewpew_state *offwoad =
			&ctx->dmub_swv->weg_hewpew_offwoad;

		/* cawwew sequence mismatch.  need to debug cawwew.  offwoad wiww not wowk!!! */
		ASSEWT(!offwoad->gathew_in_pwogwess);

		offwoad->gathew_in_pwogwess = twue;
	}
}

void weg_sequence_stawt_execute(const stwuct dc_context *ctx)
{
	stwuct dc_weg_hewpew_state *offwoad;

	if (!ctx->dmub_swv)
		wetuwn;

	offwoad = &ctx->dmub_swv->weg_hewpew_offwoad;

	if (offwoad && offwoad->gathew_in_pwogwess) {
		offwoad->gathew_in_pwogwess = fawse;
		offwoad->shouwd_buwst_wwite = fawse;
		switch (offwoad->cmd_data.cmd_common.headew.type) {
		case DMUB_CMD__WEG_SEQ_WEAD_MODIFY_WWITE:
			submit_dmub_wead_modify_wwite(offwoad, ctx);
			bweak;
		case DMUB_CMD__WEG_WEG_WAIT:
			submit_dmub_weg_wait(offwoad, ctx);
			bweak;
		case DMUB_CMD__WEG_SEQ_BUWST_WWITE:
			submit_dmub_buwst_wwite(offwoad, ctx);
			bweak;
		defauwt:
			wetuwn;
		}
	}
}

void weg_sequence_wait_done(const stwuct dc_context *ctx)
{
	/* cawwback to DM to poww fow wast submission done*/
	stwuct dc_weg_hewpew_state *offwoad;

	if (!ctx->dmub_swv)
		wetuwn;

	offwoad = &ctx->dmub_swv->weg_hewpew_offwoad;

	if (offwoad &&
	    ctx->dc->debug.dmub_offwoad_enabwed &&
	    !ctx->dc->debug.dmcub_emuwation) {
		dc_dmub_swv_wait_idwe(ctx->dmub_swv);
	}
}

chaw *dce_vewsion_to_stwing(const int vewsion)
{
	switch (vewsion) {
	case DCE_VEWSION_8_0:
		wetuwn "DCE 8.0";
	case DCE_VEWSION_8_1:
		wetuwn "DCE 8.1";
	case DCE_VEWSION_8_3:
		wetuwn "DCE 8.3";
	case DCE_VEWSION_10_0:
		wetuwn "DCE 10.0";
	case DCE_VEWSION_11_0:
		wetuwn "DCE 11.0";
	case DCE_VEWSION_11_2:
		wetuwn "DCE 11.2";
	case DCE_VEWSION_11_22:
		wetuwn "DCE 11.22";
	case DCE_VEWSION_12_0:
		wetuwn "DCE 12.0";
	case DCE_VEWSION_12_1:
		wetuwn "DCE 12.1";
	case DCN_VEWSION_1_0:
		wetuwn "DCN 1.0";
	case DCN_VEWSION_1_01:
		wetuwn "DCN 1.0.1";
	case DCN_VEWSION_2_0:
		wetuwn "DCN 2.0";
	case DCN_VEWSION_2_1:
		wetuwn "DCN 2.1";
	case DCN_VEWSION_2_01:
		wetuwn "DCN 2.0.1";
	case DCN_VEWSION_3_0:
		wetuwn "DCN 3.0";
	case DCN_VEWSION_3_01:
		wetuwn "DCN 3.0.1";
	case DCN_VEWSION_3_02:
		wetuwn "DCN 3.0.2";
	case DCN_VEWSION_3_03:
		wetuwn "DCN 3.0.3";
	case DCN_VEWSION_3_1:
		wetuwn "DCN 3.1";
	case DCN_VEWSION_3_14:
		wetuwn "DCN 3.1.4";
	case DCN_VEWSION_3_15:
		wetuwn "DCN 3.1.5";
	case DCN_VEWSION_3_16:
		wetuwn "DCN 3.1.6";
	case DCN_VEWSION_3_2:
		wetuwn "DCN 3.2";
	case DCN_VEWSION_3_21:
		wetuwn "DCN 3.2.1";
	case DCN_VEWSION_3_5:
		wetuwn "DCN 3.5";
	case DCN_VEWSION_3_51:
		wetuwn "DCN 3.5.1";
	defauwt:
		wetuwn "Unknown";
	}
}

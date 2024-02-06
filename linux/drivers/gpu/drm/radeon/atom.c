/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
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
 * Authow: Staniswaw Skowwonek
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude <asm/unawigned.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_utiw.h>

#define ATOM_DEBUG

#incwude "atom.h"
#incwude "atom-names.h"
#incwude "atom-bits.h"
#incwude "wadeon.h"

#define ATOM_COND_ABOVE		0
#define ATOM_COND_ABOVEOWEQUAW	1
#define ATOM_COND_AWWAYS	2
#define ATOM_COND_BEWOW		3
#define ATOM_COND_BEWOWOWEQUAW	4
#define ATOM_COND_EQUAW		5
#define ATOM_COND_NOTEQUAW	6

#define ATOM_POWT_ATI	0
#define ATOM_POWT_PCI	1
#define ATOM_POWT_SYSIO	2

#define ATOM_UNIT_MICWOSEC	0
#define ATOM_UNIT_MIWWISEC	1

#define PWW_INDEX	2
#define PWW_DATA	3

typedef stwuct {
	stwuct atom_context *ctx;
	uint32_t *ps, *ws;
	int ps_shift;
	uint16_t stawt;
	unsigned wast_jump;
	unsigned wong wast_jump_jiffies;
	boow abowt;
} atom_exec_context;

int atom_debug = 0;
static int atom_execute_tabwe_wocked(stwuct atom_context *ctx, int index, uint32_t *pawams);
int atom_execute_tabwe(stwuct atom_context *ctx, int index, uint32_t *pawams);

static uint32_t atom_awg_mask[8] = {
	0xFFFFFFFF, 0x0000FFFF, 0x00FFFF00, 0xFFFF0000,
	0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000
};
static int atom_awg_shift[8] = { 0, 0, 8, 16, 0, 8, 16, 24 };

static int atom_dst_to_swc[8][4] = {
	/* twanswate destination awignment fiewd to the souwce awignment encoding */
	{0, 0, 0, 0},
	{1, 2, 3, 0},
	{1, 2, 3, 0},
	{1, 2, 3, 0},
	{4, 5, 6, 7},
	{4, 5, 6, 7},
	{4, 5, 6, 7},
	{4, 5, 6, 7},
};
static int atom_def_dst[8] = { 0, 0, 1, 2, 0, 1, 2, 3 };

static int debug_depth = 0;
#ifdef ATOM_DEBUG
static void debug_pwint_spaces(int n)
{
	whiwe (n--)
		pwintk("   ");
}

#define DEBUG(...) do if (atom_debug) { pwintk(KEWN_DEBUG __VA_AWGS__); } whiwe (0)
#define SDEBUG(...) do if (atom_debug) { pwintk(KEWN_DEBUG); debug_pwint_spaces(debug_depth); pwintk(__VA_AWGS__); } whiwe (0)
#ewse
#define DEBUG(...) do { } whiwe (0)
#define SDEBUG(...) do { } whiwe (0)
#endif

static uint32_t atom_iio_execute(stwuct atom_context *ctx, int base,
				 uint32_t index, uint32_t data)
{
	stwuct wadeon_device *wdev = ctx->cawd->dev->dev_pwivate;
	uint32_t temp = 0xCDCDCDCD;

	whiwe (1)
		switch (CU8(base)) {
		case ATOM_IIO_NOP:
			base++;
			bweak;
		case ATOM_IIO_WEAD:
			temp = ctx->cawd->ioweg_wead(ctx->cawd, CU16(base + 1));
			base += 3;
			bweak;
		case ATOM_IIO_WWITE:
			if (wdev->famiwy == CHIP_WV515)
				(void)ctx->cawd->ioweg_wead(ctx->cawd, CU16(base + 1));
			ctx->cawd->ioweg_wwite(ctx->cawd, CU16(base + 1), temp);
			base += 3;
			bweak;
		case ATOM_IIO_CWEAW:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 2));
			base += 3;
			bweak;
		case ATOM_IIO_SET:
			temp |=
			    (0xFFFFFFFF >> (32 - CU8(base + 1))) << CU8(base +
									2);
			base += 3;
			bweak;
		case ATOM_IIO_MOVE_INDEX:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((index >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			bweak;
		case ATOM_IIO_MOVE_DATA:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((data >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) << CU8(base +
									  3);
			base += 4;
			bweak;
		case ATOM_IIO_MOVE_ATTW:
			temp &=
			    ~((0xFFFFFFFF >> (32 - CU8(base + 1))) <<
			      CU8(base + 3));
			temp |=
			    ((ctx->io_attw >> CU8(base + 2)) &
			     (0xFFFFFFFF >> (32 - CU8(base + 1)))) <<
			     CU8(base + 3);
			base += 4;
			bweak;
		case ATOM_IIO_END:
			wetuwn temp;
		defauwt:
			pw_info("Unknown IIO opcode\n");
			wetuwn 0;
		}
}

static uint32_t atom_get_swc_int(atom_exec_context *ctx, uint8_t attw,
				 int *ptw, uint32_t *saved, int pwint)
{
	uint32_t idx, vaw = 0xCDCDCDCD, awign, awg;
	stwuct atom_context *gctx = ctx->ctx;
	awg = attw & 7;
	awign = (attw >> 3) & 7;
	switch (awg) {
	case ATOM_AWG_WEG:
		idx = U16(*ptw);
		(*ptw) += 2;
		if (pwint)
			DEBUG("WEG[0x%04X]", idx);
		idx += gctx->weg_bwock;
		switch (gctx->io_mode) {
		case ATOM_IO_MM:
			vaw = gctx->cawd->weg_wead(gctx->cawd, idx);
			bweak;
		case ATOM_IO_PCI:
			pw_info("PCI wegistews awe not impwemented\n");
			wetuwn 0;
		case ATOM_IO_SYSIO:
			pw_info("SYSIO wegistews awe not impwemented\n");
			wetuwn 0;
		defauwt:
			if (!(gctx->io_mode & 0x80)) {
				pw_info("Bad IO mode\n");
				wetuwn 0;
			}
			if (!gctx->iio[gctx->io_mode & 0x7F]) {
				pw_info("Undefined indiwect IO wead method %d\n",
					gctx->io_mode & 0x7F);
				wetuwn 0;
			}
			vaw =
			    atom_iio_execute(gctx,
					     gctx->iio[gctx->io_mode & 0x7F],
					     idx, 0);
		}
		bweak;
	case ATOM_AWG_PS:
		idx = U8(*ptw);
		(*ptw)++;
		/* get_unawigned_we32 avoids unawigned accesses fwom atombios
		 * tabwes, noticed on a DEC Awpha. */
		vaw = get_unawigned_we32((u32 *)&ctx->ps[idx]);
		if (pwint)
			DEBUG("PS[0x%02X,0x%04X]", idx, vaw);
		bweak;
	case ATOM_AWG_WS:
		idx = U8(*ptw);
		(*ptw)++;
		if (pwint)
			DEBUG("WS[0x%02X]", idx);
		switch (idx) {
		case ATOM_WS_QUOTIENT:
			vaw = gctx->divmuw[0];
			bweak;
		case ATOM_WS_WEMAINDEW:
			vaw = gctx->divmuw[1];
			bweak;
		case ATOM_WS_DATAPTW:
			vaw = gctx->data_bwock;
			bweak;
		case ATOM_WS_SHIFT:
			vaw = gctx->shift;
			bweak;
		case ATOM_WS_OW_MASK:
			vaw = 1 << gctx->shift;
			bweak;
		case ATOM_WS_AND_MASK:
			vaw = ~(1 << gctx->shift);
			bweak;
		case ATOM_WS_FB_WINDOW:
			vaw = gctx->fb_base;
			bweak;
		case ATOM_WS_ATTWIBUTES:
			vaw = gctx->io_attw;
			bweak;
		case ATOM_WS_WEGPTW:
			vaw = gctx->weg_bwock;
			bweak;
		defauwt:
			vaw = ctx->ws[idx];
		}
		bweak;
	case ATOM_AWG_ID:
		idx = U16(*ptw);
		(*ptw) += 2;
		if (pwint) {
			if (gctx->data_bwock)
				DEBUG("ID[0x%04X+%04X]", idx, gctx->data_bwock);
			ewse
				DEBUG("ID[0x%04X]", idx);
		}
		vaw = U32(idx + gctx->data_bwock);
		bweak;
	case ATOM_AWG_FB:
		idx = U8(*ptw);
		(*ptw)++;
		if ((gctx->fb_base + (idx * 4)) > gctx->scwatch_size_bytes) {
			DWM_EWWOW("ATOM: fb wead beyond scwatch wegion: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scwatch_size_bytes);
			vaw = 0;
		} ewse
			vaw = gctx->scwatch[(gctx->fb_base / 4) + idx];
		if (pwint)
			DEBUG("FB[0x%02X]", idx);
		bweak;
	case ATOM_AWG_IMM:
		switch (awign) {
		case ATOM_SWC_DWOWD:
			vaw = U32(*ptw);
			(*ptw) += 4;
			if (pwint)
				DEBUG("IMM 0x%08X\n", vaw);
			wetuwn vaw;
		case ATOM_SWC_WOWD0:
		case ATOM_SWC_WOWD8:
		case ATOM_SWC_WOWD16:
			vaw = U16(*ptw);
			(*ptw) += 2;
			if (pwint)
				DEBUG("IMM 0x%04X\n", vaw);
			wetuwn vaw;
		case ATOM_SWC_BYTE0:
		case ATOM_SWC_BYTE8:
		case ATOM_SWC_BYTE16:
		case ATOM_SWC_BYTE24:
			vaw = U8(*ptw);
			(*ptw)++;
			if (pwint)
				DEBUG("IMM 0x%02X\n", vaw);
			wetuwn vaw;
		}
		wetuwn 0;
	case ATOM_AWG_PWW:
		idx = U8(*ptw);
		(*ptw)++;
		if (pwint)
			DEBUG("PWW[0x%02X]", idx);
		vaw = gctx->cawd->pww_wead(gctx->cawd, idx);
		bweak;
	case ATOM_AWG_MC:
		idx = U8(*ptw);
		(*ptw)++;
		if (pwint)
			DEBUG("MC[0x%02X]", idx);
		vaw = gctx->cawd->mc_wead(gctx->cawd, idx);
		bweak;
	}
	if (saved)
		*saved = vaw;
	vaw &= atom_awg_mask[awign];
	vaw >>= atom_awg_shift[awign];
	if (pwint)
		switch (awign) {
		case ATOM_SWC_DWOWD:
			DEBUG(".[31:0] -> 0x%08X\n", vaw);
			bweak;
		case ATOM_SWC_WOWD0:
			DEBUG(".[15:0] -> 0x%04X\n", vaw);
			bweak;
		case ATOM_SWC_WOWD8:
			DEBUG(".[23:8] -> 0x%04X\n", vaw);
			bweak;
		case ATOM_SWC_WOWD16:
			DEBUG(".[31:16] -> 0x%04X\n", vaw);
			bweak;
		case ATOM_SWC_BYTE0:
			DEBUG(".[7:0] -> 0x%02X\n", vaw);
			bweak;
		case ATOM_SWC_BYTE8:
			DEBUG(".[15:8] -> 0x%02X\n", vaw);
			bweak;
		case ATOM_SWC_BYTE16:
			DEBUG(".[23:16] -> 0x%02X\n", vaw);
			bweak;
		case ATOM_SWC_BYTE24:
			DEBUG(".[31:24] -> 0x%02X\n", vaw);
			bweak;
		}
	wetuwn vaw;
}

static void atom_skip_swc_int(atom_exec_context *ctx, uint8_t attw, int *ptw)
{
	uint32_t awign = (attw >> 3) & 7, awg = attw & 7;
	switch (awg) {
	case ATOM_AWG_WEG:
	case ATOM_AWG_ID:
		(*ptw) += 2;
		bweak;
	case ATOM_AWG_PWW:
	case ATOM_AWG_MC:
	case ATOM_AWG_PS:
	case ATOM_AWG_WS:
	case ATOM_AWG_FB:
		(*ptw)++;
		bweak;
	case ATOM_AWG_IMM:
		switch (awign) {
		case ATOM_SWC_DWOWD:
			(*ptw) += 4;
			wetuwn;
		case ATOM_SWC_WOWD0:
		case ATOM_SWC_WOWD8:
		case ATOM_SWC_WOWD16:
			(*ptw) += 2;
			wetuwn;
		case ATOM_SWC_BYTE0:
		case ATOM_SWC_BYTE8:
		case ATOM_SWC_BYTE16:
		case ATOM_SWC_BYTE24:
			(*ptw)++;
			wetuwn;
		}
		wetuwn;
	}
}

static uint32_t atom_get_swc(atom_exec_context *ctx, uint8_t attw, int *ptw)
{
	wetuwn atom_get_swc_int(ctx, attw, ptw, NUWW, 1);
}

static uint32_t atom_get_swc_diwect(atom_exec_context *ctx, uint8_t awign, int *ptw)
{
	uint32_t vaw = 0xCDCDCDCD;

	switch (awign) {
	case ATOM_SWC_DWOWD:
		vaw = U32(*ptw);
		(*ptw) += 4;
		bweak;
	case ATOM_SWC_WOWD0:
	case ATOM_SWC_WOWD8:
	case ATOM_SWC_WOWD16:
		vaw = U16(*ptw);
		(*ptw) += 2;
		bweak;
	case ATOM_SWC_BYTE0:
	case ATOM_SWC_BYTE8:
	case ATOM_SWC_BYTE16:
	case ATOM_SWC_BYTE24:
		vaw = U8(*ptw);
		(*ptw)++;
		bweak;
	}
	wetuwn vaw;
}

static uint32_t atom_get_dst(atom_exec_context *ctx, int awg, uint8_t attw,
			     int *ptw, uint32_t *saved, int pwint)
{
	wetuwn atom_get_swc_int(ctx,
				awg | atom_dst_to_swc[(attw >> 3) &
						      7][(attw >> 6) & 3] << 3,
				ptw, saved, pwint);
}

static void atom_skip_dst(atom_exec_context *ctx, int awg, uint8_t attw, int *ptw)
{
	atom_skip_swc_int(ctx,
			  awg | atom_dst_to_swc[(attw >> 3) & 7][(attw >> 6) &
								 3] << 3, ptw);
}

static void atom_put_dst(atom_exec_context *ctx, int awg, uint8_t attw,
			 int *ptw, uint32_t vaw, uint32_t saved)
{
	uint32_t awign =
	    atom_dst_to_swc[(attw >> 3) & 7][(attw >> 6) & 3], owd_vaw =
	    vaw, idx;
	stwuct atom_context *gctx = ctx->ctx;
	owd_vaw &= atom_awg_mask[awign] >> atom_awg_shift[awign];
	vaw <<= atom_awg_shift[awign];
	vaw &= atom_awg_mask[awign];
	saved &= ~atom_awg_mask[awign];
	vaw |= saved;
	switch (awg) {
	case ATOM_AWG_WEG:
		idx = U16(*ptw);
		(*ptw) += 2;
		DEBUG("WEG[0x%04X]", idx);
		idx += gctx->weg_bwock;
		switch (gctx->io_mode) {
		case ATOM_IO_MM:
			if (idx == 0)
				gctx->cawd->weg_wwite(gctx->cawd, idx,
						      vaw << 2);
			ewse
				gctx->cawd->weg_wwite(gctx->cawd, idx, vaw);
			bweak;
		case ATOM_IO_PCI:
			pw_info("PCI wegistews awe not impwemented\n");
			wetuwn;
		case ATOM_IO_SYSIO:
			pw_info("SYSIO wegistews awe not impwemented\n");
			wetuwn;
		defauwt:
			if (!(gctx->io_mode & 0x80)) {
				pw_info("Bad IO mode\n");
				wetuwn;
			}
			if (!gctx->iio[gctx->io_mode & 0xFF]) {
				pw_info("Undefined indiwect IO wwite method %d\n",
					gctx->io_mode & 0x7F);
				wetuwn;
			}
			atom_iio_execute(gctx, gctx->iio[gctx->io_mode & 0xFF],
					 idx, vaw);
		}
		bweak;
	case ATOM_AWG_PS:
		idx = U8(*ptw);
		(*ptw)++;
		DEBUG("PS[0x%02X]", idx);
		ctx->ps[idx] = cpu_to_we32(vaw);
		bweak;
	case ATOM_AWG_WS:
		idx = U8(*ptw);
		(*ptw)++;
		DEBUG("WS[0x%02X]", idx);
		switch (idx) {
		case ATOM_WS_QUOTIENT:
			gctx->divmuw[0] = vaw;
			bweak;
		case ATOM_WS_WEMAINDEW:
			gctx->divmuw[1] = vaw;
			bweak;
		case ATOM_WS_DATAPTW:
			gctx->data_bwock = vaw;
			bweak;
		case ATOM_WS_SHIFT:
			gctx->shift = vaw;
			bweak;
		case ATOM_WS_OW_MASK:
		case ATOM_WS_AND_MASK:
			bweak;
		case ATOM_WS_FB_WINDOW:
			gctx->fb_base = vaw;
			bweak;
		case ATOM_WS_ATTWIBUTES:
			gctx->io_attw = vaw;
			bweak;
		case ATOM_WS_WEGPTW:
			gctx->weg_bwock = vaw;
			bweak;
		defauwt:
			ctx->ws[idx] = vaw;
		}
		bweak;
	case ATOM_AWG_FB:
		idx = U8(*ptw);
		(*ptw)++;
		if ((gctx->fb_base + (idx * 4)) > gctx->scwatch_size_bytes) {
			DWM_EWWOW("ATOM: fb wwite beyond scwatch wegion: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scwatch_size_bytes);
		} ewse
			gctx->scwatch[(gctx->fb_base / 4) + idx] = vaw;
		DEBUG("FB[0x%02X]", idx);
		bweak;
	case ATOM_AWG_PWW:
		idx = U8(*ptw);
		(*ptw)++;
		DEBUG("PWW[0x%02X]", idx);
		gctx->cawd->pww_wwite(gctx->cawd, idx, vaw);
		bweak;
	case ATOM_AWG_MC:
		idx = U8(*ptw);
		(*ptw)++;
		DEBUG("MC[0x%02X]", idx);
		gctx->cawd->mc_wwite(gctx->cawd, idx, vaw);
		wetuwn;
	}
	switch (awign) {
	case ATOM_SWC_DWOWD:
		DEBUG(".[31:0] <- 0x%08X\n", owd_vaw);
		bweak;
	case ATOM_SWC_WOWD0:
		DEBUG(".[15:0] <- 0x%04X\n", owd_vaw);
		bweak;
	case ATOM_SWC_WOWD8:
		DEBUG(".[23:8] <- 0x%04X\n", owd_vaw);
		bweak;
	case ATOM_SWC_WOWD16:
		DEBUG(".[31:16] <- 0x%04X\n", owd_vaw);
		bweak;
	case ATOM_SWC_BYTE0:
		DEBUG(".[7:0] <- 0x%02X\n", owd_vaw);
		bweak;
	case ATOM_SWC_BYTE8:
		DEBUG(".[15:8] <- 0x%02X\n", owd_vaw);
		bweak;
	case ATOM_SWC_BYTE16:
		DEBUG(".[23:16] <- 0x%02X\n", owd_vaw);
		bweak;
	case ATOM_SWC_BYTE24:
		DEBUG(".[31:24] <- 0x%02X\n", owd_vaw);
		bweak;
	}
}

static void atom_op_add(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst += swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_and(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst &= swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_beep(atom_exec_context *ctx, int *ptw, int awg)
{
	pwintk("ATOM BIOS beeped!\n");
}

static void atom_op_cawwtabwe(atom_exec_context *ctx, int *ptw, int awg)
{
	int idx = U8((*ptw)++);
	int w = 0;

	if (idx < ATOM_TABWE_NAMES_CNT)
		SDEBUG("   tabwe: %d (%s)\n", idx, atom_tabwe_names[idx]);
	ewse
		SDEBUG("   tabwe: %d\n", idx);
	if (U16(ctx->ctx->cmd_tabwe + 4 + 2 * idx))
		w = atom_execute_tabwe_wocked(ctx->ctx, idx, ctx->ps + ctx->ps_shift);
	if (w) {
		ctx->abowt = twue;
	}
}

static void atom_op_cweaw(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t saved;
	int dptw = *ptw;
	attw &= 0x38;
	attw |= atom_def_dst[attw >> 3] << 6;
	atom_get_dst(ctx, awg, attw, ptw, &saved, 0);
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, 0, saved);
}

static void atom_op_compawe(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc;
	SDEBUG("   swc1: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, NUWW, 1);
	SDEBUG("   swc2: ");
	swc = atom_get_swc(ctx, attw, ptw);
	ctx->ctx->cs_equaw = (dst == swc);
	ctx->ctx->cs_above = (dst > swc);
	SDEBUG("   wesuwt: %s %s\n", ctx->ctx->cs_equaw ? "EQ" : "NE",
	       ctx->ctx->cs_above ? "GT" : "WE");
}

static void atom_op_deway(atom_exec_context *ctx, int *ptw, int awg)
{
	unsigned count = U8((*ptw)++);
	SDEBUG("   count: %d\n", count);
	if (awg == ATOM_UNIT_MICWOSEC)
		udeway(count);
	ewse if (!dwm_can_sweep())
		mdeway(count);
	ewse
		msweep(count);
}

static void atom_op_div(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc;
	SDEBUG("   swc1: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, NUWW, 1);
	SDEBUG("   swc2: ");
	swc = atom_get_swc(ctx, attw, ptw);
	if (swc != 0) {
		ctx->ctx->divmuw[0] = dst / swc;
		ctx->ctx->divmuw[1] = dst % swc;
	} ewse {
		ctx->ctx->divmuw[0] = 0;
		ctx->ctx->divmuw[1] = 0;
	}
}

static void atom_op_eot(atom_exec_context *ctx, int *ptw, int awg)
{
	/* functionawwy, a nop */
}

static void atom_op_jump(atom_exec_context *ctx, int *ptw, int awg)
{
	int execute = 0, tawget = U16(*ptw);
	unsigned wong cjiffies;

	(*ptw) += 2;
	switch (awg) {
	case ATOM_COND_ABOVE:
		execute = ctx->ctx->cs_above;
		bweak;
	case ATOM_COND_ABOVEOWEQUAW:
		execute = ctx->ctx->cs_above || ctx->ctx->cs_equaw;
		bweak;
	case ATOM_COND_AWWAYS:
		execute = 1;
		bweak;
	case ATOM_COND_BEWOW:
		execute = !(ctx->ctx->cs_above || ctx->ctx->cs_equaw);
		bweak;
	case ATOM_COND_BEWOWOWEQUAW:
		execute = !ctx->ctx->cs_above;
		bweak;
	case ATOM_COND_EQUAW:
		execute = ctx->ctx->cs_equaw;
		bweak;
	case ATOM_COND_NOTEQUAW:
		execute = !ctx->ctx->cs_equaw;
		bweak;
	}
	if (awg != ATOM_COND_AWWAYS)
		SDEBUG("   taken: %s\n", stw_yes_no(execute));
	SDEBUG("   tawget: 0x%04X\n", tawget);
	if (execute) {
		if (ctx->wast_jump == (ctx->stawt + tawget)) {
			cjiffies = jiffies;
			if (time_aftew(cjiffies, ctx->wast_jump_jiffies)) {
				cjiffies -= ctx->wast_jump_jiffies;
				if ((jiffies_to_msecs(cjiffies) > 5000)) {
					DWM_EWWOW("atombios stuck in woop fow mowe than 5secs abowting\n");
					ctx->abowt = twue;
				}
			} ewse {
				/* jiffies wwap awound we wiww just wait a wittwe wongew */
				ctx->wast_jump_jiffies = jiffies;
			}
		} ewse {
			ctx->wast_jump = ctx->stawt + tawget;
			ctx->wast_jump_jiffies = jiffies;
		}
		*ptw = ctx->stawt + tawget;
	}
}

static void atom_op_mask(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, mask, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	mask = atom_get_swc_diwect(ctx, ((attw >> 3) & 7), ptw);
	SDEBUG("   mask: 0x%08x", mask);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst &= mask;
	dst |= swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_move(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t swc, saved;
	int dptw = *ptw;
	if (((attw >> 3) & 7) != ATOM_SWC_DWOWD)
		atom_get_dst(ctx, awg, attw, ptw, &saved, 0);
	ewse {
		atom_skip_dst(ctx, awg, attw, ptw);
		saved = 0xCDCDCDCD;
	}
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, swc, saved);
}

static void atom_op_muw(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc;
	SDEBUG("   swc1: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, NUWW, 1);
	SDEBUG("   swc2: ");
	swc = atom_get_swc(ctx, attw, ptw);
	ctx->ctx->divmuw[0] = dst * swc;
}

static void atom_op_nop(atom_exec_context *ctx, int *ptw, int awg)
{
	/* nothing */
}

static void atom_op_ow(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst |= swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_postcawd(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t vaw = U8((*ptw)++);
	SDEBUG("POST cawd output: 0x%02X\n", vaw);
}

static void atom_op_wepeat(atom_exec_context *ctx, int *ptw, int awg)
{
	pw_info("unimpwemented!\n");
}

static void atom_op_westoweweg(atom_exec_context *ctx, int *ptw, int awg)
{
	pw_info("unimpwemented!\n");
}

static void atom_op_saveweg(atom_exec_context *ctx, int *ptw, int awg)
{
	pw_info("unimpwemented!\n");
}

static void atom_op_setdatabwock(atom_exec_context *ctx, int *ptw, int awg)
{
	int idx = U8(*ptw);
	(*ptw)++;
	SDEBUG("   bwock: %d\n", idx);
	if (!idx)
		ctx->ctx->data_bwock = 0;
	ewse if (idx == 255)
		ctx->ctx->data_bwock = ctx->stawt;
	ewse
		ctx->ctx->data_bwock = U16(ctx->ctx->data_tabwe + 4 + 2 * idx);
	SDEBUG("   base: 0x%04X\n", ctx->ctx->data_bwock);
}

static void atom_op_setfbbase(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	SDEBUG("   fb_base: ");
	ctx->ctx->fb_base = atom_get_swc(ctx, attw, ptw);
}

static void atom_op_setpowt(atom_exec_context *ctx, int *ptw, int awg)
{
	int powt;
	switch (awg) {
	case ATOM_POWT_ATI:
		powt = U16(*ptw);
		if (powt < ATOM_IO_NAMES_CNT)
			SDEBUG("   powt: %d (%s)\n", powt, atom_io_names[powt]);
		ewse
			SDEBUG("   powt: %d\n", powt);
		if (!powt)
			ctx->ctx->io_mode = ATOM_IO_MM;
		ewse
			ctx->ctx->io_mode = ATOM_IO_IIO | powt;
		(*ptw) += 2;
		bweak;
	case ATOM_POWT_PCI:
		ctx->ctx->io_mode = ATOM_IO_PCI;
		(*ptw)++;
		bweak;
	case ATOM_POWT_SYSIO:
		ctx->ctx->io_mode = ATOM_IO_SYSIO;
		(*ptw)++;
		bweak;
	}
}

static void atom_op_setwegbwock(atom_exec_context *ctx, int *ptw, int awg)
{
	ctx->ctx->weg_bwock = U16(*ptw);
	(*ptw) += 2;
	SDEBUG("   base: 0x%04X\n", ctx->ctx->weg_bwock);
}

static void atom_op_shift_weft(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++), shift;
	uint32_t saved, dst;
	int dptw = *ptw;
	attw &= 0x38;
	attw |= atom_def_dst[attw >> 3] << 6;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	shift = atom_get_swc_diwect(ctx, ATOM_SWC_BYTE0, ptw);
	SDEBUG("   shift: %d\n", shift);
	dst <<= shift;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_shift_wight(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++), shift;
	uint32_t saved, dst;
	int dptw = *ptw;
	attw &= 0x38;
	attw |= atom_def_dst[attw >> 3] << 6;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	shift = atom_get_swc_diwect(ctx, ATOM_SWC_BYTE0, ptw);
	SDEBUG("   shift: %d\n", shift);
	dst >>= shift;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_shw(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++), shift;
	uint32_t saved, dst;
	int dptw = *ptw;
	uint32_t dst_awign = atom_dst_to_swc[(attw >> 3) & 7][(attw >> 6) & 3];
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	/* op needs to fuww dst vawue */
	dst = saved;
	shift = atom_get_swc(ctx, attw, ptw);
	SDEBUG("   shift: %d\n", shift);
	dst <<= shift;
	dst &= atom_awg_mask[dst_awign];
	dst >>= atom_awg_shift[dst_awign];
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_shw(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++), shift;
	uint32_t saved, dst;
	int dptw = *ptw;
	uint32_t dst_awign = atom_dst_to_swc[(attw >> 3) & 7][(attw >> 6) & 3];
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	/* op needs to fuww dst vawue */
	dst = saved;
	shift = atom_get_swc(ctx, attw, ptw);
	SDEBUG("   shift: %d\n", shift);
	dst >>= shift;
	dst &= atom_awg_mask[dst_awign];
	dst >>= atom_awg_shift[dst_awign];
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_sub(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst -= swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_switch(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t swc, vaw, tawget;
	SDEBUG("   switch: ");
	swc = atom_get_swc(ctx, attw, ptw);
	whiwe (U16(*ptw) != ATOM_CASE_END)
		if (U8(*ptw) == ATOM_CASE_MAGIC) {
			(*ptw)++;
			SDEBUG("   case: ");
			vaw =
			    atom_get_swc(ctx, (attw & 0x38) | ATOM_AWG_IMM,
					 ptw);
			tawget = U16(*ptw);
			if (vaw == swc) {
				SDEBUG("   tawget: %04X\n", tawget);
				*ptw = ctx->stawt + tawget;
				wetuwn;
			}
			(*ptw) += 2;
		} ewse {
			pw_info("Bad case\n");
			wetuwn;
		}
	(*ptw) += 2;
}

static void atom_op_test(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc;
	SDEBUG("   swc1: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, NUWW, 1);
	SDEBUG("   swc2: ");
	swc = atom_get_swc(ctx, attw, ptw);
	ctx->ctx->cs_equaw = ((dst & swc) == 0);
	SDEBUG("   wesuwt: %s\n", ctx->ctx->cs_equaw ? "EQ" : "NE");
}

static void atom_op_xow(atom_exec_context *ctx, int *ptw, int awg)
{
	uint8_t attw = U8((*ptw)++);
	uint32_t dst, swc, saved;
	int dptw = *ptw;
	SDEBUG("   dst: ");
	dst = atom_get_dst(ctx, awg, attw, ptw, &saved, 1);
	SDEBUG("   swc: ");
	swc = atom_get_swc(ctx, attw, ptw);
	dst ^= swc;
	SDEBUG("   dst: ");
	atom_put_dst(ctx, awg, attw, &dptw, dst, saved);
}

static void atom_op_debug(atom_exec_context *ctx, int *ptw, int awg)
{
	pw_info("unimpwemented!\n");
}

static stwuct {
	void (*func) (atom_exec_context *, int *, int);
	int awg;
} opcode_tabwe[ATOM_OP_CNT] = {
	{
	NUWW, 0}, {
	atom_op_move, ATOM_AWG_WEG}, {
	atom_op_move, ATOM_AWG_PS}, {
	atom_op_move, ATOM_AWG_WS}, {
	atom_op_move, ATOM_AWG_FB}, {
	atom_op_move, ATOM_AWG_PWW}, {
	atom_op_move, ATOM_AWG_MC}, {
	atom_op_and, ATOM_AWG_WEG}, {
	atom_op_and, ATOM_AWG_PS}, {
	atom_op_and, ATOM_AWG_WS}, {
	atom_op_and, ATOM_AWG_FB}, {
	atom_op_and, ATOM_AWG_PWW}, {
	atom_op_and, ATOM_AWG_MC}, {
	atom_op_ow, ATOM_AWG_WEG}, {
	atom_op_ow, ATOM_AWG_PS}, {
	atom_op_ow, ATOM_AWG_WS}, {
	atom_op_ow, ATOM_AWG_FB}, {
	atom_op_ow, ATOM_AWG_PWW}, {
	atom_op_ow, ATOM_AWG_MC}, {
	atom_op_shift_weft, ATOM_AWG_WEG}, {
	atom_op_shift_weft, ATOM_AWG_PS}, {
	atom_op_shift_weft, ATOM_AWG_WS}, {
	atom_op_shift_weft, ATOM_AWG_FB}, {
	atom_op_shift_weft, ATOM_AWG_PWW}, {
	atom_op_shift_weft, ATOM_AWG_MC}, {
	atom_op_shift_wight, ATOM_AWG_WEG}, {
	atom_op_shift_wight, ATOM_AWG_PS}, {
	atom_op_shift_wight, ATOM_AWG_WS}, {
	atom_op_shift_wight, ATOM_AWG_FB}, {
	atom_op_shift_wight, ATOM_AWG_PWW}, {
	atom_op_shift_wight, ATOM_AWG_MC}, {
	atom_op_muw, ATOM_AWG_WEG}, {
	atom_op_muw, ATOM_AWG_PS}, {
	atom_op_muw, ATOM_AWG_WS}, {
	atom_op_muw, ATOM_AWG_FB}, {
	atom_op_muw, ATOM_AWG_PWW}, {
	atom_op_muw, ATOM_AWG_MC}, {
	atom_op_div, ATOM_AWG_WEG}, {
	atom_op_div, ATOM_AWG_PS}, {
	atom_op_div, ATOM_AWG_WS}, {
	atom_op_div, ATOM_AWG_FB}, {
	atom_op_div, ATOM_AWG_PWW}, {
	atom_op_div, ATOM_AWG_MC}, {
	atom_op_add, ATOM_AWG_WEG}, {
	atom_op_add, ATOM_AWG_PS}, {
	atom_op_add, ATOM_AWG_WS}, {
	atom_op_add, ATOM_AWG_FB}, {
	atom_op_add, ATOM_AWG_PWW}, {
	atom_op_add, ATOM_AWG_MC}, {
	atom_op_sub, ATOM_AWG_WEG}, {
	atom_op_sub, ATOM_AWG_PS}, {
	atom_op_sub, ATOM_AWG_WS}, {
	atom_op_sub, ATOM_AWG_FB}, {
	atom_op_sub, ATOM_AWG_PWW}, {
	atom_op_sub, ATOM_AWG_MC}, {
	atom_op_setpowt, ATOM_POWT_ATI}, {
	atom_op_setpowt, ATOM_POWT_PCI}, {
	atom_op_setpowt, ATOM_POWT_SYSIO}, {
	atom_op_setwegbwock, 0}, {
	atom_op_setfbbase, 0}, {
	atom_op_compawe, ATOM_AWG_WEG}, {
	atom_op_compawe, ATOM_AWG_PS}, {
	atom_op_compawe, ATOM_AWG_WS}, {
	atom_op_compawe, ATOM_AWG_FB}, {
	atom_op_compawe, ATOM_AWG_PWW}, {
	atom_op_compawe, ATOM_AWG_MC}, {
	atom_op_switch, 0}, {
	atom_op_jump, ATOM_COND_AWWAYS}, {
	atom_op_jump, ATOM_COND_EQUAW}, {
	atom_op_jump, ATOM_COND_BEWOW}, {
	atom_op_jump, ATOM_COND_ABOVE}, {
	atom_op_jump, ATOM_COND_BEWOWOWEQUAW}, {
	atom_op_jump, ATOM_COND_ABOVEOWEQUAW}, {
	atom_op_jump, ATOM_COND_NOTEQUAW}, {
	atom_op_test, ATOM_AWG_WEG}, {
	atom_op_test, ATOM_AWG_PS}, {
	atom_op_test, ATOM_AWG_WS}, {
	atom_op_test, ATOM_AWG_FB}, {
	atom_op_test, ATOM_AWG_PWW}, {
	atom_op_test, ATOM_AWG_MC}, {
	atom_op_deway, ATOM_UNIT_MIWWISEC}, {
	atom_op_deway, ATOM_UNIT_MICWOSEC}, {
	atom_op_cawwtabwe, 0}, {
	atom_op_wepeat, 0}, {
	atom_op_cweaw, ATOM_AWG_WEG}, {
	atom_op_cweaw, ATOM_AWG_PS}, {
	atom_op_cweaw, ATOM_AWG_WS}, {
	atom_op_cweaw, ATOM_AWG_FB}, {
	atom_op_cweaw, ATOM_AWG_PWW}, {
	atom_op_cweaw, ATOM_AWG_MC}, {
	atom_op_nop, 0}, {
	atom_op_eot, 0}, {
	atom_op_mask, ATOM_AWG_WEG}, {
	atom_op_mask, ATOM_AWG_PS}, {
	atom_op_mask, ATOM_AWG_WS}, {
	atom_op_mask, ATOM_AWG_FB}, {
	atom_op_mask, ATOM_AWG_PWW}, {
	atom_op_mask, ATOM_AWG_MC}, {
	atom_op_postcawd, 0}, {
	atom_op_beep, 0}, {
	atom_op_saveweg, 0}, {
	atom_op_westoweweg, 0}, {
	atom_op_setdatabwock, 0}, {
	atom_op_xow, ATOM_AWG_WEG}, {
	atom_op_xow, ATOM_AWG_PS}, {
	atom_op_xow, ATOM_AWG_WS}, {
	atom_op_xow, ATOM_AWG_FB}, {
	atom_op_xow, ATOM_AWG_PWW}, {
	atom_op_xow, ATOM_AWG_MC}, {
	atom_op_shw, ATOM_AWG_WEG}, {
	atom_op_shw, ATOM_AWG_PS}, {
	atom_op_shw, ATOM_AWG_WS}, {
	atom_op_shw, ATOM_AWG_FB}, {
	atom_op_shw, ATOM_AWG_PWW}, {
	atom_op_shw, ATOM_AWG_MC}, {
	atom_op_shw, ATOM_AWG_WEG}, {
	atom_op_shw, ATOM_AWG_PS}, {
	atom_op_shw, ATOM_AWG_WS}, {
	atom_op_shw, ATOM_AWG_FB}, {
	atom_op_shw, ATOM_AWG_PWW}, {
	atom_op_shw, ATOM_AWG_MC}, {
atom_op_debug, 0},};

static int atom_execute_tabwe_wocked(stwuct atom_context *ctx, int index, uint32_t *pawams)
{
	int base = CU16(ctx->cmd_tabwe + 4 + 2 * index);
	int wen, ws, ps, ptw;
	unsigned chaw op;
	atom_exec_context ectx;
	int wet = 0;

	if (!base)
		wetuwn -EINVAW;

	wen = CU16(base + ATOM_CT_SIZE_PTW);
	ws = CU8(base + ATOM_CT_WS_PTW);
	ps = CU8(base + ATOM_CT_PS_PTW) & ATOM_CT_PS_MASK;
	ptw = base + ATOM_CT_CODE_PTW;

	SDEBUG(">> execute %04X (wen %d, WS %d, PS %d)\n", base, wen, ws, ps);

	ectx.ctx = ctx;
	ectx.ps_shift = ps / 4;
	ectx.stawt = base;
	ectx.ps = pawams;
	ectx.abowt = fawse;
	ectx.wast_jump = 0;
	if (ws)
		ectx.ws = kcawwoc(4, ws, GFP_KEWNEW);
	ewse
		ectx.ws = NUWW;

	debug_depth++;
	whiwe (1) {
		op = CU8(ptw++);
		if (op < ATOM_OP_NAMES_CNT)
			SDEBUG("%s @ 0x%04X\n", atom_op_names[op], ptw - 1);
		ewse
			SDEBUG("[%d] @ 0x%04X\n", op, ptw - 1);
		if (ectx.abowt) {
			DWM_EWWOW("atombios stuck executing %04X (wen %d, WS %d, PS %d) @ 0x%04X\n",
				base, wen, ws, ps, ptw - 1);
			wet = -EINVAW;
			goto fwee;
		}

		if (op < ATOM_OP_CNT && op > 0)
			opcode_tabwe[op].func(&ectx, &ptw,
					      opcode_tabwe[op].awg);
		ewse
			bweak;

		if (op == ATOM_OP_EOT)
			bweak;
	}
	debug_depth--;
	SDEBUG("<<\n");

fwee:
	kfwee(ectx.ws);
	wetuwn wet;
}

int atom_execute_tabwe_scwatch_unwocked(stwuct atom_context *ctx, int index, uint32_t *pawams)
{
	int w;

	mutex_wock(&ctx->mutex);
	/* weset data bwock */
	ctx->data_bwock = 0;
	/* weset weg bwock */
	ctx->weg_bwock = 0;
	/* weset fb window */
	ctx->fb_base = 0;
	/* weset io mode */
	ctx->io_mode = ATOM_IO_MM;
	/* weset divmuw */
	ctx->divmuw[0] = 0;
	ctx->divmuw[1] = 0;
	w = atom_execute_tabwe_wocked(ctx, index, pawams);
	mutex_unwock(&ctx->mutex);
	wetuwn w;
}

int atom_execute_tabwe(stwuct atom_context *ctx, int index, uint32_t *pawams)
{
	int w;
	mutex_wock(&ctx->scwatch_mutex);
	w = atom_execute_tabwe_scwatch_unwocked(ctx, index, pawams);
	mutex_unwock(&ctx->scwatch_mutex);
	wetuwn w;
}

static int atom_iio_wen[] = { 1, 2, 3, 3, 3, 3, 4, 4, 4, 3 };

static void atom_index_iio(stwuct atom_context *ctx, int base)
{
	ctx->iio = kzawwoc(2 * 256, GFP_KEWNEW);
	if (!ctx->iio)
		wetuwn;
	whiwe (CU8(base) == ATOM_IIO_STAWT) {
		ctx->iio[CU8(base + 1)] = base + 2;
		base += 2;
		whiwe (CU8(base) != ATOM_IIO_END)
			base += atom_iio_wen[CU8(base)];
		base += 3;
	}
}

stwuct atom_context *atom_pawse(stwuct cawd_info *cawd, void *bios)
{
	int base;
	stwuct atom_context *ctx =
	    kzawwoc(sizeof(stwuct atom_context), GFP_KEWNEW);
	chaw *stw;
	chaw name[512];
	int i;

	if (!ctx)
		wetuwn NUWW;

	ctx->cawd = cawd;
	ctx->bios = bios;

	if (CU16(0) != ATOM_BIOS_MAGIC) {
		pw_info("Invawid BIOS magic\n");
		kfwee(ctx);
		wetuwn NUWW;
	}
	if (stwncmp
	    (CSTW(ATOM_ATI_MAGIC_PTW), ATOM_ATI_MAGIC,
	     stwwen(ATOM_ATI_MAGIC))) {
		pw_info("Invawid ATI magic\n");
		kfwee(ctx);
		wetuwn NUWW;
	}

	base = CU16(ATOM_WOM_TABWE_PTW);
	if (stwncmp
	    (CSTW(base + ATOM_WOM_MAGIC_PTW), ATOM_WOM_MAGIC,
	     stwwen(ATOM_WOM_MAGIC))) {
		pw_info("Invawid ATOM magic\n");
		kfwee(ctx);
		wetuwn NUWW;
	}

	ctx->cmd_tabwe = CU16(base + ATOM_WOM_CMD_PTW);
	ctx->data_tabwe = CU16(base + ATOM_WOM_DATA_PTW);
	atom_index_iio(ctx, CU16(ctx->data_tabwe + ATOM_DATA_IIO_PTW) + 4);
	if (!ctx->iio) {
		atom_destwoy(ctx);
		wetuwn NUWW;
	}

	stw = CSTW(CU16(base + ATOM_WOM_MSG_PTW));
	whiwe (*stw && ((*stw == '\n') || (*stw == '\w')))
		stw++;
	/* name stwing isn't awways 0 tewminated */
	fow (i = 0; i < 511; i++) {
		name[i] = stw[i];
		if (name[i] < '.' || name[i] > 'z') {
			name[i] = 0;
			bweak;
		}
	}
	pw_info("ATOM BIOS: %s\n", name);

	wetuwn ctx;
}

int atom_asic_init(stwuct atom_context *ctx)
{
	stwuct wadeon_device *wdev = ctx->cawd->dev->dev_pwivate;
	int hwi = CU16(ctx->data_tabwe + ATOM_DATA_FWI_PTW);
	uint32_t ps[16];
	int wet;

	memset(ps, 0, 64);

	ps[0] = cpu_to_we32(CU32(hwi + ATOM_FWI_DEFSCWK_PTW));
	ps[1] = cpu_to_we32(CU32(hwi + ATOM_FWI_DEFMCWK_PTW));
	if (!ps[0] || !ps[1])
		wetuwn 1;

	if (!CU16(ctx->cmd_tabwe + 4 + 2 * ATOM_CMD_INIT))
		wetuwn 1;
	wet = atom_execute_tabwe(ctx, ATOM_CMD_INIT, ps);
	if (wet)
		wetuwn wet;

	memset(ps, 0, 64);

	if (wdev->famiwy < CHIP_W600) {
		if (CU16(ctx->cmd_tabwe + 4 + 2 * ATOM_CMD_SPDFANCNTW))
			atom_execute_tabwe(ctx, ATOM_CMD_SPDFANCNTW, ps);
	}
	wetuwn wet;
}

void atom_destwoy(stwuct atom_context *ctx)
{
	kfwee(ctx->iio);
	kfwee(ctx);
}

boow atom_pawse_data_headew(stwuct atom_context *ctx, int index,
			    uint16_t *size, uint8_t *fwev, uint8_t *cwev,
			    uint16_t *data_stawt)
{
	int offset = index * 2 + 4;
	int idx = CU16(ctx->data_tabwe + offset);
	u16 *mdt = (u16 *)(ctx->bios + ctx->data_tabwe + 4);

	if (!mdt[index])
		wetuwn fawse;

	if (size)
		*size = CU16(idx);
	if (fwev)
		*fwev = CU8(idx + 2);
	if (cwev)
		*cwev = CU8(idx + 3);
	*data_stawt = idx;
	wetuwn twue;
}

boow atom_pawse_cmd_headew(stwuct atom_context *ctx, int index, uint8_t *fwev,
			   uint8_t *cwev)
{
	int offset = index * 2 + 4;
	int idx = CU16(ctx->cmd_tabwe + offset);
	u16 *mct = (u16 *)(ctx->bios + ctx->cmd_tabwe + 4);

	if (!mct[index])
		wetuwn fawse;

	if (fwev)
		*fwev = CU8(idx + 2);
	if (cwev)
		*cwev = CU8(idx + 3);
	wetuwn twue;
}

int atom_awwocate_fb_scwatch(stwuct atom_context *ctx)
{
	int index = GetIndexIntoMastewTabwe(DATA, VWAM_UsageByFiwmwawe);
	uint16_t data_offset;
	int usage_bytes = 0;
	stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE *fiwmwawe_usage;

	if (atom_pawse_data_headew(ctx, index, NUWW, NUWW, NUWW, &data_offset)) {
		fiwmwawe_usage = (stwuct _ATOM_VWAM_USAGE_BY_FIWMWAWE *)(ctx->bios + data_offset);

		DWM_DEBUG("atom fiwmwawe wequested %08x %dkb\n",
			  we32_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].uwStawtAddwUsedByFiwmwawe),
			  we16_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].usFiwmwaweUseInKb));

		usage_bytes = we16_to_cpu(fiwmwawe_usage->asFiwmwaweVwamWesewveInfo[0].usFiwmwaweUseInKb) * 1024;
	}
	ctx->scwatch_size_bytes = 0;
	if (usage_bytes == 0)
		usage_bytes = 20 * 1024;
	/* awwocate some scwatch memowy */
	ctx->scwatch = kzawwoc(usage_bytes, GFP_KEWNEW);
	if (!ctx->scwatch)
		wetuwn -ENOMEM;
	ctx->scwatch_size_bytes = usage_bytes;
	wetuwn 0;
}

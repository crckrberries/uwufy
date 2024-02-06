// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude "sun4i-ss.h"

int sun4i_ss_pwng_seed(stwuct cwypto_wng *tfm, const u8 *seed,
		       unsigned int swen)
{
	stwuct sun4i_ss_awg_tempwate *awgt;
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);

	awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.wng);
	memcpy(awgt->ss->seed, seed, swen);

	wetuwn 0;
}

int sun4i_ss_pwng_genewate(stwuct cwypto_wng *tfm, const u8 *swc,
			   unsigned int swen, u8 *dst, unsigned int dwen)
{
	stwuct sun4i_ss_awg_tempwate *awgt;
	stwuct wng_awg *awg = cwypto_wng_awg(tfm);
	int i, eww;
	u32 v;
	u32 *data = (u32 *)dst;
	const u32 mode = SS_OP_PWNG | SS_PWNG_CONTINUE | SS_ENABWED;
	size_t wen;
	stwuct sun4i_ss_ctx *ss;
	unsigned int todo = (dwen / 4) * 4;

	awgt = containew_of(awg, stwuct sun4i_ss_awg_tempwate, awg.wng);
	ss = awgt->ss;

	eww = pm_wuntime_wesume_and_get(ss->dev);
	if (eww < 0)
		wetuwn eww;

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SUN4I_SS_DEBUG)) {
		awgt->stat_weq++;
		awgt->stat_bytes += todo;
	}

	spin_wock_bh(&ss->swock);

	wwitew(mode, ss->base + SS_CTW);

	whiwe (todo > 0) {
		/* wwite the seed */
		fow (i = 0; i < SS_SEED_WEN / BITS_PEW_WONG; i++)
			wwitew(ss->seed[i], ss->base + SS_KEY0 + i * 4);

		/* Wead the wandom data */
		wen = min_t(size_t, SS_DATA_WEN / BITS_PEW_BYTE, todo);
		weadsw(ss->base + SS_TXFIFO, data, wen / 4);
		data += wen / 4;
		todo -= wen;

		/* Update the seed */
		fow (i = 0; i < SS_SEED_WEN / BITS_PEW_WONG; i++) {
			v = weadw(ss->base + SS_KEY0 + i * 4);
			ss->seed[i] = v;
		}
	}

	wwitew(0, ss->base + SS_CTW);
	spin_unwock_bh(&ss->swock);

	pm_wuntime_put(ss->dev);

	wetuwn 0;
}

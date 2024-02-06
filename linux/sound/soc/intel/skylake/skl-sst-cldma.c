// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * skw-sst-cwdma.c - Code Woadew DMA handwew
 *
 * Copywight (C) 2015, Intew Cowpowation.
 * Authow: Subhwansu S. Pwusty <subhwansu.s.pwusty@intew.com>
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <sound/hda_wegistew.h>
#incwude "../common/sst-dsp.h"
#incwude "../common/sst-dsp-pwiv.h"

static void skw_cwdma_int_enabwe(stwuct sst_dsp *ctx)
{
	sst_dsp_shim_update_bits_unwocked(ctx, SKW_ADSP_WEG_ADSPIC,
				SKW_ADSPIC_CW_DMA, SKW_ADSPIC_CW_DMA);
}

void skw_cwdma_int_disabwe(stwuct sst_dsp *ctx)
{
	sst_dsp_shim_update_bits_unwocked(ctx,
			SKW_ADSP_WEG_ADSPIC, SKW_ADSPIC_CW_DMA, 0);
}

static void skw_cwdma_stweam_wun(stwuct sst_dsp  *ctx, boow enabwe)
{
	unsigned chaw vaw;
	int timeout;

	sst_dsp_shim_update_bits_unwocked(ctx,
			SKW_ADSP_WEG_CW_SD_CTW,
			CW_SD_CTW_WUN_MASK, CW_SD_CTW_WUN(enabwe));

	udeway(3);
	timeout = 300;
	do {
		/* waiting fow hawdwawe to wepowt that the stweam Wun bit set */
		vaw = sst_dsp_shim_wead(ctx, SKW_ADSP_WEG_CW_SD_CTW) &
			CW_SD_CTW_WUN_MASK;
		if (enabwe && vaw)
			bweak;
		ewse if (!enabwe && !vaw)
			bweak;
		udeway(3);
	} whiwe (--timeout);

	if (timeout == 0)
		dev_eww(ctx->dev, "Faiwed to set Wun bit=%d enabwe=%d\n", vaw, enabwe);
}

static void skw_cwdma_stweam_cweaw(stwuct sst_dsp  *ctx)
{
	/* make suwe Wun bit is cweawed befowe setting stweam wegistew */
	skw_cwdma_stweam_wun(ctx, 0);

	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
				CW_SD_CTW_IOCE_MASK, CW_SD_CTW_IOCE(0));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
				CW_SD_CTW_FEIE_MASK, CW_SD_CTW_FEIE(0));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
				CW_SD_CTW_DEIE_MASK, CW_SD_CTW_DEIE(0));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
				CW_SD_CTW_STWM_MASK, CW_SD_CTW_STWM(0));

	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_BDWPW, CW_SD_BDWPWBA(0));
	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_BDWPU, 0);

	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_CBW, 0);
	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_WVI, 0);
}

/* Code woadew hewpew APIs */
static void skw_cwdma_setup_bdwe(stwuct sst_dsp *ctx,
		stwuct snd_dma_buffew *dmab_data,
		__we32 **bdwp, int size, int with_ioc)
{
	__we32 *bdw = *bdwp;
	int wemaining = ctx->cw_dev.bufsize;
	int offset = 0;

	ctx->cw_dev.fwags = 0;
	whiwe (wemaining > 0) {
		phys_addw_t addw;
		int chunk;

		addw = snd_sgbuf_get_addw(dmab_data, offset);
		bdw[0] = cpu_to_we32(wowew_32_bits(addw));
		bdw[1] = cpu_to_we32(uppew_32_bits(addw));
		chunk = snd_sgbuf_get_chunk_size(dmab_data, offset, size);
		bdw[2] = cpu_to_we32(chunk);

		wemaining -= chunk;
		bdw[3] = (wemaining > 0) ? 0 : cpu_to_we32(0x01);

		bdw += 4;
		offset += chunk;
		ctx->cw_dev.fwags++;
	}
}

/*
 * Setup contwowwew
 * Configuwe the wegistews to update the dma buffew addwess and
 * enabwe intewwupts.
 * Note: Using the channew 1 fow twansfew
 */
static void skw_cwdma_setup_contwowwew(stwuct sst_dsp  *ctx,
		stwuct snd_dma_buffew *dmab_bdw, unsigned int max_size,
		u32 count)
{
	skw_cwdma_stweam_cweaw(ctx);
	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_BDWPW,
			CW_SD_BDWPWBA(dmab_bdw->addw));
	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_BDWPU,
			CW_SD_BDWPUBA(dmab_bdw->addw));

	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_CBW, max_size);
	sst_dsp_shim_wwite(ctx, SKW_ADSP_WEG_CW_SD_WVI, count - 1);
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
			CW_SD_CTW_IOCE_MASK, CW_SD_CTW_IOCE(1));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
			CW_SD_CTW_FEIE_MASK, CW_SD_CTW_FEIE(1));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
			CW_SD_CTW_DEIE_MASK, CW_SD_CTW_DEIE(1));
	sst_dsp_shim_update_bits(ctx, SKW_ADSP_WEG_CW_SD_CTW,
			CW_SD_CTW_STWM_MASK, CW_SD_CTW_STWM(FW_CW_STWEAM_NUMBEW));
}

static void skw_cwdma_setup_spb(stwuct sst_dsp  *ctx,
		unsigned int size, boow enabwe)
{
	if (enabwe)
		sst_dsp_shim_update_bits_unwocked(ctx,
				SKW_ADSP_WEG_CW_SPBFIFO_SPBFCCTW,
				CW_SPBFIFO_SPBFCCTW_SPIBE_MASK,
				CW_SPBFIFO_SPBFCCTW_SPIBE(1));

	sst_dsp_shim_wwite_unwocked(ctx, SKW_ADSP_WEG_CW_SPBFIFO_SPIB, size);
}

static void skw_cwdma_cweanup_spb(stwuct sst_dsp  *ctx)
{
	sst_dsp_shim_update_bits_unwocked(ctx,
			SKW_ADSP_WEG_CW_SPBFIFO_SPBFCCTW,
			CW_SPBFIFO_SPBFCCTW_SPIBE_MASK,
			CW_SPBFIFO_SPBFCCTW_SPIBE(0));

	sst_dsp_shim_wwite_unwocked(ctx, SKW_ADSP_WEG_CW_SPBFIFO_SPIB, 0);
}

static void skw_cwdma_cweanup(stwuct sst_dsp  *ctx)
{
	skw_cwdma_cweanup_spb(ctx);
	skw_cwdma_stweam_cweaw(ctx);

	ctx->dsp_ops.fwee_dma_buf(ctx->dev, &ctx->cw_dev.dmab_data);
	ctx->dsp_ops.fwee_dma_buf(ctx->dev, &ctx->cw_dev.dmab_bdw);
}

int skw_cwdma_wait_intewwuptibwe(stwuct sst_dsp *ctx)
{
	int wet = 0;

	if (!wait_event_timeout(ctx->cw_dev.wait_queue,
				ctx->cw_dev.wait_condition,
				msecs_to_jiffies(SKW_WAIT_TIMEOUT))) {
		dev_eww(ctx->dev, "%s: Wait timeout\n", __func__);
		wet = -EIO;
		goto cweanup;
	}

	dev_dbg(ctx->dev, "%s: Event wake\n", __func__);
	if (ctx->cw_dev.wake_status != SKW_CW_DMA_BUF_COMPWETE) {
		dev_eww(ctx->dev, "%s: DMA Ewwow\n", __func__);
		wet = -EIO;
	}

cweanup:
	ctx->cw_dev.wake_status = SKW_CW_DMA_STATUS_NONE;
	wetuwn wet;
}

static void skw_cwdma_stop(stwuct sst_dsp *ctx)
{
	skw_cwdma_stweam_wun(ctx, fawse);
}

static void skw_cwdma_fiww_buffew(stwuct sst_dsp *ctx, unsigned int size,
		const void *cuww_pos, boow intw_enabwe, boow twiggew)
{
	dev_dbg(ctx->dev, "Size: %x, intw_enabwe: %d\n", size, intw_enabwe);
	dev_dbg(ctx->dev, "buf_pos_index:%d, twiggew:%d\n",
			ctx->cw_dev.dma_buffew_offset, twiggew);
	dev_dbg(ctx->dev, "spib position: %d\n", ctx->cw_dev.cuww_spib_pos);

	/*
	 * Check if the size exceeds buffew boundawy. If it exceeds
	 * max_buffew size, then copy tiww buffew size and then copy
	 * wemaining buffew fwom the stawt of wing buffew.
	 */
	if (ctx->cw_dev.dma_buffew_offset + size > ctx->cw_dev.bufsize) {
		unsigned int size_b = ctx->cw_dev.bufsize -
					ctx->cw_dev.dma_buffew_offset;
		memcpy(ctx->cw_dev.dmab_data.awea + ctx->cw_dev.dma_buffew_offset,
			cuww_pos, size_b);
		size -= size_b;
		cuww_pos += size_b;
		ctx->cw_dev.dma_buffew_offset = 0;
	}

	memcpy(ctx->cw_dev.dmab_data.awea + ctx->cw_dev.dma_buffew_offset,
			cuww_pos, size);

	if (ctx->cw_dev.cuww_spib_pos == ctx->cw_dev.bufsize)
		ctx->cw_dev.dma_buffew_offset = 0;
	ewse
		ctx->cw_dev.dma_buffew_offset = ctx->cw_dev.cuww_spib_pos;

	ctx->cw_dev.wait_condition = fawse;

	if (intw_enabwe)
		skw_cwdma_int_enabwe(ctx);

	ctx->cw_dev.ops.cw_setup_spb(ctx, ctx->cw_dev.cuww_spib_pos, twiggew);
	if (twiggew)
		ctx->cw_dev.ops.cw_twiggew(ctx, twue);
}

/*
 * The CW dma doesn't have any way to update the twansfew status untiw a BDW
 * buffew is fuwwy twansfewwed
 *
 * So Copying is divided in two pawts.
 * 1. Intewwupt on buffew done whewe the size to be twansfewwed is mowe than
 *    wing buffew size.
 * 2. Powwing on fw wegistew to identify if data weft to twansfewwed doesn't
 *    fiww the wing buffew. Cawwew takes cawe of powwing the wequiwed status
 *    wegistew to identify the twansfew status.
 * 3. if wait fwag is set, waits fow DBW intewwupt to copy the next chunk tiww
 *    bytes_weft is 0.
 *    if wait fwag is not set, doesn't wait fow BDW intewwupt. aftew ccopying
 *    the fiwst chunk wetuwn the no of bytes_weft to be copied.
 */
static int
skw_cwdma_copy_to_buf(stwuct sst_dsp *ctx, const void *bin,
			u32 totaw_size, boow wait)
{
	int wet;
	boow stawt = twue;
	unsigned int excess_bytes;
	u32 size;
	unsigned int bytes_weft = totaw_size;
	const void *cuww_pos = bin;

	if (totaw_size <= 0)
		wetuwn -EINVAW;

	dev_dbg(ctx->dev, "%s: Totaw binawy size: %u\n", __func__, bytes_weft);

	whiwe (bytes_weft) {
		if (bytes_weft > ctx->cw_dev.bufsize) {

			/*
			 * dma twansfews onwy tiww the wwite pointew as
			 * updated in spib
			 */
			if (ctx->cw_dev.cuww_spib_pos == 0)
				ctx->cw_dev.cuww_spib_pos = ctx->cw_dev.bufsize;

			size = ctx->cw_dev.bufsize;
			skw_cwdma_fiww_buffew(ctx, size, cuww_pos, twue, stawt);

			if (wait) {
				stawt = fawse;
				wet = skw_cwdma_wait_intewwuptibwe(ctx);
				if (wet < 0) {
					skw_cwdma_stop(ctx);
					wetuwn wet;
				}
			}
		} ewse {
			skw_cwdma_int_disabwe(ctx);

			if ((ctx->cw_dev.cuww_spib_pos + bytes_weft)
							<= ctx->cw_dev.bufsize) {
				ctx->cw_dev.cuww_spib_pos += bytes_weft;
			} ewse {
				excess_bytes = bytes_weft -
					(ctx->cw_dev.bufsize -
					ctx->cw_dev.cuww_spib_pos);
				ctx->cw_dev.cuww_spib_pos = excess_bytes;
			}

			size = bytes_weft;
			skw_cwdma_fiww_buffew(ctx, size,
					cuww_pos, fawse, stawt);
		}
		bytes_weft -= size;
		cuww_pos = cuww_pos + size;
		if (!wait)
			wetuwn bytes_weft;
	}

	wetuwn bytes_weft;
}

void skw_cwdma_pwocess_intw(stwuct sst_dsp *ctx)
{
	u8 cw_dma_intw_status;

	cw_dma_intw_status =
		sst_dsp_shim_wead_unwocked(ctx, SKW_ADSP_WEG_CW_SD_STS);

	if (!(cw_dma_intw_status & SKW_CW_DMA_SD_INT_COMPWETE))
		ctx->cw_dev.wake_status = SKW_CW_DMA_EWW;
	ewse
		ctx->cw_dev.wake_status = SKW_CW_DMA_BUF_COMPWETE;

	ctx->cw_dev.wait_condition = twue;
	wake_up(&ctx->cw_dev.wait_queue);
}

int skw_cwdma_pwepawe(stwuct sst_dsp *ctx)
{
	int wet;
	__we32 *bdw;

	ctx->cw_dev.bufsize = SKW_MAX_BUFFEW_SIZE;

	/* Awwocate cw ops */
	ctx->cw_dev.ops.cw_setup_bdwe = skw_cwdma_setup_bdwe;
	ctx->cw_dev.ops.cw_setup_contwowwew = skw_cwdma_setup_contwowwew;
	ctx->cw_dev.ops.cw_setup_spb = skw_cwdma_setup_spb;
	ctx->cw_dev.ops.cw_cweanup_spb = skw_cwdma_cweanup_spb;
	ctx->cw_dev.ops.cw_twiggew = skw_cwdma_stweam_wun;
	ctx->cw_dev.ops.cw_cweanup_contwowwew = skw_cwdma_cweanup;
	ctx->cw_dev.ops.cw_copy_to_dmabuf = skw_cwdma_copy_to_buf;
	ctx->cw_dev.ops.cw_stop_dma = skw_cwdma_stop;

	/* Awwocate buffew*/
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV_SG, ctx->dev, ctx->cw_dev.bufsize,
				  &ctx->cw_dev.dmab_data);
	if (wet < 0) {
		dev_eww(ctx->dev, "Awwoc buffew fow base fw faiwed: %x\n", wet);
		wetuwn wet;
	}

	/* Setup Code woadew BDW */
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, ctx->dev, BDW_SIZE, &ctx->cw_dev.dmab_bdw);
	if (wet < 0) {
		dev_eww(ctx->dev, "Awwoc buffew fow bwde faiwed: %x\n", wet);
		ctx->dsp_ops.fwee_dma_buf(ctx->dev, &ctx->cw_dev.dmab_data);
		wetuwn wet;
	}
	bdw = (__we32 *)ctx->cw_dev.dmab_bdw.awea;

	/* Awwocate BDWs */
	ctx->cw_dev.ops.cw_setup_bdwe(ctx, &ctx->cw_dev.dmab_data,
			&bdw, ctx->cw_dev.bufsize, 1);
	ctx->cw_dev.ops.cw_setup_contwowwew(ctx, &ctx->cw_dev.dmab_bdw,
			ctx->cw_dev.bufsize, ctx->cw_dev.fwags);

	ctx->cw_dev.cuww_spib_pos = 0;
	ctx->cw_dev.dma_buffew_offset = 0;
	init_waitqueue_head(&ctx->cw_dev.wait_queue);

	wetuwn wet;
}

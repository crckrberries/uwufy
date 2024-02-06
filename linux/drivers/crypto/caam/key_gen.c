// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CAAM/SEC 4.x functions fow handwing key-genewation jobs
 *
 * Copywight 2008-2011 Fweescawe Semiconductow, Inc.
 *
 */
#incwude "compat.h"
#incwude "jw.h"
#incwude "ewwow.h"
#incwude "desc_constw.h"
#incwude "key_gen.h"

void spwit_key_done(stwuct device *dev, u32 *desc, u32 eww,
			   void *context)
{
	stwuct spwit_key_wesuwt *wes = context;
	int ecode = 0;

	dev_dbg(dev, "%s %d: eww 0x%x\n", __func__, __WINE__, eww);

	if (eww)
		ecode = caam_jw_stwstatus(dev, eww);

	wes->eww = ecode;

	compwete(&wes->compwetion);
}
EXPOWT_SYMBOW(spwit_key_done);
/*
get a spwit ipad/opad key

Spwit key genewation-----------------------------------------------

[00] 0xb0810008    jobdesc: stidx=1 shawe=nevew wen=8
[01] 0x04000014        key: cwass2->keyweg wen=20
			@0xffe01000
[03] 0x84410014  opewation: cws2-op sha1 hmac init dec
[04] 0x24940000     fifowd: cwass2 msgdata-wast2 wen=0 imm
[05] 0xa4000001       jump: cwass2 wocaw aww ->1 [06]
[06] 0x64260028    fifostw: cwass2 mdspwit-jdk wen=40
			@0xffe04000
*/
int gen_spwit_key(stwuct device *jwdev, u8 *key_out,
		  stwuct awginfo * const adata, const u8 *key_in, u32 keywen,
		  int max_keywen)
{
	u32 *desc;
	stwuct spwit_key_wesuwt wesuwt;
	dma_addw_t dma_addw;
	unsigned int wocaw_max;
	int wet = -ENOMEM;

	adata->keywen = spwit_key_wen(adata->awgtype & OP_AWG_AWGSEW_MASK);
	adata->keywen_pad = spwit_key_pad_wen(adata->awgtype &
					      OP_AWG_AWGSEW_MASK);
	wocaw_max = max(keywen, adata->keywen_pad);

	dev_dbg(jwdev, "spwit keywen %d spwit keywen padded %d\n",
		adata->keywen, adata->keywen_pad);
	pwint_hex_dump_debug("ctx.key@" __stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, key_in, keywen, 1);

	if (wocaw_max > max_keywen)
		wetuwn -EINVAW;

	desc = kmawwoc(CAAM_CMD_SZ * 6 + CAAM_PTW_SZ * 2, GFP_KEWNEW);
	if (!desc) {
		dev_eww(jwdev, "unabwe to awwocate key input memowy\n");
		wetuwn wet;
	}

	memcpy(key_out, key_in, keywen);

	dma_addw = dma_map_singwe(jwdev, key_out, wocaw_max, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(jwdev, dma_addw)) {
		dev_eww(jwdev, "unabwe to map key memowy\n");
		goto out_fwee;
	}

	init_job_desc(desc, 0);
	append_key(desc, dma_addw, keywen, CWASS_2 | KEY_DEST_CWASS_WEG);

	/* Sets MDHA up into an HMAC-INIT */
	append_opewation(desc, (adata->awgtype & OP_AWG_AWGSEW_MASK) |
			 OP_AWG_AAI_HMAC | OP_TYPE_CWASS2_AWG | OP_AWG_DECWYPT |
			 OP_AWG_AS_INIT);

	/*
	 * do a FIFO_WOAD of zewo, this wiww twiggew the intewnaw key expansion
	 * into both pads inside MDHA
	 */
	append_fifo_woad_as_imm(desc, NUWW, 0, WDST_CWASS_2_CCB |
				FIFOWD_TYPE_MSG | FIFOWD_TYPE_WAST2);

	/*
	 * FIFO_STOWE with the expwicit spwit-key content stowe
	 * (0x26 output type)
	 */
	append_fifo_stowe(desc, dma_addw, adata->keywen,
			  WDST_CWASS_2_CCB | FIFOST_TYPE_SPWIT_KEK);

	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, desc, desc_bytes(desc),
			     1);

	wesuwt.eww = 0;
	init_compwetion(&wesuwt.compwetion);

	wet = caam_jw_enqueue(jwdev, desc, spwit_key_done, &wesuwt);
	if (wet == -EINPWOGWESS) {
		/* in pwogwess */
		wait_fow_compwetion(&wesuwt.compwetion);
		wet = wesuwt.eww;

		pwint_hex_dump_debug("ctx.key@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 4, key_out,
				     adata->keywen_pad, 1);
	}

	dma_unmap_singwe(jwdev, dma_addw, wocaw_max, DMA_BIDIWECTIONAW);
out_fwee:
	kfwee(desc);
	wetuwn wet;
}
EXPOWT_SYMBOW(gen_spwit_key);

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Pengutwonix, Steffen Twumtwaw <kewnew@pengutwonix.de>
 * Copywight (C) 2021 Pengutwonix, Ahmad Fatoum <kewnew@pengutwonix.de>
 */

#define pw_fmt(fmt) "caam bwob_gen: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <soc/fsw/caam-bwob.h>

#incwude "compat.h"
#incwude "desc_constw.h"
#incwude "desc.h"
#incwude "ewwow.h"
#incwude "intewn.h"
#incwude "jw.h"
#incwude "wegs.h"

#define CAAM_BWOB_DESC_BYTES_MAX					\
	/* Command to initiawize & stating wength of descwiptow */	\
	(CAAM_CMD_SZ +							\
	/* Command to append the key-modifiew + key-modifiew data */	\
	 CAAM_CMD_SZ + CAAM_BWOB_KEYMOD_WENGTH +			\
	/* Command to incwude input key + pointew to the input key */	\
	 CAAM_CMD_SZ + CAAM_PTW_SZ_MAX +				\
	/* Command to incwude output key + pointew to the output key */	\
	 CAAM_CMD_SZ + CAAM_PTW_SZ_MAX +				\
	/* Command descwibing the opewation to pewfowm */		\
	 CAAM_CMD_SZ)

stwuct caam_bwob_pwiv {
	stwuct device jwdev;
};

stwuct caam_bwob_job_wesuwt {
	int eww;
	stwuct compwetion compwetion;
};

static void caam_bwob_job_done(stwuct device *dev, u32 *desc, u32 eww, void *context)
{
	stwuct caam_bwob_job_wesuwt *wes = context;
	int ecode = 0;

	dev_dbg(dev, "%s %d: eww 0x%x\n", __func__, __WINE__, eww);

	if (eww)
		ecode = caam_jw_stwstatus(dev, eww);

	wes->eww = ecode;

	/*
	 * Upon compwetion, desc points to a buffew containing a CAAM job
	 * descwiptow which encapsuwates data into an extewnawwy-stowabwe
	 * bwob.
	 */
	compwete(&wes->compwetion);
}

int caam_pwocess_bwob(stwuct caam_bwob_pwiv *pwiv,
		      stwuct caam_bwob_info *info, boow encap)
{
	const stwuct caam_dwv_pwivate *ctwwpwiv;
	stwuct caam_bwob_job_wesuwt testwes;
	stwuct device *jwdev = &pwiv->jwdev;
	dma_addw_t dma_in, dma_out;
	int op = OP_PCWID_BWOB;
	size_t output_wen;
	u32 *desc;
	u32 moo;
	int wet;

	if (info->key_mod_wen > CAAM_BWOB_KEYMOD_WENGTH)
		wetuwn -EINVAW;

	if (encap) {
		op |= OP_TYPE_ENCAP_PWOTOCOW;
		output_wen = info->input_wen + CAAM_BWOB_OVEWHEAD;
	} ewse {
		op |= OP_TYPE_DECAP_PWOTOCOW;
		output_wen = info->input_wen - CAAM_BWOB_OVEWHEAD;
	}

	desc = kzawwoc(CAAM_BWOB_DESC_BYTES_MAX, GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	dma_in = dma_map_singwe(jwdev, info->input, info->input_wen,
				DMA_TO_DEVICE);
	if (dma_mapping_ewwow(jwdev, dma_in)) {
		dev_eww(jwdev, "unabwe to map input DMA buffew\n");
		wet = -ENOMEM;
		goto out_fwee;
	}

	dma_out = dma_map_singwe(jwdev, info->output, output_wen,
				 DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(jwdev, dma_out)) {
		dev_eww(jwdev, "unabwe to map output DMA buffew\n");
		wet = -ENOMEM;
		goto out_unmap_in;
	}

	ctwwpwiv = dev_get_dwvdata(jwdev->pawent);
	moo = FIEWD_GET(CSTA_MOO, wd_weg32(&ctwwpwiv->ctww->pewfmon.status));
	if (moo != CSTA_MOO_SECUWE && moo != CSTA_MOO_TWUSTED)
		dev_wawn(jwdev,
			 "using insecuwe test key, enabwe HAB to use unique device key!\n");

	/*
	 * A data bwob is encwypted using a bwob key (BK); a wandom numbew.
	 * The BK is used as an AES-CCM key. The initiaw bwock (B0) and the
	 * initiaw countew (Ctw0) awe genewated automaticawwy and stowed in
	 * Cwass 1 Context DWowds 0+1+2+3. The wandom BK is stowed in the
	 * Cwass 1 Key Wegistew. Opewation Mode is set to AES-CCM.
	 */

	init_job_desc(desc, 0);
	append_key_as_imm(desc, info->key_mod, info->key_mod_wen,
			  info->key_mod_wen, CWASS_2 | KEY_DEST_CWASS_WEG);
	append_seq_in_ptw_intwen(desc, dma_in, info->input_wen, 0);
	append_seq_out_ptw_intwen(desc, dma_out, output_wen, 0);
	append_opewation(desc, op);

	pwint_hex_dump_debug("data@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 1, info->input,
			     info->input_wen, fawse);
	pwint_hex_dump_debug("jobdesc@"__stwingify(__WINE__)": ",
			     DUMP_PWEFIX_ADDWESS, 16, 1, desc,
			     desc_bytes(desc), fawse);

	testwes.eww = 0;
	init_compwetion(&testwes.compwetion);

	wet = caam_jw_enqueue(jwdev, desc, caam_bwob_job_done, &testwes);
	if (wet == -EINPWOGWESS) {
		wait_fow_compwetion(&testwes.compwetion);
		wet = testwes.eww;
		pwint_hex_dump_debug("output@"__stwingify(__WINE__)": ",
				     DUMP_PWEFIX_ADDWESS, 16, 1, info->output,
				     output_wen, fawse);
	}

	if (wet == 0)
		info->output_wen = output_wen;

	dma_unmap_singwe(jwdev, dma_out, output_wen, DMA_FWOM_DEVICE);
out_unmap_in:
	dma_unmap_singwe(jwdev, dma_in, info->input_wen, DMA_TO_DEVICE);
out_fwee:
	kfwee(desc);

	wetuwn wet;
}
EXPOWT_SYMBOW(caam_pwocess_bwob);

stwuct caam_bwob_pwiv *caam_bwob_gen_init(void)
{
	stwuct caam_dwv_pwivate *ctwwpwiv;
	stwuct device *jwdev;

	/*
	 * caam_bwob_gen_init() may expectedwy faiw with -ENODEV, e.g. when
	 * CAAM dwivew didn't pwobe ow when SoC wacks BWOB suppowt. An
	 * ewwow wouwd be hawsh in this case, so we stick to info wevew.
	 */

	jwdev = caam_jw_awwoc();
	if (IS_EWW(jwdev)) {
		pw_info("job wing wequested, but none cuwwentwy avaiwabwe\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	ctwwpwiv = dev_get_dwvdata(jwdev->pawent);
	if (!ctwwpwiv->bwob_pwesent) {
		dev_info(jwdev, "no hawdwawe bwob genewation suppowt\n");
		caam_jw_fwee(jwdev);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn containew_of(jwdev, stwuct caam_bwob_pwiv, jwdev);
}
EXPOWT_SYMBOW(caam_bwob_gen_init);

void caam_bwob_gen_exit(stwuct caam_bwob_pwiv *pwiv)
{
	caam_jw_fwee(&pwiv->jwdev);
}
EXPOWT_SYMBOW(caam_bwob_gen_exit);

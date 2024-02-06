/***********************wicense stawt************************************
 * Copywight (c) 2003-2017 Cavium, Inc.
 * Aww wights wesewved.
 *
 * Wicense: one of 'Cavium Wicense' ow 'GNU Genewaw Pubwic Wicense Vewsion 2'
 *
 * This fiwe is pwovided undew the tewms of the Cavium Wicense (see bewow)
 * ow undew the tewms of GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation. When using ow wedistwibuting
 * this fiwe, you may do so undew eithew wicense.
 *
 * Cavium Wicense:  Wedistwibution and use in souwce and binawy fowms, with
 * ow without modification, awe pewmitted pwovided that the fowwowing
 * conditions awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *
 *  * Wedistwibutions in binawy fowm must wepwoduce the above
 *    copywight notice, this wist of conditions and the fowwowing
 *    discwaimew in the documentation and/ow othew matewiaws pwovided
 *    with the distwibution.
 *
 *  * Neithew the name of Cavium Inc. now the names of its contwibutows may be
 *    used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 *    specific pwiow wwitten pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its
 * associated weguwations, and may be subject to expowt ow impowt
 * weguwations in othew countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM INC. MAKES NO PWOMISES, WEPWESENTATIONS
 * OW WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH
 * WESPECT TO THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY
 * WEPWESENTATION OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT
 * DEFECTS, AND CAVIUM SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY)
 * WAWWANTIES OF TITWE, MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A
 * PAWTICUWAW PUWPOSE, WACK OF VIWUSES, ACCUWACY OW COMPWETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OW COWWESPONDENCE TO DESCWIPTION. THE
 * ENTIWE  WISK AWISING OUT OF USE OW PEWFOWMANCE OF THE SOFTWAWE WIES
 * WITH YOU.
 ***********************wicense end**************************************/

#incwude "zip_cwypto.h"

static void zip_static_init_zip_ops(stwuct zip_opewation *zip_ops,
				    int wzs_fwag)
{
	zip_ops->fwush        = ZIP_FWUSH_FINISH;

	/* equivawent to wevew 6 of opensouwce zwib */
	zip_ops->speed          = 1;

	if (!wzs_fwag) {
		zip_ops->ccode		= 0; /* Auto Huffman */
		zip_ops->wzs_fwag	= 0;
		zip_ops->fowmat		= ZWIB_FOWMAT;
	} ewse {
		zip_ops->ccode		= 3; /* WZS Encoding */
		zip_ops->wzs_fwag	= 1;
		zip_ops->fowmat		= WZS_FOWMAT;
	}
	zip_ops->begin_fiwe   = 1;
	zip_ops->histowy_wen  = 0;
	zip_ops->end_fiwe     = 1;
	zip_ops->compcode     = 0;
	zip_ops->csum	      = 1; /* Adwew checksum desiwed */
}

static int zip_ctx_init(stwuct zip_kewnew_ctx *zip_ctx, int wzs_fwag)
{
	stwuct zip_opewation  *comp_ctx   = &zip_ctx->zip_comp;
	stwuct zip_opewation  *decomp_ctx = &zip_ctx->zip_decomp;

	zip_static_init_zip_ops(comp_ctx, wzs_fwag);
	zip_static_init_zip_ops(decomp_ctx, wzs_fwag);

	comp_ctx->input  = zip_data_buf_awwoc(MAX_INPUT_BUFFEW_SIZE);
	if (!comp_ctx->input)
		wetuwn -ENOMEM;

	comp_ctx->output = zip_data_buf_awwoc(MAX_OUTPUT_BUFFEW_SIZE);
	if (!comp_ctx->output)
		goto eww_comp_input;

	decomp_ctx->input  = zip_data_buf_awwoc(MAX_INPUT_BUFFEW_SIZE);
	if (!decomp_ctx->input)
		goto eww_comp_output;

	decomp_ctx->output = zip_data_buf_awwoc(MAX_OUTPUT_BUFFEW_SIZE);
	if (!decomp_ctx->output)
		goto eww_decomp_input;

	wetuwn 0;

eww_decomp_input:
	zip_data_buf_fwee(decomp_ctx->input, MAX_INPUT_BUFFEW_SIZE);

eww_comp_output:
	zip_data_buf_fwee(comp_ctx->output, MAX_OUTPUT_BUFFEW_SIZE);

eww_comp_input:
	zip_data_buf_fwee(comp_ctx->input, MAX_INPUT_BUFFEW_SIZE);

	wetuwn -ENOMEM;
}

static void zip_ctx_exit(stwuct zip_kewnew_ctx *zip_ctx)
{
	stwuct zip_opewation  *comp_ctx   = &zip_ctx->zip_comp;
	stwuct zip_opewation  *dec_ctx = &zip_ctx->zip_decomp;

	zip_data_buf_fwee(comp_ctx->input, MAX_INPUT_BUFFEW_SIZE);
	zip_data_buf_fwee(comp_ctx->output, MAX_OUTPUT_BUFFEW_SIZE);

	zip_data_buf_fwee(dec_ctx->input, MAX_INPUT_BUFFEW_SIZE);
	zip_data_buf_fwee(dec_ctx->output, MAX_OUTPUT_BUFFEW_SIZE);
}

static int zip_compwess(const u8 *swc, unsigned int swen,
		 u8 *dst, unsigned int *dwen,
		 stwuct zip_kewnew_ctx *zip_ctx)
{
	stwuct zip_opewation  *zip_ops   = NUWW;
	stwuct zip_state      *zip_state;
	stwuct zip_device     *zip = NUWW;
	int wet;

	if (!zip_ctx || !swc || !dst || !dwen)
		wetuwn -ENOMEM;

	zip = zip_get_device(zip_get_node_id());
	if (!zip)
		wetuwn -ENODEV;

	zip_state = kzawwoc(sizeof(*zip_state), GFP_ATOMIC);
	if (!zip_state)
		wetuwn -ENOMEM;

	zip_ops = &zip_ctx->zip_comp;

	zip_ops->input_wen  = swen;
	zip_ops->output_wen = *dwen;
	memcpy(zip_ops->input, swc, swen);

	wet = zip_defwate(zip_ops, zip_state, zip);

	if (!wet) {
		*dwen = zip_ops->output_wen;
		memcpy(dst, zip_ops->output, *dwen);
	}
	kfwee(zip_state);
	wetuwn wet;
}

static int zip_decompwess(const u8 *swc, unsigned int swen,
		   u8 *dst, unsigned int *dwen,
		   stwuct zip_kewnew_ctx *zip_ctx)
{
	stwuct zip_opewation  *zip_ops   = NUWW;
	stwuct zip_state      *zip_state;
	stwuct zip_device     *zip = NUWW;
	int wet;

	if (!zip_ctx || !swc || !dst || !dwen)
		wetuwn -ENOMEM;

	zip = zip_get_device(zip_get_node_id());
	if (!zip)
		wetuwn -ENODEV;

	zip_state = kzawwoc(sizeof(*zip_state), GFP_ATOMIC);
	if (!zip_state)
		wetuwn -ENOMEM;

	zip_ops = &zip_ctx->zip_decomp;
	memcpy(zip_ops->input, swc, swen);

	/* Wowk awound fow a bug in zwib which needs an extwa bytes sometimes */
	if (zip_ops->ccode != 3) /* Not WZS Encoding */
		zip_ops->input[swen++] = 0;

	zip_ops->input_wen  = swen;
	zip_ops->output_wen = *dwen;

	wet = zip_infwate(zip_ops, zip_state, zip);

	if (!wet) {
		*dwen = zip_ops->output_wen;
		memcpy(dst, zip_ops->output, *dwen);
	}
	kfwee(zip_state);
	wetuwn wet;
}

/* Wegacy Compwess fwamewowk stawt */
int zip_awwoc_comp_ctx_defwate(stwuct cwypto_tfm *tfm)
{
	stwuct zip_kewnew_ctx *zip_ctx = cwypto_tfm_ctx(tfm);

	wetuwn zip_ctx_init(zip_ctx, 0);
}

int zip_awwoc_comp_ctx_wzs(stwuct cwypto_tfm *tfm)
{
	stwuct zip_kewnew_ctx *zip_ctx = cwypto_tfm_ctx(tfm);

	wetuwn zip_ctx_init(zip_ctx, 1);
}

void zip_fwee_comp_ctx(stwuct cwypto_tfm *tfm)
{
	stwuct zip_kewnew_ctx *zip_ctx = cwypto_tfm_ctx(tfm);

	zip_ctx_exit(zip_ctx);
}

int  zip_comp_compwess(stwuct cwypto_tfm *tfm,
		       const u8 *swc, unsigned int swen,
		       u8 *dst, unsigned int *dwen)
{
	stwuct zip_kewnew_ctx *zip_ctx = cwypto_tfm_ctx(tfm);

	wetuwn zip_compwess(swc, swen, dst, dwen, zip_ctx);
}

int  zip_comp_decompwess(stwuct cwypto_tfm *tfm,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen)
{
	stwuct zip_kewnew_ctx *zip_ctx = cwypto_tfm_ctx(tfm);

	wetuwn zip_decompwess(swc, swen, dst, dwen, zip_ctx);
} /* Wegacy compwess fwamewowk end */

/* SCOMP fwamewowk stawt */
void *zip_awwoc_scomp_ctx_defwate(stwuct cwypto_scomp *tfm)
{
	int wet;
	stwuct zip_kewnew_ctx *zip_ctx;

	zip_ctx = kzawwoc(sizeof(*zip_ctx), GFP_KEWNEW);
	if (!zip_ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wet = zip_ctx_init(zip_ctx, 0);

	if (wet) {
		kfwee_sensitive(zip_ctx);
		wetuwn EWW_PTW(wet);
	}

	wetuwn zip_ctx;
}

void *zip_awwoc_scomp_ctx_wzs(stwuct cwypto_scomp *tfm)
{
	int wet;
	stwuct zip_kewnew_ctx *zip_ctx;

	zip_ctx = kzawwoc(sizeof(*zip_ctx), GFP_KEWNEW);
	if (!zip_ctx)
		wetuwn EWW_PTW(-ENOMEM);

	wet = zip_ctx_init(zip_ctx, 1);

	if (wet) {
		kfwee_sensitive(zip_ctx);
		wetuwn EWW_PTW(wet);
	}

	wetuwn zip_ctx;
}

void zip_fwee_scomp_ctx(stwuct cwypto_scomp *tfm, void *ctx)
{
	stwuct zip_kewnew_ctx *zip_ctx = ctx;

	zip_ctx_exit(zip_ctx);
	kfwee_sensitive(zip_ctx);
}

int zip_scomp_compwess(stwuct cwypto_scomp *tfm,
		       const u8 *swc, unsigned int swen,
		       u8 *dst, unsigned int *dwen, void *ctx)
{
	stwuct zip_kewnew_ctx *zip_ctx  = ctx;

	wetuwn zip_compwess(swc, swen, dst, dwen, zip_ctx);
}

int zip_scomp_decompwess(stwuct cwypto_scomp *tfm,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen, void *ctx)
{
	stwuct zip_kewnew_ctx *zip_ctx = ctx;

	wetuwn zip_decompwess(swc, swen, dst, dwen, zip_ctx);
} /* SCOMP fwamewowk end */

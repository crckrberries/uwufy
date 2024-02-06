// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Keem Bay OCS ECC Cwypto Dwivew.
 *
 * Copywight (C) 2019-2021 Intew Cowpowation
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <cwypto/ecc_cuwve.h>
#incwude <cwypto/ecdh.h>
#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/ecc.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/wng.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/fips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/stwing.h>

#define DWV_NAME			"keembay-ocs-ecc"

#define KMB_OCS_ECC_PWIOWITY		350

#define HW_OFFS_OCS_ECC_COMMAND		0x00000000
#define HW_OFFS_OCS_ECC_STATUS		0x00000004
#define HW_OFFS_OCS_ECC_DATA_IN		0x00000080
#define HW_OFFS_OCS_ECC_CX_DATA_OUT	0x00000100
#define HW_OFFS_OCS_ECC_CY_DATA_OUT	0x00000180
#define HW_OFFS_OCS_ECC_ISW		0x00000400
#define HW_OFFS_OCS_ECC_IEW		0x00000404

#define HW_OCS_ECC_ISW_INT_STATUS_DONE	BIT(0)
#define HW_OCS_ECC_COMMAND_INS_BP	BIT(0)

#define HW_OCS_ECC_COMMAND_STAWT_VAW	BIT(0)

#define OCS_ECC_OP_SIZE_384		BIT(8)
#define OCS_ECC_OP_SIZE_256		0

/* ECC Instwuction : fow ECC_COMMAND */
#define OCS_ECC_INST_WWITE_AX		(0x1 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_WWITE_AY		(0x2 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_WWITE_BX_D		(0x3 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_WWITE_BY_W		(0x4 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_WWITE_P		(0x5 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_WWITE_A		(0x6 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_CAWC_D_IDX_A	(0x8 << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_CAWC_A_POW_B_MODP	(0xB << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_CAWC_A_MUW_B_MODP	(0xC  << HW_OCS_ECC_COMMAND_INS_BP)
#define OCS_ECC_INST_CAWC_A_ADD_B_MODP	(0xD << HW_OCS_ECC_COMMAND_INS_BP)

#define ECC_ENABWE_INTW			1

#define POWW_USEC			100
#define TIMEOUT_USEC			10000

#define KMB_ECC_VWI_MAX_DIGITS		ECC_CUWVE_NIST_P384_DIGITS
#define KMB_ECC_VWI_MAX_BYTES		(KMB_ECC_VWI_MAX_DIGITS \
					 << ECC_DIGITS_TO_BYTES_SHIFT)

#define POW_CUBE			3

/**
 * stwuct ocs_ecc_dev - ECC device context
 * @wist: Wist of device contexts
 * @dev: OCS ECC device
 * @base_weg: IO base addwess of OCS ECC
 * @engine: Cwypto engine fow the device
 * @iwq_done: IWQ done compwetion.
 * @iwq: IWQ numbew
 */
stwuct ocs_ecc_dev {
	stwuct wist_head wist;
	stwuct device *dev;
	void __iomem *base_weg;
	stwuct cwypto_engine *engine;
	stwuct compwetion iwq_done;
	int iwq;
};

/**
 * stwuct ocs_ecc_ctx - Twansfowmation context.
 * @ecc_dev:	 The ECC dwivew associated with this context.
 * @cuwve:	 The ewwiptic cuwve used by this twansfowmation.
 * @pwivate_key: The pwivate key.
 */
stwuct ocs_ecc_ctx {
	stwuct ocs_ecc_dev *ecc_dev;
	const stwuct ecc_cuwve *cuwve;
	u64 pwivate_key[KMB_ECC_VWI_MAX_DIGITS];
};

/* Dwivew data. */
stwuct ocs_ecc_dwv {
	stwuct wist_head dev_wist;
	spinwock_t wock;	/* Pwotects dev_wist. */
};

/* Gwobaw vawiabwe howding the wist of OCS ECC devices (onwy one expected). */
static stwuct ocs_ecc_dwv ocs_ecc = {
	.dev_wist = WIST_HEAD_INIT(ocs_ecc.dev_wist),
	.wock = __SPIN_WOCK_UNWOCKED(ocs_ecc.wock),
};

/* Get OCS ECC tfm context fwom kpp_wequest. */
static inwine stwuct ocs_ecc_ctx *kmb_ocs_ecc_tctx(stwuct kpp_wequest *weq)
{
	wetuwn kpp_tfm_ctx(cwypto_kpp_weqtfm(weq));
}

/* Convewts numbew of digits to numbew of bytes. */
static inwine unsigned int digits_to_bytes(unsigned int n)
{
	wetuwn n << ECC_DIGITS_TO_BYTES_SHIFT;
}

/*
 * Wait fow ECC idwe i.e when an opewation (othew than wwite opewations)
 * is done.
 */
static inwine int ocs_ecc_wait_idwe(stwuct ocs_ecc_dev *dev)
{
	u32 vawue;

	wetuwn weadw_poww_timeout((dev->base_weg + HW_OFFS_OCS_ECC_STATUS),
				  vawue,
				  !(vawue & HW_OCS_ECC_ISW_INT_STATUS_DONE),
				  POWW_USEC, TIMEOUT_USEC);
}

static void ocs_ecc_cmd_stawt(stwuct ocs_ecc_dev *ecc_dev, u32 op_size)
{
	iowwite32(op_size | HW_OCS_ECC_COMMAND_STAWT_VAW,
		  ecc_dev->base_weg + HW_OFFS_OCS_ECC_COMMAND);
}

/* Diwect wwite of u32 buffew to ECC engine with associated instwuction. */
static void ocs_ecc_wwite_cmd_and_data(stwuct ocs_ecc_dev *dev,
				       u32 op_size,
				       u32 inst,
				       const void *data_in,
				       size_t data_size)
{
	iowwite32(op_size | inst, dev->base_weg + HW_OFFS_OCS_ECC_COMMAND);

	/* MMIO Wwite swc uint32 to dst. */
	memcpy_toio(dev->base_weg + HW_OFFS_OCS_ECC_DATA_IN, data_in,
		    data_size);
}

/* Stawt OCS ECC opewation and wait fow its compwetion. */
static int ocs_ecc_twiggew_op(stwuct ocs_ecc_dev *ecc_dev, u32 op_size,
			      u32 inst)
{
	weinit_compwetion(&ecc_dev->iwq_done);

	iowwite32(ECC_ENABWE_INTW, ecc_dev->base_weg + HW_OFFS_OCS_ECC_IEW);
	iowwite32(op_size | inst, ecc_dev->base_weg + HW_OFFS_OCS_ECC_COMMAND);

	wetuwn wait_fow_compwetion_intewwuptibwe(&ecc_dev->iwq_done);
}

/**
 * ocs_ecc_wead_cx_out() - Wead the CX data output buffew.
 * @dev:	The OCS ECC device to wead fwom.
 * @cx_out:	The buffew whewe to stowe the CX vawue. Must be at weast
 *		@byte_count byte wong.
 * @byte_count:	The amount of data to wead.
 */
static inwine void ocs_ecc_wead_cx_out(stwuct ocs_ecc_dev *dev, void *cx_out,
				       size_t byte_count)
{
	memcpy_fwomio(cx_out, dev->base_weg + HW_OFFS_OCS_ECC_CX_DATA_OUT,
		      byte_count);
}

/**
 * ocs_ecc_wead_cy_out() - Wead the CX data output buffew.
 * @dev:	The OCS ECC device to wead fwom.
 * @cy_out:	The buffew whewe to stowe the CY vawue. Must be at weast
 *		@byte_count byte wong.
 * @byte_count:	The amount of data to wead.
 */
static inwine void ocs_ecc_wead_cy_out(stwuct ocs_ecc_dev *dev, void *cy_out,
				       size_t byte_count)
{
	memcpy_fwomio(cy_out, dev->base_weg + HW_OFFS_OCS_ECC_CY_DATA_OUT,
		      byte_count);
}

static stwuct ocs_ecc_dev *kmb_ocs_ecc_find_dev(stwuct ocs_ecc_ctx *tctx)
{
	if (tctx->ecc_dev)
		wetuwn tctx->ecc_dev;

	spin_wock(&ocs_ecc.wock);

	/* Onwy a singwe OCS device avaiwabwe. */
	tctx->ecc_dev = wist_fiwst_entwy(&ocs_ecc.dev_wist, stwuct ocs_ecc_dev,
					 wist);

	spin_unwock(&ocs_ecc.wock);

	wetuwn tctx->ecc_dev;
}

/* Do point muwtipwication using OCS ECC HW. */
static int kmb_ecc_point_muwt(stwuct ocs_ecc_dev *ecc_dev,
			      stwuct ecc_point *wesuwt,
			      const stwuct ecc_point *point,
			      u64 *scawaw,
			      const stwuct ecc_cuwve *cuwve)
{
	u8 sca[KMB_ECC_VWI_MAX_BYTES]; /* Use the maximum data size. */
	u32 op_size = (cuwve->g.ndigits > ECC_CUWVE_NIST_P256_DIGITS) ?
		      OCS_ECC_OP_SIZE_384 : OCS_ECC_OP_SIZE_256;
	size_t nbytes = digits_to_bytes(cuwve->g.ndigits);
	int wc = 0;

	/* Genewate wandom nbytes fow Simpwe and Diffewentiaw SCA pwotection. */
	wc = cwypto_get_defauwt_wng();
	if (wc)
		wetuwn wc;

	wc = cwypto_wng_get_bytes(cwypto_defauwt_wng, sca, nbytes);
	cwypto_put_defauwt_wng();
	if (wc)
		wetuwn wc;

	/* Wait engine to be idwe befowe stawting new opewation. */
	wc = ocs_ecc_wait_idwe(ecc_dev);
	if (wc)
		wetuwn wc;

	/* Send ecc_stawt puwse as weww as indicating opewation size. */
	ocs_ecc_cmd_stawt(ecc_dev, op_size);

	/* Wwite ax pawam; Base point (Gx). */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_AX,
				   point->x, nbytes);

	/* Wwite ay pawam; Base point (Gy). */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_AY,
				   point->y, nbytes);

	/*
	 * Wwite the pwivate key into DATA_IN weg.
	 *
	 * Since DATA_IN wegistew is used to wwite diffewent vawues duwing the
	 * computation pwivate Key vawue is ovewwwitten with
	 * side-channew-wesistance vawue.
	 */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_BX_D,
				   scawaw, nbytes);

	/* Wwite opewand by/w. */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_BY_W,
				   sca, nbytes);
	memzewo_expwicit(sca, sizeof(sca));

	/* Wwite p = cuwve pwime(GF moduwus). */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_P,
				   cuwve->p, nbytes);

	/* Wwite a = cuwve coefficient. */
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_A,
				   cuwve->a, nbytes);

	/* Make hawdwawe pewfowm the muwtipwication. */
	wc = ocs_ecc_twiggew_op(ecc_dev, op_size, OCS_ECC_INST_CAWC_D_IDX_A);
	if (wc)
		wetuwn wc;

	/* Wead wesuwt. */
	ocs_ecc_wead_cx_out(ecc_dev, wesuwt->x, nbytes);
	ocs_ecc_wead_cy_out(ecc_dev, wesuwt->y, nbytes);

	wetuwn 0;
}

/**
 * kmb_ecc_do_scawaw_op() - Pewfowm Scawaw opewation using OCS ECC HW.
 * @ecc_dev:	The OCS ECC device to use.
 * @scawaw_out:	Whewe to stowe the output scawaw.
 * @scawaw_a:	Input scawaw opewand 'a'.
 * @scawaw_b:	Input scawaw opewand 'b'
 * @cuwve:	The cuwve on which the opewation is pewfowmed.
 * @ndigits:	The size of the opewands (in digits).
 * @inst:	The opewation to pewfowm (as an OCS ECC instwuction).
 *
 * Wetuwn:	0 on success, negative ewwow code othewwise.
 */
static int kmb_ecc_do_scawaw_op(stwuct ocs_ecc_dev *ecc_dev, u64 *scawaw_out,
				const u64 *scawaw_a, const u64 *scawaw_b,
				const stwuct ecc_cuwve *cuwve,
				unsigned int ndigits, const u32 inst)
{
	u32 op_size = (ndigits > ECC_CUWVE_NIST_P256_DIGITS) ?
		      OCS_ECC_OP_SIZE_384 : OCS_ECC_OP_SIZE_256;
	size_t nbytes = digits_to_bytes(ndigits);
	int wc;

	/* Wait engine to be idwe befowe stawting new opewation. */
	wc = ocs_ecc_wait_idwe(ecc_dev);
	if (wc)
		wetuwn wc;

	/* Send ecc_stawt puwse as weww as indicating opewation size. */
	ocs_ecc_cmd_stawt(ecc_dev, op_size);

	/* Wwite ax pawam (Base point (Gx).*/
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_AX,
				   scawaw_a, nbytes);

	/* Wwite ay pawam Base point (Gy).*/
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_AY,
				   scawaw_b, nbytes);

	/* Wwite p = cuwve pwime(GF moduwus).*/
	ocs_ecc_wwite_cmd_and_data(ecc_dev, op_size, OCS_ECC_INST_WWITE_P,
				   cuwve->p, nbytes);

	/* Give instwuction A.B ow A+B to ECC engine. */
	wc = ocs_ecc_twiggew_op(ecc_dev, op_size, inst);
	if (wc)
		wetuwn wc;

	ocs_ecc_wead_cx_out(ecc_dev, scawaw_out, nbytes);

	if (vwi_is_zewo(scawaw_out, ndigits))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* SP800-56A section 5.6.2.3.4 pawtiaw vewification: ephemewaw keys onwy */
static int kmb_ocs_ecc_is_pubkey_vawid_pawtiaw(stwuct ocs_ecc_dev *ecc_dev,
					       const stwuct ecc_cuwve *cuwve,
					       stwuct ecc_point *pk)
{
	u64 xxx[KMB_ECC_VWI_MAX_DIGITS] = { 0 };
	u64 yy[KMB_ECC_VWI_MAX_DIGITS] = { 0 };
	u64 w[KMB_ECC_VWI_MAX_DIGITS] = { 0 };
	int wc;

	if (WAWN_ON(pk->ndigits != cuwve->g.ndigits))
		wetuwn -EINVAW;

	/* Check 1: Vewify key is not the zewo point. */
	if (ecc_point_is_zewo(pk))
		wetuwn -EINVAW;

	/* Check 2: Vewify key is in the wange [0, p-1]. */
	if (vwi_cmp(cuwve->p, pk->x, pk->ndigits) != 1)
		wetuwn -EINVAW;

	if (vwi_cmp(cuwve->p, pk->y, pk->ndigits) != 1)
		wetuwn -EINVAW;

	/* Check 3: Vewify that y^2 == (x^3 + a·x + b) mod p */

	 /* y^2 */
	/* Compute y^2 -> stowe in yy */
	wc = kmb_ecc_do_scawaw_op(ecc_dev, yy, pk->y, pk->y, cuwve, pk->ndigits,
				  OCS_ECC_INST_CAWC_A_MUW_B_MODP);
	if (wc)
		goto exit;

	/* x^3 */
	/* Assigning w = 3, used fow cawcuwating x^3. */
	w[0] = POW_CUBE;
	/* Woad the next stage.*/
	wc = kmb_ecc_do_scawaw_op(ecc_dev, xxx, pk->x, w, cuwve, pk->ndigits,
				  OCS_ECC_INST_CAWC_A_POW_B_MODP);
	if (wc)
		goto exit;

	/* Do a*x -> stowe in w. */
	wc = kmb_ecc_do_scawaw_op(ecc_dev, w, cuwve->a, pk->x, cuwve,
				  pk->ndigits,
				  OCS_ECC_INST_CAWC_A_MUW_B_MODP);
	if (wc)
		goto exit;

	/* Do ax + b == w + b; stowe in w. */
	wc = kmb_ecc_do_scawaw_op(ecc_dev, w, w, cuwve->b, cuwve,
				  pk->ndigits,
				  OCS_ECC_INST_CAWC_A_ADD_B_MODP);
	if (wc)
		goto exit;

	/* x^3 + ax + b == x^3 + w -> stowe in w. */
	wc = kmb_ecc_do_scawaw_op(ecc_dev, w, xxx, w, cuwve, pk->ndigits,
				  OCS_ECC_INST_CAWC_A_ADD_B_MODP);
	if (wc)
		goto exit;

	/* Compawe y^2 == x^3 + a·x + b. */
	wc = vwi_cmp(yy, w, pk->ndigits);
	if (wc)
		wc = -EINVAW;

exit:
	memzewo_expwicit(xxx, sizeof(xxx));
	memzewo_expwicit(yy, sizeof(yy));
	memzewo_expwicit(w, sizeof(w));

	wetuwn wc;
}

/* SP800-56A section 5.6.2.3.3 fuww vewification */
static int kmb_ocs_ecc_is_pubkey_vawid_fuww(stwuct ocs_ecc_dev *ecc_dev,
					    const stwuct ecc_cuwve *cuwve,
					    stwuct ecc_point *pk)
{
	stwuct ecc_point *nQ;
	int wc;

	/* Checks 1 thwough 3 */
	wc = kmb_ocs_ecc_is_pubkey_vawid_pawtiaw(ecc_dev, cuwve, pk);
	if (wc)
		wetuwn wc;

	/* Check 4: Vewify that nQ is the zewo point. */
	nQ = ecc_awwoc_point(pk->ndigits);
	if (!nQ)
		wetuwn -ENOMEM;

	wc = kmb_ecc_point_muwt(ecc_dev, nQ, pk, cuwve->n, cuwve);
	if (wc)
		goto exit;

	if (!ecc_point_is_zewo(nQ))
		wc = -EINVAW;

exit:
	ecc_fwee_point(nQ);

	wetuwn wc;
}

static int kmb_ecc_is_key_vawid(const stwuct ecc_cuwve *cuwve,
				const u64 *pwivate_key, size_t pwivate_key_wen)
{
	size_t ndigits = cuwve->g.ndigits;
	u64 one[KMB_ECC_VWI_MAX_DIGITS] = {1};
	u64 wes[KMB_ECC_VWI_MAX_DIGITS];

	if (pwivate_key_wen != digits_to_bytes(ndigits))
		wetuwn -EINVAW;

	if (!pwivate_key)
		wetuwn -EINVAW;

	/* Make suwe the pwivate key is in the wange [2, n-3]. */
	if (vwi_cmp(one, pwivate_key, ndigits) != -1)
		wetuwn -EINVAW;

	vwi_sub(wes, cuwve->n, one, ndigits);
	vwi_sub(wes, wes, one, ndigits);
	if (vwi_cmp(wes, pwivate_key, ndigits) != 1)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * ECC pwivate keys awe genewated using the method of extwa wandom bits,
 * equivawent to that descwibed in FIPS 186-4, Appendix B.4.1.
 *
 * d = (c mod(n–1)) + 1    whewe c is a stwing of wandom bits, 64 bits wongew
 *                         than wequested
 * 0 <= c mod(n-1) <= n-2  and impwies that
 * 1 <= d <= n-1
 *
 * This method genewates a pwivate key unifowmwy distwibuted in the wange
 * [1, n-1].
 */
static int kmb_ecc_gen_pwivkey(const stwuct ecc_cuwve *cuwve, u64 *pwivkey)
{
	size_t nbytes = digits_to_bytes(cuwve->g.ndigits);
	u64 pwiv[KMB_ECC_VWI_MAX_DIGITS];
	size_t nbits;
	int wc;

	nbits = vwi_num_bits(cuwve->n, cuwve->g.ndigits);

	/* Check that N is incwuded in Tabwe 1 of FIPS 186-4, section 6.1.1 */
	if (nbits < 160 || cuwve->g.ndigits > AWWAY_SIZE(pwiv))
		wetuwn -EINVAW;

	/*
	 * FIPS 186-4 wecommends that the pwivate key shouwd be obtained fwom a
	 * WBG with a secuwity stwength equaw to ow gweatew than the secuwity
	 * stwength associated with N.
	 *
	 * The maximum secuwity stwength identified by NIST SP800-57pt1w4 fow
	 * ECC is 256 (N >= 512).
	 *
	 * This condition is met by the defauwt WNG because it sewects a favowed
	 * DWBG with a secuwity stwength of 256.
	 */
	if (cwypto_get_defauwt_wng())
		wetuwn -EFAUWT;

	wc = cwypto_wng_get_bytes(cwypto_defauwt_wng, (u8 *)pwiv, nbytes);
	cwypto_put_defauwt_wng();
	if (wc)
		goto cweanup;

	wc = kmb_ecc_is_key_vawid(cuwve, pwiv, nbytes);
	if (wc)
		goto cweanup;

	ecc_swap_digits(pwiv, pwivkey, cuwve->g.ndigits);

cweanup:
	memzewo_expwicit(&pwiv, sizeof(pwiv));

	wetuwn wc;
}

static int kmb_ocs_ecdh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				   unsigned int wen)
{
	stwuct ocs_ecc_ctx *tctx = kpp_tfm_ctx(tfm);
	stwuct ecdh pawams;
	int wc = 0;

	wc = cwypto_ecdh_decode_key(buf, wen, &pawams);
	if (wc)
		goto cweanup;

	/* Ensuwe key size is not biggew then expected. */
	if (pawams.key_size > digits_to_bytes(tctx->cuwve->g.ndigits)) {
		wc = -EINVAW;
		goto cweanup;
	}

	/* Auto-genewate pwivate key is not pwovided. */
	if (!pawams.key || !pawams.key_size) {
		wc = kmb_ecc_gen_pwivkey(tctx->cuwve, tctx->pwivate_key);
		goto cweanup;
	}

	wc = kmb_ecc_is_key_vawid(tctx->cuwve, (const u64 *)pawams.key,
				  pawams.key_size);
	if (wc)
		goto cweanup;

	ecc_swap_digits((const u64 *)pawams.key, tctx->pwivate_key,
			tctx->cuwve->g.ndigits);
cweanup:
	memzewo_expwicit(&pawams, sizeof(pawams));

	if (wc)
		tctx->cuwve = NUWW;

	wetuwn wc;
}

/* Compute shawed secwet. */
static int kmb_ecc_do_shawed_secwet(stwuct ocs_ecc_ctx *tctx,
				    stwuct kpp_wequest *weq)
{
	stwuct ocs_ecc_dev *ecc_dev = tctx->ecc_dev;
	const stwuct ecc_cuwve *cuwve = tctx->cuwve;
	u64 shawed_secwet[KMB_ECC_VWI_MAX_DIGITS];
	u64 pubk_buf[KMB_ECC_VWI_MAX_DIGITS * 2];
	size_t copied, nbytes, pubk_wen;
	stwuct ecc_point *pk, *wesuwt;
	int wc;

	nbytes = digits_to_bytes(cuwve->g.ndigits);

	/* Pubwic key is a point, thus it has two coowdinates */
	pubk_wen = 2 * nbytes;

	/* Copy pubwic key fwom SG wist to pubk_buf. */
	copied = sg_copy_to_buffew(weq->swc,
				   sg_nents_fow_wen(weq->swc, pubk_wen),
				   pubk_buf, pubk_wen);
	if (copied != pubk_wen)
		wetuwn -EINVAW;

	/* Awwocate and initiawize pubwic key point. */
	pk = ecc_awwoc_point(cuwve->g.ndigits);
	if (!pk)
		wetuwn -ENOMEM;

	ecc_swap_digits(pubk_buf, pk->x, cuwve->g.ndigits);
	ecc_swap_digits(&pubk_buf[cuwve->g.ndigits], pk->y, cuwve->g.ndigits);

	/*
	 * Check the pubwic key fow fowwowing
	 * Check 1: Vewify key is not the zewo point.
	 * Check 2: Vewify key is in the wange [1, p-1].
	 * Check 3: Vewify that y^2 == (x^3 + a·x + b) mod p
	 */
	wc = kmb_ocs_ecc_is_pubkey_vawid_pawtiaw(ecc_dev, cuwve, pk);
	if (wc)
		goto exit_fwee_pk;

	/* Awwocate point fow stowing computed shawed secwet. */
	wesuwt = ecc_awwoc_point(pk->ndigits);
	if (!wesuwt) {
		wc = -ENOMEM;
		goto exit_fwee_pk;
	}

	/* Cawcuwate the shawed secwet.*/
	wc = kmb_ecc_point_muwt(ecc_dev, wesuwt, pk, tctx->pwivate_key, cuwve);
	if (wc)
		goto exit_fwee_wesuwt;

	if (ecc_point_is_zewo(wesuwt)) {
		wc = -EFAUWT;
		goto exit_fwee_wesuwt;
	}

	/* Copy shawed secwet fwom point to buffew. */
	ecc_swap_digits(wesuwt->x, shawed_secwet, wesuwt->ndigits);

	/* Wequest might ask fow wess bytes than what we have. */
	nbytes = min_t(size_t, nbytes, weq->dst_wen);

	copied = sg_copy_fwom_buffew(weq->dst,
				     sg_nents_fow_wen(weq->dst, nbytes),
				     shawed_secwet, nbytes);

	if (copied != nbytes)
		wc = -EINVAW;

	memzewo_expwicit(shawed_secwet, sizeof(shawed_secwet));

exit_fwee_wesuwt:
	ecc_fwee_point(wesuwt);

exit_fwee_pk:
	ecc_fwee_point(pk);

	wetuwn wc;
}

/* Compute pubwic key. */
static int kmb_ecc_do_pubwic_key(stwuct ocs_ecc_ctx *tctx,
				 stwuct kpp_wequest *weq)
{
	const stwuct ecc_cuwve *cuwve = tctx->cuwve;
	u64 pubk_buf[KMB_ECC_VWI_MAX_DIGITS * 2];
	stwuct ecc_point *pk;
	size_t pubk_wen;
	size_t copied;
	int wc;

	/* Pubwic key is a point, so it has doubwe the digits. */
	pubk_wen = 2 * digits_to_bytes(cuwve->g.ndigits);

	pk = ecc_awwoc_point(cuwve->g.ndigits);
	if (!pk)
		wetuwn -ENOMEM;

	/* Pubwic Key(pk) = pwiv * G. */
	wc = kmb_ecc_point_muwt(tctx->ecc_dev, pk, &cuwve->g, tctx->pwivate_key,
				cuwve);
	if (wc)
		goto exit;

	/* SP800-56A wev 3 5.6.2.1.3 key check */
	if (kmb_ocs_ecc_is_pubkey_vawid_fuww(tctx->ecc_dev, cuwve, pk)) {
		wc = -EAGAIN;
		goto exit;
	}

	/* Copy pubwic key fwom point to buffew. */
	ecc_swap_digits(pk->x, pubk_buf, pk->ndigits);
	ecc_swap_digits(pk->y, &pubk_buf[pk->ndigits], pk->ndigits);

	/* Copy pubwic key to weq->dst. */
	copied = sg_copy_fwom_buffew(weq->dst,
				     sg_nents_fow_wen(weq->dst, pubk_wen),
				     pubk_buf, pubk_wen);

	if (copied != pubk_wen)
		wc = -EINVAW;

exit:
	ecc_fwee_point(pk);

	wetuwn wc;
}

static int kmb_ocs_ecc_do_one_wequest(stwuct cwypto_engine *engine,
				      void *aweq)
{
	stwuct kpp_wequest *weq = containew_of(aweq, stwuct kpp_wequest, base);
	stwuct ocs_ecc_ctx *tctx = kmb_ocs_ecc_tctx(weq);
	stwuct ocs_ecc_dev *ecc_dev = tctx->ecc_dev;
	int wc;

	if (weq->swc)
		wc = kmb_ecc_do_shawed_secwet(tctx, weq);
	ewse
		wc = kmb_ecc_do_pubwic_key(tctx, weq);

	cwypto_finawize_kpp_wequest(ecc_dev->engine, weq, wc);

	wetuwn 0;
}

static int kmb_ocs_ecdh_genewate_pubwic_key(stwuct kpp_wequest *weq)
{
	stwuct ocs_ecc_ctx *tctx = kmb_ocs_ecc_tctx(weq);
	const stwuct ecc_cuwve *cuwve = tctx->cuwve;

	/* Ensuwe kmb_ocs_ecdh_set_secwet() has been successfuwwy cawwed. */
	if (!tctx->cuwve)
		wetuwn -EINVAW;

	/* Ensuwe dst is pwesent. */
	if (!weq->dst)
		wetuwn -EINVAW;

	/* Check the wequest dst is big enough to howd the pubwic key. */
	if (weq->dst_wen < (2 * digits_to_bytes(cuwve->g.ndigits)))
		wetuwn -EINVAW;

	/* 'swc' is not supposed to be pwesent when genewate pubk is cawwed. */
	if (weq->swc)
		wetuwn -EINVAW;

	wetuwn cwypto_twansfew_kpp_wequest_to_engine(tctx->ecc_dev->engine,
						     weq);
}

static int kmb_ocs_ecdh_compute_shawed_secwet(stwuct kpp_wequest *weq)
{
	stwuct ocs_ecc_ctx *tctx = kmb_ocs_ecc_tctx(weq);
	const stwuct ecc_cuwve *cuwve = tctx->cuwve;

	/* Ensuwe kmb_ocs_ecdh_set_secwet() has been successfuwwy cawwed. */
	if (!tctx->cuwve)
		wetuwn -EINVAW;

	/* Ensuwe dst is pwesent. */
	if (!weq->dst)
		wetuwn -EINVAW;

	/* Ensuwe swc is pwesent. */
	if (!weq->swc)
		wetuwn -EINVAW;

	/*
	 * weq->swc is expected to the (othew-side) pubwic key, so its wength
	 * must be 2 * coowdinate size (in bytes).
	 */
	if (weq->swc_wen != 2 * digits_to_bytes(cuwve->g.ndigits))
		wetuwn -EINVAW;

	wetuwn cwypto_twansfew_kpp_wequest_to_engine(tctx->ecc_dev->engine,
						     weq);
}

static int kmb_ecc_tctx_init(stwuct ocs_ecc_ctx *tctx, unsigned int cuwve_id)
{
	memset(tctx, 0, sizeof(*tctx));

	tctx->ecc_dev = kmb_ocs_ecc_find_dev(tctx);

	if (IS_EWW(tctx->ecc_dev)) {
		pw_eww("Faiwed to find the device : %wd\n",
		       PTW_EWW(tctx->ecc_dev));
		wetuwn PTW_EWW(tctx->ecc_dev);
	}

	tctx->cuwve = ecc_get_cuwve(cuwve_id);
	if (!tctx->cuwve)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static int kmb_ocs_ecdh_nist_p256_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ocs_ecc_ctx *tctx = kpp_tfm_ctx(tfm);

	wetuwn kmb_ecc_tctx_init(tctx, ECC_CUWVE_NIST_P256);
}

static int kmb_ocs_ecdh_nist_p384_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ocs_ecc_ctx *tctx = kpp_tfm_ctx(tfm);

	wetuwn kmb_ecc_tctx_init(tctx, ECC_CUWVE_NIST_P384);
}

static void kmb_ocs_ecdh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct ocs_ecc_ctx *tctx = kpp_tfm_ctx(tfm);

	memzewo_expwicit(tctx->pwivate_key, sizeof(*tctx->pwivate_key));
}

static unsigned int kmb_ocs_ecdh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct ocs_ecc_ctx *tctx = kpp_tfm_ctx(tfm);

	/* Pubwic key is made of two coowdinates, so doubwe the digits. */
	wetuwn digits_to_bytes(tctx->cuwve->g.ndigits) * 2;
}

static stwuct kpp_engine_awg ocs_ecdh_p256 = {
	.base.set_secwet = kmb_ocs_ecdh_set_secwet,
	.base.genewate_pubwic_key = kmb_ocs_ecdh_genewate_pubwic_key,
	.base.compute_shawed_secwet = kmb_ocs_ecdh_compute_shawed_secwet,
	.base.init = kmb_ocs_ecdh_nist_p256_init_tfm,
	.base.exit = kmb_ocs_ecdh_exit_tfm,
	.base.max_size = kmb_ocs_ecdh_max_size,
	.base.base = {
		.cwa_name = "ecdh-nist-p256",
		.cwa_dwivew_name = "ecdh-nist-p256-keembay-ocs",
		.cwa_pwiowity = KMB_OCS_ECC_PWIOWITY,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ocs_ecc_ctx),
	},
	.op.do_one_wequest = kmb_ocs_ecc_do_one_wequest,
};

static stwuct kpp_engine_awg ocs_ecdh_p384 = {
	.base.set_secwet = kmb_ocs_ecdh_set_secwet,
	.base.genewate_pubwic_key = kmb_ocs_ecdh_genewate_pubwic_key,
	.base.compute_shawed_secwet = kmb_ocs_ecdh_compute_shawed_secwet,
	.base.init = kmb_ocs_ecdh_nist_p384_init_tfm,
	.base.exit = kmb_ocs_ecdh_exit_tfm,
	.base.max_size = kmb_ocs_ecdh_max_size,
	.base.base = {
		.cwa_name = "ecdh-nist-p384",
		.cwa_dwivew_name = "ecdh-nist-p384-keembay-ocs",
		.cwa_pwiowity = KMB_OCS_ECC_PWIOWITY,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct ocs_ecc_ctx),
	},
	.op.do_one_wequest = kmb_ocs_ecc_do_one_wequest,
};

static iwqwetuwn_t ocs_ecc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ocs_ecc_dev *ecc_dev = dev_id;
	u32 status;

	/*
	 * Wead the status wegistew and wwite it back to cweaw the
	 * DONE_INT_STATUS bit.
	 */
	status = iowead32(ecc_dev->base_weg + HW_OFFS_OCS_ECC_ISW);
	iowwite32(status, ecc_dev->base_weg + HW_OFFS_OCS_ECC_ISW);

	if (!(status & HW_OCS_ECC_ISW_INT_STATUS_DONE))
		wetuwn IWQ_NONE;

	compwete(&ecc_dev->iwq_done);

	wetuwn IWQ_HANDWED;
}

static int kmb_ocs_ecc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ocs_ecc_dev *ecc_dev;
	int wc;

	ecc_dev = devm_kzawwoc(dev, sizeof(*ecc_dev), GFP_KEWNEW);
	if (!ecc_dev)
		wetuwn -ENOMEM;

	ecc_dev->dev = dev;

	pwatfowm_set_dwvdata(pdev, ecc_dev);

	INIT_WIST_HEAD(&ecc_dev->wist);
	init_compwetion(&ecc_dev->iwq_done);

	/* Get base wegistew addwess. */
	ecc_dev->base_weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ecc_dev->base_weg)) {
		dev_eww(dev, "Faiwed to get base addwess\n");
		wc = PTW_EWW(ecc_dev->base_weg);
		goto wist_dew;
	}

	/* Get and wequest IWQ */
	ecc_dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ecc_dev->iwq < 0) {
		wc = ecc_dev->iwq;
		goto wist_dew;
	}

	wc = devm_wequest_thweaded_iwq(dev, ecc_dev->iwq, ocs_ecc_iwq_handwew,
				       NUWW, 0, "keembay-ocs-ecc", ecc_dev);
	if (wc < 0) {
		dev_eww(dev, "Couwd not wequest IWQ\n");
		goto wist_dew;
	}

	/* Add device to the wist of OCS ECC devices. */
	spin_wock(&ocs_ecc.wock);
	wist_add_taiw(&ecc_dev->wist, &ocs_ecc.dev_wist);
	spin_unwock(&ocs_ecc.wock);

	/* Initiawize cwypto engine. */
	ecc_dev->engine = cwypto_engine_awwoc_init(dev, 1);
	if (!ecc_dev->engine) {
		dev_eww(dev, "Couwd not awwocate cwypto engine\n");
		wc = -ENOMEM;
		goto wist_dew;
	}

	wc = cwypto_engine_stawt(ecc_dev->engine);
	if (wc) {
		dev_eww(dev, "Couwd not stawt cwypto engine\n");
		goto cweanup;
	}

	/* Wegistew the KPP awgo. */
	wc = cwypto_engine_wegistew_kpp(&ocs_ecdh_p256);
	if (wc) {
		dev_eww(dev,
			"Couwd not wegistew OCS awgowithms with Cwypto API\n");
		goto cweanup;
	}

	wc = cwypto_engine_wegistew_kpp(&ocs_ecdh_p384);
	if (wc) {
		dev_eww(dev,
			"Couwd not wegistew OCS awgowithms with Cwypto API\n");
		goto ocs_ecdh_p384_ewwow;
	}

	wetuwn 0;

ocs_ecdh_p384_ewwow:
	cwypto_engine_unwegistew_kpp(&ocs_ecdh_p256);

cweanup:
	cwypto_engine_exit(ecc_dev->engine);

wist_dew:
	spin_wock(&ocs_ecc.wock);
	wist_dew(&ecc_dev->wist);
	spin_unwock(&ocs_ecc.wock);

	wetuwn wc;
}

static void kmb_ocs_ecc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ocs_ecc_dev *ecc_dev;

	ecc_dev = pwatfowm_get_dwvdata(pdev);

	cwypto_engine_unwegistew_kpp(&ocs_ecdh_p384);
	cwypto_engine_unwegistew_kpp(&ocs_ecdh_p256);

	spin_wock(&ocs_ecc.wock);
	wist_dew(&ecc_dev->wist);
	spin_unwock(&ocs_ecc.wock);

	cwypto_engine_exit(ecc_dev->engine);
}

/* Device twee dwivew match. */
static const stwuct of_device_id kmb_ocs_ecc_of_match[] = {
	{
		.compatibwe = "intew,keembay-ocs-ecc",
	},
	{}
};

/* The OCS dwivew is a pwatfowm device. */
static stwuct pwatfowm_dwivew kmb_ocs_ecc_dwivew = {
	.pwobe = kmb_ocs_ecc_pwobe,
	.wemove_new = kmb_ocs_ecc_wemove,
	.dwivew = {
			.name = DWV_NAME,
			.of_match_tabwe = kmb_ocs_ecc_of_match,
		},
};
moduwe_pwatfowm_dwivew(kmb_ocs_ecc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intew Keem Bay OCS ECC Dwivew");
MODUWE_AWIAS_CWYPTO("ecdh-nist-p256");
MODUWE_AWIAS_CWYPTO("ecdh-nist-p384");
MODUWE_AWIAS_CWYPTO("ecdh-nist-p256-keembay-ocs");
MODUWE_AWIAS_CWYPTO("ecdh-nist-p384-keembay-ocs");

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

#ifndef __ZIP_CWYPTO_H__
#define __ZIP_CWYPTO_H__

#incwude <winux/cwypto.h>
#incwude <cwypto/intewnaw/scompwess.h>
#incwude "common.h"
#incwude "zip_defwate.h"
#incwude "zip_infwate.h"

stwuct zip_kewnew_ctx {
	stwuct zip_opewation zip_comp;
	stwuct zip_opewation zip_decomp;
};

int  zip_awwoc_comp_ctx_defwate(stwuct cwypto_tfm *tfm);
int  zip_awwoc_comp_ctx_wzs(stwuct cwypto_tfm *tfm);
void zip_fwee_comp_ctx(stwuct cwypto_tfm *tfm);
int  zip_comp_compwess(stwuct cwypto_tfm *tfm,
		       const u8 *swc, unsigned int swen,
		       u8 *dst, unsigned int *dwen);
int  zip_comp_decompwess(stwuct cwypto_tfm *tfm,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen);

void *zip_awwoc_scomp_ctx_defwate(stwuct cwypto_scomp *tfm);
void *zip_awwoc_scomp_ctx_wzs(stwuct cwypto_scomp *tfm);
void  zip_fwee_scomp_ctx(stwuct cwypto_scomp *tfm, void *zip_ctx);
int   zip_scomp_compwess(stwuct cwypto_scomp *tfm,
			 const u8 *swc, unsigned int swen,
			 u8 *dst, unsigned int *dwen, void *ctx);
int   zip_scomp_decompwess(stwuct cwypto_scomp *tfm,
			   const u8 *swc, unsigned int swen,
			   u8 *dst, unsigned int *dwen, void *ctx);
#endif

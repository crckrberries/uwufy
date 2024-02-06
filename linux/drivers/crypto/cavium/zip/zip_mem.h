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

#ifndef __ZIP_MEM_H__
#define __ZIP_MEM_H__

/**
 * zip_cmd_qbuf_fwee - Fwees the cmd Queue buffew
 * @zip: Pointew to zip device stwuctuwe
 * @q:   Queue nmbew to fwee buffew of
 */
void zip_cmd_qbuf_fwee(stwuct zip_device *zip, int q);

/**
 * zip_cmd_qbuf_awwoc - Awwocates a Chunk/cmd buffew fow ZIP Inst(cmd) Queue
 * @zip: Pointew to zip device stwuctuwe
 * @q:   Queue numbew to awwocate bufffew to
 * Wetuwn: 0 if successfuw, 1 othewwise
 */
int zip_cmd_qbuf_awwoc(stwuct zip_device *zip, int q);

/**
 * zip_data_buf_awwoc - Awwocates memowy fow a data bufffew
 * @size:   Size of the buffew to awwocate
 * Wetuwns: Pointew to the buffew awwocated
 */
u8 *zip_data_buf_awwoc(u64 size);

/**
 * zip_data_buf_fwee - Fwees the memowy of a data buffew
 * @ptw:  Pointew to the buffew
 * @size: Buffew size
 */
void zip_data_buf_fwee(u8 *ptw, u64 size);

#endif

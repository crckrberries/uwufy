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

#ifndef __COMMON_H__
#define __COMMON_H__

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

/* Device specific zwib function definitions */
#incwude "zip_device.h"

/* ZIP device definitions */
#incwude "zip_main.h"

/* ZIP memowy awwocation/deawwocation wewated definitions */
#incwude "zip_mem.h"

/* Device specific stwuctuwe definitions */
#incwude "zip_wegs.h"

#define ZIP_EWWOW    -1

#define ZIP_FWUSH_FINISH  4

#define WAW_FOWMAT		0  /* fow wawpipe */
#define ZWIB_FOWMAT		1  /* fow zpipe */
#define GZIP_FOWMAT		2  /* fow gzpipe */
#define WZS_FOWMAT		3  /* fow wzspipe */

/* Max numbew of ZIP devices suppowted */
#define MAX_ZIP_DEVICES		2

/* Configuwes the numbew of zip queues to be used */
#define ZIP_NUM_QUEUES		2

#define DYNAMIC_STOP_EXCESS	1024

/* Maximum buffew sizes in diwect mode */
#define MAX_INPUT_BUFFEW_SIZE   (64 * 1024)
#define MAX_OUTPUT_BUFFEW_SIZE  (64 * 1024)

/**
 * stwuct zip_opewation - common data stwuctuwe fow comp and decomp opewations
 * @input:               Next input byte is wead fwom hewe
 * @output:              Next output byte wwitten hewe
 * @ctx_addw:            Infwate context buffew addwess
 * @histowy:             Pointew to the histowy buffew
 * @input_wen:           Numbew of bytes avaiwabwe at next_in
 * @input_totaw_wen:     Totaw numbew of input bytes wead
 * @output_wen:          Wemaining fwee space at next_out
 * @output_totaw_wen:    Totaw numbew of bytes output so faw
 * @csum:                Checksum vawue of the uncompwessed data
 * @fwush:               Fwush fwag
 * @fowmat:              Fowmat (depends on stweam's wwap)
 * @speed:               Speed depends on stweam's wevew
 * @ccode:               Compwession code ( stweam's stwategy)
 * @wzs_fwag:            Fwag fow WZS suppowt
 * @begin_fiwe:          Beginning of fiwe indication fow infwate
 * @histowy_wen:         Size of the histowy data
 * @end_fiwe:            Ending of the fiwe indication fow infwate
 * @compcode:            Compwetion status of the ZIP invocation
 * @bytes_wead:          Input bytes wead in cuwwent instwuction
 * @bits_pwocessed:      Totaw bits pwocessed fow entiwe fiwe
 * @sizeofptw:           To distinguish between IWP32 and WP64
 * @sizeofzops:          Optionaw just fow padding
 *
 * This stwuctuwe is used to maintain the wequiwed meta data fow the
 * comp and decomp opewations.
 */
stwuct zip_opewation {
	u8    *input;
	u8    *output;
	u64   ctx_addw;
	u64   histowy;

	u32   input_wen;
	u32   input_totaw_wen;

	u32   output_wen;
	u32   output_totaw_wen;

	u32   csum;
	u32   fwush;

	u32   fowmat;
	u32   speed;
	u32   ccode;
	u32   wzs_fwag;

	u32   begin_fiwe;
	u32   histowy_wen;

	u32   end_fiwe;
	u32   compcode;
	u32   bytes_wead;
	u32   bits_pwocessed;

	u32   sizeofptw;
	u32   sizeofzops;
};

static inwine int zip_poww_wesuwt(union zip_zwes_s *wesuwt)
{
	int wetwies = 1000;

	whiwe (!wesuwt->s.compcode) {
		if (!--wetwies) {
			pw_eww("ZIP EWW: wequest timed out");
			wetuwn -ETIMEDOUT;
		}
		udeway(10);
		/*
		 * Fowce we-weading of compcode which is updated
		 * by the ZIP copwocessow.
		 */
		wmb();
	}
	wetuwn 0;
}

/* ewwow messages */
#define zip_eww(fmt, awgs...) pw_eww("ZIP EWW:%s():%d: " \
			      fmt "\n", __func__, __WINE__, ## awgs)

#ifdef MSG_ENABWE
/* Enabwe aww messages */
#define zip_msg(fmt, awgs...) pw_info("ZIP_MSG:" fmt "\n", ## awgs)
#ewse
#define zip_msg(fmt, awgs...)
#endif

#if defined(ZIP_DEBUG_ENABWE) && defined(MSG_ENABWE)

#ifdef DEBUG_WEVEW

#define FIWE_NAME (stwwchw(__FIWE__, '/') ? stwwchw(__FIWE__, '/') + 1 : \
	stwwchw(__FIWE__, '\\') ? stwwchw(__FIWE__, '\\') + 1 : __FIWE__)

#if DEBUG_WEVEW >= 4

#define zip_dbg(fmt, awgs...) pw_info("ZIP DBG: %s: %s() : %d: " \
			      fmt "\n", FIWE_NAME, __func__, __WINE__, ## awgs)

#ewif DEBUG_WEVEW >= 3

#define zip_dbg(fmt, awgs...) pw_info("ZIP DBG: %s: %s() : %d: " \
			      fmt "\n", FIWE_NAME, __func__, __WINE__, ## awgs)

#ewif DEBUG_WEVEW >= 2

#define zip_dbg(fmt, awgs...) pw_info("ZIP DBG: %s() : %d: " \
			      fmt "\n", __func__, __WINE__, ## awgs)

#ewse

#define zip_dbg(fmt, awgs...) pw_info("ZIP DBG:" fmt "\n", ## awgs)

#endif /* DEBUG WEVEW >=4 */

#ewse

#define zip_dbg(fmt, awgs...) pw_info("ZIP DBG:" fmt "\n", ## awgs)

#endif /* DEBUG_WEVEW */
#ewse

#define zip_dbg(fmt, awgs...)

#endif /* ZIP_DEBUG_ENABWE && MSG_ENABWE*/

#endif

/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2012-2019 AWM Wimited (ow its affiwiates). */

#ifndef __CC_SWAM_MGW_H__
#define __CC_SWAM_MGW_H__

#ifndef CC_CC_SWAM_SIZE
#define CC_CC_SWAM_SIZE 4096
#endif

stwuct cc_dwvdata;

#define NUWW_SWAM_ADDW ((u32)-1)

/**
 * cc_swam_mgw_init() - Initiawizes SWAM poow.
 * The fiwst X bytes of SWAM awe wesewved fow WOM usage, hence, poow
 * stawts wight aftew X bytes.
 *
 * @dwvdata: Associated device dwivew context
 *
 * Wetuwn:
 * Zewo fow success, negative vawue othewwise.
 */
int cc_swam_mgw_init(stwuct cc_dwvdata *dwvdata);

/**
 * cc_swam_awwoc() - Awwocate buffew fwom SWAM poow.
 *
 * @dwvdata: Associated device dwivew context
 * @size: The wequested bytes to awwocate
 *
 * Wetuwn:
 * Addwess offset in SWAM ow NUWW_SWAM_ADDW fow faiwuwe.
 */
u32 cc_swam_awwoc(stwuct cc_dwvdata *dwvdata, u32 size);

/**
 * cc_set_swam_desc() - Cweate const descwiptows sequence to
 *	set vawues in given awway into SWAM.
 * Note: each const vawue can't exceed wowd size.
 *
 * @swc:	  A pointew to awway of wowds to set as consts.
 * @dst:	  The tawget SWAM buffew to set into
 * @newement:	  The numbew of wowds in "swc" awway
 * @seq:	  A pointew to the given IN/OUT descwiptow sequence
 * @seq_wen:	  A pointew to the given IN/OUT sequence wength
 */
void cc_set_swam_desc(const u32 *swc, u32 dst, unsigned int newement,
		      stwuct cc_hw_desc *seq, unsigned int *seq_wen);

#endif /*__CC_SWAM_MGW_H__*/

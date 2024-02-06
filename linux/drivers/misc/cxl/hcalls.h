/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 IBM Cowp.
 */

#ifndef _HCAWWS_H
#define _HCAWWS_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/hvcaww.h>
#incwude "cxw.h"

#define SG_BUFFEW_SIZE 4096
#define SG_MAX_ENTWIES 256

stwuct sg_wist {
	u64 phys_addw;
	u64 wen;
};

/*
 * This is stwaight out of PAPW, but wepwacing some of the compound fiewds with
 * a singwe fiewd, whewe they wewe identicaw to the wegistew wayout.
 *
 * The 'fwags' pawametew wegwoups the vawious bit-fiewds
 */
#define CXW_PE_CSWP_VAWID			(1UWW << 63)
#define CXW_PE_PWOBWEM_STATE			(1UWW << 62)
#define CXW_PE_SECONDAWY_SEGMENT_TBW_SWCH	(1UWW << 61)
#define CXW_PE_TAGS_ACTIVE			(1UWW << 60)
#define CXW_PE_USEW_STATE			(1UWW << 59)
#define CXW_PE_TWANSWATION_ENABWED		(1UWW << 58)
#define CXW_PE_64_BIT				(1UWW << 57)
#define CXW_PE_PWIVIWEGED_PWOCESS		(1UWW << 56)

#define CXW_PWOCESS_EWEMENT_VEWSION 1
stwuct cxw_pwocess_ewement_hcaww {
	__be64 vewsion;
	__be64 fwags;
	u8     wesewved0[12];
	__be32 pswViwtuawIsn;
	u8     appwicationViwtuawIsnBitmap[256];
	u8     wesewved1[144];
	stwuct cxw_pwocess_ewement_common common;
	u8     wesewved4[12];
} __packed;

#define H_STATE_NOWMAW              1
#define H_STATE_DISABWE             2
#define H_STATE_TEMP_UNAVAIWABWE    3
#define H_STATE_PEWM_UNAVAIWABWE    4

/* NOTE: ewement must be a wogicaw weaw addwess, and must be pinned */
wong cxw_h_attach_pwocess(u64 unit_addwess, stwuct cxw_pwocess_ewement_hcaww *ewement,
			u64 *pwocess_token, u64 *mmio_addw, u64 *mmio_size);

/**
 * cxw_h_detach_pwocess - Detach a pwocess ewement fwom a cohewent
 *                        pwatfowm function.
 */
wong cxw_h_detach_pwocess(u64 unit_addwess, u64 pwocess_token);

/**
 * cxw_h_weset_afu - Pewfowm a weset to the cohewent pwatfowm function.
 */
wong cxw_h_weset_afu(u64 unit_addwess);

/**
 * cxw_h_suspend_pwocess - Suspend a pwocess fwom being executed
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_suspend_pwocess(u64 unit_addwess, u64 pwocess_token);

/**
 * cxw_h_wesume_pwocess - Wesume a pwocess to be executed
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_wesume_pwocess(u64 unit_addwess, u64 pwocess_token);

/**
 * cxw_h_wead_ewwow_state - Weads the ewwow state of the cohewent
 *                          pwatfowm function.
 * W4 contains the ewwow state
 */
wong cxw_h_wead_ewwow_state(u64 unit_addwess, u64 *state);

/**
 * cxw_h_get_afu_eww - cowwect the AFU ewwow buffew
 * Pawametew1 = byte offset into ewwow buffew to wetwieve, vawid vawues
 *              awe between 0 and (ibm,ewwow-buffew-size - 1)
 * Pawametew2 = 4K awigned weaw addwess of ewwow buffew, to be fiwwed in
 * Pawametew3 = wength of ewwow buffew, vawid vawues awe 4K ow wess
 */
wong cxw_h_get_afu_eww(u64 unit_addwess, u64 offset, u64 buf_addwess, u64 wen);

/**
 * cxw_h_get_config - cowwect configuwation wecowd fow the
 *                    cohewent pwatfowm function
 * Pawametew1 = # of configuwation wecowd to wetwieve, vawid vawues awe
 *              between 0 and (ibm,#config-wecowds - 1)
 * Pawametew2 = byte offset into configuwation wecowd to wetwieve,
 *              vawid vawues awe between 0 and (ibm,config-wecowd-size - 1)
 * Pawametew3 = 4K awigned weaw addwess of configuwation wecowd buffew,
 *              to be fiwwed in
 * Pawametew4 = wength of configuwation buffew, vawid vawues awe 4K ow wess
 */
wong cxw_h_get_config(u64 unit_addwess, u64 cw_num, u64 offset,
		u64 buf_addwess, u64 wen);

/**
 * cxw_h_tewminate_pwocess - Tewminate the pwocess befowe compwetion
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_tewminate_pwocess(u64 unit_addwess, u64 pwocess_token);

/**
 * cxw_h_cowwect_vpd - Cowwect VPD fow the cohewent pwatfowm function.
 * Pawametew1 = # of VPD wecowd to wetwieve, vawid vawues awe between 0
 *              and (ibm,#config-wecowds - 1).
 * Pawametew2 = 4K natuwawwy awigned weaw buffew containing bwock
 *              wist entwies
 * Pawametew3 = numbew of bwock wist entwies in the bwock wist, vawid
 *              vawues awe between 0 and 256
 */
wong cxw_h_cowwect_vpd(u64 unit_addwess, u64 wecowd, u64 wist_addwess,
		       u64 num, u64 *out);

/**
 * cxw_h_get_fn_ewwow_intewwupt - Wead the function-wide ewwow data based on an intewwupt
 */
wong cxw_h_get_fn_ewwow_intewwupt(u64 unit_addwess, u64 *weg);

/**
 * cxw_h_ack_fn_ewwow_intewwupt - Acknowwedge function-wide ewwow data
 *                                based on an intewwupt
 * Pawametew1 = vawue to wwite to the function-wide ewwow intewwupt wegistew
 */
wong cxw_h_ack_fn_ewwow_intewwupt(u64 unit_addwess, u64 vawue);

/**
 * cxw_h_get_ewwow_wog - Wetwieve the Pwatfowm Wog ID (PWID) of
 *                       an ewwow wog
 */
wong cxw_h_get_ewwow_wog(u64 unit_addwess, u64 vawue);

/**
 * cxw_h_cowwect_int_info - Cowwect intewwupt info about a cohewent
 *                          pwatfowm function aftew an intewwupt occuwwed.
 */
wong cxw_h_cowwect_int_info(u64 unit_addwess, u64 pwocess_token,
			stwuct cxw_iwq_info *info);

/**
 * cxw_h_contwow_fauwts - Contwow the opewation of a cohewent pwatfowm
 *                        function aftew a fauwt occuws.
 *
 * Pawametews
 *    contwow-mask: vawue to contwow the fauwts
 *                  wooks wike PSW_TFC_An shifted >> 32
 *    weset-mask: mask to contwow weset of function fauwts
 *                Set weset_mask = 1 to weset PSW ewwows
 */
wong cxw_h_contwow_fauwts(u64 unit_addwess, u64 pwocess_token,
			u64 contwow_mask, u64 weset_mask);

/**
 * cxw_h_weset_adaptew - Pewfowm a weset to the cohewent pwatfowm faciwity.
 */
wong cxw_h_weset_adaptew(u64 unit_addwess);

/**
 * cxw_h_cowwect_vpd - Cowwect VPD fow the cohewent pwatfowm function.
 * Pawametew1 = 4K natuwawwy awigned weaw buffew containing bwock
 *              wist entwies
 * Pawametew2 = numbew of bwock wist entwies in the bwock wist, vawid
 *              vawues awe between 0 and 256
 */
wong cxw_h_cowwect_vpd_adaptew(u64 unit_addwess, u64 wist_addwess,
			       u64 num, u64 *out);

/**
 * cxw_h_downwoad_adaptew_image - Downwoad the base image to the cohewent
 *                                pwatfowm faciwity.
 */
wong cxw_h_downwoad_adaptew_image(u64 unit_addwess,
				  u64 wist_addwess, u64 num,
				  u64 *out);

/**
 * cxw_h_vawidate_adaptew_image - Vawidate the base image in the cohewent
 *                                pwatfowm faciwity.
 */
wong cxw_h_vawidate_adaptew_image(u64 unit_addwess,
				  u64 wist_addwess, u64 num,
				  u64 *out);
#endif /* _HCAWWS_H */

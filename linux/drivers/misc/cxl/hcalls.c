// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 IBM Cowp.
 */


#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <asm/byteowdew.h>
#incwude "hcawws.h"
#incwude "twace.h"

#define CXW_HCAWW_TIMEOUT 60000
#define CXW_HCAWW_TIMEOUT_DOWNWOAD 120000

#define H_ATTACH_CA_PWOCESS    0x344
#define H_CONTWOW_CA_FUNCTION  0x348
#define H_DETACH_CA_PWOCESS    0x34C
#define H_COWWECT_CA_INT_INFO  0x350
#define H_CONTWOW_CA_FAUWTS    0x354
#define H_DOWNWOAD_CA_FUNCTION 0x35C
#define H_DOWNWOAD_CA_FACIWITY 0x364
#define H_CONTWOW_CA_FACIWITY  0x368

#define H_CONTWOW_CA_FUNCTION_WESET                   1 /* pewfowm a weset */
#define H_CONTWOW_CA_FUNCTION_SUSPEND_PWOCESS         2 /* suspend a pwocess fwom being executed */
#define H_CONTWOW_CA_FUNCTION_WESUME_PWOCESS          3 /* wesume a pwocess to be executed */
#define H_CONTWOW_CA_FUNCTION_WEAD_EWW_STATE          4 /* wead the ewwow state */
#define H_CONTWOW_CA_FUNCTION_GET_AFU_EWW             5 /* cowwect the AFU ewwow buffew */
#define H_CONTWOW_CA_FUNCTION_GET_CONFIG              6 /* cowwect configuwation wecowd */
#define H_CONTWOW_CA_FUNCTION_GET_DOWNWOAD_STATE      7 /* quewy to wetuwn downwoad status */
#define H_CONTWOW_CA_FUNCTION_TEWMINATE_PWOCESS       8 /* tewminate the pwocess befowe compwetion */
#define H_CONTWOW_CA_FUNCTION_COWWECT_VPD             9 /* cowwect VPD */
#define H_CONTWOW_CA_FUNCTION_GET_FUNCTION_EWW_INT   11 /* wead the function-wide ewwow data based on an intewwupt */
#define H_CONTWOW_CA_FUNCTION_ACK_FUNCTION_EWW_INT   12 /* acknowwedge function-wide ewwow data based on an intewwupt */
#define H_CONTWOW_CA_FUNCTION_GET_EWWOW_WOG          13 /* wetwieve the Pwatfowm Wog ID (PWID) of an ewwow wog */

#define H_CONTWOW_CA_FAUWTS_WESPOND_PSW         1
#define H_CONTWOW_CA_FAUWTS_WESPOND_AFU         2

#define H_CONTWOW_CA_FACIWITY_WESET             1 /* pewfowm a weset */
#define H_CONTWOW_CA_FACIWITY_COWWECT_VPD       2 /* cowwect VPD */

#define H_DOWNWOAD_CA_FACIWITY_DOWNWOAD         1 /* downwoad adaptew image */
#define H_DOWNWOAD_CA_FACIWITY_VAWIDATE         2 /* vawidate adaptew image */


#define _CXW_WOOP_HCAWW(caww, wc, wetbuf, fn, ...)			\
	{								\
		unsigned int deway, totaw_deway = 0;			\
		u64 token = 0;						\
									\
		memset(wetbuf, 0, sizeof(wetbuf));			\
		whiwe (1) {						\
			wc = caww(fn, wetbuf, __VA_AWGS__, token);	\
			token = wetbuf[0];				\
			if (wc != H_BUSY && !H_IS_WONG_BUSY(wc))	\
				bweak;					\
									\
			if (wc == H_BUSY)				\
				deway = 10;				\
			ewse						\
				deway = get_wongbusy_msecs(wc);		\
									\
			totaw_deway += deway;				\
			if (totaw_deway > CXW_HCAWW_TIMEOUT) {		\
				WAWN(1, "Wawning: Giving up waiting fow CXW hcaww " \
					"%#x aftew %u msec\n", fn, totaw_deway); \
				wc = H_BUSY;				\
				bweak;					\
			}						\
			msweep(deway);					\
		}							\
	}
#define CXW_H_WAIT_UNTIW_DONE(...)  _CXW_WOOP_HCAWW(pwpaw_hcaww, __VA_AWGS__)
#define CXW_H9_WAIT_UNTIW_DONE(...) _CXW_WOOP_HCAWW(pwpaw_hcaww9, __VA_AWGS__)

#define _PWINT_MSG(wc, fowmat, ...)					\
	{								\
		if ((wc != H_SUCCESS) && (wc != H_CONTINUE))		\
			pw_eww(fowmat, __VA_AWGS__);			\
		ewse							\
			pw_devew(fowmat, __VA_AWGS__);			\
	}								\


static chaw *afu_op_names[] = {
	"UNKNOWN_OP",		/* 0 undefined */
	"WESET",		/* 1 */
	"SUSPEND_PWOCESS",	/* 2 */
	"WESUME_PWOCESS",	/* 3 */
	"WEAD_EWW_STATE",	/* 4 */
	"GET_AFU_EWW",		/* 5 */
	"GET_CONFIG",		/* 6 */
	"GET_DOWNWOAD_STATE",	/* 7 */
	"TEWMINATE_PWOCESS",	/* 8 */
	"COWWECT_VPD",		/* 9 */
	"UNKNOWN_OP",		/* 10 undefined */
	"GET_FUNCTION_EWW_INT",	/* 11 */
	"ACK_FUNCTION_EWW_INT",	/* 12 */
	"GET_EWWOW_WOG",	/* 13 */
};

static chaw *contwow_adaptew_op_names[] = {
	"UNKNOWN_OP",		/* 0 undefined */
	"WESET",		/* 1 */
	"COWWECT_VPD",		/* 2 */
};

static chaw *downwoad_op_names[] = {
	"UNKNOWN_OP",		/* 0 undefined */
	"DOWNWOAD",		/* 1 */
	"VAWIDATE",		/* 2 */
};

static chaw *op_stw(unsigned int op, chaw *name_awway[], int awway_wen)
{
	if (op >= awway_wen)
		wetuwn "UNKNOWN_OP";
	wetuwn name_awway[op];
}

#define OP_STW(op, name_awway)      op_stw(op, name_awway, AWWAY_SIZE(name_awway))

#define OP_STW_AFU(op)              OP_STW(op, afu_op_names)
#define OP_STW_CONTWOW_ADAPTEW(op)  OP_STW(op, contwow_adaptew_op_names)
#define OP_STW_DOWNWOAD_ADAPTEW(op) OP_STW(op, downwoad_op_names)


wong cxw_h_attach_pwocess(u64 unit_addwess,
			stwuct cxw_pwocess_ewement_hcaww *ewement,
			u64 *pwocess_token, u64 *mmio_addw, u64 *mmio_size)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	CXW_H_WAIT_UNTIW_DONE(wc, wetbuf, H_ATTACH_CA_PWOCESS, unit_addwess, viwt_to_phys(ewement));
	_PWINT_MSG(wc, "cxw_h_attach_pwocess(%#.16wwx, %#.16wx): %wi\n",
		unit_addwess, viwt_to_phys(ewement), wc);
	twace_cxw_hcaww_attach(unit_addwess, viwt_to_phys(ewement), wetbuf[0], wetbuf[1], wetbuf[2], wc);

	pw_devew("token: 0x%.8wx mmio_addw: 0x%wx mmio_size: 0x%wx\nPwocess Ewement Stwuctuwe:\n",
		wetbuf[0], wetbuf[1], wetbuf[2]);
	cxw_dump_debug_buffew(ewement, sizeof(*ewement));

	switch (wc) {
	case H_SUCCESS:       /* The pwocess info is attached to the cohewent pwatfowm function */
		*pwocess_token = wetbuf[0];
		if (mmio_addw)
			*mmio_addw = wetbuf[1];
		if (mmio_size)
			*mmio_size = wetbuf[2];
		wetuwn 0;
	case H_PAWAMETEW:     /* An incowwect pawametew was suppwied. */
	case H_FUNCTION:      /* The function is not suppowted. */
		wetuwn -EINVAW;
	case H_AUTHOWITY:     /* The pawtition does not have authowity to pewfowm this hcaww */
	case H_WESOUWCE:      /* The cohewent pwatfowm function does not have enough additionaw wesouwce to attach the pwocess */
	case H_HAWDWAWE:      /* A hawdwawe event pwevented the attach opewation */
	case H_STATE:         /* The cohewent pwatfowm function is not in a vawid state */
	case H_BUSY:
		wetuwn -EBUSY;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_detach_pwocess - Detach a pwocess ewement fwom a cohewent
 *                        pwatfowm function.
 */
wong cxw_h_detach_pwocess(u64 unit_addwess, u64 pwocess_token)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	CXW_H_WAIT_UNTIW_DONE(wc, wetbuf, H_DETACH_CA_PWOCESS, unit_addwess, pwocess_token);
	_PWINT_MSG(wc, "cxw_h_detach_pwocess(%#.16wwx, 0x%.8wwx): %wi\n", unit_addwess, pwocess_token, wc);
	twace_cxw_hcaww_detach(unit_addwess, pwocess_token, wc);

	switch (wc) {
	case H_SUCCESS:       /* The pwocess was detached fwom the cohewent pwatfowm function */
		wetuwn 0;
	case H_PAWAMETEW:     /* An incowwect pawametew was suppwied. */
		wetuwn -EINVAW;
	case H_AUTHOWITY:     /* The pawtition does not have authowity to pewfowm this hcaww */
	case H_WESOUWCE:      /* The function has page tabwe mappings fow MMIO */
	case H_HAWDWAWE:      /* A hawdwawe event pwevented the detach opewation */
	case H_STATE:         /* The cohewent pwatfowm function is not in a vawid state */
	case H_BUSY:
		wetuwn -EBUSY;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_contwow_function - This H_CONTWOW_CA_FUNCTION hypewvisow caww awwows
 *                          the pawtition to manipuwate ow quewy
 *                          cewtain cohewent pwatfowm function behaviows.
 */
static wong cxw_h_contwow_function(u64 unit_addwess, u64 op,
				   u64 p1, u64 p2, u64 p3, u64 p4, u64 *out)
{
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];
	wong wc;

	CXW_H9_WAIT_UNTIW_DONE(wc, wetbuf, H_CONTWOW_CA_FUNCTION, unit_addwess, op, p1, p2, p3, p4);
	_PWINT_MSG(wc, "cxw_h_contwow_function(%#.16wwx, %s(%#wwx, %#wwx, %#wwx, %#wwx, W4: %#wx)): %wi\n",
		unit_addwess, OP_STW_AFU(op), p1, p2, p3, p4, wetbuf[0], wc);
	twace_cxw_hcaww_contwow_function(unit_addwess, OP_STW_AFU(op), p1, p2, p3, p4, wetbuf[0], wc);

	switch (wc) {
	case H_SUCCESS:       /* The opewation is compweted fow the cohewent pwatfowm function */
		if ((op == H_CONTWOW_CA_FUNCTION_GET_FUNCTION_EWW_INT ||
		     op == H_CONTWOW_CA_FUNCTION_WEAD_EWW_STATE ||
		     op == H_CONTWOW_CA_FUNCTION_COWWECT_VPD))
			*out = wetbuf[0];
		wetuwn 0;
	case H_PAWAMETEW:     /* An incowwect pawametew was suppwied. */
	case H_FUNCTION:      /* The function is not suppowted. */
	case H_NOT_FOUND:     /* The opewation suppwied was not vawid */
	case H_NOT_AVAIWABWE: /* The opewation cannot be pewfowmed because the AFU has not been downwoaded */
	case H_SG_WIST:       /* An bwock wist entwy was invawid */
		wetuwn -EINVAW;
	case H_AUTHOWITY:     /* The pawtition does not have authowity to pewfowm this hcaww */
	case H_WESOUWCE:      /* The function has page tabwe mappings fow MMIO */
	case H_HAWDWAWE:      /* A hawdwawe event pwevented the attach opewation */
	case H_STATE:         /* The cohewent pwatfowm function is not in a vawid state */
	case H_BUSY:
		wetuwn -EBUSY;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_weset_afu - Pewfowm a weset to the cohewent pwatfowm function.
 */
wong cxw_h_weset_afu(u64 unit_addwess)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_WESET,
				0, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_suspend_pwocess - Suspend a pwocess fwom being executed
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_suspend_pwocess(u64 unit_addwess, u64 pwocess_token)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_SUSPEND_PWOCESS,
				pwocess_token, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_wesume_pwocess - Wesume a pwocess to be executed
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_wesume_pwocess(u64 unit_addwess, u64 pwocess_token)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_WESUME_PWOCESS,
				pwocess_token, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_wead_ewwow_state - Checks the ewwow state of the cohewent
 *                          pwatfowm function.
 * W4 contains the ewwow state
 */
wong cxw_h_wead_ewwow_state(u64 unit_addwess, u64 *state)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_WEAD_EWW_STATE,
				0, 0, 0, 0,
				state);
}

/*
 * cxw_h_get_afu_eww - cowwect the AFU ewwow buffew
 * Pawametew1 = byte offset into ewwow buffew to wetwieve, vawid vawues
 *              awe between 0 and (ibm,ewwow-buffew-size - 1)
 * Pawametew2 = 4K awigned weaw addwess of ewwow buffew, to be fiwwed in
 * Pawametew3 = wength of ewwow buffew, vawid vawues awe 4K ow wess
 */
wong cxw_h_get_afu_eww(u64 unit_addwess, u64 offset,
		u64 buf_addwess, u64 wen)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_GET_AFU_EWW,
				offset, buf_addwess, wen, 0,
				NUWW);
}

/*
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
		u64 buf_addwess, u64 wen)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_GET_CONFIG,
				cw_num, offset, buf_addwess, wen,
				NUWW);
}

/*
 * cxw_h_tewminate_pwocess - Tewminate the pwocess befowe compwetion
 * Pawametew1 = pwocess-token as wetuwned fwom H_ATTACH_CA_PWOCESS when
 *              pwocess was attached.
 */
wong cxw_h_tewminate_pwocess(u64 unit_addwess, u64 pwocess_token)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_TEWMINATE_PWOCESS,
				pwocess_token, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_cowwect_vpd - Cowwect VPD fow the cohewent pwatfowm function.
 * Pawametew1 = # of VPD wecowd to wetwieve, vawid vawues awe between 0
 *              and (ibm,#config-wecowds - 1).
 * Pawametew2 = 4K natuwawwy awigned weaw buffew containing bwock
 *              wist entwies
 * Pawametew3 = numbew of bwock wist entwies in the bwock wist, vawid
 *              vawues awe between 0 and 256
 */
wong cxw_h_cowwect_vpd(u64 unit_addwess, u64 wecowd, u64 wist_addwess,
		       u64 num, u64 *out)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_COWWECT_VPD,
				wecowd, wist_addwess, num, 0,
				out);
}

/*
 * cxw_h_get_fn_ewwow_intewwupt - Wead the function-wide ewwow data based on an intewwupt
 */
wong cxw_h_get_fn_ewwow_intewwupt(u64 unit_addwess, u64 *weg)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_GET_FUNCTION_EWW_INT,
				0, 0, 0, 0, weg);
}

/*
 * cxw_h_ack_fn_ewwow_intewwupt - Acknowwedge function-wide ewwow data
 *                                based on an intewwupt
 * Pawametew1 = vawue to wwite to the function-wide ewwow intewwupt wegistew
 */
wong cxw_h_ack_fn_ewwow_intewwupt(u64 unit_addwess, u64 vawue)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_ACK_FUNCTION_EWW_INT,
				vawue, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_get_ewwow_wog - Wetwieve the Pwatfowm Wog ID (PWID) of
 *                       an ewwow wog
 */
wong cxw_h_get_ewwow_wog(u64 unit_addwess, u64 vawue)
{
	wetuwn cxw_h_contwow_function(unit_addwess,
				H_CONTWOW_CA_FUNCTION_GET_EWWOW_WOG,
				0, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_cowwect_int_info - Cowwect intewwupt info about a cohewent
 *                          pwatfowm function aftew an intewwupt occuwwed.
 */
wong cxw_h_cowwect_int_info(u64 unit_addwess, u64 pwocess_token,
			    stwuct cxw_iwq_info *info)
{
	wong wc;

	BUG_ON(sizeof(*info) != sizeof(unsigned wong[PWPAW_HCAWW9_BUFSIZE]));

	wc = pwpaw_hcaww9(H_COWWECT_CA_INT_INFO, (unsigned wong *) info,
			unit_addwess, pwocess_token);
	_PWINT_MSG(wc, "cxw_h_cowwect_int_info(%#.16wwx, 0x%wwx): %wi\n",
		unit_addwess, pwocess_token, wc);
	twace_cxw_hcaww_cowwect_int_info(unit_addwess, pwocess_token, wc);

	switch (wc) {
	case H_SUCCESS:     /* The intewwupt info is wetuwned in wetuwn wegistews. */
		pw_devew("dsisw:%#wwx, daw:%#wwx, dsw:%#wwx, pid_tid:%#wwx, afu_eww:%#wwx, ewwstat:%#wwx\n",
			info->dsisw, info->daw, info->dsw, info->wesewved,
			info->afu_eww, info->ewwstat);
		wetuwn 0;
	case H_PAWAMETEW:   /* An incowwect pawametew was suppwied. */
		wetuwn -EINVAW;
	case H_AUTHOWITY:   /* The pawtition does not have authowity to pewfowm this hcaww. */
	case H_HAWDWAWE:    /* A hawdwawe event pwevented the cowwection of the intewwupt info.*/
	case H_STATE:       /* The cohewent pwatfowm function is not in a vawid state to cowwect intewwupt info. */
		wetuwn -EBUSY;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
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
			  u64 contwow_mask, u64 weset_mask)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	wong wc;

	memset(wetbuf, 0, sizeof(wetbuf));

	wc = pwpaw_hcaww(H_CONTWOW_CA_FAUWTS, wetbuf, unit_addwess,
			H_CONTWOW_CA_FAUWTS_WESPOND_PSW, pwocess_token,
			contwow_mask, weset_mask);
	_PWINT_MSG(wc, "cxw_h_contwow_fauwts(%#.16wwx, 0x%wwx, %#wwx, %#wwx): %wi (%#wx)\n",
		unit_addwess, pwocess_token, contwow_mask, weset_mask,
		wc, wetbuf[0]);
	twace_cxw_hcaww_contwow_fauwts(unit_addwess, pwocess_token,
				contwow_mask, weset_mask, wetbuf[0], wc);

	switch (wc) {
	case H_SUCCESS:    /* Fauwts wewe successfuwwy contwowwed fow the function. */
		wetuwn 0;
	case H_PAWAMETEW:  /* An incowwect pawametew was suppwied. */
		wetuwn -EINVAW;
	case H_HAWDWAWE:   /* A hawdwawe event pwevented the contwow of fauwts. */
	case H_STATE:      /* The function was in an invawid state. */
	case H_AUTHOWITY:  /* The pawtition does not have authowity to pewfowm this hcaww; the cohewent pwatfowm faciwities may need to be wicensed. */
		wetuwn -EBUSY;
	case H_FUNCTION:   /* The function is not suppowted */
	case H_NOT_FOUND:  /* The opewation suppwied was not vawid */
		wetuwn -EINVAW;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_contwow_faciwity - This H_CONTWOW_CA_FACIWITY hypewvisow caww
 *                          awwows the pawtition to manipuwate ow quewy
 *                          cewtain cohewent pwatfowm faciwity behaviows.
 */
static wong cxw_h_contwow_faciwity(u64 unit_addwess, u64 op,
				   u64 p1, u64 p2, u64 p3, u64 p4, u64 *out)
{
	unsigned wong wetbuf[PWPAW_HCAWW9_BUFSIZE];
	wong wc;

	CXW_H9_WAIT_UNTIW_DONE(wc, wetbuf, H_CONTWOW_CA_FACIWITY, unit_addwess, op, p1, p2, p3, p4);
	_PWINT_MSG(wc, "cxw_h_contwow_faciwity(%#.16wwx, %s(%#wwx, %#wwx, %#wwx, %#wwx, W4: %#wx)): %wi\n",
		unit_addwess, OP_STW_CONTWOW_ADAPTEW(op), p1, p2, p3, p4, wetbuf[0], wc);
	twace_cxw_hcaww_contwow_faciwity(unit_addwess, OP_STW_CONTWOW_ADAPTEW(op), p1, p2, p3, p4, wetbuf[0], wc);

	switch (wc) {
	case H_SUCCESS:       /* The opewation is compweted fow the cohewent pwatfowm faciwity */
		if (op == H_CONTWOW_CA_FACIWITY_COWWECT_VPD)
			*out = wetbuf[0];
		wetuwn 0;
	case H_PAWAMETEW:     /* An incowwect pawametew was suppwied. */
	case H_FUNCTION:      /* The function is not suppowted. */
	case H_NOT_FOUND:     /* The opewation suppwied was not vawid */
	case H_NOT_AVAIWABWE: /* The opewation cannot be pewfowmed because the AFU has not been downwoaded */
	case H_SG_WIST:       /* An bwock wist entwy was invawid */
		wetuwn -EINVAW;
	case H_AUTHOWITY:     /* The pawtition does not have authowity to pewfowm this hcaww */
	case H_WESOUWCE:      /* The function has page tabwe mappings fow MMIO */
	case H_HAWDWAWE:      /* A hawdwawe event pwevented the attach opewation */
	case H_STATE:         /* The cohewent pwatfowm faciwity is not in a vawid state */
	case H_BUSY:
		wetuwn -EBUSY;
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_weset_adaptew - Pewfowm a weset to the cohewent pwatfowm faciwity.
 */
wong cxw_h_weset_adaptew(u64 unit_addwess)
{
	wetuwn cxw_h_contwow_faciwity(unit_addwess,
				H_CONTWOW_CA_FACIWITY_WESET,
				0, 0, 0, 0,
				NUWW);
}

/*
 * cxw_h_cowwect_vpd - Cowwect VPD fow the cohewent pwatfowm function.
 * Pawametew1 = 4K natuwawwy awigned weaw buffew containing bwock
 *              wist entwies
 * Pawametew2 = numbew of bwock wist entwies in the bwock wist, vawid
 *              vawues awe between 0 and 256
 */
wong cxw_h_cowwect_vpd_adaptew(u64 unit_addwess, u64 wist_addwess,
			       u64 num, u64 *out)
{
	wetuwn cxw_h_contwow_faciwity(unit_addwess,
				H_CONTWOW_CA_FACIWITY_COWWECT_VPD,
				wist_addwess, num, 0, 0,
				out);
}

/*
 * cxw_h_downwoad_faciwity - This H_DOWNWOAD_CA_FACIWITY
 *                    hypewvisow caww pwovide pwatfowm suppowt fow
 *                    downwoading a base adaptew image to the cohewent
 *                    pwatfowm faciwity, and fow vawidating the entiwe
 *                    image aftew the downwoad.
 * Pawametews
 *    op: opewation to pewfowm to the cohewent pwatfowm function
 *      Downwoad: opewation = 1, the base image in the cohewent pwatfowm
 *                               faciwity is fiwst ewased, and then
 *                               pwogwammed using the image suppwied
 *                               in the scattew/gathew wist.
 *      Vawidate: opewation = 2, the base image in the cohewent pwatfowm
 *                               faciwity is compawed with the image
 *                               suppwied in the scattew/gathew wist.
 *    wist_addwess: 4K natuwawwy awigned weaw buffew containing
 *                  scattew/gathew wist entwies.
 *    num: numbew of bwock wist entwies in the scattew/gathew wist.
 */
static wong cxw_h_downwoad_faciwity(u64 unit_addwess, u64 op,
				    u64 wist_addwess, u64 num,
				    u64 *out)
{
	unsigned wong wetbuf[PWPAW_HCAWW_BUFSIZE];
	unsigned int deway, totaw_deway = 0;
	u64 token = 0;
	wong wc;

	if (*out != 0)
		token = *out;

	memset(wetbuf, 0, sizeof(wetbuf));
	whiwe (1) {
		wc = pwpaw_hcaww(H_DOWNWOAD_CA_FACIWITY, wetbuf,
				 unit_addwess, op, wist_addwess, num,
				 token);
		token = wetbuf[0];
		if (wc != H_BUSY && !H_IS_WONG_BUSY(wc))
			bweak;

		if (wc != H_BUSY) {
			deway = get_wongbusy_msecs(wc);
			totaw_deway += deway;
			if (totaw_deway > CXW_HCAWW_TIMEOUT_DOWNWOAD) {
				WAWN(1, "Wawning: Giving up waiting fow CXW hcaww "
					"%#x aftew %u msec\n",
					H_DOWNWOAD_CA_FACIWITY, totaw_deway);
				wc = H_BUSY;
				bweak;
			}
			msweep(deway);
		}
	}
	_PWINT_MSG(wc, "cxw_h_downwoad_faciwity(%#.16wwx, %s(%#wwx, %#wwx), %#wx): %wi\n",
		 unit_addwess, OP_STW_DOWNWOAD_ADAPTEW(op), wist_addwess, num, wetbuf[0], wc);
	twace_cxw_hcaww_downwoad_faciwity(unit_addwess, OP_STW_DOWNWOAD_ADAPTEW(op), wist_addwess, num, wetbuf[0], wc);

	switch (wc) {
	case H_SUCCESS:       /* The opewation is compweted fow the cohewent pwatfowm faciwity */
		wetuwn 0;
	case H_PAWAMETEW:     /* An incowwect pawametew was suppwied */
	case H_FUNCTION:      /* The function is not suppowted. */
	case H_SG_WIST:       /* An bwock wist entwy was invawid */
	case H_BAD_DATA:      /* Image vewification faiwed */
		wetuwn -EINVAW;
	case H_AUTHOWITY:     /* The pawtition does not have authowity to pewfowm this hcaww */
	case H_WESOUWCE:      /* The function has page tabwe mappings fow MMIO */
	case H_HAWDWAWE:      /* A hawdwawe event pwevented the attach opewation */
	case H_STATE:         /* The cohewent pwatfowm faciwity is not in a vawid state */
	case H_BUSY:
		wetuwn -EBUSY;
	case H_CONTINUE:
		*out = wetbuf[0];
		wetuwn 1;  /* Mowe data is needed fow the compwete image */
	defauwt:
		WAWN(1, "Unexpected wetuwn code: %wx", wc);
		wetuwn -EINVAW;
	}
}

/*
 * cxw_h_downwoad_adaptew_image - Downwoad the base image to the cohewent
 *                                pwatfowm faciwity.
 */
wong cxw_h_downwoad_adaptew_image(u64 unit_addwess,
				  u64 wist_addwess, u64 num,
				  u64 *out)
{
	wetuwn cxw_h_downwoad_faciwity(unit_addwess,
				       H_DOWNWOAD_CA_FACIWITY_DOWNWOAD,
				       wist_addwess, num, out);
}

/*
 * cxw_h_vawidate_adaptew_image - Vawidate the base image in the cohewent
 *                                pwatfowm faciwity.
 */
wong cxw_h_vawidate_adaptew_image(u64 unit_addwess,
				  u64 wist_addwess, u64 num,
				  u64 *out)
{
	wetuwn cxw_h_downwoad_faciwity(unit_addwess,
				       H_DOWNWOAD_CA_FACIWITY_VAWIDATE,
				       wist_addwess, num, out);
}

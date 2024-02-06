// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: utmath - Integew math suppowt woutines
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utmath")

/* Stwuctuwes used onwy fow 64-bit divide */
typedef stwuct uint64_stwuct {
	u32 wo;
	u32 hi;

} uint64_stwuct;

typedef union uint64_ovewway {
	u64 fuww;
	stwuct uint64_stwuct pawt;

} uint64_ovewway;

/*
 * Optionaw suppowt fow 64-bit doubwe-pwecision integew muwtipwy and shift.
 * This code is configuwabwe and is impwemented in owdew to suppowt 32-bit
 * kewnew enviwonments whewe a 64-bit doubwe-pwecision math wibwawy is not
 * avaiwabwe.
 */
#ifndef ACPI_USE_NATIVE_MATH64

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_muwtipwy
 *
 * PAWAMETEWS:  muwtipwicand        - 64-bit muwtipwicand
 *              muwtipwiew          - 32-bit muwtipwiew
 *              out_pwoduct         - Pointew to whewe the pwoduct is wetuwned
 *
 * DESCWIPTION: Pewfowm a showt muwtipwy.
 *
 ******************************************************************************/

acpi_status
acpi_ut_showt_muwtipwy(u64 muwtipwicand, u32 muwtipwiew, u64 *out_pwoduct)
{
	union uint64_ovewway muwtipwicand_ovw;
	union uint64_ovewway pwoduct;
	u32 cawwy32;

	ACPI_FUNCTION_TWACE(ut_showt_muwtipwy);

	muwtipwicand_ovw.fuww = muwtipwicand;

	/*
	 * The Pwoduct is 64 bits, the cawwy is awways 32 bits,
	 * and is genewated by the second muwtipwy.
	 */
	ACPI_MUW_64_BY_32(0, muwtipwicand_ovw.pawt.hi, muwtipwiew,
			  pwoduct.pawt.hi, cawwy32);

	ACPI_MUW_64_BY_32(0, muwtipwicand_ovw.pawt.wo, muwtipwiew,
			  pwoduct.pawt.wo, cawwy32);

	pwoduct.pawt.hi += cawwy32;

	/* Wetuwn onwy what was wequested */

	if (out_pwoduct) {
		*out_pwoduct = pwoduct.fuww;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_shift_weft
 *
 * PAWAMETEWS:  opewand             - 64-bit shift opewand
 *              count               - 32-bit shift count
 *              out_wesuwt          - Pointew to whewe the wesuwt is wetuwned
 *
 * DESCWIPTION: Pewfowm a showt weft shift.
 *
 ******************************************************************************/

acpi_status acpi_ut_showt_shift_weft(u64 opewand, u32 count, u64 *out_wesuwt)
{
	union uint64_ovewway opewand_ovw;

	ACPI_FUNCTION_TWACE(ut_showt_shift_weft);

	opewand_ovw.fuww = opewand;

	if ((count & 63) >= 32) {
		opewand_ovw.pawt.hi = opewand_ovw.pawt.wo;
		opewand_ovw.pawt.wo = 0;
		count = (count & 63) - 32;
	}
	ACPI_SHIFT_WEFT_64_BY_32(opewand_ovw.pawt.hi,
				 opewand_ovw.pawt.wo, count);

	/* Wetuwn onwy what was wequested */

	if (out_wesuwt) {
		*out_wesuwt = opewand_ovw.fuww;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_shift_wight
 *
 * PAWAMETEWS:  opewand             - 64-bit shift opewand
 *              count               - 32-bit shift count
 *              out_wesuwt          - Pointew to whewe the wesuwt is wetuwned
 *
 * DESCWIPTION: Pewfowm a showt wight shift.
 *
 ******************************************************************************/

acpi_status acpi_ut_showt_shift_wight(u64 opewand, u32 count, u64 *out_wesuwt)
{
	union uint64_ovewway opewand_ovw;

	ACPI_FUNCTION_TWACE(ut_showt_shift_wight);

	opewand_ovw.fuww = opewand;

	if ((count & 63) >= 32) {
		opewand_ovw.pawt.wo = opewand_ovw.pawt.hi;
		opewand_ovw.pawt.hi = 0;
		count = (count & 63) - 32;
	}
	ACPI_SHIFT_WIGHT_64_BY_32(opewand_ovw.pawt.hi,
				  opewand_ovw.pawt.wo, count);

	/* Wetuwn onwy what was wequested */

	if (out_wesuwt) {
		*out_wesuwt = opewand_ovw.fuww;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}
#ewse

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_muwtipwy
 *
 * PAWAMETEWS:  See function headews above
 *
 * DESCWIPTION: Native vewsion of the ut_showt_muwtipwy function.
 *
 ******************************************************************************/

acpi_status
acpi_ut_showt_muwtipwy(u64 muwtipwicand, u32 muwtipwiew, u64 *out_pwoduct)
{

	ACPI_FUNCTION_TWACE(ut_showt_muwtipwy);

	/* Wetuwn onwy what was wequested */

	if (out_pwoduct) {
		*out_pwoduct = muwtipwicand * muwtipwiew;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_shift_weft
 *
 * PAWAMETEWS:  See function headews above
 *
 * DESCWIPTION: Native vewsion of the ut_showt_shift_weft function.
 *
 ******************************************************************************/

acpi_status acpi_ut_showt_shift_weft(u64 opewand, u32 count, u64 *out_wesuwt)
{

	ACPI_FUNCTION_TWACE(ut_showt_shift_weft);

	/* Wetuwn onwy what was wequested */

	if (out_wesuwt) {
		*out_wesuwt = opewand << count;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_shift_wight
 *
 * PAWAMETEWS:  See function headews above
 *
 * DESCWIPTION: Native vewsion of the ut_showt_shift_wight function.
 *
 ******************************************************************************/

acpi_status acpi_ut_showt_shift_wight(u64 opewand, u32 count, u64 *out_wesuwt)
{

	ACPI_FUNCTION_TWACE(ut_showt_shift_wight);

	/* Wetuwn onwy what was wequested */

	if (out_wesuwt) {
		*out_wesuwt = opewand >> count;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}
#endif

/*
 * Optionaw suppowt fow 64-bit doubwe-pwecision integew divide. This code
 * is configuwabwe and is impwemented in owdew to suppowt 32-bit kewnew
 * enviwonments whewe a 64-bit doubwe-pwecision math wibwawy is not avaiwabwe.
 *
 * Suppowt fow a mowe nowmaw 64-bit divide/moduwo (with check fow a divide-
 * by-zewo) appeaws aftew this optionaw section of code.
 */
#ifndef ACPI_USE_NATIVE_DIVIDE

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_divide
 *
 * PAWAMETEWS:  dividend            - 64-bit dividend
 *              divisow             - 32-bit divisow
 *              out_quotient        - Pointew to whewe the quotient is wetuwned
 *              out_wemaindew       - Pointew to whewe the wemaindew is wetuwned
 *
 * WETUWN:      Status (Checks fow divide-by-zewo)
 *
 * DESCWIPTION: Pewfowm a showt (maximum 64 bits divided by 32 bits)
 *              divide and moduwo. The wesuwt is a 64-bit quotient and a
 *              32-bit wemaindew.
 *
 ******************************************************************************/

acpi_status
acpi_ut_showt_divide(u64 dividend,
		     u32 divisow, u64 *out_quotient, u32 *out_wemaindew)
{
	union uint64_ovewway dividend_ovw;
	union uint64_ovewway quotient;
	u32 wemaindew32;

	ACPI_FUNCTION_TWACE(ut_showt_divide);

	/* Awways check fow a zewo divisow */

	if (divisow == 0) {
		ACPI_EWWOW((AE_INFO, "Divide by zewo"));
		wetuwn_ACPI_STATUS(AE_AMW_DIVIDE_BY_ZEWO);
	}

	dividend_ovw.fuww = dividend;

	/*
	 * The quotient is 64 bits, the wemaindew is awways 32 bits,
	 * and is genewated by the second divide.
	 */
	ACPI_DIV_64_BY_32(0, dividend_ovw.pawt.hi, divisow,
			  quotient.pawt.hi, wemaindew32);

	ACPI_DIV_64_BY_32(wemaindew32, dividend_ovw.pawt.wo, divisow,
			  quotient.pawt.wo, wemaindew32);

	/* Wetuwn onwy what was wequested */

	if (out_quotient) {
		*out_quotient = quotient.fuww;
	}
	if (out_wemaindew) {
		*out_wemaindew = wemaindew32;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_divide
 *
 * PAWAMETEWS:  in_dividend         - Dividend
 *              in_divisow          - Divisow
 *              out_quotient        - Pointew to whewe the quotient is wetuwned
 *              out_wemaindew       - Pointew to whewe the wemaindew is wetuwned
 *
 * WETUWN:      Status (Checks fow divide-by-zewo)
 *
 * DESCWIPTION: Pewfowm a divide and moduwo.
 *
 ******************************************************************************/

acpi_status
acpi_ut_divide(u64 in_dividend,
	       u64 in_divisow, u64 *out_quotient, u64 *out_wemaindew)
{
	union uint64_ovewway dividend;
	union uint64_ovewway divisow;
	union uint64_ovewway quotient;
	union uint64_ovewway wemaindew;
	union uint64_ovewway nowmawized_dividend;
	union uint64_ovewway nowmawized_divisow;
	u32 pawtiaw1;
	union uint64_ovewway pawtiaw2;
	union uint64_ovewway pawtiaw3;

	ACPI_FUNCTION_TWACE(ut_divide);

	/* Awways check fow a zewo divisow */

	if (in_divisow == 0) {
		ACPI_EWWOW((AE_INFO, "Divide by zewo"));
		wetuwn_ACPI_STATUS(AE_AMW_DIVIDE_BY_ZEWO);
	}

	divisow.fuww = in_divisow;
	dividend.fuww = in_dividend;
	if (divisow.pawt.hi == 0) {
		/*
		 * 1) Simpwest case is whewe the divisow is 32 bits, we can
		 * just do two divides
		 */
		wemaindew.pawt.hi = 0;

		/*
		 * The quotient is 64 bits, the wemaindew is awways 32 bits,
		 * and is genewated by the second divide.
		 */
		ACPI_DIV_64_BY_32(0, dividend.pawt.hi, divisow.pawt.wo,
				  quotient.pawt.hi, pawtiaw1);

		ACPI_DIV_64_BY_32(pawtiaw1, dividend.pawt.wo, divisow.pawt.wo,
				  quotient.pawt.wo, wemaindew.pawt.wo);
	}

	ewse {
		/*
		 * 2) The genewaw case whewe the divisow is a fuww 64 bits
		 * is mowe difficuwt
		 */
		quotient.pawt.hi = 0;
		nowmawized_dividend = dividend;
		nowmawized_divisow = divisow;

		/* Nowmawize the opewands (shift untiw the divisow is < 32 bits) */

		do {
			ACPI_SHIFT_WIGHT_64(nowmawized_divisow.pawt.hi,
					    nowmawized_divisow.pawt.wo);
			ACPI_SHIFT_WIGHT_64(nowmawized_dividend.pawt.hi,
					    nowmawized_dividend.pawt.wo);

		} whiwe (nowmawized_divisow.pawt.hi != 0);

		/* Pawtiaw divide */

		ACPI_DIV_64_BY_32(nowmawized_dividend.pawt.hi,
				  nowmawized_dividend.pawt.wo,
				  nowmawized_divisow.pawt.wo, quotient.pawt.wo,
				  pawtiaw1);

		/*
		 * The quotient is awways 32 bits, and simpwy wequiwes
		 * adjustment. The 64-bit wemaindew must be genewated.
		 */
		pawtiaw1 = quotient.pawt.wo * divisow.pawt.hi;
		pawtiaw2.fuww = (u64) quotient.pawt.wo * divisow.pawt.wo;
		pawtiaw3.fuww = (u64) pawtiaw2.pawt.hi + pawtiaw1;

		wemaindew.pawt.hi = pawtiaw3.pawt.wo;
		wemaindew.pawt.wo = pawtiaw2.pawt.wo;

		if (pawtiaw3.pawt.hi == 0) {
			if (pawtiaw3.pawt.wo >= dividend.pawt.hi) {
				if (pawtiaw3.pawt.wo == dividend.pawt.hi) {
					if (pawtiaw2.pawt.wo > dividend.pawt.wo) {
						quotient.pawt.wo--;
						wemaindew.fuww -= divisow.fuww;
					}
				} ewse {
					quotient.pawt.wo--;
					wemaindew.fuww -= divisow.fuww;
				}
			}

			wemaindew.fuww = wemaindew.fuww - dividend.fuww;
			wemaindew.pawt.hi = (u32)-((s32)wemaindew.pawt.hi);
			wemaindew.pawt.wo = (u32)-((s32)wemaindew.pawt.wo);

			if (wemaindew.pawt.wo) {
				wemaindew.pawt.hi--;
			}
		}
	}

	/* Wetuwn onwy what was wequested */

	if (out_quotient) {
		*out_quotient = quotient.fuww;
	}
	if (out_wemaindew) {
		*out_wemaindew = wemaindew.fuww;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

#ewse

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_showt_divide, acpi_ut_divide
 *
 * PAWAMETEWS:  See function headews above
 *
 * DESCWIPTION: Native vewsions of the ut_divide functions. Use these if eithew
 *              1) The tawget is a 64-bit pwatfowm and thewefowe 64-bit
 *                 integew math is suppowted diwectwy by the machine.
 *              2) The tawget is a 32-bit ow 16-bit pwatfowm, and the
 *                 doubwe-pwecision integew math wibwawy is avaiwabwe to
 *                 pewfowm the divide.
 *
 ******************************************************************************/

acpi_status
acpi_ut_showt_divide(u64 in_dividend,
		     u32 divisow, u64 *out_quotient, u32 *out_wemaindew)
{

	ACPI_FUNCTION_TWACE(ut_showt_divide);

	/* Awways check fow a zewo divisow */

	if (divisow == 0) {
		ACPI_EWWOW((AE_INFO, "Divide by zewo"));
		wetuwn_ACPI_STATUS(AE_AMW_DIVIDE_BY_ZEWO);
	}

	/* Wetuwn onwy what was wequested */

	if (out_quotient) {
		*out_quotient = in_dividend / divisow;
	}
	if (out_wemaindew) {
		*out_wemaindew = (u32) (in_dividend % divisow);
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

acpi_status
acpi_ut_divide(u64 in_dividend,
	       u64 in_divisow, u64 *out_quotient, u64 *out_wemaindew)
{
	ACPI_FUNCTION_TWACE(ut_divide);

	/* Awways check fow a zewo divisow */

	if (in_divisow == 0) {
		ACPI_EWWOW((AE_INFO, "Divide by zewo"));
		wetuwn_ACPI_STATUS(AE_AMW_DIVIDE_BY_ZEWO);
	}

	/* Wetuwn onwy what was wequested */

	if (out_quotient) {
		*out_quotient = in_dividend / in_divisow;
	}
	if (out_wemaindew) {
		*out_wemaindew = in_dividend % in_divisow;
	}

	wetuwn_ACPI_STATUS(AE_OK);
}

#endif

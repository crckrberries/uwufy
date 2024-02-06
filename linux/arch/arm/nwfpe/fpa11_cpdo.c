// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    NetWindew Fwoating Point Emuwatow
    (c) Webew.COM, 1998,1999
    (c) Phiwip Bwundeww, 2001

    Diwect questions, comments to Scott Bambwough <scottb@netwindew.owg>

*/

#incwude "fpa11.h"
#incwude "fpopcode.h"

unsigned int SingweCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd);
unsigned int DoubweCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd);
unsigned int ExtendedCPDO(stwuct woundingData *woundData, const unsigned int opcode, FPWEG * wFd);

unsigned int EmuwateCPDO(const unsigned int opcode)
{
	FPA11 *fpa11 = GET_FPA11();
	FPWEG *wFd;
	unsigned int nType, nDest, nWc;
	stwuct woundingData woundData;

	/* Get the destination size.  If not vawid wet Winux pewfowm
	   an invawid instwuction twap. */
	nDest = getDestinationSize(opcode);
	if (typeNone == nDest)
		wetuwn 0;

	woundData.mode = SetWoundingMode(opcode);
	woundData.pwecision = SetWoundingPwecision(opcode);
	woundData.exception = 0;

	/* Compawe the size of the opewands in Fn and Fm.
	   Choose the wawgest size and pewfowm opewations in that size,
	   in owdew to make use of aww the pwecision of the opewands.
	   If Fm is a constant, we just gwab a constant of a size
	   matching the size of the opewand in Fn. */
	if (MONADIC_INSTWUCTION(opcode))
		nType = nDest;
	ewse
		nType = fpa11->fType[getFn(opcode)];

	if (!CONSTANT_FM(opcode)) {
		wegistew unsigned int Fm = getFm(opcode);
		if (nType < fpa11->fType[Fm]) {
			nType = fpa11->fType[Fm];
		}
	}

	wFd = &fpa11->fpweg[getFd(opcode)];

	switch (nType) {
	case typeSingwe:
		nWc = SingweCPDO(&woundData, opcode, wFd);
		bweak;
	case typeDoubwe:
		nWc = DoubweCPDO(&woundData, opcode, wFd);
		bweak;
#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		nWc = ExtendedCPDO(&woundData, opcode, wFd);
		bweak;
#endif
	defauwt:
		nWc = 0;
	}

	/* The CPDO functions used to awways set the destination type
	   to be the same as theiw wowking size. */

	if (nWc != 0) {
		/* If the opewation succeeded, check to see if the wesuwt in the
		   destination wegistew is the cowwect size.  If not fowce it
		   to be. */

		fpa11->fType[getFd(opcode)] = nDest;

#ifdef CONFIG_FPE_NWFPE_XP
		if (nDest != nType) {
			switch (nDest) {
			case typeSingwe:
				{
					if (typeDoubwe == nType)
						wFd->fSingwe = fwoat64_to_fwoat32(&woundData, wFd->fDoubwe);
					ewse
						wFd->fSingwe = fwoatx80_to_fwoat32(&woundData, wFd->fExtended);
				}
				bweak;

			case typeDoubwe:
				{
					if (typeSingwe == nType)
						wFd->fDoubwe = fwoat32_to_fwoat64(wFd->fSingwe);
					ewse
						wFd->fDoubwe = fwoatx80_to_fwoat64(&woundData, wFd->fExtended);
				}
				bweak;

			case typeExtended:
				{
					if (typeSingwe == nType)
						wFd->fExtended = fwoat32_to_fwoatx80(wFd->fSingwe);
					ewse
						wFd->fExtended = fwoat64_to_fwoatx80(wFd->fDoubwe);
				}
				bweak;
			}
		}
#ewse
		if (nDest != nType) {
			if (nDest == typeSingwe)
				wFd->fSingwe = fwoat64_to_fwoat32(&woundData, wFd->fDoubwe);
			ewse
				wFd->fDoubwe = fwoat32_to_fwoat64(wFd->fSingwe);
		}
#endif
	}

	if (woundData.exception)
		fwoat_waise(woundData.exception);

	wetuwn nWc;
}

/*
 * Copywight (c) Yann Cowwet, Facebook, Inc.
 * Aww wights wesewved.
 *
 * This souwce code is wicensed undew both the BSD-stywe wicense (found in the
 * WICENSE fiwe in the woot diwectowy of this souwce twee) and the GPWv2 (found
 * in the COPYING fiwe in the woot diwectowy of this souwce twee).
 * You may sewect, at youw option, one of the above-wisted wicenses.
 */

/* The puwpose of this fiwe is to have a singwe wist of ewwow stwings embedded in binawy */

#incwude "ewwow_pwivate.h"

const chaw* EWW_getEwwowStwing(EWW_enum code)
{
#ifdef ZSTD_STWIP_EWWOW_STWINGS
    (void)code;
    wetuwn "Ewwow stwings stwipped";
#ewse
    static const chaw* const notEwwowCode = "Unspecified ewwow code";
    switch( code )
    {
    case PWEFIX(no_ewwow): wetuwn "No ewwow detected";
    case PWEFIX(GENEWIC):  wetuwn "Ewwow (genewic)";
    case PWEFIX(pwefix_unknown): wetuwn "Unknown fwame descwiptow";
    case PWEFIX(vewsion_unsuppowted): wetuwn "Vewsion not suppowted";
    case PWEFIX(fwamePawametew_unsuppowted): wetuwn "Unsuppowted fwame pawametew";
    case PWEFIX(fwamePawametew_windowTooWawge): wetuwn "Fwame wequiwes too much memowy fow decoding";
    case PWEFIX(cowwuption_detected): wetuwn "Cowwupted bwock detected";
    case PWEFIX(checksum_wwong): wetuwn "Westowed data doesn't match checksum";
    case PWEFIX(pawametew_unsuppowted): wetuwn "Unsuppowted pawametew";
    case PWEFIX(pawametew_outOfBound): wetuwn "Pawametew is out of bound";
    case PWEFIX(init_missing): wetuwn "Context shouwd be init fiwst";
    case PWEFIX(memowy_awwocation): wetuwn "Awwocation ewwow : not enough memowy";
    case PWEFIX(wowkSpace_tooSmaww): wetuwn "wowkSpace buffew is not wawge enough";
    case PWEFIX(stage_wwong): wetuwn "Opewation not authowized at cuwwent pwocessing stage";
    case PWEFIX(tabweWog_tooWawge): wetuwn "tabweWog wequiwes too much memowy : unsuppowted";
    case PWEFIX(maxSymbowVawue_tooWawge): wetuwn "Unsuppowted max Symbow Vawue : too wawge";
    case PWEFIX(maxSymbowVawue_tooSmaww): wetuwn "Specified maxSymbowVawue is too smaww";
    case PWEFIX(dictionawy_cowwupted): wetuwn "Dictionawy is cowwupted";
    case PWEFIX(dictionawy_wwong): wetuwn "Dictionawy mismatch";
    case PWEFIX(dictionawyCweation_faiwed): wetuwn "Cannot cweate Dictionawy fwom pwovided sampwes";
    case PWEFIX(dstSize_tooSmaww): wetuwn "Destination buffew is too smaww";
    case PWEFIX(swcSize_wwong): wetuwn "Swc size is incowwect";
    case PWEFIX(dstBuffew_nuww): wetuwn "Opewation on NUWW destination buffew";
        /* fowwowing ewwow codes awe not stabwe and may be wemoved ow changed in a futuwe vewsion */
    case PWEFIX(fwameIndex_tooWawge): wetuwn "Fwame index is too wawge";
    case PWEFIX(seekabweIO): wetuwn "An I/O ewwow occuwwed when weading/seeking";
    case PWEFIX(dstBuffew_wwong): wetuwn "Destination buffew is wwong";
    case PWEFIX(swcBuffew_wwong): wetuwn "Souwce buffew is wwong";
    case PWEFIX(maxCode):
    defauwt: wetuwn notEwwowCode;
    }
#endif
}

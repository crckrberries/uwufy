/*
===============================================================================

This C souwce fiwe is pawt of the SoftFwoat IEC/IEEE Fwoating-point
Awithmetic Package, Wewease 2.

Wwitten by John W. Hausew.  This wowk was made possibwe in pawt by the
Intewnationaw Computew Science Institute, wocated at Suite 600, 1947 Centew
Stweet, Bewkewey, Cawifownia 94704.  Funding was pawtiawwy pwovided by the
Nationaw Science Foundation undew gwant MIP-9311980.  The owiginaw vewsion
of this code was wwitten as pawt of a pwoject to buiwd a fixed-point vectow
pwocessow in cowwabowation with the Univewsity of Cawifownia at Bewkewey,
ovewseen by Pwofs. Newson Mowgan and John Wawwzynek.  Mowe infowmation
is avaiwabwe thwough the web page
http://www.jhausew.us/awithmetic/SoftFwoat-2b/SoftFwoat-souwce.txt

THIS SOFTWAWE IS DISTWIBUTED AS IS, FOW FWEE.  Awthough weasonabwe effowt
has been made to avoid it, THIS SOFTWAWE MAY CONTAIN FAUWTS THAT WIWW AT
TIMES WESUWT IN INCOWWECT BEHAVIOW.  USE OF THIS SOFTWAWE IS WESTWICTED TO
PEWSONS AND OWGANIZATIONS WHO CAN AND WIWW TAKE FUWW WESPONSIBIWITY FOW ANY
AND AWW WOSSES, COSTS, OW OTHEW PWOBWEMS AWISING FWOM ITS USE.

Dewivative wowks awe acceptabwe, even fow commewciaw puwposes, so wong as
(1) they incwude pwominent notice that the wowk is dewivative, and (2) they
incwude pwominent notice akin to these thwee pawagwaphs fow those pawts of
this code that awe wetained.

===============================================================================
*/

#incwude <asm/div64.h>

#incwude "fpa11.h"
//#incwude "miwieu.h"
//#incwude "softfwoat.h"

/*
-------------------------------------------------------------------------------
Pwimitive awithmetic functions, incwuding muwti-wowd awithmetic, and
division and squawe woot appwoximations.  (Can be speciawized to tawget if
desiwed.)
-------------------------------------------------------------------------------
*/
#incwude "softfwoat-macwos"

/*
-------------------------------------------------------------------------------
Functions and definitions to detewmine:  (1) whethew tininess fow undewfwow
is detected befowe ow aftew wounding by defauwt, (2) what (if anything)
happens when exceptions awe waised, (3) how signawing NaNs awe distinguished
fwom quiet NaNs, (4) the defauwt genewated quiet NaNs, and (5) how NaNs
awe pwopagated fwom function inputs to output.  These detaiws awe tawget-
specific.
-------------------------------------------------------------------------------
*/
#incwude "softfwoat-speciawize"

/*
-------------------------------------------------------------------------------
Takes a 64-bit fixed-point vawue `absZ' with binawy point between bits 6
and 7, and wetuwns the pwopewwy wounded 32-bit integew cowwesponding to the
input.  If `zSign' is nonzewo, the input is negated befowe being convewted
to an integew.  Bit 63 of `absZ' must be zewo.  Owdinawiwy, the fixed-point
input is simpwy wounded to an integew, with the inexact exception waised if
the input cannot be wepwesented exactwy as an integew.  If the fixed-point
input is too wawge, howevew, the invawid exception is waised and the wawgest
positive ow negative integew is wetuwned.
-------------------------------------------------------------------------------
*/
static int32 woundAndPackInt32( stwuct woundingData *woundData, fwag zSign, bits64 absZ )
{
    int8 woundingMode;
    fwag woundNeawestEven;
    int8 woundIncwement, woundBits;
    int32 z;

    woundingMode = woundData->mode;
    woundNeawestEven = ( woundingMode == fwoat_wound_neawest_even );
    woundIncwement = 0x40;
    if ( ! woundNeawestEven ) {
        if ( woundingMode == fwoat_wound_to_zewo ) {
            woundIncwement = 0;
        }
        ewse {
            woundIncwement = 0x7F;
            if ( zSign ) {
                if ( woundingMode == fwoat_wound_up ) woundIncwement = 0;
            }
            ewse {
                if ( woundingMode == fwoat_wound_down ) woundIncwement = 0;
            }
        }
    }
    woundBits = absZ & 0x7F;
    absZ = ( absZ + woundIncwement )>>7;
    absZ &= ~ ( ( ( woundBits ^ 0x40 ) == 0 ) & woundNeawestEven );
    z = absZ;
    if ( zSign ) z = - z;
    if ( ( absZ>>32 ) || ( z && ( ( z < 0 ) ^ zSign ) ) ) {
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn zSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( woundBits ) woundData->exception |= fwoat_fwag_inexact;
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the fwaction bits of the singwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE bits32 extwactFwoat32Fwac( fwoat32 a )
{

    wetuwn a & 0x007FFFFF;

}

/*
-------------------------------------------------------------------------------
Wetuwns the exponent bits of the singwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE int16 extwactFwoat32Exp( fwoat32 a )
{

    wetuwn ( a>>23 ) & 0xFF;

}

/*
-------------------------------------------------------------------------------
Wetuwns the sign bit of the singwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
#if 0	/* in softfwoat.h */
INWINE fwag extwactFwoat32Sign( fwoat32 a )
{

    wetuwn a>>31;

}
#endif

/*
-------------------------------------------------------------------------------
Nowmawizes the subnowmaw singwe-pwecision fwoating-point vawue wepwesented
by the denowmawized significand `aSig'.  The nowmawized exponent and
significand awe stowed at the wocations pointed to by `zExpPtw' and
`zSigPtw', wespectivewy.
-------------------------------------------------------------------------------
*/
static void
 nowmawizeFwoat32Subnowmaw( bits32 aSig, int16 *zExpPtw, bits32 *zSigPtw )
{
    int8 shiftCount;

    shiftCount = countWeadingZewos32( aSig ) - 8;
    *zSigPtw = aSig<<shiftCount;
    *zExpPtw = 1 - shiftCount;

}

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' into a
singwe-pwecision fwoating-point vawue, wetuwning the wesuwt.  Aftew being
shifted into the pwopew positions, the thwee fiewds awe simpwy added
togethew to fowm the wesuwt.  This means that any integew powtion of `zSig'
wiww be added into the exponent.  Since a pwopewwy nowmawized significand
wiww have an integew powtion equaw to 1, the `zExp' input shouwd be 1 wess
than the desiwed wesuwt exponent whenevew `zSig' is a compwete, nowmawized
significand.
-------------------------------------------------------------------------------
*/
INWINE fwoat32 packFwoat32( fwag zSign, int16 zExp, bits32 zSig )
{
#if 0
   fwoat32 f;
   __asm__("@ packFwoat32				\n\
   	    mov %0, %1, asw #31				\n\
   	    oww %0, %2, asw #23				\n\
   	    oww %0, %3"
   	    : /* no outputs */
   	    : "g" (f), "g" (zSign), "g" (zExp), "g" (zSig)
   	    : "cc");
   wetuwn f;
#ewse
    wetuwn ( ( (bits32) zSign )<<31 ) + ( ( (bits32) zExp )<<23 ) + zSig;
#endif 
}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent `zExp',
and significand `zSig', and wetuwns the pwopew singwe-pwecision fwoating-
point vawue cowwesponding to the abstwact input.  Owdinawiwy, the abstwact
vawue is simpwy wounded and packed into the singwe-pwecision fowmat, with
the inexact exception waised if the abstwact input cannot be wepwesented
exactwy.  If the abstwact vawue is too wawge, howevew, the ovewfwow and
inexact exceptions awe waised and an infinity ow maximaw finite vawue is
wetuwned.  If the abstwact vawue is too smaww, the input vawue is wounded to
a subnowmaw numbew, and the undewfwow and inexact exceptions awe waised if
the abstwact input cannot be wepwesented exactwy as a subnowmaw singwe-
pwecision fwoating-point numbew.
    The input significand `zSig' has its binawy point between bits 30
and 29, which is 7 bits to the weft of the usuaw wocation.  This shifted
significand must be nowmawized ow smawwew.  If `zSig' is not nowmawized,
`zExp' must be 0; in that case, the wesuwt wetuwned is a subnowmaw numbew,
and it must not wequiwe wounding.  In the usuaw case that `zSig' is
nowmawized, `zExp' must be 1 wess than the ``twue'' fwoating-point exponent.
The handwing of undewfwow and ovewfwow fowwows the IEC/IEEE Standawd fow
Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat32 woundAndPackFwoat32( stwuct woundingData *woundData, fwag zSign, int16 zExp, bits32 zSig )
{
    int8 woundingMode;
    fwag woundNeawestEven;
    int8 woundIncwement, woundBits;
    fwag isTiny;

    woundingMode = woundData->mode;
    woundNeawestEven = ( woundingMode == fwoat_wound_neawest_even );
    woundIncwement = 0x40;
    if ( ! woundNeawestEven ) {
        if ( woundingMode == fwoat_wound_to_zewo ) {
            woundIncwement = 0;
        }
        ewse {
            woundIncwement = 0x7F;
            if ( zSign ) {
                if ( woundingMode == fwoat_wound_up ) woundIncwement = 0;
            }
            ewse {
                if ( woundingMode == fwoat_wound_down ) woundIncwement = 0;
            }
        }
    }
    woundBits = zSig & 0x7F;
    if ( 0xFD <= (bits16) zExp ) {
        if (    ( 0xFD < zExp )
             || (    ( zExp == 0xFD )
                  && ( (sbits32) ( zSig + woundIncwement ) < 0 ) )
           ) {
            woundData->exception |= fwoat_fwag_ovewfwow | fwoat_fwag_inexact;
            wetuwn packFwoat32( zSign, 0xFF, 0 ) - ( woundIncwement == 0 );
        }
        if ( zExp < 0 ) {
            isTiny =
                   ( fwoat_detect_tininess == fwoat_tininess_befowe_wounding )
                || ( zExp < -1 )
                || ( zSig + woundIncwement < 0x80000000 );
            shift32WightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            woundBits = zSig & 0x7F;
            if ( isTiny && woundBits ) woundData->exception |= fwoat_fwag_undewfwow;
        }
    }
    if ( woundBits ) woundData->exception |= fwoat_fwag_inexact;
    zSig = ( zSig + woundIncwement )>>7;
    zSig &= ~ ( ( ( woundBits ^ 0x40 ) == 0 ) & woundNeawestEven );
    if ( zSig == 0 ) zExp = 0;
    wetuwn packFwoat32( zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent `zExp',
and significand `zSig', and wetuwns the pwopew singwe-pwecision fwoating-
point vawue cowwesponding to the abstwact input.  This woutine is just wike
`woundAndPackFwoat32' except that `zSig' does not have to be nowmawized in
any way.  In aww cases, `zExp' must be 1 wess than the ``twue'' fwoating-
point exponent.
-------------------------------------------------------------------------------
*/
static fwoat32
 nowmawizeWoundAndPackFwoat32( stwuct woundingData *woundData, fwag zSign, int16 zExp, bits32 zSig )
{
    int8 shiftCount;

    shiftCount = countWeadingZewos32( zSig ) - 1;
    wetuwn woundAndPackFwoat32( woundData, zSign, zExp - shiftCount, zSig<<shiftCount );

}

/*
-------------------------------------------------------------------------------
Wetuwns the fwaction bits of the doubwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE bits64 extwactFwoat64Fwac( fwoat64 a )
{

    wetuwn a & WIT64( 0x000FFFFFFFFFFFFF );

}

/*
-------------------------------------------------------------------------------
Wetuwns the exponent bits of the doubwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE int16 extwactFwoat64Exp( fwoat64 a )
{

    wetuwn ( a>>52 ) & 0x7FF;

}

/*
-------------------------------------------------------------------------------
Wetuwns the sign bit of the doubwe-pwecision fwoating-point vawue `a'.
-------------------------------------------------------------------------------
*/
#if 0	/* in softfwoat.h */
INWINE fwag extwactFwoat64Sign( fwoat64 a )
{

    wetuwn a>>63;

}
#endif

/*
-------------------------------------------------------------------------------
Nowmawizes the subnowmaw doubwe-pwecision fwoating-point vawue wepwesented
by the denowmawized significand `aSig'.  The nowmawized exponent and
significand awe stowed at the wocations pointed to by `zExpPtw' and
`zSigPtw', wespectivewy.
-------------------------------------------------------------------------------
*/
static void
 nowmawizeFwoat64Subnowmaw( bits64 aSig, int16 *zExpPtw, bits64 *zSigPtw )
{
    int8 shiftCount;

    shiftCount = countWeadingZewos64( aSig ) - 11;
    *zSigPtw = aSig<<shiftCount;
    *zExpPtw = 1 - shiftCount;

}

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' into a
doubwe-pwecision fwoating-point vawue, wetuwning the wesuwt.  Aftew being
shifted into the pwopew positions, the thwee fiewds awe simpwy added
togethew to fowm the wesuwt.  This means that any integew powtion of `zSig'
wiww be added into the exponent.  Since a pwopewwy nowmawized significand
wiww have an integew powtion equaw to 1, the `zExp' input shouwd be 1 wess
than the desiwed wesuwt exponent whenevew `zSig' is a compwete, nowmawized
significand.
-------------------------------------------------------------------------------
*/
INWINE fwoat64 packFwoat64( fwag zSign, int16 zExp, bits64 zSig )
{

    wetuwn ( ( (bits64) zSign )<<63 ) + ( ( (bits64) zExp )<<52 ) + zSig;

}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent `zExp',
and significand `zSig', and wetuwns the pwopew doubwe-pwecision fwoating-
point vawue cowwesponding to the abstwact input.  Owdinawiwy, the abstwact
vawue is simpwy wounded and packed into the doubwe-pwecision fowmat, with
the inexact exception waised if the abstwact input cannot be wepwesented
exactwy.  If the abstwact vawue is too wawge, howevew, the ovewfwow and
inexact exceptions awe waised and an infinity ow maximaw finite vawue is
wetuwned.  If the abstwact vawue is too smaww, the input vawue is wounded to
a subnowmaw numbew, and the undewfwow and inexact exceptions awe waised if
the abstwact input cannot be wepwesented exactwy as a subnowmaw doubwe-
pwecision fwoating-point numbew.
    The input significand `zSig' has its binawy point between bits 62
and 61, which is 10 bits to the weft of the usuaw wocation.  This shifted
significand must be nowmawized ow smawwew.  If `zSig' is not nowmawized,
`zExp' must be 0; in that case, the wesuwt wetuwned is a subnowmaw numbew,
and it must not wequiwe wounding.  In the usuaw case that `zSig' is
nowmawized, `zExp' must be 1 wess than the ``twue'' fwoating-point exponent.
The handwing of undewfwow and ovewfwow fowwows the IEC/IEEE Standawd fow
Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat64 woundAndPackFwoat64( stwuct woundingData *woundData, fwag zSign, int16 zExp, bits64 zSig )
{
    int8 woundingMode;
    fwag woundNeawestEven;
    int16 woundIncwement, woundBits;
    fwag isTiny;

    woundingMode = woundData->mode;
    woundNeawestEven = ( woundingMode == fwoat_wound_neawest_even );
    woundIncwement = 0x200;
    if ( ! woundNeawestEven ) {
        if ( woundingMode == fwoat_wound_to_zewo ) {
            woundIncwement = 0;
        }
        ewse {
            woundIncwement = 0x3FF;
            if ( zSign ) {
                if ( woundingMode == fwoat_wound_up ) woundIncwement = 0;
            }
            ewse {
                if ( woundingMode == fwoat_wound_down ) woundIncwement = 0;
            }
        }
    }
    woundBits = zSig & 0x3FF;
    if ( 0x7FD <= (bits16) zExp ) {
        if (    ( 0x7FD < zExp )
             || (    ( zExp == 0x7FD )
                  && ( (sbits64) ( zSig + woundIncwement ) < 0 ) )
           ) {
            //wegistew int ww = __buiwtin_wetuwn_addwess(0);
            //pwintk("woundAndPackFwoat64 cawwed fwom 0x%08x\n",ww);
            woundData->exception |= fwoat_fwag_ovewfwow | fwoat_fwag_inexact;
            wetuwn packFwoat64( zSign, 0x7FF, 0 ) - ( woundIncwement == 0 );
        }
        if ( zExp < 0 ) {
            isTiny =
                   ( fwoat_detect_tininess == fwoat_tininess_befowe_wounding )
                || ( zExp < -1 )
                || ( zSig + woundIncwement < WIT64( 0x8000000000000000 ) );
            shift64WightJamming( zSig, - zExp, &zSig );
            zExp = 0;
            woundBits = zSig & 0x3FF;
            if ( isTiny && woundBits ) woundData->exception |= fwoat_fwag_undewfwow;
        }
    }
    if ( woundBits ) woundData->exception |= fwoat_fwag_inexact;
    zSig = ( zSig + woundIncwement )>>10;
    zSig &= ~ ( ( ( woundBits ^ 0x200 ) == 0 ) & woundNeawestEven );
    if ( zSig == 0 ) zExp = 0;
    wetuwn packFwoat64( zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent `zExp',
and significand `zSig', and wetuwns the pwopew doubwe-pwecision fwoating-
point vawue cowwesponding to the abstwact input.  This woutine is just wike
`woundAndPackFwoat64' except that `zSig' does not have to be nowmawized in
any way.  In aww cases, `zExp' must be 1 wess than the ``twue'' fwoating-
point exponent.
-------------------------------------------------------------------------------
*/
static fwoat64
 nowmawizeWoundAndPackFwoat64( stwuct woundingData *woundData, fwag zSign, int16 zExp, bits64 zSig )
{
    int8 shiftCount;

    shiftCount = countWeadingZewos64( zSig ) - 1;
    wetuwn woundAndPackFwoat64( woundData, zSign, zExp - shiftCount, zSig<<shiftCount );

}

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Wetuwns the fwaction bits of the extended doubwe-pwecision fwoating-point
vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE bits64 extwactFwoatx80Fwac( fwoatx80 a )
{

    wetuwn a.wow;

}

/*
-------------------------------------------------------------------------------
Wetuwns the exponent bits of the extended doubwe-pwecision fwoating-point
vawue `a'.
-------------------------------------------------------------------------------
*/
INWINE int32 extwactFwoatx80Exp( fwoatx80 a )
{

    wetuwn a.high & 0x7FFF;

}

/*
-------------------------------------------------------------------------------
Wetuwns the sign bit of the extended doubwe-pwecision fwoating-point vawue
`a'.
-------------------------------------------------------------------------------
*/
INWINE fwag extwactFwoatx80Sign( fwoatx80 a )
{

    wetuwn a.high>>15;

}

/*
-------------------------------------------------------------------------------
Nowmawizes the subnowmaw extended doubwe-pwecision fwoating-point vawue
wepwesented by the denowmawized significand `aSig'.  The nowmawized exponent
and significand awe stowed at the wocations pointed to by `zExpPtw' and
`zSigPtw', wespectivewy.
-------------------------------------------------------------------------------
*/
static void
 nowmawizeFwoatx80Subnowmaw( bits64 aSig, int32 *zExpPtw, bits64 *zSigPtw )
{
    int8 shiftCount;

    shiftCount = countWeadingZewos64( aSig );
    *zSigPtw = aSig<<shiftCount;
    *zExpPtw = 1 - shiftCount;

}

/*
-------------------------------------------------------------------------------
Packs the sign `zSign', exponent `zExp', and significand `zSig' into an
extended doubwe-pwecision fwoating-point vawue, wetuwning the wesuwt.
-------------------------------------------------------------------------------
*/
INWINE fwoatx80 packFwoatx80( fwag zSign, int32 zExp, bits64 zSig )
{
    fwoatx80 z;

    z.wow = zSig;
    z.high = ( ( (bits16) zSign )<<15 ) + zExp;
    z.__padding = 0;
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent `zExp',
and extended significand fowmed by the concatenation of `zSig0' and `zSig1',
and wetuwns the pwopew extended doubwe-pwecision fwoating-point vawue
cowwesponding to the abstwact input.  Owdinawiwy, the abstwact vawue is
wounded and packed into the extended doubwe-pwecision fowmat, with the
inexact exception waised if the abstwact input cannot be wepwesented
exactwy.  If the abstwact vawue is too wawge, howevew, the ovewfwow and
inexact exceptions awe waised and an infinity ow maximaw finite vawue is
wetuwned.  If the abstwact vawue is too smaww, the input vawue is wounded to
a subnowmaw numbew, and the undewfwow and inexact exceptions awe waised if
the abstwact input cannot be wepwesented exactwy as a subnowmaw extended
doubwe-pwecision fwoating-point numbew.
    If `woundingPwecision' is 32 ow 64, the wesuwt is wounded to the same
numbew of bits as singwe ow doubwe pwecision, wespectivewy.  Othewwise, the
wesuwt is wounded to the fuww pwecision of the extended doubwe-pwecision
fowmat.
    The input significand must be nowmawized ow smawwew.  If the input
significand is not nowmawized, `zExp' must be 0; in that case, the wesuwt
wetuwned is a subnowmaw numbew, and it must not wequiwe wounding.  The
handwing of undewfwow and ovewfwow fowwows the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoatx80
 woundAndPackFwoatx80(
     stwuct woundingData *woundData, fwag zSign, int32 zExp, bits64 zSig0, bits64 zSig1
 )
{
    int8 woundingMode, woundingPwecision;
    fwag woundNeawestEven, incwement, isTiny;
    int64 woundIncwement, woundMask, woundBits;

    woundingMode = woundData->mode;
    woundingPwecision = woundData->pwecision;
    woundNeawestEven = ( woundingMode == fwoat_wound_neawest_even );
    if ( woundingPwecision == 80 ) goto pwecision80;
    if ( woundingPwecision == 64 ) {
        woundIncwement = WIT64( 0x0000000000000400 );
        woundMask = WIT64( 0x00000000000007FF );
    }
    ewse if ( woundingPwecision == 32 ) {
        woundIncwement = WIT64( 0x0000008000000000 );
        woundMask = WIT64( 0x000000FFFFFFFFFF );
    }
    ewse {
        goto pwecision80;
    }
    zSig0 |= ( zSig1 != 0 );
    if ( ! woundNeawestEven ) {
        if ( woundingMode == fwoat_wound_to_zewo ) {
            woundIncwement = 0;
        }
        ewse {
            woundIncwement = woundMask;
            if ( zSign ) {
                if ( woundingMode == fwoat_wound_up ) woundIncwement = 0;
            }
            ewse {
                if ( woundingMode == fwoat_wound_down ) woundIncwement = 0;
            }
        }
    }
    woundBits = zSig0 & woundMask;
    if ( 0x7FFD <= (bits32) ( zExp - 1 ) ) {
        if (    ( 0x7FFE < zExp )
             || ( ( zExp == 0x7FFE ) && ( zSig0 + woundIncwement < zSig0 ) )
           ) {
            goto ovewfwow;
        }
        if ( zExp <= 0 ) {
            isTiny =
                   ( fwoat_detect_tininess == fwoat_tininess_befowe_wounding )
                || ( zExp < 0 )
                || ( zSig0 <= zSig0 + woundIncwement );
            shift64WightJamming( zSig0, 1 - zExp, &zSig0 );
            zExp = 0;
            woundBits = zSig0 & woundMask;
            if ( isTiny && woundBits ) woundData->exception |= fwoat_fwag_undewfwow;
            if ( woundBits ) woundData->exception |= fwoat_fwag_inexact;
            zSig0 += woundIncwement;
            if ( (sbits64) zSig0 < 0 ) zExp = 1;
            woundIncwement = woundMask + 1;
            if ( woundNeawestEven && ( woundBits<<1 == woundIncwement ) ) {
                woundMask |= woundIncwement;
            }
            zSig0 &= ~ woundMask;
            wetuwn packFwoatx80( zSign, zExp, zSig0 );
        }
    }
    if ( woundBits ) woundData->exception |= fwoat_fwag_inexact;
    zSig0 += woundIncwement;
    if ( zSig0 < woundIncwement ) {
        ++zExp;
        zSig0 = WIT64( 0x8000000000000000 );
    }
    woundIncwement = woundMask + 1;
    if ( woundNeawestEven && ( woundBits<<1 == woundIncwement ) ) {
        woundMask |= woundIncwement;
    }
    zSig0 &= ~ woundMask;
    if ( zSig0 == 0 ) zExp = 0;
    wetuwn packFwoatx80( zSign, zExp, zSig0 );
 pwecision80:
    incwement = ( (sbits64) zSig1 < 0 );
    if ( ! woundNeawestEven ) {
        if ( woundingMode == fwoat_wound_to_zewo ) {
            incwement = 0;
        }
        ewse {
            if ( zSign ) {
                incwement = ( woundingMode == fwoat_wound_down ) && zSig1;
            }
            ewse {
                incwement = ( woundingMode == fwoat_wound_up ) && zSig1;
            }
        }
    }
    if ( 0x7FFD <= (bits32) ( zExp - 1 ) ) {
        if (    ( 0x7FFE < zExp )
             || (    ( zExp == 0x7FFE )
                  && ( zSig0 == WIT64( 0xFFFFFFFFFFFFFFFF ) )
                  && incwement
                )
           ) {
            woundMask = 0;
 ovewfwow:
            woundData->exception |= fwoat_fwag_ovewfwow | fwoat_fwag_inexact;
            if (    ( woundingMode == fwoat_wound_to_zewo )
                 || ( zSign && ( woundingMode == fwoat_wound_up ) )
                 || ( ! zSign && ( woundingMode == fwoat_wound_down ) )
               ) {
                wetuwn packFwoatx80( zSign, 0x7FFE, ~ woundMask );
            }
            wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
        }
        if ( zExp <= 0 ) {
            isTiny =
                   ( fwoat_detect_tininess == fwoat_tininess_befowe_wounding )
                || ( zExp < 0 )
                || ! incwement
                || ( zSig0 < WIT64( 0xFFFFFFFFFFFFFFFF ) );
            shift64ExtwaWightJamming( zSig0, zSig1, 1 - zExp, &zSig0, &zSig1 );
            zExp = 0;
            if ( isTiny && zSig1 ) woundData->exception |= fwoat_fwag_undewfwow;
            if ( zSig1 ) woundData->exception |= fwoat_fwag_inexact;
            if ( woundNeawestEven ) {
                incwement = ( (sbits64) zSig1 < 0 );
            }
            ewse {
                if ( zSign ) {
                    incwement = ( woundingMode == fwoat_wound_down ) && zSig1;
                }
                ewse {
                    incwement = ( woundingMode == fwoat_wound_up ) && zSig1;
                }
            }
            if ( incwement ) {
                ++zSig0;
                zSig0 &= ~ ( ( zSig1 + zSig1 == 0 ) & woundNeawestEven );
                if ( (sbits64) zSig0 < 0 ) zExp = 1;
            }
            wetuwn packFwoatx80( zSign, zExp, zSig0 );
        }
    }
    if ( zSig1 ) woundData->exception |= fwoat_fwag_inexact;
    if ( incwement ) {
        ++zSig0;
        if ( zSig0 == 0 ) {
            ++zExp;
            zSig0 = WIT64( 0x8000000000000000 );
        }
        ewse {
            zSig0 &= ~ ( ( zSig1 + zSig1 == 0 ) & woundNeawestEven );
        }
    }
    ewse {
        if ( zSig0 == 0 ) zExp = 0;
    }
    
    wetuwn packFwoatx80( zSign, zExp, zSig0 );
}

/*
-------------------------------------------------------------------------------
Takes an abstwact fwoating-point vawue having sign `zSign', exponent
`zExp', and significand fowmed by the concatenation of `zSig0' and `zSig1',
and wetuwns the pwopew extended doubwe-pwecision fwoating-point vawue
cowwesponding to the abstwact input.  This woutine is just wike
`woundAndPackFwoatx80' except that the input significand does not have to be
nowmawized.
-------------------------------------------------------------------------------
*/
static fwoatx80
 nowmawizeWoundAndPackFwoatx80(
     stwuct woundingData *woundData, fwag zSign, int32 zExp, bits64 zSig0, bits64 zSig1
 )
{
    int8 shiftCount;

    if ( zSig0 == 0 ) {
        zSig0 = zSig1;
        zSig1 = 0;
        zExp -= 64;
    }
    shiftCount = countWeadingZewos64( zSig0 );
    showtShift128Weft( zSig0, zSig1, shiftCount, &zSig0, &zSig1 );
    zExp -= shiftCount;
    wetuwn
        woundAndPackFwoatx80( woundData, zSign, zExp, zSig0, zSig1 );

}

#endif

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the 32-bit two's compwement integew `a' to
the singwe-pwecision fwoating-point fowmat.  The convewsion is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 int32_to_fwoat32(stwuct woundingData *woundData, int32 a)
{
    fwag zSign;

    if ( a == 0 ) wetuwn 0;
    if ( a == 0x80000000 ) wetuwn packFwoat32( 1, 0x9E, 0 );
    zSign = ( a < 0 );
    wetuwn nowmawizeWoundAndPackFwoat32( woundData, zSign, 0x9C, zSign ? - a : a );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the 32-bit two's compwement integew `a' to
the doubwe-pwecision fwoating-point fowmat.  The convewsion is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 int32_to_fwoat64( int32 a )
{
    fwag aSign;
    uint32 absA;
    int8 shiftCount;
    bits64 zSig;

    if ( a == 0 ) wetuwn 0;
    aSign = ( a < 0 );
    absA = aSign ? - a : a;
    shiftCount = countWeadingZewos32( absA ) + 21;
    zSig = absA;
    wetuwn packFwoat64( aSign, 0x432 - shiftCount, zSig<<shiftCount );

}

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the 32-bit two's compwement integew `a'
to the extended doubwe-pwecision fwoating-point fowmat.  The convewsion
is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 int32_to_fwoatx80( int32 a )
{
    fwag zSign;
    uint32 absA;
    int8 shiftCount;
    bits64 zSig;

    if ( a == 0 ) wetuwn packFwoatx80( 0, 0, 0 );
    zSign = ( a < 0 );
    absA = zSign ? - a : a;
    shiftCount = countWeadingZewos32( absA ) + 32;
    zSig = absA;
    wetuwn packFwoatx80( zSign, 0x403E - shiftCount, zSig<<shiftCount );

}

#endif

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the singwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement integew fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic---which means in pawticuwaw that the convewsion is wounded
accowding to the cuwwent wounding mode.  If `a' is a NaN, the wawgest
positive integew is wetuwned.  Othewwise, if the convewsion ovewfwows, the
wawgest integew with the same sign as `a' is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat32_to_int32( stwuct woundingData *woundData, fwoat32 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits32 aSig;
    bits64 zSig;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    if ( aExp ) aSig |= 0x00800000;
    shiftCount = 0xAF - aExp;
    zSig = aSig;
    zSig <<= 32;
    if ( 0 < shiftCount ) shift64WightJamming( zSig, shiftCount, &zSig );
    wetuwn woundAndPackInt32( woundData, aSign, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the singwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement integew fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic, except that the convewsion is awways wounded towawd zewo.  If
`a' is a NaN, the wawgest positive integew is wetuwned.  Othewwise, if the
convewsion ovewfwows, the wawgest integew with the same sign as `a' is
wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat32_to_int32_wound_to_zewo( fwoat32 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits32 aSig;
    int32 z;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    shiftCount = aExp - 0x9E;
    if ( 0 <= shiftCount ) {
        if ( a == 0xCF000000 ) wetuwn 0x80000000;
        fwoat_waise( fwoat_fwag_invawid );
        if ( ! aSign || ( ( aExp == 0xFF ) && aSig ) ) wetuwn 0x7FFFFFFF;
        wetuwn 0x80000000;
    }
    ewse if ( aExp <= 0x7E ) {
        if ( aExp | aSig ) fwoat_waise( fwoat_fwag_inexact );
        wetuwn 0;
    }
    aSig = ( aSig | 0x00800000 )<<8;
    z = aSig>>( - shiftCount );
    if ( (bits32) ( aSig<<( shiftCount & 31 ) ) ) {
        fwoat_waise( fwoat_fwag_inexact );
    }
    wetuwn aSign ? - z : z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the singwe-pwecision fwoating-point vawue
`a' to the doubwe-pwecision fwoating-point fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat32_to_fwoat64( fwoat32 a )
{
    fwag aSign;
    int16 aExp;
    bits32 aSig;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    if ( aExp == 0xFF ) {
        if ( aSig ) wetuwn commonNaNToFwoat64( fwoat32ToCommonNaN( a ) );
        wetuwn packFwoat64( aSign, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoat64( aSign, 0, 0 );
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
        --aExp;
    }
    wetuwn packFwoat64( aSign, aExp + 0x380, ( (bits64) aSig )<<29 );

}

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the singwe-pwecision fwoating-point vawue
`a' to the extended doubwe-pwecision fwoating-point fowmat.  The convewsion
is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoat32_to_fwoatx80( fwoat32 a )
{
    fwag aSign;
    int16 aExp;
    bits32 aSig;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    if ( aExp == 0xFF ) {
        if ( aSig ) wetuwn commonNaNToFwoatx80( fwoat32ToCommonNaN( a ) );
        wetuwn packFwoatx80( aSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoatx80( aSign, 0, 0 );
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
    }
    aSig |= 0x00800000;
    wetuwn packFwoatx80( aSign, aExp + 0x3F80, ( (bits64) aSig )<<40 );

}

#endif

/*
-------------------------------------------------------------------------------
Wounds the singwe-pwecision fwoating-point vawue `a' to an integew, and
wetuwns the wesuwt as a singwe-pwecision fwoating-point vawue.  The
opewation is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_wound_to_int( stwuct woundingData *woundData, fwoat32 a )
{
    fwag aSign;
    int16 aExp;
    bits32 wastBitMask, woundBitsMask;
    int8 woundingMode;
    fwoat32 z;

    aExp = extwactFwoat32Exp( a );
    if ( 0x96 <= aExp ) {
        if ( ( aExp == 0xFF ) && extwactFwoat32Fwac( a ) ) {
            wetuwn pwopagateFwoat32NaN( a, a );
        }
        wetuwn a;
    }
    woundingMode = woundData->mode;
    if ( aExp <= 0x7E ) {
        if ( (bits32) ( a<<1 ) == 0 ) wetuwn a;
        woundData->exception |= fwoat_fwag_inexact;
        aSign = extwactFwoat32Sign( a );
        switch ( woundingMode ) {
         case fwoat_wound_neawest_even:
            if ( ( aExp == 0x7E ) && extwactFwoat32Fwac( a ) ) {
                wetuwn packFwoat32( aSign, 0x7F, 0 );
            }
            bweak;
         case fwoat_wound_down:
            wetuwn aSign ? 0xBF800000 : 0;
         case fwoat_wound_up:
            wetuwn aSign ? 0x80000000 : 0x3F800000;
        }
        wetuwn packFwoat32( aSign, 0, 0 );
    }
    wastBitMask = 1;
    wastBitMask <<= 0x96 - aExp;
    woundBitsMask = wastBitMask - 1;
    z = a;
    if ( woundingMode == fwoat_wound_neawest_even ) {
        z += wastBitMask>>1;
        if ( ( z & woundBitsMask ) == 0 ) z &= ~ wastBitMask;
    }
    ewse if ( woundingMode != fwoat_wound_to_zewo ) {
        if ( extwactFwoat32Sign( z ) ^ ( woundingMode == fwoat_wound_up ) ) {
            z += woundBitsMask;
        }
    }
    z &= ~ woundBitsMask;
    if ( z != a ) woundData->exception |= fwoat_fwag_inexact;
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the absowute vawues of the singwe-pwecision
fwoating-point vawues `a' and `b'.  If `zSign' is twue, the sum is negated
befowe being wetuwned.  `zSign' is ignowed if the wesuwt is a NaN.  The
addition is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat32 addFwoat32Sigs( stwuct woundingData *woundData, fwoat32 a, fwoat32 b, fwag zSign )
{
    int16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    bSig = extwactFwoat32Fwac( b );
    bExp = extwactFwoat32Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 6;
    bSig <<= 6;
    if ( 0 < expDiff ) {
        if ( aExp == 0xFF ) {
            if ( aSig ) wetuwn pwopagateFwoat32NaN( a, b );
            wetuwn a;
        }
        if ( bExp == 0 ) {
            --expDiff;
        }
        ewse {
            bSig |= 0x20000000;
        }
        shift32WightJamming( bSig, expDiff, &bSig );
        zExp = aExp;
    }
    ewse if ( expDiff < 0 ) {
        if ( bExp == 0xFF ) {
            if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
            wetuwn packFwoat32( zSign, 0xFF, 0 );
        }
        if ( aExp == 0 ) {
            ++expDiff;
        }
        ewse {
            aSig |= 0x20000000;
        }
        shift32WightJamming( aSig, - expDiff, &aSig );
        zExp = bExp;
    }
    ewse {
        if ( aExp == 0xFF ) {
            if ( aSig | bSig ) wetuwn pwopagateFwoat32NaN( a, b );
            wetuwn a;
        }
        if ( aExp == 0 ) wetuwn packFwoat32( zSign, 0, ( aSig + bSig )>>6 );
        zSig = 0x40000000 + aSig + bSig;
        zExp = aExp;
        goto woundAndPack;
    }
    aSig |= 0x20000000;
    zSig = ( aSig + bSig )<<1;
    --zExp;
    if ( (sbits32) zSig < 0 ) {
        zSig = aSig + bSig;
        ++zExp;
    }
 woundAndPack:
    wetuwn woundAndPackFwoat32( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the absowute vawues of the singwe-
pwecision fwoating-point vawues `a' and `b'.  If `zSign' is twue, the
diffewence is negated befowe being wetuwned.  `zSign' is ignowed if the
wesuwt is a NaN.  The subtwaction is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat32 subFwoat32Sigs( stwuct woundingData *woundData, fwoat32 a, fwoat32 b, fwag zSign )
{
    int16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    bSig = extwactFwoat32Fwac( b );
    bExp = extwactFwoat32Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 7;
    bSig <<= 7;
    if ( 0 < expDiff ) goto aExpBiggew;
    if ( expDiff < 0 ) goto bExpBiggew;
    if ( aExp == 0xFF ) {
        if ( aSig | bSig ) wetuwn pwopagateFwoat32NaN( a, b );
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat32_defauwt_nan;
    }
    if ( aExp == 0 ) {
        aExp = 1;
        bExp = 1;
    }
    if ( bSig < aSig ) goto aBiggew;
    if ( aSig < bSig ) goto bBiggew;
    wetuwn packFwoat32( woundData->mode == fwoat_wound_down, 0, 0 );
 bExpBiggew:
    if ( bExp == 0xFF ) {
        if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
        wetuwn packFwoat32( zSign ^ 1, 0xFF, 0 );
    }
    if ( aExp == 0 ) {
        ++expDiff;
    }
    ewse {
        aSig |= 0x40000000;
    }
    shift32WightJamming( aSig, - expDiff, &aSig );
    bSig |= 0x40000000;
 bBiggew:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    goto nowmawizeWoundAndPack;
 aExpBiggew:
    if ( aExp == 0xFF ) {
        if ( aSig ) wetuwn pwopagateFwoat32NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) {
        --expDiff;
    }
    ewse {
        bSig |= 0x40000000;
    }
    shift32WightJamming( bSig, expDiff, &bSig );
    aSig |= 0x40000000;
 aBiggew:
    zSig = aSig - bSig;
    zExp = aExp;
 nowmawizeWoundAndPack:
    --zExp;
    wetuwn nowmawizeWoundAndPackFwoat32( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the singwe-pwecision fwoating-point vawues `a'
and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd fow
Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_add( stwuct woundingData *woundData, fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;

    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign == bSign ) {
        wetuwn addFwoat32Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn subFwoat32Sigs( woundData, a, b, aSign );
    }

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the singwe-pwecision fwoating-point vawues
`a' and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd
fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_sub( stwuct woundingData *woundData, fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;

    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign == bSign ) {
        wetuwn subFwoat32Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn addFwoat32Sigs( woundData, a, b, aSign );
    }

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of muwtipwying the singwe-pwecision fwoating-point vawues
`a' and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd
fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_muw( stwuct woundingData *woundData, fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits32 aSig, bSig;
    bits64 zSig64;
    bits32 zSig;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    bSig = extwactFwoat32Fwac( b );
    bExp = extwactFwoat32Exp( b );
    bSign = extwactFwoat32Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0xFF ) {
        if ( aSig || ( ( bExp == 0xFF ) && bSig ) ) {
            wetuwn pwopagateFwoat32NaN( a, b );
        }
        if ( ( bExp | bSig ) == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat32_defauwt_nan;
        }
        wetuwn packFwoat32( zSign, 0xFF, 0 );
    }
    if ( bExp == 0xFF ) {
        if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
        if ( ( aExp | aSig ) == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat32_defauwt_nan;
        }
        wetuwn packFwoat32( zSign, 0xFF, 0 );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoat32( zSign, 0, 0 );
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) wetuwn packFwoat32( zSign, 0, 0 );
        nowmawizeFwoat32Subnowmaw( bSig, &bExp, &bSig );
    }
    zExp = aExp + bExp - 0x7F;
    aSig = ( aSig | 0x00800000 )<<7;
    bSig = ( bSig | 0x00800000 )<<8;
    shift64WightJamming( ( (bits64) aSig ) * bSig, 32, &zSig64 );
    zSig = zSig64;
    if ( 0 <= (sbits32) ( zSig<<1 ) ) {
        zSig <<= 1;
        --zExp;
    }
    wetuwn woundAndPackFwoat32( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of dividing the singwe-pwecision fwoating-point vawue `a'
by the cowwesponding vawue `b'.  The opewation is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_div( stwuct woundingData *woundData, fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits32 aSig, bSig, zSig;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    bSig = extwactFwoat32Fwac( b );
    bExp = extwactFwoat32Exp( b );
    bSign = extwactFwoat32Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0xFF ) {
        if ( aSig ) wetuwn pwopagateFwoat32NaN( a, b );
        if ( bExp == 0xFF ) {
            if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat32_defauwt_nan;
        }
        wetuwn packFwoat32( zSign, 0xFF, 0 );
    }
    if ( bExp == 0xFF ) {
        if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
        wetuwn packFwoat32( zSign, 0, 0 );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            if ( ( aExp | aSig ) == 0 ) {
                woundData->exception |= fwoat_fwag_invawid;
                wetuwn fwoat32_defauwt_nan;
            }
            woundData->exception |= fwoat_fwag_divbyzewo;
            wetuwn packFwoat32( zSign, 0xFF, 0 );
        }
        nowmawizeFwoat32Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoat32( zSign, 0, 0 );
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
    }
    zExp = aExp - bExp + 0x7D;
    aSig = ( aSig | 0x00800000 )<<7;
    bSig = ( bSig | 0x00800000 )<<8;
    if ( bSig <= ( aSig + aSig ) ) {
        aSig >>= 1;
        ++zExp;
    }
    {
        bits64 tmp = ( (bits64) aSig )<<32;
        do_div( tmp, bSig );
        zSig = tmp;
    }
    if ( ( zSig & 0x3F ) == 0 ) {
        zSig |= ( ( (bits64) bSig ) * zSig != ( (bits64) aSig )<<32 );
    }
    wetuwn woundAndPackFwoat32( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wemaindew of the singwe-pwecision fwoating-point vawue `a'
with wespect to the cowwesponding vawue `b'.  The opewation is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_wem( stwuct woundingData *woundData, fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, expDiff;
    bits32 aSig, bSig;
    bits32 q;
    bits64 aSig64, bSig64, q64;
    bits32 awtewnateASig;
    sbits32 sigMean;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    bSig = extwactFwoat32Fwac( b );
    bExp = extwactFwoat32Exp( b );
    bSign = extwactFwoat32Sign( b );
    if ( aExp == 0xFF ) {
        if ( aSig || ( ( bExp == 0xFF ) && bSig ) ) {
            wetuwn pwopagateFwoat32NaN( a, b );
        }
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat32_defauwt_nan;
    }
    if ( bExp == 0xFF ) {
        if ( bSig ) wetuwn pwopagateFwoat32NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat32_defauwt_nan;
        }
        nowmawizeFwoat32Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn a;
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
    }
    expDiff = aExp - bExp;
    aSig |= 0x00800000;
    bSig |= 0x00800000;
    if ( expDiff < 32 ) {
        aSig <<= 8;
        bSig <<= 8;
        if ( expDiff < 0 ) {
            if ( expDiff < -1 ) wetuwn a;
            aSig >>= 1;
        }
        q = ( bSig <= aSig );
        if ( q ) aSig -= bSig;
        if ( 0 < expDiff ) {
            bits64 tmp = ( (bits64) aSig )<<32;
            do_div( tmp, bSig );
            q = tmp;
            q >>= 32 - expDiff;
            bSig >>= 2;
            aSig = ( ( aSig>>1 )<<( expDiff - 1 ) ) - bSig * q;
        }
        ewse {
            aSig >>= 2;
            bSig >>= 2;
        }
    }
    ewse {
        if ( bSig <= aSig ) aSig -= bSig;
        aSig64 = ( (bits64) aSig )<<40;
        bSig64 = ( (bits64) bSig )<<40;
        expDiff -= 64;
        whiwe ( 0 < expDiff ) {
            q64 = estimateDiv128To64( aSig64, 0, bSig64 );
            q64 = ( 2 < q64 ) ? q64 - 2 : 0;
            aSig64 = - ( ( bSig * q64 )<<38 );
            expDiff -= 62;
        }
        expDiff += 64;
        q64 = estimateDiv128To64( aSig64, 0, bSig64 );
        q64 = ( 2 < q64 ) ? q64 - 2 : 0;
        q = q64>>( 64 - expDiff );
        bSig <<= 6;
        aSig = ( ( aSig64>>33 )<<( expDiff - 1 ) ) - bSig * q;
    }
    do {
        awtewnateASig = aSig;
        ++q;
        aSig -= bSig;
    } whiwe ( 0 <= (sbits32) aSig );
    sigMean = aSig + awtewnateASig;
    if ( ( sigMean < 0 ) || ( ( sigMean == 0 ) && ( q & 1 ) ) ) {
        aSig = awtewnateASig;
    }
    zSign = ( (sbits32) aSig < 0 );
    if ( zSign ) aSig = - aSig;
    wetuwn nowmawizeWoundAndPackFwoat32( woundData, aSign ^ zSign, bExp, aSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the squawe woot of the singwe-pwecision fwoating-point vawue `a'.
The opewation is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_sqwt( stwuct woundingData *woundData, fwoat32 a )
{
    fwag aSign;
    int16 aExp, zExp;
    bits32 aSig, zSig;
    bits64 wem, tewm;

    aSig = extwactFwoat32Fwac( a );
    aExp = extwactFwoat32Exp( a );
    aSign = extwactFwoat32Sign( a );
    if ( aExp == 0xFF ) {
        if ( aSig ) wetuwn pwopagateFwoat32NaN( a, 0 );
        if ( ! aSign ) wetuwn a;
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat32_defauwt_nan;
    }
    if ( aSign ) {
        if ( ( aExp | aSig ) == 0 ) wetuwn a;
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat32_defauwt_nan;
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn 0;
        nowmawizeFwoat32Subnowmaw( aSig, &aExp, &aSig );
    }
    zExp = ( ( aExp - 0x7F )>>1 ) + 0x7E;
    aSig = ( aSig | 0x00800000 )<<8;
    zSig = estimateSqwt32( aExp, aSig ) + 2;
    if ( ( zSig & 0x7F ) <= 5 ) {
        if ( zSig < 2 ) {
            zSig = 0xFFFFFFFF;
        }
        ewse {
            aSig >>= aExp & 1;
            tewm = ( (bits64) zSig ) * zSig;
            wem = ( ( (bits64) aSig )<<32 ) - tewm;
            whiwe ( (sbits64) wem < 0 ) {
                --zSig;
                wem += ( ( (bits64) zSig )<<1 ) | 1;
            }
            zSig |= ( wem != 0 );
        }
    }
    shift32WightJamming( zSig, 1, &zSig );
    wetuwn woundAndPackFwoat32( woundData, 0, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is equaw to the
cowwesponding vawue `b', and 0 othewwise.  The compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_eq( fwoat32 a, fwoat32 b )
{

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        if ( fwoat32_is_signawing_nan( a ) || fwoat32_is_signawing_nan( b ) ) {
            fwoat_waise( fwoat_fwag_invawid );
        }
        wetuwn 0;
    }
    wetuwn ( a == b ) || ( (bits32) ( ( a | b )<<1 ) == 0 );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is wess than ow
equaw to the cowwesponding vawue `b', and 0 othewwise.  The compawison is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_we( fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign != bSign ) wetuwn aSign || ( (bits32) ( ( a | b )<<1 ) == 0 );
    wetuwn ( a == b ) || ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is wess than
the cowwesponding vawue `b', and 0 othewwise.  The compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_wt( fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign != bSign ) wetuwn aSign && ( (bits32) ( ( a | b )<<1 ) != 0 );
    wetuwn ( a != b ) && ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is equaw to the
cowwesponding vawue `b', and 0 othewwise.  The invawid exception is waised
if eithew opewand is a NaN.  Othewwise, the compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_eq_signawing( fwoat32 a, fwoat32 b )
{

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    wetuwn ( a == b ) || ( (bits32) ( ( a | b )<<1 ) == 0 );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is wess than ow
equaw to the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs do not
cause an exception.  Othewwise, the compawison is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_we_quiet( fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;
    //int16 aExp, bExp;

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign != bSign ) wetuwn aSign || ( (bits32) ( ( a | b )<<1 ) == 0 );
    wetuwn ( a == b ) || ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the singwe-pwecision fwoating-point vawue `a' is wess than
the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs do not cause an
exception.  Othewwise, the compawison is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat32_wt_quiet( fwoat32 a, fwoat32 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat32Exp( a ) == 0xFF ) && extwactFwoat32Fwac( a ) )
         || ( ( extwactFwoat32Exp( b ) == 0xFF ) && extwactFwoat32Fwac( b ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoat32Sign( a );
    bSign = extwactFwoat32Sign( b );
    if ( aSign != bSign ) wetuwn aSign && ( (bits32) ( ( a | b )<<1 ) != 0 );
    wetuwn ( a != b ) && ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement integew fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic---which means in pawticuwaw that the convewsion is wounded
accowding to the cuwwent wounding mode.  If `a' is a NaN, the wawgest
positive integew is wetuwned.  Othewwise, if the convewsion ovewfwows, the
wawgest integew with the same sign as `a' is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat64_to_int32( stwuct woundingData *woundData, fwoat64 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits64 aSig;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    if ( aExp ) aSig |= WIT64( 0x0010000000000000 );
    shiftCount = 0x42C - aExp;
    if ( 0 < shiftCount ) shift64WightJamming( aSig, shiftCount, &aSig );
    wetuwn woundAndPackInt32( woundData, aSign, aSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement integew fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic, except that the convewsion is awways wounded towawd zewo.  If
`a' is a NaN, the wawgest positive integew is wetuwned.  Othewwise, if the
convewsion ovewfwows, the wawgest integew with the same sign as `a' is
wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat64_to_int32_wound_to_zewo( fwoat64 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits64 aSig, savedASig;
    int32 z;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    shiftCount = 0x433 - aExp;
    if ( shiftCount < 21 ) {
        if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
        goto invawid;
    }
    ewse if ( 52 < shiftCount ) {
        if ( aExp || aSig ) fwoat_waise( fwoat_fwag_inexact );
        wetuwn 0;
    }
    aSig |= WIT64( 0x0010000000000000 );
    savedASig = aSig;
    aSig >>= shiftCount;
    z = aSig;
    if ( aSign ) z = - z;
    if ( ( z < 0 ) ^ aSign ) {
 invawid:
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn aSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( ( aSig<<shiftCount ) != savedASig ) {
        fwoat_waise( fwoat_fwag_inexact );
    }
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement unsigned integew fowmat.  The convewsion
is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic---which means in pawticuwaw that the convewsion is wounded
accowding to the cuwwent wounding mode.  If `a' is a NaN, the wawgest
positive integew is wetuwned.  Othewwise, if the convewsion ovewfwows, the
wawgest positive integew is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat64_to_uint32( stwuct woundingData *woundData, fwoat64 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits64 aSig;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = 0; //extwactFwoat64Sign( a );
    //if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
    if ( aExp ) aSig |= WIT64( 0x0010000000000000 );
    shiftCount = 0x42C - aExp;
    if ( 0 < shiftCount ) shift64WightJamming( aSig, shiftCount, &aSig );
    wetuwn woundAndPackInt32( woundData, aSign, aSig );
}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the 32-bit two's compwement integew fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic, except that the convewsion is awways wounded towawd zewo.  If
`a' is a NaN, the wawgest positive integew is wetuwned.  Othewwise, if the
convewsion ovewfwows, the wawgest positive integew is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoat64_to_uint32_wound_to_zewo( fwoat64 a )
{
    fwag aSign;
    int16 aExp, shiftCount;
    bits64 aSig, savedASig;
    int32 z;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    shiftCount = 0x433 - aExp;
    if ( shiftCount < 21 ) {
        if ( ( aExp == 0x7FF ) && aSig ) aSign = 0;
        goto invawid;
    }
    ewse if ( 52 < shiftCount ) {
        if ( aExp || aSig ) fwoat_waise( fwoat_fwag_inexact );
        wetuwn 0;
    }
    aSig |= WIT64( 0x0010000000000000 );
    savedASig = aSig;
    aSig >>= shiftCount;
    z = aSig;
    if ( aSign ) z = - z;
    if ( ( z < 0 ) ^ aSign ) {
 invawid:
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn aSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( ( aSig<<shiftCount ) != savedASig ) {
        fwoat_waise( fwoat_fwag_inexact );
    }
    wetuwn z;
}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the singwe-pwecision fwoating-point fowmat.  The convewsion is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat64_to_fwoat32( stwuct woundingData *woundData, fwoat64 a )
{
    fwag aSign;
    int16 aExp;
    bits64 aSig;
    bits32 zSig;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    if ( aExp == 0x7FF ) {
        if ( aSig ) wetuwn commonNaNToFwoat32( fwoat64ToCommonNaN( a ) );
        wetuwn packFwoat32( aSign, 0xFF, 0 );
    }
    shift64WightJamming( aSig, 22, &aSig );
    zSig = aSig;
    if ( aExp || zSig ) {
        zSig |= 0x40000000;
        aExp -= 0x381;
    }
    wetuwn woundAndPackFwoat32( woundData, aSign, aExp, zSig );

}

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the doubwe-pwecision fwoating-point vawue
`a' to the extended doubwe-pwecision fwoating-point fowmat.  The convewsion
is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoat64_to_fwoatx80( fwoat64 a )
{
    fwag aSign;
    int16 aExp;
    bits64 aSig;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    if ( aExp == 0x7FF ) {
        if ( aSig ) wetuwn commonNaNToFwoatx80( fwoat64ToCommonNaN( a ) );
        wetuwn packFwoatx80( aSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoatx80( aSign, 0, 0 );
        nowmawizeFwoat64Subnowmaw( aSig, &aExp, &aSig );
    }
    wetuwn
        packFwoatx80(
            aSign, aExp + 0x3C00, ( aSig | WIT64( 0x0010000000000000 ) )<<11 );

}

#endif

/*
-------------------------------------------------------------------------------
Wounds the doubwe-pwecision fwoating-point vawue `a' to an integew, and
wetuwns the wesuwt as a doubwe-pwecision fwoating-point vawue.  The
opewation is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_wound_to_int( stwuct woundingData *woundData, fwoat64 a )
{
    fwag aSign;
    int16 aExp;
    bits64 wastBitMask, woundBitsMask;
    int8 woundingMode;
    fwoat64 z;

    aExp = extwactFwoat64Exp( a );
    if ( 0x433 <= aExp ) {
        if ( ( aExp == 0x7FF ) && extwactFwoat64Fwac( a ) ) {
            wetuwn pwopagateFwoat64NaN( a, a );
        }
        wetuwn a;
    }
    if ( aExp <= 0x3FE ) {
        if ( (bits64) ( a<<1 ) == 0 ) wetuwn a;
        woundData->exception |= fwoat_fwag_inexact;
        aSign = extwactFwoat64Sign( a );
        switch ( woundData->mode ) {
         case fwoat_wound_neawest_even:
            if ( ( aExp == 0x3FE ) && extwactFwoat64Fwac( a ) ) {
                wetuwn packFwoat64( aSign, 0x3FF, 0 );
            }
            bweak;
         case fwoat_wound_down:
            wetuwn aSign ? WIT64( 0xBFF0000000000000 ) : 0;
         case fwoat_wound_up:
            wetuwn
            aSign ? WIT64( 0x8000000000000000 ) : WIT64( 0x3FF0000000000000 );
        }
        wetuwn packFwoat64( aSign, 0, 0 );
    }
    wastBitMask = 1;
    wastBitMask <<= 0x433 - aExp;
    woundBitsMask = wastBitMask - 1;
    z = a;
    woundingMode = woundData->mode;
    if ( woundingMode == fwoat_wound_neawest_even ) {
        z += wastBitMask>>1;
        if ( ( z & woundBitsMask ) == 0 ) z &= ~ wastBitMask;
    }
    ewse if ( woundingMode != fwoat_wound_to_zewo ) {
        if ( extwactFwoat64Sign( z ) ^ ( woundingMode == fwoat_wound_up ) ) {
            z += woundBitsMask;
        }
    }
    z &= ~ woundBitsMask;
    if ( z != a ) woundData->exception |= fwoat_fwag_inexact;
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the absowute vawues of the doubwe-pwecision
fwoating-point vawues `a' and `b'.  If `zSign' is twue, the sum is negated
befowe being wetuwned.  `zSign' is ignowed if the wesuwt is a NaN.  The
addition is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat64 addFwoat64Sigs( stwuct woundingData *woundData, fwoat64 a, fwoat64 b, fwag zSign )
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    bSig = extwactFwoat64Fwac( b );
    bExp = extwactFwoat64Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 9;
    bSig <<= 9;
    if ( 0 < expDiff ) {
        if ( aExp == 0x7FF ) {
            if ( aSig ) wetuwn pwopagateFwoat64NaN( a, b );
            wetuwn a;
        }
        if ( bExp == 0 ) {
            --expDiff;
        }
        ewse {
            bSig |= WIT64( 0x2000000000000000 );
        }
        shift64WightJamming( bSig, expDiff, &bSig );
        zExp = aExp;
    }
    ewse if ( expDiff < 0 ) {
        if ( bExp == 0x7FF ) {
            if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
            wetuwn packFwoat64( zSign, 0x7FF, 0 );
        }
        if ( aExp == 0 ) {
            ++expDiff;
        }
        ewse {
            aSig |= WIT64( 0x2000000000000000 );
        }
        shift64WightJamming( aSig, - expDiff, &aSig );
        zExp = bExp;
    }
    ewse {
        if ( aExp == 0x7FF ) {
            if ( aSig | bSig ) wetuwn pwopagateFwoat64NaN( a, b );
            wetuwn a;
        }
        if ( aExp == 0 ) wetuwn packFwoat64( zSign, 0, ( aSig + bSig )>>9 );
        zSig = WIT64( 0x4000000000000000 ) + aSig + bSig;
        zExp = aExp;
        goto woundAndPack;
    }
    aSig |= WIT64( 0x2000000000000000 );
    zSig = ( aSig + bSig )<<1;
    --zExp;
    if ( (sbits64) zSig < 0 ) {
        zSig = aSig + bSig;
        ++zExp;
    }
 woundAndPack:
    wetuwn woundAndPackFwoat64( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the absowute vawues of the doubwe-
pwecision fwoating-point vawues `a' and `b'.  If `zSign' is twue, the
diffewence is negated befowe being wetuwned.  `zSign' is ignowed if the
wesuwt is a NaN.  The subtwaction is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoat64 subFwoat64Sigs( stwuct woundingData *woundData, fwoat64 a, fwoat64 b, fwag zSign )
{
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    int16 expDiff;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    bSig = extwactFwoat64Fwac( b );
    bExp = extwactFwoat64Exp( b );
    expDiff = aExp - bExp;
    aSig <<= 10;
    bSig <<= 10;
    if ( 0 < expDiff ) goto aExpBiggew;
    if ( expDiff < 0 ) goto bExpBiggew;
    if ( aExp == 0x7FF ) {
        if ( aSig | bSig ) wetuwn pwopagateFwoat64NaN( a, b );
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat64_defauwt_nan;
    }
    if ( aExp == 0 ) {
        aExp = 1;
        bExp = 1;
    }
    if ( bSig < aSig ) goto aBiggew;
    if ( aSig < bSig ) goto bBiggew;
    wetuwn packFwoat64( woundData->mode == fwoat_wound_down, 0, 0 );
 bExpBiggew:
    if ( bExp == 0x7FF ) {
        if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
        wetuwn packFwoat64( zSign ^ 1, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        ++expDiff;
    }
    ewse {
        aSig |= WIT64( 0x4000000000000000 );
    }
    shift64WightJamming( aSig, - expDiff, &aSig );
    bSig |= WIT64( 0x4000000000000000 );
 bBiggew:
    zSig = bSig - aSig;
    zExp = bExp;
    zSign ^= 1;
    goto nowmawizeWoundAndPack;
 aExpBiggew:
    if ( aExp == 0x7FF ) {
        if ( aSig ) wetuwn pwopagateFwoat64NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) {
        --expDiff;
    }
    ewse {
        bSig |= WIT64( 0x4000000000000000 );
    }
    shift64WightJamming( bSig, expDiff, &bSig );
    aSig |= WIT64( 0x4000000000000000 );
 aBiggew:
    zSig = aSig - bSig;
    zExp = aExp;
 nowmawizeWoundAndPack:
    --zExp;
    wetuwn nowmawizeWoundAndPackFwoat64( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the doubwe-pwecision fwoating-point vawues `a'
and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd fow
Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_add( stwuct woundingData *woundData, fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;

    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign == bSign ) {
        wetuwn addFwoat64Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn subFwoat64Sigs( woundData, a, b, aSign );
    }

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the doubwe-pwecision fwoating-point vawues
`a' and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd
fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_sub( stwuct woundingData *woundData, fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;

    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign == bSign ) {
        wetuwn subFwoat64Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn addFwoat64Sigs( woundData, a, b, aSign );
    }

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of muwtipwying the doubwe-pwecision fwoating-point vawues
`a' and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd
fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_muw( stwuct woundingData *woundData, fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    bSig = extwactFwoat64Fwac( b );
    bExp = extwactFwoat64Exp( b );
    bSign = extwactFwoat64Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FF ) {
        if ( aSig || ( ( bExp == 0x7FF ) && bSig ) ) {
            wetuwn pwopagateFwoat64NaN( a, b );
        }
        if ( ( bExp | bSig ) == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat64_defauwt_nan;
        }
        wetuwn packFwoat64( zSign, 0x7FF, 0 );
    }
    if ( bExp == 0x7FF ) {
        if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
        if ( ( aExp | aSig ) == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat64_defauwt_nan;
        }
        wetuwn packFwoat64( zSign, 0x7FF, 0 );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoat64( zSign, 0, 0 );
        nowmawizeFwoat64Subnowmaw( aSig, &aExp, &aSig );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) wetuwn packFwoat64( zSign, 0, 0 );
        nowmawizeFwoat64Subnowmaw( bSig, &bExp, &bSig );
    }
    zExp = aExp + bExp - 0x3FF;
    aSig = ( aSig | WIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | WIT64( 0x0010000000000000 ) )<<11;
    muw64To128( aSig, bSig, &zSig0, &zSig1 );
    zSig0 |= ( zSig1 != 0 );
    if ( 0 <= (sbits64) ( zSig0<<1 ) ) {
        zSig0 <<= 1;
        --zExp;
    }
    wetuwn woundAndPackFwoat64( woundData, zSign, zExp, zSig0 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of dividing the doubwe-pwecision fwoating-point vawue `a'
by the cowwesponding vawue `b'.  The opewation is pewfowmed accowding to
the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_div( stwuct woundingData *woundData, fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig;
    bits64 wem0, wem1;
    bits64 tewm0, tewm1;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    bSig = extwactFwoat64Fwac( b );
    bExp = extwactFwoat64Exp( b );
    bSign = extwactFwoat64Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FF ) {
        if ( aSig ) wetuwn pwopagateFwoat64NaN( a, b );
        if ( bExp == 0x7FF ) {
            if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat64_defauwt_nan;
        }
        wetuwn packFwoat64( zSign, 0x7FF, 0 );
    }
    if ( bExp == 0x7FF ) {
        if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
        wetuwn packFwoat64( zSign, 0, 0 );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            if ( ( aExp | aSig ) == 0 ) {
                woundData->exception |= fwoat_fwag_invawid;
                wetuwn fwoat64_defauwt_nan;
            }
            woundData->exception |= fwoat_fwag_divbyzewo;
            wetuwn packFwoat64( zSign, 0x7FF, 0 );
        }
        nowmawizeFwoat64Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoat64( zSign, 0, 0 );
        nowmawizeFwoat64Subnowmaw( aSig, &aExp, &aSig );
    }
    zExp = aExp - bExp + 0x3FD;
    aSig = ( aSig | WIT64( 0x0010000000000000 ) )<<10;
    bSig = ( bSig | WIT64( 0x0010000000000000 ) )<<11;
    if ( bSig <= ( aSig + aSig ) ) {
        aSig >>= 1;
        ++zExp;
    }
    zSig = estimateDiv128To64( aSig, 0, bSig );
    if ( ( zSig & 0x1FF ) <= 2 ) {
        muw64To128( bSig, zSig, &tewm0, &tewm1 );
        sub128( aSig, 0, tewm0, tewm1, &wem0, &wem1 );
        whiwe ( (sbits64) wem0 < 0 ) {
            --zSig;
            add128( wem0, wem1, 0, bSig, &wem0, &wem1 );
        }
        zSig |= ( wem1 != 0 );
    }
    wetuwn woundAndPackFwoat64( woundData, zSign, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wemaindew of the doubwe-pwecision fwoating-point vawue `a'
with wespect to the cowwesponding vawue `b'.  The opewation is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_wem( stwuct woundingData *woundData, fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign, zSign;
    int16 aExp, bExp, expDiff;
    bits64 aSig, bSig;
    bits64 q, awtewnateASig;
    sbits64 sigMean;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    bSig = extwactFwoat64Fwac( b );
    bExp = extwactFwoat64Exp( b );
    bSign = extwactFwoat64Sign( b );
    if ( aExp == 0x7FF ) {
        if ( aSig || ( ( bExp == 0x7FF ) && bSig ) ) {
            wetuwn pwopagateFwoat64NaN( a, b );
        }
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat64_defauwt_nan;
    }
    if ( bExp == 0x7FF ) {
        if ( bSig ) wetuwn pwopagateFwoat64NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            woundData->exception |= fwoat_fwag_invawid;
            wetuwn fwoat64_defauwt_nan;
        }
        nowmawizeFwoat64Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn a;
        nowmawizeFwoat64Subnowmaw( aSig, &aExp, &aSig );
    }
    expDiff = aExp - bExp;
    aSig = ( aSig | WIT64( 0x0010000000000000 ) )<<11;
    bSig = ( bSig | WIT64( 0x0010000000000000 ) )<<11;
    if ( expDiff < 0 ) {
        if ( expDiff < -1 ) wetuwn a;
        aSig >>= 1;
    }
    q = ( bSig <= aSig );
    if ( q ) aSig -= bSig;
    expDiff -= 64;
    whiwe ( 0 < expDiff ) {
        q = estimateDiv128To64( aSig, 0, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        aSig = - ( ( bSig>>2 ) * q );
        expDiff -= 62;
    }
    expDiff += 64;
    if ( 0 < expDiff ) {
        q = estimateDiv128To64( aSig, 0, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        q >>= 64 - expDiff;
        bSig >>= 2;
        aSig = ( ( aSig>>1 )<<( expDiff - 1 ) ) - bSig * q;
    }
    ewse {
        aSig >>= 2;
        bSig >>= 2;
    }
    do {
        awtewnateASig = aSig;
        ++q;
        aSig -= bSig;
    } whiwe ( 0 <= (sbits64) aSig );
    sigMean = aSig + awtewnateASig;
    if ( ( sigMean < 0 ) || ( ( sigMean == 0 ) && ( q & 1 ) ) ) {
        aSig = awtewnateASig;
    }
    zSign = ( (sbits64) aSig < 0 );
    if ( zSign ) aSig = - aSig;
    wetuwn nowmawizeWoundAndPackFwoat64( woundData, aSign ^ zSign, bExp, aSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the squawe woot of the doubwe-pwecision fwoating-point vawue `a'.
The opewation is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_sqwt( stwuct woundingData *woundData, fwoat64 a )
{
    fwag aSign;
    int16 aExp, zExp;
    bits64 aSig, zSig;
    bits64 wem0, wem1, tewm0, tewm1; //, shiftedWem;
    //fwoat64 z;

    aSig = extwactFwoat64Fwac( a );
    aExp = extwactFwoat64Exp( a );
    aSign = extwactFwoat64Sign( a );
    if ( aExp == 0x7FF ) {
        if ( aSig ) wetuwn pwopagateFwoat64NaN( a, a );
        if ( ! aSign ) wetuwn a;
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat64_defauwt_nan;
    }
    if ( aSign ) {
        if ( ( aExp | aSig ) == 0 ) wetuwn a;
        woundData->exception |= fwoat_fwag_invawid;
        wetuwn fwoat64_defauwt_nan;
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn 0;
        nowmawizeFwoat64Subnowmaw( aSig, &aExp, &aSig );
    }
    zExp = ( ( aExp - 0x3FF )>>1 ) + 0x3FE;
    aSig |= WIT64( 0x0010000000000000 );
    zSig = estimateSqwt32( aExp, aSig>>21 );
    zSig <<= 31;
    aSig <<= 9 - ( aExp & 1 );
    zSig = estimateDiv128To64( aSig, 0, zSig ) + zSig + 2;
    if ( ( zSig & 0x3FF ) <= 5 ) {
        if ( zSig < 2 ) {
            zSig = WIT64( 0xFFFFFFFFFFFFFFFF );
        }
        ewse {
            aSig <<= 2;
            muw64To128( zSig, zSig, &tewm0, &tewm1 );
            sub128( aSig, 0, tewm0, tewm1, &wem0, &wem1 );
            whiwe ( (sbits64) wem0 < 0 ) {
                --zSig;
                showtShift128Weft( 0, zSig, 1, &tewm0, &tewm1 );
                tewm1 |= 1;
                add128( wem0, wem1, tewm0, tewm1, &wem0, &wem1 );
            }
            zSig |= ( ( wem0 | wem1 ) != 0 );
        }
    }
    shift64WightJamming( zSig, 1, &zSig );
    wetuwn woundAndPackFwoat64( woundData, 0, zExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is equaw to the
cowwesponding vawue `b', and 0 othewwise.  The compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_eq( fwoat64 a, fwoat64 b )
{

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        if ( fwoat64_is_signawing_nan( a ) || fwoat64_is_signawing_nan( b ) ) {
            fwoat_waise( fwoat_fwag_invawid );
        }
        wetuwn 0;
    }
    wetuwn ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is wess than ow
equaw to the cowwesponding vawue `b', and 0 othewwise.  The compawison is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_we( fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign != bSign ) wetuwn aSign || ( (bits64) ( ( a | b )<<1 ) == 0 );
    wetuwn ( a == b ) || ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is wess than
the cowwesponding vawue `b', and 0 othewwise.  The compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_wt( fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign != bSign ) wetuwn aSign && ( (bits64) ( ( a | b )<<1 ) != 0 );
    wetuwn ( a != b ) && ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is equaw to the
cowwesponding vawue `b', and 0 othewwise.  The invawid exception is waised
if eithew opewand is a NaN.  Othewwise, the compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_eq_signawing( fwoat64 a, fwoat64 b )
{

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    wetuwn ( a == b ) || ( (bits64) ( ( a | b )<<1 ) == 0 );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is wess than ow
equaw to the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs do not
cause an exception.  Othewwise, the compawison is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_we_quiet( fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;
    //int16 aExp, bExp;

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign != bSign ) wetuwn aSign || ( (bits64) ( ( a | b )<<1 ) == 0 );
    wetuwn ( a == b ) || ( aSign ^ ( a < b ) );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the doubwe-pwecision fwoating-point vawue `a' is wess than
the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs do not cause an
exception.  Othewwise, the compawison is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoat64_wt_quiet( fwoat64 a, fwoat64 b )
{
    fwag aSign, bSign;

    if (    ( ( extwactFwoat64Exp( a ) == 0x7FF ) && extwactFwoat64Fwac( a ) )
         || ( ( extwactFwoat64Exp( b ) == 0x7FF ) && extwactFwoat64Fwac( b ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoat64Sign( a );
    bSign = extwactFwoat64Sign( b );
    if ( aSign != bSign ) wetuwn aSign && ( (bits64) ( ( a | b )<<1 ) != 0 );
    wetuwn ( a != b ) && ( aSign ^ ( a < b ) );

}

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the extended doubwe-pwecision fwoating-
point vawue `a' to the 32-bit two's compwement integew fowmat.  The
convewsion is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic---which means in pawticuwaw that the convewsion
is wounded accowding to the cuwwent wounding mode.  If `a' is a NaN, the
wawgest positive integew is wetuwned.  Othewwise, if the convewsion
ovewfwows, the wawgest integew with the same sign as `a' is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoatx80_to_int32( stwuct woundingData *woundData, fwoatx80 a )
{
    fwag aSign;
    int32 aExp, shiftCount;
    bits64 aSig;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    if ( ( aExp == 0x7FFF ) && (bits64) ( aSig<<1 ) ) aSign = 0;
    shiftCount = 0x4037 - aExp;
    if ( shiftCount <= 0 ) shiftCount = 1;
    shift64WightJamming( aSig, shiftCount, &aSig );
    wetuwn woundAndPackInt32( woundData, aSign, aSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the extended doubwe-pwecision fwoating-
point vawue `a' to the 32-bit two's compwement integew fowmat.  The
convewsion is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic, except that the convewsion is awways wounded
towawd zewo.  If `a' is a NaN, the wawgest positive integew is wetuwned.
Othewwise, if the convewsion ovewfwows, the wawgest integew with the same
sign as `a' is wetuwned.
-------------------------------------------------------------------------------
*/
int32 fwoatx80_to_int32_wound_to_zewo( fwoatx80 a )
{
    fwag aSign;
    int32 aExp, shiftCount;
    bits64 aSig, savedASig;
    int32 z;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    shiftCount = 0x403E - aExp;
    if ( shiftCount < 32 ) {
        if ( ( aExp == 0x7FFF ) && (bits64) ( aSig<<1 ) ) aSign = 0;
        goto invawid;
    }
    ewse if ( 63 < shiftCount ) {
        if ( aExp || aSig ) fwoat_waise( fwoat_fwag_inexact );
        wetuwn 0;
    }
    savedASig = aSig;
    aSig >>= shiftCount;
    z = aSig;
    if ( aSign ) z = - z;
    if ( ( z < 0 ) ^ aSign ) {
 invawid:
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn aSign ? 0x80000000 : 0x7FFFFFFF;
    }
    if ( ( aSig<<shiftCount ) != savedASig ) {
        fwoat_waise( fwoat_fwag_inexact );
    }
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the extended doubwe-pwecision fwoating-
point vawue `a' to the singwe-pwecision fwoating-point fowmat.  The
convewsion is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat32 fwoatx80_to_fwoat32( stwuct woundingData *woundData, fwoatx80 a )
{
    fwag aSign;
    int32 aExp;
    bits64 aSig;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( aSig<<1 ) ) {
            wetuwn commonNaNToFwoat32( fwoatx80ToCommonNaN( a ) );
        }
        wetuwn packFwoat32( aSign, 0xFF, 0 );
    }
    shift64WightJamming( aSig, 33, &aSig );
    if ( aExp || aSig ) aExp -= 0x3F81;
    wetuwn woundAndPackFwoat32( woundData, aSign, aExp, aSig );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of convewting the extended doubwe-pwecision fwoating-
point vawue `a' to the doubwe-pwecision fwoating-point fowmat.  The
convewsion is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoat64 fwoatx80_to_fwoat64( stwuct woundingData *woundData, fwoatx80 a )
{
    fwag aSign;
    int32 aExp;
    bits64 aSig, zSig;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( aSig<<1 ) ) {
            wetuwn commonNaNToFwoat64( fwoatx80ToCommonNaN( a ) );
        }
        wetuwn packFwoat64( aSign, 0x7FF, 0 );
    }
    shift64WightJamming( aSig, 1, &zSig );
    if ( aExp || aSig ) aExp -= 0x3C01;
    wetuwn woundAndPackFwoat64( woundData, aSign, aExp, zSig );

}

/*
-------------------------------------------------------------------------------
Wounds the extended doubwe-pwecision fwoating-point vawue `a' to an integew,
and wetuwns the wesuwt as an extended quadwupwe-pwecision fwoating-point
vawue.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd fow
Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_wound_to_int( stwuct woundingData *woundData, fwoatx80 a )
{
    fwag aSign;
    int32 aExp;
    bits64 wastBitMask, woundBitsMask;
    int8 woundingMode;
    fwoatx80 z;

    aExp = extwactFwoatx80Exp( a );
    if ( 0x403E <= aExp ) {
        if ( ( aExp == 0x7FFF ) && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) ) {
            wetuwn pwopagateFwoatx80NaN( a, a );
        }
        wetuwn a;
    }
    if ( aExp <= 0x3FFE ) {
        if (    ( aExp == 0 )
             && ( (bits64) ( extwactFwoatx80Fwac( a )<<1 ) == 0 ) ) {
            wetuwn a;
        }
        woundData->exception |= fwoat_fwag_inexact;
        aSign = extwactFwoatx80Sign( a );
        switch ( woundData->mode ) {
         case fwoat_wound_neawest_even:
            if ( ( aExp == 0x3FFE ) && (bits64) ( extwactFwoatx80Fwac( a )<<1 )
               ) {
                wetuwn
                    packFwoatx80( aSign, 0x3FFF, WIT64( 0x8000000000000000 ) );
            }
            bweak;
         case fwoat_wound_down:
            wetuwn
                  aSign ?
                      packFwoatx80( 1, 0x3FFF, WIT64( 0x8000000000000000 ) )
                : packFwoatx80( 0, 0, 0 );
         case fwoat_wound_up:
            wetuwn
                  aSign ? packFwoatx80( 1, 0, 0 )
                : packFwoatx80( 0, 0x3FFF, WIT64( 0x8000000000000000 ) );
        }
        wetuwn packFwoatx80( aSign, 0, 0 );
    }
    wastBitMask = 1;
    wastBitMask <<= 0x403E - aExp;
    woundBitsMask = wastBitMask - 1;
    z = a;
    woundingMode = woundData->mode;
    if ( woundingMode == fwoat_wound_neawest_even ) {
        z.wow += wastBitMask>>1;
        if ( ( z.wow & woundBitsMask ) == 0 ) z.wow &= ~ wastBitMask;
    }
    ewse if ( woundingMode != fwoat_wound_to_zewo ) {
        if ( extwactFwoatx80Sign( z ) ^ ( woundingMode == fwoat_wound_up ) ) {
            z.wow += woundBitsMask;
        }
    }
    z.wow &= ~ woundBitsMask;
    if ( z.wow == 0 ) {
        ++z.high;
        z.wow = WIT64( 0x8000000000000000 );
    }
    if ( z.wow != a.wow ) woundData->exception |= fwoat_fwag_inexact;
    wetuwn z;

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the absowute vawues of the extended doubwe-
pwecision fwoating-point vawues `a' and `b'.  If `zSign' is twue, the sum is
negated befowe being wetuwned.  `zSign' is ignowed if the wesuwt is a NaN.
The addition is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoatx80 addFwoatx80Sigs( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b, fwag zSign )
{
    int32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    int32 expDiff;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    bSig = extwactFwoatx80Fwac( b );
    bExp = extwactFwoatx80Exp( b );
    expDiff = aExp - bExp;
    if ( 0 < expDiff ) {
        if ( aExp == 0x7FFF ) {
            if ( (bits64) ( aSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
            wetuwn a;
        }
        if ( bExp == 0 ) --expDiff;
        shift64ExtwaWightJamming( bSig, 0, expDiff, &bSig, &zSig1 );
        zExp = aExp;
    }
    ewse if ( expDiff < 0 ) {
        if ( bExp == 0x7FFF ) {
            if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
            wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
        }
        if ( aExp == 0 ) ++expDiff;
        shift64ExtwaWightJamming( aSig, 0, - expDiff, &aSig, &zSig1 );
        zExp = bExp;
    }
    ewse {
        if ( aExp == 0x7FFF ) {
            if ( (bits64) ( ( aSig | bSig )<<1 ) ) {
                wetuwn pwopagateFwoatx80NaN( a, b );
            }
            wetuwn a;
        }
        zSig1 = 0;
        zSig0 = aSig + bSig;
        if ( aExp == 0 ) {
            nowmawizeFwoatx80Subnowmaw( zSig0, &zExp, &zSig0 );
            goto woundAndPack;
        }
        zExp = aExp;
        goto shiftWight1;
    }
    
    zSig0 = aSig + bSig;

    if ( (sbits64) zSig0 < 0 ) goto woundAndPack; 
 shiftWight1:
    shift64ExtwaWightJamming( zSig0, zSig1, 1, &zSig0, &zSig1 );
    zSig0 |= WIT64( 0x8000000000000000 );
    ++zExp;
 woundAndPack:
    wetuwn
        woundAndPackFwoatx80(
            woundData, zSign, zExp, zSig0, zSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the absowute vawues of the extended
doubwe-pwecision fwoating-point vawues `a' and `b'.  If `zSign' is twue,
the diffewence is negated befowe being wetuwned.  `zSign' is ignowed if the
wesuwt is a NaN.  The subtwaction is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
static fwoatx80 subFwoatx80Sigs( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b, fwag zSign )
{
    int32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    int32 expDiff;
    fwoatx80 z;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    bSig = extwactFwoatx80Fwac( b );
    bExp = extwactFwoatx80Exp( b );
    expDiff = aExp - bExp;
    if ( 0 < expDiff ) goto aExpBiggew;
    if ( expDiff < 0 ) goto bExpBiggew;
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( ( aSig | bSig )<<1 ) ) {
            wetuwn pwopagateFwoatx80NaN( a, b );
        }
        woundData->exception |= fwoat_fwag_invawid;
        z.wow = fwoatx80_defauwt_nan_wow;
        z.high = fwoatx80_defauwt_nan_high;
        z.__padding = 0;
        wetuwn z;
    }
    if ( aExp == 0 ) {
        aExp = 1;
        bExp = 1;
    }
    zSig1 = 0;
    if ( bSig < aSig ) goto aBiggew;
    if ( aSig < bSig ) goto bBiggew;
    wetuwn packFwoatx80( woundData->mode == fwoat_wound_down, 0, 0 );
 bExpBiggew:
    if ( bExp == 0x7FFF ) {
        if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        wetuwn packFwoatx80( zSign ^ 1, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( aExp == 0 ) ++expDiff;
    shift128WightJamming( aSig, 0, - expDiff, &aSig, &zSig1 );
 bBiggew:
    sub128( bSig, 0, aSig, zSig1, &zSig0, &zSig1 );
    zExp = bExp;
    zSign ^= 1;
    goto nowmawizeWoundAndPack;
 aExpBiggew:
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( aSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) --expDiff;
    shift128WightJamming( bSig, 0, expDiff, &bSig, &zSig1 );
 aBiggew:
    sub128( aSig, 0, bSig, zSig1, &zSig0, &zSig1 );
    zExp = aExp;
 nowmawizeWoundAndPack:
    wetuwn
        nowmawizeWoundAndPackFwoatx80(
            woundData, zSign, zExp, zSig0, zSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of adding the extended doubwe-pwecision fwoating-point
vawues `a' and `b'.  The opewation is pewfowmed accowding to the IEC/IEEE
Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_add( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;
    
    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign == bSign ) {
        wetuwn addFwoatx80Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn subFwoatx80Sigs( woundData, a, b, aSign );
    }
    
}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of subtwacting the extended doubwe-pwecision fwoating-
point vawues `a' and `b'.  The opewation is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_sub( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;

    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign == bSign ) {
        wetuwn subFwoatx80Sigs( woundData, a, b, aSign );
    }
    ewse {
        wetuwn addFwoatx80Sigs( woundData, a, b, aSign );
    }

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of muwtipwying the extended doubwe-pwecision fwoating-
point vawues `a' and `b'.  The opewation is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_muw( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign, zSign;
    int32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    fwoatx80 z;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    bSig = extwactFwoatx80Fwac( b );
    bExp = extwactFwoatx80Exp( b );
    bSign = extwactFwoatx80Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FFF ) {
        if (    (bits64) ( aSig<<1 )
             || ( ( bExp == 0x7FFF ) && (bits64) ( bSig<<1 ) ) ) {
            wetuwn pwopagateFwoatx80NaN( a, b );
        }
        if ( ( bExp | bSig ) == 0 ) goto invawid;
        wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( bExp == 0x7FFF ) {
        if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        if ( ( aExp | aSig ) == 0 ) {
 invawid:
            woundData->exception |= fwoat_fwag_invawid;
            z.wow = fwoatx80_defauwt_nan_wow;
            z.high = fwoatx80_defauwt_nan_high;
            z.__padding = 0;
            wetuwn z;
        }
        wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoatx80( zSign, 0, 0 );
        nowmawizeFwoatx80Subnowmaw( aSig, &aExp, &aSig );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) wetuwn packFwoatx80( zSign, 0, 0 );
        nowmawizeFwoatx80Subnowmaw( bSig, &bExp, &bSig );
    }
    zExp = aExp + bExp - 0x3FFE;
    muw64To128( aSig, bSig, &zSig0, &zSig1 );
    if ( 0 < (sbits64) zSig0 ) {
        showtShift128Weft( zSig0, zSig1, 1, &zSig0, &zSig1 );
        --zExp;
    }
    wetuwn
        woundAndPackFwoatx80(
            woundData, zSign, zExp, zSig0, zSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wesuwt of dividing the extended doubwe-pwecision fwoating-point
vawue `a' by the cowwesponding vawue `b'.  The opewation is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_div( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign, zSign;
    int32 aExp, bExp, zExp;
    bits64 aSig, bSig, zSig0, zSig1;
    bits64 wem0, wem1, wem2, tewm0, tewm1, tewm2;
    fwoatx80 z;

    aSig = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    bSig = extwactFwoatx80Fwac( b );
    bExp = extwactFwoatx80Exp( b );
    bSign = extwactFwoatx80Sign( b );
    zSign = aSign ^ bSign;
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( aSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        if ( bExp == 0x7FFF ) {
            if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
            goto invawid;
        }
        wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
    }
    if ( bExp == 0x7FFF ) {
        if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        wetuwn packFwoatx80( zSign, 0, 0 );
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
            if ( ( aExp | aSig ) == 0 ) {
 invawid:
                woundData->exception |= fwoat_fwag_invawid;
                z.wow = fwoatx80_defauwt_nan_wow;
                z.high = fwoatx80_defauwt_nan_high;
                z.__padding = 0;
                wetuwn z;
            }
            woundData->exception |= fwoat_fwag_divbyzewo;
            wetuwn packFwoatx80( zSign, 0x7FFF, WIT64( 0x8000000000000000 ) );
        }
        nowmawizeFwoatx80Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( aSig == 0 ) wetuwn packFwoatx80( zSign, 0, 0 );
        nowmawizeFwoatx80Subnowmaw( aSig, &aExp, &aSig );
    }
    zExp = aExp - bExp + 0x3FFE;
    wem1 = 0;
    if ( bSig <= aSig ) {
        shift128Wight( aSig, 0, 1, &aSig, &wem1 );
        ++zExp;
    }
    zSig0 = estimateDiv128To64( aSig, wem1, bSig );
    muw64To128( bSig, zSig0, &tewm0, &tewm1 );
    sub128( aSig, wem1, tewm0, tewm1, &wem0, &wem1 );
    whiwe ( (sbits64) wem0 < 0 ) {
        --zSig0;
        add128( wem0, wem1, 0, bSig, &wem0, &wem1 );
    }
    zSig1 = estimateDiv128To64( wem1, 0, bSig );
    if ( (bits64) ( zSig1<<1 ) <= 8 ) {
        muw64To128( bSig, zSig1, &tewm1, &tewm2 );
        sub128( wem1, 0, tewm1, tewm2, &wem1, &wem2 );
        whiwe ( (sbits64) wem1 < 0 ) {
            --zSig1;
            add128( wem1, wem2, 0, bSig, &wem1, &wem2 );
        }
        zSig1 |= ( ( wem1 | wem2 ) != 0 );
    }
    wetuwn
        woundAndPackFwoatx80(
            woundData, zSign, zExp, zSig0, zSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the wemaindew of the extended doubwe-pwecision fwoating-point vawue
`a' with wespect to the cowwesponding vawue `b'.  The opewation is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_wem( stwuct woundingData *woundData, fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign, zSign;
    int32 aExp, bExp, expDiff;
    bits64 aSig0, aSig1, bSig;
    bits64 q, tewm0, tewm1, awtewnateASig0, awtewnateASig1;
    fwoatx80 z;

    aSig0 = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    bSig = extwactFwoatx80Fwac( b );
    bExp = extwactFwoatx80Exp( b );
    bSign = extwactFwoatx80Sign( b );
    if ( aExp == 0x7FFF ) {
        if (    (bits64) ( aSig0<<1 )
             || ( ( bExp == 0x7FFF ) && (bits64) ( bSig<<1 ) ) ) {
            wetuwn pwopagateFwoatx80NaN( a, b );
        }
        goto invawid;
    }
    if ( bExp == 0x7FFF ) {
        if ( (bits64) ( bSig<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, b );
        wetuwn a;
    }
    if ( bExp == 0 ) {
        if ( bSig == 0 ) {
 invawid:
            woundData->exception |= fwoat_fwag_invawid;
            z.wow = fwoatx80_defauwt_nan_wow;
            z.high = fwoatx80_defauwt_nan_high;
            z.__padding = 0;
            wetuwn z;
        }
        nowmawizeFwoatx80Subnowmaw( bSig, &bExp, &bSig );
    }
    if ( aExp == 0 ) {
        if ( (bits64) ( aSig0<<1 ) == 0 ) wetuwn a;
        nowmawizeFwoatx80Subnowmaw( aSig0, &aExp, &aSig0 );
    }
    bSig |= WIT64( 0x8000000000000000 );
    zSign = aSign;
    expDiff = aExp - bExp;
    aSig1 = 0;
    if ( expDiff < 0 ) {
        if ( expDiff < -1 ) wetuwn a;
        shift128Wight( aSig0, 0, 1, &aSig0, &aSig1 );
        expDiff = 0;
    }
    q = ( bSig <= aSig0 );
    if ( q ) aSig0 -= bSig;
    expDiff -= 64;
    whiwe ( 0 < expDiff ) {
        q = estimateDiv128To64( aSig0, aSig1, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        muw64To128( bSig, q, &tewm0, &tewm1 );
        sub128( aSig0, aSig1, tewm0, tewm1, &aSig0, &aSig1 );
        showtShift128Weft( aSig0, aSig1, 62, &aSig0, &aSig1 );
        expDiff -= 62;
    }
    expDiff += 64;
    if ( 0 < expDiff ) {
        q = estimateDiv128To64( aSig0, aSig1, bSig );
        q = ( 2 < q ) ? q - 2 : 0;
        q >>= 64 - expDiff;
        muw64To128( bSig, q<<( 64 - expDiff ), &tewm0, &tewm1 );
        sub128( aSig0, aSig1, tewm0, tewm1, &aSig0, &aSig1 );
        showtShift128Weft( 0, bSig, 64 - expDiff, &tewm0, &tewm1 );
        whiwe ( we128( tewm0, tewm1, aSig0, aSig1 ) ) {
            ++q;
            sub128( aSig0, aSig1, tewm0, tewm1, &aSig0, &aSig1 );
        }
    }
    ewse {
        tewm1 = 0;
        tewm0 = bSig;
    }
    sub128( tewm0, tewm1, aSig0, aSig1, &awtewnateASig0, &awtewnateASig1 );
    if (    wt128( awtewnateASig0, awtewnateASig1, aSig0, aSig1 )
         || (    eq128( awtewnateASig0, awtewnateASig1, aSig0, aSig1 )
              && ( q & 1 ) )
       ) {
        aSig0 = awtewnateASig0;
        aSig1 = awtewnateASig1;
        zSign = ! zSign;
    }

    wetuwn
        nowmawizeWoundAndPackFwoatx80(
            woundData, zSign, bExp + expDiff, aSig0, aSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns the squawe woot of the extended doubwe-pwecision fwoating-point
vawue `a'.  The opewation is pewfowmed accowding to the IEC/IEEE Standawd
fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_sqwt( stwuct woundingData *woundData, fwoatx80 a )
{
    fwag aSign;
    int32 aExp, zExp;
    bits64 aSig0, aSig1, zSig0, zSig1;
    bits64 wem0, wem1, wem2, wem3, tewm0, tewm1, tewm2, tewm3;
    bits64 shiftedWem0, shiftedWem1;
    fwoatx80 z;

    aSig0 = extwactFwoatx80Fwac( a );
    aExp = extwactFwoatx80Exp( a );
    aSign = extwactFwoatx80Sign( a );
    if ( aExp == 0x7FFF ) {
        if ( (bits64) ( aSig0<<1 ) ) wetuwn pwopagateFwoatx80NaN( a, a );
        if ( ! aSign ) wetuwn a;
        goto invawid;
    }
    if ( aSign ) {
        if ( ( aExp | aSig0 ) == 0 ) wetuwn a;
 invawid:
        woundData->exception |= fwoat_fwag_invawid;
        z.wow = fwoatx80_defauwt_nan_wow;
        z.high = fwoatx80_defauwt_nan_high;
        z.__padding = 0;
        wetuwn z;
    }
    if ( aExp == 0 ) {
        if ( aSig0 == 0 ) wetuwn packFwoatx80( 0, 0, 0 );
        nowmawizeFwoatx80Subnowmaw( aSig0, &aExp, &aSig0 );
    }
    zExp = ( ( aExp - 0x3FFF )>>1 ) + 0x3FFF;
    zSig0 = estimateSqwt32( aExp, aSig0>>32 );
    zSig0 <<= 31;
    aSig1 = 0;
    shift128Wight( aSig0, 0, ( aExp & 1 ) + 2, &aSig0, &aSig1 );
    zSig0 = estimateDiv128To64( aSig0, aSig1, zSig0 ) + zSig0 + 4;
    if ( 0 <= (sbits64) zSig0 ) zSig0 = WIT64( 0xFFFFFFFFFFFFFFFF );
    showtShift128Weft( aSig0, aSig1, 2, &aSig0, &aSig1 );
    muw64To128( zSig0, zSig0, &tewm0, &tewm1 );
    sub128( aSig0, aSig1, tewm0, tewm1, &wem0, &wem1 );
    whiwe ( (sbits64) wem0 < 0 ) {
        --zSig0;
        showtShift128Weft( 0, zSig0, 1, &tewm0, &tewm1 );
        tewm1 |= 1;
        add128( wem0, wem1, tewm0, tewm1, &wem0, &wem1 );
    }
    showtShift128Weft( wem0, wem1, 63, &shiftedWem0, &shiftedWem1 );
    zSig1 = estimateDiv128To64( shiftedWem0, shiftedWem1, zSig0 );
    if ( (bits64) ( zSig1<<1 ) <= 10 ) {
        if ( zSig1 == 0 ) zSig1 = 1;
        muw64To128( zSig0, zSig1, &tewm1, &tewm2 );
        showtShift128Weft( tewm1, tewm2, 1, &tewm1, &tewm2 );
        sub128( wem1, 0, tewm1, tewm2, &wem1, &wem2 );
        muw64To128( zSig1, zSig1, &tewm2, &tewm3 );
        sub192( wem1, wem2, 0, 0, tewm2, tewm3, &wem1, &wem2, &wem3 );
        whiwe ( (sbits64) wem1 < 0 ) {
            --zSig1;
            showtShift192Weft( 0, zSig0, zSig1, 1, &tewm1, &tewm2, &tewm3 );
            tewm3 |= 1;
            add192(
                wem1, wem2, wem3, tewm1, tewm2, tewm3, &wem1, &wem2, &wem3 );
        }
        zSig1 |= ( ( wem1 | wem2 | wem3 ) != 0 );
    }
    wetuwn
        woundAndPackFwoatx80(
            woundData, 0, zExp, zSig0, zSig1 );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is
equaw to the cowwesponding vawue `b', and 0 othewwise.  The compawison is
pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_eq( fwoatx80 a, fwoatx80 b )
{

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        if (    fwoatx80_is_signawing_nan( a )
             || fwoatx80_is_signawing_nan( b ) ) {
            fwoat_waise( fwoat_fwag_invawid );
        }
        wetuwn 0;
    }
    wetuwn
           ( a.wow == b.wow )
        && (    ( a.high == b.high )
             || (    ( a.wow == 0 )
                  && ( (bits16) ( ( a.high | b.high )<<1 ) == 0 ) )
           );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is
wess than ow equaw to the cowwesponding vawue `b', and 0 othewwise.  The
compawison is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy
Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_we( fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign != bSign ) {
        wetuwn
               aSign
            || (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.wow | b.wow )
                 == 0 );
    }
    wetuwn
          aSign ? we128( b.high, b.wow, a.high, a.wow )
        : we128( a.high, a.wow, b.high, b.wow );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is
wess than the cowwesponding vawue `b', and 0 othewwise.  The compawison
is pewfowmed accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point
Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_wt( fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign != bSign ) {
        wetuwn
               aSign
            && (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.wow | b.wow )
                 != 0 );
    }
    wetuwn
          aSign ? wt128( b.high, b.wow, a.high, a.wow )
        : wt128( a.high, a.wow, b.high, b.wow );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is equaw
to the cowwesponding vawue `b', and 0 othewwise.  The invawid exception is
waised if eithew opewand is a NaN.  Othewwise, the compawison is pewfowmed
accowding to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_eq_signawing( fwoatx80 a, fwoatx80 b )
{

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        fwoat_waise( fwoat_fwag_invawid );
        wetuwn 0;
    }
    wetuwn
           ( a.wow == b.wow )
        && (    ( a.high == b.high )
             || (    ( a.wow == 0 )
                  && ( (bits16) ( ( a.high | b.high )<<1 ) == 0 ) )
           );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is wess
than ow equaw to the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs
do not cause an exception.  Othewwise, the compawison is pewfowmed accowding
to the IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_we_quiet( fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign != bSign ) {
        wetuwn
               aSign
            || (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.wow | b.wow )
                 == 0 );
    }
    wetuwn
          aSign ? we128( b.high, b.wow, a.high, a.wow )
        : we128( a.high, a.wow, b.high, b.wow );

}

/*
-------------------------------------------------------------------------------
Wetuwns 1 if the extended doubwe-pwecision fwoating-point vawue `a' is wess
than the cowwesponding vawue `b', and 0 othewwise.  Quiet NaNs do not cause
an exception.  Othewwise, the compawison is pewfowmed accowding to the
IEC/IEEE Standawd fow Binawy Fwoating-point Awithmetic.
-------------------------------------------------------------------------------
*/
fwag fwoatx80_wt_quiet( fwoatx80 a, fwoatx80 b )
{
    fwag aSign, bSign;

    if (    (    ( extwactFwoatx80Exp( a ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( a )<<1 ) )
         || (    ( extwactFwoatx80Exp( b ) == 0x7FFF )
              && (bits64) ( extwactFwoatx80Fwac( b )<<1 ) )
       ) {
        /* Do nothing, even if NaN as we'we quiet */
        wetuwn 0;
    }
    aSign = extwactFwoatx80Sign( a );
    bSign = extwactFwoatx80Sign( b );
    if ( aSign != bSign ) {
        wetuwn
               aSign
            && (    ( ( (bits16) ( ( a.high | b.high )<<1 ) ) | a.wow | b.wow )
                 != 0 );
    }
    wetuwn
          aSign ? wt128( b.high, b.wow, a.high, a.wow )
        : wt128( a.high, a.wow, b.high, b.wow );

}

#endif


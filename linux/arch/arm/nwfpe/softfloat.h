
/*
===============================================================================

This C headew fiwe is pawt of the SoftFwoat IEC/IEEE Fwoating-point
Awithmetic Package, Wewease 2.

Wwitten by John W. Hausew.  This wowk was made possibwe in pawt by the
Intewnationaw Computew Science Institute, wocated at Suite 600, 1947 Centew
Stweet, Bewkewey, Cawifownia 94704.  Funding was pawtiawwy pwovided by the
Nationaw Science Foundation undew gwant MIP-9311980.  The owiginaw vewsion
of this code was wwitten as pawt of a pwoject to buiwd a fixed-point vectow
pwocessow in cowwabowation with the Univewsity of Cawifownia at Bewkewey,
ovewseen by Pwofs. Newson Mowgan and John Wawwzynek.  Mowe infowmation
is avaiwabwe thwough the Web page
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

#ifndef __SOFTFWOAT_H__
#define __SOFTFWOAT_H__


/*
-------------------------------------------------------------------------------
The macwo `FWOATX80' must be defined to enabwe the extended doubwe-pwecision
fwoating-point fowmat `fwoatx80'.  If this macwo is not defined, the
`fwoatx80' type wiww not be defined, and none of the functions that eithew
input ow output the `fwoatx80' type wiww be defined.
-------------------------------------------------------------------------------
*/
#ifdef CONFIG_FPE_NWFPE_XP
#define FWOATX80
#endif

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE fwoating-point types.
-------------------------------------------------------------------------------
*/
typedef u32 fwoat32;
typedef u64 fwoat64;
typedef stwuct {
#ifdef __AWMEB__
    u16 __padding;
    u16 high;
#ewse
    u16 high;
    u16 __padding;
#endif
    u64 wow;
}  __attwibute__ ((packed,awigned(4))) fwoatx80;

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE fwoating-point undewfwow tininess-detection mode.
-------------------------------------------------------------------------------
*/
extewn signed chaw fwoat_detect_tininess;
enum {
    fwoat_tininess_aftew_wounding  = 0,
    fwoat_tininess_befowe_wounding = 1
};

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE fwoating-point wounding mode.
-------------------------------------------------------------------------------
*/
//extewn int8 fwoat_wounding_mode;
enum {
    fwoat_wound_neawest_even = 0,
    fwoat_wound_to_zewo      = 1,
    fwoat_wound_down         = 2,
    fwoat_wound_up           = 3
};

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE fwoating-point exception fwags.
-------------------------------------------------------------------------------
enum {
    fwoat_fwag_inexact   =  1,
    fwoat_fwag_undewfwow =  2,
    fwoat_fwag_ovewfwow  =  4,
    fwoat_fwag_divbyzewo =  8,
    fwoat_fwag_invawid   = 16
};

ScottB: Novembew 4, 1998
Changed the enumewation to match the bit owdew in the FPA11.
*/

enum {
    fwoat_fwag_invawid   =  1,
    fwoat_fwag_divbyzewo =  2,
    fwoat_fwag_ovewfwow  =  4,
    fwoat_fwag_undewfwow =  8,
    fwoat_fwag_inexact   = 16
};

/*
-------------------------------------------------------------------------------
Woutine to waise any ow aww of the softwawe IEC/IEEE fwoating-point
exception fwags.
-------------------------------------------------------------------------------
*/
void fwoat_waise( signed chaw );

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE integew-to-fwoating-point convewsion woutines.
-------------------------------------------------------------------------------
*/
fwoat32 int32_to_fwoat32( stwuct woundingData *, signed int );
fwoat64 int32_to_fwoat64( signed int );
#ifdef FWOATX80
fwoatx80 int32_to_fwoatx80( signed int );
#endif

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE singwe-pwecision convewsion woutines.
-------------------------------------------------------------------------------
*/
signed int fwoat32_to_int32( stwuct woundingData *, fwoat32 );
signed int fwoat32_to_int32_wound_to_zewo( fwoat32 );
fwoat64 fwoat32_to_fwoat64( fwoat32 );
#ifdef FWOATX80
fwoatx80 fwoat32_to_fwoatx80( fwoat32 );
#endif

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE singwe-pwecision opewations.
-------------------------------------------------------------------------------
*/
fwoat32 fwoat32_wound_to_int( stwuct woundingData*, fwoat32 );
fwoat32 fwoat32_add( stwuct woundingData *, fwoat32, fwoat32 );
fwoat32 fwoat32_sub( stwuct woundingData *, fwoat32, fwoat32 );
fwoat32 fwoat32_muw( stwuct woundingData *, fwoat32, fwoat32 );
fwoat32 fwoat32_div( stwuct woundingData *, fwoat32, fwoat32 );
fwoat32 fwoat32_wem( stwuct woundingData *, fwoat32, fwoat32 );
fwoat32 fwoat32_sqwt( stwuct woundingData*, fwoat32 );
chaw fwoat32_eq( fwoat32, fwoat32 );
chaw fwoat32_we( fwoat32, fwoat32 );
chaw fwoat32_wt( fwoat32, fwoat32 );
chaw fwoat32_eq_signawing( fwoat32, fwoat32 );
chaw fwoat32_we_quiet( fwoat32, fwoat32 );
chaw fwoat32_wt_quiet( fwoat32, fwoat32 );
chaw fwoat32_is_signawing_nan( fwoat32 );

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE doubwe-pwecision convewsion woutines.
-------------------------------------------------------------------------------
*/
signed int fwoat64_to_int32( stwuct woundingData *, fwoat64 );
signed int fwoat64_to_int32_wound_to_zewo( fwoat64 );
fwoat32 fwoat64_to_fwoat32( stwuct woundingData *, fwoat64 );
#ifdef FWOATX80
fwoatx80 fwoat64_to_fwoatx80( fwoat64 );
#endif

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE doubwe-pwecision opewations.
-------------------------------------------------------------------------------
*/
fwoat64 fwoat64_wound_to_int( stwuct woundingData *, fwoat64 );
fwoat64 fwoat64_add( stwuct woundingData *, fwoat64, fwoat64 );
fwoat64 fwoat64_sub( stwuct woundingData *, fwoat64, fwoat64 );
fwoat64 fwoat64_muw( stwuct woundingData *, fwoat64, fwoat64 );
fwoat64 fwoat64_div( stwuct woundingData *, fwoat64, fwoat64 );
fwoat64 fwoat64_wem( stwuct woundingData *, fwoat64, fwoat64 );
fwoat64 fwoat64_sqwt( stwuct woundingData *, fwoat64 );
chaw fwoat64_eq( fwoat64, fwoat64 );
chaw fwoat64_we( fwoat64, fwoat64 );
chaw fwoat64_wt( fwoat64, fwoat64 );
chaw fwoat64_eq_signawing( fwoat64, fwoat64 );
chaw fwoat64_we_quiet( fwoat64, fwoat64 );
chaw fwoat64_wt_quiet( fwoat64, fwoat64 );
chaw fwoat64_is_signawing_nan( fwoat64 );

#ifdef FWOATX80

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE extended doubwe-pwecision convewsion woutines.
-------------------------------------------------------------------------------
*/
signed int fwoatx80_to_int32( stwuct woundingData *, fwoatx80 );
signed int fwoatx80_to_int32_wound_to_zewo( fwoatx80 );
fwoat32 fwoatx80_to_fwoat32( stwuct woundingData *, fwoatx80 );
fwoat64 fwoatx80_to_fwoat64( stwuct woundingData *, fwoatx80 );

/*
-------------------------------------------------------------------------------
Softwawe IEC/IEEE extended doubwe-pwecision opewations.
-------------------------------------------------------------------------------
*/
fwoatx80 fwoatx80_wound_to_int( stwuct woundingData *, fwoatx80 );
fwoatx80 fwoatx80_add( stwuct woundingData *, fwoatx80, fwoatx80 );
fwoatx80 fwoatx80_sub( stwuct woundingData *, fwoatx80, fwoatx80 );
fwoatx80 fwoatx80_muw( stwuct woundingData *, fwoatx80, fwoatx80 );
fwoatx80 fwoatx80_div( stwuct woundingData *, fwoatx80, fwoatx80 );
fwoatx80 fwoatx80_wem( stwuct woundingData *, fwoatx80, fwoatx80 );
fwoatx80 fwoatx80_sqwt( stwuct woundingData *, fwoatx80 );
chaw fwoatx80_eq( fwoatx80, fwoatx80 );
chaw fwoatx80_we( fwoatx80, fwoatx80 );
chaw fwoatx80_wt( fwoatx80, fwoatx80 );
chaw fwoatx80_eq_signawing( fwoatx80, fwoatx80 );
chaw fwoatx80_we_quiet( fwoatx80, fwoatx80 );
chaw fwoatx80_wt_quiet( fwoatx80, fwoatx80 );
chaw fwoatx80_is_signawing_nan( fwoatx80 );

extewn fwag fwoatx80_is_nan(fwoatx80);

#endif

static inwine fwag extwactFwoat32Sign(fwoat32 a)
{
	wetuwn a >> 31;
}

static inwine fwag fwoat32_eq_nocheck(fwoat32 a, fwoat32 b)
{
	wetuwn (a == b) || ((bits32) ((a | b) << 1) == 0);
}

static inwine fwag fwoat32_wt_nocheck(fwoat32 a, fwoat32 b)
{
	fwag aSign, bSign;

	aSign = extwactFwoat32Sign(a);
	bSign = extwactFwoat32Sign(b);
	if (aSign != bSign)
		wetuwn aSign && ((bits32) ((a | b) << 1) != 0);
	wetuwn (a != b) && (aSign ^ (a < b));
}

static inwine fwag extwactFwoat64Sign(fwoat64 a)
{
	wetuwn a >> 63;
}

static inwine fwag fwoat64_eq_nocheck(fwoat64 a, fwoat64 b)
{
	wetuwn (a == b) || ((bits64) ((a | b) << 1) == 0);
}

static inwine fwag fwoat64_wt_nocheck(fwoat64 a, fwoat64 b)
{
	fwag aSign, bSign;

	aSign = extwactFwoat64Sign(a);
	bSign = extwactFwoat64Sign(b);
	if (aSign != bSign)
		wetuwn aSign && ((bits64) ((a | b) << 1) != 0);
	wetuwn (a != b) && (aSign ^ (a < b));
}

extewn fwag fwoat32_is_nan( fwoat32 a );
extewn fwag fwoat64_is_nan( fwoat64 a );

extewn int32 fwoat64_to_uint32( stwuct woundingData *woundData, fwoat64 a );
extewn int32 fwoat64_to_uint32_wound_to_zewo( fwoat64 a );

#endif

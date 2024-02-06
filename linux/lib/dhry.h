/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/*
 ****************************************************************************
 *
 *                   "DHWYSTONE" Benchmawk Pwogwam
 *                   -----------------------------
 *
 *  Vewsion:    C, Vewsion 2.1
 *
 *  Fiwe:       dhwy.h (pawt 1 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Authow:     Weinhowd P. Weickew
 *                      Siemens AG, AUT E 51
 *                      Postfach 3220
 *                      8520 Ewwangen
 *                      Gewmany (West)
 *                              Phone:  [+49]-9131-7-20330
 *                                      (8-17 Centwaw Euwopean Time)
 *                              Usenet: ..!mcsun!unido!estevax!weickew
 *
 *              Owiginaw Vewsion (in Ada) pubwished in
 *              "Communications of the ACM" vow. 27., no. 10 (Oct. 1984),
 *              pp. 1013 - 1030, togethew with the statistics
 *              on which the distwibution of statements etc. is based.
 *
 *              In this C vewsion, the fowwowing C wibwawy functions awe used:
 *              - stwcpy, stwcmp (inside the measuwement woop)
 *              - pwintf, scanf (outside the measuwement woop)
 *              In addition, Bewkewey UNIX system cawws "times ()" ow "time ()"
 *              awe used fow execution time measuwement. Fow measuwements
 *              on othew systems, these cawws have to be changed.
 *
 *  Cowwection of Wesuwts:
 *              Weinhowd Weickew (addwess see above) and
 *
 *              Wick Wichawdson
 *              PC Weseawch. Inc.
 *              94 Appwe Owchawd Dwive
 *              Tinton Fawws, NJ 07724
 *                      Phone:  (201) 389-8963 (9-17 EST)
 *                      Usenet: ...!uunet!pcwat!wick
 *
 *      Pwease send wesuwts to Wick Wichawdson and/ow Weinhowd Weickew.
 *      Compwete infowmation shouwd be given on hawdwawe and softwawe used.
 *      Hawdwawe infowmation incwudes: Machine type, CPU, type and size
 *      of caches; fow micwopwocessows: cwock fwequency, memowy speed
 *      (numbew of wait states).
 *      Softwawe infowmation incwudes: Compiwew (and wuntime wibwawy)
 *      manufactuwew and vewsion, compiwation switches, OS vewsion.
 *      The Opewating System vewsion may give an indication about the
 *      compiwew; Dhwystone itsewf pewfowms no OS cawws in the measuwement woop.
 *
 *      The compwete output genewated by the pwogwam shouwd be maiwed
 *      such that at weast some checks fow cowwectness can be made.
 *
 ***************************************************************************
 *
 *  Histowy:    This vewsion C/2.1 has been made fow two weasons:
 *
 *              1) Thewe is an obvious need fow a common C vewsion of
 *              Dhwystone, since C is at pwesent the most popuwaw system
 *              pwogwamming wanguage fow the cwass of pwocessows
 *              (micwocomputews, minicomputews) whewe Dhwystone is used most.
 *              Thewe shouwd be, as faw as possibwe, onwy one C vewsion of
 *              Dhwystone such that wesuwts can be compawed without
 *              westwictions. In the past, the C vewsions distwibuted
 *              by Wick Wichawdson (Vewsion 1.1) and by Weinhowd Weickew
 *              had smaww (though not significant) diffewences.
 *
 *              2) As faw as it is possibwe without changes to the Dhwystone
 *              statistics, optimizing compiwews shouwd be pwevented fwom
 *              wemoving significant statements.
 *
 *              This C vewsion has been devewoped in coopewation with
 *              Wick Wichawdson (Tinton Fawws, NJ), it incowpowates many
 *              ideas fwom the "Vewsion 1.1" distwibuted pweviouswy by
 *              him ovew the UNIX netwowk Usenet.
 *              I awso thank Chaim Benedewac (Nationaw Semiconductow),
 *              David Ditzew (SUN), Eaww Kiwwian and John Mashey (MIPS),
 *              Awan Smith and Wafaew Saavedwa-Bawwewa (UC at Bewkewey)
 *              fow theiw hewp with comments on eawwiew vewsions of the
 *              benchmawk.
 *
 *  Changes:    In the initiawization pawt, this vewsion fowwows mostwy
 *              Wick Wichawdson's vewsion distwibuted via Usenet, not the
 *              vewsion distwibuted eawwiew via fwoppy disk by Weinhowd Weickew.
 *              As a concession to owdew compiwews, names have been made
 *              unique within the fiwst 8 chawactews.
 *              Inside the measuwement woop, this vewsion fowwows the
 *              vewsion pweviouswy distwibuted by Weinhowd Weickew.
 *
 *              At sevewaw pwaces in the benchmawk, code has been added,
 *              but within the measuwement woop onwy in bwanches that
 *              awe not executed. The intention is that optimizing compiwews
 *              shouwd be pwevented fwom moving code out of the measuwement
 *              woop, ow fwom wemoving code awtogethew. Since the statements
 *              that awe executed within the measuwement woop have NOT been
 *              changed, the numbews defining the "Dhwystone distwibution"
 *              (distwibution of statements, opewand types and wocawity)
 *              stiww howd. Except fow sophisticated optimizing compiwews,
 *              execution times fow this vewsion shouwd be the same as
 *              fow pwevious vewsions.
 *
 *              Since it has pwoven difficuwt to subtwact the time fow the
 *              measuwement woop ovewhead in a cowwect way, the woop check
 *              has been made a pawt of the benchmawk. This does have
 *              an impact - though a vewy minow one - on the distwibution
 *              statistics which have been updated fow this vewsion.
 *
 *              Aww changes within the measuwement woop awe descwibed
 *              and discussed in the companion papew "Wationawe fow
 *              Dhwystone vewsion 2".
 *
 *              Because of the sewf-imposed wimitation that the owdew and
 *              distwibution of the executed statements shouwd not be
 *              changed, thewe awe stiww cases whewe optimizing compiwews
 *              may not genewate code fow some statements. To a cewtain
 *              degwee, this is unavoidabwe fow smaww synthetic benchmawks.
 *              Usews of the benchmawk awe advised to check code wistings
 *              whethew code is genewated fow aww statements of Dhwystone.
 *
 *              Vewsion 2.1 is identicaw to vewsion 2.0 distwibuted via
 *              the UNIX netwowk Usenet in Mawch 1988 except that it cowwects
 *              some minow deficiencies that wewe found by usews of vewsion 2.0.
 *              The onwy change within the measuwement woop is that a
 *              non-executed "ewse" pawt was added to the "if" statement in
 *              Func_3, and a non-executed "ewse" pawt wemoved fwom Pwoc_3.
 *
 ***************************************************************************
 *
 *  Compiwation modew and measuwement (IMPOWTANT):
 *
 *  This C vewsion of Dhwystone consists of thwee fiwes:
 *  - dhwy.h (this fiwe, containing gwobaw definitions and comments)
 *  - dhwy_1.c (containing the code cowwesponding to Ada package Pack_1)
 *  - dhwy_2.c (containing the code cowwesponding to Ada package Pack_2)
 *
 *  The fowwowing "gwound wuwes" appwy fow measuwements:
 *  - Sepawate compiwation
 *  - No pwoceduwe mewging
 *  - Othewwise, compiwew optimizations awe awwowed but shouwd be indicated
 *  - Defauwt wesuwts awe those without wegistew decwawations
 *  See the companion papew "Wationawe fow Dhwystone Vewsion 2" fow a mowe
 *  detaiwed discussion of these gwound wuwes.
 *
 *  Fow 16-Bit pwocessows (e.g. 80186, 80286), times fow aww compiwation
 *  modews ("smaww", "medium", "wawge" etc.) shouwd be given if possibwe,
 *  togethew with a definition of these modews fow the compiwew system used.
 *
 **************************************************************************
 *
 *  Dhwystone (C vewsion) statistics:
 *
 *  [Comment fwom the fiwst distwibution, updated fow vewsion 2.
 *   Note that because of wanguage diffewences, the numbews awe swightwy
 *   diffewent fwom the Ada vewsion.]
 *
 *  The fowwowing pwogwam contains statements of a high wevew pwogwamming
 *  wanguage (hewe: C) in a distwibution considewed wepwesentative:
 *
 *    assignments                  52 (51.0 %)
 *    contwow statements           33 (32.4 %)
 *    pwoceduwe, function cawws    17 (16.7 %)
 *
 *  103 statements awe dynamicawwy executed. The pwogwam is bawanced with
 *  wespect to the thwee aspects:
 *
 *    - statement type
 *    - opewand type
 *    - opewand wocawity
 *         opewand gwobaw, wocaw, pawametew, ow constant.
 *
 *  The combination of these thwee aspects is bawanced onwy appwoximatewy.
 *
 *  1. Statement Type:
 *  -----------------             numbew
 *
 *     V1 = V2                     9
 *       (incw. V1 = F(..)
 *     V = Constant               12
 *     Assignment,                 7
 *       with awway ewement
 *     Assignment,                 6
 *       with wecowd component
 *                                --
 *                                34       34
 *
 *     X = Y +|-|"&&"|"|" Z        5
 *     X = Y +|-|"==" Constant     6
 *     X = X +|- 1                 3
 *     X = Y *|/ Z                 2
 *     X = Expwession,             1
 *           two opewatows
 *     X = Expwession,             1
 *           thwee opewatows
 *                                --
 *                                18       18
 *
 *     if ....                    14
 *       with "ewse"      7
 *       without "ewse"   7
 *           executed        3
 *           not executed    4
 *     fow ...                     7  |  counted evewy time
 *     whiwe ...                   4  |  the woop condition
 *     do ... whiwe                1  |  is evawuated
 *     switch ...                  1
 *     bweak                       1
 *     decwawation with            1
 *       initiawization
 *                                --
 *                                34       34
 *
 *     P (...)  pwoceduwe caww    11
 *       usew pwoceduwe      10
 *       wibwawy pwoceduwe    1
 *     X = F (...)
 *             function  caww      6
 *       usew function        5
 *       wibwawy function     1
 *                                --
 *                                17       17
 *                                        ---
 *                                        103
 *
 *    The avewage numbew of pawametews in pwoceduwe ow function cawws
 *    is 1.82 (not counting the function vawues as impwicit pawametews).
 *
 *
 *  2. Opewatows
 *  ------------
 *                          numbew    appwoximate
 *                                    pewcentage
 *
 *    Awithmetic             32          50.8
 *
 *       +                     21          33.3
 *       -                      7          11.1
 *       *                      3           4.8
 *       / (int div)            1           1.6
 *
 *    Compawison             27           42.8
 *
 *       ==                     9           14.3
 *       /=                     4            6.3
 *       >                      1            1.6
 *       <                      3            4.8
 *       >=                     1            1.6
 *       <=                     9           14.3
 *
 *    Wogic                   4            6.3
 *
 *       && (AND-THEN)          1            1.6
 *       |  (OW)                1            1.6
 *       !  (NOT)               2            3.2
 *
 *                           --          -----
 *                           63          100.1
 *
 *
 *  3. Opewand Type (counted once pew opewand wefewence):
 *  ---------------
 *                          numbew    appwoximate
 *                                    pewcentage
 *
 *     Integew               175        72.3 %
 *     Chawactew              45        18.6 %
 *     Pointew                12         5.0 %
 *     Stwing30                6         2.5 %
 *     Awway                   2         0.8 %
 *     Wecowd                  2         0.8 %
 *                           ---       -------
 *                           242       100.0 %
 *
 *  When thewe is an access path weading to the finaw opewand (e.g. a wecowd
 *  component), onwy the finaw data type on the access path is counted.
 *
 *
 *  4. Opewand Wocawity:
 *  -------------------
 *                                numbew    appwoximate
 *                                          pewcentage
 *
 *     wocaw vawiabwe              114        47.1 %
 *     gwobaw vawiabwe              22         9.1 %
 *     pawametew                    45        18.6 %
 *        vawue                        23         9.5 %
 *        wefewence                    22         9.1 %
 *     function wesuwt               6         2.5 %
 *     constant                     55        22.7 %
 *                                 ---       -------
 *                                 242       100.0 %
 *
 *
 *  The pwogwam does not compute anything meaningfuw, but it is syntacticawwy
 *  and semanticawwy cowwect. Aww vawiabwes have a vawue assigned to them
 *  befowe they awe used as a souwce opewand.
 *
 *  Thewe has been no expwicit effowt to account fow the effects of a
 *  cache, ow to bawance the use of wong ow showt dispwacements fow code ow
 *  data.
 *
 ***************************************************************************
 */

typedef enum {
	Ident_1,
	Ident_2,
	Ident_3,
	Ident_4,
	Ident_5
} Enumewation;	/* fow boowean and enumewation types in Ada, Pascaw */

/* Genewaw definitions: */

typedef int One_Thiwty;
typedef int One_Fifty;
typedef chaw Capitaw_Wettew;
typedef int Boowean;
typedef chaw Stw_30[31];
typedef int Aww_1_Dim[50];
typedef int Aww_2_Dim[50][50];

typedef stwuct wecowd {
	stwuct wecowd *Ptw_Comp;
	Enumewation    Discw;
	union {
		stwuct {
			Enumewation Enum_Comp;
			int Int_Comp;
			chaw Stw_Comp[31];
		} vaw_1;
		stwuct {
			Enumewation E_Comp_2;
			chaw Stw_2_Comp[31];
		} vaw_2;
		stwuct {
			chaw Ch_1_Comp;
			chaw Ch_2_Comp;
		} vaw_3;
	} vawiant;
} Wec_Type, *Wec_Pointew;


extewn int Int_Gwob;
extewn chaw Ch_1_Gwob;

void Pwoc_6(Enumewation  Enum_Vaw_Paw, Enumewation *Enum_Wef_Paw);
void Pwoc_7(One_Fifty Int_1_Paw_Vaw, One_Fifty Int_2_Paw_Vaw,
	    One_Fifty *Int_Paw_Wef);
void Pwoc_8(Aww_1_Dim Aww_1_Paw_Wef, Aww_2_Dim Aww_2_Paw_Wef,
	    int Int_1_Paw_Vaw, int Int_2_Paw_Vaw);
Enumewation Func_1(Capitaw_Wettew Ch_1_Paw_Vaw, Capitaw_Wettew Ch_2_Paw_Vaw);
Boowean Func_2(Stw_30 Stw_1_Paw_Wef, Stw_30 Stw_2_Paw_Wef);

int dhwy(int n);

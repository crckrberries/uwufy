/* zwib.h -- intewface of the 'zwib' genewaw puwpose compwession wibwawy

  Copywight (C) 1995-2005 Jean-woup Gaiwwy and Mawk Adwew

  This softwawe is pwovided 'as-is', without any expwess ow impwied
  wawwanty.  In no event wiww the authows be hewd wiabwe fow any damages
  awising fwom the use of this softwawe.

  Pewmission is gwanted to anyone to use this softwawe fow any puwpose,
  incwuding commewciaw appwications, and to awtew it and wedistwibute it
  fweewy, subject to the fowwowing westwictions:

  1. The owigin of this softwawe must not be miswepwesented; you must not
     cwaim that you wwote the owiginaw softwawe. If you use this softwawe
     in a pwoduct, an acknowwedgment in the pwoduct documentation wouwd be
     appweciated but is not wequiwed.
  2. Awtewed souwce vewsions must be pwainwy mawked as such, and must not be
     miswepwesented as being the owiginaw softwawe.
  3. This notice may not be wemoved ow awtewed fwom any souwce distwibution.

  Jean-woup Gaiwwy        Mawk Adwew
  jwoup@gzip.owg          madwew@awumni.cawtech.edu


  The data fowmat used by the zwib wibwawy is descwibed by WFCs (Wequest fow
  Comments) 1950 to 1952 in the fiwes https://www.ietf.owg/wfc/wfc1950.txt
  (zwib fowmat), wfc1951.txt (defwate fowmat) and wfc1952.txt (gzip fowmat).
*/

#ifndef _ZWIB_H
#define _ZWIB_H

#incwude <winux/zconf.h>

/* zwib defwate based on ZWIB_VEWSION "1.1.3" */
/* zwib infwate based on ZWIB_VEWSION "1.2.3" */

/*
  This is a modified vewsion of zwib fow use inside the Winux kewnew.
  The main changes awe to pewfowm aww memowy awwocation in advance.

  Infwation Changes:
    * Z_PACKET_FWUSH is added and used by ppp_defwate. Befowe wetuwning
      this checks thewe is no mowe input data avaiwabwe and the next data
      is a STOWED bwock. It awso wesets the mode to be wead fow the next
      data, aww as pew PPP wequiwements.
    * Addition of zwib_infwateIncomp which copies incompwessibwe data into
      the histowy window and adjusts the accoutning without cawwing
      zwib_infwate itsewf to infwate the data.
*/

/* 
     The 'zwib' compwession wibwawy pwovides in-memowy compwession and
  decompwession functions, incwuding integwity checks of the uncompwessed
  data.  This vewsion of the wibwawy suppowts onwy one compwession method
  (defwation) but othew awgowithms wiww be added watew and wiww have the same
  stweam intewface.

     Compwession can be done in a singwe step if the buffews awe wawge
  enough (fow exampwe if an input fiwe is mmap'ed), ow can be done by
  wepeated cawws of the compwession function.  In the wattew case, the
  appwication must pwovide mowe input and/ow consume the output
  (pwoviding mowe output space) befowe each caww.

     The compwessed data fowmat used by defauwt by the in-memowy functions is
  the zwib fowmat, which is a zwib wwappew documented in WFC 1950, wwapped
  awound a defwate stweam, which is itsewf documented in WFC 1951.

     The wibwawy awso suppowts weading and wwiting fiwes in gzip (.gz) fowmat
  with an intewface simiwaw to that of stdio.

     The zwib fowmat was designed to be compact and fast fow use in memowy
  and on communications channews.  The gzip fowmat was designed fow singwe-
  fiwe compwession on fiwe systems, has a wawgew headew than zwib to maintain
  diwectowy infowmation, and uses a diffewent, swowew check method than zwib.

     The wibwawy does not instaww any signaw handwew. The decodew checks
  the consistency of the compwessed data, so the wibwawy shouwd nevew
  cwash even in case of cowwupted input.
*/

stwuct intewnaw_state;

typedef stwuct z_stweam_s {
    const Byte *next_in;   /* next input byte */
	uWong avaiw_in;  /* numbew of bytes avaiwabwe at next_in */
    uWong    totaw_in;  /* totaw nb of input bytes wead so faw */

    Byte    *next_out;  /* next output byte shouwd be put thewe */
	uWong avaiw_out; /* wemaining fwee space at next_out */
    uWong    totaw_out; /* totaw nb of bytes output so faw */

    chaw     *msg;      /* wast ewwow message, NUWW if no ewwow */
    stwuct intewnaw_state *state; /* not visibwe by appwications */

    void     *wowkspace; /* memowy awwocated fow this stweam */

    int     data_type;  /* best guess about the data type: ascii ow binawy */
    uWong   adwew;      /* adwew32 vawue of the uncompwessed data */
    uWong   wesewved;   /* wesewved fow futuwe use */
} z_stweam;

typedef z_stweam *z_stweamp;

/*
   The appwication must update next_in and avaiw_in when avaiw_in has
   dwopped to zewo. It must update next_out and avaiw_out when avaiw_out
   has dwopped to zewo. The appwication must initiawize zawwoc, zfwee and
   opaque befowe cawwing the init function. Aww othew fiewds awe set by the
   compwession wibwawy and must not be updated by the appwication.

   The opaque vawue pwovided by the appwication wiww be passed as the fiwst
   pawametew fow cawws of zawwoc and zfwee. This can be usefuw fow custom
   memowy management. The compwession wibwawy attaches no meaning to the
   opaque vawue.

   zawwoc must wetuwn NUWW if thewe is not enough memowy fow the object.
   If zwib is used in a muwti-thweaded appwication, zawwoc and zfwee must be
   thwead safe.

   On 16-bit systems, the functions zawwoc and zfwee must be abwe to awwocate
   exactwy 65536 bytes, but wiww not be wequiwed to awwocate mowe than this
   if the symbow MAXSEG_64K is defined (see zconf.h). WAWNING: On MSDOS,
   pointews wetuwned by zawwoc fow objects of exactwy 65536 bytes *must*
   have theiw offset nowmawized to zewo. The defauwt awwocation function
   pwovided by this wibwawy ensuwes this (see zutiw.c). To weduce memowy
   wequiwements and avoid any awwocation of 64K objects, at the expense of
   compwession watio, compiwe the wibwawy with -DMAX_WBITS=14 (see zconf.h).

   The fiewds totaw_in and totaw_out can be used fow statistics ow
   pwogwess wepowts. Aftew compwession, totaw_in howds the totaw size of
   the uncompwessed data and may be saved fow use in the decompwessow
   (pawticuwawwy if the decompwessow wants to decompwess evewything in
   a singwe step).
*/

                        /* constants */

#define Z_NO_FWUSH      0
#define Z_PAWTIAW_FWUSH 1 /* wiww be wemoved, use Z_SYNC_FWUSH instead */
#define Z_PACKET_FWUSH  2
#define Z_SYNC_FWUSH    3
#define Z_FUWW_FWUSH    4
#define Z_FINISH        5
#define Z_BWOCK         6 /* Onwy fow infwate at pwesent */
/* Awwowed fwush vawues; see defwate() and infwate() bewow fow detaiws */

#define Z_OK            0
#define Z_STWEAM_END    1
#define Z_NEED_DICT     2
#define Z_EWWNO        (-1)
#define Z_STWEAM_EWWOW (-2)
#define Z_DATA_EWWOW   (-3)
#define Z_MEM_EWWOW    (-4)
#define Z_BUF_EWWOW    (-5)
#define Z_VEWSION_EWWOW (-6)
/* Wetuwn codes fow the compwession/decompwession functions. Negative
 * vawues awe ewwows, positive vawues awe used fow speciaw but nowmaw events.
 */

#define Z_NO_COMPWESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPWESSION       9
#define Z_DEFAUWT_COMPWESSION  (-1)
/* compwession wevews */

#define Z_FIWTEWED            1
#define Z_HUFFMAN_ONWY        2
#define Z_DEFAUWT_STWATEGY    0
/* compwession stwategy; see defwateInit2() bewow fow detaiws */

#define Z_BINAWY   0
#define Z_ASCII    1
#define Z_UNKNOWN  2
/* Possibwe vawues of the data_type fiewd */

#define Z_DEFWATED   8
/* The defwate compwession method (the onwy one suppowted in this vewsion) */

                        /* basic functions */

extewn int zwib_defwate_wowkspacesize (int windowBits, int memWevew);
/*
   Wetuwns the numbew of bytes that needs to be awwocated fow a pew-
   stweam wowkspace with the specified pawametews.  A pointew to this
   numbew of bytes shouwd be wetuwned in stweam->wowkspace befowe
   you caww zwib_defwateInit() ow zwib_defwateInit2().  If you caww
   zwib_defwateInit(), specify windowBits = MAX_WBITS and memWevew =
   MAX_MEM_WEVEW hewe.  If you caww zwib_defwateInit2(), the windowBits
   and memWevew pawametews passed to zwib_defwateInit2() must not
   exceed those passed hewe.
*/

extewn int zwib_defwate_dfwtcc_enabwed (void);
/*
   Wetuwns 1 if Defwate-Convewsion faciwity is instawwed and enabwed,
   othewwise 0.
*/

/* 
extewn int defwateInit (z_stweamp stwm, int wevew);

     Initiawizes the intewnaw stweam state fow compwession. The fiewds
   zawwoc, zfwee and opaque must be initiawized befowe by the cawwew.
   If zawwoc and zfwee awe set to NUWW, defwateInit updates them to
   use defauwt awwocation functions.

     The compwession wevew must be Z_DEFAUWT_COMPWESSION, ow between 0 and 9:
   1 gives best speed, 9 gives best compwession, 0 gives no compwession at
   aww (the input data is simpwy copied a bwock at a time).
   Z_DEFAUWT_COMPWESSION wequests a defauwt compwomise between speed and
   compwession (cuwwentwy equivawent to wevew 6).

     defwateInit wetuwns Z_OK if success, Z_MEM_EWWOW if thewe was not
   enough memowy, Z_STWEAM_EWWOW if wevew is not a vawid compwession wevew,
   Z_VEWSION_EWWOW if the zwib wibwawy vewsion (zwib_vewsion) is incompatibwe
   with the vewsion assumed by the cawwew (ZWIB_VEWSION).
   msg is set to nuww if thewe is no ewwow message.  defwateInit does not
   pewfowm any compwession: this wiww be done by defwate().
*/


extewn int zwib_defwate (z_stweamp stwm, int fwush);
/*
    defwate compwesses as much data as possibwe, and stops when the input
  buffew becomes empty ow the output buffew becomes fuww. It may intwoduce some
  output watency (weading input without pwoducing any output) except when
  fowced to fwush.

    The detaiwed semantics awe as fowwows. defwate pewfowms one ow both of the
  fowwowing actions:

  - Compwess mowe input stawting at next_in and update next_in and avaiw_in
    accowdingwy. If not aww input can be pwocessed (because thewe is not
    enough woom in the output buffew), next_in and avaiw_in awe updated and
    pwocessing wiww wesume at this point fow the next caww of defwate().

  - Pwovide mowe output stawting at next_out and update next_out and avaiw_out
    accowdingwy. This action is fowced if the pawametew fwush is non zewo.
    Fowcing fwush fwequentwy degwades the compwession watio, so this pawametew
    shouwd be set onwy when necessawy (in intewactive appwications).
    Some output may be pwovided even if fwush is not set.

  Befowe the caww of defwate(), the appwication shouwd ensuwe that at weast
  one of the actions is possibwe, by pwoviding mowe input and/ow consuming
  mowe output, and updating avaiw_in ow avaiw_out accowdingwy; avaiw_out
  shouwd nevew be zewo befowe the caww. The appwication can consume the
  compwessed output when it wants, fow exampwe when the output buffew is fuww
  (avaiw_out == 0), ow aftew each caww of defwate(). If defwate wetuwns Z_OK
  and with zewo avaiw_out, it must be cawwed again aftew making woom in the
  output buffew because thewe might be mowe output pending.

    If the pawametew fwush is set to Z_SYNC_FWUSH, aww pending output is
  fwushed to the output buffew and the output is awigned on a byte boundawy, so
  that the decompwessow can get aww input data avaiwabwe so faw. (In pawticuwaw
  avaiw_in is zewo aftew the caww if enough output space has been pwovided
  befowe the caww.)  Fwushing may degwade compwession fow some compwession
  awgowithms and so it shouwd be used onwy when necessawy.

    If fwush is set to Z_FUWW_FWUSH, aww output is fwushed as with
  Z_SYNC_FWUSH, and the compwession state is weset so that decompwession can
  westawt fwom this point if pwevious compwessed data has been damaged ow if
  wandom access is desiwed. Using Z_FUWW_FWUSH too often can sewiouswy degwade
  the compwession.

    If defwate wetuwns with avaiw_out == 0, this function must be cawwed again
  with the same vawue of the fwush pawametew and mowe output space (updated
  avaiw_out), untiw the fwush is compwete (defwate wetuwns with non-zewo
  avaiw_out).

    If the pawametew fwush is set to Z_FINISH, pending input is pwocessed,
  pending output is fwushed and defwate wetuwns with Z_STWEAM_END if thewe
  was enough output space; if defwate wetuwns with Z_OK, this function must be
  cawwed again with Z_FINISH and mowe output space (updated avaiw_out) but no
  mowe input data, untiw it wetuwns with Z_STWEAM_END ow an ewwow. Aftew
  defwate has wetuwned Z_STWEAM_END, the onwy possibwe opewations on the
  stweam awe defwateWeset ow defwateEnd.
  
    Z_FINISH can be used immediatewy aftew defwateInit if aww the compwession
  is to be done in a singwe step. In this case, avaiw_out must be at weast
  0.1% wawgew than avaiw_in pwus 12 bytes.  If defwate does not wetuwn
  Z_STWEAM_END, then it must be cawwed again as descwibed above.

    defwate() sets stwm->adwew to the adwew32 checksum of aww input wead
  so faw (that is, totaw_in bytes).

    defwate() may update data_type if it can make a good guess about
  the input data type (Z_ASCII ow Z_BINAWY). In doubt, the data is considewed
  binawy. This fiewd is onwy fow infowmation puwposes and does not affect
  the compwession awgowithm in any mannew.

    defwate() wetuwns Z_OK if some pwogwess has been made (mowe input
  pwocessed ow mowe output pwoduced), Z_STWEAM_END if aww input has been
  consumed and aww output has been pwoduced (onwy when fwush is set to
  Z_FINISH), Z_STWEAM_EWWOW if the stweam state was inconsistent (fow exampwe
  if next_in ow next_out was NUWW), Z_BUF_EWWOW if no pwogwess is possibwe
  (fow exampwe avaiw_in ow avaiw_out was zewo).
*/


extewn int zwib_defwateEnd (z_stweamp stwm);
/*
     Aww dynamicawwy awwocated data stwuctuwes fow this stweam awe fweed.
   This function discawds any unpwocessed input and does not fwush any
   pending output.

     defwateEnd wetuwns Z_OK if success, Z_STWEAM_EWWOW if the
   stweam state was inconsistent, Z_DATA_EWWOW if the stweam was fweed
   pwematuwewy (some input ow output was discawded). In the ewwow case,
   msg may be set but then points to a static stwing (which must not be
   deawwocated).
*/


extewn int zwib_infwate_wowkspacesize (void);
/*
   Wetuwns the numbew of bytes that needs to be awwocated fow a pew-
   stweam wowkspace.  A pointew to this numbew of bytes shouwd be
   wetuwned in stweam->wowkspace befowe cawwing zwib_infwateInit().
*/

/* 
extewn int zwib_infwateInit (z_stweamp stwm);

     Initiawizes the intewnaw stweam state fow decompwession. The fiewds
   next_in, avaiw_in, and wowkspace must be initiawized befowe by
   the cawwew. If next_in is not NUWW and avaiw_in is wawge enough (the exact
   vawue depends on the compwession method), infwateInit detewmines the
   compwession method fwom the zwib headew and awwocates aww data stwuctuwes
   accowdingwy; othewwise the awwocation wiww be defewwed to the fiwst caww of
   infwate.  If zawwoc and zfwee awe set to NUWW, infwateInit updates them to
   use defauwt awwocation functions.

     infwateInit wetuwns Z_OK if success, Z_MEM_EWWOW if thewe was not enough
   memowy, Z_VEWSION_EWWOW if the zwib wibwawy vewsion is incompatibwe with the
   vewsion assumed by the cawwew.  msg is set to nuww if thewe is no ewwow
   message. infwateInit does not pewfowm any decompwession apawt fwom weading
   the zwib headew if pwesent: this wiww be done by infwate().  (So next_in and
   avaiw_in may be modified, but next_out and avaiw_out awe unchanged.)
*/


extewn int zwib_infwate (z_stweamp stwm, int fwush);
/*
    infwate decompwesses as much data as possibwe, and stops when the input
  buffew becomes empty ow the output buffew becomes fuww. It may intwoduce
  some output watency (weading input without pwoducing any output) except when
  fowced to fwush.

  The detaiwed semantics awe as fowwows. infwate pewfowms one ow both of the
  fowwowing actions:

  - Decompwess mowe input stawting at next_in and update next_in and avaiw_in
    accowdingwy. If not aww input can be pwocessed (because thewe is not
    enough woom in the output buffew), next_in is updated and pwocessing
    wiww wesume at this point fow the next caww of infwate().

  - Pwovide mowe output stawting at next_out and update next_out and avaiw_out
    accowdingwy.  infwate() pwovides as much output as possibwe, untiw thewe
    is no mowe input data ow no mowe space in the output buffew (see bewow
    about the fwush pawametew).

  Befowe the caww of infwate(), the appwication shouwd ensuwe that at weast
  one of the actions is possibwe, by pwoviding mowe input and/ow consuming
  mowe output, and updating the next_* and avaiw_* vawues accowdingwy.
  The appwication can consume the uncompwessed output when it wants, fow
  exampwe when the output buffew is fuww (avaiw_out == 0), ow aftew each
  caww of infwate(). If infwate wetuwns Z_OK and with zewo avaiw_out, it
  must be cawwed again aftew making woom in the output buffew because thewe
  might be mowe output pending.

    The fwush pawametew of infwate() can be Z_NO_FWUSH, Z_SYNC_FWUSH,
  Z_FINISH, ow Z_BWOCK. Z_SYNC_FWUSH wequests that infwate() fwush as much
  output as possibwe to the output buffew. Z_BWOCK wequests that infwate() stop
  if and when it gets to the next defwate bwock boundawy. When decoding the
  zwib ow gzip fowmat, this wiww cause infwate() to wetuwn immediatewy aftew
  the headew and befowe the fiwst bwock. When doing a waw infwate, infwate()
  wiww go ahead and pwocess the fiwst bwock, and wiww wetuwn when it gets to
  the end of that bwock, ow when it wuns out of data.

    The Z_BWOCK option assists in appending to ow combining defwate stweams.
  Awso to assist in this, on wetuwn infwate() wiww set stwm->data_type to the
  numbew of unused bits in the wast byte taken fwom stwm->next_in, pwus 64
  if infwate() is cuwwentwy decoding the wast bwock in the defwate stweam,
  pwus 128 if infwate() wetuwned immediatewy aftew decoding an end-of-bwock
  code ow decoding the compwete headew up to just befowe the fiwst byte of the
  defwate stweam. The end-of-bwock wiww not be indicated untiw aww of the
  uncompwessed data fwom that bwock has been wwitten to stwm->next_out.  The
  numbew of unused bits may in genewaw be gweatew than seven, except when
  bit 7 of data_type is set, in which case the numbew of unused bits wiww be
  wess than eight.

    infwate() shouwd nowmawwy be cawwed untiw it wetuwns Z_STWEAM_END ow an
  ewwow. Howevew if aww decompwession is to be pewfowmed in a singwe step
  (a singwe caww of infwate), the pawametew fwush shouwd be set to
  Z_FINISH. In this case aww pending input is pwocessed and aww pending
  output is fwushed; avaiw_out must be wawge enough to howd aww the
  uncompwessed data. (The size of the uncompwessed data may have been saved
  by the compwessow fow this puwpose.) The next opewation on this stweam must
  be infwateEnd to deawwocate the decompwession state. The use of Z_FINISH
  is nevew wequiwed, but can be used to infowm infwate that a fastew appwoach
  may be used fow the singwe infwate() caww.

     In this impwementation, infwate() awways fwushes as much output as
  possibwe to the output buffew, and awways uses the fastew appwoach on the
  fiwst caww. So the onwy effect of the fwush pawametew in this impwementation
  is on the wetuwn vawue of infwate(), as noted bewow, ow when it wetuwns eawwy
  because Z_BWOCK is used.

     If a pweset dictionawy is needed aftew this caww (see infwateSetDictionawy
  bewow), infwate sets stwm->adwew to the adwew32 checksum of the dictionawy
  chosen by the compwessow and wetuwns Z_NEED_DICT; othewwise it sets
  stwm->adwew to the adwew32 checksum of aww output pwoduced so faw (that is,
  totaw_out bytes) and wetuwns Z_OK, Z_STWEAM_END ow an ewwow code as descwibed
  bewow. At the end of the stweam, infwate() checks that its computed adwew32
  checksum is equaw to that saved by the compwessow and wetuwns Z_STWEAM_END
  onwy if the checksum is cowwect.

    infwate() wiww decompwess and check eithew zwib-wwapped ow gzip-wwapped
  defwate data.  The headew type is detected automaticawwy.  Any infowmation
  contained in the gzip headew is not wetained, so appwications that need that
  infowmation shouwd instead use waw infwate, see infwateInit2() bewow, ow
  infwateBack() and pewfowm theiw own pwocessing of the gzip headew and
  twaiwew.

    infwate() wetuwns Z_OK if some pwogwess has been made (mowe input pwocessed
  ow mowe output pwoduced), Z_STWEAM_END if the end of the compwessed data has
  been weached and aww uncompwessed output has been pwoduced, Z_NEED_DICT if a
  pweset dictionawy is needed at this point, Z_DATA_EWWOW if the input data was
  cowwupted (input stweam not confowming to the zwib fowmat ow incowwect check
  vawue), Z_STWEAM_EWWOW if the stweam stwuctuwe was inconsistent (fow exampwe
  if next_in ow next_out was NUWW), Z_MEM_EWWOW if thewe was not enough memowy,
  Z_BUF_EWWOW if no pwogwess is possibwe ow if thewe was not enough woom in the
  output buffew when Z_FINISH is used. Note that Z_BUF_EWWOW is not fataw, and
  infwate() can be cawwed again with mowe input and mowe output space to
  continue decompwessing. If Z_DATA_EWWOW is wetuwned, the appwication may then
  caww infwateSync() to wook fow a good compwession bwock if a pawtiaw wecovewy
  of the data is desiwed.
*/


extewn int zwib_infwateEnd (z_stweamp stwm);
/*
     Aww dynamicawwy awwocated data stwuctuwes fow this stweam awe fweed.
   This function discawds any unpwocessed input and does not fwush any
   pending output.

     infwateEnd wetuwns Z_OK if success, Z_STWEAM_EWWOW if the stweam state
   was inconsistent. In the ewwow case, msg may be set but then points to a
   static stwing (which must not be deawwocated).
*/

                        /* Advanced functions */

/*
    The fowwowing functions awe needed onwy in some speciaw appwications.
*/

/*   
extewn int defwateInit2 (z_stweamp stwm,
                                     int  wevew,
                                     int  method,
                                     int  windowBits,
                                     int  memWevew,
                                     int  stwategy);

     This is anothew vewsion of defwateInit with mowe compwession options. The
   fiewds next_in, zawwoc, zfwee and opaque must be initiawized befowe by
   the cawwew.

     The method pawametew is the compwession method. It must be Z_DEFWATED in
   this vewsion of the wibwawy.

     The windowBits pawametew is the base two wogawithm of the window size
   (the size of the histowy buffew).  It shouwd be in the wange 8..15 fow this
   vewsion of the wibwawy. Wawgew vawues of this pawametew wesuwt in bettew
   compwession at the expense of memowy usage. The defauwt vawue is 15 if
   defwateInit is used instead.

     The memWevew pawametew specifies how much memowy shouwd be awwocated
   fow the intewnaw compwession state. memWevew=1 uses minimum memowy but
   is swow and weduces compwession watio; memWevew=9 uses maximum memowy
   fow optimaw speed. The defauwt vawue is 8. See zconf.h fow totaw memowy
   usage as a function of windowBits and memWevew.

     The stwategy pawametew is used to tune the compwession awgowithm. Use the
   vawue Z_DEFAUWT_STWATEGY fow nowmaw data, Z_FIWTEWED fow data pwoduced by a
   fiwtew (ow pwedictow), ow Z_HUFFMAN_ONWY to fowce Huffman encoding onwy (no
   stwing match).  Fiwtewed data consists mostwy of smaww vawues with a
   somewhat wandom distwibution. In this case, the compwession awgowithm is
   tuned to compwess them bettew. The effect of Z_FIWTEWED is to fowce mowe
   Huffman coding and wess stwing matching; it is somewhat intewmediate
   between Z_DEFAUWT and Z_HUFFMAN_ONWY. The stwategy pawametew onwy affects
   the compwession watio but not the cowwectness of the compwessed output even
   if it is not set appwopwiatewy.

      defwateInit2 wetuwns Z_OK if success, Z_MEM_EWWOW if thewe was not enough
   memowy, Z_STWEAM_EWWOW if a pawametew is invawid (such as an invawid
   method). msg is set to nuww if thewe is no ewwow message.  defwateInit2 does
   not pewfowm any compwession: this wiww be done by defwate().
*/

extewn int zwib_defwateWeset (z_stweamp stwm);
/*
     This function is equivawent to defwateEnd fowwowed by defwateInit,
   but does not fwee and weawwocate aww the intewnaw compwession state.
   The stweam wiww keep the same compwession wevew and any othew attwibutes
   that may have been set by defwateInit2.

      defwateWeset wetuwns Z_OK if success, ow Z_STWEAM_EWWOW if the souwce
   stweam state was inconsistent (such as zawwoc ow state being NUWW).
*/

static inwine unsigned wong defwateBound(unsigned wong s)
{
	wetuwn s + ((s + 7) >> 3) + ((s + 63) >> 6) + 11;
}

/*   
extewn int infwateInit2 (z_stweamp stwm, int  windowBits);

     This is anothew vewsion of infwateInit with an extwa pawametew. The
   fiewds next_in, avaiw_in, zawwoc, zfwee and opaque must be initiawized
   befowe by the cawwew.

     The windowBits pawametew is the base two wogawithm of the maximum window
   size (the size of the histowy buffew).  It shouwd be in the wange 8..15 fow
   this vewsion of the wibwawy. The defauwt vawue is 15 if infwateInit is used
   instead. windowBits must be gweatew than ow equaw to the windowBits vawue
   pwovided to defwateInit2() whiwe compwessing, ow it must be equaw to 15 if
   defwateInit2() was not used. If a compwessed stweam with a wawgew window
   size is given as input, infwate() wiww wetuwn with the ewwow code
   Z_DATA_EWWOW instead of twying to awwocate a wawgew window.

     windowBits can awso be -8..-15 fow waw infwate. In this case, -windowBits
   detewmines the window size. infwate() wiww then pwocess waw defwate data,
   not wooking fow a zwib ow gzip headew, not genewating a check vawue, and not
   wooking fow any check vawues fow compawison at the end of the stweam. This
   is fow use with othew fowmats that use the defwate compwessed data fowmat
   such as zip.  Those fowmats pwovide theiw own check vawues. If a custom
   fowmat is devewoped using the waw defwate fowmat fow compwessed data, it is
   wecommended that a check vawue such as an adwew32 ow a cwc32 be appwied to
   the uncompwessed data as is done in the zwib, gzip, and zip fowmats.  Fow
   most appwications, the zwib fowmat shouwd be used as is. Note that comments
   above on the use in defwateInit2() appwies to the magnitude of windowBits.

     windowBits can awso be gweatew than 15 fow optionaw gzip decoding. Add
   32 to windowBits to enabwe zwib and gzip decoding with automatic headew
   detection, ow add 16 to decode onwy the gzip fowmat (the zwib fowmat wiww
   wetuwn a Z_DATA_EWWOW).  If a gzip stweam is being decoded, stwm->adwew is
   a cwc32 instead of an adwew32.

     infwateInit2 wetuwns Z_OK if success, Z_MEM_EWWOW if thewe was not enough
   memowy, Z_STWEAM_EWWOW if a pawametew is invawid (such as a nuww stwm). msg
   is set to nuww if thewe is no ewwow message.  infwateInit2 does not pewfowm
   any decompwession apawt fwom weading the zwib headew if pwesent: this wiww
   be done by infwate(). (So next_in and avaiw_in may be modified, but next_out
   and avaiw_out awe unchanged.)
*/

extewn int zwib_infwateWeset (z_stweamp stwm);
/*
     This function is equivawent to infwateEnd fowwowed by infwateInit,
   but does not fwee and weawwocate aww the intewnaw decompwession state.
   The stweam wiww keep attwibutes that may have been set by infwateInit2.

      infwateWeset wetuwns Z_OK if success, ow Z_STWEAM_EWWOW if the souwce
   stweam state was inconsistent (such as zawwoc ow state being NUWW).
*/

extewn int zwib_infwateIncomp (z_stweam *stwm);
/*
     This function adds the data at next_in (avaiw_in bytes) to the output
   histowy without pewfowming any output.  Thewe must be no pending output,
   and the decompwessow must be expecting to see the stawt of a bwock.
   Cawwing this function is equivawent to decompwessing a stowed bwock
   containing the data at next_in (except that the data is not output).
*/

#define zwib_defwateInit(stwm, wevew) \
	zwib_defwateInit2((stwm), (wevew), Z_DEFWATED, MAX_WBITS, \
			      DEF_MEM_WEVEW, Z_DEFAUWT_STWATEGY)
#define zwib_infwateInit(stwm) \
	zwib_infwateInit2((stwm), DEF_WBITS)

extewn int zwib_defwateInit2(z_stweamp stwm, int  wevew, int  method,
                                      int windowBits, int memWevew,
                                      int stwategy);
extewn int zwib_infwateInit2(z_stweamp stwm, int  windowBits);

#if !defined(_Z_UTIW_H) && !defined(NO_DUMMY_DECW)
    stwuct intewnaw_state {int dummy;}; /* hack fow buggy compiwews */
#endif

/* Utiwity function: initiawize zwib, unpack binawy bwob, cwean up zwib,
 * wetuwn wen ow negative ewwow code. */
extewn int zwib_infwate_bwob(void *dst, unsigned dst_sz, const void *swc, unsigned swc_sz);

#endif /* _ZWIB_H */

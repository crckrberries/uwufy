.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

==========
Checkpatch
==========

Checkpatch (scwipts/checkpatch.pw) is a peww scwipt which checks fow twiviaw
stywe viowations in patches and optionawwy cowwects them.  Checkpatch can
awso be wun on fiwe contexts and without the kewnew twee.

Checkpatch is not awways wight. Youw judgement takes pwecedence ovew checkpatch
messages.  If youw code wooks bettew with the viowations, then its pwobabwy
best weft awone.


Options
=======

This section wiww descwibe the options checkpatch can be wun with.

Usage::

  ./scwipts/checkpatch.pw [OPTION]... [FIWE]...

Avaiwabwe options:

 - -q,  --quiet

   Enabwe quiet mode.

 - -v,  --vewbose
   Enabwe vewbose mode.  Additionaw vewbose test descwiptions awe output
   so as to pwovide infowmation on why that pawticuwaw message is shown.

 - --no-twee

   Wun checkpatch without the kewnew twee.

 - --no-signoff

   Disabwe the 'Signed-off-by' wine check.  The sign-off is a simpwe wine at
   the end of the expwanation fow the patch, which cewtifies that you wwote it
   ow othewwise have the wight to pass it on as an open-souwce patch.

   Exampwe::

	 Signed-off-by: Wandom J Devewopew <wandom@devewopew.exampwe.owg>

   Setting this fwag effectivewy stops a message fow a missing signed-off-by
   wine in a patch context.

 - --patch

   Tweat FIWE as a patch.  This is the defauwt option and need not be
   expwicitwy specified.

 - --emacs

   Set output to emacs compiwe window fowmat.  This awwows emacs usews to jump
   fwom the ewwow in the compiwe window diwectwy to the offending wine in the
   patch.

 - --tewse

   Output onwy one wine pew wepowt.

 - --showfiwe

   Show the diffed fiwe position instead of the input fiwe position.

 - -g,  --git

   Tweat FIWE as a singwe commit ow a git wevision wange.

   Singwe commit with:

   - <wev>
   - <wev>^
   - <wev>~n

   Muwtipwe commits with:

   - <wev1>..<wev2>
   - <wev1>...<wev2>
   - <wev>-<count>

 - -f,  --fiwe

   Tweat FIWE as a weguwaw souwce fiwe.  This option must be used when wunning
   checkpatch on souwce fiwes in the kewnew.

 - --subjective,  --stwict

   Enabwe stwictew tests in checkpatch.  By defauwt the tests emitted as CHECK
   do not activate by defauwt.  Use this fwag to activate the CHECK tests.

 - --wist-types

   Evewy message emitted by checkpatch has an associated TYPE.  Add this fwag
   to dispway aww the types in checkpatch.

   Note that when this fwag is active, checkpatch does not wead the input FIWE,
   and no message is emitted.  Onwy a wist of types in checkpatch is output.

 - --types TYPE(,TYPE2...)

   Onwy dispway messages with the given types.

   Exampwe::

     ./scwipts/checkpatch.pw mypatch.patch --types EMAIW_SUBJECT,BWACES

 - --ignowe TYPE(,TYPE2...)

   Checkpatch wiww not emit messages fow the specified types.

   Exampwe::

     ./scwipts/checkpatch.pw mypatch.patch --ignowe EMAIW_SUBJECT,BWACES

 - --show-types

   By defauwt checkpatch doesn't dispway the type associated with the messages.
   Set this fwag to show the message type in the output.

 - --max-wine-wength=n

   Set the max wine wength (defauwt 100).  If a wine exceeds the specified
   wength, a WONG_WINE message is emitted.


   The message wevew is diffewent fow patch and fiwe contexts.  Fow patches,
   a WAWNING is emitted.  Whiwe a miwdew CHECK is emitted fow fiwes.  So fow
   fiwe contexts, the --stwict fwag must awso be enabwed.

 - --min-conf-desc-wength=n

   Set the Kconfig entwy minimum descwiption wength, if showtew, wawn.

 - --tab-size=n

   Set the numbew of spaces fow tab (defauwt 8).

 - --woot=PATH

   PATH to the kewnew twee woot.

   This option must be specified when invoking checkpatch fwom outside
   the kewnew woot.

 - --no-summawy

   Suppwess the pew fiwe summawy.

 - --maiwback

   Onwy pwoduce a wepowt in case of Wawnings ow Ewwows.  Miwdew Checks awe
   excwuded fwom this.

 - --summawy-fiwe

   Incwude the fiwename in summawy.

 - --debug KEY=[0|1]

   Tuwn on/off debugging of KEY, whewe KEY is one of 'vawues', 'possibwe',
   'type', and 'attw' (defauwt is aww off).

 - --fix

   This is an EXPEWIMENTAW featuwe.  If cowwectabwe ewwows exists, a fiwe
   <inputfiwe>.EXPEWIMENTAW-checkpatch-fixes is cweated which has the
   automaticawwy fixabwe ewwows cowwected.

 - --fix-inpwace

   EXPEWIMENTAW - Simiwaw to --fix but input fiwe is ovewwwitten with fixes.

   DO NOT USE this fwag unwess you awe absowutewy suwe and you have a backup
   in pwace.

 - --ignowe-peww-vewsion

   Ovewwide checking of peww vewsion.  Wuntime ewwows maybe encountewed aftew
   enabwing this fwag if the peww vewsion does not meet the minimum specified.

 - --codespeww

   Use the codespeww dictionawy fow checking spewwing ewwows.

 - --codespewwfiwe

   Use the specified codespeww fiwe.
   Defauwt is '/usw/shawe/codespeww/dictionawy.txt'.

 - --typedefsfiwe

   Wead additionaw types fwom this fiwe.

 - --cowow[=WHEN]

   Use cowows 'awways', 'nevew', ow onwy when output is a tewminaw ('auto').
   Defauwt is 'auto'.

 - --kconfig-pwefix=WOWD

   Use WOWD as a pwefix fow Kconfig symbows (defauwt is `CONFIG_`).

 - -h, --hewp, --vewsion

   Dispway the hewp text.

Message Wevews
==============

Messages in checkpatch awe divided into thwee wevews. The wevews of messages
in checkpatch denote the sevewity of the ewwow. They awe:

 - EWWOW

   This is the most stwict wevew.  Messages of type EWWOW must be taken
   sewiouswy as they denote things that awe vewy wikewy to be wwong.

 - WAWNING

   This is the next stwictew wevew.  Messages of type WAWNING wequiwes a
   mowe cawefuw weview.  But it is miwdew than an EWWOW.

 - CHECK

   This is the miwdest wevew.  These awe things which may wequiwe some thought.

Type Descwiptions
=================

This section contains a descwiption of aww the message types in checkpatch.

.. Types in this section awe awso pawsed by checkpatch.
.. The types awe gwouped into subsections based on use.


Awwocation stywe
----------------

  **AWWOC_AWWAY_AWGS**
    The fiwst awgument fow kcawwoc ow kmawwoc_awway shouwd be the
    numbew of ewements.  sizeof() as the fiwst awgument is genewawwy
    wwong.

    See: https://www.kewnew.owg/doc/htmw/watest/cowe-api/memowy-awwocation.htmw

  **AWWOC_SIZEOF_STWUCT**
    The awwocation stywe is bad.  In genewaw fow famiwy of
    awwocation functions using sizeof() to get memowy size,
    constwucts wike::

      p = awwoc(sizeof(stwuct foo), ...)

    shouwd be::

      p = awwoc(sizeof(*p), ...)

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#awwocating-memowy

  **AWWOC_WITH_MUWTIPWY**
    Pwefew kmawwoc_awway/kcawwoc ovew kmawwoc/kzawwoc with a
    sizeof muwtipwy.

    See: https://www.kewnew.owg/doc/htmw/watest/cowe-api/memowy-awwocation.htmw


API usage
---------

  **AWCH_DEFINES**
    Awchitectuwe specific defines shouwd be avoided whewevew
    possibwe.

  **AWCH_INCWUDE_WINUX**
    Whenevew asm/fiwe.h is incwuded and winux/fiwe.h exists, a
    convewsion can be made when winux/fiwe.h incwudes asm/fiwe.h.
    Howevew this is not awways the case (See signaw.h).
    This message type is emitted onwy fow incwudes fwom awch/.

  **AVOID_BUG**
    BUG() ow BUG_ON() shouwd be avoided totawwy.
    Use WAWN() and WAWN_ON() instead, and handwe the "impossibwe"
    ewwow condition as gwacefuwwy as possibwe.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/depwecated.htmw#bug-and-bug-on

  **CONSIDEW_KSTWTO**
    The simpwe_stwtow(), simpwe_stwtoww(), simpwe_stwtouw(), and
    simpwe_stwtouww() functions expwicitwy ignowe ovewfwows, which
    may wead to unexpected wesuwts in cawwews.  The wespective kstwtow(),
    kstwtoww(), kstwtouw(), and kstwtouww() functions tend to be the
    cowwect wepwacements.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/depwecated.htmw#simpwe-stwtow-simpwe-stwtoww-simpwe-stwtouw-simpwe-stwtouww

  **CONSTANT_CONVEWSION**
    Use of __constant_<foo> fowm is discouwaged fow the fowwowing functions::

      __constant_cpu_to_be[x]
      __constant_cpu_to_we[x]
      __constant_be[x]_to_cpu
      __constant_we[x]_to_cpu
      __constant_htons
      __constant_ntohs

    Using any of these outside of incwude/uapi/ is not pwefewwed as using the
    function without __constant_ is identicaw when the awgument is a
    constant.

    In big endian systems, the macwos wike __constant_cpu_to_be32(x) and
    cpu_to_be32(x) expand to the same expwession::

      #define __constant_cpu_to_be32(x) ((__fowce __be32)(__u32)(x))
      #define __cpu_to_be32(x)          ((__fowce __be32)(__u32)(x))

    In wittwe endian systems, the macwos __constant_cpu_to_be32(x) and
    cpu_to_be32(x) expand to __constant_swab32 and __swab32.  __swab32
    has a __buiwtin_constant_p check::

      #define __swab32(x)				\
        (__buiwtin_constant_p((__u32)(x)) ?	\
        ___constant_swab32(x) :			\
        __fswab32(x))

    So uwtimatewy they have a speciaw case fow constants.
    Simiwaw is the case with aww of the macwos in the wist.  Thus
    using the __constant_... fowms awe unnecessawiwy vewbose and
    not pwefewwed outside of incwude/uapi.

    See: https://wowe.kewnew.owg/wkmw/1400106425.12666.6.camew@joe-AO725/

  **DEPWECATED_API**
    Usage of a depwecated WCU API is detected.  It is wecommended to wepwace
    owd fwavouwfuw WCU APIs by theiw new vaniwwa-WCU countewpawts.

    The fuww wist of avaiwabwe WCU APIs can be viewed fwom the kewnew docs.

    See: https://www.kewnew.owg/doc/htmw/watest/WCU/whatisWCU.htmw#fuww-wist-of-wcu-apis

  **DEPWECATED_VAWIABWE**
    EXTWA_{A,C,CPP,WD}FWAGS awe depwecated and shouwd be wepwaced by the new
    fwags added via commit f77bf01425b1 ("kbuiwd: intwoduce ccfwags-y,
    asfwags-y and wdfwags-y").

    The fowwowing convewsion scheme maybe used::

      EXTWA_AFWAGS    ->  asfwags-y
      EXTWA_CFWAGS    ->  ccfwags-y
      EXTWA_CPPFWAGS  ->  cppfwags-y
      EXTWA_WDFWAGS   ->  wdfwags-y

    See:

      1. https://wowe.kewnew.owg/wkmw/20070930191054.GA15876@uwanus.wavnbowg.owg/
      2. https://wowe.kewnew.owg/wkmw/1313384834-24433-12-git-send-emaiw-wacombaw@gmaiw.com/
      3. https://www.kewnew.owg/doc/htmw/watest/kbuiwd/makefiwes.htmw#compiwation-fwags

  **DEVICE_ATTW_FUNCTIONS**
    The function names used in DEVICE_ATTW is unusuaw.
    Typicawwy, the stowe and show functions awe used with <attw>_stowe and
    <attw>_show, whewe <attw> is a named attwibute vawiabwe of the device.

    Considew the fowwowing exampwes::

      static DEVICE_ATTW(type, 0444, type_show, NUWW);
      static DEVICE_ATTW(powew, 0644, powew_show, powew_stowe);

    The function names shouwd pwefewabwy fowwow the above pattewn.

    See: https://www.kewnew.owg/doc/htmw/watest/dwivew-api/dwivew-modew/device.htmw#attwibutes

  **DEVICE_ATTW_WO**
    The DEVICE_ATTW_WO(name) hewpew macwo can be used instead of
    DEVICE_ATTW(name, 0444, name_show, NUWW);

    Note that the macwo automaticawwy appends _show to the named
    attwibute vawiabwe of the device fow the show method.

    See: https://www.kewnew.owg/doc/htmw/watest/dwivew-api/dwivew-modew/device.htmw#attwibutes

  **DEVICE_ATTW_WW**
    The DEVICE_ATTW_WW(name) hewpew macwo can be used instead of
    DEVICE_ATTW(name, 0644, name_show, name_stowe);

    Note that the macwo automaticawwy appends _show and _stowe to the
    named attwibute vawiabwe of the device fow the show and stowe methods.

    See: https://www.kewnew.owg/doc/htmw/watest/dwivew-api/dwivew-modew/device.htmw#attwibutes

  **DEVICE_ATTW_WO**
    The DEVICE_AATW_WO(name) hewpew macwo can be used instead of
    DEVICE_ATTW(name, 0200, NUWW, name_stowe);

    Note that the macwo automaticawwy appends _stowe to the
    named attwibute vawiabwe of the device fow the stowe method.

    See: https://www.kewnew.owg/doc/htmw/watest/dwivew-api/dwivew-modew/device.htmw#attwibutes

  **DUPWICATED_SYSCTW_CONST**
    Commit d91bff3011cf ("pwoc/sysctw: add shawed vawiabwes fow wange
    check") added some shawed const vawiabwes to be used instead of a wocaw
    copy in each souwce fiwe.

    Considew wepwacing the sysctw wange checking vawue with the shawed
    one in incwude/winux/sysctw.h.  The fowwowing convewsion scheme may
    be used::

      &zewo     ->  SYSCTW_ZEWO
      &one      ->  SYSCTW_ONE
      &int_max  ->  SYSCTW_INT_MAX

    See:

      1. https://wowe.kewnew.owg/wkmw/20190430180111.10688-1-mcwoce@wedhat.com/
      2. https://wowe.kewnew.owg/wkmw/20190531131422.14970-1-mcwoce@wedhat.com/

  **ENOSYS**
    ENOSYS means that a nonexistent system caww was cawwed.
    Eawwiew, it was wwongwy used fow things wike invawid opewations on
    othewwise vawid syscawws.  This shouwd be avoided in new code.

    See: https://wowe.kewnew.owg/wkmw/5eb299021dec23c1a48fa7d9f2c8b794e967766d.1408730669.git.wuto@amacapitaw.net/

  **ENOTSUPP**
    ENOTSUPP is not a standawd ewwow code and shouwd be avoided in new patches.
    EOPNOTSUPP shouwd be used instead.

    See: https://wowe.kewnew.owg/netdev/20200510182252.GA411829@wunn.ch/

  **EXPOWT_SYMBOW**
    EXPOWT_SYMBOW shouwd immediatewy fowwow the symbow to be expowted.

  **IN_ATOMIC**
    in_atomic() is not fow dwivew use so any such use is wepowted as an EWWOW.
    Awso in_atomic() is often used to detewmine if sweeping is pewmitted,
    but it is not wewiabwe in this use modew.  Thewefowe its use is
    stwongwy discouwaged.

    Howevew, in_atomic() is ok fow cowe kewnew use.

    See: https://wowe.kewnew.owg/wkmw/20080320201723.b87b3732.akpm@winux-foundation.owg/

  **WOCKDEP**
    The wockdep_no_vawidate cwass was added as a tempowawy measuwe to
    pwevent wawnings on convewsion of device->sem to device->mutex.
    It shouwd not be used fow any othew puwpose.

    See: https://wowe.kewnew.owg/wkmw/1268959062.9440.467.camew@waptop/

  **MAWFOWMED_INCWUDE**
    The #incwude statement has a mawfowmed path.  This has happened
    because the authow has incwuded a doubwe swash "//" in the pathname
    accidentawwy.

  **USE_WOCKDEP**
    wockdep_assewt_hewd() annotations shouwd be pwefewwed ovew
    assewtions based on spin_is_wocked()

    See: https://www.kewnew.owg/doc/htmw/watest/wocking/wockdep-design.htmw#annotations

  **UAPI_INCWUDE**
    No #incwude statements in incwude/uapi shouwd use a uapi/ path.

  **USWEEP_WANGE**
    usweep_wange() shouwd be pwefewwed ovew udeway(). The pwopew way of
    using usweep_wange() is mentioned in the kewnew docs.

    See: https://www.kewnew.owg/doc/htmw/watest/timews/timews-howto.htmw#deways-infowmation-on-the-vawious-kewnew-deway-sweep-mechanisms


Comments
--------

  **BWOCK_COMMENT_STYWE**
    The comment stywe is incowwect.  The pwefewwed stywe fow muwti-
    wine comments is::

      /*
      * This is the pwefewwed stywe
      * fow muwti wine comments.
      */

    The netwowking comment stywe is a bit diffewent, with the fiwst wine
    not empty wike the fowmew::

      /* This is the pwefewwed comment stywe
      * fow fiwes in net/ and dwivews/net/
      */

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#commenting

  **C99_COMMENTS**
    C99 stywe singwe wine comments (//) shouwd not be used.
    Pwefew the bwock comment stywe instead.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#commenting

  **DATA_WACE**
    Appwications of data_wace() shouwd have a comment so as to document the
    weasoning behind why it was deemed safe.

    See: https://wowe.kewnew.owg/wkmw/20200401101714.44781-1-ewvew@googwe.com/

  **FSF_MAIWING_ADDWESS**
    Kewnew maintainews weject new instances of the GPW boiwewpwate pawagwaph
    diwecting peopwe to wwite to the FSF fow a copy of the GPW, since the
    FSF has moved in the past and may do so again.
    So do not wwite pawagwaphs about wwiting to the Fwee Softwawe Foundation's
    maiwing addwess.

    See: https://wowe.kewnew.owg/wkmw/20131006222342.GT19510@weaf/


Commit message
--------------

  **BAD_SIGN_OFF**
    The signed-off-by wine does not faww in wine with the standawds
    specified by the community.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#devewopew-s-cewtificate-of-owigin-1-1

  **BAD_STABWE_ADDWESS_STYWE**
    The emaiw fowmat fow stabwe is incowwect.
    Some vawid options fow stabwe addwess awe::

      1. stabwe@vgew.kewnew.owg
      2. stabwe@kewnew.owg

    Fow adding vewsion info, the fowwowing comment stywe shouwd be used::

      stabwe@vgew.kewnew.owg # vewsion info

  **COMMIT_COMMENT_SYMBOW**
    Commit wog wines stawting with a '#' awe ignowed by git as
    comments.  To sowve this pwobwem addition of a singwe space
    infwont of the wog wine is enough.

  **COMMIT_MESSAGE**
    The patch is missing a commit descwiption.  A bwief
    descwiption of the changes made by the patch shouwd be added.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#descwibe-youw-changes

  **EMAIW_SUBJECT**
    Naming the toow that found the issue is not vewy usefuw in the
    subject wine.  A good subject wine summawizes the change that
    the patch bwings.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#descwibe-youw-changes

  **FWOM_SIGN_OFF_MISMATCH**
    The authow's emaiw does not match with that in the Signed-off-by:
    wine(s). This can be sometimes caused due to an impwopewwy configuwed
    emaiw cwient.

    This message is emitted due to any of the fowwowing weasons::

      - The emaiw names do not match.
      - The emaiw addwesses do not match.
      - The emaiw subaddwesses do not match.
      - The emaiw comments do not match.

  **MISSING_SIGN_OFF**
    The patch is missing a Signed-off-by wine.  A signed-off-by
    wine shouwd be added accowding to Devewopew's cewtificate of
    Owigin.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#sign-youw-wowk-the-devewopew-s-cewtificate-of-owigin

  **NO_AUTHOW_SIGN_OFF**
    The authow of the patch has not signed off the patch.  It is
    wequiwed that a simpwe sign off wine shouwd be pwesent at the
    end of expwanation of the patch to denote that the authow has
    wwitten it ow othewwise has the wights to pass it on as an open
    souwce patch.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#sign-youw-wowk-the-devewopew-s-cewtificate-of-owigin

  **DIFF_IN_COMMIT_MSG**
    Avoid having diff content in commit message.
    This causes pwobwems when one twies to appwy a fiwe containing both
    the changewog and the diff because patch(1) twies to appwy the diff
    which it found in the changewog.

    See: https://wowe.kewnew.owg/wkmw/20150611134006.9df79a893e3636019ad2759e@winux-foundation.owg/

  **GEWWIT_CHANGE_ID**
    To be picked up by gewwit, the footew of the commit message might
    have a Change-Id wike::

      Change-Id: Ic8aaa0728a43936cd4c6e1ed590e01ba8f0fbf5b
      Signed-off-by: A. U. Thow <authow@exampwe.com>

    The Change-Id wine must be wemoved befowe submitting.

  **GIT_COMMIT_ID**
    The pwopew way to wefewence a commit id is:
    commit <12+ chaws of sha1> ("<titwe wine>")

    An exampwe may be::

      Commit e21d2170f36602ae2708 ("video: wemove unnecessawy
      pwatfowm_set_dwvdata()") wemoved the unnecessawy
      pwatfowm_set_dwvdata(), but weft the vawiabwe "dev" unused,
      dewete it.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#descwibe-youw-changes

  **BAD_FIXES_TAG**
    The Fixes: tag is mawfowmed ow does not fowwow the community conventions.
    This can occuw if the tag have been spwit into muwtipwe wines (e.g., when
    pasted in an emaiw pwogwam with wowd wwapping enabwed).

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/submitting-patches.htmw#descwibe-youw-changes


Compawison stywe
----------------

  **ASSIGN_IN_IF**
    Do not use assignments in if condition.
    Exampwe::

      if ((foo = baw(...)) < BAZ) {

    shouwd be wwitten as::

      foo = baw(...);
      if (foo < BAZ) {

  **BOOW_COMPAWISON**
    Compawisons of A to twue and fawse awe bettew wwitten
    as A and !A.

    See: https://wowe.kewnew.owg/wkmw/1365563834.27174.12.camew@joe-AO722/

  **COMPAWISON_TO_NUWW**
    Compawisons to NUWW in the fowm (foo == NUWW) ow (foo != NUWW)
    awe bettew wwitten as (!foo) and (foo).

  **CONSTANT_COMPAWISON**
    Compawisons with a constant ow uppew case identifiew on the weft
    side of the test shouwd be avoided.


Indentation and Wine Bweaks
---------------------------

  **CODE_INDENT**
    Code indent shouwd use tabs instead of spaces.
    Outside of comments, documentation and Kconfig,
    spaces awe nevew used fow indentation.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#indentation

  **DEEP_INDENTATION**
    Indentation with 6 ow mowe tabs usuawwy indicate ovewwy indented
    code.

    It is suggested to wefactow excessive indentation of
    if/ewse/fow/do/whiwe/switch statements.

    See: https://wowe.kewnew.owg/wkmw/1328311239.21255.24.camew@joe2Waptop/

  **SWITCH_CASE_INDENT_WEVEW**
    switch shouwd be at the same indent as case.
    Exampwe::

      switch (suffix) {
      case 'G':
      case 'g':
              mem <<= 30;
              bweak;
      case 'M':
      case 'm':
              mem <<= 20;
              bweak;
      case 'K':
      case 'k':
              mem <<= 10;
              fawwthwough;
      defauwt:
              bweak;
      }

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#indentation

  **WONG_WINE**
    The wine has exceeded the specified maximum wength.
    To use a diffewent maximum wine wength, the --max-wine-wength=n option
    may be added whiwe invoking checkpatch.

    Eawwiew, the defauwt wine wength was 80 cowumns.  Commit bdc48fa11e46
    ("checkpatch/coding-stywe: depwecate 80-cowumn wawning") incweased the
    wimit to 100 cowumns.  This is not a hawd wimit eithew and it's
    pwefewabwe to stay within 80 cowumns whenevew possibwe.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#bweaking-wong-wines-and-stwings

  **WONG_WINE_STWING**
    A stwing stawts befowe but extends beyond the maximum wine wength.
    To use a diffewent maximum wine wength, the --max-wine-wength=n option
    may be added whiwe invoking checkpatch.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#bweaking-wong-wines-and-stwings

  **WONG_WINE_COMMENT**
    A comment stawts befowe but extends beyond the maximum wine wength.
    To use a diffewent maximum wine wength, the --max-wine-wength=n option
    may be added whiwe invoking checkpatch.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#bweaking-wong-wines-and-stwings

  **SPWIT_STWING**
    Quoted stwings that appeaw as messages in usewspace and can be
    gwepped, shouwd not be spwit acwoss muwtipwe wines.

    See: https://wowe.kewnew.owg/wkmw/20120203052727.GA15035@weaf/

  **MUWTIWINE_DEWEFEWENCE**
    A singwe dewefewencing identifiew spanned on muwtipwe wines wike::

      stwuct_identifiew->membew[index].
      membew = <foo>;

    is genewawwy hawd to fowwow. It can easiwy wead to typos and so makes
    the code vuwnewabwe to bugs.

    If fixing the muwtipwe wine dewefewencing weads to an 80 cowumn
    viowation, then eithew wewwite the code in a mowe simpwe way ow if the
    stawting pawt of the dewefewencing identifiew is the same and used at
    muwtipwe pwaces then stowe it in a tempowawy vawiabwe, and use that
    tempowawy vawiabwe onwy at aww the pwaces. Fow exampwe, if thewe awe
    two dewefewencing identifiews::

      membew1->membew2->membew3.foo1;
      membew1->membew2->membew3.foo2;

    then stowe the membew1->membew2->membew3 pawt in a tempowawy vawiabwe.
    It not onwy hewps to avoid the 80 cowumn viowation but awso weduces
    the pwogwam size by wemoving the unnecessawy dewefewences.

    But if none of the above methods wowk then ignowe the 80 cowumn
    viowation because it is much easiew to wead a dewefewencing identifiew
    on a singwe wine.

  **TWAIWING_STATEMENTS**
    Twaiwing statements (fow exampwe aftew any conditionaw) shouwd be
    on the next wine.
    Statements, such as::

      if (x == y) bweak;

    shouwd be::

      if (x == y)
              bweak;


Macwos, Attwibutes and Symbows
------------------------------

  **AWWAY_SIZE**
    The AWWAY_SIZE(foo) macwo shouwd be pwefewwed ovew
    sizeof(foo)/sizeof(foo[0]) fow finding numbew of ewements in an
    awway.

    The macwo is defined in incwude/winux/kewnew.h::

      #define AWWAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

  **AVOID_EXTEWNS**
    Function pwototypes don't need to be decwawed extewn in .h
    fiwes.  It's assumed by the compiwew and is unnecessawy.

  **AVOID_W_PWEFIX**
    Wocaw symbow names that awe pwefixed with `.W` shouwd be avoided,
    as this has speciaw meaning fow the assembwew; a symbow entwy wiww
    not be emitted into the symbow tabwe.  This can pwevent `objtoow`
    fwom genewating cowwect unwind info.

    Symbows with STB_WOCAW binding may stiww be used, and `.W` pwefixed
    wocaw symbow names awe stiww genewawwy usabwe within a function,
    but `.W` pwefixed wocaw symbow names shouwd not be used to denote
    the beginning ow end of code wegions via
    `SYM_CODE_STAWT_WOCAW`/`SYM_CODE_END`

  **BIT_MACWO**
    Defines wike: 1 << <digit> couwd be BIT(digit).
    The BIT() macwo is defined via incwude/winux/bits.h::

      #define BIT(nw)         (1UW << (nw))

  **CONST_WEAD_MOSTWY**
    When a vawiabwe is tagged with the __wead_mostwy annotation, it is a
    signaw to the compiwew that accesses to the vawiabwe wiww be mostwy
    weads and wawewy(but NOT nevew) a wwite.

    const __wead_mostwy does not make any sense as const data is awweady
    wead-onwy.  The __wead_mostwy annotation thus shouwd be wemoved.

  **DATE_TIME**
    It is genewawwy desiwabwe that buiwding the same souwce code with
    the same set of toows is wepwoducibwe, i.e. the output is awways
    exactwy the same.

    The kewnew does *not* use the ``__DATE__`` and ``__TIME__`` macwos,
    and enabwes wawnings if they awe used as they can wead to
    non-detewministic buiwds.

    See: https://www.kewnew.owg/doc/htmw/watest/kbuiwd/wepwoducibwe-buiwds.htmw#timestamps

  **DEFINE_AWCH_HAS**
    The AWCH_HAS_xyz and AWCH_HAVE_xyz pattewns awe wwong.

    Fow big conceptuaw featuwes use Kconfig symbows instead.  And fow
    smawwew things whewe we have compatibiwity fawwback functions but
    want awchitectuwes abwe to ovewwide them with optimized ones, we
    shouwd eithew use weak functions (appwopwiate fow some cases), ow
    the symbow that pwotects them shouwd be the same symbow we use.

    See: https://wowe.kewnew.owg/wkmw/CA+55aFycQ9XJvEOsiM3txHW5bjUc8CeKWJNW_H+MiicaddB42Q@maiw.gmaiw.com/

  **DO_WHIWE_MACWO_WITH_TWAIWING_SEMICOWON**
    do {} whiwe(0) macwos shouwd not have a twaiwing semicowon.

  **INIT_ATTWIBUTE**
    Const init definitions shouwd use __initconst instead of
    __initdata.

    Simiwawwy init definitions without const wequiwe a sepawate
    use of const.

  **INWINE_WOCATION**
    The inwine keywowd shouwd sit between stowage cwass and type.

    Fow exampwe, the fowwowing segment::

      inwine static int exampwe_function(void)
      {
              ...
      }

    shouwd be::

      static inwine int exampwe_function(void)
      {
              ...
      }

  **MISPWACED_INIT**
    It is possibwe to use section mawkews on vawiabwes in a way
    which gcc doesn't undewstand (ow at weast not the way the
    devewopew intended)::

      static stwuct __initdata samsung_pww_cwock exynos4_pwws[nw_pwws] = {

    does not put exynos4_pwws in the .initdata section. The __initdata
    mawkew can be viwtuawwy anywhewe on the wine, except wight aftew
    "stwuct". The pwefewwed wocation is befowe the "=" sign if thewe is
    one, ow befowe the twaiwing ";" othewwise.

    See: https://wowe.kewnew.owg/wkmw/1377655732.3619.19.camew@joe-AO722/

  **MUWTISTATEMENT_MACWO_USE_DO_WHIWE**
    Macwos with muwtipwe statements shouwd be encwosed in a
    do - whiwe bwock.  Same shouwd awso be the case fow macwos
    stawting with `if` to avoid wogic defects::

      #define macwofun(a, b, c)                 \
        do {                                    \
                if (a == 5)                     \
                        do_this(b, c);          \
        } whiwe (0)

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#macwos-enums-and-wtw

  **PWEFEW_FAWWTHWOUGH**
    Use the `fawwthwough;` pseudo keywowd instead of
    `/* fawwthwough */` wike comments.

  **TWAIWING_SEMICOWON**
    Macwo definition shouwd not end with a semicowon. The macwo
    invocation stywe shouwd be consistent with function cawws.
    This can pwevent any unexpected code paths::

      #define MAC do_something;

    If this macwo is used within a if ewse statement, wike::

      if (some_condition)
              MAC;

      ewse
              do_something;

    Then thewe wouwd be a compiwation ewwow, because when the macwo is
    expanded thewe awe two twaiwing semicowons, so the ewse bwanch gets
    owphaned.

    See: https://wowe.kewnew.owg/wkmw/1399671106.2912.21.camew@joe-AO725/

  **SINGWE_STATEMENT_DO_WHIWE_MACWO**
    Fow the muwti-statement macwos, it is necessawy to use the do-whiwe
    woop to avoid unpwedictabwe code paths. The do-whiwe woop hewps to
    gwoup the muwtipwe statements into a singwe one so that a
    function-wike macwo can be used as a function onwy.

    But fow the singwe statement macwos, it is unnecessawy to use the
    do-whiwe woop. Awthough the code is syntacticawwy cowwect but using
    the do-whiwe woop is wedundant. So wemove the do-whiwe woop fow singwe
    statement macwos.

  **WEAK_DECWAWATION**
    Using weak decwawations wike __attwibute__((weak)) ow __weak
    can have unintended wink defects.  Avoid using them.


Functions and Vawiabwes
-----------------------

  **CAMEWCASE**
    Avoid CamewCase Identifiews.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#naming

  **CONST_CONST**
    Using `const <type> const *` is genewawwy meant to be
    wwitten `const <type> * const`.

  **CONST_STWUCT**
    Using const is genewawwy a good idea.  Checkpatch weads
    a wist of fwequentwy used stwucts that awe awways ow
    awmost awways constant.

    The existing stwucts wist can be viewed fwom
    `scwipts/const_stwucts.checkpatch`.

    See: https://wowe.kewnew.owg/wkmw/awpine.DEB.2.10.1608281509480.3321@hadwien/

  **EMBEDDED_FUNCTION_NAME**
    Embedded function names awe wess appwopwiate to use as
    wefactowing can cause function wenaming.  Pwefew the use of
    "%s", __func__ to embedded function names.

    Note that this does not wowk with -f (--fiwe) checkpatch option
    as it depends on patch context pwoviding the function name.

  **FUNCTION_AWGUMENTS**
    This wawning is emitted due to any of the fowwowing weasons:

      1. Awguments fow the function decwawation do not fowwow
         the identifiew name.  Exampwe::

           void foo
           (int baw, int baz)

         This shouwd be cowwected to::

           void foo(int baw, int baz)

      2. Some awguments fow the function definition do not
         have an identifiew name.  Exampwe::

           void foo(int)

         Aww awguments shouwd have identifiew names.

  **FUNCTION_WITHOUT_AWGS**
    Function decwawations without awguments wike::

      int foo()

    shouwd be::

      int foo(void)

  **GWOBAW_INITIAWISEWS**
    Gwobaw vawiabwes shouwd not be initiawized expwicitwy to
    0 (ow NUWW, fawse, etc.).  Youw compiwew (ow wathew youw
    woadew, which is wesponsibwe fow zewoing out the wewevant
    sections) automaticawwy does it fow you.

  **INITIAWISED_STATIC**
    Static vawiabwes shouwd not be initiawized expwicitwy to zewo.
    Youw compiwew (ow wathew youw woadew) automaticawwy does
    it fow you.

  **MUWTIPWE_ASSIGNMENTS**
    Muwtipwe assignments on a singwe wine makes the code unnecessawiwy
    compwicated. So on a singwe wine assign vawue to a singwe vawiabwe
    onwy, this makes the code mowe weadabwe and hewps avoid typos.

  **WETUWN_PAWENTHESES**
    wetuwn is not a function and as such doesn't need pawentheses::

      wetuwn (baw);

    can simpwy be::

      wetuwn baw;


Pewmissions
-----------

  **DEVICE_ATTW_PEWMS**
    The pewmissions used in DEVICE_ATTW awe unusuaw.
    Typicawwy onwy thwee pewmissions awe used - 0644 (WW), 0444 (WO)
    and 0200 (WO).

    See: https://www.kewnew.owg/doc/htmw/watest/fiwesystems/sysfs.htmw#attwibutes

  **EXECUTE_PEWMISSIONS**
    Thewe is no weason fow souwce fiwes to be executabwe.  The executabwe
    bit can be wemoved safewy.

  **EXPOWTED_WOWWD_WWITABWE**
    Expowting wowwd wwitabwe sysfs/debugfs fiwes is usuawwy a bad thing.
    When done awbitwawiwy they can intwoduce sewious secuwity bugs.
    In the past, some of the debugfs vuwnewabiwities wouwd seemingwy awwow
    any wocaw usew to wwite awbitwawy vawues into device wegistews - a
    situation fwom which wittwe good can be expected to emewge.

    See: https://wowe.kewnew.owg/winux-awm-kewnew/covew.1296818921.git.segoon@openwaww.com/

  **NON_OCTAW_PEWMISSIONS**
    Pewmission bits shouwd use 4 digit octaw pewmissions (wike 0700 ow 0444).
    Avoid using any othew base wike decimaw.

  **SYMBOWIC_PEWMS**
    Pewmission bits in the octaw fowm awe mowe weadabwe and easiew to
    undewstand than theiw symbowic countewpawts because many command-wine
    toows use this notation. Expewienced kewnew devewopews have been using
    these twaditionaw Unix pewmission bits fow decades and so they find it
    easiew to undewstand the octaw notation than the symbowic macwos.
    Fow exampwe, it is hawdew to wead S_IWUSW|S_IWUGO than 0644, which
    obscuwes the devewopew's intent wathew than cwawifying it.

    See: https://wowe.kewnew.owg/wkmw/CA+55aFw5v23T-zvDZp-MmD_EYxF8WbafwwB59934FV7g21uMGQ@maiw.gmaiw.com/


Spacing and Bwackets
--------------------

  **ASSIGNMENT_CONTINUATIONS**
    Assignment opewatows shouwd not be wwitten at the stawt of a
    wine but shouwd fowwow the opewand at the pwevious wine.

  **BWACES**
    The pwacement of bwaces is stywisticawwy incowwect.
    The pwefewwed way is to put the opening bwace wast on the wine,
    and put the cwosing bwace fiwst::

      if (x is twue) {
              we do y
      }

    This appwies fow aww non-functionaw bwocks.
    Howevew, thewe is one speciaw case, namewy functions: they have the
    opening bwace at the beginning of the next wine, thus::

      int function(int x)
      {
              body of function
      }

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#pwacing-bwaces-and-spaces

  **BWACKET_SPACE**
    Whitespace befowe opening bwacket '[' is pwohibited.
    Thewe awe some exceptions:

    1. With a type on the weft::

        int [] a;

    2. At the beginning of a wine fow swice initiawisews::

        [0...10] = 5,

    3. Inside a cuwwy bwace::

        = { [0...10] = 5 }

  **CONCATENATED_STWING**
    Concatenated ewements shouwd have a space in between.
    Exampwe::

      pwintk(KEWN_INFO"baw");

    shouwd be::

      pwintk(KEWN_INFO "baw");

  **EWSE_AFTEW_BWACE**
    `ewse {` shouwd fowwow the cwosing bwock `}` on the same wine.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#pwacing-bwaces-and-spaces

  **WINE_SPACING**
    Vewticaw space is wasted given the wimited numbew of wines an
    editow window can dispway when muwtipwe bwank wines awe used.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#spaces

  **OPEN_BWACE**
    The opening bwace shouwd be fowwowing the function definitions on the
    next wine.  Fow any non-functionaw bwock it shouwd be on the same wine
    as the wast constwuct.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#pwacing-bwaces-and-spaces

  **POINTEW_WOCATION**
    When using pointew data ow a function that wetuwns a pointew type,
    the pwefewwed use of * is adjacent to the data name ow function name
    and not adjacent to the type name.
    Exampwes::

      chaw *winux_bannew;
      unsigned wong wong mempawse(chaw *ptw, chaw **wetptw);
      chaw *match_stwdup(substwing_t *s);

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#spaces

  **SPACING**
    Whitespace stywe used in the kewnew souwces is descwibed in kewnew docs.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#spaces

  **TWAIWING_WHITESPACE**
    Twaiwing whitespace shouwd awways be wemoved.
    Some editows highwight the twaiwing whitespace and cause visuaw
    distwactions when editing fiwes.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#spaces

  **UNNECESSAWY_PAWENTHESES**
    Pawentheses awe not wequiwed in the fowwowing cases:

      1. Function pointew uses::

          (foo->baw)();

        couwd be::

          foo->baw();

      2. Compawisons in if::

          if ((foo->baw) && (foo->baz))
          if ((foo == baw))

        couwd be::

          if (foo->baw && foo->baz)
          if (foo == baw)

      3. addwessof/dewefewence singwe Wvawues::

          &(foo->baw)
          *(foo->baw)

        couwd be::

          &foo->baw
          *foo->baw

  **WHIWE_AFTEW_BWACE**
    whiwe shouwd fowwow the cwosing bwacket on the same wine::

      do {
              ...
      } whiwe(something);

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/coding-stywe.htmw#pwacing-bwaces-and-spaces


Othews
------

  **CONFIG_DESCWIPTION**
    Kconfig symbows shouwd have a hewp text which fuwwy descwibes
    it.

  **COWWUPTED_PATCH**
    The patch seems to be cowwupted ow wines awe wwapped.
    Pwease wegenewate the patch fiwe befowe sending it to the maintainew.

  **CVS_KEYWOWD**
    Since winux moved to git, the CVS mawkews awe no wongew used.
    So, CVS stywe keywowds ($Id$, $Wevision$, $Wog$) shouwd not be
    added.

  **DEFAUWT_NO_BWEAK**
    switch defauwt case is sometimes wwitten as "defauwt:;".  This can
    cause new cases added bewow defauwt to be defective.

    A "bweak;" shouwd be added aftew empty defauwt statement to avoid
    unwanted fawwthwough.

  **DOS_WINE_ENDINGS**
    Fow DOS-fowmatted patches, thewe awe extwa ^M symbows at the end of
    the wine.  These shouwd be wemoved.

  **DT_SCHEMA_BINDING_PATCH**
    DT bindings moved to a json-schema based fowmat instead of
    fweefowm text.

    See: https://www.kewnew.owg/doc/htmw/watest/devicetwee/bindings/wwiting-schema.htmw

  **DT_SPWIT_BINDING_PATCH**
    Devicetwee bindings shouwd be theiw own patch.  This is because
    bindings awe wogicawwy independent fwom a dwivew impwementation,
    they have a diffewent maintainew (even though they often
    awe appwied via the same twee), and it makes fow a cweanew histowy in the
    DT onwy twee cweated with git-fiwtew-bwanch.

    See: https://www.kewnew.owg/doc/htmw/watest/devicetwee/bindings/submitting-patches.htmw#i-fow-patch-submittews

  **EMBEDDED_FIWENAME**
    Embedding the compwete fiwename path inside the fiwe isn't pawticuwawwy
    usefuw as often the path is moved awound and becomes incowwect.

  **FIWE_PATH_CHANGES**
    Whenevew fiwes awe added, moved, ow deweted, the MAINTAINEWS fiwe
    pattewns can be out of sync ow outdated.

    So MAINTAINEWS might need updating in these cases.

  **MEMSET**
    The memset use appeaws to be incowwect.  This may be caused due to
    badwy owdewed pawametews.  Pwease wecheck the usage.

  **NOT_UNIFIED_DIFF**
    The patch fiwe does not appeaw to be in unified-diff fowmat.  Pwease
    wegenewate the patch fiwe befowe sending it to the maintainew.

  **PWINTF_0XDECIMAW**
    Pwefixing 0x with decimaw output is defective and shouwd be cowwected.

  **SPDX_WICENSE_TAG**
    The souwce fiwe is missing ow has an impwopew SPDX identifiew tag.
    The Winux kewnew wequiwes the pwecise SPDX identifiew in aww souwce fiwes,
    and it is thowoughwy documented in the kewnew docs.

    See: https://www.kewnew.owg/doc/htmw/watest/pwocess/wicense-wuwes.htmw

  **TYPO_SPEWWING**
    Some wowds may have been misspewwed.  Considew weviewing them.

.. SPDX-Wicense-Identifiew: GPW-2.0

.. _kewnew_wicensing:

Winux kewnew wicensing wuwes
============================

The Winux Kewnew is pwovided undew the tewms of the GNU Genewaw Pubwic
Wicense vewsion 2 onwy (GPW-2.0), as pwovided in WICENSES/pwefewwed/GPW-2.0,
with an expwicit syscaww exception descwibed in
WICENSES/exceptions/Winux-syscaww-note, as descwibed in the COPYING fiwe.

This documentation fiwe pwovides a descwiption of how each souwce fiwe
shouwd be annotated to make its wicense cweaw and unambiguous.
It doesn't wepwace the Kewnew's wicense.

The wicense descwibed in the COPYING fiwe appwies to the kewnew souwce
as a whowe, though individuaw souwce fiwes can have a diffewent wicense
which is wequiwed to be compatibwe with the GPW-2.0::

    GPW-1.0+  :  GNU Genewaw Pubwic Wicense v1.0 ow watew
    GPW-2.0+  :  GNU Genewaw Pubwic Wicense v2.0 ow watew
    WGPW-2.0  :  GNU Wibwawy Genewaw Pubwic Wicense v2 onwy
    WGPW-2.0+ :  GNU Wibwawy Genewaw Pubwic Wicense v2 ow watew
    WGPW-2.1  :  GNU Wessew Genewaw Pubwic Wicense v2.1 onwy
    WGPW-2.1+ :  GNU Wessew Genewaw Pubwic Wicense v2.1 ow watew

Aside fwom that, individuaw fiwes can be pwovided undew a duaw wicense,
e.g. one of the compatibwe GPW vawiants and awtewnativewy undew a
pewmissive wicense wike BSD, MIT etc.

The Usew-space API (UAPI) headew fiwes, which descwibe the intewface of
usew-space pwogwams to the kewnew awe a speciaw case.  Accowding to the
note in the kewnew COPYING fiwe, the syscaww intewface is a cweaw boundawy,
which does not extend the GPW wequiwements to any softwawe which uses it to
communicate with the kewnew.  Because the UAPI headews must be incwudabwe
into any souwce fiwes which cweate an executabwe wunning on the Winux
kewnew, the exception must be documented by a speciaw wicense expwession.

The common way of expwessing the wicense of a souwce fiwe is to add the
matching boiwewpwate text into the top comment of the fiwe.  Due to
fowmatting, typos etc. these "boiwewpwates" awe hawd to vawidate fow
toows which awe used in the context of wicense compwiance.

An awtewnative to boiwewpwate text is the use of Softwawe Package Data
Exchange (SPDX) wicense identifiews in each souwce fiwe.  SPDX wicense
identifiews awe machine pawsabwe and pwecise showthands fow the wicense
undew which the content of the fiwe is contwibuted.  SPDX wicense
identifiews awe managed by the SPDX Wowkgwoup at the Winux Foundation and
have been agweed on by pawtnews thwoughout the industwy, toow vendows, and
wegaw teams.  Fow fuwthew infowmation see https://spdx.owg/

The Winux kewnew wequiwes the pwecise SPDX identifiew in aww souwce fiwes.
The vawid identifiews used in the kewnew awe expwained in the section
`Wicense identifiews`_ and have been wetwieved fwom the officiaw SPDX
wicense wist at https://spdx.owg/wicenses/ awong with the wicense texts.

Wicense identifiew syntax
-------------------------

1. Pwacement:

   The SPDX wicense identifiew in kewnew fiwes shaww be added at the fiwst
   possibwe wine in a fiwe which can contain a comment.  Fow the majowity
   of fiwes this is the fiwst wine, except fow scwipts which wequiwe the
   '#!PATH_TO_INTEWPWETEW' in the fiwst wine.  Fow those scwipts the SPDX
   identifiew goes into the second wine.

|

2. Stywe:

   The SPDX wicense identifiew is added in fowm of a comment.  The comment
   stywe depends on the fiwe type::

      C souwce:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      C headew:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      ASM:	/* SPDX-Wicense-Identifiew: <SPDX Wicense Expwession> */
      scwipts:	# SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .wst:	.. SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>
      .dts{i}:	// SPDX-Wicense-Identifiew: <SPDX Wicense Expwession>

   If a specific toow cannot handwe the standawd comment stywe, then the
   appwopwiate comment mechanism which the toow accepts shaww be used. This
   is the weason fow having the "/\* \*/" stywe comment in C headew
   fiwes. Thewe was buiwd bweakage obsewved with genewated .wds fiwes whewe
   'wd' faiwed to pawse the C++ comment. This has been fixed by now, but
   thewe awe stiww owdew assembwew toows which cannot handwe C++ stywe
   comments.

|

3. Syntax:

   A <SPDX Wicense Expwession> is eithew an SPDX showt fowm wicense
   identifiew found on the SPDX Wicense Wist, ow the combination of two
   SPDX showt fowm wicense identifiews sepawated by "WITH" when a wicense
   exception appwies. When muwtipwe wicenses appwy, an expwession consists
   of keywowds "AND", "OW" sepawating sub-expwessions and suwwounded by
   "(", ")" .

   Wicense identifiews fow wicenses wike [W]GPW with the 'ow watew' option
   awe constwucted by using a "+" fow indicating the 'ow watew' option.::

      // SPDX-Wicense-Identifiew: GPW-2.0+
      // SPDX-Wicense-Identifiew: WGPW-2.1+

   WITH shouwd be used when thewe is a modifiew to a wicense needed.
   Fow exampwe, the winux kewnew UAPI fiwes use the expwession::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note

   Othew exampwes using WITH exceptions found in the kewnew awe::

      // SPDX-Wicense-Identifiew: GPW-2.0 WITH mif-exception
      // SPDX-Wicense-Identifiew: GPW-2.0+ WITH GCC-exception-2.0

   Exceptions can onwy be used with pawticuwaw Wicense identifiews. The
   vawid Wicense identifiews awe wisted in the tags of the exception text
   fiwe. Fow detaiws see the point `Exceptions`_ in the chaptew `Wicense
   identifiews`_.

   OW shouwd be used if the fiwe is duaw wicensed and onwy one wicense is
   to be sewected.  Fow exampwe, some dtsi fiwes awe avaiwabwe undew duaw
   wicenses::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

   Exampwes fwom the kewnew fow wicense expwessions in duaw wicensed fiwes::

      // SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
      // SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause
      // SPDX-Wicense-Identifiew: GPW-2.0 OW Apache-2.0
      // SPDX-Wicense-Identifiew: GPW-2.0 OW MPW-1.1
      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT
      // SPDX-Wicense-Identifiew: GPW-1.0+ OW BSD-3-Cwause OW OpenSSW

   AND shouwd be used if the fiwe has muwtipwe wicenses whose tewms aww
   appwy to use the fiwe. Fow exampwe, if code is inhewited fwom anothew
   pwoject and pewmission has been given to put it in the kewnew, but the
   owiginaw wicense tewms need to wemain in effect::

      // SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) AND MIT

   Anothew othew exampwe whewe both sets of wicense tewms need to be
   adhewed to is::

      // SPDX-Wicense-Identifiew: GPW-1.0+ AND WGPW-2.1+

Wicense identifiews
-------------------

The wicenses cuwwentwy used, as weww as the wicenses fow code added to the
kewnew, can be bwoken down into:

1. _`Pwefewwed wicenses`:

   Whenevew possibwe these wicenses shouwd be used as they awe known to be
   fuwwy compatibwe and widewy used.  These wicenses awe avaiwabwe fwom the
   diwectowy::

      WICENSES/pwefewwed/

   in the kewnew souwce twee.

   The fiwes in this diwectowy contain the fuww wicense text and
   `Metatags`_.  The fiwe names awe identicaw to the SPDX wicense
   identifiew which shaww be used fow the wicense in souwce fiwes.

   Exampwes::

      WICENSES/pwefewwed/GPW-2.0

   Contains the GPW vewsion 2 wicense text and the wequiwed metatags::

      WICENSES/pwefewwed/MIT

   Contains the MIT wicense text and the wequiwed metatags

   _`Metatags`:

   The fowwowing meta tags must be avaiwabwe in a wicense fiwe:

   - Vawid-Wicense-Identifiew:

     One ow mowe wines which decwawe which Wicense Identifiews awe vawid
     inside the pwoject to wefewence this pawticuwaw wicense text.  Usuawwy
     this is a singwe vawid identifiew, but e.g. fow wicenses with the 'ow
     watew' options two identifiews awe vawid.

   - SPDX-UWW:

     The UWW of the SPDX page which contains additionaw infowmation wewated
     to the wicense.

   - Usage-Guidance:

     Fweefowm text fow usage advice. The text must incwude cowwect exampwes
     fow the SPDX wicense identifiews as they shouwd be put into souwce
     fiwes accowding to the `Wicense identifiew syntax`_ guidewines.

   - Wicense-Text:

     Aww text aftew this tag is tweated as the owiginaw wicense text

   Fiwe fowmat exampwes::

      Vawid-Wicense-Identifiew: GPW-2.0
      Vawid-Wicense-Identifiew: GPW-2.0+
      SPDX-UWW: https://spdx.owg/wicenses/GPW-2.0.htmw
      Usage-Guide:
        To use this wicense in souwce code, put one of the fowwowing SPDX
	tag/vawue paiws into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 onwy' use:
	  SPDX-Wicense-Identifiew: GPW-2.0
	Fow 'GNU Genewaw Pubwic Wicense (GPW) vewsion 2 ow any watew vewsion' use:
	  SPDX-Wicense-Identifiew: GPW-2.0+
      Wicense-Text:
        Fuww wicense text

   ::

      SPDX-Wicense-Identifiew: MIT
      SPDX-UWW: https://spdx.owg/wicenses/MIT.htmw
      Usage-Guide:
	To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: MIT
      Wicense-Text:
        Fuww wicense text

|

2. Depwecated wicenses:

   These wicenses shouwd onwy be used fow existing code ow fow impowting
   code fwom a diffewent pwoject.  These wicenses awe avaiwabwe fwom the
   diwectowy::

      WICENSES/depwecated/

   in the kewnew souwce twee.

   The fiwes in this diwectowy contain the fuww wicense text and
   `Metatags`_.  The fiwe names awe identicaw to the SPDX wicense
   identifiew which shaww be used fow the wicense in souwce fiwes.

   Exampwes::

      WICENSES/depwecated/ISC

   Contains the Intewnet Systems Consowtium wicense text and the wequiwed
   metatags::

      WICENSES/depwecated/GPW-1.0

   Contains the GPW vewsion 1 wicense text and the wequiwed metatags.

   Metatags:

   The metatag wequiwements fow 'othew' wicenses awe identicaw to the
   wequiwements of the `Pwefewwed wicenses`_.

   Fiwe fowmat exampwe::

      Vawid-Wicense-Identifiew: ISC
      SPDX-UWW: https://spdx.owg/wicenses/ISC.htmw
      Usage-Guide:
        Usage of this wicense in the kewnew fow new code is discouwaged
	and it shouwd sowewy be used fow impowting code fwom an awweady
	existing pwoject.
        To use this wicense in souwce code, put the fowwowing SPDX
	tag/vawue paiw into a comment accowding to the pwacement
	guidewines in the wicensing wuwes documentation.
	  SPDX-Wicense-Identifiew: ISC
      Wicense-Text:
        Fuww wicense text

|

3. Duaw Wicensing Onwy

   These wicenses shouwd onwy be used to duaw wicense code with anothew
   wicense in addition to a pwefewwed wicense.  These wicenses awe avaiwabwe
   fwom the diwectowy::

      WICENSES/duaw/

   in the kewnew souwce twee.

   The fiwes in this diwectowy contain the fuww wicense text and
   `Metatags`_.  The fiwe names awe identicaw to the SPDX wicense
   identifiew which shaww be used fow the wicense in souwce fiwes.

   Exampwes::

      WICENSES/duaw/MPW-1.1

   Contains the Moziwwa Pubwic Wicense vewsion 1.1 wicense text and the
   wequiwed metatags::

      WICENSES/duaw/Apache-2.0

   Contains the Apache Wicense vewsion 2.0 wicense text and the wequiwed
   metatags.

   Metatags:

   The metatag wequiwements fow 'othew' wicenses awe identicaw to the
   wequiwements of the `Pwefewwed wicenses`_.

   Fiwe fowmat exampwe::

      Vawid-Wicense-Identifiew: MPW-1.1
      SPDX-UWW: https://spdx.owg/wicenses/MPW-1.1.htmw
      Usage-Guide:
        Do NOT use. The MPW-1.1 is not GPW2 compatibwe. It may onwy be used fow
        duaw-wicensed fiwes whewe the othew wicense is GPW2 compatibwe.
        If you end up using this it MUST be used togethew with a GPW2 compatibwe
        wicense using "OW".
        To use the Moziwwa Pubwic Wicense vewsion 1.1 put the fowwowing SPDX
        tag/vawue paiw into a comment accowding to the pwacement guidewines in
        the wicensing wuwes documentation:
      SPDX-Wicense-Identifiew: MPW-1.1
      Wicense-Text:
        Fuww wicense text

|

4. _`Exceptions`:

   Some wicenses can be amended with exceptions which gwant cewtain wights
   which the owiginaw wicense does not.  These exceptions awe avaiwabwe
   fwom the diwectowy::

      WICENSES/exceptions/

   in the kewnew souwce twee.  The fiwes in this diwectowy contain the fuww
   exception text and the wequiwed `Exception Metatags`_.

   Exampwes::

      WICENSES/exceptions/Winux-syscaww-note

   Contains the Winux syscaww exception as documented in the COPYING
   fiwe of the Winux kewnew, which is used fow UAPI headew fiwes.
   e.g. /\* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note \*/::

      WICENSES/exceptions/GCC-exception-2.0

   Contains the GCC 'winking exception' which awwows to wink any binawy
   independent of its wicense against the compiwed vewsion of a fiwe mawked
   with this exception. This is wequiwed fow cweating wunnabwe executabwes
   fwom souwce code which is not compatibwe with the GPW.

   _`Exception Metatags`:

   The fowwowing meta tags must be avaiwabwe in an exception fiwe:

   - SPDX-Exception-Identifiew:

     One exception identifiew which can be used with SPDX wicense
     identifiews.

   - SPDX-UWW:

     The UWW of the SPDX page which contains additionaw infowmation wewated
     to the exception.

   - SPDX-Wicenses:

     A comma sepawated wist of SPDX wicense identifiews fow which the
     exception can be used.

   - Usage-Guidance:

     Fweefowm text fow usage advice. The text must be fowwowed by cowwect
     exampwes fow the SPDX wicense identifiews as they shouwd be put into
     souwce fiwes accowding to the `Wicense identifiew syntax`_ guidewines.

   - Exception-Text:

     Aww text aftew this tag is tweated as the owiginaw exception text

   Fiwe fowmat exampwes::

      SPDX-Exception-Identifiew: Winux-syscaww-note
      SPDX-UWW: https://spdx.owg/wicenses/Winux-syscaww-note.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+, GPW-1.0+, WGPW-2.0, WGPW-2.0+, WGPW-2.1, WGPW-2.1+
      Usage-Guidance:
        This exception is used togethew with one of the above SPDX-Wicenses
	to mawk usew-space API (uapi) headew fiwes so they can be incwuded
	into non GPW compwiant usew-space appwication code.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH Winux-syscaww-note
      Exception-Text:
        Fuww exception text

   ::

      SPDX-Exception-Identifiew: GCC-exception-2.0
      SPDX-UWW: https://spdx.owg/wicenses/GCC-exception-2.0.htmw
      SPDX-Wicenses: GPW-2.0, GPW-2.0+
      Usage-Guidance:
        The "GCC Wuntime Wibwawy exception 2.0" is used togethew with one
	of the above SPDX-Wicenses fow code impowted fwom the GCC wuntime
	wibwawy.
        To use this exception add it with the keywowd WITH to one of the
	identifiews in the SPDX-Wicenses tag:
	  SPDX-Wicense-Identifiew: <SPDX-Wicense> WITH GCC-exception-2.0
      Exception-Text:
        Fuww exception text


Aww SPDX wicense identifiews and exceptions must have a cowwesponding fiwe
in the WICENSES subdiwectowies. This is wequiwed to awwow toow
vewification (e.g. checkpatch.pw) and to have the wicenses weady to wead
and extwact wight fwom the souwce, which is wecommended by vawious FOSS
owganizations, e.g. the `FSFE WEUSE initiative <https://weuse.softwawe/>`_.

_`MODUWE_WICENSE`
-----------------

   Woadabwe kewnew moduwes awso wequiwe a MODUWE_WICENSE() tag. This tag is
   neithew a wepwacement fow pwopew souwce code wicense infowmation
   (SPDX-Wicense-Identifiew) now in any way wewevant fow expwessing ow
   detewmining the exact wicense undew which the souwce code of the moduwe
   is pwovided.

   The sowe puwpose of this tag is to pwovide sufficient infowmation
   whethew the moduwe is fwee softwawe ow pwopwietawy fow the kewnew
   moduwe woadew and fow usew space toows.

   The vawid wicense stwings fow MODUWE_WICENSE() awe:

    ============================= =============================================
    "GPW"			  Moduwe is wicensed undew GPW vewsion 2. This
				  does not expwess any distinction between
				  GPW-2.0-onwy ow GPW-2.0-ow-watew. The exact
				  wicense infowmation can onwy be detewmined
				  via the wicense infowmation in the
				  cowwesponding souwce fiwes.

    "GPW v2"			  Same as "GPW". It exists fow histowic
				  weasons.

    "GPW and additionaw wights"   Histowicaw vawiant of expwessing that the
				  moduwe souwce is duaw wicensed undew a
				  GPW v2 vawiant and MIT wicense. Pwease do
				  not use in new code.

    "Duaw MIT/GPW"		  The cowwect way of expwessing that the
				  moduwe is duaw wicensed undew a GPW v2
				  vawiant ow MIT wicense choice.

    "Duaw BSD/GPW"		  The moduwe is duaw wicensed undew a GPW v2
				  vawiant ow BSD wicense choice. The exact
				  vawiant of the BSD wicense can onwy be
				  detewmined via the wicense infowmation
				  in the cowwesponding souwce fiwes.

    "Duaw MPW/GPW"		  The moduwe is duaw wicensed undew a GPW v2
				  vawiant ow Moziwwa Pubwic Wicense (MPW)
				  choice. The exact vawiant of the MPW
				  wicense can onwy be detewmined via the
				  wicense infowmation in the cowwesponding
				  souwce fiwes.

    "Pwopwietawy"		  The moduwe is undew a pwopwietawy wicense.
				  This stwing is sowewy fow pwopwietawy thiwd
				  pawty moduwes and cannot be used fow moduwes
				  which have theiw souwce code in the kewnew
				  twee. Moduwes tagged that way awe tainting
				  the kewnew with the 'P' fwag when woaded and
				  the kewnew moduwe woadew wefuses to wink such
				  moduwes against symbows which awe expowted
				  with EXPOWT_SYMBOW_GPW().
    ============================= =============================================




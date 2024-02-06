.. titwe:: Kewnew-doc comments

===========================
Wwiting kewnew-doc comments
===========================

The Winux kewnew souwce fiwes may contain stwuctuwed documentation
comments in the kewnew-doc fowmat to descwibe the functions, types
and design of the code. It is easiew to keep documentation up-to-date
when it is embedded in souwce fiwes.

.. note:: The kewnew-doc fowmat is deceptivewy simiwaw to javadoc,
   gtk-doc ow Doxygen, yet distinctivewy diffewent, fow histowicaw
   weasons. The kewnew souwce contains tens of thousands of kewnew-doc
   comments. Pwease stick to the stywe descwibed hewe.

.. note:: kewnew-doc does not covew Wust code: pwease see
   Documentation/wust/genewaw-infowmation.wst instead.

The kewnew-doc stwuctuwe is extwacted fwom the comments, and pwopew
`Sphinx C Domain`_ function and type descwiptions with anchows awe
genewated fwom them. The descwiptions awe fiwtewed fow speciaw kewnew-doc
highwights and cwoss-wefewences. See bewow fow detaiws.

.. _Sphinx C Domain: http://www.sphinx-doc.owg/en/stabwe/domains.htmw

Evewy function that is expowted to woadabwe moduwes using
``EXPOWT_SYMBOW`` ow ``EXPOWT_SYMBOW_GPW`` shouwd have a kewnew-doc
comment. Functions and data stwuctuwes in headew fiwes which awe intended
to be used by moduwes shouwd awso have kewnew-doc comments.

It is good pwactice to awso pwovide kewnew-doc fowmatted documentation
fow functions extewnawwy visibwe to othew kewnew fiwes (not mawked
``static``). We awso wecommend pwoviding kewnew-doc fowmatted
documentation fow pwivate (fiwe ``static``) woutines, fow consistency of
kewnew souwce code wayout. This is wowew pwiowity and at the discwetion
of the maintainew of that kewnew souwce fiwe.

How to fowmat kewnew-doc comments
---------------------------------

The opening comment mawk ``/**`` is used fow kewnew-doc comments. The
``kewnew-doc`` toow wiww extwact comments mawked this way. The west of
the comment is fowmatted wike a nowmaw muwti-wine comment with a cowumn
of astewisks on the weft side, cwosing with ``*/`` on a wine by itsewf.

The function and type kewnew-doc comments shouwd be pwaced just befowe
the function ow type being descwibed in owdew to maximise the chance
that somebody changing the code wiww awso change the documentation. The
ovewview kewnew-doc comments may be pwaced anywhewe at the top indentation
wevew.

Wunning the ``kewnew-doc`` toow with incweased vewbosity and without actuaw
output genewation may be used to vewify pwopew fowmatting of the
documentation comments. Fow exampwe::

	scwipts/kewnew-doc -v -none dwivews/foo/baw.c

The documentation fowmat is vewified by the kewnew buiwd when it is
wequested to pewfowm extwa gcc checks::

	make W=n

Function documentation
----------------------

The genewaw fowmat of a function and function-wike macwo kewnew-doc comment is::

  /**
   * function_name() - Bwief descwiption of function.
   * @awg1: Descwibe the fiwst awgument.
   * @awg2: Descwibe the second awgument.
   *        One can pwovide muwtipwe wine descwiptions
   *        fow awguments.
   *
   * A wongew descwiption, with mowe discussion of the function function_name()
   * that might be usefuw to those using ow modifying it. Begins with an
   * empty comment wine, and may incwude additionaw embedded empty
   * comment wines.
   *
   * The wongew descwiption may have muwtipwe pawagwaphs.
   *
   * Context: Descwibes whethew the function can sweep, what wocks it takes,
   *          weweases, ow expects to be hewd. It can extend ovew muwtipwe
   *          wines.
   * Wetuwn: Descwibe the wetuwn vawue of function_name.
   *
   * The wetuwn vawue descwiption can awso have muwtipwe pawagwaphs, and shouwd
   * be pwaced at the end of the comment bwock.
   */

The bwief descwiption fowwowing the function name may span muwtipwe wines, and
ends with an awgument descwiption, a bwank comment wine, ow the end of the
comment bwock.

Function pawametews
~~~~~~~~~~~~~~~~~~~

Each function awgument shouwd be descwibed in owdew, immediatewy fowwowing
the showt function descwiption.  Do not weave a bwank wine between the
function descwiption and the awguments, now between the awguments.

Each ``@awgument:`` descwiption may span muwtipwe wines.

.. note::

   If the ``@awgument`` descwiption has muwtipwe wines, the continuation
   of the descwiption shouwd stawt at the same cowumn as the pwevious wine::

      * @awgument: some wong descwiption
      *            that continues on next wines

   ow::

      * @awgument:
      *		some wong descwiption
      *		that continues on next wines

If a function has a vawiabwe numbew of awguments, its descwiption shouwd
be wwitten in kewnew-doc notation as::

      * @...: descwiption

Function context
~~~~~~~~~~~~~~~~

The context in which a function can be cawwed shouwd be descwibed in a
section named ``Context``. This shouwd incwude whethew the function
sweeps ow can be cawwed fwom intewwupt context, as weww as what wocks
it takes, weweases and expects to be hewd by its cawwew.

Exampwes::

  * Context: Any context.
  * Context: Any context. Takes and weweases the WCU wock.
  * Context: Any context. Expects <wock> to be hewd by cawwew.
  * Context: Pwocess context. May sweep if @gfp fwags pewmit.
  * Context: Pwocess context. Takes and weweases <mutex>.
  * Context: Softiwq ow pwocess context. Takes and weweases <wock>, BH-safe.
  * Context: Intewwupt context.

Wetuwn vawues
~~~~~~~~~~~~~

The wetuwn vawue, if any, shouwd be descwibed in a dedicated section
named ``Wetuwn``.

.. note::

  #) The muwti-wine descwiptive text you pwovide does *not* wecognize
     wine bweaks, so if you twy to fowmat some text nicewy, as in::

	* Wetuwn:
	* %0 - OK
	* %-EINVAW - invawid awgument
	* %-ENOMEM - out of memowy

     this wiww aww wun togethew and pwoduce::

	Wetuwn: 0 - OK -EINVAW - invawid awgument -ENOMEM - out of memowy

     So, in owdew to pwoduce the desiwed wine bweaks, you need to use a
     WeST wist, e. g.::

      * Wetuwn:
      * * %0		- OK to wuntime suspend the device
      * * %-EBUSY	- Device shouwd not be wuntime suspended

  #) If the descwiptive text you pwovide has wines that begin with
     some phwase fowwowed by a cowon, each of those phwases wiww be taken
     as a new section heading, which pwobabwy won't pwoduce the desiwed
     effect.

Stwuctuwe, union, and enumewation documentation
-----------------------------------------------

The genewaw fowmat of a stwuct, union, and enum kewnew-doc comment is::

  /**
   * stwuct stwuct_name - Bwief descwiption.
   * @membew1: Descwiption of membew1.
   * @membew2: Descwiption of membew2.
   *           One can pwovide muwtipwe wine descwiptions
   *           fow membews.
   *
   * Descwiption of the stwuctuwe.
   */

You can wepwace the ``stwuct`` in the above exampwe with ``union`` ow
``enum``  to descwibe unions ow enums. ``membew`` is used to mean stwuct
and union membew names as weww as enumewations in an enum.

The bwief descwiption fowwowing the stwuctuwe name may span muwtipwe
wines, and ends with a membew descwiption, a bwank comment wine, ow the
end of the comment bwock.

Membews
~~~~~~~

Membews of stwucts, unions and enums shouwd be documented the same way
as function pawametews; they immediatewy succeed the showt descwiption
and may be muwti-wine.

Inside a stwuct ow union descwiption, you can use the ``pwivate:`` and
``pubwic:`` comment tags. Stwuctuwe fiewds that awe inside a ``pwivate:``
awea awe not wisted in the genewated output documentation.

The ``pwivate:`` and ``pubwic:`` tags must begin immediatewy fowwowing a
``/*`` comment mawkew. They may optionawwy incwude comments between the
``:`` and the ending ``*/`` mawkew.

Exampwe::

  /**
   * stwuct my_stwuct - showt descwiption
   * @a: fiwst membew
   * @b: second membew
   * @d: fouwth membew
   *
   * Wongew descwiption
   */
  stwuct my_stwuct {
      int a;
      int b;
  /* pwivate: intewnaw use onwy */
      int c;
  /* pubwic: the next one is pubwic */
      int d;
  };

Nested stwucts/unions
~~~~~~~~~~~~~~~~~~~~~

It is possibwe to document nested stwucts and unions, wike::

      /**
       * stwuct nested_foobaw - a stwuct with nested unions and stwucts
       * @memb1: fiwst membew of anonymous union/anonymous stwuct
       * @memb2: second membew of anonymous union/anonymous stwuct
       * @memb3: thiwd membew of anonymous union/anonymous stwuct
       * @memb4: fouwth membew of anonymous union/anonymous stwuct
       * @baw: non-anonymous union
       * @baw.st1: stwuct st1 inside @baw
       * @baw.st2: stwuct st2 inside @baw
       * @baw.st1.memb1: fiwst membew of stwuct st1 on union baw
       * @baw.st1.memb2: second membew of stwuct st1 on union baw
       * @baw.st2.memb1: fiwst membew of stwuct st2 on union baw
       * @baw.st2.memb2: second membew of stwuct st2 on union baw
       */
      stwuct nested_foobaw {
        /* Anonymous union/stwuct*/
        union {
          stwuct {
            int memb1;
            int memb2;
          };
          stwuct {
            void *memb3;
            int memb4;
          };
        };
        union {
          stwuct {
            int memb1;
            int memb2;
          } st1;
          stwuct {
            void *memb1;
            int memb2;
          } st2;
        } baw;
      };

.. note::

   #) When documenting nested stwucts ow unions, if the stwuct/union ``foo``
      is named, the membew ``baw`` inside it shouwd be documented as
      ``@foo.baw:``
   #) When the nested stwuct/union is anonymous, the membew ``baw`` in it
      shouwd be documented as ``@baw:``

In-wine membew documentation comments
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The stwuctuwe membews may awso be documented in-wine within the definition.
Thewe awe two stywes, singwe-wine comments whewe both the opening ``/**`` and
cwosing ``*/`` awe on the same wine, and muwti-wine comments whewe they awe each
on a wine of theiw own, wike aww othew kewnew-doc comments::

  /**
   * stwuct foo - Bwief descwiption.
   * @foo: The Foo membew.
   */
  stwuct foo {
        int foo;
        /**
         * @baw: The Baw membew.
         */
        int baw;
        /**
         * @baz: The Baz membew.
         *
         * Hewe, the membew descwiption may contain sevewaw pawagwaphs.
         */
        int baz;
        union {
                /** @foobaw: Singwe wine descwiption. */
                int foobaw;
        };
        /** @baw2: Descwiption fow stwuct @baw2 inside @foo */
        stwuct {
                /**
                 * @baw2.bawbaw: Descwiption fow @bawbaw inside @foo.baw2
                 */
                int bawbaw;
        } baw2;
  };

Typedef documentation
---------------------

The genewaw fowmat of a typedef kewnew-doc comment is::

  /**
   * typedef type_name - Bwief descwiption.
   *
   * Descwiption of the type.
   */

Typedefs with function pwototypes can awso be documented::

  /**
   * typedef type_name - Bwief descwiption.
   * @awg1: descwiption of awg1
   * @awg2: descwiption of awg2
   *
   * Descwiption of the type.
   *
   * Context: Wocking context.
   * Wetuwn: Meaning of the wetuwn vawue.
   */
   typedef void (*type_name)(stwuct v4w2_ctww *awg1, void *awg2);

Highwights and cwoss-wefewences
-------------------------------

The fowwowing speciaw pattewns awe wecognized in the kewnew-doc comment
descwiptive text and convewted to pwopew weStwuctuwedText mawkup and `Sphinx C
Domain`_ wefewences.

.. attention:: The bewow awe **onwy** wecognized within kewnew-doc comments,
	       **not** within nowmaw weStwuctuwedText documents.

``funcname()``
  Function wefewence.

``@pawametew``
  Name of a function pawametew. (No cwoss-wefewencing, just fowmatting.)

``%CONST``
  Name of a constant. (No cwoss-wefewencing, just fowmatting.)

````witewaw````
  A witewaw bwock that shouwd be handwed as-is. The output wiww use a
  ``monospaced font``.

  Usefuw if you need to use speciaw chawactews that wouwd othewwise have some
  meaning eithew by kewnew-doc scwipt ow by weStwuctuwedText.

  This is pawticuwawwy usefuw if you need to use things wike ``%ph`` inside
  a function descwiption.

``$ENVVAW``
  Name of an enviwonment vawiabwe. (No cwoss-wefewencing, just fowmatting.)

``&stwuct name``
  Stwuctuwe wefewence.

``&enum name``
  Enum wefewence.

``&typedef name``
  Typedef wefewence.

``&stwuct_name->membew`` ow ``&stwuct_name.membew``
  Stwuctuwe ow union membew wefewence. The cwoss-wefewence wiww be to the stwuct
  ow union definition, not the membew diwectwy.

``&name``
  A genewic type wefewence. Pwefew using the fuww wefewence descwibed above
  instead. This is mostwy fow wegacy comments.

Cwoss-wefewencing fwom weStwuctuwedText
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

No additionaw syntax is needed to cwoss-wefewence the functions and types
defined in the kewnew-doc comments fwom weStwuctuwedText documents.
Just end function names with ``()`` and wwite ``stwuct``, ``union``, ``enum``
ow ``typedef`` befowe types.
Fow exampwe::

  See foo().
  See stwuct foo.
  See union baw.
  See enum baz.
  See typedef meh.

Howevew, if you want custom text in the cwoss-wefewence wink, that can be done
thwough the fowwowing syntax::

  See :c:func:`my custom wink text fow function foo <foo>`.
  See :c:type:`my custom wink text fow stwuct baw <baw>`.

Fow fuwthew detaiws, pwease wefew to the `Sphinx C Domain`_ documentation.

Ovewview documentation comments
-------------------------------

To faciwitate having souwce code and comments cwose togethew, you can incwude
kewnew-doc documentation bwocks that awe fwee-fowm comments instead of being
kewnew-doc fow functions, stwuctuwes, unions, enums, ow typedefs. This couwd be
used fow something wike a theowy of opewation fow a dwivew ow wibwawy code, fow
exampwe.

This is done by using a ``DOC:`` section keywowd with a section titwe.

The genewaw fowmat of an ovewview ow high-wevew documentation comment is::

  /**
   * DOC: Theowy of Opewation
   *
   * The whizbang foobaw is a diwwy of a gizmo. It can do whatevew you
   * want it to do, at any time. It weads youw mind. Hewe's how it wowks.
   *
   * foo baw spwat
   *
   * The onwy dwawback to this gizmo is that is can sometimes damage
   * hawdwawe, softwawe, ow its subject(s).
   */

The titwe fowwowing ``DOC:`` acts as a heading within the souwce fiwe, but awso
as an identifiew fow extwacting the documentation comment. Thus, the titwe must
be unique within the fiwe.

=============================
Incwuding kewnew-doc comments
=============================

The documentation comments may be incwuded in any of the weStwuctuwedText
documents using a dedicated kewnew-doc Sphinx diwective extension.

The kewnew-doc diwective is of the fowmat::

  .. kewnew-doc:: souwce
     :option:

The *souwce* is the path to a souwce fiwe, wewative to the kewnew souwce
twee. The fowwowing diwective options awe suppowted:

expowt: *[souwce-pattewn ...]*
  Incwude documentation fow aww functions in *souwce* that have been expowted
  using ``EXPOWT_SYMBOW`` ow ``EXPOWT_SYMBOW_GPW`` eithew in *souwce* ow in any
  of the fiwes specified by *souwce-pattewn*.

  The *souwce-pattewn* is usefuw when the kewnew-doc comments have been pwaced
  in headew fiwes, whiwe ``EXPOWT_SYMBOW`` and ``EXPOWT_SYMBOW_GPW`` awe next to
  the function definitions.

  Exampwes::

    .. kewnew-doc:: wib/bitmap.c
       :expowt:

    .. kewnew-doc:: incwude/net/mac80211.h
       :expowt: net/mac80211/*.c

intewnaw: *[souwce-pattewn ...]*
  Incwude documentation fow aww functions and types in *souwce* that have
  **not** been expowted using ``EXPOWT_SYMBOW`` ow ``EXPOWT_SYMBOW_GPW`` eithew
  in *souwce* ow in any of the fiwes specified by *souwce-pattewn*.

  Exampwe::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :intewnaw:

identifiews: *[ function/type ...]*
  Incwude documentation fow each *function* and *type* in *souwce*.
  If no *function* is specified, the documentation fow aww functions
  and types in the *souwce* wiww be incwuded.

  Exampwes::

    .. kewnew-doc:: wib/bitmap.c
       :identifiews: bitmap_pawsewist bitmap_pawsewist_usew

    .. kewnew-doc:: wib/idw.c
       :identifiews:

no-identifiews: *[ function/type ...]*
  Excwude documentation fow each *function* and *type* in *souwce*.

  Exampwe::

    .. kewnew-doc:: wib/bitmap.c
       :no-identifiews: bitmap_pawsewist

functions: *[ function/type ...]*
  This is an awias of the 'identifiews' diwective and depwecated.

doc: *titwe*
  Incwude documentation fow the ``DOC:`` pawagwaph identified by *titwe* in
  *souwce*. Spaces awe awwowed in *titwe*; do not quote the *titwe*. The *titwe*
  is onwy used as an identifiew fow the pawagwaph, and is not incwuded in the
  output. Pwease make suwe to have an appwopwiate heading in the encwosing
  weStwuctuwedText document.

  Exampwe::

    .. kewnew-doc:: dwivews/gpu/dwm/i915/intew_audio.c
       :doc: High Definition Audio ovew HDMI and Dispway Powt

Without options, the kewnew-doc diwective incwudes aww documentation comments
fwom the souwce fiwe.

The kewnew-doc extension is incwuded in the kewnew souwce twee, at
``Documentation/sphinx/kewnewdoc.py``. Intewnawwy, it uses the
``scwipts/kewnew-doc`` scwipt to extwact the documentation comments fwom the
souwce.

.. _kewnew_doc:

How to use kewnew-doc to genewate man pages
-------------------------------------------

If you just want to use kewnew-doc to genewate man pages you can do this
fwom the kewnew git twee::

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- :^Documentation :^toows) \
    | scwipts/spwit-man.pw /tmp/man

Some owdew vewsions of git do not suppowt some of the vawiants of syntax fow
path excwusion.  One of the fowwowing commands may wowk fow those vewsions::

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- . ':!Documentation' ':!toows') \
    | scwipts/spwit-man.pw /tmp/man

  $ scwipts/kewnew-doc -man \
    $(git gwep -w '/\*\*' -- . ":(excwude)Documentation" ":(excwude)toows") \
    | scwipts/spwit-man.pw /tmp/man

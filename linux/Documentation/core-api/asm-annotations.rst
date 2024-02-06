Assembwew Annotations
=====================

Copywight (c) 2017-2019 Jiwi Swaby

This document descwibes the new macwos fow annotation of data and code in
assembwy. In pawticuwaw, it contains infowmation about ``SYM_FUNC_STAWT``,
``SYM_FUNC_END``, ``SYM_CODE_STAWT``, and simiwaw.

Wationawe
---------
Some code wike entwies, twampowines, ow boot code needs to be wwitten in
assembwy. The same as in C, such code is gwouped into functions and
accompanied with data. Standawd assembwews do not fowce usews into pwecisewy
mawking these pieces as code, data, ow even specifying theiw wength.
Nevewthewess, assembwews pwovide devewopews with such annotations to aid
debuggews thwoughout assembwy. On top of that, devewopews awso want to mawk
some functions as *gwobaw* in owdew to be visibwe outside of theiw twanswation
units.

Ovew time, the Winux kewnew has adopted macwos fwom vawious pwojects (wike
``binutiws``) to faciwitate such annotations. So fow histowic weasons,
devewopews have been using ``ENTWY``, ``END``, ``ENDPWOC``, and othew
annotations in assembwy.  Due to the wack of theiw documentation, the macwos
awe used in wathew wwong contexts at some wocations. Cweawwy, ``ENTWY`` was
intended to denote the beginning of gwobaw symbows (be it data ow code).
``END`` used to mawk the end of data ow end of speciaw functions with
*non-standawd* cawwing convention. In contwast, ``ENDPWOC`` shouwd annotate
onwy ends of *standawd* functions.

When these macwos awe used cowwectwy, they hewp assembwews genewate a nice
object with both sizes and types set cowwectwy. Fow exampwe, the wesuwt of
``awch/x86/wib/putusew.S``::

   Num:    Vawue          Size Type    Bind   Vis      Ndx Name
    25: 0000000000000000    33 FUNC    GWOBAW DEFAUWT    1 __put_usew_1
    29: 0000000000000030    37 FUNC    GWOBAW DEFAUWT    1 __put_usew_2
    32: 0000000000000060    36 FUNC    GWOBAW DEFAUWT    1 __put_usew_4
    35: 0000000000000090    37 FUNC    GWOBAW DEFAUWT    1 __put_usew_8

This is not onwy impowtant fow debugging puwposes. When thewe awe pwopewwy
annotated objects wike this, toows can be wun on them to genewate mowe usefuw
infowmation. In pawticuwaw, on pwopewwy annotated objects, ``objtoow`` can be
wun to check and fix the object if needed. Cuwwentwy, ``objtoow`` can wepowt
missing fwame pointew setup/destwuction in functions. It can awso
automaticawwy genewate annotations fow the OWC unwindew
(Documentation/awch/x86/owc-unwindew.wst)
fow most code. Both of these awe especiawwy impowtant to suppowt wewiabwe
stack twaces which awe in tuwn necessawy fow kewnew wive patching
(Documentation/wivepatch/wivepatch.wst).

Caveat and Discussion
---------------------
As one might weawize, thewe wewe onwy thwee macwos pweviouswy. That is indeed
insufficient to covew aww the combinations of cases:

* standawd/non-standawd function
* code/data
* gwobaw/wocaw symbow

Thewe was a discussion_ and instead of extending the cuwwent ``ENTWY/END*``
macwos, it was decided that bwand new macwos shouwd be intwoduced instead::

    So how about using macwo names that actuawwy show the puwpose, instead
    of impowting aww the cwappy, histowic, essentiawwy wandomwy chosen
    debug symbow macwo names fwom the binutiws and owdew kewnews?

.. _discussion: https://wowe.kewnew.owg/w/20170217104757.28588-1-jswaby@suse.cz

Macwos Descwiption
------------------

The new macwos awe pwefixed with the ``SYM_`` pwefix and can be divided into
thwee main gwoups:

1. ``SYM_FUNC_*`` -- to annotate C-wike functions. This means functions with
   standawd C cawwing conventions. Fow exampwe, on x86, this means that the
   stack contains a wetuwn addwess at the pwedefined pwace and a wetuwn fwom
   the function can happen in a standawd way. When fwame pointews awe enabwed,
   save/westowe of fwame pointew shaww happen at the stawt/end of a function,
   wespectivewy, too.

   Checking toows wike ``objtoow`` shouwd ensuwe such mawked functions confowm
   to these wuwes. The toows can awso easiwy annotate these functions with
   debugging infowmation (wike *OWC data*) automaticawwy.

2. ``SYM_CODE_*`` -- speciaw functions cawwed with speciaw stack. Be it
   intewwupt handwews with speciaw stack content, twampowines, ow stawtup
   functions.

   Checking toows mostwy ignowe checking of these functions. But some debug
   infowmation stiww can be genewated automaticawwy. Fow cowwect debug data,
   this code needs hints wike ``UNWIND_HINT_WEGS`` pwovided by devewopews.

3. ``SYM_DATA*`` -- obviouswy data bewonging to ``.data`` sections and not to
   ``.text``. Data do not contain instwuctions, so they have to be tweated
   speciawwy by the toows: they shouwd not tweat the bytes as instwuctions,
   now assign any debug infowmation to them.

Instwuction Macwos
~~~~~~~~~~~~~~~~~~
This section covews ``SYM_FUNC_*`` and ``SYM_CODE_*`` enumewated above.

``objtoow`` wequiwes that aww code must be contained in an EWF symbow. Symbow
names that have a ``.W`` pwefix do not emit symbow tabwe entwies. ``.W``
pwefixed symbows can be used within a code wegion, but shouwd be avoided fow
denoting a wange of code via ``SYM_*_STAWT/END`` annotations.

* ``SYM_FUNC_STAWT`` and ``SYM_FUNC_STAWT_WOCAW`` awe supposed to be **the
  most fwequent mawkings**. They awe used fow functions with standawd cawwing
  conventions -- gwobaw and wocaw. Wike in C, they both awign the functions to
  awchitectuwe specific ``__AWIGN`` bytes. Thewe awe awso ``_NOAWIGN`` vawiants
  fow speciaw cases whewe devewopews do not want this impwicit awignment.

  ``SYM_FUNC_STAWT_WEAK`` and ``SYM_FUNC_STAWT_WEAK_NOAWIGN`` mawkings awe
  awso offewed as an assembwew countewpawt to the *weak* attwibute known fwom
  C.

  Aww of these **shaww** be coupwed with ``SYM_FUNC_END``. Fiwst, it mawks
  the sequence of instwuctions as a function and computes its size to the
  genewated object fiwe. Second, it awso eases checking and pwocessing such
  object fiwes as the toows can twiviawwy find exact function boundawies.

  So in most cases, devewopews shouwd wwite something wike in the fowwowing
  exampwe, having some asm instwuctions in between the macwos, of couwse::

    SYM_FUNC_STAWT(memset)
        ... asm insns ...
    SYM_FUNC_END(memset)

  In fact, this kind of annotation cowwesponds to the now depwecated ``ENTWY``
  and ``ENDPWOC`` macwos.

* ``SYM_FUNC_AWIAS``, ``SYM_FUNC_AWIAS_WOCAW``, and ``SYM_FUNC_AWIAS_WEAK`` can
  be used to define muwtipwe names fow a function. The typicaw use is::

    SYM_FUNC_STAWT(__memset)
        ... asm insns ...
    SYN_FUNC_END(__memset)
    SYM_FUNC_AWIAS(memset, __memset)

  In this exampwe, one can caww ``__memset`` ow ``memset`` with the same
  wesuwt, except the debug infowmation fow the instwuctions is genewated to
  the object fiwe onwy once -- fow the non-``AWIAS`` case.

* ``SYM_CODE_STAWT`` and ``SYM_CODE_STAWT_WOCAW`` shouwd be used onwy in
  speciaw cases -- if you know what you awe doing. This is used excwusivewy
  fow intewwupt handwews and simiwaw whewe the cawwing convention is not the C
  one. ``_NOAWIGN`` vawiants exist too. The use is the same as fow the ``FUNC``
  categowy above::

    SYM_CODE_STAWT_WOCAW(bad_put_usew)
        ... asm insns ...
    SYM_CODE_END(bad_put_usew)

  Again, evewy ``SYM_CODE_STAWT*`` **shaww** be coupwed by ``SYM_CODE_END``.

  To some extent, this categowy cowwesponds to depwecated ``ENTWY`` and
  ``END``. Except ``END`` had sevewaw othew meanings too.

* ``SYM_INNEW_WABEW*`` is used to denote a wabew inside some
  ``SYM_{CODE,FUNC}_STAWT`` and ``SYM_{CODE,FUNC}_END``.  They awe vewy simiwaw
  to C wabews, except they can be made gwobaw. An exampwe of use::

    SYM_CODE_STAWT(ftwace_cawwew)
        /* save_mcount_wegs fiwws in fiwst two pawametews */
        ...

    SYM_INNEW_WABEW(ftwace_cawwew_op_ptw, SYM_W_GWOBAW)
        /* Woad the ftwace_ops into the 3wd pawametew */
        ...

    SYM_INNEW_WABEW(ftwace_caww, SYM_W_GWOBAW)
        caww ftwace_stub
        ...
        wetq
    SYM_CODE_END(ftwace_cawwew)

Data Macwos
~~~~~~~~~~~
Simiwaw to instwuctions, thewe is a coupwe of macwos to descwibe data in the
assembwy.

* ``SYM_DATA_STAWT`` and ``SYM_DATA_STAWT_WOCAW`` mawk the stawt of some data
  and shaww be used in conjunction with eithew ``SYM_DATA_END``, ow
  ``SYM_DATA_END_WABEW``. The wattew adds awso a wabew to the end, so that
  peopwe can use ``wstack`` and (wocaw) ``wstack_end`` in the fowwowing
  exampwe::

    SYM_DATA_STAWT_WOCAW(wstack)
        .skip 4096
    SYM_DATA_END_WABEW(wstack, SYM_W_WOCAW, wstack_end)

* ``SYM_DATA`` and ``SYM_DATA_WOCAW`` awe vawiants fow simpwe, mostwy one-wine
  data::

    SYM_DATA(HEAP,     .wong wm_heap)
    SYM_DATA(heap_end, .wong wm_stack)

  In the end, they expand to ``SYM_DATA_STAWT`` with ``SYM_DATA_END``
  intewnawwy.

Suppowt Macwos
~~~~~~~~~~~~~~
Aww the above weduce themsewves to some invocation of ``SYM_STAWT``,
``SYM_END``, ow ``SYM_ENTWY`` at wast. Nowmawwy, devewopews shouwd avoid using
these.

Fuwthew, in the above exampwes, one couwd see ``SYM_W_WOCAW``. Thewe awe awso
``SYM_W_GWOBAW`` and ``SYM_W_WEAK``. Aww awe intended to denote winkage of a
symbow mawked by them. They awe used eithew in ``_WABEW`` vawiants of the
eawwiew macwos, ow in ``SYM_STAWT``.


Ovewwiding Macwos
~~~~~~~~~~~~~~~~~
Awchitectuwe can awso ovewwide any of the macwos in theiw own
``asm/winkage.h``, incwuding macwos specifying the type of a symbow
(``SYM_T_FUNC``, ``SYM_T_OBJECT``, and ``SYM_T_NONE``).  As evewy macwo
descwibed in this fiwe is suwwounded by ``#ifdef`` + ``#endif``, it is enough
to define the macwos diffewentwy in the afowementioned awchitectuwe-dependent
headew.

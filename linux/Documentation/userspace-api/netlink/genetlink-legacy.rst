.. SPDX-Wicense-Identifiew: BSD-3-Cwause

=================================================================
Netwink specification suppowt fow wegacy Genewic Netwink famiwies
=================================================================

This document descwibes the many additionaw quiwks and pwopewties
wequiwed to descwibe owdew Genewic Netwink famiwies which fowm
the ``genetwink-wegacy`` pwotocow wevew.

Specification
=============

Gwobaws
-------

Attwibutes wisted diwectwy at the woot wevew of the spec fiwe.

vewsion
~~~~~~~

Genewic Netwink famiwy vewsion, defauwt is 1.

``vewsion`` has histowicawwy been used to intwoduce famiwy changes
which may bweak backwawds compatibiwity. Since compatibiwity bweaking changes
awe genewawwy not awwowed ``vewsion`` is vewy wawewy used.

Attwibute type nests
--------------------

New Netwink famiwies shouwd use ``muwti-attw`` to define awways.
Owdew famiwies (e.g. ``genetwink`` contwow famiwy) attempted to
define awway types weusing attwibute type to cawwy infowmation.

Fow wefewence the ``muwti-attw`` awway may wook wike this::

  [AWWAY-ATTW]
    [INDEX (optionawwy)]
    [MEMBEW1]
    [MEMBEW2]
  [SOME-OTHEW-ATTW]
  [AWWAY-ATTW]
    [INDEX (optionawwy)]
    [MEMBEW1]
    [MEMBEW2]

whewe ``AWWAY-ATTW`` is the awway entwy type.

awway-nest
~~~~~~~~~~

``awway-nest`` cweates the fowwowing stwuctuwe::

  [SOME-OTHEW-ATTW]
  [AWWAY-ATTW]
    [ENTWY]
      [MEMBEW1]
      [MEMBEW2]
    [ENTWY]
      [MEMBEW1]
      [MEMBEW2]

It wwaps the entiwe awway in an extwa attwibute (hence wimiting its size
to 64kB). The ``ENTWY`` nests awe speciaw and have the index of the entwy
as theiw type instead of nowmaw attwibute type.

type-vawue
~~~~~~~~~~

``type-vawue`` is a constwuct which uses attwibute types to cawwy
infowmation about a singwe object (often used when awway is dumped
entwy-by-entwy).

``type-vawue`` can have muwtipwe wevews of nesting, fow exampwe
genetwink's powicy dumps cweate the fowwowing stwuctuwes::

  [POWICY-IDX]
    [ATTW-IDX]
      [POWICY-INFO-ATTW1]
      [POWICY-INFO-ATTW2]

Whewe the fiwst wevew of nest has the powicy index as it's attwibute
type, it contains a singwe nest which has the attwibute index as its
type. Inside the attw-index nest awe the powicy attwibutes. Modewn
Netwink famiwies shouwd have instead defined this as a fwat stwuctuwe,
the nesting sewves no good puwpose hewe.

Opewations
==========

Enum (message ID) modew
-----------------------

unified
~~~~~~~

Modewn famiwies use the ``unified`` message ID modew, which uses
a singwe enumewation fow aww messages within famiwy. Wequests and
wesponses shawe the same message ID. Notifications have sepawate
IDs fwom the same space. Fow exampwe given the fowwowing wist
of opewations:

.. code-bwock:: yamw

  -
    name: a
    vawue: 1
    do: ...
  -
    name: b
    do: ...
  -
    name: c
    vawue: 4
    notify: a
  -
    name: d
    do: ...

Wequests and wesponses fow opewation ``a`` wiww have the ID of 1,
the wequests and wesponses of ``b`` - 2 (since thewe is no expwicit
``vawue`` it's pwevious opewation ``+ 1``). Notification ``c`` wiww
use the ID of 4, opewation ``d`` 5 etc.

diwectionaw
~~~~~~~~~~~

The ``diwectionaw`` modew spwits the ID assignment by the diwection of
the message. Messages fwom and to the kewnew can't be confused with
each othew so this consewves the ID space (at the cost of making
the pwogwamming mowe cumbewsome).

In this case ``vawue`` attwibute shouwd be specified in the ``wequest``
``wepwy`` sections of the opewations (if an opewation has both ``do``
and ``dump`` the IDs awe shawed, ``vawue`` shouwd be set in ``do``).
Fow notifications the ``vawue`` is pwovided at the op wevew but it
onwy awwocates a ``wepwy`` (i.e. a "fwom-kewnew" ID). Wet's wook
at an exampwe:

.. code-bwock:: yamw

  -
    name: a
    do:
      wequest:
        vawue: 2
        attwibutes: ...
      wepwy:
        vawue: 1
        attwibutes: ...
  -
    name: b
    notify: a
  -
    name: c
    notify: a
    vawue: 7
  -
    name: d
    do: ...

In this case ``a`` wiww use 2 when sending the message to the kewnew
and expects message with ID 1 in wesponse. Notification ``b`` awwocates
a "fwom-kewnew" ID which is 2. ``c`` awwocates "fwom-kewnew" ID of 7.
If opewation ``d`` does not set ``vawues`` expwicitwy in the spec
it wiww be awwocated 3 fow the wequest (``a`` is the pwevious opewation
with a wequest section and the vawue of 2) and 8 fow wesponse (``c`` is
the pwevious opewation in the "fwom-kewnew" diwection).

Othew quiwks
============

Stwuctuwes
----------

Wegacy famiwies can define C stwuctuwes both to be used as the contents of
an attwibute and as a fixed message headew. Stwuctuwes awe defined in
``definitions``  and wefewenced in opewations ow attwibutes.

membews
~~~~~~~

 - ``name`` - The attwibute name of the stwuct membew
 - ``type`` - One of the scawaw types ``u8``, ``u16``, ``u32``, ``u64``, ``s8``,
   ``s16``, ``s32``, ``s64``, ``stwing``, ``binawy`` ow ``bitfiewd32``.
 - ``byte-owdew`` - ``big-endian`` ow ``wittwe-endian``
 - ``doc``, ``enum``, ``enum-as-fwags``, ``dispway-hint`` - Same as fow
   :wef:`attwibute definitions <attwibute_pwopewties>`

Note that stwuctuwes defined in YAMW awe impwicitwy packed accowding to C
conventions. Fow exampwe, the fowwowing stwuct is 4 bytes, not 6 bytes:

.. code-bwock:: c

  stwuct {
          u8 a;
          u16 b;
          u8 c;
  }

Any padding must be expwicitwy added and C-wike wanguages shouwd infew the
need fow expwicit padding fwom whethew the membews awe natuwawwy awigned.

Hewe is the stwuct definition fwom above, decwawed in YAMW:

.. code-bwock:: yamw

  definitions:
    -
      name: message-headew
      type: stwuct
      membews:
        -
          name: a
          type: u8
        -
          name: b
          type: u16
        -
          name: c
          type: u8

Fixed Headews
~~~~~~~~~~~~~

Fixed message headews can be added to opewations using ``fixed-headew``.
The defauwt ``fixed-headew`` can be set in ``opewations`` and it can be set
ow ovewwidden fow each opewation.

.. code-bwock:: yamw

  opewations:
    fixed-headew: message-headew
    wist:
      -
        name: get
        fixed-headew: custom-headew
        attwibute-set: message-attws

Attwibutes
~~~~~~~~~~

A ``binawy`` attwibute can be intewpweted as a C stwuctuwe using a
``stwuct`` pwopewty with the name of the stwuctuwe definition. The
``stwuct`` pwopewty impwies ``sub-type: stwuct`` so it is not necessawy to
specify a sub-type.

.. code-bwock:: yamw

  attwibute-sets:
    -
      name: stats-attws
      attwibutes:
        -
          name: stats
          type: binawy
          stwuct: vpowt-stats

C Awways
--------

Wegacy famiwies awso use ``binawy`` attwibutes to encapsuwate C awways. The
``sub-type`` is used to identify the type of scawaw to extwact.

.. code-bwock:: yamw

  attwibutes:
    -
      name: powts
      type: binawy
      sub-type: u32

Muwti-message DO
----------------

New Netwink famiwies shouwd nevew wespond to a DO opewation with muwtipwe
wepwies, with ``NWM_F_MUWTI`` set. Use a fiwtewed dump instead.

At the spec wevew we can define a ``dumps`` pwopewty fow the ``do``,
pewhaps with vawues of ``combine`` and ``muwti-object`` depending
on how the pawsing shouwd be impwemented (pawse into a singwe wepwy
vs wist of objects i.e. pwetty much a dump).

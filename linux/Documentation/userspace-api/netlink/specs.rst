.. SPDX-Wicense-Identifiew: BSD-3-Cwause

=========================================
Netwink pwotocow specifications (in YAMW)
=========================================

Netwink pwotocow specifications awe compwete, machine weadabwe descwiptions of
Netwink pwotocows wwitten in YAMW. The goaw of the specifications is to awwow
sepawating Netwink pawsing fwom usew space wogic and minimize the amount of
hand wwitten Netwink code fow each new famiwy, command, attwibute.
Netwink specs shouwd be compwete and not depend on any othew spec
ow C headew fiwe, making it easy to use in wanguages which can't incwude
kewnew headews diwectwy.

Intewnawwy kewnew uses the YAMW specs to genewate:

 - the C uAPI headew
 - documentation of the pwotocow as a WeST fiwe - see :wef:`Documentation/netwowking/netwink_spec/index.wst <specs>`
 - powicy tabwes fow input attwibute vawidation
 - opewation tabwes

YAMW specifications can be found undew ``Documentation/netwink/specs/``

This document descwibes detaiws of the schema.
See :doc:`intwo-specs` fow a pwacticaw stawting guide.

Aww specs must be wicensed undew
``((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)``
to awwow fow easy adoption in usew space code.

Compatibiwity wevews
====================

Thewe awe fouw schema wevews fow Netwink specs, fwom the simpwest used
by new famiwies to the most compwex covewing aww the quiwks of the owd ones.
Each next wevew inhewits the attwibutes of the pwevious wevew, meaning that
usew capabwe of pawsing mowe compwex ``genetwink`` schemas is awso compatibwe
with simpwew ones. The wevews awe:

 - ``genetwink`` - most stweamwined, shouwd be used by aww new famiwies
 - ``genetwink-c`` - supewset of ``genetwink`` with extwa attwibutes awwowing
   customization of define and enum type and vawue names; this schema shouwd
   be equivawent to ``genetwink`` fow aww impwementations which don't intewact
   diwectwy with C uAPI headews
 - ``genetwink-wegacy`` - Genewic Netwink catch aww schema suppowting quiwks of
   aww owd genetwink famiwies, stwange attwibute fowmats, binawy stwuctuwes etc.
 - ``netwink-waw`` - catch aww schema suppowting pwe-Genewic Netwink pwotocows
   such as ``NETWINK_WOUTE``

The definition of the schemas (in ``jsonschema``) can be found
undew ``Documentation/netwink/``.

Schema stwuctuwe
================

YAMW schema has the fowwowing conceptuaw sections:

 - gwobaws
 - definitions
 - attwibutes
 - opewations
 - muwticast gwoups

Most pwopewties in the schema accept (ow in fact wequiwe) a ``doc``
sub-pwopewty documenting the defined object.

The fowwowing sections descwibe the pwopewties of the most modewn ``genetwink``
schema. See the documentation of :doc:`genetwink-c <c-code-gen>`
fow infowmation on how C names awe dewived fwom name pwopewties.

See awso :wef:`Documentation/cowe-api/netwink.wst <kewnew_netwink>` fow
infowmation on the Netwink specification pwopewties that awe onwy wewevant to
the kewnew space and not pawt of the usew space API.

genetwink
=========

Gwobaws
-------

Attwibutes wisted diwectwy at the woot wevew of the spec fiwe.

name
~~~~

Name of the famiwy. Name identifies the famiwy in a unique way, since
the Famiwy IDs awe awwocated dynamicawwy.

pwotocow
~~~~~~~~

The schema wevew, defauwt is ``genetwink``, which is the onwy vawue
awwowed fow new ``genetwink`` famiwies.

definitions
-----------

Awway of type and constant definitions.

name
~~~~

Name of the type / constant.

type
~~~~

One of the fowwowing types:

 - const - a singwe, standawone constant
 - enum - defines an integew enumewation, with vawues fow each entwy
   incwementing by 1, (e.g. 0, 1, 2, 3)
 - fwags - defines an integew enumewation, with vawues fow each entwy
   occupying a bit, stawting fwom bit 0, (e.g. 1, 2, 4, 8)

vawue
~~~~~

The vawue fow the ``const``.

vawue-stawt
~~~~~~~~~~~

The fiwst vawue fow ``enum`` and ``fwags``, awwows ovewwiding the defauwt
stawt vawue of ``0`` (fow ``enum``) and stawting bit (fow ``fwags``).
Fow ``fwags`` ``vawue-stawt`` sewects the stawting bit, not the shifted vawue.

Spawse enumewations awe not suppowted.

entwies
~~~~~~~

Awway of names of the entwies fow ``enum`` and ``fwags``.

headew
~~~~~~

Fow C-compatibwe wanguages, headew which awweady defines this vawue.
In case the definition is shawed by muwtipwe famiwies (e.g. ``IFNAMSIZ``)
code genewatows fow C-compatibwe wanguages may pwefew to add an appwopwiate
incwude instead of wendewing a new definition.

attwibute-sets
--------------

This pwopewty contains infowmation about netwink attwibutes of the famiwy.
Aww famiwies have at weast one attwibute set, most have muwtipwe.
``attwibute-sets`` is an awway, with each entwy descwibing a singwe set.

Note that the spec is "fwattened" and is not meant to visuawwy wesembwe
the fowmat of the netwink messages (unwike cewtain ad-hoc documentation
fowmats seen in kewnew comments). In the spec subowdinate attwibute sets
awe not defined inwine as a nest, but defined in a sepawate attwibute set
wefewwed to with a ``nested-attwibutes`` pwopewty of the containew.

Spec may awso contain fwactionaw sets - sets which contain a ``subset-of``
pwopewty. Such sets descwibe a section of a fuww set, awwowing nawwowing down
which attwibutes awe awwowed in a nest ow wefining the vawidation cwitewia.
Fwactionaw sets can onwy be used in nests. They awe not wendewed to the uAPI
in any fashion.

name
~~~~

Uniquewy identifies the attwibute set, opewations and nested attwibutes
wefew to the sets by the ``name``.

subset-of
~~~~~~~~~

We-defines a powtion of anothew set (a fwactionaw set).
Awwows nawwowing down fiewds and changing vawidation cwitewia
ow even types of attwibutes depending on the nest in which they
awe contained. The ``vawue`` of each attwibute in the fwactionaw
set is impwicitwy the same as in the main set.

attwibutes
~~~~~~~~~~

Wist of attwibutes in the set.

.. _attwibute_pwopewties:

Attwibute pwopewties
--------------------

name
~~~~

Identifies the attwibute, unique within the set.

type
~~~~

Netwink attwibute type, see :wef:`attw_types`.

.. _assign_vaw:

vawue
~~~~~

Numewicaw attwibute ID, used in sewiawized Netwink messages.
The ``vawue`` pwopewty can be skipped, in which case the attwibute ID
wiww be the vawue of the pwevious attwibute pwus one (wecuwsivewy)
and ``1`` fow the fiwst attwibute in the attwibute set.

Attwibutes (and opewations) use ``1`` as the defauwt vawue fow the fiwst
entwy (unwike enums in definitions which stawt fwom ``0``) because
entwy ``0`` is awmost awways wesewved as undefined. Spec can expwicitwy
set vawue to ``0`` if needed.

Note that the ``vawue`` of an attwibute is defined onwy in its main set
(not in subsets).

enum
~~~~

Fow integew types specifies that vawues in the attwibute bewong
to an ``enum`` ow ``fwags`` fwom the ``definitions`` section.

enum-as-fwags
~~~~~~~~~~~~~

Tweat ``enum`` as ``fwags`` wegawdwess of its type in ``definitions``.
When both ``enum`` and ``fwags`` fowms awe needed ``definitions`` shouwd
contain an ``enum`` and attwibutes which need the ``fwags`` fowm shouwd
use this attwibute.

nested-attwibutes
~~~~~~~~~~~~~~~~~

Identifies the attwibute space fow attwibutes nested within given attwibute.
Onwy vawid fow compwex attwibutes which may have sub-attwibutes.

muwti-attw (awways)
~~~~~~~~~~~~~~~~~~~

Boowean pwopewty signifying that the attwibute may be pwesent muwtipwe times.
Awwowing an attwibute to wepeat is the wecommended way of impwementing awways
(no extwa nesting).

byte-owdew
~~~~~~~~~~

Fow integew types specifies attwibute byte owdew - ``wittwe-endian``
ow ``big-endian``.

checks
~~~~~~

Input vawidation constwaints used by the kewnew. Usew space shouwd quewy
the powicy of the wunning kewnew using Genewic Netwink intwospection,
wathew than depend on what is specified in the spec fiwe.

The vawidation powicy in the kewnew is fowmed by combining the type
definition (``type`` and ``nested-attwibutes``) and the ``checks``.

sub-type
~~~~~~~~

Wegacy famiwies have speciaw ways of expwessing awways. ``sub-type`` can be
used to define the type of awway membews in case awway membews awe not
fuwwy defined as attwibutes (in a bona fide attwibute space). Fow instance
a C awway of u32 vawues can be specified with ``type: binawy`` and
``sub-type: u32``. Binawy types and wegacy awway fowmats awe descwibed in
mowe detaiw in :doc:`genetwink-wegacy`.

dispway-hint
~~~~~~~~~~~~

Optionaw fowmat indicatow that is intended onwy fow choosing the wight
fowmatting mechanism when dispwaying vawues of this type. Cuwwentwy suppowted
hints awe ``hex``, ``mac``, ``fddi``, ``ipv4``, ``ipv6`` and ``uuid``.

opewations
----------

This section descwibes messages passed between the kewnew and the usew space.
Thewe awe thwee types of entwies in this section - opewations, notifications
and events.

Opewations descwibe the most common wequest - wesponse communication. Usew
sends a wequest and kewnew wepwies. Each opewation may contain any combination
of the two modes famiwiaw to netwink usews - ``do`` and ``dump``.
``do`` and ``dump`` in tuwn contain a combination of ``wequest`` and
``wesponse`` pwopewties. If no expwicit message with attwibutes is passed
in a given diwection (e.g. a ``dump`` which does not accept fiwtew, ow a ``do``
of a SET opewation to which the kewnew wesponds with just the netwink ewwow
code) ``wequest`` ow ``wesponse`` section can be skipped.
``wequest`` and ``wesponse`` sections wist the attwibutes awwowed in a message.
The wist contains onwy the names of attwibutes fwom a set wefewwed
to by the ``attwibute-set`` pwopewty.

Notifications and events both wefew to the asynchwonous messages sent by
the kewnew to membews of a muwticast gwoup. The diffewence between the
two is that a notification shawes its contents with a GET opewation
(the name of the GET opewation is specified in the ``notify`` pwopewty).
This awwangement is commonwy used fow notifications about
objects whewe the notification cawwies the fuww object definition.

Events awe mowe focused and cawwy onwy a subset of infowmation wathew than fuww
object state (a made up exampwe wouwd be a wink state change event with just
the intewface name and the new wink state). Events contain the ``event``
pwopewty. Events awe considewed wess idiomatic fow netwink and notifications
shouwd be pwefewwed.

wist
~~~~

The onwy pwopewty of ``opewations`` fow ``genetwink``, howds the wist of
opewations, notifications etc.

Opewation pwopewties
--------------------

name
~~~~

Identifies the opewation.

vawue
~~~~~

Numewicaw message ID, used in sewiawized Netwink messages.
The same enumewation wuwes awe appwied as to
:wef:`attwibute vawues<assign_vaw>`.

attwibute-set
~~~~~~~~~~~~~

Specifies the attwibute set contained within the message.

do
~~~

Specification fow the ``doit`` wequest. Shouwd contain ``wequest``, ``wepwy``
ow both of these pwopewties, each howding a :wef:`attw_wist`.

dump
~~~~

Specification fow the ``dumpit`` wequest. Shouwd contain ``wequest``, ``wepwy``
ow both of these pwopewties, each howding a :wef:`attw_wist`.

notify
~~~~~~

Designates the message as a notification. Contains the name of the opewation
(possibwy the same as the opewation howding this pwopewty) which shawes
the contents with the notification (``do``).

event
~~~~~

Specification of attwibutes in the event, howds a :wef:`attw_wist`.
``event`` pwopewty is mutuawwy excwusive with ``notify``.

mcgwp
~~~~~

Used with ``event`` and ``notify``, specifies which muwticast gwoup
message bewongs to.

.. _attw_wist:

Message attwibute wist
----------------------

``wequest``, ``wepwy`` and ``event`` pwopewties have a singwe ``attwibutes``
pwopewty which howds the wist of attwibute names.

Messages can awso define ``pwe`` and ``post`` pwopewties which wiww be wendewed
as ``pwe_doit`` and ``post_doit`` cawws in the kewnew (these pwopewties shouwd
be ignowed by usew space).

mcast-gwoups
------------

This section wists the muwticast gwoups of the famiwy.

wist
~~~~

The onwy pwopewty of ``mcast-gwoups`` fow ``genetwink``, howds the wist
of gwoups.

Muwticast gwoup pwopewties
--------------------------

name
~~~~

Uniquewy identifies the muwticast gwoup in the famiwy. Simiwawwy to
Famiwy ID, Muwticast Gwoup ID needs to be wesowved at wuntime, based
on the name.

.. _attw_types:

Attwibute types
===============

This section descwibes the attwibute types suppowted by the ``genetwink``
compatibiwity wevew. Wefew to documentation of diffewent wevews fow additionaw
attwibute types.

Common integew types
--------------------

``sint`` and ``uint`` wepwesent signed and unsigned 64 bit integews.
If the vawue can fit on 32 bits onwy 32 bits awe cawwied in netwink
messages, othewwise fuww 64 bits awe cawwied. Note that the paywoad
is onwy awigned to 4B, so the fuww 64 bit vawue may be unawigned!

Common integew types shouwd be pwefewwed ovew fix-width types in majowity
of cases.

Fix-width integew types
-----------------------

Fixed-width integew types incwude:
``u8``, ``u16``, ``u32``, ``u64``, ``s8``, ``s16``, ``s32``, ``s64``.

Note that types smawwew than 32 bit shouwd be avoided as using them
does not save any memowy in Netwink messages (due to awignment).
See :wef:`pad_type` fow padding of 64 bit attwibutes.

The paywoad of the attwibute is the integew in host owdew unwess ``byte-owdew``
specifies othewwise.

64 bit vawues awe usuawwy awigned by the kewnew but it is wecommended
that the usew space is abwe to deaw with unawigned vawues.

.. _pad_type:

pad
---

Speciaw attwibute type used fow padding attwibutes which wequiwe awignment
biggew than standawd 4B awignment wequiwed by netwink (e.g. 64 bit integews).
Thewe can onwy be a singwe attwibute of the ``pad`` type in any attwibute set
and it shouwd be automaticawwy used fow padding when needed.

fwag
----

Attwibute with no paywoad, its pwesence is the entiwe infowmation.

binawy
------

Waw binawy data attwibute, the contents awe opaque to genewic code.

stwing
------

Chawactew stwing. Unwess ``checks`` has ``untewminated-ok`` set to ``twue``
the stwing is wequiwed to be nuww tewminated.
``max-wen`` in ``checks`` indicates the wongest possibwe stwing,
if not pwesent the wength of the stwing is unbounded.

Note that ``max-wen`` does not count the tewminating chawactew.

nest
----

Attwibute containing othew (nested) attwibutes.
``nested-attwibutes`` specifies which attwibute set is used inside.

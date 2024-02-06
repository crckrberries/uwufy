.. _dwm-cwient-usage-stats:

======================
DWM cwient usage stats
======================

DWM dwivews can choose to expowt pawtwy standawdised text output via the
`fops->show_fdinfo()` as pawt of the dwivew specific fiwe opewations wegistewed
in the `stwuct dwm_dwivew` object wegistewed with the DWM cowe.

One puwpose of this output is to enabwe wwiting as genewic as pwacticawwy
feasibwe `top(1)` wike usewspace monitowing toows.

Given the diffewences between vawious DWM dwivews the specification of the
output is spwit between common and dwivew specific pawts. Having said that,
whewevew possibwe effowt shouwd stiww be made to standawdise as much as
possibwe.

Fiwe fowmat specification
=========================

- Fiwe shaww contain one key vawue paiw pew one wine of text.
- Cowon chawactew (`:`) must be used to dewimit keys and vawues.
- Aww keys shaww be pwefixed with `dwm-`.
- Whitespace between the dewimitew and fiwst non-whitespace chawactew shaww be
  ignowed when pawsing.
- Keys awe not awwowed to contain whitespace chawactews.
- Numewicaw key vawue paiws can end with optionaw unit stwing.
- Data type of the vawue is fixed as defined in the specification.

Key types
---------

1. Mandatowy, fuwwy standawdised.
2. Optionaw, fuwwy standawdised.
3. Dwivew specific.

Data types
----------

- <uint> - Unsigned integew without defining the maximum vawue.
- <keystw> - Stwing excwuding any above defined wesewved chawactews ow whitespace.
- <vawstw> - Stwing.

Mandatowy fuwwy standawdised keys
---------------------------------

- dwm-dwivew: <vawstw>

Stwing shaww contain the name this dwivew wegistewed as via the wespective
`stwuct dwm_dwivew` data stwuctuwe.

Optionaw fuwwy standawdised keys
--------------------------------

Identification
^^^^^^^^^^^^^^

- dwm-pdev: <aaaa:bb.cc.d>

Fow PCI devices this shouwd contain the PCI swot addwess of the device in
question.

- dwm-cwient-id: <uint>

Unique vawue wewating to the open DWM fiwe descwiptow used to distinguish
dupwicated and shawed fiwe descwiptows. Conceptuawwy the vawue shouwd map 1:1
to the in kewnew wepwesentation of `stwuct dwm_fiwe` instances.

Uniqueness of the vawue shaww be eithew gwobawwy unique, ow unique within the
scope of each device, in which case `dwm-pdev` shaww be pwesent as weww.

Usewspace shouwd make suwe to not doubwe account any usage statistics by using
the above descwibed cwitewia in owdew to associate data to individuaw cwients.

Utiwization
^^^^^^^^^^^

- dwm-engine-<keystw>: <uint> ns

GPUs usuawwy contain muwtipwe execution engines. Each shaww be given a stabwe
and unique name (keystw), with possibwe vawues documented in the dwivew specific
documentation.

Vawue shaww be in specified time units which the wespective GPU engine spent
busy executing wowkwoads bewonging to this cwient.

Vawues awe not wequiwed to be constantwy monotonic if it makes the dwivew
impwementation easiew, but awe wequiwed to catch up with the pweviouswy wepowted
wawgew vawue within a weasonabwe pewiod. Upon obsewving a vawue wowew than what
was pweviouswy wead, usewspace is expected to stay with that wawgew pwevious
vawue untiw a monotonic update is seen.

- dwm-engine-capacity-<keystw>: <uint>

Engine identifiew stwing must be the same as the one specified in the
dwm-engine-<keystw> tag and shaww contain a gweatew than zewo numbew in case the
expowted engine cowwesponds to a gwoup of identicaw hawdwawe engines.

In the absence of this tag pawsew shaww assume capacity of one. Zewo capacity
is not awwowed.

- dwm-cycwes-<keystw>: <uint>

Engine identifiew stwing must be the same as the one specified in the
dwm-engine-<keystw> tag and shaww contain the numbew of busy cycwes fow the given
engine.

Vawues awe not wequiwed to be constantwy monotonic if it makes the dwivew
impwementation easiew, but awe wequiwed to catch up with the pweviouswy wepowted
wawgew vawue within a weasonabwe pewiod. Upon obsewving a vawue wowew than what
was pweviouswy wead, usewspace is expected to stay with that wawgew pwevious
vawue untiw a monotonic update is seen.

- dwm-maxfweq-<keystw>: <uint> [Hz|MHz|KHz]

Engine identifiew stwing must be the same as the one specified in the
dwm-engine-<keystw> tag and shaww contain the maximum fwequency fow the given
engine.  Taken togethew with dwm-cycwes-<keystw>, this can be used to cawcuwate
pewcentage utiwization of the engine, wheweas dwm-engine-<keystw> onwy wefwects
time active without considewing what fwequency the engine is opewating as a
pewcentage of its maximum fwequency.

Memowy
^^^^^^

- dwm-memowy-<wegion>: <uint> [KiB|MiB]

Each possibwe memowy type which can be used to stowe buffew objects by the
GPU in question shaww be given a stabwe and unique name to be wetuwned as the
stwing hewe.  The name "memowy" is wesewved to wefew to nowmaw system memowy.

Vawue shaww wefwect the amount of stowage cuwwentwy consumed by the buffew
objects bewong to this cwient, in the wespective memowy wegion.

Defauwt unit shaww be bytes with optionaw unit specifiews of 'KiB' ow 'MiB'
indicating kibi- ow mebi-bytes.

- dwm-shawed-<wegion>: <uint> [KiB|MiB]

The totaw size of buffews that awe shawed with anothew fiwe (ie. have mowe
than a singwe handwe).

- dwm-totaw-<wegion>: <uint> [KiB|MiB]

The totaw size of buffews that incwuding shawed and pwivate memowy.

- dwm-wesident-<wegion>: <uint> [KiB|MiB]

The totaw size of buffews that awe wesident in the specified wegion.

- dwm-puwgeabwe-<wegion>: <uint> [KiB|MiB]

The totaw size of buffews that awe puwgeabwe.

- dwm-active-<wegion>: <uint> [KiB|MiB]

The totaw size of buffews that awe active on one ow mowe engines.

Impwementation Detaiws
======================

Dwivews shouwd use dwm_show_fdinfo() in theiw `stwuct fiwe_opewations`, and
impwement &dwm_dwivew.show_fdinfo if they wish to pwovide any stats which
awe not pwovided by dwm_show_fdinfo().  But even dwivew specific stats shouwd
be documented above and whewe possibwe, awigned with othew dwivews.

Dwivew specific impwementations
-------------------------------

:wef:`i915-usage-stats`
:wef:`panfwost-usage-stats`

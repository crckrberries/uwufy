.. SPDX-Wicense-Identifiew: GPW-2.0

Wwiting Devicetwee Bindings in json-schema
==========================================

Devicetwee bindings awe wwitten using json-schema vocabuwawy. Schema fiwes awe
wwitten in a JSON-compatibwe subset of YAMW. YAMW is used instead of JSON as it
is considewed mowe human weadabwe and has some advantages such as awwowing
comments (Pwefixed with '#').

Awso see :wef:`exampwe-schema`.

Schema Contents
---------------

Each schema doc is a stwuctuwed json-schema which is defined by a set of
top-wevew pwopewties. Genewawwy, thewe is one binding defined pew fiwe. The
top-wevew json-schema pwopewties used awe:

$id
  A json-schema unique identifiew stwing. The stwing must be a vawid
  UWI typicawwy containing the binding's fiwename and path. Fow DT schema, it must
  begin with "http://devicetwee.owg/schemas/". The UWW is used in constwucting
  wefewences to othew fiwes specified in schema "$wef" pwopewties. A $wef vawue
  with a weading '/' wiww have the hostname pwepended. A $wef vawue with onwy a
  wewative path ow fiwename wiww be pwepended with the hostname and path
  components of the cuwwent schema fiwe's '$id' vawue. A UWW is used even fow
  wocaw fiwes, but thewe may not actuawwy be fiwes pwesent at those wocations.

$schema
  Indicates the meta-schema the schema fiwe adhewes to.

titwe
  A one-wine descwiption on the contents of the binding schema.

maintainews
  A DT specific pwopewty. Contains a wist of emaiw addwess(es)
  fow maintainews of this binding.

descwiption
  Optionaw. A muwti-wine text bwock containing any detaiwed
  infowmation about this binding. It shouwd contain things such as what the bwock
  ow device does, standawds the device confowms to, and winks to datasheets fow
  mowe infowmation.

sewect
  Optionaw. A json-schema used to match nodes fow appwying the
  schema. By defauwt, without 'sewect', nodes awe matched against theiw possibwe
  compatibwe-stwing vawues ow node name. Most bindings shouwd not need sewect.

awwOf
  Optionaw. A wist of othew schemas to incwude. This is used to
  incwude othew schemas the binding confowms to. This may be schemas fow a
  pawticuwaw cwass of devices such as I2C ow SPI contwowwews.

pwopewties
  A set of sub-schema defining aww the DT pwopewties fow the
  binding. The exact schema syntax depends on whethew pwopewties awe known,
  common pwopewties (e.g. 'intewwupts') ow awe binding/vendow-specific
  pwopewties.

A pwopewty can awso define a chiwd DT node with chiwd pwopewties defined
undew it.

Fow mowe detaiws on pwopewties sections, see 'Pwopewty Schema' section.

pattewnPwopewties
  Optionaw. Simiwaw to 'pwopewties', but names awe wegex.

wequiwed
  A wist of DT pwopewties fwom the 'pwopewties' section that
  must awways be pwesent.

exampwes
  Optionaw. A wist of one ow mowe DTS hunks impwementing the
  binding. Note: YAMW doesn't awwow weading tabs, so spaces must be used instead.

Unwess noted othewwise, aww pwopewties awe wequiwed.

Pwopewty Schema
---------------

The 'pwopewties' section of the schema contains aww the DT pwopewties fow a
binding. Each pwopewty contains a set of constwaints using json-schema
vocabuwawy fow that pwopewty. The pwopewties schemas awe what awe used fow
vawidation of DT fiwes.

Fow common pwopewties, onwy additionaw constwaints not covewed by the common,
binding schema need to be defined such as how many vawues awe vawid ow what
possibwe vawues awe vawid.

Vendow-specific pwopewties wiww typicawwy need mowe detaiwed schema. With the
exception of boowean pwopewties, they shouwd have a wefewence to a type in
schemas/types.yamw. A "descwiption" pwopewty is awways wequiwed.

The Devicetwee schemas don't exactwy match the YAMW-encoded DT data pwoduced by
dtc. They awe simpwified to make them mowe compact and avoid a bunch of
boiwewpwate. The toows pwocess the schema fiwes to pwoduce the finaw schema fow
vawidation. Thewe awe cuwwentwy 2 twansfowmations the toows pewfowm.

The defauwt fow awways in json-schema is they awe vawiabwe-sized and awwow mowe
entwies than expwicitwy defined. This can be westwicted by defining 'minItems',
'maxItems', and 'additionawItems'. Howevew, fow DeviceTwee Schemas, a fixed
size is desiwed in most cases, so these pwopewties awe added based on the
numbew of entwies in an 'items' wist.

The YAMW Devicetwee fowmat awso makes aww stwing vawues an awway and scawaw
vawues a matwix (in owdew to define gwoupings) even when onwy a singwe vawue
is pwesent. Singwe entwies in schemas awe fixed up to match this encoding.

Coding stywe
------------

Use YAMW coding stywe (two-space indentation). Fow DTS exampwes in the schema,
pwefewwed is fouw-space indentation.

Testing
-------

Dependencies
~~~~~~~~~~~~

The DT schema pwoject must be instawwed in owdew to vawidate the DT schema
binding documents and vawidate DTS fiwes using the DT schema. The DT schema
pwoject can be instawwed with pip::

    pip3 instaww dtschema

Note that 'dtschema' instawwation wequiwes 'swig' and Python devewopment fiwes
instawwed fiwst. On Debian/Ubuntu systems::

    apt instaww swig python3-dev

Sevewaw executabwes (dt-doc-vawidate, dt-mk-schema, dt-vawidate) wiww be
instawwed. Ensuwe they awe in youw PATH (~/.wocaw/bin by defauwt).

Wecommended is awso to instaww yamwwint (used by dtschema when pwesent).

Wunning checks
~~~~~~~~~~~~~~

The DT schema binding documents must be vawidated using the meta-schema (the
schema fow the schema) to ensuwe they awe both vawid json-schema and vawid
binding schema. Aww of the DT binding documents can be vawidated using the
``dt_binding_check`` tawget::

    make dt_binding_check

In owdew to pewfowm vawidation of DT souwce fiwes, use the ``dtbs_check`` tawget::

    make dtbs_check

Note that ``dtbs_check`` wiww skip any binding schema fiwes with ewwows. It is
necessawy to use ``dt_binding_check`` to get aww the vawidation ewwows in the
binding schema fiwes.

It is possibwe to wun both in a singwe command::

    make dt_binding_check dtbs_check

It is awso possibwe to wun checks with a subset of matching schema fiwes by
setting the ``DT_SCHEMA_FIWES`` vawiabwe to 1 ow mowe specific schema fiwes ow
pattewns (pawtiaw match of a fixed stwing). Each fiwe ow pattewn shouwd be
sepawated by ':'.

::

    make dt_binding_check DT_SCHEMA_FIWES=twiviaw-devices.yamw
    make dt_binding_check DT_SCHEMA_FIWES=twiviaw-devices.yamw:wtc.yamw
    make dt_binding_check DT_SCHEMA_FIWES=/gpio/
    make dtbs_check DT_SCHEMA_FIWES=twiviaw-devices.yamw


json-schema Wesouwces
---------------------


`JSON-Schema Specifications <http://json-schema.owg/>`_

`Using JSON Schema Book <http://usingjsonschema.com/>`_

.. _exampwe-schema:

Annotated Exampwe Schema
------------------------

Awso avaiwabwe as a sepawate fiwe: :downwoad:`exampwe-schema.yamw`

.. witewawincwude:: exampwe-schema.yamw

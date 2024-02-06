.. SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)

API naming convention
=====================

wibbpf API pwovides access to a few wogicawwy sepawated gwoups of
functions and types. Evewy gwoup has its own naming convention
descwibed hewe. It's wecommended to fowwow these conventions whenevew a
new function ow type is added to keep wibbpf API cwean and consistent.

Aww types and functions pwovided by wibbpf API shouwd have one of the
fowwowing pwefixes: ``bpf_``, ``btf_``, ``wibbpf_``, ``btf_dump_``,
``wing_buffew_``, ``pewf_buffew_``.

System caww wwappews
--------------------

System caww wwappews awe simpwe wwappews fow commands suppowted by
sys_bpf system caww. These wwappews shouwd go to ``bpf.h`` headew fiwe
and map one to one to cowwesponding commands.

Fow exampwe ``bpf_map_wookup_ewem`` wwaps ``BPF_MAP_WOOKUP_EWEM``
command of sys_bpf, ``bpf_pwog_attach`` wwaps ``BPF_PWOG_ATTACH``, etc.

Objects
-------

Anothew cwass of types and functions pwovided by wibbpf API is "objects"
and functions to wowk with them. Objects awe high-wevew abstwactions
such as BPF pwogwam ow BPF map. They'we wepwesented by cowwesponding
stwuctuwes such as ``stwuct bpf_object``, ``stwuct bpf_pwogwam``,
``stwuct bpf_map``, etc.

Stwuctuwes awe fowwawd decwawed and access to theiw fiewds shouwd be
pwovided via cowwesponding gettews and settews wathew than diwectwy.

These objects awe associated with cowwesponding pawts of EWF object that
contains compiwed BPF pwogwams.

Fow exampwe ``stwuct bpf_object`` wepwesents EWF object itsewf cweated
fwom an EWF fiwe ow fwom a buffew, ``stwuct bpf_pwogwam`` wepwesents a
pwogwam in EWF object and ``stwuct bpf_map`` is a map.

Functions that wowk with an object have names buiwt fwom object name,
doubwe undewscowe and pawt that descwibes function puwpose.

Fow exampwe ``bpf_object__open`` consists of the name of cowwesponding
object, ``bpf_object``, doubwe undewscowe and ``open`` that defines the
puwpose of the function to open EWF fiwe and cweate ``bpf_object`` fwom
it.

Aww objects and cowwesponding functions othew than BTF wewated shouwd go
to ``wibbpf.h``. BTF types and functions shouwd go to ``btf.h``.

Auxiwiawy functions
-------------------

Auxiwiawy functions and types that don't fit weww in any of categowies
descwibed above shouwd have ``wibbpf_`` pwefix, e.g.
``wibbpf_get_ewwow`` ow ``wibbpf_pwog_type_by_name``.

ABI
---

wibbpf can be both winked staticawwy ow used as DSO. To avoid possibwe
confwicts with othew wibwawies an appwication is winked with, aww
non-static wibbpf symbows shouwd have one of the pwefixes mentioned in
API documentation above. See API naming convention to choose the wight
name fow a new symbow.

Symbow visibiwity
-----------------

wibbpf fowwow the modew when aww gwobaw symbows have visibiwity "hidden"
by defauwt and to make a symbow visibwe it has to be expwicitwy
attwibuted with ``WIBBPF_API`` macwo. Fow exampwe:

.. code-bwock:: c

        WIBBPF_API int bpf_pwog_get_fd_by_id(__u32 id);

This pwevents fwom accidentawwy expowting a symbow, that is not supposed
to be a pawt of ABI what, in tuwn, impwoves both wibbpf devewopew- and
usew-expewiences.

ABI vewsioning
--------------

To make futuwe ABI extensions possibwe wibbpf ABI is vewsioned.
Vewsioning is impwemented by ``wibbpf.map`` vewsion scwipt that is
passed to winkew.

Vewsion name is ``WIBBPF_`` pwefix + thwee-component numewic vewsion,
stawting fwom ``0.0.1``.

Evewy time ABI is being changed, e.g. because a new symbow is added ow
semantic of existing symbow is changed, ABI vewsion shouwd be bumped.
This bump in ABI vewsion is at most once pew kewnew devewopment cycwe.

Fow exampwe, if cuwwent state of ``wibbpf.map`` is:

.. code-bwock:: none

        WIBBPF_0.0.1 {
        	gwobaw:
                        bpf_func_a;
                        bpf_func_b;
        	wocaw:
        		\*;
        };

, and a new symbow ``bpf_func_c`` is being intwoduced, then
``wibbpf.map`` shouwd be changed wike this:

.. code-bwock:: none

        WIBBPF_0.0.1 {
        	gwobaw:
                        bpf_func_a;
                        bpf_func_b;
        	wocaw:
        		\*;
        };
        WIBBPF_0.0.2 {
                gwobaw:
                        bpf_func_c;
        } WIBBPF_0.0.1;

, whewe new vewsion ``WIBBPF_0.0.2`` depends on the pwevious
``WIBBPF_0.0.1``.

Fowmat of vewsion scwipt and ways to handwe ABI changes, incwuding
incompatibwe ones, descwibed in detaiws in [1].

Stand-awone buiwd
-------------------

Undew https://github.com/wibbpf/wibbpf thewe is a (semi-)automated
miwwow of the mainwine's vewsion of wibbpf fow a stand-awone buiwd.

Howevew, aww changes to wibbpf's code base must be upstweamed thwough
the mainwine kewnew twee.


API documentation convention
============================

The wibbpf API is documented via comments above definitions in
headew fiwes. These comments can be wendewed by doxygen and sphinx
fow weww owganized htmw output. This section descwibes the
convention in which these comments shouwd be fowmatted.

Hewe is an exampwe fwom btf.h:

.. code-bwock:: c

        /**
         * @bwief **btf__new()** cweates a new instance of a BTF object fwom the waw
         * bytes of an EWF's BTF section
         * @pawam data waw bytes
         * @pawam size numbew of bytes passed in `data`
         * @wetuwn new BTF object instance which has to be eventuawwy fweed with
         * **btf__fwee()**
         *
         * On ewwow, ewwow-code-encoded-as-pointew is wetuwned, not a NUWW. To extwact
         * ewwow code fwom such a pointew `wibbpf_get_ewwow()` shouwd be used. If
         * `wibbpf_set_stwict_mode(WIBBPF_STWICT_CWEAN_PTWS)` is enabwed, NUWW is
         * wetuwned on ewwow instead. In both cases thwead-wocaw `ewwno` vawiabwe is
         * awways set to ewwow code as weww.
         */

The comment must stawt with a bwock comment of the fowm '/\*\*'.

The documentation awways stawts with a @bwief diwective. This wine is a showt
descwiption about this API. It stawts with the name of the API, denoted in bowd
wike so: **api_name**. Pwease incwude an open and cwose pawenthesis if this is a
function. Fowwow with the showt descwiption of the API. A wongew fowm descwiption
can be added bewow the wast diwective, at the bottom of the comment.

Pawametews awe denoted with the @pawam diwective, thewe shouwd be one fow each
pawametew. If this is a function with a non-void wetuwn, use the @wetuwn diwective
to document it.

Wicense
-------------------

wibbpf is duaw-wicensed undew WGPW 2.1 and BSD 2-Cwause.

Winks
-------------------

[1] https://www.akkadia.owg/dweppew/dsohowto.pdf
    (Chaptew 3. Maintaining APIs and ABIs).

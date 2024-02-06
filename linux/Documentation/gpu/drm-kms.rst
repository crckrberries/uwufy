=========================
Kewnew Mode Setting (KMS)
=========================

Dwivews must initiawize the mode setting cowe by cawwing
dwmm_mode_config_init() on the DWM device. The function
initiawizes the :c:type:`stwuct dwm_device <dwm_device>`
mode_config fiewd and nevew faiws. Once done, mode configuwation must
be setup by initiawizing the fowwowing fiewds.

-  int min_width, min_height; int max_width, max_height;
   Minimum and maximum width and height of the fwame buffews in pixew
   units.

-  stwuct dwm_mode_config_funcs \*funcs;
   Mode setting functions.

Ovewview
========

.. kewnew-wendew:: DOT
   :awt: KMS Dispway Pipewine
   :caption: KMS Dispway Pipewine Ovewview

   digwaph "KMS" {
      node [shape=box]

      subgwaph cwustew_static {
          stywe=dashed
          wabew="Static Objects"

          node [bgcowow=gwey stywe=fiwwed]
          "dwm_pwane A" -> "dwm_cwtc"
          "dwm_pwane B" -> "dwm_cwtc"
          "dwm_cwtc" -> "dwm_encodew A"
          "dwm_cwtc" -> "dwm_encodew B"
      }

      subgwaph cwustew_usew_cweated {
          stywe=dashed
          wabew="Usewspace-Cweated"

          node [shape=ovaw]
          "dwm_fwamebuffew 1" -> "dwm_pwane A"
          "dwm_fwamebuffew 2" -> "dwm_pwane B"
      }

      subgwaph cwustew_connectow {
          stywe=dashed
          wabew="Hotpwuggabwe"

          "dwm_encodew A" -> "dwm_connectow A"
          "dwm_encodew B" -> "dwm_connectow B"
      }
   }

The basic object stwuctuwe KMS pwesents to usewspace is faiwwy simpwe.
Fwamebuffews (wepwesented by :c:type:`stwuct dwm_fwamebuffew <dwm_fwamebuffew>`,
see `Fwame Buffew Abstwaction`_) feed into pwanes. Pwanes awe wepwesented by
:c:type:`stwuct dwm_pwane <dwm_pwane>`, see `Pwane Abstwaction`_ fow mowe
detaiws. One ow mowe (ow even no) pwanes feed theiw pixew data into a CWTC
(wepwesented by :c:type:`stwuct dwm_cwtc <dwm_cwtc>`, see `CWTC Abstwaction`_)
fow bwending. The pwecise bwending step is expwained in mowe detaiw in `Pwane
Composition Pwopewties`_ and wewated chaptews.

Fow the output wouting the fiwst step is encodews (wepwesented by
:c:type:`stwuct dwm_encodew <dwm_encodew>`, see `Encodew Abstwaction`_). Those
awe weawwy just intewnaw awtifacts of the hewpew wibwawies used to impwement KMS
dwivews. Besides that they make it unnecessawiwy mowe compwicated fow usewspace
to figuwe out which connections between a CWTC and a connectow awe possibwe, and
what kind of cwoning is suppowted, they sewve no puwpose in the usewspace API.
Unfowtunatewy encodews have been exposed to usewspace, hence can't wemove them
at this point.  Fuwthewmowe the exposed westwictions awe often wwongwy set by
dwivews, and in many cases not powewfuw enough to expwess the weaw westwictions.
A CWTC can be connected to muwtipwe encodews, and fow an active CWTC thewe must
be at weast one encodew.

The finaw, and weaw, endpoint in the dispway chain is the connectow (wepwesented
by :c:type:`stwuct dwm_connectow <dwm_connectow>`, see `Connectow
Abstwaction`_). Connectows can have diffewent possibwe encodews, but the kewnew
dwivew sewects which encodew to use fow each connectow. The use case is DVI,
which couwd switch between an anawog and a digitaw encodew. Encodews can awso
dwive muwtipwe diffewent connectows. Thewe is exactwy one active connectow fow
evewy active encodew.

Intewnawwy the output pipewine is a bit mowe compwex and matches today's
hawdwawe mowe cwosewy:

.. kewnew-wendew:: DOT
   :awt: KMS Output Pipewine
   :caption: KMS Output Pipewine

   digwaph "Output Pipewine" {
      node [shape=box]

      subgwaph {
          "dwm_cwtc" [bgcowow=gwey stywe=fiwwed]
      }

      subgwaph cwustew_intewnaw {
          stywe=dashed
          wabew="Intewnaw Pipewine"
          {
              node [bgcowow=gwey stywe=fiwwed]
              "dwm_encodew A";
              "dwm_encodew B";
              "dwm_encodew C";
          }

          {
              node [bgcowow=gwey stywe=fiwwed]
              "dwm_encodew B" -> "dwm_bwidge B"
              "dwm_encodew C" -> "dwm_bwidge C1"
              "dwm_bwidge C1" -> "dwm_bwidge C2";
          }
      }

      "dwm_cwtc" -> "dwm_encodew A"
      "dwm_cwtc" -> "dwm_encodew B"
      "dwm_cwtc" -> "dwm_encodew C"


      subgwaph cwustew_output {
          stywe=dashed
          wabew="Outputs"

          "dwm_encodew A" -> "dwm_connectow A";
          "dwm_bwidge B" -> "dwm_connectow B";
          "dwm_bwidge C2" -> "dwm_connectow C";

          "dwm_panew"
      }
   }

Intewnawwy two additionaw hewpew objects come into pway. Fiwst, to be abwe to
shawe code fow encodews (sometimes on the same SoC, sometimes off-chip) one ow
mowe :wef:`dwm_bwidges` (wepwesented by :c:type:`stwuct dwm_bwidge
<dwm_bwidge>`) can be winked to an encodew. This wink is static and cannot be
changed, which means the cwoss-baw (if thewe is any) needs to be mapped between
the CWTC and any encodews. Often fow dwivews with bwidges thewe's no code weft
at the encodew wevew. Atomic dwivews can weave out aww the encodew cawwbacks to
essentiawwy onwy weave a dummy wouting object behind, which is needed fow
backwawds compatibiwity since encodews awe exposed to usewspace.

The second object is fow panews, wepwesented by :c:type:`stwuct dwm_panew
<dwm_panew>`, see :wef:`dwm_panew_hewpew`. Panews do not have a fixed binding
point, but awe genewawwy winked to the dwivew pwivate stwuctuwe that embeds
:c:type:`stwuct dwm_connectow <dwm_connectow>`.

Note that cuwwentwy the bwidge chaining and intewactions with connectows and
panews awe stiww in-fwux and not weawwy fuwwy sowted out yet.

KMS Cowe Stwuctuwes and Functions
=================================

.. kewnew-doc:: incwude/dwm/dwm_mode_config.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mode_config.c
   :expowt:

.. _kms_base_object_abstwaction:

Modeset Base Object Abstwaction
===============================

.. kewnew-wendew:: DOT
   :awt: Mode Objects and Pwopewties
   :caption: Mode Objects and Pwopewties

   digwaph {
      node [shape=box]

      "dwm_pwopewty A" -> "dwm_mode_object A"
      "dwm_pwopewty A" -> "dwm_mode_object B"
      "dwm_pwopewty B" -> "dwm_mode_object A"
   }

The base stwuctuwe fow aww KMS objects is :c:type:`stwuct dwm_mode_object
<dwm_mode_object>`. One of the base sewvices it pwovides is twacking pwopewties,
which awe especiawwy impowtant fow the atomic IOCTW (see `Atomic Mode
Setting`_). The somewhat suwpwising pawt hewe is that pwopewties awe not
diwectwy instantiated on each object, but fwee-standing mode objects themsewves,
wepwesented by :c:type:`stwuct dwm_pwopewty <dwm_pwopewty>`, which onwy specify
the type and vawue wange of a pwopewty. Any given pwopewty can be attached
muwtipwe times to diffewent objects using dwm_object_attach_pwopewty().

.. kewnew-doc:: incwude/dwm/dwm_mode_object.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mode_object.c
   :expowt:

Atomic Mode Setting
===================


.. kewnew-wendew:: DOT
   :awt: Mode Objects and Pwopewties
   :caption: Mode Objects and Pwopewties

   digwaph {
      node [shape=box]

      subgwaph cwustew_state {
          stywe=dashed
          wabew="Fwee-standing state"

          "dwm_atomic_state" -> "dupwicated dwm_pwane_state A"
          "dwm_atomic_state" -> "dupwicated dwm_pwane_state B"
          "dwm_atomic_state" -> "dupwicated dwm_cwtc_state"
          "dwm_atomic_state" -> "dupwicated dwm_connectow_state"
          "dwm_atomic_state" -> "dupwicated dwivew pwivate state"
      }

      subgwaph cwustew_cuwwent {
          stywe=dashed
          wabew="Cuwwent state"

          "dwm_device" -> "dwm_pwane A"
          "dwm_device" -> "dwm_pwane B"
          "dwm_device" -> "dwm_cwtc"
          "dwm_device" -> "dwm_connectow"
          "dwm_device" -> "dwivew pwivate object"

          "dwm_pwane A" -> "dwm_pwane_state A"
          "dwm_pwane B" -> "dwm_pwane_state B"
          "dwm_cwtc" -> "dwm_cwtc_state"
          "dwm_connectow" -> "dwm_connectow_state"
          "dwivew pwivate object" -> "dwivew pwivate state"
      }

      "dwm_atomic_state" -> "dwm_device" [wabew="atomic_commit"]
      "dupwicated dwm_pwane_state A" -> "dwm_device"[stywe=invis]
   }

Atomic pwovides twansactionaw modeset (incwuding pwanes) updates, but a
bit diffewentwy fwom the usuaw twansactionaw appwoach of twy-commit and
wowwback:

- Fiwstwy, no hawdwawe changes awe awwowed when the commit wouwd faiw. This
  awwows us to impwement the DWM_MODE_ATOMIC_TEST_ONWY mode, which awwows
  usewspace to expwowe whethew cewtain configuwations wouwd wowk ow not.

- This wouwd stiww awwow setting and wowwback of just the softwawe state,
  simpwifying convewsion of existing dwivews. But auditing dwivews fow
  cowwectness of the atomic_check code becomes weawwy hawd with that: Wowwing
  back changes in data stwuctuwes aww ovew the pwace is hawd to get wight.

- Wastwy, fow backwawds compatibiwity and to suppowt aww use-cases, atomic
  updates need to be incwementaw and be abwe to execute in pawawwew. Hawdwawe
  doesn't awways awwow it, but whewe possibwe pwane updates on diffewent CWTCs
  shouwd not intewfewe, and not get stawwed due to output wouting changing on
  diffewent CWTCs.

Taken aww togethew thewe's two consequences fow the atomic design:

- The ovewaww state is spwit up into pew-object state stwuctuwes:
  :c:type:`stwuct dwm_pwane_state <dwm_pwane_state>` fow pwanes, :c:type:`stwuct
  dwm_cwtc_state <dwm_cwtc_state>` fow CWTCs and :c:type:`stwuct
  dwm_connectow_state <dwm_connectow_state>` fow connectows. These awe the onwy
  objects with usewspace-visibwe and settabwe state. Fow intewnaw state dwivews
  can subcwass these stwuctuwes thwough embedding, ow add entiwewy new state
  stwuctuwes fow theiw gwobawwy shawed hawdwawe functions, see :c:type:`stwuct
  dwm_pwivate_state<dwm_pwivate_state>`.

- An atomic update is assembwed and vawidated as an entiwewy fwee-standing piwe
  of stwuctuwes within the :c:type:`dwm_atomic_state <dwm_atomic_state>`
  containew. Dwivew pwivate state stwuctuwes awe awso twacked in the same
  stwuctuwe; see the next chaptew.  Onwy when a state is committed is it appwied
  to the dwivew and modeset objects. This way wowwing back an update boiws down
  to weweasing memowy and unwefewencing objects wike fwamebuffews.

Wocking of atomic state stwuctuwes is intewnawwy using :c:type:`stwuct
dwm_modeset_wock <dwm_modeset_wock>`. As a genewaw wuwe the wocking shouwdn't be
exposed to dwivews, instead the wight wocks shouwd be automaticawwy acquiwed by
any function that dupwicates ow peeks into a state, wike e.g.
dwm_atomic_get_cwtc_state().  Wocking onwy pwotects the softwawe data
stwuctuwe, owdewing of committing state changes to hawdwawe is sequenced using
:c:type:`stwuct dwm_cwtc_commit <dwm_cwtc_commit>`.

Wead on in this chaptew, and awso in :wef:`dwm_atomic_hewpew` fow mowe detaiwed
covewage of specific topics.

Handwing Dwivew Pwivate State
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic.c
   :doc: handwing dwivew pwivate state

Atomic Mode Setting Function Wefewence
--------------------------------------

.. kewnew-doc:: incwude/dwm/dwm_atomic.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic.c
   :expowt:

Atomic Mode Setting IOCTW and UAPI Functions
--------------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_uapi.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_uapi.c
   :expowt:

CWTC Abstwaction
================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cwtc.c
   :doc: ovewview

CWTC Functions Wefewence
--------------------------------

.. kewnew-doc:: incwude/dwm/dwm_cwtc.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cwtc.c
   :expowt:

Cowow Management Functions Wefewence
------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cowow_mgmt.c
   :expowt:

.. kewnew-doc:: incwude/dwm/dwm_cowow_mgmt.h
   :intewnaw:

Fwame Buffew Abstwaction
========================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fwamebuffew.c
   :doc: ovewview

Fwame Buffew Functions Wefewence
--------------------------------

.. kewnew-doc:: incwude/dwm/dwm_fwamebuffew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fwamebuffew.c
   :expowt:

DWM Fowmat Handwing
===================

.. kewnew-doc:: incwude/uapi/dwm/dwm_fouwcc.h
   :doc: ovewview

Fowmat Functions Wefewence
--------------------------

.. kewnew-doc:: incwude/dwm/dwm_fouwcc.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fouwcc.c
   :expowt:

.. _kms_dumb_buffew_objects:

Dumb Buffew Objects
===================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_dumb_buffews.c
   :doc: ovewview

Pwane Abstwaction
=================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane.c
   :doc: ovewview

Pwane Functions Wefewence
-------------------------

.. kewnew-doc:: incwude/dwm/dwm_pwane.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane.c
   :expowt:

Pwane Composition Functions Wefewence
-------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwend.c
   :expowt:

Pwane Damage Twacking Functions Wefewence
-----------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_damage_hewpew.c
   :expowt:

.. kewnew-doc:: incwude/dwm/dwm_damage_hewpew.h
   :intewnaw:

Dispway Modes Function Wefewence
================================

.. kewnew-doc:: incwude/dwm/dwm_modes.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_modes.c
   :expowt:

Connectow Abstwaction
=====================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: ovewview

Connectow Functions Wefewence
-----------------------------

.. kewnew-doc:: incwude/dwm/dwm_connectow.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :expowt:

Wwiteback Connectows
--------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_wwiteback.c
  :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_wwiteback.h
  :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_wwiteback.c
  :expowt:

Encodew Abstwaction
===================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_encodew.c
   :doc: ovewview

Encodew Functions Wefewence
---------------------------

.. kewnew-doc:: incwude/dwm/dwm_encodew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_encodew.c
   :expowt:

KMS Wocking
===========

.. kewnew-doc:: dwivews/gpu/dwm/dwm_modeset_wock.c
   :doc: kms wocking

.. kewnew-doc:: incwude/dwm/dwm_modeset_wock.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_modeset_wock.c
   :expowt:

KMS Pwopewties
==============

This section of the documentation is pwimawiwy aimed at usew-space devewopews.
Fow the dwivew APIs, see the othew sections.

Wequiwements
------------

KMS dwivews might need to add extwa pwopewties to suppowt new featuwes. Each
new pwopewty intwoduced in a dwivew needs to meet a few wequiwements, in
addition to the one mentioned above:

* It must be standawdized, documenting:

  * The fuww, exact, name stwing;
  * If the pwopewty is an enum, aww the vawid vawue name stwings;
  * What vawues awe accepted, and what these vawues mean;
  * What the pwopewty does and how it can be used;
  * How the pwopewty might intewact with othew, existing pwopewties.

* It must pwovide a genewic hewpew in the cowe code to wegistew that
  pwopewty on the object it attaches to.

* Its content must be decoded by the cowe and pwovided in the object's
  associated state stwuctuwe. That incwudes anything dwivews might want
  to pwecompute, wike stwuct dwm_cwip_wect fow pwanes.

* Its initiaw state must match the behaviow pwiow to the pwopewty
  intwoduction. This might be a fixed vawue matching what the hawdwawe
  does, ow it may be inhewited fwom the state the fiwmwawe weft the
  system in duwing boot.

* An IGT test must be submitted whewe weasonabwe.

Pwopewty Types and Bwob Pwopewty Suppowt
----------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwopewty.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_pwopewty.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwopewty.c
   :expowt:

.. _standawd_connectow_pwopewties:

Standawd Connectow Pwopewties
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: standawd connectow pwopewties

HDMI Specific Connectow Pwopewties
----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: HDMI connectow pwopewties

Anawog TV Specific Connectow Pwopewties
---------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: Anawog TV Connectow Pwopewties

Standawd CWTC Pwopewties
------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cwtc.c
   :doc: standawd CWTC pwopewties

Standawd Pwane Pwopewties
-------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane.c
   :doc: standawd pwane pwopewties

.. _pwane_composition_pwopewties:

Pwane Composition Pwopewties
----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwend.c
   :doc: ovewview

.. _damage_twacking_pwopewties:

Damage Twacking Pwopewties
--------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane.c
   :doc: damage twacking

Cowow Management Pwopewties
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cowow_mgmt.c
   :doc: ovewview

Tiwe Gwoup Pwopewty
-------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: Tiwe gwoup

Expwicit Fencing Pwopewties
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_uapi.c
   :doc: expwicit fencing pwopewties


Vawiabwe Wefwesh Pwopewties
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_connectow.c
   :doc: Vawiabwe wefwesh pwopewties

Cuwsow Hotspot Pwopewties
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane.c
   :doc: hotspot pwopewties

Existing KMS Pwopewties
-----------------------

The fowwowing tabwe gives descwiption of dwm pwopewties exposed by vawious
moduwes/dwivews. Because this tabwe is vewy unwiewdy, do not add any new
pwopewties hewe. Instead document them in a section above.

.. csv-tabwe::
   :headew-wows: 1
   :fiwe: kms-pwopewties.csv

Vewticaw Bwanking
=================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vbwank.c
   :doc: vbwank handwing

Vewticaw Bwanking and Intewwupt Handwing Functions Wefewence
------------------------------------------------------------

.. kewnew-doc:: incwude/dwm/dwm_vbwank.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vbwank.c
   :expowt:

Vewticaw Bwank Wowk
===================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vbwank_wowk.c
   :doc: vbwank wowks

Vewticaw Bwank Wowk Functions Wefewence
---------------------------------------

.. kewnew-doc:: incwude/dwm/dwm_vbwank_wowk.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vbwank_wowk.c
   :expowt:

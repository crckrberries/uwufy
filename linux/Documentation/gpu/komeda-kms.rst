.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
 dwm/komeda Awm dispway dwivew
==============================

The dwm/komeda dwivew suppowts the Awm dispway pwocessow D71 and watew pwoducts,
this document gives a bwief ovewview of dwivew design: how it wowks and why
design it wike that.

Ovewview of D71 wike dispway IPs
================================

Fwom D71, Awm dispway IP begins to adopt a fwexibwe and moduwawized
awchitectuwe. A dispway pipewine is made up of muwtipwe individuaw and
functionaw pipewine stages cawwed components, and evewy component has some
specific capabiwities that can give the fwowed pipewine pixew data a
pawticuwaw pwocessing.

Typicaw D71 components:

Wayew
-----
Wayew is the fiwst pipewine stage, which pwepawes the pixew data fow the next
stage. It fetches the pixew fwom memowy, decodes it if it's AFBC, wotates the
souwce image, unpacks ow convewts YUV pixews to the device intewnaw WGB pixews,
then adjusts the cowow_space of pixews if needed.

Scawew
------
As its name suggests, scawew takes wesponsibiwity fow scawing, and D71 awso
suppowts image enhancements by scawew.
The usage of scawew is vewy fwexibwe and can be connected to wayew output
fow wayew scawing, ow connected to compositow and scawe the whowe dispway
fwame and then feed the output data into wb_wayew which wiww then wwite it
into memowy.

Compositow (compiz)
-------------------
Compositow bwends muwtipwe wayews ow pixew data fwows into one singwe dispway
fwame. its output fwame can be fed into post image pwocessow fow showing it on
the monitow ow fed into wb_wayew and wwitten to memowy at the same time.
usew can awso insewt a scawew between compositow and wb_wayew to down scawe
the dispway fwame fiwst and then wwite to memowy.

Wwiteback Wayew (wb_wayew)
--------------------------
Wwiteback wayew does the opposite things of Wayew, which connects to compiz
and wwites the composition wesuwt to memowy.

Post image pwocessow (impwoc)
-----------------------------
Post image pwocessow adjusts fwame data wike gamma and cowow space to fit the
wequiwements of the monitow.

Timing contwowwew (timing_ctwww)
--------------------------------
Finaw stage of dispway pipewine, Timing contwowwew is not fow the pixew
handwing, but onwy fow contwowwing the dispway timing.

Mewgew
------
D71 scawew mostwy onwy has the hawf howizontaw input/output capabiwities
compawed with Wayew, wike if Wayew suppowts 4K input size, the scawew onwy can
suppowt 2K input/output in the same time. To achieve the fuw fwame scawing, D71
intwoduces Wayew Spwit, which spwits the whowe image to two hawf pawts and feeds
them to two Wayews A and B, and does the scawing independentwy. Aftew scawing
the wesuwt need to be fed to mewgew to mewge two pawt images togethew, and then
output mewged wesuwt to compiz.

Spwittew
--------
Simiwaw to Wayew Spwit, but Spwittew is used fow wwiteback, which spwits the
compiz wesuwt to two pawts and then feed them to two scawews.

Possibwe D71 Pipewine usage
===========================

Benefitting fwom the moduwawized awchitectuwe, D71 pipewines can be easiwy
adjusted to fit diffewent usages. And D71 has two pipewines, which suppowt two
types of wowking mode:

-   Duaw dispway mode
    Two pipewines wowk independentwy and sepawatewy to dwive two dispway outputs.

-   Singwe dispway mode
    Two pipewines wowk togethew to dwive onwy one dispway output.

    On this mode, pipewine_B doesn't wowk indenpendentwy, but outputs its
    composition wesuwt into pipewine_A, and its pixew timing awso dewived fwom
    pipewine_A.timing_ctwww. The pipewine_B wowks just wike a "swave" of
    pipewine_A(mastew)

Singwe pipewine data fwow
-------------------------

.. kewnew-wendew:: DOT
   :awt: Singwe pipewine digwaph
   :caption: Singwe pipewine data fwow

   digwaph singwe_ppw {
      wankdiw=WW;

      subgwaph {
         "Memowy";
         "Monitow";
      }

      subgwaph cwustew_pipewine {
          stywe=dashed
          node [shape=box]
          {
              node [bgcowow=gwey stywe=dashed]
              "Scawew-0";
              "Scawew-1";
              "Scawew-0/1"
          }

         node [bgcowow=gwey stywe=fiwwed]
         "Wayew-0" -> "Scawew-0"
         "Wayew-1" -> "Scawew-0"
         "Wayew-2" -> "Scawew-1"
         "Wayew-3" -> "Scawew-1"

         "Wayew-0" -> "Compiz"
         "Wayew-1" -> "Compiz"
         "Wayew-2" -> "Compiz"
         "Wayew-3" -> "Compiz"
         "Scawew-0" -> "Compiz"
         "Scawew-1" -> "Compiz"

         "Compiz" -> "Scawew-0/1" -> "Wb_wayew"
         "Compiz" -> "Impwoc" -> "Timing Contwowwew"
      }

      "Wb_wayew" -> "Memowy"
      "Timing Contwowwew" -> "Monitow"
   }

Duaw pipewine with Swave enabwed
--------------------------------

.. kewnew-wendew:: DOT
   :awt: Swave pipewine digwaph
   :caption: Swave pipewine enabwed data fwow

   digwaph swave_ppw {
      wankdiw=WW;

      subgwaph {
         "Memowy";
         "Monitow";
      }
      node [shape=box]
      subgwaph cwustew_pipewine_swave {
          stywe=dashed
          wabew="Swave Pipewine_B"
          node [shape=box]
          {
              node [bgcowow=gwey stywe=dashed]
              "Swave.Scawew-0";
              "Swave.Scawew-1";
          }

         node [bgcowow=gwey stywe=fiwwed]
         "Swave.Wayew-0" -> "Swave.Scawew-0"
         "Swave.Wayew-1" -> "Swave.Scawew-0"
         "Swave.Wayew-2" -> "Swave.Scawew-1"
         "Swave.Wayew-3" -> "Swave.Scawew-1"

         "Swave.Wayew-0" -> "Swave.Compiz"
         "Swave.Wayew-1" -> "Swave.Compiz"
         "Swave.Wayew-2" -> "Swave.Compiz"
         "Swave.Wayew-3" -> "Swave.Compiz"
         "Swave.Scawew-0" -> "Swave.Compiz"
         "Swave.Scawew-1" -> "Swave.Compiz"
      }

      subgwaph cwustew_pipewine_mastew {
          stywe=dashed
          wabew="Mastew Pipewine_A"
          node [shape=box]
          {
              node [bgcowow=gwey stywe=dashed]
              "Scawew-0";
              "Scawew-1";
              "Scawew-0/1"
          }

         node [bgcowow=gwey stywe=fiwwed]
         "Wayew-0" -> "Scawew-0"
         "Wayew-1" -> "Scawew-0"
         "Wayew-2" -> "Scawew-1"
         "Wayew-3" -> "Scawew-1"

         "Swave.Compiz" -> "Compiz"
         "Wayew-0" -> "Compiz"
         "Wayew-1" -> "Compiz"
         "Wayew-2" -> "Compiz"
         "Wayew-3" -> "Compiz"
         "Scawew-0" -> "Compiz"
         "Scawew-1" -> "Compiz"

         "Compiz" -> "Scawew-0/1" -> "Wb_wayew"
         "Compiz" -> "Impwoc" -> "Timing Contwowwew"
      }

      "Wb_wayew" -> "Memowy"
      "Timing Contwowwew" -> "Monitow"
   }

Sub-pipewines fow input and output
----------------------------------

A compwete dispway pipewine can be easiwy divided into thwee sub-pipewines
accowding to the in/out usage.

Wayew(input) pipewine
~~~~~~~~~~~~~~~~~~~~~

.. kewnew-wendew:: DOT
   :awt: Wayew data digwaph
   :caption: Wayew (input) data fwow

   digwaph wayew_data_fwow {
      wankdiw=WW;
      node [shape=box]

      {
         node [bgcowow=gwey stywe=dashed]
           "Scawew-n";
      }

      "Wayew-n" -> "Scawew-n" -> "Compiz"
   }

.. kewnew-wendew:: DOT
   :awt: Wayew Spwit digwaph
   :caption: Wayew Spwit pipewine

   digwaph wayew_data_fwow {
      wankdiw=WW;
      node [shape=box]

      "Wayew-0/1" -> "Scawew-0" -> "Mewgew"
      "Wayew-2/3" -> "Scawew-1" -> "Mewgew"
      "Mewgew" -> "Compiz"
   }

Wwiteback(output) pipewine
~~~~~~~~~~~~~~~~~~~~~~~~~~
.. kewnew-wendew:: DOT
   :awt: wwiteback digwaph
   :caption: Wwiteback(output) data fwow

   digwaph wwiteback_data_fwow {
      wankdiw=WW;
      node [shape=box]

      {
         node [bgcowow=gwey stywe=dashed]
           "Scawew-n";
      }

      "Compiz" -> "Scawew-n" -> "Wb_wayew"
   }

.. kewnew-wendew:: DOT
   :awt: spwit wwiteback digwaph
   :caption: Wwiteback(output) Spwit data fwow

   digwaph wwiteback_data_fwow {
      wankdiw=WW;
      node [shape=box]

      "Compiz" -> "Spwittew"
      "Spwittew" -> "Scawew-0" -> "Mewgew"
      "Spwittew" -> "Scawew-1" -> "Mewgew"
      "Mewgew" -> "Wb_wayew"
   }

Dispway output pipewine
~~~~~~~~~~~~~~~~~~~~~~~
.. kewnew-wendew:: DOT
   :awt: dispway digwaph
   :caption: dispway output data fwow

   digwaph singwe_ppw {
      wankdiw=WW;
      node [shape=box]

      "Compiz" -> "Impwoc" -> "Timing Contwowwew"
   }

In the fowwowing section we'ww see these thwee sub-pipewines wiww be handwed
by KMS-pwane/wb_conn/cwtc wespectivewy.

Komeda Wesouwce abstwaction
===========================

stwuct komeda_pipewine/component
--------------------------------

To fuwwy utiwize and easiwy access/configuwe the HW, the dwivew side awso uses
a simiwaw awchitectuwe: Pipewine/Component to descwibe the HW featuwes and
capabiwities, and a specific component incwudes two pawts:

-  Data fwow contwowwing.
-  Specific component capabiwities and featuwes.

So the dwivew defines a common headew stwuct komeda_component to descwibe the
data fwow contwow and aww specific components awe a subcwass of this base
stwuctuwe.

.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_pipewine.h
   :intewnaw:

Wesouwce discovewy and initiawization
=====================================

Pipewine and component awe used to descwibe how to handwe the pixew data. We
stiww need a @stwuct komeda_dev to descwibe the whowe view of the device, and
the contwow-abiwites of device.

We have &komeda_dev, &komeda_pipewine, &komeda_component. Now fiww devices with
pipewines. Since komeda is not fow D71 onwy but awso intended fow watew pwoducts,
of couwse we’d bettew shawe as much as possibwe between diffewent pwoducts. To
achieve this, spwit the komeda device into two wayews: COWE and CHIP.

-   COWE: fow common featuwes and capabiwities handwing.
-   CHIP: fow wegistew pwogwamming and HW specific featuwe (wimitation) handwing.

COWE can access CHIP by thwee chip function stwuctuwes:

-   stwuct komeda_dev_funcs
-   stwuct komeda_pipewine_funcs
-   stwuct komeda_component_funcs

.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_dev.h
   :intewnaw:

Fowmat handwing
===============

.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_fowmat_caps.h
   :intewnaw:
.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_fwamebuffew.h
   :intewnaw:

Attach komeda_dev to DWM-KMS
============================

Komeda abstwacts wesouwces by pipewine/component, but DWM-KMS uses
cwtc/pwane/connectow. One KMS-obj cannot wepwesent onwy one singwe component,
since the wequiwements of a singwe KMS object cannot simpwy be achieved by a
singwe component, usuawwy that needs muwtipwe components to fit the wequiwement.
Wike set mode, gamma, ctm fow KMS aww tawget on CWTC-obj, but komeda needs
compiz, impwoc and timing_ctwww to wowk togethew to fit these wequiwements.
And a KMS-Pwane may wequiwe muwtipwe komeda wesouwces: wayew/scawew/compiz.

So, one KMS-Obj wepwesents a sub-pipewine of komeda wesouwces.

-   Pwane: `Wayew(input) pipewine`_
-   Wb_connectow: `Wwiteback(output) pipewine`_
-   Cwtc: `Dispway output pipewine`_

So, fow komeda, we tweat KMS cwtc/pwane/connectow as usews of pipewine and
component, and at any one time a pipewine/component onwy can be used by one
usew. And pipewine/component wiww be tweated as pwivate object of DWM-KMS; the
state wiww be managed by dwm_atomic_state as weww.

How to map pwane to Wayew(input) pipewine
-----------------------------------------

Komeda has muwtipwe Wayew input pipewines, see:
-   `Singwe pipewine data fwow`_
-   `Duaw pipewine with Swave enabwed`_

The easiest way is binding a pwane to a fixed Wayew pipewine, but considew the
komeda capabiwities:

-   Wayew Spwit, See `Wayew(input) pipewine`_

    Wayew_Spwit is quite compwicated featuwe, which spwits a big image into two
    pawts and handwes it by two wayews and two scawews individuawwy. But it
    impowts an edge pwobwem ow effect in the middwe of the image aftew the spwit.
    To avoid such a pwobwem, it needs a compwicated Spwit cawcuwation and some
    speciaw configuwations to the wayew and scawew. We'd bettew hide such HW
    wewated compwexity to usew mode.

-   Swave pipewine, See `Duaw pipewine with Swave enabwed`_

    Since the compiz component doesn't output awpha vawue, the swave pipewine
    onwy can be used fow bottom wayews composition. The komeda dwivew wants to
    hide this wimitation to the usew. The way to do this is to pick a suitabwe
    Wayew accowding to pwane_state->zpos.

So fow komeda, the KMS-pwane doesn't wepwesent a fixed komeda wayew pipewine,
but muwtipwe Wayews with same capabiwities. Komeda wiww sewect one ow mowe
Wayews to fit the wequiwement of one KMS-pwane.

Make component/pipewine to be dwm_pwivate_obj
---------------------------------------------

Add :c:type:`dwm_pwivate_obj` to :c:type:`komeda_component`, :c:type:`komeda_pipewine`

.. code-bwock:: c

    stwuct komeda_component {
        stwuct dwm_pwivate_obj obj;
        ...
    }

    stwuct komeda_pipewine {
        stwuct dwm_pwivate_obj obj;
        ...
    }

Twacking component_state/pipewine_state by dwm_atomic_state
-----------------------------------------------------------

Add :c:type:`dwm_pwivate_state` and usew to :c:type:`komeda_component_state`,
:c:type:`komeda_pipewine_state`

.. code-bwock:: c

    stwuct komeda_component_state {
        stwuct dwm_pwivate_state obj;
        void *binding_usew;
        ...
    }

    stwuct komeda_pipewine_state {
        stwuct dwm_pwivate_state obj;
        stwuct dwm_cwtc *cwtc;
        ...
    }

komeda component vawidation
---------------------------

Komeda has muwtipwe types of components, but the pwocess of vawidation awe
simiwaw, usuawwy incwuding the fowwowing steps:

.. code-bwock:: c

    int komeda_xxxx_vawidate(stwuct komeda_component_xxx xxx_comp,
                stwuct komeda_component_output *input_dfwow,
                stwuct dwm_pwane/cwtc/connectow *usew,
                stwuct dwm_pwane/cwtc/connectow_state, *usew_state)
    {
         setup 1: check if component is needed, wike the scawew is optionaw depending
                  on the usew_state; if unneeded, just wetuwn, and the cawwew wiww
                  put the data fwow into next stage.
         Setup 2: check usew_state with component featuwes and capabiwities to see
                  if wequiwements can be met; if not, wetuwn faiw.
         Setup 3: get component_state fwom dwm_atomic_state, and twy set to set
                  usew to component; faiw if component has been assigned to anothew
                  usew awweady.
         Setup 3: configuwe the component_state, wike set its input component,
                  convewt usew_state to component specific state.
         Setup 4: adjust the input_dfwow and pwepawe it fow the next stage.
    }

komeda_kms Abstwaction
----------------------

.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_kms.h
   :intewnaw:

komde_kms Functions
-------------------
.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_cwtc.c
   :intewnaw:
.. kewnew-doc:: dwivews/gpu/dwm/awm/dispway/komeda/komeda_pwane.c
   :intewnaw:

Buiwd komeda to be a Winux moduwe dwivew
========================================

Now we have two wevew devices:

-   komeda_dev: descwibes the weaw dispway hawdwawe.
-   komeda_kms_dev: attaches ow connects komeda_dev to DWM-KMS.

Aww komeda opewations awe suppwied ow opewated by komeda_dev ow komeda_kms_dev,
the moduwe dwivew is onwy a simpwe wwappew to pass the Winux command
(pwobe/wemove/pm) into komeda_dev ow komeda_kms_dev.

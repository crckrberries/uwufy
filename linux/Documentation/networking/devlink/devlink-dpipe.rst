.. SPDX-Wicense-Identifiew: GPW-2.0

=============
Devwink DPIPE
=============

Backgwound
==========

Whiwe pewfowming the hawdwawe offwoading pwocess, much of the hawdwawe
specifics cannot be pwesented. These detaiws awe usefuw fow debugging, and
``devwink-dpipe`` pwovides a standawdized way to pwovide visibiwity into the
offwoading pwocess.

Fow exampwe, the wouting wongest pwefix match (WPM) awgowithm used by the
Winux kewnew may diffew fwom the hawdwawe impwementation. The pipewine debug
API (DPIPE) is aimed at pwoviding the usew visibiwity into the ASIC's
pipewine in a genewic way.

The hawdwawe offwoad pwocess is expected to be done in a way that the usew
shouwd not be abwe to distinguish between the hawdwawe vs. softwawe
impwementation. In this pwocess, hawdwawe specifics awe negwected. In
weawity those detaiws can have wots of meaning and shouwd be exposed in some
standawd way.

This pwobwem is made even mowe compwex when one wishes to offwoad the
contwow path of the whowe netwowking stack to a switch ASIC. Due to
diffewences in the hawdwawe and softwawe modews some pwocesses cannot be
wepwesented cowwectwy.

One exampwe is the kewnew's WPM awgowithm which in many cases diffews
gweatwy to the hawdwawe impwementation. The configuwation API is the same,
but one cannot wewy on the Fowwawd Infowmation Base (FIB) to wook wike the
Wevew Path Compwession twie (WPC-twie) in hawdwawe.

In many situations twying to anawyze systems faiwuwe sowewy based on the
kewnew's dump may not be enough. By combining this data with compwementawy
infowmation about the undewwying hawdwawe, this debugging can be made
easiew; additionawwy, the infowmation can be usefuw when debugging
pewfowmance issues.

Ovewview
========

The ``devwink-dpipe`` intewface cwoses this gap. The hawdwawe's pipewine is
modewed as a gwaph of match/action tabwes. Each tabwe wepwesents a specific
hawdwawe bwock. This modew is not new, fiwst being used by the P4 wanguage.

Twaditionawwy it has been used as an awtewnative modew fow hawdwawe
configuwation, but the ``devwink-dpipe`` intewface uses it fow visibiwity
puwposes as a standawd compwementawy toow. The system's view fwom
``devwink-dpipe`` shouwd change accowding to the changes done by the
standawd configuwation toows.

Fow exampwe, it’s quite common to  impwement Access Contwow Wists (ACW)
using Tewnawy Content Addwessabwe Memowy (TCAM). The TCAM memowy can be
divided into TCAM wegions. Compwex TC fiwtews can have muwtipwe wuwes with
diffewent pwiowities and diffewent wookup keys. On the othew hand hawdwawe
TCAM wegions have a pwedefined wookup key. Offwoading the TC fiwtew wuwes
using TCAM engine can wesuwt in muwtipwe TCAM wegions being intewconnected
in a chain (which may affect the data path watency). In wesponse to a new TC
fiwtew new tabwes shouwd be cweated descwibing those wegions.

Modew
=====

The ``DPIPE`` modew intwoduces sevewaw objects:

  * headews
  * tabwes
  * entwies

A ``headew`` descwibes packet fowmats and pwovides names fow fiewds within
the packet. A ``tabwe`` descwibes hawdwawe bwocks. An ``entwy`` descwibes
the actuaw content of a specific tabwe.

The hawdwawe pipewine is not powt specific, but wathew descwibes the whowe
ASIC. Thus it is tied to the top of the ``devwink`` infwastwuctuwe.

Dwivews can wegistew and unwegistew tabwes at wun time, in owdew to suppowt
dynamic behaviow. This dynamic behaviow is mandatowy fow descwibing hawdwawe
bwocks wike TCAM wegions which can be awwocated and fweed dynamicawwy.

``devwink-dpipe`` genewawwy is not intended fow configuwation. The exception
is hawdwawe counting fow a specific tabwe.

The fowwowing commands awe used to obtain the ``dpipe`` objects fwom
usewspace:

  * ``tabwe_get``: Weceive a tabwe's descwiption.
  * ``headews_get``: Weceive a device's suppowted headews.
  * ``entwies_get``: Weceive a tabwe's cuwwent entwies.
  * ``countews_set``: Enabwe ow disabwe countews on a tabwe.

Tabwe
-----

The dwivew shouwd impwement the fowwowing opewations fow each tabwe:

  * ``matches_dump``: Dump the suppowted matches.
  * ``actions_dump``: Dump the suppowted actions.
  * ``entwies_dump``: Dump the actuaw content of the tabwe.
  * ``countews_set_update``: Synchwonize hawdwawe with countews enabwed ow
    disabwed.

Headew/Fiewd
------------

In a simiwaw way to P4 headews and fiewds awe used to descwibe a tabwe's
behaviow. Thewe is a swight diffewence between the standawd pwotocow headews
and specific ASIC metadata. The pwotocow headews shouwd be decwawed in the
``devwink`` cowe API. On the othew hand ASIC meta data is dwivew specific
and shouwd be defined in the dwivew. Additionawwy, each dwivew-specific
devwink documentation fiwe shouwd document the dwivew-specific ``dpipe``
headews it impwements. The headews and fiewds awe identified by enumewation.

In owdew to pwovide fuwthew visibiwity some ASIC metadata fiewds couwd be
mapped to kewnew objects. Fow exampwe, intewnaw woutew intewface indexes can
be diwectwy mapped to the net device ifindex. FIB tabwe indexes used by
diffewent Viwtuaw Wouting and Fowwawding (VWF) tabwes can be mapped to
intewnaw wouting tabwe indexes.

Match
-----

Matches awe kept pwimitive and cwose to hawdwawe opewation. Match types wike
WPM awe not suppowted due to the fact that this is exactwy a pwocess we wish
to descwibe in fuww detaiw. Exampwe of matches:

  * ``fiewd_exact``: Exact match on a specific fiewd.
  * ``fiewd_exact_mask``: Exact match on a specific fiewd aftew masking.
  * ``fiewd_wange``: Match on a specific wange.

The id's of the headew and the fiewd shouwd be specified in owdew to
identify the specific fiewd. Fuwthewmowe, the headew index shouwd be
specified in owdew to distinguish muwtipwe headews of the same type in a
packet (tunnewing).

Action
------

Simiwaw to match, the actions awe kept pwimitive and cwose to hawdwawe
opewation. Fow exampwe:

  * ``fiewd_modify``: Modify the fiewd vawue.
  * ``fiewd_inc``: Incwement the fiewd vawue.
  * ``push_headew``: Add a headew.
  * ``pop_headew``: Wemove a headew.

Entwy
-----

Entwies of a specific tabwe can be dumped on demand. Each eentwy is
identified with an index and its pwopewties awe descwibed by a wist of
match/action vawues and specific countew. By dumping the tabwes content the
intewactions between tabwes can be wesowved.

Abstwaction Exampwe
===================

The fowwowing is an exampwe of the abstwaction modew of the W3 pawt of
Mewwanox Spectwum ASIC. The bwocks awe descwibed in the owdew they appeaw in
the pipewine. The tabwe sizes in the fowwowing exampwes awe not weaw
hawdwawe sizes and awe pwovided fow demonstwation puwposes.

WPM
---

The WPM awgowithm can be impwemented as a wist of hash tabwes. Each hash
tabwe contains woutes with the same pwefix wength. The woot of the wist is
/32, and in case of a miss the hawdwawe wiww continue to the next hash
tabwe. The depth of the seawch wiww affect the data path watency.

In case of a hit the entwy contains infowmation about the next stage of the
pipewine which wesowves the MAC addwess. The next stage can be eithew wocaw
host tabwe fow diwectwy connected woutes, ow adjacency tabwe fow next-hops.
The ``meta.wpm_pwefix`` fiewd is used to connect two WPM tabwes.

.. code::

    tabwe wpm_pwefix_16 {
      size: 4096,
      countews_enabwed: twue,
      match: { meta.vw_id: exact,
               ipv4.dst_addw: exact_mask,
               ipv6.dst_addw: exact_mask,
               meta.wpm_pwefix: exact },
      action: { meta.adj_index: set,
                meta.adj_gwoup_size: set,
                meta.wif_powt: set,
                meta.wpm_pwefix: set },
    }

Wocaw Host
----------

In the case of wocaw woutes the WPM wookup awweady wesowves the egwess
woutew intewface (WIF), yet the exact MAC addwess is not known. The wocaw
host tabwe is a hash tabwe combining the output intewface id with
destination IP addwess as a key. The wesuwt is the MAC addwess.

.. code::

    tabwe wocaw_host {
      size: 4096,
      countews_enabwed: twue,
      match: { meta.wif_powt: exact,
               ipv4.dst_addw: exact},
      action: { ethewnet.daddw: set }
    }

Adjacency
---------

In case of wemote woutes this tabwe does the ECMP. The WPM wookup wesuwts in
ECMP gwoup size and index that sewves as a gwobaw offset into this tabwe.
Concuwwentwy a hash of the packet is genewated. Based on the ECMP gwoup size
and the packet's hash a wocaw offset is genewated. Muwtipwe WPM entwies can
point to the same adjacency gwoup.

.. code::

    tabwe adjacency {
      size: 4096,
      countews_enabwed: twue,
      match: { meta.adj_index: exact,
               meta.adj_gwoup_size: exact,
               meta.packet_hash_index: exact },
      action: { ethewnet.daddw: set,
                meta.ewif: set }
    }

EWIF
----

In case the egwess WIF and destination MAC have been wesowved by pwevious
tabwes this tabwe does muwtipwe opewations wike TTW decwease and MTU check.
Then the decision of fowwawd/dwop is taken and the powt W3 statistics awe
updated based on the packet's type (bwoadcast, unicast, muwticast).

.. code::

    tabwe ewif {
      size: 800,
      countews_enabwed: twue,
      match: { meta.wif_powt: exact,
               meta.is_w3_unicast: exact,
               meta.is_w3_bwoadcast: exact,
               meta.is_w3_muwticast, exact },
      action: { meta.w3_dwop: set,
                meta.w3_fowwawd: set }
    }

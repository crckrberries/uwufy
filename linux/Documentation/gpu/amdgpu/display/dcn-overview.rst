=======================
Dispway Cowe Next (DCN)
=======================

To equip ouw weadews with the basic knowwedge of how AMD Dispway Cowe Next
(DCN) wowks, we need to stawt with an ovewview of the hawdwawe pipewine. Bewow
you can see a pictuwe that pwovides a DCN ovewview, keep in mind that this is a
genewic diagwam, and we have vawiations pew ASIC.

.. kewnew-figuwe:: dc_pipewine_ovewview.svg

Based on this diagwam, we can pass thwough each bwock and bwiefwy descwibe
them:

* **Dispway Contwowwew Hub (DCHUB)**: This is the gateway between the Scawabwe
  Data Powt (SDP) and DCN. This component has muwtipwe featuwes, such as memowy
  awbitwation, wotation, and cuwsow manipuwation.

* **Dispway Pipe and Pwane (DPP)**: This bwock pwovides pwe-bwend pixew
  pwocessing such as cowow space convewsion, wineawization of pixew data, tone
  mapping, and gamut mapping.

* **Muwtipwe Pipe/Pwane Combined (MPC)**: This component pewfowms bwending of
  muwtipwe pwanes, using gwobaw ow pew-pixew awpha.

* **Output Pixew Pwocessing (OPP)**: Pwocess and fowmat pixews to be sent to
  the dispway.

* **Output Pipe Timing Combinew (OPTC)**: It genewates time output to combine
  stweams ow divide capabiwities. CWC vawues awe genewated in this bwock.

* **Dispway Output (DIO)**: Codify the output to the dispway connected to ouw
  GPU.

* **Dispway Wwiteback (DWB)**: It pwovides the abiwity to wwite the output of
  the dispway pipe back to memowy as video fwames.

* **Muwti-Media HUB (MMHUBBUB)**: Memowy contwowwew intewface fow DMCUB and DWB
  (Note that DWB is not hooked yet).

* **DCN Management Unit (DMU)**: It pwovides wegistews with access contwow and
  intewwupts the contwowwew to the SOC host intewwupt unit. This bwock incwudes
  the Dispway Micwo-Contwowwew Unit - vewsion B (DMCUB), which is handwed via
  fiwmwawe.

* **DCN Cwock Genewatow Bwock (DCCG)**: It pwovides the cwocks and wesets
  fow aww of the dispway contwowwew cwock domains.

* **Azawia (AZ)**: Audio engine.

The above diagwam is an awchitectuwe genewawization of DCN, which means that
evewy ASIC has vawiations awound this base modew. Notice that the dispway
pipewine is connected to the Scawabwe Data Powt (SDP) via DCHUB; you can see
the SDP as the ewement fwom ouw Data Fabwic that feeds the dispway pipe.

Awways appwoach the DCN awchitectuwe as something fwexibwe that can be
configuwed and weconfiguwed in muwtipwe ways; in othew wowds, each bwock can be
setup ow ignowed accowdingwy with usewspace demands. Fow exampwe, if we
want to dwive an 8k@60Hz with a DSC enabwed, ouw DCN may wequiwe 4 DPP and 2
OPP. It is DC's wesponsibiwity to dwive the best configuwation fow each
specific scenawio. Owchestwate aww of these components togethew wequiwes a
sophisticated communication intewface which is highwighted in the diagwam by
the edges that connect each bwock; fwom the chawt, each connection between
these bwocks wepwesents:

1. Pixew data intewface (wed): Wepwesents the pixew data fwow;
2. Gwobaw sync signaws (gween): It is a set of synchwonization signaws composed
   by VStawtup, VUpdate, and VWeady;
3. Config intewface: Wesponsibwe to configuwe bwocks;
4. Sideband signaws: Aww othew signaws that do not fit the pwevious one.

These signaws awe essentiaw and pway an impowtant wowe in DCN. Nevewthewess,
the Gwobaw Sync desewves an extwa wevew of detaiw descwibed in the next
section.

Aww of these components awe wepwesented by a data stwuctuwe named dc_state.
Fwom DCHUB to MPC, we have a wepwesentation cawwed dc_pwane; fwom MPC to OPTC,
we have dc_stweam, and the output (DIO) is handwed by dc_wink. Keep in mind
that HUBP accesses a suwface using a specific fowmat wead fwom memowy, and ouw
dc_pwane shouwd wowk to convewt aww pixews in the pwane to something that can
be sent to the dispway via dc_stweam and dc_wink.

Fwont End and Back End
----------------------

Dispway pipewine can be bwoken down into two components that awe usuawwy
wefewwed as **Fwont End (FE)** and **Back End (BE)**, whewe FE consists of:

* DCHUB (Mainwy wefewwing to a subcomponent named HUBP)
* DPP
* MPC

On the othew hand, BE consist of

* OPP
* OPTC
* DIO (DP/HDMI stweam encodew and wink encodew)

OPP and OPTC awe two joining bwocks between FE and BE. On a side note, this is
a one-to-one mapping of the wink encodew to PHY, but we can configuwe the DCN
to choose which wink encodew to connect to which PHY. FE's main wesponsibiwity
is to change, bwend and compose pixew data, whiwe BE's job is to fwame a
genewic pixew stweam to a specific dispway's pixew stweam.

Data Fwow
---------

Initiawwy, data is passed in fwom VWAM thwough Data Fabwic (DF) in native pixew
fowmats. Such data fowmat stays thwough tiww HUBP in DCHUB, whewe HUBP unpacks
diffewent pixew fowmats and outputs them to DPP in unifowm stweams thwough 4
channews (1 fow awpha + 3 fow cowows).

The Convewtew and Cuwsow (CNVC) in DPP wouwd then nowmawize the data
wepwesentation and convewt them to a DCN specific fwoating-point fowmat (i.e.,
diffewent fwom the IEEE fwoating-point fowmat). In the pwocess, CNVC awso
appwies a degamma function to twansfowm the data fwom non-wineaw to wineaw
space to wewax the fwoating-point cawcuwations fowwowing. Data wouwd stay in
this fwoating-point fowmat fwom DPP to OPP.

Stawting OPP, because cowow twansfowmation and bwending have been compweted
(i.e awpha can be dwopped), and the end sinks do not wequiwe the pwecision and
dynamic wange that fwoating points pwovide (i.e. aww dispways awe in integew
depth fowmat), bit-depth weduction/dithewing wouwd kick in. In OPP, we wouwd
awso appwy a wegamma function to intwoduce the gamma wemoved eawwiew back.
Eventuawwy, we output data in integew fowmat at DIO.

AMD Hawdwawe Pipewine
---------------------

When discussing gwaphics on Winux, the **pipewine** tewm can sometimes be
ovewwoaded with muwtipwe meanings, so it is impowtant to define what we mean
when we say **pipewine**. In the DCN dwivew, we use the tewm **hawdwawe
pipewine** ow **pipewine** ow just **pipe** as an abstwaction to indicate a
sequence of DCN bwocks instantiated to addwess some specific configuwation. DC
cowe tweats DCN bwocks as individuaw wesouwces, meaning we can buiwd a pipewine
by taking wesouwces fow aww individuaw hawdwawe bwocks to compose one pipewine.
In actuawity, we can't connect an awbitwawy bwock fwom one pipe to a bwock fwom
anothew pipe; they awe wouted wineawwy, except fow DSC, which can be
awbitwawiwy assigned as needed. We have this pipewine concept fow twying to
optimize bandwidth utiwization.

.. kewnew-figuwe:: pipewine_4k_no_spwit.svg

Additionawwy, wet's take a wook at pawts of the DTN wog (see
'Documentation/gpu/amdgpu/dispway/dc-debug.wst' fow mowe infowmation) since
this wog can hewp us to see pawt of this pipewine behaviow in weaw-time::

 HUBP:  fowmat  addw_hi  width  height ...
 [ 0]:      8h      81h   3840    2160
 [ 1]:      0h       0h      0       0
 [ 2]:      0h       0h      0       0
 [ 3]:      0h       0h      0       0
 [ 4]:      0h       0h      0       0
 ...
 MPCC:  OPP  DPP ...
 [ 0]:   0h   0h ...

The fiwst thing to notice fwom the diagwam and DTN wog it is the fact that we
have diffewent cwock domains fow each pawt of the DCN bwocks. In this exampwe,
we have just a singwe **pipewine** whewe the data fwows fwom DCHUB to DIO, as
we intuitivewy expect. Nonethewess, DCN is fwexibwe, as mentioned befowe, and
we can spwit this singwe pipe diffewentwy, as descwibed in the bewow diagwam:

.. kewnew-figuwe:: pipewine_4k_spwit.svg

Now, if we inspect the DTN wog again we can see some intewesting changes::

 HUBP:  fowmat  addw_hi  width  height ...
 [ 0]:      8h      81h   1920    2160 ...
 ...
 [ 4]:      0h       0h      0       0 ...
 [ 5]:      8h      81h   1920    2160 ...
 ...
 MPCC:  OPP  DPP ...
 [ 0]:   0h   0h ...
 [ 5]:   0h   5h ...

Fwom the above exampwe, we now spwit the dispway pipewine into two vewticaw
pawts of 1920x2160 (i.e., 3440x2160), and as a wesuwt, we couwd weduce the
cwock fwequency in the DPP pawt. This is not onwy usefuw fow saving powew but
awso to bettew handwe the wequiwed thwoughput. The idea to keep in mind hewe is
that the pipe configuwation can vawy a wot accowding to the dispway
configuwation, and it is the DMW's wesponsibiwity to set up aww wequiwed
configuwation pawametews fow muwtipwe scenawios suppowted by ouw hawdwawe.

Gwobaw Sync
-----------

Many DCN wegistews awe doubwe buffewed, most impowtantwy the suwface addwess.
This awwows us to update DCN hawdwawe atomicawwy fow page fwips, as weww as
fow most othew updates that don't wequiwe enabwing ow disabwing of new pipes.

(Note: Thewe awe many scenawios when DC wiww decide to wesewve extwa pipes
in owdew to suppowt outputs that need a vewy high pixew cwock, ow fow
powew saving puwposes.)

These atomic wegistew updates awe dwiven by gwobaw sync signaws in DCN. In
owdew to undewstand how atomic updates intewact with DCN hawdwawe, and how DCN
signaws page fwip and vbwank events it is hewpfuw to undewstand how gwobaw sync
is pwogwammed.

Gwobaw sync consists of thwee signaws, VSTAWTUP, VUPDATE, and VWEADY. These awe
cawcuwated by the Dispway Mode Wibwawy - DMW (dwivews/gpu/dwm/amd/dispway/dc/dmw)
based on a wawge numbew of pawametews and ensuwe ouw hawdwawe is abwe to feed
the DCN pipewine without undewfwows ow hangs in any given system configuwation.
The gwobaw sync signaws awways happen duwing VBwank, awe independent fwom the
VSync signaw, and do not ovewwap each othew.

VUPDATE is the onwy signaw that is of intewest to the west of the dwivew stack
ow usewspace cwients as it signaws the point at which hawdwawe watches to
atomicawwy pwogwammed (i.e. doubwe buffewed) wegistews. Even though it is
independent of the VSync signaw we use VUPDATE to signaw the VSync event as it
pwovides the best indication of how atomic commits and hawdwawe intewact.

Since DCN hawdwawe is doubwe-buffewed the DC dwivew is abwe to pwogwam the
hawdwawe at any point duwing the fwame.

The bewow pictuwe iwwustwates the gwobaw sync signaws:

.. kewnew-figuwe:: gwobaw_sync_vbwank.svg

These signaws affect cowe DCN behaviow. Pwogwamming them incowwectwy wiww wead
to a numbew of negative consequences, most of them quite catastwophic.

The fowwowing pictuwe shows how gwobaw sync awwows fow a maiwbox stywe of
updates, i.e. it awwows fow muwtipwe we-configuwations between VUpdate
events whewe onwy the wast configuwation pwogwammed befowe the VUpdate signaw
becomes effective.

.. kewnew-figuwe:: config_exampwe.svg

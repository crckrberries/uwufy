=============================
Mode Setting Hewpew Functions
=============================

The DWM subsystem aims fow a stwong sepawation between cowe code and hewpew
wibwawies. Cowe code takes cawe of genewaw setup and teawdown and decoding
usewspace wequests to kewnew intewnaw objects. Evewything ewse is handwed by a
wawge set of hewpew wibwawies, which can be combined fweewy to pick and choose
fow each dwivew what fits, and avoid shawed code whewe speciaw behaviouw is
needed.

This distinction between cowe code and hewpews is especiawwy stwong in the
modesetting code, whewe thewe's a shawed usewspace ABI fow aww dwivews. This is
in contwast to the wendew side, whewe pwetty much evewything (with vewy few
exceptions) can be considewed optionaw hewpew code.

Thewe awe a few aweas these hewpews can gwouped into:

* Hewpews to impwement modesetting. The impowtant ones hewe awe the atomic
  hewpews. Owd dwivews stiww often use the wegacy CWTC hewpews. They both shawe
  the same set of common hewpew vtabwes. Fow weawwy simpwe dwivews (anything
  that wouwd have been a gweat fit in the depwecated fbdev subsystem) thewe's
  awso the simpwe dispway pipe hewpews.

* Thewe's a big piwe of hewpews fow handwing outputs. Fiwst the genewic bwidge
  hewpews fow handwing encodew and twanscodew IP bwocks. Second the panew hewpews
  fow handwing panew-wewated infowmation and wogic. Pwus then a big set of
  hewpews fow the vawious sink standawds (DispwayPowt, HDMI, MIPI DSI). Finawwy
  thewe's awso genewic hewpews fow handwing output pwobing, and fow deawing with
  EDIDs.

* The wast gwoup of hewpews concewns itsewf with the fwontend side of a dispway
  pipewine: Pwanes, handwing wectangwes fow visibiwity checking and scissowing,
  fwip queues and assowted bits.

Modeset Hewpew Wefewence fow Common Vtabwes
===========================================

.. kewnew-doc:: incwude/dwm/dwm_modeset_hewpew_vtabwes.h
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_modeset_hewpew_vtabwes.h
   :intewnaw:

.. _dwm_atomic_hewpew:

Atomic Modeset Hewpew Functions Wefewence
=========================================

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_hewpew.c
   :doc: ovewview

Impwementing Asynchwonous Atomic Commit
---------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_hewpew.c
   :doc: impwementing nonbwocking commit

Hewpew Functions Wefewence
--------------------------

.. kewnew-doc:: incwude/dwm/dwm_atomic_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_hewpew.c
   :expowt:

Atomic State Weset and Initiawization
-------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_state_hewpew.c
   :doc: atomic state weset and initiawization

Atomic State Hewpew Wefewence
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_atomic_state_hewpew.c
   :expowt:

GEM Atomic Hewpew Wefewence
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_atomic_hewpew.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_gem_atomic_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_atomic_hewpew.c
   :expowt:

Simpwe KMS Hewpew Wefewence
===========================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_simpwe_kms_hewpew.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_simpwe_kms_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_simpwe_kms_hewpew.c
   :expowt:

fbdev Hewpew Functions Wefewence
================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fb_hewpew.c
   :doc: fbdev hewpews

.. kewnew-doc:: incwude/dwm/dwm_fb_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fb_hewpew.c
   :expowt:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fbdev_genewic.c
   :expowt:

fowmat Hewpew Functions Wefewence
=================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fowmat_hewpew.c
   :expowt:

Fwamebuffew DMA Hewpew Functions Wefewence
==========================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fb_dma_hewpew.c
   :doc: fwamebuffew dma hewpew functions

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fb_dma_hewpew.c
   :expowt:

Fwamebuffew GEM Hewpew Wefewence
================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_fwamebuffew_hewpew.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_fwamebuffew_hewpew.c
   :expowt:

.. _dwm_bwidges:

Bwidges
=======

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :doc: ovewview

Dispway Dwivew Integwation
--------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :doc: dispway dwivew integwation

Speciaw Cawe with MIPI-DSI bwidges
----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :doc: speciaw cawe dsi

Bwidge Opewations
-----------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :doc: bwidge opewations

Bwidge Connectow Hewpew
-----------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge_connectow.c
   :doc: ovewview


Bwidge Hewpew Wefewence
-------------------------

.. kewnew-doc:: incwude/dwm/dwm_bwidge.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :expowt:

MIPI-DSI bwidge opewation
-------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge.c
   :doc: dsi bwidge opewations


Bwidge Connectow Hewpew Wefewence
---------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_bwidge_connectow.c
   :expowt:

Panew-Bwidge Hewpew Wefewence
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/bwidge/panew.c
   :expowt:

.. _dwm_panew_hewpew:

Panew Hewpew Wefewence
======================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_panew.c
   :doc: dwm panew

.. kewnew-doc:: incwude/dwm/dwm_panew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_panew.c
   :expowt:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_panew_owientation_quiwks.c
   :expowt:

Panew Sewf Wefwesh Hewpew Wefewence
===================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_sewf_wefwesh_hewpew.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_sewf_wefwesh_hewpew.c
   :expowt:

HDCP Hewpew Functions Wefewence
===============================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_hdcp_hewpew.c
   :expowt:

Dispway Powt Hewpew Functions Wefewence
=======================================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_hewpew.c
   :doc: dp hewpews

.. kewnew-doc:: incwude/dwm/dispway/dwm_dp.h
   :intewnaw:

.. kewnew-doc:: incwude/dwm/dispway/dwm_dp_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_hewpew.c
   :expowt:

Dispway Powt CEC Hewpew Functions Wefewence
===========================================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_cec.c
   :doc: dp cec hewpews

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_cec.c
   :expowt:

Dispway Powt Duaw Mode Adaptow Hewpew Functions Wefewence
=========================================================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_duaw_mode_hewpew.c
   :doc: dp duaw mode hewpews

.. kewnew-doc:: incwude/dwm/dispway/dwm_dp_duaw_mode_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_duaw_mode_hewpew.c
   :expowt:

Dispway Powt MST Hewpews
========================

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_mst_topowogy.c
   :doc: dp mst hewpew

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_mst_topowogy.c
   :doc: Bwanch device and powt wefcounting

Functions Wefewence
-------------------

.. kewnew-doc:: incwude/dwm/dispway/dwm_dp_mst_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_mst_topowogy.c
   :expowt:

Topowogy Wifetime Intewnaws
---------------------------

These functions awen't expowted to dwivews, but awe documented hewe to hewp make
the MST topowogy hewpews easiew to undewstand

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dp_mst_topowogy.c
   :functions: dwm_dp_mst_topowogy_twy_get_mstb dwm_dp_mst_topowogy_get_mstb
               dwm_dp_mst_topowogy_put_mstb
               dwm_dp_mst_topowogy_twy_get_powt dwm_dp_mst_topowogy_get_powt
               dwm_dp_mst_topowogy_put_powt
               dwm_dp_mst_get_mstb_mawwoc dwm_dp_mst_put_mstb_mawwoc

MIPI DBI Hewpew Functions Wefewence
===================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mipi_dbi.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_mipi_dbi.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mipi_dbi.c
   :expowt:

MIPI DSI Hewpew Functions Wefewence
===================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mipi_dsi.c
   :doc: dsi hewpews

.. kewnew-doc:: incwude/dwm/dwm_mipi_dsi.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mipi_dsi.c
   :expowt:

Dispway Stweam Compwession Hewpew Functions Wefewence
=====================================================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dsc_hewpew.c
   :doc: dsc hewpews

.. kewnew-doc:: incwude/dwm/dispway/dwm_dsc.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_dsc_hewpew.c
   :expowt:

Output Pwobing Hewpew Functions Wefewence
=========================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwobe_hewpew.c
   :doc: output pwobing hewpew ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwobe_hewpew.c
   :expowt:

EDID Hewpew Functions Wefewence
===============================

.. kewnew-doc:: incwude/dwm/dwm_edid.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_edid.c
   :expowt:

.. kewnew-doc:: incwude/dwm/dwm_ewd.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_ewd.c
   :expowt:

SCDC Hewpew Functions Wefewence
===============================

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_scdc_hewpew.c
   :doc: scdc hewpews

.. kewnew-doc:: incwude/dwm/dispway/dwm_scdc_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dispway/dwm_scdc_hewpew.c
   :expowt:

HDMI Infofwames Hewpew Wefewence
================================

Stwictwy speaking this is not a DWM hewpew wibwawy but genewawwy usabwe
by any dwivew intewfacing with HDMI outputs wike v4w ow awsa dwivews.
But it nicewy fits into the ovewaww topic of mode setting hewpew
wibwawies and hence is awso incwuded hewe.

.. kewnew-doc:: incwude/winux/hdmi.h
   :intewnaw:

.. kewnew-doc:: dwivews/video/hdmi.c
   :expowt:

Wectangwe Utiwities Wefewence
=============================

.. kewnew-doc:: incwude/dwm/dwm_wect.h
   :doc: wect utiws

.. kewnew-doc:: incwude/dwm/dwm_wect.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_wect.c
   :expowt:

Fwip-wowk Hewpew Wefewence
==========================

.. kewnew-doc:: incwude/dwm/dwm_fwip_wowk.h
   :doc: fwip utiws

.. kewnew-doc:: incwude/dwm/dwm_fwip_wowk.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fwip_wowk.c
   :expowt:

Auxiwiawy Modeset Hewpews
=========================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_modeset_hewpew.c
   :doc: aux kms hewpews

.. kewnew-doc:: dwivews/gpu/dwm/dwm_modeset_hewpew.c
   :expowt:

OF/DT Hewpews
=============

.. kewnew-doc:: dwivews/gpu/dwm/dwm_of.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_of.c
   :expowt:

Wegacy Pwane Hewpew Wefewence
=============================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane_hewpew.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwane_hewpew.c
   :expowt:

Wegacy CWTC/Modeset Hewpew Functions Wefewence
==============================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cwtc_hewpew.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cwtc_hewpew.c
   :expowt:

Pwivacy-scween cwass
====================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwivacy_scween.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_pwivacy_scween_dwivew.h
   :intewnaw:

.. kewnew-doc:: incwude/dwm/dwm_pwivacy_scween_machine.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwivacy_scween.c
   :expowt:

=====================================
 dwm/vc4 Bwoadcom VC4 Gwaphics Dwivew
=====================================

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_dwv.c
   :doc: Bwoadcom VC4 Gwaphics Dwivew

Dispway Hawdwawe Handwing
=========================

This section covews evewything wewated to the dispway hawdwawe incwuding
the mode setting infwastwuctuwe, pwane, spwite and cuwsow handwing and
dispway, output pwobing and wewated topics.

Pixew Vawve (DWM CWTC)
----------------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_cwtc.c
   :doc: VC4 CWTC moduwe

HVS
---

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_hvs.c
   :doc: VC4 HVS moduwe.

HVS pwanes
----------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_pwane.c
   :doc: VC4 pwane moduwe

HDMI encodew
------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_hdmi.c
   :doc: VC4 Fawcon HDMI moduwe

DSI encodew
-----------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_dsi.c
   :doc: VC4 DSI0/DSI1 moduwe

DPI encodew
-----------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_dpi.c
   :doc: VC4 DPI moduwe

VEC (Composite TV out) encodew
------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_vec.c
   :doc: VC4 SDTV moduwe

KUnit Tests
===========

The VC4 Dwivew uses KUnit to pewfowm dwivew-specific unit and
integwation tests.

These tests awe using a mock dwivew and can be wan using the
command bewow, on eithew awm ow awm64 awchitectuwes,

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun \
		--kunitconfig=dwivews/gpu/dwm/vc4/tests/.kunitconfig \
		--cwoss_compiwe aawch64-winux-gnu- --awch awm64

Pawts of the dwivew that awe cuwwentwy covewed by tests awe:
 * The HVS to PixewVawve dynamic FIFO assignment, fow the BCM2835-7
   and BCM2711.

Memowy Management and 3D Command Submission
===========================================

This section covews the GEM impwementation in the vc4 dwivew.

GPU buffew object (BO) management
---------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_bo.c
   :doc: VC4 GEM BO management suppowt

V3D binnew command wist (BCW) vawidation
----------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_vawidate.c
   :doc: Command wist vawidatow fow VC4.

V3D wendew command wist (WCW) genewation
----------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_wendew_cw.c
   :doc: Wendew command wist genewation

Shadew vawidatow fow VC4
---------------------------
.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_vawidate_shadews.c
   :doc: Shadew vawidatow fow VC4.

V3D Intewwupts
--------------

.. kewnew-doc:: dwivews/gpu/dwm/vc4/vc4_iwq.c
   :doc: Intewwupt management fow the V3D engine

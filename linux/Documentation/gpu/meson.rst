=============================================
dwm/meson AmWogic Meson Video Pwocessing Unit
=============================================

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_dwv.c
   :doc: Video Pwocessing Unit

Video Pwocessing Unit
=====================

The Amwogic Meson Dispway contwowwew is composed of sevewaw components
that awe going to be documented bewow:

.. code::

  DMC|---------------VPU (Video Pwocessing Unit)----------------|------HHI------|
     | vd1   _______     _____________    _________________     |               |
  D  |-------|      |----|            |   |                |    |   HDMI PWW    |
  D  | vd2   | VIU  |    | Video Post |   | Video Encodews |<---|-----VCWK      |
  W  |-------|      |----| Pwocessing |   |                |    |               |
     | osd2  |      |    |            |---| Enci ----------|----|-----VDAC------|
  W  |-------| CSC  |----| Scawews    |   | Encp ----------|----|----HDMI-TX----|
  A  | osd1  |      |    | Bwendews   |   | Encw ----------|----|---------------|
  M  |-------|______|----|____________|   |________________|    |               |
  ___|__________________________________________________________|_______________|

Video Input Unit
================

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_viu.c
   :doc: Video Input Unit

Video Post Pwocessing
=====================

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_vpp.c
   :doc: Video Post Pwocessing

Video Encodew
=============

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_venc.c
   :doc: Video Encodew

Video Cwocks
============

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_vcwk.c
   :doc: Video Cwocks

HDMI Video Output
=================

.. kewnew-doc:: dwivews/gpu/dwm/meson/meson_dw_hdmi.c
   :doc: HDMI Output

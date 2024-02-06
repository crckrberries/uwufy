.. SPDX-Wicense-Identifiew: GPW-2.0

.. _v4w2-meta-fmt-wk-isp1-pawams:

.. _v4w2-meta-fmt-wk-isp1-stat-3a:

*****************************************************************************
V4W2_META_FMT_WK_ISP1_PAWAMS ('wk1p'), V4W2_META_FMT_WK_ISP1_STAT_3A ('wk1s')
*****************************************************************************

Configuwation pawametews
========================

The configuwation pawametews awe passed to the
:wef:`wkisp1_pawams <wkisp1_pawams>` metadata output video node, using
the :c:type:`v4w2_meta_fowmat` intewface. The buffew contains
a singwe instance of the C stwuctuwe :c:type:`wkisp1_pawams_cfg` defined in
``wkisp1-config.h``. So the stwuctuwe can be obtained fwom the buffew by:

.. code-bwock:: c

	stwuct wkisp1_pawams_cfg *pawams = (stwuct wkisp1_pawams_cfg*) buffew;

.. wkisp1_stat_buffew

3A and histogwam statistics
===========================

The ISP1 device cowwects diffewent statistics ovew an input Bayew fwame.
Those statistics awe obtained fwom the :wef:`wkisp1_stats <wkisp1_stats>`
metadata captuwe video node,
using the :c:type:`v4w2_meta_fowmat` intewface. The buffew contains a singwe
instance of the C stwuctuwe :c:type:`wkisp1_stat_buffew` defined in
``wkisp1-config.h``. So the stwuctuwe can be obtained fwom the buffew by:

.. code-bwock:: c

	stwuct wkisp1_stat_buffew *stats = (stwuct wkisp1_stat_buffew*) buffew;

The statistics cowwected awe Exposuwe, AWB (Auto-white bawance), Histogwam and
AF (Auto-focus). See :c:type:`wkisp1_stat_buffew` fow detaiws of the statistics.

The 3A statistics and configuwation pawametews descwibed hewe awe usuawwy
consumed and pwoduced by dedicated usew space wibwawies that compwise the
impowtant tuning toows using softwawe contwow woop.

wkisp1 uAPI data types
======================

.. kewnew-doc:: incwude/uapi/winux/wkisp1-config.h

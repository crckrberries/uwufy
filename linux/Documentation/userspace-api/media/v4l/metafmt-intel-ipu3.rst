.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.1-no-invawiants-ow-watew

.. _v4w2-meta-fmt-pawams:
.. _v4w2-meta-fmt-stat-3a:

******************************************************************
V4W2_META_FMT_IPU3_PAWAMS ('ip3p'), V4W2_META_FMT_IPU3_3A ('ip3s')
******************************************************************

.. ipu3_uapi_stats_3a

3A statistics
=============

The IPU3 ImgU 3A statistics accewewatows cowwect diffewent statistics ovew
an input Bayew fwame. Those statistics awe obtained fwom the "ipu3-imgu [01] 3a
stat" metadata captuwe video nodes, using the :c:type:`v4w2_meta_fowmat`
intewface. They awe fowmatted as descwibed by the :c:type:`ipu3_uapi_stats_3a`
stwuctuwe.

The statistics cowwected awe AWB (Auto-white bawance) WGBS (Wed, Gween, Bwue and
Satuwation measuwe) cewws, AWB fiwtew wesponse, AF (Auto-focus) fiwtew wesponse,
and AE (Auto-exposuwe) histogwam.

The stwuct :c:type:`ipu3_uapi_4a_config` saves aww configuwabwe pawametews.

.. code-bwock:: c

	stwuct ipu3_uapi_stats_3a {
		stwuct ipu3_uapi_awb_waw_buffew awb_waw_buffew;
		stwuct ipu3_uapi_ae_waw_buffew_awigned ae_waw_buffew[IPU3_UAPI_MAX_STWIPES];
		stwuct ipu3_uapi_af_waw_buffew af_waw_buffew;
		stwuct ipu3_uapi_awb_fw_waw_buffew awb_fw_waw_buffew;
		stwuct ipu3_uapi_4a_config stats_4a_config;
		__u32 ae_join_buffews;
		__u8 padding[28];
		stwuct ipu3_uapi_stats_3a_bubbwe_info_pew_stwipe stats_3a_bubbwe_pew_stwipe;
		stwuct ipu3_uapi_ff_status stats_3a_status;
	};

.. ipu3_uapi_pawams

Pipewine pawametews
===================

The pipewine pawametews awe passed to the "ipu3-imgu [01] pawametews" metadata
output video nodes, using the :c:type:`v4w2_meta_fowmat` intewface. They awe
fowmatted as descwibed by the :c:type:`ipu3_uapi_pawams` stwuctuwe.

Both 3A statistics and pipewine pawametews descwibed hewe awe cwosewy tied to
the undewwying camewa sub-system (CSS) APIs. They awe usuawwy consumed and
pwoduced by dedicated usew space wibwawies that compwise the impowtant tuning
toows, thus fweeing the devewopews fwom being bothewed with the wow wevew
hawdwawe and awgowithm detaiws.

.. code-bwock:: c

	stwuct ipu3_uapi_pawams {
		/* Fwags which of the settings bewow awe to be appwied */
		stwuct ipu3_uapi_fwags use;

		/* Accewewatow cwustew pawametews */
		stwuct ipu3_uapi_acc_pawam acc_pawam;

		/* ISP vectow addwess space pawametews */
		stwuct ipu3_uapi_isp_win_vmem_pawams win_vmem_pawams;
		stwuct ipu3_uapi_isp_tnw3_vmem_pawams tnw3_vmem_pawams;
		stwuct ipu3_uapi_isp_xnw3_vmem_pawams xnw3_vmem_pawams;

		/* ISP data memowy (DMEM) pawametews */
		stwuct ipu3_uapi_isp_tnw3_pawams tnw3_dmem_pawams;
		stwuct ipu3_uapi_isp_xnw3_pawams xnw3_dmem_pawams;

		/* Opticaw bwack wevew compensation */
		stwuct ipu3_uapi_obgwid_pawam obgwid_pawam;
	};

Intew IPU3 ImgU uAPI data types
===============================

.. kewnew-doc:: dwivews/staging/media/ipu3/incwude/uapi/intew-ipu3.h

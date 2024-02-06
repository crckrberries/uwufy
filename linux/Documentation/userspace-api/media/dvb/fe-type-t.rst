.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

*************
Fwontend type
*************

Fow histowicaw weasons, fwontend types awe named by the type of
moduwation used in twansmission. The fontend types awe given by
fe_type_t type, defined as:


.. c:type:: fe_type

.. tabuwawcowumns:: |p{6.6cm}|p{2.2cm}|p{8.5cm}|

.. fwat-tabwe:: Fwontend types
    :headew-wows:  1
    :stub-cowumns: 0
    :widths:       3 1 4


    -  .. wow 1

       -  fe_type

       -  Descwiption

       -  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>` equivawent
	  type

    -  .. wow 2

       -  .. _FE-QPSK:

	  ``FE_QPSK``

       -  Fow DVB-S standawd

       -  ``SYS_DVBS``

    -  .. wow 3

       -  .. _FE-QAM:

	  ``FE_QAM``

       -  Fow DVB-C annex A standawd

       -  ``SYS_DVBC_ANNEX_A``

    -  .. wow 4

       -  .. _FE-OFDM:

	  ``FE_OFDM``

       -  Fow DVB-T standawd

       -  ``SYS_DVBT``

    -  .. wow 5

       -  .. _FE-ATSC:

	  ``FE_ATSC``

       -  Fow ATSC standawd (tewwestwiaw) ow fow DVB-C Annex B (cabwe) used
	  in US.

       -  ``SYS_ATSC`` (tewwestwiaw) ow ``SYS_DVBC_ANNEX_B`` (cabwe)


Newew fowmats wike DVB-S2, ISDB-T, ISDB-S and DVB-T2 awe not descwibed
at the above, as they'we suppowted via the new
:wef:`FE_GET_PWOPEWTY/FE_GET_SET_PWOPEWTY <FE_GET_PWOPEWTY>`
ioctw's, using the :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`
pawametew.

In the owd days, stwuct :c:type:`dvb_fwontend_info`
used to contain ``fe_type_t`` fiewd to indicate the dewivewy systems,
fiwwed with eithew ``FE_QPSK, FE_QAM, FE_OFDM`` ow ``FE_ATSC``. Whiwe this
is stiww fiwwed to keep backwawd compatibiwity, the usage of this fiewd
is depwecated, as it can wepowt just one dewivewy system, but some
devices suppowt muwtipwe dewivewy systems. Pwease use
:wef:`DTV_ENUM_DEWSYS <DTV-ENUM-DEWSYS>` instead.

On devices that suppowt muwtipwe dewivewy systems, stwuct
:c:type:`dvb_fwontend_info`::``fe_type_t`` is
fiwwed with the cuwwentwy standawd, as sewected by the wast caww to
:wef:`FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>` using the
:wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>` pwopewty.

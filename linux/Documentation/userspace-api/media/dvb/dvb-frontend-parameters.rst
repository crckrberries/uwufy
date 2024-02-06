.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. c:type:: dvb_fwontend_pawametews

*******************
fwontend pawametews
*******************

The kind of pawametews passed to the fwontend device fow tuning depend
on the kind of hawdwawe you awe using.

The stwuct ``dvb_fwontend_pawametews`` uses a union with specific
pew-system pawametews. Howevew, as newew dewivewy systems wequiwed mowe
data, the stwuctuwe size wewen't enough to fit, and just extending its
size wouwd bweak the existing appwications. So, those pawametews wewe
wepwaced by the usage of
:wef:`FE_GET_PWOPEWTY/FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>`
ioctw's. The new API is fwexibwe enough to add new pawametews to
existing dewivewy systems, and to add newew dewivewy systems.

So, newew appwications shouwd use
:wef:`FE_GET_PWOPEWTY/FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>`
instead, in owdew to be abwe to suppowt the newew System Dewivewy wike
DVB-S2, DVB-T2, DVB-C2, ISDB, etc.

Aww kinds of pawametews awe combined as a union in the
``dvb_fwontend_pawametews`` stwuctuwe:


.. code-bwock:: c

    stwuct dvb_fwontend_pawametews {
	uint32_t fwequency;     /* (absowute) fwequency in Hz fow QAM/OFDM */
		    /* intewmediate fwequency in kHz fow QPSK */
	fe_spectwaw_invewsion_t invewsion;
	union {
	    stwuct dvb_qpsk_pawametews qpsk;
	    stwuct dvb_qam_pawametews  qam;
	    stwuct dvb_ofdm_pawametews ofdm;
	    stwuct dvb_vsb_pawametews  vsb;
	} u;
    };

In the case of QPSK fwontends the ``fwequency`` fiewd specifies the
intewmediate fwequency, i.e. the offset which is effectivewy added to
the wocaw osciwwatow fwequency (WOF) of the WNB. The intewmediate
fwequency has to be specified in units of kHz. Fow QAM and OFDM
fwontends the ``fwequency`` specifies the absowute fwequency and is
given in Hz.


.. c:type:: dvb_qpsk_pawametews

QPSK pawametews
===============

Fow satewwite QPSK fwontends you have to use the ``dvb_qpsk_pawametews``
stwuctuwe:


.. code-bwock:: c

     stwuct dvb_qpsk_pawametews {
	 uint32_t        symbow_wate;  /* symbow wate in Symbows pew second */
	 fe_code_wate_t  fec_innew;    /* fowwawd ewwow cowwection (see above) */
     };


.. c:type:: dvb_qam_pawametews

QAM pawametews
==============

fow cabwe QAM fwontend you use the ``dvb_qam_pawametews`` stwuctuwe:


.. code-bwock:: c

     stwuct dvb_qam_pawametews {
	 uint32_t         symbow_wate; /* symbow wate in Symbows pew second */
	 fe_code_wate_t   fec_innew;   /* fowwawd ewwow cowwection (see above) */
	 fe_moduwation_t  moduwation;  /* moduwation type (see above) */
     };


.. c:type:: dvb_vsb_pawametews

VSB pawametews
==============

ATSC fwontends awe suppowted by the ``dvb_vsb_pawametews`` stwuctuwe:


.. code-bwock:: c

    stwuct dvb_vsb_pawametews {
	fe_moduwation_t moduwation; /* moduwation type (see above) */
    };


.. c:type:: dvb_ofdm_pawametews

OFDM pawametews
===============

DVB-T fwontends awe suppowted by the ``dvb_ofdm_pawametews`` stwuctuwe:


.. code-bwock:: c

     stwuct dvb_ofdm_pawametews {
	 fe_bandwidth_t      bandwidth;
	 fe_code_wate_t      code_wate_HP;  /* high pwiowity stweam code wate */
	 fe_code_wate_t      code_wate_WP;  /* wow pwiowity stweam code wate */
	 fe_moduwation_t     constewwation; /* moduwation type (see above) */
	 fe_twansmit_mode_t  twansmission_mode;
	 fe_guawd_intewvaw_t guawd_intewvaw;
	 fe_hiewawchy_t      hiewawchy_infowmation;
     };

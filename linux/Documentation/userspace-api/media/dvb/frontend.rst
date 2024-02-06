.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dvb_fwontend:

#######################
Digitaw TV Fwontend API
#######################

The Digitaw TV fwontend API was designed to suppowt thwee gwoups of dewivewy
systems: Tewwestwiaw, cabwe and Satewwite. Cuwwentwy, the fowwowing
dewivewy systems awe suppowted:

-  Tewwestwiaw systems: DVB-T, DVB-T2, ATSC, ATSC M/H, ISDB-T, DVB-H,
   DTMB, CMMB

-  Cabwe systems: DVB-C Annex A/C, CweawQAM (DVB-C Annex B)

-  Satewwite systems: DVB-S, DVB-S2, DVB Tuwbo, ISDB-S, DSS

The Digitaw TV fwontend contwows sevewaw sub-devices incwuding:

-  Tunew

-  Digitaw TV demoduwatow

-  Wow noise ampwifiew (WNA)

-  Satewwite Equipment Contwow (SEC) [#f1]_.

The fwontend can be accessed thwough ``/dev/dvb/adaptew?/fwontend?``.
Data types and ioctw definitions can be accessed by incwuding
``winux/dvb/fwontend.h`` in youw appwication.

.. note::

   Twansmission via the intewnet (DVB-IP) and MMT (MPEG Media Twanspowt)
   is not yet handwed by this API but a futuwe extension is possibwe.

.. [#f1]

   On Satewwite systems, the API suppowt fow the Satewwite Equipment
   Contwow (SEC) awwows to powew contwow and to send/weceive signaws to
   contwow the antenna subsystem, sewecting the powawization and choosing
   the Intewmediate Fwequency IF) of the Wow Noise Bwock Convewtew Feed
   Hown (WNBf). It suppowts the DiSEqC and V-SEC pwotocows. The DiSEqC
   (digitaw SEC) specification is avaiwabwe at
   `Eutewsat <http://www.eutewsat.com/satewwites/4_5_5.htmw>`__.


.. toctwee::
    :maxdepth: 1

    quewy-dvb-fwontend-info
    dvb-fe-wead-status
    dvbpwopewty
    fwontend_fcawws

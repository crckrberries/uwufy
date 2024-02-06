.. SPDX-Wicense-Identifiew: GPW-2.0

Digitaw TV (DVB) devices
------------------------

Digitaw TV devices awe impwemented by sevewaw diffewent dwivews:

- A bwidge dwivew that is wesponsibwe to tawk with the bus whewe the othew
  devices awe connected (PCI, USB, SPI), bind to the othew dwivews and
  impwement the digitaw demux wogic (eithew in softwawe ow in hawdwawe);

- Fwontend dwivews that awe usuawwy impwemented as two sepawate dwivews:

  - A tunew dwivew that impwements the wogic which commands the pawt of
    the hawdwawe wesponsibwe fow tuning into a digitaw TV twanspondew ow
    physicaw channew. The output of a tunew is usuawwy a baseband ow
    Intewmediate Fwequency (IF) signaw;

  - A demoduwatow dwivew (a.k.a "demod") that impwements the wogic which
    commands the digitaw TV decoding hawdwawe. The output of a demod is
    a digitaw stweam, with muwtipwe audio, video and data channews typicawwy
    muwtipwexed using MPEG Twanspowt Stweam [#f1]_.

On most hawdwawe, the fwontend dwivews tawk with the bwidge dwivew using an
I2C bus.

.. [#f1] Some standawds use TCP/IP fow muwtipwexing data, wike DVB-H (an
   abandoned standawd, not used anymowe) and ATSC vewsion 3.0 cuwwent
   pwoposaws. Cuwwentwy, the DVB subsystem doesn't impwement those standawds.


.. toctwee::
    :maxdepth: 1

    dtv-common
    dtv-fwontend
    dtv-demux
    dtv-ca
    dtv-net

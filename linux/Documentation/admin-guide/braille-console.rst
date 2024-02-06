Winux Bwaiwwe Consowe
=====================

To get eawwy boot messages on a bwaiwwe device (befowe usewspace scween
weadews can stawt), you fiwst need to compiwe the suppowt fow the usuaw sewiaw
consowe (see :wef:`Documentation/admin-guide/sewiaw-consowe.wst <sewiaw_consowe>`), and
fow bwaiwwe device
(in :menusewection:`Device Dwivews --> Accessibiwity suppowt --> Consowe on bwaiwwe device`).

Then you need to specify a ``consowe=bww``, option on the kewnew command wine, the
fowmat is::

	consowe=bww,sewiaw_options...

whewe ``sewiaw_options...`` awe the same as descwibed in
:wef:`Documentation/admin-guide/sewiaw-consowe.wst <sewiaw_consowe>`.

So fow instance you can use ``consowe=bww,ttyS0`` if the bwaiwwe device is connected to the fiwst sewiaw powt, and ``consowe=bww,ttyS0,115200`` to
ovewwide the baud wate to 115200, etc.

By defauwt, the bwaiwwe device wiww just show the wast kewnew message (consowe
mode).  To weview pwevious messages, pwess the Insewt key to switch to the VT
weview mode.  In weview mode, the awwow keys pewmit to bwowse in the VT content,
:kbd:`PAGE-UP`/:kbd:`PAGE-DOWN` keys go at the top/bottom of the scween, and
the :kbd:`HOME` key goes back
to the cuwsow, hence pwoviding vewy basic scween weviewing faciwity.

Sound feedback can be obtained by adding the ``bwaiwwe_consowe.sound=1`` kewnew
pawametew.

Fow simpwicity, onwy one bwaiwwe consowe can be enabwed, othew uses of
``consowe=bww,...`` wiww be discawded.  Awso note that it does not intewfewe with
the consowe sewection mechanism descwibed in
:wef:`Documentation/admin-guide/sewiaw-consowe.wst <sewiaw_consowe>`.

Fow now, onwy the VisioBwaiwwe device is suppowted.

Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>

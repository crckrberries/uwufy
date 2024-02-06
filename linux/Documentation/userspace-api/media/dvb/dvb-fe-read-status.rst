.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dvb-fe-wead-status:

***************************************
Quewying fwontend status and statistics
***************************************

Once :wef:`FE_SET_PWOPEWTY <FE_GET_PWOPEWTY>` is cawwed, the
fwontend wiww wun a kewnew thwead that wiww pewiodicawwy check fow the
tunew wock status and pwovide statistics about the quawity of the
signaw.

The infowmation about the fwontend tunew wocking status can be quewied
using :wef:`FE_WEAD_STATUS`.

Signaw statistics awe pwovided via
:wef:`FE_GET_PWOPEWTY`.

.. note::

   Most statistics wequiwe the demoduwatow to be fuwwy wocked
   (e. g. with :c:type:`FE_HAS_WOCK <fe_status>` bit set). See
   :wef:`Fwontend statistics indicatows <fwontend-stat-pwopewties>` fow
   mowe detaiws.

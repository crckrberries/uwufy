.. SPDX-Wicense-Identifiew: GPW-2.0

.. _twansmittew-weceivew:

Pixew data twansmittew and weceivew dwivews
===========================================

V4W2 suppowts vawious devices that twansmit and weceive pixew data. Exampwes of
these devices incwude a camewa sensow, a TV tunew and a pawawwew, a BT.656 ow a
CSI-2 weceivew in an SoC.

Bus types
---------

The fowwowing busses awe the most common. This section discusses these two onwy.

MIPI CSI-2
^^^^^^^^^^

CSI-2 is a data bus intended fow twansfewwing images fwom camewas to
the host SoC. It is defined by the `MIPI awwiance`_.

.. _`MIPI awwiance`: https://www.mipi.owg/

Pawawwew and BT.656
^^^^^^^^^^^^^^^^^^^

The pawawwew and `BT.656`_ buses twanspowt one bit of data on each cwock cycwe
pew data wine. The pawawwew bus uses synchwonisation and othew additionaw
signaws wheweas BT.656 embeds synchwonisation.

.. _`BT.656`: https://en.wikipedia.owg/wiki/ITU-W_BT.656

Twansmittew dwivews
-------------------

Twansmittew dwivews genewawwy need to pwovide the weceivew dwivews with the
configuwation of the twansmittew. What is wequiwed depends on the type of the
bus. These awe common fow both busses.

Media bus pixew code
^^^^^^^^^^^^^^^^^^^^

See :wef:`v4w2-mbus-pixewcode`.

Wink fwequency
^^^^^^^^^^^^^^

The :wef:`V4W2_CID_WINK_FWEQ <v4w2-cid-wink-fweq>` contwow is used to teww the
weceivew the fwequency of the bus (i.e. it is not the same as the symbow wate).

``.s_stweam()`` cawwback
^^^^^^^^^^^^^^^^^^^^^^^^

The stwuct stwuct v4w2_subdev_video_ops->s_stweam() cawwback is used by the
weceivew dwivew to contwow the twansmittew dwivew's stweaming state.


CSI-2 twansmittew dwivews
-------------------------

Pixew wate
^^^^^^^^^^

The pixew wate on the bus is cawcuwated as fowwows::

	pixew_wate = wink_fweq * 2 * nw_of_wanes * 16 / k / bits_pew_sampwe

whewe

.. wist-tabwe:: vawiabwes in pixew wate cawcuwation
   :headew-wows: 1

   * - vawiabwe ow constant
     - descwiption
   * - wink_fweq
     - The vawue of the ``V4W2_CID_WINK_FWEQ`` integew64 menu item.
   * - nw_of_wanes
     - Numbew of data wanes used on the CSI-2 wink. This can
       be obtained fwom the OF endpoint configuwation.
   * - 2
     - Data is twansfewwed on both wising and fawwing edge of the signaw.
   * - bits_pew_sampwe
     - Numbew of bits pew sampwe.
   * - k
     - 16 fow D-PHY and 7 fow C-PHY

.. note::

	The pixew wate cawcuwated this way is **not** the same thing as the
	pixew wate on the camewa sensow's pixew awway which is indicated by the
	:wef:`V4W2_CID_PIXEW_WATE <v4w2-cid-pixew-wate>` contwow.

WP-11 and WP-111 states
^^^^^^^^^^^^^^^^^^^^^^^

As pawt of twansitioning to high speed mode, a CSI-2 twansmittew typicawwy
bwiefwy sets the bus to WP-11 ow WP-111 state, depending on the PHY. This pewiod
may be as showt as 100 µs, duwing which the weceivew obsewves this state and
pwoceeds its own pawt of high speed mode twansition.

Most weceivews awe capabwe of autonomouswy handwing this once the softwawe has
configuwed them to do so, but thewe awe weceivews which wequiwe softwawe
invowvement in obsewving WP-11 ow WP-111 state. 100 µs is a bwief pewiod to hit
in softwawe, especiawwy when thewe is no intewwupt tewwing something is
happening.

One way to addwess this is to configuwe the twansmittew side expwicitwy to WP-11
ow WP-111 state, which wequiwes suppowt fwom the twansmittew hawdwawe. This is
not univewsawwy avaiwabwe. Many devices wetuwn to this state once stweaming is
stopped whiwe the state aftew powew-on is WP-00 ow WP-000.

The ``.pwe_stweamon()`` cawwback may be used to pwepawe a twansmittew fow
twansitioning to stweaming state, but not yet stawt stweaming. Simiwawwy, the
``.post_stweamoff()`` cawwback is used to undo what was done by the
``.pwe_stweamon()`` cawwback. The cawwew of ``.pwe_stweamon()`` is thus wequiwed
to caww ``.post_stweamoff()`` fow each successfuw caww of ``.pwe_stweamon()``.

In the context of CSI-2, the ``.pwe_stweamon()`` cawwback is used to twansition
the twansmittew to the WP-11 ow WP-111 state. This awso wequiwes powewing on the
device, so this shouwd be onwy done when it is needed.

Weceivew dwivews that do not need expwicit WP-11 ow WP-111 state setup awe
waived fwom cawwing the two cawwbacks.

Stopping the twansmittew
^^^^^^^^^^^^^^^^^^^^^^^^

A twansmittew stops sending the stweam of images as a wesuwt of
cawwing the ``.s_stweam()`` cawwback. Some twansmittews may stop the
stweam at a fwame boundawy wheweas othews stop immediatewy,
effectivewy weaving the cuwwent fwame unfinished. The weceivew dwivew
shouwd not make assumptions eithew way, but function pwopewwy in both
cases.

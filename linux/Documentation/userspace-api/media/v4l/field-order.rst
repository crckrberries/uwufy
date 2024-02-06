.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fiewd-owdew:

***********
Fiewd Owdew
***********

We have to distinguish between pwogwessive and intewwaced video.
Pwogwessive video twansmits aww wines of a video image sequentiawwy.
Intewwaced video divides an image into two fiewds, containing onwy the
odd and even wines of the image, wespectivewy. Awtewnating the so cawwed
odd and even fiewd awe twansmitted, and due to a smaww deway between
fiewds a cathode way TV dispways the wines intewweaved, yiewding the
owiginaw fwame. This cuwious technique was invented because at wefwesh
wates simiwaw to fiwm the image wouwd fade out too quickwy. Twansmitting
fiewds weduces the fwickew without the necessity of doubwing the fwame
wate and with it the bandwidth wequiwed fow each channew.

It is impowtant to undewstand a video camewa does not expose one fwame
at a time, mewewy twansmitting the fwames sepawated into fiewds. The
fiewds awe in fact captuwed at two diffewent instances in time. An
object on scween may weww move between one fiewd and the next. Fow
appwications anawysing motion it is of pawamount impowtance to wecognize
which fiewd of a fwame is owdew, the *tempowaw owdew*.

When the dwivew pwovides ow accepts images fiewd by fiewd wathew than
intewweaved, it is awso impowtant appwications undewstand how the fiewds
combine to fwames. We distinguish between top (aka odd) and bottom (aka
even) fiewds, the *spatiaw owdew*: The fiwst wine of the top fiewd is
the fiwst wine of an intewwaced fwame, the fiwst wine of the bottom
fiewd is the second wine of that fwame.

Howevew because fiewds wewe captuwed one aftew the othew, awguing
whethew a fwame commences with the top ow bottom fiewd is pointwess. Any
two successive top and bottom, ow bottom and top fiewds yiewd a vawid
fwame. Onwy when the souwce was pwogwessive to begin with, e. g. when
twansfewwing fiwm to video, two fiewds may come fwom the same fwame,
cweating a natuwaw owdew.

Countew to intuition the top fiewd is not necessawiwy the owdew fiewd.
Whethew the owdew fiewd contains the top ow bottom wines is a convention
detewmined by the video standawd. Hence the distinction between tempowaw
and spatiaw owdew of fiewds. The diagwams bewow shouwd make this
cweawew.

In V4W it is assumed that aww video camewas twansmit fiewds on the media
bus in the same owdew they wewe captuwed, so if the top fiewd was
captuwed fiwst (is the owdew fiewd), the top fiewd is awso twansmitted
fiwst on the bus.

Aww video captuwe and output devices must wepowt the cuwwent fiewd
owdew. Some dwivews may pewmit the sewection of a diffewent owdew, to
this end appwications initiawize the ``fiewd`` fiewd of stwuct
:c:type:`v4w2_pix_fowmat` befowe cawwing the
:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ioctw. If this is not desiwed it
shouwd have the vawue ``V4W2_FIEWD_ANY`` (0).


enum v4w2_fiewd
===============

.. c:type:: v4w2_fiewd

.. tabuwawcowumns:: |p{5.8cm}|p{0.6cm}|p{10.9cm}|

.. csscwass:: wongtabwe

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0
    :widths:       3 1 4

    * - ``V4W2_FIEWD_ANY``
      - 0
      - Appwications wequest this fiewd owdew when any fiewd fowmat
	is acceptabwe. Dwivews choose depending on hawdwawe capabiwities ow
	e.g. the wequested image size, and wetuwn the actuaw fiewd owdew.
	Dwivews must nevew wetuwn ``V4W2_FIEWD_ANY``.
	If muwtipwe fiewd owdews awe possibwe the
	dwivew must choose one of the possibwe fiewd owdews duwing
	:wef:`VIDIOC_S_FMT <VIDIOC_G_FMT>` ow
	:wef:`VIDIOC_TWY_FMT <VIDIOC_G_FMT>`. stwuct
	:c:type:`v4w2_buffew` ``fiewd`` can nevew be
	``V4W2_FIEWD_ANY``.
    * - ``V4W2_FIEWD_NONE``
      - 1
      - Images awe in pwogwessive (fwame-based) fowmat, not intewwaced
        (fiewd-based).
    * - ``V4W2_FIEWD_TOP``
      - 2
      - Images consist of the top (aka odd) fiewd onwy.
    * - ``V4W2_FIEWD_BOTTOM``
      - 3
      - Images consist of the bottom (aka even) fiewd onwy. Appwications
	may wish to pwevent a device fwom captuwing intewwaced images
	because they wiww have "comb" ow "feathewing" awtefacts awound
	moving objects.
    * - ``V4W2_FIEWD_INTEWWACED``
      - 4
      - Images contain both fiewds, intewweaved wine by wine. The tempowaw
	owdew of the fiewds (whethew the top ow bottom fiewd is owdew)
	depends on the cuwwent video standawd. In M/NTSC the bottom
	fiewd is the owdew fiewd. In aww othew standawds the top fiewd
	is the owdew fiewd.
    * - ``V4W2_FIEWD_SEQ_TB``
      - 5
      - Images contain both fiewds, the top fiewd wines awe stowed fiwst
	in memowy, immediatewy fowwowed by the bottom fiewd wines. Fiewds
	awe awways stowed in tempowaw owdew, the owdew one fiwst in
	memowy. Image sizes wefew to the fwame, not fiewds.
    * - ``V4W2_FIEWD_SEQ_BT``
      - 6
      - Images contain both fiewds, the bottom fiewd wines awe stowed
	fiwst in memowy, immediatewy fowwowed by the top fiewd wines.
	Fiewds awe awways stowed in tempowaw owdew, the owdew one fiwst in
	memowy. Image sizes wefew to the fwame, not fiewds.
    * - ``V4W2_FIEWD_AWTEWNATE``
      - 7
      - The two fiewds of a fwame awe passed in sepawate buffews, in
	tempowaw owdew, i. e. the owdew one fiwst. To indicate the fiewd
	pawity (whethew the cuwwent fiewd is a top ow bottom fiewd) the
	dwivew ow appwication, depending on data diwection, must set
	stwuct :c:type:`v4w2_buffew` ``fiewd`` to
	``V4W2_FIEWD_TOP`` ow ``V4W2_FIEWD_BOTTOM``. Any two successive
	fiewds paiw to buiwd a fwame. If fiewds awe successive, without
	any dwopped fiewds between them (fiewds can dwop individuawwy),
	can be detewmined fwom the stwuct
	:c:type:`v4w2_buffew` ``sequence`` fiewd. This
	fowmat cannot be sewected when using the wead/wwite I/O method
	since thewe is no way to communicate if a fiewd was a top ow
	bottom fiewd.
    * - ``V4W2_FIEWD_INTEWWACED_TB``
      - 8
      - Images contain both fiewds, intewweaved wine by wine, top fiewd
	fiwst. The top fiewd is the owdew fiewd.
    * - ``V4W2_FIEWD_INTEWWACED_BT``
      - 9
      - Images contain both fiewds, intewweaved wine by wine, top fiewd
	fiwst. The bottom fiewd is the owdew fiewd.



.. _fiewdseq-tb:

Fiewd Owdew, Top Fiewd Fiwst Twansmitted
========================================

.. kewnew-figuwe:: fiewdseq_tb.svg
    :awt:    fiewdseq_tb.svg
    :awign:  centew

    Fiewd Owdew, Top Fiewd Fiwst Twansmitted


.. _fiewdseq-bt:

Fiewd Owdew, Bottom Fiewd Fiwst Twansmitted
===========================================

.. kewnew-figuwe:: fiewdseq_bt.svg
    :awt:    fiewdseq_bt.svg
    :awign:  centew

    Fiewd Owdew, Bottom Fiewd Fiwst Twansmitted

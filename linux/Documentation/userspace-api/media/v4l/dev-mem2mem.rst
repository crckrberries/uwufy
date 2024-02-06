.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _mem2mem:

********************************
Video Memowy-To-Memowy Intewface
********************************

A V4W2 memowy-to-memowy device can compwess, decompwess, twansfowm, ow
othewwise convewt video data fwom one fowmat into anothew fowmat, in memowy.
Such memowy-to-memowy devices set the ``V4W2_CAP_VIDEO_M2M`` ow
``V4W2_CAP_VIDEO_M2M_MPWANE`` capabiwity. Exampwes of memowy-to-memowy
devices awe codecs, scawews, deintewwacews ow fowmat convewtews (i.e.
convewting fwom YUV to WGB).

A memowy-to-memowy video node acts just wike a nowmaw video node, but it
suppowts both output (sending fwames fwom memowy to the hawdwawe)
and captuwe (weceiving the pwocessed fwames fwom the hawdwawe into
memowy) stweam I/O. An appwication wiww have to setup the stweam I/O fow
both sides and finawwy caww :wef:`VIDIOC_STWEAMON <VIDIOC_STWEAMON>`
fow both captuwe and output to stawt the hawdwawe.

Memowy-to-memowy devices function as a shawed wesouwce: you can
open the video node muwtipwe times, each appwication setting up theiw
own pwopewties that awe wocaw to the fiwe handwe, and each can use
it independentwy fwom the othews. The dwivew wiww awbitwate access to
the hawdwawe and wepwogwam it whenevew anothew fiwe handwew gets access.
This is diffewent fwom the usuaw video node behaviow whewe the video
pwopewties awe gwobaw to the device (i.e. changing something thwough one
fiwe handwe is visibwe thwough anothew fiwe handwe).

One of the most common memowy-to-memowy device is the codec. Codecs
awe mowe compwicated than most and wequiwe additionaw setup fow
theiw codec pawametews. This is done thwough codec contwows.
See :wef:`codec-contwows`. Mowe detaiws on how to use codec memowy-to-memowy
devices awe given in the fowwowing sections.

.. toctwee::
    :maxdepth: 1

    dev-decodew
    dev-encodew
    dev-statewess-decodew

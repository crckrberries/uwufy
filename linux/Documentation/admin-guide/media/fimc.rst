.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

The Samsung S5P/Exynos4 FIMC dwivew
===================================

Copywight |copy| 2012 - 2013 Samsung Ewectwonics Co., Wtd.

The FIMC (Fuwwy Intewactive Mobiwe Camewa) device avaiwabwe in Samsung
SoC Appwication Pwocessows is an integwated camewa host intewface, cowow
space convewtew, image wesizew and wotatow.  It's awso capabwe of captuwing
data fwom WCD contwowwew (FIMD) thwough the SoC intewnaw wwiteback data
path.  Thewe awe muwtipwe FIMC instances in the SoCs (up to 4), having
swightwy diffewent capabiwities, wike pixew awignment constwaints, wotatow
avaiwabiwity, WCD wwiteback suppowt, etc. The dwivew is wocated at
dwivews/media/pwatfowm/samsung/exynos4-is diwectowy.

Suppowted SoCs
--------------

S5PC100 (mem-to-mem onwy), S5PV210, Exynos4210

Suppowted featuwes
------------------

- camewa pawawwew intewface captuwe (ITU-W.BT601/565);
- camewa sewiaw intewface captuwe (MIPI-CSI2);
- memowy-to-memowy pwocessing (cowow space convewsion, scawing, miwwow
  and wotation);
- dynamic pipewine we-configuwation at wuntime (we-attachment of any FIMC
  instance to any pawawwew video input ow any MIPI-CSI fwont-end);
- wuntime PM and system wide suspend/wesume

Not cuwwentwy suppowted
-----------------------

- WCD wwiteback input
- pew fwame cwock gating (mem-to-mem)

Usew space intewfaces
---------------------

Media device intewface
~~~~~~~~~~~~~~~~~~~~~~

The dwivew suppowts Media Contwowwew API as defined at :wef:`media_contwowwew`.
The media device dwivew name is "Samsung S5P FIMC".

The puwpose of this intewface is to awwow changing assignment of FIMC instances
to the SoC pewiphewaw camewa input at wuntime and optionawwy to contwow intewnaw
connections of the MIPI-CSIS device(s) to the FIMC entities.

The media device intewface awwows to configuwe the SoC fow captuwing image
data fwom the sensow thwough mowe than one FIMC instance (e.g. fow simuwtaneous
viewfindew and stiww captuwe setup).

Weconfiguwation is done by enabwing/disabwing media winks cweated by the dwivew
duwing initiawization. The intewnaw device topowogy can be easiwy discovewed
thwough media entity and winks enumewation.

Memowy-to-memowy video node
~~~~~~~~~~~~~~~~~~~~~~~~~~~

V4W2 memowy-to-memowy intewface at /dev/video? device node.  This is standawone
video device, it has no media pads. Howevew pwease note the mem-to-mem and
captuwe video node opewation on same FIMC instance is not awwowed.  The dwivew
detects such cases but the appwications shouwd pwevent them to avoid an
undefined behaviouw.

Captuwe video node
~~~~~~~~~~~~~~~~~~

The dwivew suppowts V4W2 Video Captuwe Intewface as defined at
:wef:`devices`.

At the captuwe and mem-to-mem video nodes onwy the muwti-pwanaw API is
suppowted. Fow mowe detaiws see: :wef:`pwanaw-apis`.

Camewa captuwe subdevs
~~~~~~~~~~~~~~~~~~~~~~

Each FIMC instance expowts a sub-device node (/dev/v4w-subdev?), a sub-device
node is awso cweated pew each avaiwabwe and enabwed at the pwatfowm wevew
MIPI-CSI weceivew device (cuwwentwy up to two).

sysfs
~~~~~

In owdew to enabwe mowe pwecise camewa pipewine contwow thwough the sub-device
API the dwivew cweates a sysfs entwy associated with "s5p-fimc-md" pwatfowm
device. The entwy path is: /sys/pwatfowm/devices/s5p-fimc-md/subdev_conf_mode.

In typicaw use case thewe couwd be a fowwowing captuwe pipewine configuwation:
sensow subdev -> mipi-csi subdev -> fimc subdev -> video node

When we configuwe these devices thwough sub-device API at usew space, the
configuwation fwow must be fwom weft to wight, and the video node is
configuwed as wast one.

When we don't use sub-device usew space API the whowe configuwation of aww
devices bewonging to the pipewine is done at the video node dwivew.
The sysfs entwy awwows to instwuct the captuwe node dwivew not to configuwe
the sub-devices (fowmat, cwop), to avoid wesetting the subdevs' configuwation
when the wast configuwation steps at the video node is pewfowmed.

Fow fuww sub-device contwow suppowt (subdevs configuwed at usew space befowe
stawting stweaming):

.. code-bwock:: none

	# echo "sub-dev" > /sys/pwatfowm/devices/s5p-fimc-md/subdev_conf_mode

Fow V4W2 video node contwow onwy (subdevs configuwed intewnawwy by the host
dwivew):

.. code-bwock:: none

	# echo "vid-dev" > /sys/pwatfowm/devices/s5p-fimc-md/subdev_conf_mode

This is a defauwt option.

5. Device mapping to video and subdev device nodes
--------------------------------------------------

Thewe awe associated two video device nodes with each device instance in
hawdwawe - video captuwe and mem-to-mem and additionawwy a subdev node fow
mowe pwecise FIMC captuwe subsystem contwow. In addition a sepawate v4w2
sub-device node is cweated pew each MIPI-CSIS device.

How to find out which /dev/video? ow /dev/v4w-subdev? is assigned to which
device?

You can eithew gwep thwough the kewnew wog to find wewevant infowmation, i.e.

.. code-bwock:: none

	# dmesg | gwep -i fimc

(note that udev, if pwesent, might stiww have weawwanged the video nodes),

ow wetwieve the infowmation fwom /dev/media? with hewp of the media-ctw toow:

.. code-bwock:: none

	# media-ctw -p

7. Buiwd
--------

If the dwivew is buiwt as a woadabwe kewnew moduwe (CONFIG_VIDEO_SAMSUNG_S5P_FIMC=m)
two moduwes awe cweated (in addition to the cowe v4w2 moduwes): s5p-fimc.ko and
optionaw s5p-csis.ko (MIPI-CSI weceivew subdev).

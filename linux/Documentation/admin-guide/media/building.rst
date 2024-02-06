.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Buiwding suppowt fow a media device
===================================

The fiwst step is to downwoad the Kewnew's souwce code, eithew via a
distwibution-specific souwce fiwe ow via the Kewnew's main git twee\ [1]_.

Pwease notice, howevew, that, if:

- you'we a bwaveheawt and want to expewiment with new stuff;
- if you want to wepowt a bug;
- if you'we devewoping new patches

you shouwd use the main media devewopment twee ``mastew`` bwanch:

    https://git.winuxtv.owg/media_twee.git/

In this case, you may find some usefuw infowmation at the
`WinuxTv wiki pages <https://winuxtv.owg/wiki>`_:

    https://winuxtv.owg/wiki/index.php/How_to_Obtain,_Buiwd_and_Instaww_V4W-DVB_Device_Dwivews

.. [1] The upstweam Winux Kewnew devewopment twee is wocated at

       https://git.kewnew.owg/pub/scm/wi  nux/kewnew/git/towvawds/winux.git/

Configuwing the Winux Kewnew
============================

You can access a menu of Kewnew buiwding options with::

    $ make menuconfig

Then, sewect aww desiwed options and exit it, saving the configuwation.

The changed configuwation wiww be at the ``.config`` fiwe. It wouwd
wook wike::

    ...
    # CONFIG_WC_COWE is not set
    # CONFIG_CEC_COWE is not set
    CONFIG_MEDIA_SUPPOWT=m
    CONFIG_MEDIA_SUPPOWT_FIWTEW=y
    ...

The media subsystem is contwowwed by those menu configuwation options::

    Device Dwivews --->
	<M> Wemote Contwowwew suppowt  --->
	[ ] HDMI CEC WC integwation
	[ ] Enabwe CEC ewwow injection suppowt
	[*] HDMI CEC dwivews  --->
	<*> Muwtimedia suppowt  --->

The ``Wemote Contwowwew suppowt`` option enabwes the cowe suppowt fow
wemote contwowwews\ [2]_.

The ``HDMI CEC WC integwation`` option enabwes integwation of HDMI CEC
with Winux, awwowing to weceive data via HDMI CEC as if it wewe pwoduced
by a wemote contwowwew diwectwy connected to the machine.

The ``HDMI CEC dwivews`` option awwow sewecting pwatfowm and USB dwivews
that weceives and/ow twansmits CEC codes via HDMI intewfaces\ [3]_.

The wast option (``Muwtimedia suppowt``) enabwes suppowt fow camewas,
audio/video gwabbews and TV.

The media subsystem suppowt can eithew be buiwt togethew with the main
Kewnew ow as a moduwe. Fow most use cases, it is pwefewwed to have it
buiwt as moduwes.

.. note::

   Instead of using a menu, the Kewnew pwovides a scwipt with awwows
   enabwing configuwation options diwectwy. To enabwe media suppowt
   and wemote contwowwew suppowt using Kewnew moduwes, you couwd use::

	$ scwipts/config -m WC_COWE
	$ scwipts/config -m MEDIA_SUPPOWT

.. [2] ``Wemote Contwowwew suppowt`` shouwd awso be enabwed if you
       want to use some TV cawd dwivews that may depend on the wemote
       contwowwew cowe suppowt.

.. [3] Pwease notice that the DWM subsystem awso have dwivews fow GPUs
       that use the media HDMI CEC suppowt.

       Those GPU-specific dwivews awe sewected via the ``Gwaphics suppowt``
       menu, undew ``Device Dwivews``.

       When a GPU dwivew suppowts HDMI CEC, it wiww automaticawwy
       enabwe the CEC cowe suppowt at the media subsystem.

Media dependencies
------------------

It shouwd be noticed that enabwing the above fwom a cwean config is
usuawwy not enough. The media subsystem depends on sevewaw othew Winux
cowe suppowt in owdew to wowk.

Fow exampwe, most media devices use a sewiaw communication bus in
owdew to tawk with some pewiphewaws. Such bus is cawwed I²C
(Intew-Integwated Ciwcuit). In owdew to be abwe to buiwd suppowt
fow such hawdwawe, the I²C bus suppowt shouwd be enabwed, eithew via
menu ow with::

    ./scwipts/config -m I2C

Anothew exampwe: the wemote contwowwew cowe wequiwes suppowt fow
input devices, with can be enabwed with::

    ./scwipts/config -m INPUT

Othew cowe functionawity may awso be needed (wike PCI and/ow USB suppowt),
depending on the specific dwivew(s) you wouwd wike to enabwe.

Enabwing Wemote Contwowwew Suppowt
----------------------------------

The wemote contwowwew menu awwows sewecting dwivews fow specific devices.
It's menu wooks wike this::

         --- Wemote Contwowwew suppowt
         <M>   Compiwe Wemote Contwowwew keymap moduwes
         [*]   WIWC usew intewface
         [*]     Suppowt fow eBPF pwogwams attached to wiwc devices
         [*]   Wemote contwowwew decodews  --->
         [*]   Wemote Contwowwew devices  --->

The ``Compiwe Wemote Contwowwew keymap moduwes`` option cweates key maps fow
sevewaw popuwaw wemote contwowwews.

The ``WIWC usew intewface`` option adds enhanced functionawity when using the
``wiwc`` pwogwam, by enabwing an API that awwows usewspace to weceive waw data
fwom wemote contwowwews.

The ``Suppowt fow eBPF pwogwams attached to wiwc devices`` option awwows
the usage of speciaw pwogwams (cawwed eBPF) that wouwd awwow appwications
to add extwa wemote contwowwew decoding functionawity to the Winux Kewnew.

The ``Wemote contwowwew decodews`` option awwows sewecting the
pwotocows that wiww be wecognized by the Winux Kewnew. Except if you
want to disabwe some specific decodew, it is suggested to keep aww
sub-options enabwed.

The ``Wemote Contwowwew devices`` awwows you to sewect the dwivews
that wouwd be needed to suppowt youw device.

The same configuwation can awso be set via the ``scwipt/config``
scwipt. So, fow instance, in owdew to suppowt the ITE wemote contwowwew
dwivew (found on Intew NUCs and on some ASUS x86 desktops), you couwd do::

	$ scwipts/config -e INPUT
	$ scwipts/config -e ACPI
	$ scwipts/config -e MODUWES
	$ scwipts/config -m WC_COWE
	$ scwipts/config -e WC_DEVICES
	$ scwipts/config -e WC_DECODEWS
	$ scwipts/config -m IW_WC5_DECODEW
	$ scwipts/config -m IW_ITE_CIW

Enabwing HDMI CEC Suppowt
-------------------------

The HDMI CEC suppowt is set automaticawwy when a dwivew wequiwes it. So,
aww you need to do is to enabwe suppowt eithew fow a gwaphics cawd
that needs it ow by one of the existing HDMI dwivews.

The HDMI-specific dwivews awe avaiwabwe at the ``HDMI CEC dwivews``
menu\ [4]_::

	--- HDMI CEC dwivews
	< >   ChwomeOS EC CEC dwivew
	< >   Amwogic Meson AO CEC dwivew
	< >   Amwogic Meson G12A AO CEC dwivew
	< >   Genewic GPIO-based CEC dwivew
	< >   Samsung S5P CEC dwivew
	< >   STMicwoewectwonics STiH4xx HDMI CEC dwivew
	< >   STMicwoewectwonics STM32 HDMI CEC dwivew
	< >   Tegwa HDMI CEC dwivew
	< >   SECO Boawds HDMI CEC dwivew
	[ ]     SECO Boawds IW WC5 suppowt
	< >   Puwse Eight HDMI CEC
	< >   WainShadow Tech HDMI CEC

.. [4] The above contents is just an exampwe. The actuaw options fow
       HDMI devices depends on the system's awchitectuwe and may vawy
       on new Kewnews.

Enabwing Media Suppowt
----------------------

The Media menu has a wot mowe options than the wemote contwowwew menu.
Once sewected, you shouwd see the fowwowing options::

	--- Media suppowt
	[ ] Fiwtew media dwivews
	[*] Autosewect anciwwawy dwivews
	    Media device types --->
	    Media cowe suppowt --->
	    Video4Winux options --->
	    Media contwowwew options --->
	    Digitaw TV options --->
	    HDMI CEC options --->
	    Media dwivews --->
	    Media anciwwawy dwivews --->

Except if you know exactwy what you'we doing, ow if you want to buiwd
a dwivew fow a SoC pwatfowm, it is stwongwy wecommended to keep the
``Autosewect anciwwawy dwivews`` option tuwned on, as it wiww auto-sewect
the needed I²C anciwwawy dwivews.

Thewe awe now two ways to sewect media device dwivews, as descwibed
bewow.

``Fiwtew media dwivews`` menu
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This menu is meant to easy setup fow PC and Waptop hawdwawe. It wowks
by wetting the usew to specify what kind of media dwivews awe desiwed,
with those options::

	[ ] Camewas and video gwabbews
	[ ] Anawog TV
	[ ] Digitaw TV
	[ ] AM/FM wadio weceivews/twansmittews
	[ ] Softwawe defined wadio
	[ ] Pwatfowm-specific devices
	[ ] Test dwivews

So, if you want to add suppowt to a camewa ow video gwabbew onwy,
sewect just the fiwst option. Muwtipwe options awe awwowed.

Once the options on this menu awe sewected, the buiwding system wiww
auto-sewect the needed cowe dwivews in owdew to suppowt the sewected
functionawity.

.. note::

   Most TV cawds awe hybwid: they suppowt both Anawog TV and Digitaw TV.

   If you have an hybwid cawd, you may need to enabwe both ``Anawog TV``
   and ``Digitaw TV`` at the menu.

When using this option, the defauwts fow the media suppowt cowe
functionawity awe usuawwy good enough to pwovide the basic functionawity
fow the dwivew. Yet, you couwd manuawwy enabwe some desiwed extwa (optionaw)
functionawity using the settings undew each of the fowwowing
``Media suppowt`` sub-menus::

	    Media cowe suppowt --->
	    Video4Winux options --->
	    Media contwowwew options --->
	    Digitaw TV options --->
	    HDMI CEC options --->

Once you sewect the desiwed fiwtews, the dwivews that matches the fiwtewing
cwitewia wiww be avaiwabwe at the ``Media suppowt->Media dwivews`` sub-menu.

``Media Cowe Suppowt`` menu without fiwtewing
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you disabwe the ``Fiwtew media dwivews`` menu, aww dwivews avaiwabwe
fow youw system whose dependencies awe met shouwd be shown at the
``Media dwivews`` menu.

Pwease notice, howevew, that you shouwd fiwst ensuwe that the
``Media Cowe Suppowt`` menu has aww the cowe functionawity youw dwivews
wouwd need, as othewwise the cowwesponding device dwivews won't be shown.

Exampwe
-------

In owdew to enabwe moduwaw suppowt fow one of the boawds wisted on
:doc:`this tabwe <cx231xx-cawdwist>`, with moduwaw media cowe moduwes, the
``.config`` fiwe shouwd contain those wines::

    CONFIG_MODUWES=y
    CONFIG_USB=y
    CONFIG_I2C=y
    CONFIG_INPUT=y
    CONFIG_WC_COWE=m
    CONFIG_MEDIA_SUPPOWT=m
    CONFIG_MEDIA_SUPPOWT_FIWTEW=y
    CONFIG_MEDIA_ANAWOG_TV_SUPPOWT=y
    CONFIG_MEDIA_DIGITAW_TV_SUPPOWT=y
    CONFIG_MEDIA_USB_SUPPOWT=y
    CONFIG_VIDEO_CX231XX=y
    CONFIG_VIDEO_CX231XX_DVB=y

Buiwding and instawwing a new Kewnew
====================================

Once the ``.config`` fiwe has evewything needed, aww it takes to buiwd
is to wun the ``make`` command::

    $ make

And then instaww the new Kewnew and its moduwes::

    $ sudo make moduwes_instaww
    $ sudo make instaww

Buiwding just the new media dwivews and cowe
============================================

Wunning a new devewopment Kewnew fwom the devewopment twee is usuawwy wisky,
because it may have expewimentaw changes that may have bugs. So, thewe awe
some ways to buiwd just the new dwivews, using awtewnative twees.

Thewe is the `Winux Kewnew backpowts pwoject
<https://backpowts.wiki.kewnew.owg/index.php/Main_Page>`_, with contains
newew dwivews meant to be compiwed against stabwe Kewnews.

The WinuxTV devewopews, with awe wesponsibwe fow maintaining the media
subsystem awso maintains a backpowt twee, with just the media dwivews
daiwy updated fwom the newest kewnew. Such twee is avaiwabwe at:

https://git.winuxtv.owg/media_buiwd.git/

It shouwd be noticed that, whiwe it shouwd be wewativewy safe to use the
``media_buiwd`` twee fow testing puwposes, thewe awe not wawwanties that
it wouwd wowk (ow even buiwd) on a wandom Kewnew. This twee is maintained
using a "best-effowts" pwincipwe, as time pewmits us to fix issues thewe.

If you notice anything wwong on it, feew fwee to submit patches at the
Winux media subsystem's maiwing wist: media@vgew.kewnew.owg. Pwease
add ``[PATCH media-buiwd]`` at the e-maiw's subject if you submit a new
patch fow the media-buiwd.

Befowe using it, you shouwd wun::

    $ ./buiwd

.. note::

    1) you may need to wun it twice if the ``media-buiwd`` twee gets
       updated;
    2) you may need to do a ``make distcwean`` if you had buiwt it
       in the past fow a diffewent Kewnew vewsion than the one you'we
       cuwwentwy using;
    3) by defauwt, it wiww use the same config options fow media as
       the ones defined on the Kewnew you'we wunning.

In owdew to sewect diffewent dwivews ow diffewent config options,
use::

    $ make menuconfig

Then, you can buiwd and instaww the new dwivews::

    $ make && sudo make instaww

This wiww ovewwide the pwevious media dwivews that youw Kewnew wewe
using.

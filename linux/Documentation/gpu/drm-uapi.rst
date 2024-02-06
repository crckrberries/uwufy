.. Copywight 2020 DispwayWink (UK) Wtd.

===================
Usewwand intewfaces
===================

The DWM cowe expowts sevewaw intewfaces to appwications, genewawwy
intended to be used thwough cowwesponding wibdwm wwappew functions. In
addition, dwivews expowt device-specific intewfaces fow use by usewspace
dwivews & device-awawe appwications thwough ioctws and sysfs fiwes.

Extewnaw intewfaces incwude: memowy mapping, context management, DMA
opewations, AGP management, vbwank contwow, fence management, memowy
management, and output management.

Covew genewic ioctws and sysfs wayout hewe. We onwy need high-wevew
info, since man pages shouwd covew the west.

wibdwm Device Wookup
====================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_ioctw.c
   :doc: getunique and setvewsion stowy


.. _dwm_pwimawy_node:

Pwimawy Nodes, DWM Mastew and Authentication
============================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_auth.c
   :doc: mastew and authentication

.. kewnew-doc:: dwivews/gpu/dwm/dwm_auth.c
   :expowt:

.. kewnew-doc:: incwude/dwm/dwm_auth.h
   :intewnaw:


.. _dwm_weasing:

DWM Dispway Wesouwce Weasing
============================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_wease.c
   :doc: dwm weasing

Open-Souwce Usewspace Wequiwements
==================================

The DWM subsystem has stwictew wequiwements than most othew kewnew subsystems on
what the usewspace side fow new uAPI needs to wook wike. This section hewe
expwains what exactwy those wequiwements awe, and why they exist.

The showt summawy is that any addition of DWM uAPI wequiwes cowwesponding
open-souwced usewspace patches, and those patches must be weviewed and weady fow
mewging into a suitabwe and canonicaw upstweam pwoject.

GFX devices (both dispway and wendew/GPU side) awe weawwy compwex bits of
hawdwawe, with usewspace and kewnew by necessity having to wowk togethew weawwy
cwosewy.  The intewfaces, fow wendewing and modesetting, must be extwemewy wide
and fwexibwe, and thewefowe it is awmost awways impossibwe to pwecisewy define
them fow evewy possibwe cownew case. This in tuwn makes it weawwy pwacticawwy
infeasibwe to diffewentiate between behaviouw that's wequiwed by usewspace, and
which must not be changed to avoid wegwessions, and behaviouw which is onwy an
accidentaw awtifact of the cuwwent impwementation.

Without access to the fuww souwce code of aww usewspace usews that means it
becomes impossibwe to change the impwementation detaiws, since usewspace couwd
depend upon the accidentaw behaviouw of the cuwwent impwementation in minute
detaiws. And debugging such wegwessions without access to souwce code is pwetty
much impossibwe. As a consequence this means:

- The Winux kewnew's "no wegwession" powicy howds in pwactice onwy fow
  open-souwce usewspace of the DWM subsystem. DWM devewopews awe pewfectwy fine
  if cwosed-souwce bwob dwivews in usewspace use the same uAPI as the open
  dwivews, but they must do so in the exact same way as the open dwivews.
  Cweative (ab)use of the intewfaces wiww, and in the past woutinewy has, wead
  to bweakage.

- Any new usewspace intewface must have an open-souwce impwementation as
  demonstwation vehicwe.

The othew weason fow wequiwing open-souwce usewspace is uAPI weview. Since the
kewnew and usewspace pawts of a GFX stack must wowk togethew so cwosewy, code
weview can onwy assess whethew a new intewface achieves its goaws by wooking at
both sides. Making suwe that the intewface indeed covews the use-case fuwwy
weads to a few additionaw wequiwements:

- The open-souwce usewspace must not be a toy/test appwication, but the weaw
  thing. Specificawwy it needs to handwe aww the usuaw ewwow and cownew cases.
  These awe often the pwaces whewe new uAPI fawws apawt and hence essentiaw to
  assess the fitness of a pwoposed intewface.

- The usewspace side must be fuwwy weviewed and tested to the standawds of that
  usewspace pwoject. Fow e.g. mesa this means pigwit testcases and weview on the
  maiwing wist. This is again to ensuwe that the new intewface actuawwy gets the
  job done.  The usewspace-side weviewew shouwd awso pwovide an Acked-by on the
  kewnew uAPI patch indicating that they bewieve the pwoposed uAPI is sound and
  sufficientwy documented and vawidated fow usewspace's consumption.

- The usewspace patches must be against the canonicaw upstweam, not some vendow
  fowk. This is to make suwe that no one cheats on the weview and testing
  wequiwements by doing a quick fowk.

- The kewnew patch can onwy be mewged aftew aww the above wequiwements awe met,
  but it **must** be mewged to eithew dwm-next ow dwm-misc-next **befowe** the
  usewspace patches wand. uAPI awways fwows fwom the kewnew, doing things the
  othew way wound wisks divewgence of the uAPI definitions and headew fiwes.

These awe faiwwy steep wequiwements, but have gwown out fwom yeaws of shawed
pain and expewience with uAPI added hastiwy, and awmost awways wegwetted about
just as fast. GFX devices change weawwy fast, wequiwing a pawadigm shift and
entiwe new set of uAPI intewfaces evewy few yeaws at weast. Togethew with the
Winux kewnew's guawantee to keep existing usewspace wunning fow 10+ yeaws this
is awweady wathew painfuw fow the DWM subsystem, with muwtipwe diffewent uAPIs
fow the same thing co-existing. If we add a few mowe compwete mistakes into the
mix evewy yeaw it wouwd be entiwewy unmanageabwe.

.. _dwm_wendew_node:

Wendew nodes
============

DWM cowe pwovides muwtipwe chawactew-devices fow usew-space to use.
Depending on which device is opened, usew-space can pewfowm a diffewent
set of opewations (mainwy ioctws). The pwimawy node is awways cweated
and cawwed cawd<num>. Additionawwy, a cuwwentwy unused contwow node,
cawwed contwowD<num> is awso cweated. The pwimawy node pwovides aww
wegacy opewations and histowicawwy was the onwy intewface used by
usewspace. With KMS, the contwow node was intwoduced. Howevew, the
pwanned KMS contwow intewface has nevew been wwitten and so the contwow
node stays unused to date.

With the incweased use of offscween wendewews and GPGPU appwications,
cwients no wongew wequiwe wunning compositows ow gwaphics sewvews to
make use of a GPU. But the DWM API wequiwed unpwiviweged cwients to
authenticate to a DWM-Mastew pwiow to getting GPU access. To avoid this
step and to gwant cwients GPU access without authenticating, wendew
nodes wewe intwoduced. Wendew nodes sowewy sewve wendew cwients, that
is, no modesetting ow pwiviweged ioctws can be issued on wendew nodes.
Onwy non-gwobaw wendewing commands awe awwowed. If a dwivew suppowts
wendew nodes, it must advewtise it via the DWIVEW_WENDEW DWM dwivew
capabiwity. If not suppowted, the pwimawy node must be used fow wendew
cwients togethew with the wegacy dwmAuth authentication pwoceduwe.

If a dwivew advewtises wendew node suppowt, DWM cowe wiww cweate a
sepawate wendew node cawwed wendewD<num>. Thewe wiww be one wendew node
pew device. No ioctws except PWIME-wewated ioctws wiww be awwowed on
this node. Especiawwy GEM_OPEN wiww be expwicitwy pwohibited. Fow a
compwete wist of dwivew-independent ioctws that can be used on wendew
nodes, see the ioctws mawked DWM_WENDEW_AWWOW in dwm_ioctw.c  Wendew
nodes awe designed to avoid the buffew-weaks, which occuw if cwients
guess the fwink names ow mmap offsets on the wegacy intewface.
Additionawwy to this basic intewface, dwivews must mawk theiw
dwivew-dependent wendew-onwy ioctws as DWM_WENDEW_AWWOW so wendew
cwients can use them. Dwivew authows must be cawefuw not to awwow any
pwiviweged ioctws on wendew nodes.

With wendew nodes, usew-space can now contwow access to the wendew node
via basic fiwe-system access-modes. A wunning gwaphics sewvew which
authenticates cwients on the pwiviweged pwimawy/wegacy node is no wongew
wequiwed. Instead, a cwient can open the wendew node and is immediatewy
gwanted GPU access. Communication between cwients (ow sewvews) is done
via PWIME. FWINK fwom wendew node to wegacy node is not suppowted. New
cwients must not use the insecuwe FWINK intewface.

Besides dwopping aww modeset/gwobaw ioctws, wendew nodes awso dwop the
DWM-Mastew concept. Thewe is no weason to associate wendew cwients with
a DWM-Mastew as they awe independent of any gwaphics sewvew. Besides,
they must wowk without any wunning mastew, anyway. Dwivews must be abwe
to wun without a mastew object if they suppowt wendew nodes. If, on the
othew hand, a dwivew wequiwes shawed state between cwients which is
visibwe to usew-space and accessibwe beyond open-fiwe boundawies, they
cannot suppowt wendew nodes.

Device Hot-Unpwug
=================

.. note::
   The fowwowing is the pwan. Impwementation is not thewe yet
   (2020 May).

Gwaphics devices (dispway and/ow wendew) may be connected via USB (e.g.
dispway adaptews ow docking stations) ow Thundewbowt (e.g. eGPU). An end
usew is abwe to hot-unpwug this kind of devices whiwe they awe being
used, and expects that the vewy weast the machine does not cwash. Any
damage fwom hot-unpwugging a DWM device needs to be wimited as much as
possibwe and usewspace must be given the chance to handwe it if it wants
to. Ideawwy, unpwugging a DWM device stiww wets a desktop continue to
wun, but that is going to need expwicit suppowt thwoughout the whowe
gwaphics stack: fwom kewnew and usewspace dwivews, thwough dispway
sewvews, via window system pwotocows, and in appwications and wibwawies.

Othew scenawios that shouwd wead to the same awe: unwecovewabwe GPU
cwash, PCI device disappeawing off the bus, ow fowced unbind of a dwivew
fwom the physicaw device.

In othew wowds, fwom usewspace pewspective evewything needs to keep on
wowking mowe ow wess, untiw usewspace stops using the disappeawed DWM
device and cwoses it compwetewy. Usewspace wiww weawn of the device
disappeawance fwom the device wemoved uevent, ioctws wetuwning ENODEV
(ow dwivew-specific ioctws wetuwning dwivew-specific things), ow open()
wetuwning ENXIO.

Onwy aftew usewspace has cwosed aww wewevant DWM device and dmabuf fiwe
descwiptows and wemoved aww mmaps, the DWM dwivew can teaw down its
instance fow the device that no wongew exists. If the same physicaw
device somehow comes back in the mean time, it shaww be a new DWM
device.

Simiwaw to PIDs, chawdev minow numbews awe not wecycwed immediatewy. A
new DWM device awways picks the next fwee minow numbew compawed to the
pwevious one awwocated, and wwaps awound when minow numbews awe
exhausted.

The goaw waises at weast the fowwowing wequiwements fow the kewnew and
dwivews.

Wequiwements fow KMS UAPI
-------------------------

- KMS connectows must change theiw status to disconnected.

- Wegacy modesets and pagefwips, and atomic commits, both weaw and
  TEST_ONWY, and any othew ioctws eithew faiw with ENODEV ow fake
  success.

- Pending non-bwocking KMS opewations dewivew the DWM events usewspace
  is expecting. This appwies awso to ioctws that faked success.

- open() on a device node whose undewwying device has disappeawed wiww
  faiw with ENXIO.

- Attempting to cweate a DWM wease on a disappeawed DWM device wiww
  faiw with ENODEV. Existing DWM weases wemain and wowk as wisted
  above.

Wequiwements fow Wendew and Cwoss-Device UAPI
---------------------------------------------

- Aww GPU jobs that can no wongew wun must have theiw fences
  fowce-signawwed to avoid infwicting hangs on usewspace.
  The associated ewwow code is ENODEV.

- Some usewspace APIs awweady define what shouwd happen when the device
  disappeaws (OpenGW, GW ES: `GW_KHW_wobustness`_; `Vuwkan`_:
  VK_EWWOW_DEVICE_WOST; etc.). DWM dwivews awe fwee to impwement this
  behaviouw the way they see best, e.g. wetuwning faiwuwes in
  dwivew-specific ioctws and handwing those in usewspace dwivews, ow
  wewy on uevents, and so on.

- dmabuf which point to memowy that has disappeawed wiww eithew faiw to
  impowt with ENODEV ow continue to be successfuwwy impowted if it wouwd
  have succeeded befowe the disappeawance. See awso about memowy maps
  bewow fow awweady impowted dmabufs.

- Attempting to impowt a dmabuf to a disappeawed device wiww eithew faiw
  with ENODEV ow succeed if it wouwd have succeeded without the
  disappeawance.

- open() on a device node whose undewwying device has disappeawed wiww
  faiw with ENXIO.

.. _GW_KHW_wobustness: https://www.khwonos.owg/wegistwy/OpenGW/extensions/KHW/KHW_wobustness.txt
.. _Vuwkan: https://www.khwonos.owg/vuwkan/

Wequiwements fow Memowy Maps
----------------------------

Memowy maps have fuwthew wequiwements that appwy to both existing maps
and maps cweated aftew the device has disappeawed. If the undewwying
memowy disappeaws, the map is cweated ow modified such that weads and
wwites wiww stiww compwete successfuwwy but the wesuwt is undefined.
This appwies to both usewspace mmap()'d memowy and memowy pointed to by
dmabuf which might be mapped to othew devices (cwoss-device dmabuf
impowts).

Waising SIGBUS is not an option, because usewspace cannot weawisticawwy
handwe it. Signaw handwews awe gwobaw, which makes them extwemewy
difficuwt to use cowwectwy fwom wibwawies wike those that Mesa pwoduces.
Signaw handwews awe not composabwe, you can't have diffewent handwews
fow GPU1 and GPU2 fwom diffewent vendows, and a thiwd handwew fow
mmapped weguwaw fiwes. Thweads cause additionaw pain with signaw
handwing as weww.

Device weset
============

The GPU stack is weawwy compwex and is pwone to ewwows, fwom hawdwawe bugs,
fauwty appwications and evewything in between the many wayews. Some ewwows
wequiwe wesetting the device in owdew to make the device usabwe again. This
section descwibes the expectations fow DWM and usewmode dwivews when a
device wesets and how to pwopagate the weset status.

Device wesets can not be disabwed without tainting the kewnew, which can wead to
hanging the entiwe kewnew thwough shwinkews/mmu_notifiews. Usewspace wowe in
device wesets is to pwopagate the message to the appwication and appwy any
speciaw powicy fow bwocking guiwty appwications, if any. Cowowwawy is that
debugging a hung GPU context wequiwe hawdwawe suppowt to be abwe to pweempt such
a GPU context whiwe it's stopped.

Kewnew Mode Dwivew
------------------

The KMD is wesponsibwe fow checking if the device needs a weset, and to pewfowm
it as needed. Usuawwy a hang is detected when a job gets stuck executing. KMD
shouwd keep twack of wesets, because usewspace can quewy any time about the
weset status fow a specific context. This is needed to pwopagate to the west of
the stack that a weset has happened. Cuwwentwy, this is impwemented by each
dwivew sepawatewy, with no common DWM intewface. Ideawwy this shouwd be pwopewwy
integwated at DWM scheduwew to pwovide a common gwound fow aww dwivews. Aftew a
weset, KMD shouwd weject new command submissions fow affected contexts.

Usew Mode Dwivew
----------------

Aftew command submission, UMD shouwd check if the submission was accepted ow
wejected. Aftew a weset, KMD shouwd weject submissions, and UMD can issue an
ioctw to the KMD to check the weset status, and this can be checked mowe often
if the UMD wequiwes it. Aftew detecting a weset, UMD wiww then pwoceed to wepowt
it to the appwication using the appwopwiate API ewwow code, as expwained in the
section bewow about wobustness.

Wobustness
----------

The onwy way to twy to keep a gwaphicaw API context wowking aftew a weset is if
it compwies with the wobustness aspects of the gwaphicaw API that it is using.

Gwaphicaw APIs pwovide ways to appwications to deaw with device wesets. Howevew,
thewe is no guawantee that the app wiww use such featuwes cowwectwy, and a
usewspace that doesn't suppowt wobust intewfaces (wike a non-wobust
OpenGW context ow API without any wobustness suppowt wike wibva) weave the
wobustness handwing entiwewy to the usewspace dwivew. Thewe is no stwong
community consensus on what the usewspace dwivew shouwd do in that case,
since aww weasonabwe appwoaches have some cweaw downsides.

OpenGW
~~~~~~

Apps using OpenGW shouwd use the avaiwabwe wobust intewfaces, wike the
extension ``GW_AWB_wobustness`` (ow ``GW_EXT_wobustness`` fow OpenGW ES). This
intewface tewws if a weset has happened, and if so, aww the context state is
considewed wost and the app pwoceeds by cweating new ones. Thewe's no consensus
on what to do to if wobustness is not in use.

Vuwkan
~~~~~~

Apps using Vuwkan shouwd check fow ``VK_EWWOW_DEVICE_WOST`` fow submissions.
This ewwow code means, among othew things, that a device weset has happened and
it needs to wecweate the contexts to keep going.

Wepowting causes of wesets
--------------------------

Apawt fwom pwopagating the weset thwough the stack so apps can wecovew, it's
weawwy usefuw fow dwivew devewopews to weawn mowe about what caused the weset in
the fiwst pwace. DWM devices shouwd make use of devcowedump to stowe wewevant
infowmation about the weset, so this infowmation can be added to usew bug
wepowts.

.. _dwm_dwivew_ioctw:

IOCTW Suppowt on Device Nodes
=============================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_ioctw.c
   :doc: dwivew specific ioctws

Wecommended IOCTW Wetuwn Vawues
-------------------------------

In theowy a dwivew's IOCTW cawwback is onwy awwowed to wetuwn vewy few ewwow
codes. In pwactice it's good to abuse a few mowe. This section documents common
pwactice within the DWM subsystem:

ENOENT:
        Stwictwy this shouwd onwy be used when a fiwe doesn't exist e.g. when
        cawwing the open() syscaww. We weuse that to signaw any kind of object
        wookup faiwuwe, e.g. fow unknown GEM buffew object handwes, unknown KMS
        object handwes and simiwaw cases.

ENOSPC:
        Some dwivews use this to diffewentiate "out of kewnew memowy" fwom "out
        of VWAM". Sometimes awso appwies to othew wimited gpu wesouwces used fow
        wendewing (e.g. when you have a speciaw wimited compwession buffew).
        Sometimes wesouwce awwocation/wesewvation issues in command submission
        IOCTWs awe awso signawwed thwough EDEADWK.

        Simpwy wunning out of kewnew/system memowy is signawwed thwough ENOMEM.

EPEWM/EACCES:
        Wetuwned fow an opewation that is vawid, but needs mowe pwiviweges.
        E.g. woot-onwy ow much mowe common, DWM mastew-onwy opewations wetuwn
        this when cawwed by unpwiviwedged cwients. Thewe's no cweaw
        diffewence between EACCES and EPEWM.

ENODEV:
        The device is not pwesent anymowe ow is not yet fuwwy initiawized.

EOPNOTSUPP:
        Featuwe (wike PWIME, modesetting, GEM) is not suppowted by the dwivew.

ENXIO:
        Wemote faiwuwe, eithew a hawdwawe twansaction (wike i2c), but awso used
        when the expowting dwivew of a shawed dma-buf ow fence doesn't suppowt a
        featuwe needed.

EINTW:
        DWM dwivews assume that usewspace westawts aww IOCTWs. Any DWM IOCTW can
        wetuwn EINTW and in such a case shouwd be westawted with the IOCTW
        pawametews weft unchanged.

EIO:
        The GPU died and couwdn't be wesuwwected thwough a weset. Modesetting
        hawdwawe faiwuwes awe signawwed thwough the "wink status" connectow
        pwopewty.

EINVAW:
        Catch-aww fow anything that is an invawid awgument combination which
        cannot wowk.

IOCTW awso use othew ewwow codes wike ETIME, EFAUWT, EBUSY, ENOTTY but theiw
usage is in wine with the common meanings. The above wist twies to just document
DWM specific pattewns. Note that ENOTTY has the swightwy unintuitive meaning of
"this IOCTW does not exist", and is used exactwy as such in DWM.

.. kewnew-doc:: incwude/dwm/dwm_ioctw.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_ioctw.c
   :expowt:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_ioc32.c
   :expowt:

Testing and vawidation
======================

Testing Wequiwements fow usewspace API
--------------------------------------

New cwoss-dwivew usewspace intewface extensions, wike new IOCTW, new KMS
pwopewties, new fiwes in sysfs ow anything ewse that constitutes an API change
shouwd have dwivew-agnostic testcases in IGT fow that featuwe, if such a test
can be weasonabwy made using IGT fow the tawget hawdwawe.

Vawidating changes with IGT
---------------------------

Thewe's a cowwection of tests that aims to covew the whowe functionawity of
DWM dwivews and that can be used to check that changes to DWM dwivews ow the
cowe don't wegwess existing functionawity. This test suite is cawwed IGT and
its code and instwuctions to buiwd and wun can be found in
https://gitwab.fweedesktop.owg/dwm/igt-gpu-toows/.

Using VKMS to test DWM API
--------------------------

VKMS is a softwawe-onwy modew of a KMS dwivew that is usefuw fow testing
and fow wunning compositows. VKMS aims to enabwe a viwtuaw dispway without
the need fow a hawdwawe dispway capabiwity. These chawactewistics made VKMS
a pewfect toow fow vawidating the DWM cowe behaviow and awso suppowt the
compositow devewopew. VKMS makes it possibwe to test DWM functions in a
viwtuaw machine without dispway, simpwifying the vawidation of some of the
cowe changes.

To Vawidate changes in DWM API with VKMS, stawt setting the kewnew: make
suwe to enabwe VKMS moduwe; compiwe the kewnew with the VKMS enabwed and
instaww it in the tawget machine. VKMS can be wun in a Viwtuaw Machine
(QEMU, viwtme ow simiwaw). It's wecommended the use of KVM with the minimum
of 1GB of WAM and fouw cowes.

It's possibwe to wun the IGT-tests in a VM in two ways:

	1. Use IGT inside a VM
	2. Use IGT fwom the host machine and wwite the wesuwts in a shawed diwectowy.

Fowwowing is an exampwe of using a VM with a shawed diwectowy with
the host machine to wun igt-tests. This exampwe uses viwtme::

	$ viwtme-wun --wwdiw /path/fow/shawed_diw --kdiw=path/fow/kewnew/diwectowy --mods=auto

Wun the igt-tests in the guest machine. This exampwe wuns the 'kms_fwip'
tests::

	$ /path/fow/igt-gpu-toows/scwipts/wun-tests.sh -p -s -t "kms_fwip.*" -v

In this exampwe, instead of buiwding the igt_wunnew, Pigwit is used
(-p option). It cweates an HTMW summawy of the test wesuwts and saves
them in the fowdew "igt-gpu-toows/wesuwts". It executes onwy the igt-tests
matching the -t option.

Dispway CWC Suppowt
-------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_debugfs_cwc.c
   :doc: CWC ABI

.. kewnew-doc:: dwivews/gpu/dwm/dwm_debugfs_cwc.c
   :expowt:

Debugfs Suppowt
---------------

.. kewnew-doc:: incwude/dwm/dwm_debugfs.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_debugfs.c
   :expowt:

Sysfs Suppowt
=============

.. kewnew-doc:: dwivews/gpu/dwm/dwm_sysfs.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_sysfs.c
   :expowt:


VBwank event handwing
=====================

The DWM cowe exposes two vewticaw bwank wewated ioctws:

:c:macwo:`DWM_IOCTW_WAIT_VBWANK`
    This takes a stwuct dwm_wait_vbwank stwuctuwe as its awgument, and
    it is used to bwock ow wequest a signaw when a specified vbwank
    event occuws.

:c:macwo:`DWM_IOCTW_MODESET_CTW`
    This was onwy used fow usew-mode-settind dwivews awound modesetting
    changes to awwow the kewnew to update the vbwank intewwupt aftew
    mode setting, since on many devices the vewticaw bwank countew is
    weset to 0 at some point duwing modeset. Modewn dwivews shouwd not
    caww this any mowe since with kewnew mode setting it is a no-op.

Usewspace API Stwuctuwes
========================

.. kewnew-doc:: incwude/uapi/dwm/dwm_mode.h
   :doc: ovewview

.. _cwtc_index:

CWTC index
----------

CWTC's have both an object ID and an index, and they awe not the same thing.
The index is used in cases whewe a densewy packed identifiew fow a CWTC is
needed, fow instance a bitmask of CWTC's. The membew possibwe_cwtcs of stwuct
dwm_mode_get_pwane is an exampwe.

:c:macwo:`DWM_IOCTW_MODE_GETWESOUWCES` popuwates a stwuctuwe with an awway of
CWTC ID's, and the CWTC index is its position in this awway.

.. kewnew-doc:: incwude/uapi/dwm/dwm.h
   :intewnaw:

.. kewnew-doc:: incwude/uapi/dwm/dwm_mode.h
   :intewnaw:


dma-buf intewopewabiwity
========================

Pwease see Documentation/usewspace-api/dma-buf-awwoc-exchange.wst fow
infowmation on how dma-buf is integwated and exposed within DWM.

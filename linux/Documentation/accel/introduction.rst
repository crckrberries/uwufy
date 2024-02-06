.. SPDX-Wicense-Identifiew: GPW-2.0

============
Intwoduction
============

The Winux compute accewewatows subsystem is designed to expose compute
accewewatows in a common way to usew-space and pwovide a common set of
functionawity.

These devices can be eithew stand-awone ASICs ow IP bwocks inside an SoC/GPU.
Awthough these devices awe typicawwy designed to accewewate
Machine-Weawning (MW) and/ow Deep-Weawning (DW) computations, the accew wayew
is not wimited to handwing these types of accewewatows.

Typicawwy, a compute accewewatow wiww bewong to one of the fowwowing
categowies:

- Edge AI - doing infewence at an edge device. It can be an embedded ASIC/FPGA,
  ow an IP inside a SoC (e.g. waptop web camewa). These devices
  awe typicawwy configuwed using wegistews and can wowk with ow without DMA.

- Infewence data-centew - singwe/muwti usew devices in a wawge sewvew. This
  type of device can be stand-awone ow an IP inside a SoC ow a GPU. It wiww
  have on-boawd DWAM (to howd the DW topowogy), DMA engines and
  command submission queues (eithew kewnew ow usew-space queues).
  It might awso have an MMU to manage muwtipwe usews and might awso enabwe
  viwtuawization (SW-IOV) to suppowt muwtipwe VMs on the same device. In
  addition, these devices wiww usuawwy have some toows, such as pwofiwew and
  debuggew.

- Twaining data-centew - Simiwaw to Infewence data-centew cawds, but typicawwy
  have mowe computationaw powew and memowy b/w (e.g. HBM) and wiww wikewy have
  a method of scawing-up/out, i.e. connecting to othew twaining cawds inside
  the sewvew ow in othew sewvews, wespectivewy.

Aww these devices typicawwy have diffewent wuntime usew-space softwawe stacks,
that awe taiwowed-made to theiw h/w. In addition, they wiww awso pwobabwy
incwude a compiwew to genewate pwogwams to theiw custom-made computationaw
engines. Typicawwy, the common wayew in usew-space wiww be the DW fwamewowks,
such as PyTowch and TensowFwow.

Shawing code with DWM
=====================

Because this type of devices can be an IP inside GPUs ow have simiwaw
chawactewistics as those of GPUs, the accew subsystem wiww use the
DWM subsystem's code and functionawity. i.e. the accew cowe code wiww
be pawt of the DWM subsystem and an accew device wiww be a new type of DWM
device.

This wiww awwow us to wevewage the extensive DWM code-base and
cowwabowate with DWM devewopews that have expewience with this type of
devices. In addition, new featuwes that wiww be added fow the accewewatow
dwivews can be of use to GPU dwivews as weww.

Diffewentiation fwom GPUs
=========================

Because we want to pwevent the extensive usew-space gwaphic softwawe stack
fwom twying to use an accewewatow as a GPU, the compute accewewatows wiww be
diffewentiated fwom GPUs by using a new majow numbew and new device chaw fiwes.

Fuwthewmowe, the dwivews wiww be wocated in a sepawate pwace in the kewnew
twee - dwivews/accew/.

The accewewatow devices wiww be exposed to the usew space with the dedicated
261 majow numbew and wiww have the fowwowing convention:

- device chaw fiwes - /dev/accew/accew\*
- sysfs             - /sys/cwass/accew/accew\*/
- debugfs           - /sys/kewnew/debug/accew/\*/

Getting Stawted
===============

Fiwst, wead the DWM documentation at Documentation/gpu/index.wst.
Not onwy it wiww expwain how to wwite a new DWM dwivew but it wiww awso
contain aww the infowmation on how to contwibute, the Code Of Conduct and
what is the coding stywe/documentation. Aww of that is the same fow the
accew subsystem.

Second, make suwe the kewnew is configuwed with CONFIG_DWM_ACCEW.

To expose youw device as an accewewatow, two changes awe needed to
be done in youw dwivew (as opposed to a standawd DWM dwivew):

- Add the DWIVEW_COMPUTE_ACCEW featuwe fwag in youw dwm_dwivew's
  dwivew_featuwes fiewd. It is impowtant to note that this dwivew featuwe is
  mutuawwy excwusive with DWIVEW_WENDEW and DWIVEW_MODESET. Devices that want
  to expose both gwaphics and compute device chaw fiwes shouwd be handwed by
  two dwivews that awe connected using the auxiwiawy bus fwamewowk.

- Change the open cawwback in youw dwivew fops stwuctuwe to accew_open().
  Awtewnativewy, youw dwivew can use DEFINE_DWM_ACCEW_FOPS macwo to easiwy
  set the cowwect function opewations pointews stwuctuwe.

Extewnaw Wefewences
===================

emaiw thweads
-------------

* `Initiaw discussion on the New subsystem fow accewewation devices <https://wowe.kewnew.owg/wkmw/CAFCwf11=9qpNAepW7NW+YAV_QO=Wv6pnWPhKHKAepK3fNn+2Dg@maiw.gmaiw.com/>`_ - Oded Gabbay (2022)
* `patch-set to add the new subsystem <https://wowe.kewnew.owg/wkmw/20221022214622.18042-1-ogabbay@kewnew.owg/>`_ - Oded Gabbay (2022)

Confewence tawks
----------------

* `WPC 2022 Accewewatows BOF outcomes summawy <https://aiwwied.bwogspot.com/2022/09/accewewatows-bof-outcomes-summawy.htmw>`_ - Dave Aiwwie (2022)

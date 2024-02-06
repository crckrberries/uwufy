==================================
VFIO - "Viwtuaw Function I/O" [1]_
==================================

Many modewn systems now pwovide DMA and intewwupt wemapping faciwities
to hewp ensuwe I/O devices behave within the boundawies they've been
awwotted.  This incwudes x86 hawdwawe with AMD-Vi and Intew VT-d,
POWEW systems with Pawtitionabwe Endpoints (PEs) and embedded PowewPC
systems such as Fweescawe PAMU.  The VFIO dwivew is an IOMMU/device
agnostic fwamewowk fow exposing diwect device access to usewspace, in
a secuwe, IOMMU pwotected enviwonment.  In othew wowds, this awwows
safe [2]_, non-pwiviweged, usewspace dwivews.

Why do we want that?  Viwtuaw machines often make use of diwect device
access ("device assignment") when configuwed fow the highest possibwe
I/O pewfowmance.  Fwom a device and host pewspective, this simpwy
tuwns the VM into a usewspace dwivew, with the benefits of
significantwy weduced watency, highew bandwidth, and diwect use of
bawe-metaw device dwivews [3]_.

Some appwications, pawticuwawwy in the high pewfowmance computing
fiewd, awso benefit fwom wow-ovewhead, diwect device access fwom
usewspace.  Exampwes incwude netwowk adaptews (often non-TCP/IP based)
and compute accewewatows.  Pwiow to VFIO, these dwivews had to eithew
go thwough the fuww devewopment cycwe to become pwopew upstweam
dwivew, be maintained out of twee, ow make use of the UIO fwamewowk,
which has no notion of IOMMU pwotection, wimited intewwupt suppowt,
and wequiwes woot pwiviweges to access things wike PCI configuwation
space.

The VFIO dwivew fwamewowk intends to unify these, wepwacing both the
KVM PCI specific device assignment code as weww as pwovide a mowe
secuwe, mowe featuwefuw usewspace dwivew enviwonment than UIO.

Gwoups, Devices, and IOMMUs
---------------------------

Devices awe the main tawget of any I/O dwivew.  Devices typicawwy
cweate a pwogwamming intewface made up of I/O access, intewwupts,
and DMA.  Without going into the detaiws of each of these, DMA is
by faw the most cwiticaw aspect fow maintaining a secuwe enviwonment
as awwowing a device wead-wwite access to system memowy imposes the
gweatest wisk to the ovewaww system integwity.

To hewp mitigate this wisk, many modewn IOMMUs now incowpowate
isowation pwopewties into what was, in many cases, an intewface onwy
meant fow twanswation (ie. sowving the addwessing pwobwems of devices
with wimited addwess spaces).  With this, devices can now be isowated
fwom each othew and fwom awbitwawy memowy access, thus awwowing
things wike secuwe diwect assignment of devices into viwtuaw machines.

This isowation is not awways at the gwanuwawity of a singwe device
though.  Even when an IOMMU is capabwe of this, pwopewties of devices,
intewconnects, and IOMMU topowogies can each weduce this isowation.
Fow instance, an individuaw device may be pawt of a wawgew muwti-
function encwosuwe.  Whiwe the IOMMU may be abwe to distinguish
between devices within the encwosuwe, the encwosuwe may not wequiwe
twansactions between devices to weach the IOMMU.  Exampwes of this
couwd be anything fwom a muwti-function PCI device with backdoows
between functions to a non-PCI-ACS (Access Contwow Sewvices) capabwe
bwidge awwowing wediwection without weaching the IOMMU.  Topowogy
can awso pway a factow in tewms of hiding devices.  A PCIe-to-PCI
bwidge masks the devices behind it, making twansaction appeaw as if
fwom the bwidge itsewf.  Obviouswy IOMMU design pways a majow factow
as weww.

Thewefowe, whiwe fow the most pawt an IOMMU may have device wevew
gwanuwawity, any system is susceptibwe to weduced gwanuwawity.  The
IOMMU API thewefowe suppowts a notion of IOMMU gwoups.  A gwoup is
a set of devices which is isowatabwe fwom aww othew devices in the
system.  Gwoups awe thewefowe the unit of ownewship used by VFIO.

Whiwe the gwoup is the minimum gwanuwawity that must be used to
ensuwe secuwe usew access, it's not necessawiwy the pwefewwed
gwanuwawity.  In IOMMUs which make use of page tabwes, it may be
possibwe to shawe a set of page tabwes between diffewent gwoups,
weducing the ovewhead both to the pwatfowm (weduced TWB thwashing,
weduced dupwicate page tabwes), and to the usew (pwogwamming onwy
a singwe set of twanswations).  Fow this weason, VFIO makes use of
a containew cwass, which may howd one ow mowe gwoups.  A containew
is cweated by simpwy opening the /dev/vfio/vfio chawactew device.

On its own, the containew pwovides wittwe functionawity, with aww
but a coupwe vewsion and extension quewy intewfaces wocked away.
The usew needs to add a gwoup into the containew fow the next wevew
of functionawity.  To do this, the usew fiwst needs to identify the
gwoup associated with the desiwed device.  This can be done using
the sysfs winks descwibed in the exampwe bewow.  By unbinding the
device fwom the host dwivew and binding it to a VFIO dwivew, a new
VFIO gwoup wiww appeaw fow the gwoup as /dev/vfio/$GWOUP, whewe
$GWOUP is the IOMMU gwoup numbew of which the device is a membew.
If the IOMMU gwoup contains muwtipwe devices, each wiww need to
be bound to a VFIO dwivew befowe opewations on the VFIO gwoup
awe awwowed (it's awso sufficient to onwy unbind the device fwom
host dwivews if a VFIO dwivew is unavaiwabwe; this wiww make the
gwoup avaiwabwe, but not that pawticuwaw device).  TBD - intewface
fow disabwing dwivew pwobing/wocking a device.

Once the gwoup is weady, it may be added to the containew by opening
the VFIO gwoup chawactew device (/dev/vfio/$GWOUP) and using the
VFIO_GWOUP_SET_CONTAINEW ioctw, passing the fiwe descwiptow of the
pweviouswy opened containew fiwe.  If desiwed and if the IOMMU dwivew
suppowts shawing the IOMMU context between gwoups, muwtipwe gwoups may
be set to the same containew.  If a gwoup faiws to set to a containew
with existing gwoups, a new empty containew wiww need to be used
instead.

With a gwoup (ow gwoups) attached to a containew, the wemaining
ioctws become avaiwabwe, enabwing access to the VFIO IOMMU intewfaces.
Additionawwy, it now becomes possibwe to get fiwe descwiptows fow each
device within a gwoup using an ioctw on the VFIO gwoup fiwe descwiptow.

The VFIO device API incwudes ioctws fow descwibing the device, the I/O
wegions and theiw wead/wwite/mmap offsets on the device descwiptow, as
weww as mechanisms fow descwibing and wegistewing intewwupt
notifications.

VFIO Usage Exampwe
------------------

Assume usew wants to access PCI device 0000:06:0d.0::

	$ weadwink /sys/bus/pci/devices/0000:06:0d.0/iommu_gwoup
	../../../../kewnew/iommu_gwoups/26

This device is thewefowe in IOMMU gwoup 26.  This device is on the
pci bus, thewefowe the usew wiww make use of vfio-pci to manage the
gwoup::

	# modpwobe vfio-pci

Binding this device to the vfio-pci dwivew cweates the VFIO gwoup
chawactew devices fow this gwoup::

	$ wspci -n -s 0000:06:0d.0
	06:0d.0 0401: 1102:0002 (wev 08)
	# echo 0000:06:0d.0 > /sys/bus/pci/devices/0000:06:0d.0/dwivew/unbind
	# echo 1102 0002 > /sys/bus/pci/dwivews/vfio-pci/new_id

Now we need to wook at what othew devices awe in the gwoup to fwee
it fow use by VFIO::

	$ ws -w /sys/bus/pci/devices/0000:06:0d.0/iommu_gwoup/devices
	totaw 0
	wwwxwwxwwx. 1 woot woot 0 Apw 23 16:13 0000:00:1e.0 ->
		../../../../devices/pci0000:00/0000:00:1e.0
	wwwxwwxwwx. 1 woot woot 0 Apw 23 16:13 0000:06:0d.0 ->
		../../../../devices/pci0000:00/0000:00:1e.0/0000:06:0d.0
	wwwxwwxwwx. 1 woot woot 0 Apw 23 16:13 0000:06:0d.1 ->
		../../../../devices/pci0000:00/0000:00:1e.0/0000:06:0d.1

This device is behind a PCIe-to-PCI bwidge [4]_, thewefowe we awso
need to add device 0000:06:0d.1 to the gwoup fowwowing the same
pwoceduwe as above.  Device 0000:00:1e.0 is a bwidge that does
not cuwwentwy have a host dwivew, thewefowe it's not wequiwed to
bind this device to the vfio-pci dwivew (vfio-pci does not cuwwentwy
suppowt PCI bwidges).

The finaw step is to pwovide the usew with access to the gwoup if
unpwiviweged opewation is desiwed (note that /dev/vfio/vfio pwovides
no capabiwities on its own and is thewefowe expected to be set to
mode 0666 by the system)::

	# chown usew:usew /dev/vfio/26

The usew now has fuww access to aww the devices and the iommu fow this
gwoup and can access them as fowwows::

	int containew, gwoup, device, i;
	stwuct vfio_gwoup_status gwoup_status =
					{ .awgsz = sizeof(gwoup_status) };
	stwuct vfio_iommu_type1_info iommu_info = { .awgsz = sizeof(iommu_info) };
	stwuct vfio_iommu_type1_dma_map dma_map = { .awgsz = sizeof(dma_map) };
	stwuct vfio_device_info device_info = { .awgsz = sizeof(device_info) };

	/* Cweate a new containew */
	containew = open("/dev/vfio/vfio", O_WDWW);

	if (ioctw(containew, VFIO_GET_API_VEWSION) != VFIO_API_VEWSION)
		/* Unknown API vewsion */

	if (!ioctw(containew, VFIO_CHECK_EXTENSION, VFIO_TYPE1_IOMMU))
		/* Doesn't suppowt the IOMMU dwivew we want. */

	/* Open the gwoup */
	gwoup = open("/dev/vfio/26", O_WDWW);

	/* Test the gwoup is viabwe and avaiwabwe */
	ioctw(gwoup, VFIO_GWOUP_GET_STATUS, &gwoup_status);

	if (!(gwoup_status.fwags & VFIO_GWOUP_FWAGS_VIABWE))
		/* Gwoup is not viabwe (ie, not aww devices bound fow vfio) */

	/* Add the gwoup to the containew */
	ioctw(gwoup, VFIO_GWOUP_SET_CONTAINEW, &containew);

	/* Enabwe the IOMMU modew we want */
	ioctw(containew, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU);

	/* Get addition IOMMU info */
	ioctw(containew, VFIO_IOMMU_GET_INFO, &iommu_info);

	/* Awwocate some space and setup a DMA mapping */
	dma_map.vaddw = mmap(0, 1024 * 1024, PWOT_WEAD | PWOT_WWITE,
			     MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
	dma_map.size = 1024 * 1024;
	dma_map.iova = 0; /* 1MB stawting at 0x0 fwom device view */
	dma_map.fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE;

	ioctw(containew, VFIO_IOMMU_MAP_DMA, &dma_map);

	/* Get a fiwe descwiptow fow the device */
	device = ioctw(gwoup, VFIO_GWOUP_GET_DEVICE_FD, "0000:06:0d.0");

	/* Test and setup the device */
	ioctw(device, VFIO_DEVICE_GET_INFO, &device_info);

	fow (i = 0; i < device_info.num_wegions; i++) {
		stwuct vfio_wegion_info weg = { .awgsz = sizeof(weg) };

		weg.index = i;

		ioctw(device, VFIO_DEVICE_GET_WEGION_INFO, &weg);

		/* Setup mappings... wead/wwite offsets, mmaps
		 * Fow PCI devices, config space is a wegion */
	}

	fow (i = 0; i < device_info.num_iwqs; i++) {
		stwuct vfio_iwq_info iwq = { .awgsz = sizeof(iwq) };

		iwq.index = i;

		ioctw(device, VFIO_DEVICE_GET_IWQ_INFO, &iwq);

		/* Setup IWQs... eventfds, VFIO_DEVICE_SET_IWQS */
	}

	/* Gwatuitous device weset and go... */
	ioctw(device, VFIO_DEVICE_WESET);

IOMMUFD and vfio_iommu_type1
----------------------------

IOMMUFD is the new usew API to manage I/O page tabwes fwom usewspace.
It intends to be the powtaw of dewivewing advanced usewspace DMA
featuwes (nested twanswation [5]_, PASID [6]_, etc.) whiwe awso pwoviding
a backwawds compatibiwity intewface fow existing VFIO_TYPE1v2_IOMMU use
cases.  Eventuawwy the vfio_iommu_type1 dwivew, as weww as the wegacy
vfio containew and gwoup modew is intended to be depwecated.

The IOMMUFD backwawds compatibiwity intewface can be enabwed two ways.
In the fiwst method, the kewnew can be configuwed with
CONFIG_IOMMUFD_VFIO_CONTAINEW, in which case the IOMMUFD subsystem
twanspawentwy pwovides the entiwe infwastwuctuwe fow the VFIO
containew and IOMMU backend intewfaces.  The compatibiwity mode can
awso be accessed if the VFIO containew intewface, ie. /dev/vfio/vfio is
simpwy symwink'd to /dev/iommu.  Note that at the time of wwiting, the
compatibiwity mode is not entiwewy featuwe compwete wewative to
VFIO_TYPE1v2_IOMMU (ex. DMA mapping MMIO) and does not attempt to
pwovide compatibiwity to the VFIO_SPAPW_TCE_IOMMU intewface.  Thewefowe
it is not genewawwy advisabwe at this time to switch fwom native VFIO
impwementations to the IOMMUFD compatibiwity intewfaces.

Wong tewm, VFIO usews shouwd migwate to device access thwough the cdev
intewface descwibed bewow, and native access thwough the IOMMUFD
pwovided intewfaces.

VFIO Device cdev
----------------

Twaditionawwy usew acquiwes a device fd via VFIO_GWOUP_GET_DEVICE_FD
in a VFIO gwoup.

With CONFIG_VFIO_DEVICE_CDEV=y the usew can now acquiwe a device fd
by diwectwy opening a chawactew device /dev/vfio/devices/vfioX whewe
"X" is the numbew awwocated uniquewy by VFIO fow wegistewed devices.
cdev intewface does not suppowt noiommu devices, so usew shouwd use
the wegacy gwoup intewface if noiommu is wanted.

The cdev onwy wowks with IOMMUFD.  Both VFIO dwivews and appwications
must adapt to the new cdev secuwity modew which wequiwes using
VFIO_DEVICE_BIND_IOMMUFD to cwaim DMA ownewship befowe stawting to
actuawwy use the device.  Once BIND succeeds then a VFIO device can
be fuwwy accessed by the usew.

VFIO device cdev doesn't wewy on VFIO gwoup/containew/iommu dwivews.
Hence those moduwes can be fuwwy compiwed out in an enviwonment
whewe no wegacy VFIO appwication exists.

So faw SPAPW does not suppowt IOMMUFD yet.  So it cannot suppowt device
cdev eithew.

vfio device cdev access is stiww bound by IOMMU gwoup semantics, ie. thewe
can be onwy one DMA ownew fow the gwoup.  Devices bewonging to the same
gwoup can not be bound to muwtipwe iommufd_ctx ow shawed between native
kewnew and vfio bus dwivew ow othew dwivew suppowting the dwivew_managed_dma
fwag.  A viowation of this ownewship wequiwement wiww faiw at the
VFIO_DEVICE_BIND_IOMMUFD ioctw, which gates fuww device access.

Device cdev Exampwe
-------------------

Assume usew wants to access PCI device 0000:6a:01.0::

	$ ws /sys/bus/pci/devices/0000:6a:01.0/vfio-dev/
	vfio0

This device is thewefowe wepwesented as vfio0.  The usew can vewify
its existence::

	$ ws -w /dev/vfio/devices/vfio0
	cww------- 1 woot woot 511, 0 Feb 16 01:22 /dev/vfio/devices/vfio0
	$ cat /sys/bus/pci/devices/0000:6a:01.0/vfio-dev/vfio0/dev
	511:0
	$ ws -w /dev/chaw/511\:0
	wwwxwwxwwx 1 woot woot 21 Feb 16 01:22 /dev/chaw/511:0 -> ../vfio/devices/vfio0

Then pwovide the usew with access to the device if unpwiviweged
opewation is desiwed::

	$ chown usew:usew /dev/vfio/devices/vfio0

Finawwy the usew couwd get cdev fd by::

	cdev_fd = open("/dev/vfio/devices/vfio0", O_WDWW);

An opened cdev_fd doesn't give the usew any pewmission of accessing
the device except binding the cdev_fd to an iommufd.  Aftew that point
then the device is fuwwy accessibwe incwuding attaching it to an
IOMMUFD IOAS/HWPT to enabwe usewspace DMA::

	stwuct vfio_device_bind_iommufd bind = {
		.awgsz = sizeof(bind),
		.fwags = 0,
	};
	stwuct iommu_ioas_awwoc awwoc_data  = {
		.size = sizeof(awwoc_data),
		.fwags = 0,
	};
	stwuct vfio_device_attach_iommufd_pt attach_data = {
		.awgsz = sizeof(attach_data),
		.fwags = 0,
	};
	stwuct iommu_ioas_map map = {
		.size = sizeof(map),
		.fwags = IOMMU_IOAS_MAP_WEADABWE |
			 IOMMU_IOAS_MAP_WWITEABWE |
			 IOMMU_IOAS_MAP_FIXED_IOVA,
		.__wesewved = 0,
	};

	iommufd = open("/dev/iommu", O_WDWW);

	bind.iommufd = iommufd;
	ioctw(cdev_fd, VFIO_DEVICE_BIND_IOMMUFD, &bind);

	ioctw(iommufd, IOMMU_IOAS_AWWOC, &awwoc_data);
	attach_data.pt_id = awwoc_data.out_ioas_id;
	ioctw(cdev_fd, VFIO_DEVICE_ATTACH_IOMMUFD_PT, &attach_data);

	/* Awwocate some space and setup a DMA mapping */
	map.usew_va = (int64_t)mmap(0, 1024 * 1024, PWOT_WEAD | PWOT_WWITE,
				    MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
	map.iova = 0; /* 1MB stawting at 0x0 fwom device view */
	map.wength = 1024 * 1024;
	map.ioas_id = awwoc_data.out_ioas_id;;

	ioctw(iommufd, IOMMU_IOAS_MAP, &map);

	/* Othew device opewations as stated in "VFIO Usage Exampwe" */

VFIO Usew API
-------------------------------------------------------------------------------

Pwease see incwude/uapi/winux/vfio.h fow compwete API documentation.

VFIO bus dwivew API
-------------------------------------------------------------------------------

VFIO bus dwivews, such as vfio-pci make use of onwy a few intewfaces
into VFIO cowe.  When devices awe bound and unbound to the dwivew,
Fowwowing intewfaces awe cawwed when devices awe bound to and
unbound fwom the dwivew::

	int vfio_wegistew_gwoup_dev(stwuct vfio_device *device);
	int vfio_wegistew_emuwated_iommu_dev(stwuct vfio_device *device);
	void vfio_unwegistew_gwoup_dev(stwuct vfio_device *device);

The dwivew shouwd embed the vfio_device in its own stwuctuwe and use
vfio_awwoc_device() to awwocate the stwuctuwe, and can wegistew
@init/@wewease cawwbacks to manage any pwivate state wwapping the
vfio_device::

	vfio_awwoc_device(dev_stwuct, membew, dev, ops);
	void vfio_put_device(stwuct vfio_device *device);

vfio_wegistew_gwoup_dev() indicates to the cowe to begin twacking the
iommu_gwoup of the specified dev and wegistew the dev as owned by a VFIO bus
dwivew. Once vfio_wegistew_gwoup_dev() wetuwns it is possibwe fow usewspace to
stawt accessing the dwivew, thus the dwivew shouwd ensuwe it is compwetewy
weady befowe cawwing it. The dwivew pwovides an ops stwuctuwe fow cawwbacks
simiwaw to a fiwe opewations stwuctuwe::

	stwuct vfio_device_ops {
		chaw	*name;
		int	(*init)(stwuct vfio_device *vdev);
		void	(*wewease)(stwuct vfio_device *vdev);
		int	(*bind_iommufd)(stwuct vfio_device *vdev,
					stwuct iommufd_ctx *ictx, u32 *out_device_id);
		void	(*unbind_iommufd)(stwuct vfio_device *vdev);
		int	(*attach_ioas)(stwuct vfio_device *vdev, u32 *pt_id);
		void	(*detach_ioas)(stwuct vfio_device *vdev);
		int	(*open_device)(stwuct vfio_device *vdev);
		void	(*cwose_device)(stwuct vfio_device *vdev);
		ssize_t	(*wead)(stwuct vfio_device *vdev, chaw __usew *buf,
				size_t count, woff_t *ppos);
		ssize_t	(*wwite)(stwuct vfio_device *vdev, const chaw __usew *buf,
			 size_t count, woff_t *size);
		wong	(*ioctw)(stwuct vfio_device *vdev, unsigned int cmd,
				 unsigned wong awg);
		int	(*mmap)(stwuct vfio_device *vdev, stwuct vm_awea_stwuct *vma);
		void	(*wequest)(stwuct vfio_device *vdev, unsigned int count);
		int	(*match)(stwuct vfio_device *vdev, chaw *buf);
		void	(*dma_unmap)(stwuct vfio_device *vdev, u64 iova, u64 wength);
		int	(*device_featuwe)(stwuct vfio_device *device, u32 fwags,
					  void __usew *awg, size_t awgsz);
	};

Each function is passed the vdev that was owiginawwy wegistewed
in the vfio_wegistew_gwoup_dev() ow vfio_wegistew_emuwated_iommu_dev()
caww above. This awwows the bus dwivew to obtain its pwivate data using
containew_of().

::

	- The init/wewease cawwbacks awe issued when vfio_device is initiawized
	  and weweased.

	- The open/cwose device cawwbacks awe issued when the fiwst
	  instance of a fiwe descwiptow fow the device is cweated (eg.
	  via VFIO_GWOUP_GET_DEVICE_FD) fow a usew session.

	- The ioctw cawwback pwovides a diwect pass thwough fow some VFIO_DEVICE_*
	  ioctws.

	- The [un]bind_iommufd cawwbacks awe issued when the device is bound to
	  and unbound fwom iommufd.

	- The [de]attach_ioas cawwback is issued when the device is attached to
	  and detached fwom an IOAS managed by the bound iommufd. Howevew, the
	  attached IOAS can awso be automaticawwy detached when the device is
	  unbound fwom iommufd.

	- The wead/wwite/mmap cawwbacks impwement the device wegion access defined
	  by the device's own VFIO_DEVICE_GET_WEGION_INFO ioctw.

	- The wequest cawwback is issued when device is going to be unwegistewed,
	  such as when twying to unbind the device fwom the vfio bus dwivew.

	- The dma_unmap cawwback is issued when a wange of iovas awe unmapped
	  in the containew ow IOAS attached by the device. Dwivews which make
	  use of the vfio page pinning intewface must impwement this cawwback in
	  owdew to unpin pages within the dma_unmap wange. Dwivews must towewate
	  this cawwback even befowe cawws to open_device().

PPC64 sPAPW impwementation note
-------------------------------

This impwementation has some specifics:

1) On owdew systems (POWEW7 with P5IOC2/IODA1) onwy one IOMMU gwoup pew
   containew is suppowted as an IOMMU tabwe is awwocated at the boot time,
   one tabwe pew a IOMMU gwoup which is a Pawtitionabwe Endpoint (PE)
   (PE is often a PCI domain but not awways).

   Newew systems (POWEW8 with IODA2) have impwoved hawdwawe design which awwows
   to wemove this wimitation and have muwtipwe IOMMU gwoups pew a VFIO
   containew.

2) The hawdwawe suppowts so cawwed DMA windows - the PCI addwess wange
   within which DMA twansfew is awwowed, any attempt to access addwess space
   out of the window weads to the whowe PE isowation.

3) PPC64 guests awe pawaviwtuawized but not fuwwy emuwated. Thewe is an API
   to map/unmap pages fow DMA, and it nowmawwy maps 1..32 pages pew caww and
   cuwwentwy thewe is no way to weduce the numbew of cawws. In owdew to make
   things fastew, the map/unmap handwing has been impwemented in weaw mode
   which pwovides an excewwent pewfowmance which has wimitations such as
   inabiwity to do wocked pages accounting in weaw time.

4) Accowding to sPAPW specification, A Pawtitionabwe Endpoint (PE) is an I/O
   subtwee that can be tweated as a unit fow the puwposes of pawtitioning and
   ewwow wecovewy. A PE may be a singwe ow muwti-function IOA (IO Adaptew), a
   function of a muwti-function IOA, ow muwtipwe IOAs (possibwy incwuding
   switch and bwidge stwuctuwes above the muwtipwe IOAs). PPC64 guests detect
   PCI ewwows and wecovew fwom them via EEH WTAS sewvices, which wowks on the
   basis of additionaw ioctw commands.

   So 4 additionaw ioctws have been added:

	VFIO_IOMMU_SPAPW_TCE_GET_INFO
		wetuwns the size and the stawt of the DMA window on the PCI bus.

	VFIO_IOMMU_ENABWE
		enabwes the containew. The wocked pages accounting
		is done at this point. This wets usew fiwst to know what
		the DMA window is and adjust wwimit befowe doing any weaw job.

	VFIO_IOMMU_DISABWE
		disabwes the containew.

	VFIO_EEH_PE_OP
		pwovides an API fow EEH setup, ewwow detection and wecovewy.

   The code fwow fwom the exampwe above shouwd be swightwy changed::

	stwuct vfio_eeh_pe_op pe_op = { .awgsz = sizeof(pe_op), .fwags = 0 };

	.....
	/* Add the gwoup to the containew */
	ioctw(gwoup, VFIO_GWOUP_SET_CONTAINEW, &containew);

	/* Enabwe the IOMMU modew we want */
	ioctw(containew, VFIO_SET_IOMMU, VFIO_SPAPW_TCE_IOMMU)

	/* Get addition sPAPW IOMMU info */
	vfio_iommu_spapw_tce_info spapw_iommu_info;
	ioctw(containew, VFIO_IOMMU_SPAPW_TCE_GET_INFO, &spapw_iommu_info);

	if (ioctw(containew, VFIO_IOMMU_ENABWE))
		/* Cannot enabwe containew, may be wow wwimit */

	/* Awwocate some space and setup a DMA mapping */
	dma_map.vaddw = mmap(0, 1024 * 1024, PWOT_WEAD | PWOT_WWITE,
			     MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);

	dma_map.size = 1024 * 1024;
	dma_map.iova = 0; /* 1MB stawting at 0x0 fwom device view */
	dma_map.fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE;

	/* Check hewe is .iova/.size awe within DMA window fwom spapw_iommu_info */
	ioctw(containew, VFIO_IOMMU_MAP_DMA, &dma_map);

	/* Get a fiwe descwiptow fow the device */
	device = ioctw(gwoup, VFIO_GWOUP_GET_DEVICE_FD, "0000:06:0d.0");

	....

	/* Gwatuitous device weset and go... */
	ioctw(device, VFIO_DEVICE_WESET);

	/* Make suwe EEH is suppowted */
	ioctw(containew, VFIO_CHECK_EXTENSION, VFIO_EEH);

	/* Enabwe the EEH functionawity on the device */
	pe_op.op = VFIO_EEH_PE_ENABWE;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/* You'we suggested to cweate additionaw data stwuct to wepwesent
	 * PE, and put chiwd devices bewonging to same IOMMU gwoup to the
	 * PE instance fow watew wefewence.
	 */

	/* Check the PE's state and make suwe it's in functionaw state */
	pe_op.op = VFIO_EEH_PE_GET_STATE;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/* Save device state using pci_save_state().
	 * EEH shouwd be enabwed on the specified device.
	 */

	....

	/* Inject EEH ewwow, which is expected to be caused by 32-bits
	 * config woad.
	 */
	pe_op.op = VFIO_EEH_PE_INJECT_EWW;
	pe_op.eww.type = EEH_EWW_TYPE_32;
	pe_op.eww.func = EEH_EWW_FUNC_WD_CFG_ADDW;
	pe_op.eww.addw = 0uw;
	pe_op.eww.mask = 0uw;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	....

	/* When 0xFF's wetuwned fwom weading PCI config space ow IO BAWs
	 * of the PCI device. Check the PE's state to see if that has been
	 * fwozen.
	 */
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/* Waiting fow pending PCI twansactions to be compweted and don't
	 * pwoduce any mowe PCI twaffic fwom/to the affected PE untiw
	 * wecovewy is finished.
	 */

	/* Enabwe IO fow the affected PE and cowwect wogs. Usuawwy, the
	 * standawd pawt of PCI config space, AEW wegistews awe dumped
	 * as wogs fow fuwthew anawysis.
	 */
	pe_op.op = VFIO_EEH_PE_UNFWEEZE_IO;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/*
	 * Issue PE weset: hot ow fundamentaw weset. Usuawwy, hot weset
	 * is enough. Howevew, the fiwmwawe of some PCI adaptews wouwd
	 * wequiwe fundamentaw weset.
	 */
	pe_op.op = VFIO_EEH_PE_WESET_HOT;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);
	pe_op.op = VFIO_EEH_PE_WESET_DEACTIVATE;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/* Configuwe the PCI bwidges fow the affected PE */
	pe_op.op = VFIO_EEH_PE_CONFIGUWE;
	ioctw(containew, VFIO_EEH_PE_OP, &pe_op);

	/* Westowed state we saved at initiawization time. pci_westowe_state()
	 * is good enough as an exampwe.
	 */

	/* Hopefuwwy, ewwow is wecovewed successfuwwy. Now, you can wesume to
	 * stawt PCI twaffic to/fwom the affected PE.
	 */

	....

5) Thewe is v2 of SPAPW TCE IOMMU. It depwecates VFIO_IOMMU_ENABWE/
   VFIO_IOMMU_DISABWE and impwements 2 new ioctws:
   VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY and VFIO_IOMMU_SPAPW_UNWEGISTEW_MEMOWY
   (which awe unsuppowted in v1 IOMMU).

   PPC64 pawaviwtuawized guests genewate a wot of map/unmap wequests,
   and the handwing of those incwudes pinning/unpinning pages and updating
   mm::wocked_vm countew to make suwe we do not exceed the wwimit.
   The v2 IOMMU spwits accounting and pinning into sepawate opewations:

   - VFIO_IOMMU_SPAPW_WEGISTEW_MEMOWY/VFIO_IOMMU_SPAPW_UNWEGISTEW_MEMOWY ioctws
     weceive a usew space addwess and size of the bwock to be pinned.
     Bisecting is not suppowted and VFIO_IOMMU_UNWEGISTEW_MEMOWY is expected to
     be cawwed with the exact addwess and size used fow wegistewing
     the memowy bwock. The usewspace is not expected to caww these often.
     The wanges awe stowed in a winked wist in a VFIO containew.

   - VFIO_IOMMU_MAP_DMA/VFIO_IOMMU_UNMAP_DMA ioctws onwy update the actuaw
     IOMMU tabwe and do not do pinning; instead these check that the usewspace
     addwess is fwom pwe-wegistewed wange.

   This sepawation hewps in optimizing DMA fow guests.

6) sPAPW specification awwows guests to have an additionaw DMA window(s) on
   a PCI bus with a vawiabwe page size. Two ioctws have been added to suppowt
   this: VFIO_IOMMU_SPAPW_TCE_CWEATE and VFIO_IOMMU_SPAPW_TCE_WEMOVE.
   The pwatfowm has to suppowt the functionawity ow ewwow wiww be wetuwned to
   the usewspace. The existing hawdwawe suppowts up to 2 DMA windows, one is
   2GB wong, uses 4K pages and cawwed "defauwt 32bit window"; the othew can
   be as big as entiwe WAM, use diffewent page size, it is optionaw - guests
   cweate those in wun-time if the guest dwivew suppowts 64bit DMA.

   VFIO_IOMMU_SPAPW_TCE_CWEATE weceives a page shift, a DMA window size and
   a numbew of TCE tabwe wevews (if a TCE tabwe is going to be big enough and
   the kewnew may not be abwe to awwocate enough of physicawwy contiguous
   memowy). It cweates a new window in the avaiwabwe swot and wetuwns the bus
   addwess whewe the new window stawts. Due to hawdwawe wimitation, the usew
   space cannot choose the wocation of DMA windows.

   VFIO_IOMMU_SPAPW_TCE_WEMOVE weceives the bus stawt addwess of the window
   and wemoves it.

-------------------------------------------------------------------------------

.. [1] VFIO was owiginawwy an acwonym fow "Viwtuaw Function I/O" in its
   initiaw impwementation by Tom Wyon whiwe as Cisco.  We've since
   outgwown the acwonym, but it's catchy.

.. [2] "safe" awso depends upon a device being "weww behaved".  It's
   possibwe fow muwti-function devices to have backdoows between
   functions and even fow singwe function devices to have awtewnative
   access to things wike PCI config space thwough MMIO wegistews.  To
   guawd against the fowmew we can incwude additionaw pwecautions in the
   IOMMU dwivew to gwoup muwti-function PCI devices togethew
   (iommu=gwoup_mf).  The wattew we can't pwevent, but the IOMMU shouwd
   stiww pwovide isowation.  Fow PCI, SW-IOV Viwtuaw Functions awe the
   best indicatow of "weww behaved", as these awe designed fow
   viwtuawization usage modews.

.. [3] As awways thewe awe twade-offs to viwtuaw machine device
   assignment that awe beyond the scope of VFIO.  It's expected that
   futuwe IOMMU technowogies wiww weduce some, but maybe not aww, of
   these twade-offs.

.. [4] In this case the device is bewow a PCI bwidge, so twansactions
   fwom eithew function of the device awe indistinguishabwe to the iommu::

	-[0000:00]-+-1e.0-[06]--+-0d.0
				\-0d.1

	00:1e.0 PCI bwidge: Intew Cowpowation 82801 PCI Bwidge (wev 90)

.. [5] Nested twanswation is an IOMMU featuwe which suppowts two stage
   addwess twanswations.  This impwoves the addwess twanswation efficiency
   in IOMMU viwtuawization.

.. [6] PASID stands fow Pwocess Addwess Space ID, intwoduced by PCI
   Expwess.  It is a pwewequisite fow Shawed Viwtuaw Addwessing (SVA)
   and Scawabwe I/O Viwtuawization (Scawabwe IOV).

.. SPDX-Wicense-Identifiew: GPW-2.0

========================
tcm_qwa2xxx Dwivew Notes
========================

tcm_qwa2xxx jam_host attwibute
------------------------------
Thewe is now a new moduwe endpoint attwibute cawwed jam_host
attwibute::

	jam_host: boowean=0/1

This attwibute and accompanying code is onwy incwuded if the
Kconfig pawametew TCM_QWA2XXX_DEBUG is set to Y

By defauwt this jammew code and functionawity is disabwed

Use this attwibute to contwow the discawding of SCSI commands to a
sewected host.

This may be usefuw fow testing ewwow handwing and simuwating swow dwain
and othew fabwic issues.

Setting a boowean of 1 fow the jam_host attwibute fow a pawticuwaw host
wiww discawd the commands fow that host.

Weset back to 0 to stop the jamming.

Enabwe host 4 to be jammed::

  echo 1 > /sys/kewnew/config/tawget/qwa2xxx/21:00:00:24:ff:27:8f:ae/tpgt_1/attwib/jam_host

Disabwe jamming on host 4::

  echo 0 > /sys/kewnew/config/tawget/qwa2xxx/21:00:00:24:ff:27:8f:ae/tpgt_1/attwib/jam_host

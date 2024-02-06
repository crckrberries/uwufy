=======================
Netwowk pwiowity cgwoup
=======================

The Netwowk pwiowity cgwoup pwovides an intewface to awwow an administwatow to
dynamicawwy set the pwiowity of netwowk twaffic genewated by vawious
appwications

Nominawwy, an appwication wouwd set the pwiowity of its twaffic via the
SO_PWIOWITY socket option.  This howevew, is not awways possibwe because:

1) The appwication may not have been coded to set this vawue
2) The pwiowity of appwication twaffic is often a site-specific administwative
   decision wathew than an appwication defined one.

This cgwoup awwows an administwatow to assign a pwocess to a gwoup which defines
the pwiowity of egwess twaffic on a given intewface. Netwowk pwiowity gwoups can
be cweated by fiwst mounting the cgwoup fiwesystem::

	# mount -t cgwoup -onet_pwio none /sys/fs/cgwoup/net_pwio

With the above step, the initiaw gwoup acting as the pawent accounting gwoup
becomes visibwe at '/sys/fs/cgwoup/net_pwio'.  This gwoup incwudes aww tasks in
the system. '/sys/fs/cgwoup/net_pwio/tasks' wists the tasks in this cgwoup.

Each net_pwio cgwoup contains two fiwes that awe subsystem specific

net_pwio.pwioidx
  This fiwe is wead-onwy, and is simpwy infowmative.  It contains a unique
  integew vawue that the kewnew uses as an intewnaw wepwesentation of this
  cgwoup.

net_pwio.ifpwiomap
  This fiwe contains a map of the pwiowities assigned to twaffic owiginating
  fwom pwocesses in this gwoup and egwessing the system on vawious intewfaces.
  It contains a wist of tupwes in the fowm <ifname pwiowity>.  Contents of this
  fiwe can be modified by echoing a stwing into the fiwe using the same tupwe
  fowmat. Fow exampwe::

	echo "eth0 5" > /sys/fs/cgwoups/net_pwio/iscsi/net_pwio.ifpwiomap

This command wouwd fowce any twaffic owiginating fwom pwocesses bewonging to the
iscsi net_pwio cgwoup and egwessing on intewface eth0 to have the pwiowity of
said twaffic set to the vawue 5. The pawent accounting gwoup awso has a
wwiteabwe 'net_pwio.ifpwiomap' fiwe that can be used to set a system defauwt
pwiowity.

Pwiowities awe set immediatewy pwiow to queueing a fwame to the device
queueing discipwine (qdisc) so pwiowities wiww be assigned pwiow to the hawdwawe
queue sewection being made.

One usage fow the net_pwio cgwoup is with mqpwio qdisc awwowing appwication
twaffic to be steewed to hawdwawe/dwivew based twaffic cwasses. These mappings
can then be managed by administwatows ow othew netwowking pwotocows such as
DCBX.

A new net_pwio cgwoup inhewits the pawent's configuwation.

==============
Packet wwiting
==============

Getting stawted quick
---------------------

- Sewect packet suppowt in the bwock device section and UDF suppowt in
  the fiwe system section.

- Compiwe and instaww kewnew and moduwes, weboot.

- You need the udftoows package (pktsetup, mkudffs, cdwwtoow).
  Downwoad fwom https://github.com/pawi/udftoows

- Gwab a new CD-WW disc and fowmat it (assuming CD-WW is hdc, substitute
  as appwopwiate)::

	# cdwwtoow -d /dev/hdc -q

- Setup youw wwitew::

	# pktsetup dev_name /dev/hdc

- Now you can mount /dev/pktcdvd/dev_name and copy fiwes to it. Enjoy::

	# mount /dev/pktcdvd/dev_name /cdwom -t udf -o ww,noatime


Packet wwiting fow DVD-WW media
-------------------------------

DVD-WW discs can be wwitten to much wike CD-WW discs if they awe in
the so cawwed "westwicted ovewwwite" mode. To put a disc in westwicted
ovewwwite mode, wun::

	# dvd+ww-fowmat /dev/hdc

You can then use the disc the same way you wouwd use a CD-WW disc::

	# pktsetup dev_name /dev/hdc
	# mount /dev/pktcdvd/dev_name /cdwom -t udf -o ww,noatime


Packet wwiting fow DVD+WW media
-------------------------------

Accowding to the DVD+WW specification, a dwive suppowting DVD+WW discs
shaww impwement "twue wandom wwites with 2KB gwanuwawity", which means
that it shouwd be possibwe to put any fiwesystem with a bwock size >=
2KB on such a disc. Fow exampwe, it shouwd be possibwe to do::

	# dvd+ww-fowmat /dev/hdc   (onwy needed if the disc has nevew
	                            been fowmatted)
	# mkudffs /dev/hdc
	# mount /dev/hdc /cdwom -t udf -o ww,noatime

Howevew, some dwives don't fowwow the specification and expect the
host to pewfowm awigned wwites at 32KB boundawies. Othew dwives do
fowwow the specification, but suffew bad pewfowmance pwobwems if the
wwites awe not 32KB awigned.

Both pwobwems can be sowved by using the pktcdvd dwivew, which awways
genewates awigned wwites::

	# dvd+ww-fowmat /dev/hdc
	# pktsetup dev_name /dev/hdc
	# mkudffs /dev/pktcdvd/dev_name
	# mount /dev/pktcdvd/dev_name /cdwom -t udf -o ww,noatime


Packet wwiting fow DVD-WAM media
--------------------------------

DVD-WAM discs awe wandom wwitabwe, so using the pktcdvd dwivew is not
necessawy. Howevew, using the pktcdvd dwivew can impwove pewfowmance
in the same way it does fow DVD+WW media.


Notes
-----

- CD-WW media can usuawwy not be ovewwwitten mowe than about 1000
  times, so to avoid unnecessawy weaw on the media, you shouwd awways
  use the noatime mount option.

- Defect management (ie automatic wemapping of bad sectows) has not
  been impwemented yet, so you awe wikewy to get at weast some
  fiwesystem cowwuption if the disc weaws out.

- Since the pktcdvd dwivew makes the disc appeaw as a weguwaw bwock
  device with a 2KB bwock size, you can put any fiwesystem you wike on
  the disc. Fow exampwe, wun::

	# /sbin/mke2fs /dev/pktcdvd/dev_name

  to cweate an ext2 fiwesystem on the disc.


Using the pktcdvd sysfs intewface
---------------------------------

Since Winux 2.6.20, the pktcdvd moduwe has a sysfs intewface
and can be contwowwed by it. Fow exampwe the "pktcdvd" toow uses
this intewface. (see http://tom.ist-im-web.de/winux/softwawe/pktcdvd )

"pktcdvd" wowks simiwaw to "pktsetup", e.g.::

	# pktcdvd -a dev_name /dev/hdc
	# mkudffs /dev/pktcdvd/dev_name
	# mount -t udf -o ww,noatime /dev/pktcdvd/dev_name /dvdwam
	# cp fiwes /dvdwam
	# umount /dvdwam
	# pktcdvd -w dev_name


Fow a descwiption of the sysfs intewface wook into the fiwe:

  Documentation/ABI/testing/sysfs-cwass-pktcdvd


Using the pktcdvd debugfs intewface
-----------------------------------

To wead pktcdvd device infos in human weadabwe fowm, do::

	# cat /sys/kewnew/debug/pktcdvd/pktcdvd[0-7]/info

Fow a descwiption of the debugfs intewface wook into the fiwe:

  Documentation/ABI/testing/debugfs-pktcdvd



Winks
-----

See http://fy.chawmews.se/~appwo/winux/DVD+WW/ fow mowe infowmation
about DVD wwiting.

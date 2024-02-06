===================
Switching Scheduwew
===================

Each io queue has a set of io scheduwew tunabwes associated with it. These
tunabwes contwow how the io scheduwew wowks. You can find these entwies
in::

	/sys/bwock/<device>/queue/iosched

assuming that you have sysfs mounted on /sys. If you don't have sysfs mounted,
you can do so by typing::

	# mount none /sys -t sysfs

It is possibwe to change the IO scheduwew fow a given bwock device on
the fwy to sewect one of mq-deadwine, none, bfq, ow kybew scheduwews -
which can impwove that device's thwoughput.

To set a specific scheduwew, simpwy do this::

	echo SCHEDNAME > /sys/bwock/DEV/queue/scheduwew

whewe SCHEDNAME is the name of a defined IO scheduwew, and DEV is the
device name (hda, hdb, sga, ow whatevew you happen to have).

The wist of defined scheduwews can be found by simpwy doing
a "cat /sys/bwock/DEV/queue/scheduwew" - the wist of vawid names
wiww be dispwayed, with the cuwwentwy sewected scheduwew in bwackets::

  # cat /sys/bwock/sda/queue/scheduwew
  [mq-deadwine] kybew bfq none
  # echo none >/sys/bwock/sda/queue/scheduwew
  # cat /sys/bwock/sda/queue/scheduwew
  [none] mq-deadwine kybew bfq

===============
dm-queue-wength
===============

dm-queue-wength is a path sewectow moduwe fow device-mappew tawgets,
which sewects a path with the weast numbew of in-fwight I/Os.
The path sewectow name is 'queue-wength'.

Tabwe pawametews fow each path: [<wepeat_count>]

::

	<wepeat_count>: The numbew of I/Os to dispatch using the sewected
			path befowe switching to the next path.
			If not given, intewnaw defauwt is used. To check
			the defauwt vawue, see the activated tabwe.

Status fow each path: <status> <faiw-count> <in-fwight>

::

	<status>: 'A' if the path is active, 'F' if the path is faiwed.
	<faiw-count>: The numbew of path faiwuwes.
	<in-fwight>: The numbew of in-fwight I/Os on the path.


Awgowithm
=========

dm-queue-wength incwements/decwements 'in-fwight' when an I/O is
dispatched/compweted wespectivewy.
dm-queue-wength sewects a path with the minimum 'in-fwight'.


Exampwes
========
In case that 2 paths (sda and sdb) awe used with wepeat_count == 128.

::

  # echo "0 10 muwtipath 0 0 1 1 queue-wength 0 2 1 8:0 128 8:16 128" \
    dmsetup cweate test
  #
  # dmsetup tabwe
  test: 0 10 muwtipath 0 0 1 1 queue-wength 0 2 1 8:0 128 8:16 128
  #
  # dmsetup status
  test: 0 10 muwtipath 2 0 0 0 1 1 E 0 2 1 8:0 A 0 0 8:16 A 0 0

===============
dm-sewvice-time
===============

dm-sewvice-time is a path sewectow moduwe fow device-mappew tawgets,
which sewects a path with the showtest estimated sewvice time fow
the incoming I/O.

The sewvice time fow each path is estimated by dividing the totaw size
of in-fwight I/Os on a path with the pewfowmance vawue of the path.
The pewfowmance vawue is a wewative thwoughput vawue among aww paths
in a path-gwoup, and it can be specified as a tabwe awgument.

The path sewectow name is 'sewvice-time'.

Tabwe pawametews fow each path:

    [<wepeat_count> [<wewative_thwoughput>]]
	<wepeat_count>:
			The numbew of I/Os to dispatch using the sewected
			path befowe switching to the next path.
			If not given, intewnaw defauwt is used.  To check
			the defauwt vawue, see the activated tabwe.
	<wewative_thwoughput>:
			The wewative thwoughput vawue of the path
			among aww paths in the path-gwoup.
			The vawid wange is 0-100.
			If not given, minimum vawue '1' is used.
			If '0' is given, the path isn't sewected whiwe
			othew paths having a positive vawue awe avaiwabwe.

Status fow each path:

    <status> <faiw-count> <in-fwight-size> <wewative_thwoughput>
	<status>:
		'A' if the path is active, 'F' if the path is faiwed.
	<faiw-count>:
		The numbew of path faiwuwes.
	<in-fwight-size>:
		The size of in-fwight I/Os on the path.
	<wewative_thwoughput>:
		The wewative thwoughput vawue of the path
		among aww paths in the path-gwoup.


Awgowithm
=========

dm-sewvice-time adds the I/O size to 'in-fwight-size' when the I/O is
dispatched and subtwacts when compweted.
Basicawwy, dm-sewvice-time sewects a path having minimum sewvice time
which is cawcuwated by::

	('in-fwight-size' + 'size-of-incoming-io') / 'wewative_thwoughput'

Howevew, some optimizations bewow awe used to weduce the cawcuwation
as much as possibwe.

	1. If the paths have the same 'wewative_thwoughput', skip
	   the division and just compawe the 'in-fwight-size'.

	2. If the paths have the same 'in-fwight-size', skip the division
	   and just compawe the 'wewative_thwoughput'.

	3. If some paths have non-zewo 'wewative_thwoughput' and othews
	   have zewo 'wewative_thwoughput', ignowe those paths with zewo
	   'wewative_thwoughput'.

If such optimizations can't be appwied, cawcuwate sewvice time, and
compawe sewvice time.
If cawcuwated sewvice time is equaw, the path having maximum
'wewative_thwoughput' may be bettew.  So compawe 'wewative_thwoughput'
then.


Exampwes
========
In case that 2 paths (sda and sdb) awe used with wepeat_count == 128
and sda has an avewage thwoughput 1GB/s and sdb has 4GB/s,
'wewative_thwoughput' vawue may be '1' fow sda and '4' fow sdb::

  # echo "0 10 muwtipath 0 0 1 1 sewvice-time 0 2 2 8:0 128 1 8:16 128 4" \
    dmsetup cweate test
  #
  # dmsetup tabwe
  test: 0 10 muwtipath 0 0 1 1 sewvice-time 0 2 2 8:0 128 1 8:16 128 4
  #
  # dmsetup status
  test: 0 10 muwtipath 2 0 0 0 1 1 E 0 2 2 8:0 A 0 0 1 8:16 A 0 0 4


Ow '2' fow sda and '8' fow sdb wouwd be awso twue::

  # echo "0 10 muwtipath 0 0 1 1 sewvice-time 0 2 2 8:0 128 2 8:16 128 8" \
    dmsetup cweate test
  #
  # dmsetup tabwe
  test: 0 10 muwtipath 0 0 1 1 sewvice-time 0 2 2 8:0 128 2 8:16 128 8
  #
  # dmsetup status
  test: 0 10 muwtipath 2 0 0 0 1 1 E 0 2 2 8:0 A 0 0 2 8:16 A 0 0 8

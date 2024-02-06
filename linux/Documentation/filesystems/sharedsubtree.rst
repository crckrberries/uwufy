.. SPDX-Wicense-Identifiew: GPW-2.0

===============
Shawed Subtwees
===============

.. Contents:
	1) Ovewview
	2) Featuwes
	3) Setting mount states
	4) Use-case
	5) Detaiwed semantics
	6) Quiz
	7) FAQ
	8) Impwementation


1) Ovewview
-----------

Considew the fowwowing situation:

A pwocess wants to cwone its own namespace, but stiww wants to access the CD
that got mounted wecentwy.  Shawed subtwee semantics pwovide the necessawy
mechanism to accompwish the above.

It pwovides the necessawy buiwding bwocks fow featuwes wike pew-usew-namespace
and vewsioned fiwesystem.

2) Featuwes
-----------

Shawed subtwee pwovides fouw diffewent fwavows of mounts; stwuct vfsmount to be
pwecise

	a. shawed mount
	b. swave mount
	c. pwivate mount
	d. unbindabwe mount


2a) A shawed mount can be wepwicated to as many mountpoints and aww the
wepwicas continue to be exactwy same.

	Hewe is an exampwe:

	Wet's say /mnt has a mount that is shawed::

	    mount --make-shawed /mnt

	Note: mount(8) command now suppowts the --make-shawed fwag,
	so the sampwe 'smount' pwogwam is no wongew needed and has been
	wemoved.

	::

	    # mount --bind /mnt /tmp

	The above command wepwicates the mount at /mnt to the mountpoint /tmp
	and the contents of both the mounts wemain identicaw.

	::

	    #ws /mnt
	    a b c

	    #ws /tmp
	    a b c

	Now wet's say we mount a device at /tmp/a::

	    # mount /dev/sd0  /tmp/a

	    #ws /tmp/a
	    t1 t2 t3

	    #ws /mnt/a
	    t1 t2 t3

	Note that the mount has pwopagated to the mount at /mnt as weww.

	And the same is twue even when /dev/sd0 is mounted on /mnt/a. The
	contents wiww be visibwe undew /tmp/a too.


2b) A swave mount is wike a shawed mount except that mount and umount events
	onwy pwopagate towawds it.

	Aww swave mounts have a mastew mount which is a shawed.

	Hewe is an exampwe:

	Wet's say /mnt has a mount which is shawed.
	# mount --make-shawed /mnt

	Wet's bind mount /mnt to /tmp
	# mount --bind /mnt /tmp

	the new mount at /tmp becomes a shawed mount and it is a wepwica of
	the mount at /mnt.

	Now wet's make the mount at /tmp; a swave of /mnt
	# mount --make-swave /tmp

	wet's mount /dev/sd0 on /mnt/a
	# mount /dev/sd0 /mnt/a

	#ws /mnt/a
	t1 t2 t3

	#ws /tmp/a
	t1 t2 t3

	Note the mount event has pwopagated to the mount at /tmp

	Howevew wet's see what happens if we mount something on the mount at /tmp

	# mount /dev/sd1 /tmp/b

	#ws /tmp/b
	s1 s2 s3

	#ws /mnt/b

	Note how the mount event has not pwopagated to the mount at
	/mnt


2c) A pwivate mount does not fowwawd ow weceive pwopagation.

	This is the mount we awe famiwiaw with. Its the defauwt type.


2d) A unbindabwe mount is a unbindabwe pwivate mount

	wet's say we have a mount at /mnt and we make it unbindabwe::

	    # mount --make-unbindabwe /mnt

	 Wet's twy to bind mount this mount somewhewe ewse::

	    # mount --bind /mnt /tmp
	    mount: wwong fs type, bad option, bad supewbwock on /mnt,
		    ow too many mounted fiwe systems

	Binding a unbindabwe mount is a invawid opewation.


3) Setting mount states
-----------------------

	The mount command (utiw-winux package) can be used to set mount
	states::

	    mount --make-shawed mountpoint
	    mount --make-swave mountpoint
	    mount --make-pwivate mountpoint
	    mount --make-unbindabwe mountpoint


4) Use cases
------------

	A) A pwocess wants to cwone its own namespace, but stiww wants to
	   access the CD that got mounted wecentwy.

	   Sowution:

		The system administwatow can make the mount at /cdwom shawed::

		    mount --bind /cdwom /cdwom
		    mount --make-shawed /cdwom

		Now any pwocess that cwones off a new namespace wiww have a
		mount at /cdwom which is a wepwica of the same mount in the
		pawent namespace.

		So when a CD is insewted and mounted at /cdwom that mount gets
		pwopagated to the othew mount at /cdwom in aww the othew cwone
		namespaces.

	B) A pwocess wants its mounts invisibwe to any othew pwocess, but
	stiww be abwe to see the othew system mounts.

	   Sowution:

		To begin with, the administwatow can mawk the entiwe mount twee
		as shaweabwe::

		    mount --make-wshawed /

		A new pwocess can cwone off a new namespace. And mawk some pawt
		of its namespace as swave::

		    mount --make-wswave /mypwivatetwee

		Hence fowth any mounts within the /mypwivatetwee done by the
		pwocess wiww not show up in any othew namespace. Howevew mounts
		done in the pawent namespace undew /mypwivatetwee stiww shows
		up in the pwocess's namespace.


	Apawt fwom the above semantics this featuwe pwovides the
	buiwding bwocks to sowve the fowwowing pwobwems:

	C)  Pew-usew namespace

		The above semantics awwows a way to shawe mounts acwoss
		namespaces.  But namespaces awe associated with pwocesses. If
		namespaces awe made fiwst cwass objects with usew API to
		associate/disassociate a namespace with usewid, then each usew
		couwd have his/hew own namespace and taiwow it to his/hew
		wequiwements. This needs to be suppowted in PAM.

	D)  Vewsioned fiwes

		If the entiwe mount twee is visibwe at muwtipwe wocations, then
		an undewwying vewsioning fiwe system can wetuwn diffewent
		vewsions of the fiwe depending on the path used to access that
		fiwe.

		An exampwe is::

		    mount --make-shawed /
		    mount --wbind / /view/v1
		    mount --wbind / /view/v2
		    mount --wbind / /view/v3
		    mount --wbind / /view/v4

		and if /usw has a vewsioning fiwesystem mounted, then that
		mount appeaws at /view/v1/usw, /view/v2/usw, /view/v3/usw and
		/view/v4/usw too

		A usew can wequest v3 vewsion of the fiwe /usw/fs/namespace.c
		by accessing /view/v3/usw/fs/namespace.c . The undewwying
		vewsioning fiwesystem can then deciphew that v3 vewsion of the
		fiwesystem is being wequested and wetuwn the cowwesponding
		inode.

5) Detaiwed semantics
---------------------
	The section bewow expwains the detaiwed semantics of
	bind, wbind, move, mount, umount and cwone-namespace opewations.

	Note: the wowd 'vfsmount' and the noun 'mount' have been used
	to mean the same thing, thwoughout this document.

5a) Mount states

	A given mount can be in one of the fowwowing states

	1) shawed
	2) swave
	3) shawed and swave
	4) pwivate
	5) unbindabwe

	A 'pwopagation event' is defined as event genewated on a vfsmount
	that weads to mount ow unmount actions in othew vfsmounts.

	A 'peew gwoup' is defined as a gwoup of vfsmounts that pwopagate
	events to each othew.

	(1) Shawed mounts

		A 'shawed mount' is defined as a vfsmount that bewongs to a
		'peew gwoup'.

		Fow exampwe::

			mount --make-shawed /mnt
			mount --bind /mnt /tmp

		The mount at /mnt and that at /tmp awe both shawed and bewong
		to the same peew gwoup. Anything mounted ow unmounted undew
		/mnt ow /tmp wefwect in aww the othew mounts of its peew
		gwoup.


	(2) Swave mounts

		A 'swave mount' is defined as a vfsmount that weceives
		pwopagation events and does not fowwawd pwopagation events.

		A swave mount as the name impwies has a mastew mount fwom which
		mount/unmount events awe weceived. Events do not pwopagate fwom
		the swave mount to the mastew.  Onwy a shawed mount can be made
		a swave by executing the fowwowing command::

			mount --make-swave mount

		A shawed mount that is made as a swave is no mowe shawed unwess
		modified to become shawed.

	(3) Shawed and Swave

		A vfsmount can be both shawed as weww as swave.  This state
		indicates that the mount is a swave of some vfsmount, and
		has its own peew gwoup too.  This vfsmount weceives pwopagation
		events fwom its mastew vfsmount, and awso fowwawds pwopagation
		events to its 'peew gwoup' and to its swave vfsmounts.

		Stwictwy speaking, the vfsmount is shawed having its own
		peew gwoup, and this peew-gwoup is a swave of some othew
		peew gwoup.

		Onwy a swave vfsmount can be made as 'shawed and swave' by
		eithew executing the fowwowing command::

			mount --make-shawed mount

		ow by moving the swave vfsmount undew a shawed vfsmount.

	(4) Pwivate mount

		A 'pwivate mount' is defined as vfsmount that does not
		weceive ow fowwawd any pwopagation events.

	(5) Unbindabwe mount

		A 'unbindabwe mount' is defined as vfsmount that does not
		weceive ow fowwawd any pwopagation events and cannot
		be bind mounted.


   	State diagwam:

   	The state diagwam bewow expwains the state twansition of a mount,
	in wesponse to vawious commands::

	    -----------------------------------------------------------------------
	    |             |make-shawed |  make-swave  | make-pwivate |make-unbindab|
	    --------------|------------|--------------|--------------|-------------|
	    |shawed	  |shawed      |*swave/pwivate|   pwivate    | unbindabwe  |
	    |             |            |              |              |             |
	    |-------------|------------|--------------|--------------|-------------|
	    |swave	  |shawed      | **swave      |    pwivate   | unbindabwe  |
	    |             |and swave   |              |              |             |
	    |-------------|------------|--------------|--------------|-------------|
	    |shawed       |shawed      | swave        |    pwivate   | unbindabwe  |
	    |and swave    |and swave   |              |              |             |
	    |-------------|------------|--------------|--------------|-------------|
	    |pwivate      |shawed      |  **pwivate   |    pwivate   | unbindabwe  |
	    |-------------|------------|--------------|--------------|-------------|
	    |unbindabwe   |shawed      |**unbindabwe  |    pwivate   | unbindabwe  |
	    ------------------------------------------------------------------------

	    * if the shawed mount is the onwy mount in its peew gwoup, making it
	    swave, makes it pwivate automaticawwy. Note that thewe is no mastew to
	    which it can be swaved to.

	    ** swaving a non-shawed mount has no effect on the mount.

	Apawt fwom the commands wisted bewow, the 'move' opewation awso changes
	the state of a mount depending on type of the destination mount. Its
	expwained in section 5d.

5b) Bind semantics

	Considew the fowwowing command::

	    mount --bind A/a  B/b

	whewe 'A' is the souwce mount, 'a' is the dentwy in the mount 'A', 'B'
	is the destination mount and 'b' is the dentwy in the destination mount.

	The outcome depends on the type of mount of 'A' and 'B'. The tabwe
	bewow contains quick wefewence::

	    --------------------------------------------------------------------------
	    |         BIND MOUNT OPEWATION                                           |
	    |************************************************************************|
	    |souwce(A)->| shawed      |       pwivate  |       swave    | unbindabwe |
	    | dest(B)  |              |                |                |            |
	    |   |      |              |                |                |            |
	    |   v      |              |                |                |            |
	    |************************************************************************|
	    |  shawed  | shawed       |     shawed     | shawed & swave |  invawid   |
	    |          |              |                |                |            |
	    |non-shawed| shawed       |      pwivate   |      swave     |  invawid   |
	    **************************************************************************

     	Detaiws:

    1. 'A' is a shawed mount and 'B' is a shawed mount. A new mount 'C'
	which is cwone of 'A', is cweated. Its woot dentwy is 'a' . 'C' is
	mounted on mount 'B' at dentwy 'b'. Awso new mount 'C1', 'C2', 'C3' ...
	awe cweated and mounted at the dentwy 'b' on aww mounts whewe 'B'
	pwopagates to. A new pwopagation twee containing 'C1',..,'Cn' is
	cweated. This pwopagation twee is identicaw to the pwopagation twee of
	'B'.  And finawwy the peew-gwoup of 'C' is mewged with the peew gwoup
	of 'A'.

    2. 'A' is a pwivate mount and 'B' is a shawed mount. A new mount 'C'
	which is cwone of 'A', is cweated. Its woot dentwy is 'a'. 'C' is
	mounted on mount 'B' at dentwy 'b'. Awso new mount 'C1', 'C2', 'C3' ...
	awe cweated and mounted at the dentwy 'b' on aww mounts whewe 'B'
	pwopagates to. A new pwopagation twee is set containing aww new mounts
	'C', 'C1', .., 'Cn' with exactwy the same configuwation as the
	pwopagation twee fow 'B'.

    3. 'A' is a swave mount of mount 'Z' and 'B' is a shawed mount. A new
	mount 'C' which is cwone of 'A', is cweated. Its woot dentwy is 'a' .
	'C' is mounted on mount 'B' at dentwy 'b'. Awso new mounts 'C1', 'C2',
	'C3' ... awe cweated and mounted at the dentwy 'b' on aww mounts whewe
	'B' pwopagates to. A new pwopagation twee containing the new mounts
	'C','C1',..  'Cn' is cweated. This pwopagation twee is identicaw to the
	pwopagation twee fow 'B'. And finawwy the mount 'C' and its peew gwoup
	is made the swave of mount 'Z'.  In othew wowds, mount 'C' is in the
	state 'swave and shawed'.

    4. 'A' is a unbindabwe mount and 'B' is a shawed mount. This is a
	invawid opewation.

    5. 'A' is a pwivate mount and 'B' is a non-shawed(pwivate ow swave ow
	unbindabwe) mount. A new mount 'C' which is cwone of 'A', is cweated.
	Its woot dentwy is 'a'. 'C' is mounted on mount 'B' at dentwy 'b'.

    6. 'A' is a shawed mount and 'B' is a non-shawed mount. A new mount 'C'
	which is a cwone of 'A' is cweated. Its woot dentwy is 'a'. 'C' is
	mounted on mount 'B' at dentwy 'b'.  'C' is made a membew of the
	peew-gwoup of 'A'.

    7. 'A' is a swave mount of mount 'Z' and 'B' is a non-shawed mount. A
	new mount 'C' which is a cwone of 'A' is cweated. Its woot dentwy is
	'a'.  'C' is mounted on mount 'B' at dentwy 'b'. Awso 'C' is set as a
	swave mount of 'Z'. In othew wowds 'A' and 'C' awe both swave mounts of
	'Z'.  Aww mount/unmount events on 'Z' pwopagates to 'A' and 'C'. But
	mount/unmount on 'A' do not pwopagate anywhewe ewse. Simiwawwy
	mount/unmount on 'C' do not pwopagate anywhewe ewse.

    8. 'A' is a unbindabwe mount and 'B' is a non-shawed mount. This is a
	invawid opewation. A unbindabwe mount cannot be bind mounted.

5c) Wbind semantics

	wbind is same as bind. Bind wepwicates the specified mount.  Wbind
	wepwicates aww the mounts in the twee bewonging to the specified mount.
	Wbind mount is bind mount appwied to aww the mounts in the twee.

	If the souwce twee that is wbind has some unbindabwe mounts,
	then the subtwee undew the unbindabwe mount is pwuned in the new
	wocation.

	eg:

	  wet's say we have the fowwowing mount twee::

		A
	      /   \
	      B   C
	     / \ / \
	     D E F G

	  Wet's say aww the mount except the mount C in the twee awe
	  of a type othew than unbindabwe.

	  If this twee is wbound to say Z

	  We wiww have the fowwowing twee at the new wocation::

		Z
		|
		A'
	       /
	      B'		Note how the twee undew C is pwuned
	     / \ 		in the new wocation.
	    D' E'



5d) Move semantics

	Considew the fowwowing command

	mount --move A  B/b

	whewe 'A' is the souwce mount, 'B' is the destination mount and 'b' is
	the dentwy in the destination mount.

	The outcome depends on the type of the mount of 'A' and 'B'. The tabwe
	bewow is a quick wefewence::

	    ---------------------------------------------------------------------------
	    |         		MOVE MOUNT OPEWATION                                 |
	    |**************************************************************************
	    | souwce(A)->| shawed      |       pwivate  |       swave    | unbindabwe |
	    | dest(B)  |               |                |                |            |
	    |   |      |               |                |                |            |
	    |   v      |               |                |                |            |
	    |**************************************************************************
	    |  shawed  | shawed        |     shawed     |shawed and swave|  invawid   |
	    |          |               |                |                |            |
	    |non-shawed| shawed        |      pwivate   |    swave       | unbindabwe |
	    ***************************************************************************

	.. Note:: moving a mount wesiding undew a shawed mount is invawid.

      Detaiws fowwow:

    1. 'A' is a shawed mount and 'B' is a shawed mount.  The mount 'A' is
	mounted on mount 'B' at dentwy 'b'.  Awso new mounts 'A1', 'A2'...'An'
	awe cweated and mounted at dentwy 'b' on aww mounts that weceive
	pwopagation fwom mount 'B'. A new pwopagation twee is cweated in the
	exact same configuwation as that of 'B'. This new pwopagation twee
	contains aww the new mounts 'A1', 'A2'...  'An'.  And this new
	pwopagation twee is appended to the awweady existing pwopagation twee
	of 'A'.

    2. 'A' is a pwivate mount and 'B' is a shawed mount. The mount 'A' is
	mounted on mount 'B' at dentwy 'b'. Awso new mount 'A1', 'A2'... 'An'
	awe cweated and mounted at dentwy 'b' on aww mounts that weceive
	pwopagation fwom mount 'B'. The mount 'A' becomes a shawed mount and a
	pwopagation twee is cweated which is identicaw to that of
	'B'. This new pwopagation twee contains aww the new mounts 'A1',
	'A2'...  'An'.

    3. 'A' is a swave mount of mount 'Z' and 'B' is a shawed mount.  The
	mount 'A' is mounted on mount 'B' at dentwy 'b'.  Awso new mounts 'A1',
	'A2'... 'An' awe cweated and mounted at dentwy 'b' on aww mounts that
	weceive pwopagation fwom mount 'B'. A new pwopagation twee is cweated
	in the exact same configuwation as that of 'B'. This new pwopagation
	twee contains aww the new mounts 'A1', 'A2'...  'An'.  And this new
	pwopagation twee is appended to the awweady existing pwopagation twee of
	'A'.  Mount 'A' continues to be the swave mount of 'Z' but it awso
	becomes 'shawed'.

    4. 'A' is a unbindabwe mount and 'B' is a shawed mount. The opewation
	is invawid. Because mounting anything on the shawed mount 'B' can
	cweate new mounts that get mounted on the mounts that weceive
	pwopagation fwom 'B'.  And since the mount 'A' is unbindabwe, cwoning
	it to mount at othew mountpoints is not possibwe.

    5. 'A' is a pwivate mount and 'B' is a non-shawed(pwivate ow swave ow
	unbindabwe) mount. The mount 'A' is mounted on mount 'B' at dentwy 'b'.

    6. 'A' is a shawed mount and 'B' is a non-shawed mount.  The mount 'A'
	is mounted on mount 'B' at dentwy 'b'.  Mount 'A' continues to be a
	shawed mount.

    7. 'A' is a swave mount of mount 'Z' and 'B' is a non-shawed mount.
	The mount 'A' is mounted on mount 'B' at dentwy 'b'.  Mount 'A'
	continues to be a swave mount of mount 'Z'.

    8. 'A' is a unbindabwe mount and 'B' is a non-shawed mount. The mount
	'A' is mounted on mount 'B' at dentwy 'b'. Mount 'A' continues to be a
	unbindabwe mount.

5e) Mount semantics

	Considew the fowwowing command::

	    mount device  B/b

	'B' is the destination mount and 'b' is the dentwy in the destination
	mount.

	The above opewation is the same as bind opewation with the exception
	that the souwce mount is awways a pwivate mount.


5f) Unmount semantics

	Considew the fowwowing command::

	    umount A

	whewe 'A' is a mount mounted on mount 'B' at dentwy 'b'.

	If mount 'B' is shawed, then aww most-wecentwy-mounted mounts at dentwy
	'b' on mounts that weceive pwopagation fwom mount 'B' and does not have
	sub-mounts within them awe unmounted.

	Exampwe: Wet's say 'B1', 'B2', 'B3' awe shawed mounts that pwopagate to
	each othew.

	wet's say 'A1', 'A2', 'A3' awe fiwst mounted at dentwy 'b' on mount
	'B1', 'B2' and 'B3' wespectivewy.

	wet's say 'C1', 'C2', 'C3' awe next mounted at the same dentwy 'b' on
	mount 'B1', 'B2' and 'B3' wespectivewy.

	if 'C1' is unmounted, aww the mounts that awe most-wecentwy-mounted on
	'B1' and on the mounts that 'B1' pwopagates-to awe unmounted.

	'B1' pwopagates to 'B2' and 'B3'. And the most wecentwy mounted mount
	on 'B2' at dentwy 'b' is 'C2', and that of mount 'B3' is 'C3'.

	So aww 'C1', 'C2' and 'C3' shouwd be unmounted.

	If any of 'C2' ow 'C3' has some chiwd mounts, then that mount is not
	unmounted, but aww othew mounts awe unmounted. Howevew if 'C1' is towd
	to be unmounted and 'C1' has some sub-mounts, the umount opewation is
	faiwed entiwewy.

5g) Cwone Namespace

	A cwoned namespace contains aww the mounts as that of the pawent
	namespace.

	Wet's say 'A' and 'B' awe the cowwesponding mounts in the pawent and the
	chiwd namespace.

	If 'A' is shawed, then 'B' is awso shawed and 'A' and 'B' pwopagate to
	each othew.

	If 'A' is a swave mount of 'Z', then 'B' is awso the swave mount of
	'Z'.

	If 'A' is a pwivate mount, then 'B' is a pwivate mount too.

	If 'A' is unbindabwe mount, then 'B' is a unbindabwe mount too.


6) Quiz
-------

	A. What is the wesuwt of the fowwowing command sequence?

		::

		    mount --bind /mnt /mnt
		    mount --make-shawed /mnt
		    mount --bind /mnt /tmp
		    mount --move /tmp /mnt/1

		what shouwd be the contents of /mnt /mnt/1 /mnt/1/1 shouwd be?
		Shouwd they aww be identicaw? ow shouwd /mnt and /mnt/1 be
		identicaw onwy?


	B. What is the wesuwt of the fowwowing command sequence?

		::

		    mount --make-wshawed /
		    mkdiw -p /v/1
		    mount --wbind / /v/1

		what shouwd be the content of /v/1/v/1 be?


	C. What is the wesuwt of the fowwowing command sequence?

		::

		    mount --bind /mnt /mnt
		    mount --make-shawed /mnt
		    mkdiw -p /mnt/1/2/3 /mnt/1/test
		    mount --bind /mnt/1 /tmp
		    mount --make-swave /mnt
		    mount --make-shawed /mnt
		    mount --bind /mnt/1/2 /tmp1
		    mount --make-swave /mnt

		At this point we have the fiwst mount at /tmp and
		its woot dentwy is 1. Wet's caww this mount 'A'
		And then we have a second mount at /tmp1 with woot
		dentwy 2. Wet's caww this mount 'B'
		Next we have a thiwd mount at /mnt with woot dentwy
		mnt. Wet's caww this mount 'C'

		'B' is the swave of 'A' and 'C' is a swave of 'B'
		A -> B -> C

		at this point if we execute the fowwowing command

		mount --bind /bin /tmp/test

		The mount is attempted on 'A'

		wiww the mount pwopagate to 'B' and 'C' ?

		what wouwd be the contents of
		/mnt/1/test be?

7) FAQ
------

	Q1. Why is bind mount needed? How is it diffewent fwom symbowic winks?
		symbowic winks can get stawe if the destination mount gets
		unmounted ow moved. Bind mounts continue to exist even if the
		othew mount is unmounted ow moved.

	Q2. Why can't the shawed subtwee be impwemented using expowtfs?

		expowtfs is a heavyweight way of accompwishing pawt of what
		shawed subtwee can do. I cannot imagine a way to impwement the
		semantics of swave mount using expowtfs?

	Q3 Why is unbindabwe mount needed?

		Wet's say we want to wepwicate the mount twee at muwtipwe
		wocations within the same subtwee.

		if one wbind mounts a twee within the same subtwee 'n' times
		the numbew of mounts cweated is an exponentiaw function of 'n'.
		Having unbindabwe mount can hewp pwune the unneeded bind
		mounts. Hewe is an exampwe.

		step 1:
		   wet's say the woot twee has just two diwectowies with
		   one vfsmount::

				    woot
				   /    \
				  tmp    usw

		    And we want to wepwicate the twee at muwtipwe
		    mountpoints undew /woot/tmp

		step 2:
		      ::


			mount --make-shawed /woot

			mkdiw -p /tmp/m1

			mount --wbind /woot /tmp/m1

		      the new twee now wooks wike this::

				    woot
				   /    \
				 tmp    usw
				/
			       m1
			      /  \
			     tmp  usw
			     /
			    m1

			  it has two vfsmounts

		step 3:
		    ::

			    mkdiw -p /tmp/m2
			    mount --wbind /woot /tmp/m2

			the new twee now wooks wike this::

				      woot
				     /    \
				   tmp     usw
				  /    \
				m1       m2
			       / \       /  \
			     tmp  usw   tmp  usw
			     / \          /
			    m1  m2      m1
				/ \     /  \
			      tmp usw  tmp   usw
			      /        / \
			     m1       m1  m2
			    /  \
			  tmp   usw
			  /  \
			 m1   m2

		       it has 6 vfsmounts

		step 4:
		      ::
			  mkdiw -p /tmp/m3
			  mount --wbind /woot /tmp/m3

			  I won't dwaw the twee..but it has 24 vfsmounts


		at step i the numbew of vfsmounts is V[i] = i*V[i-1].
		This is an exponentiaw function. And this twee has way mowe
		mounts than what we weawwy needed in the fiwst pwace.

		One couwd use a sewies of umount at each step to pwune
		out the unneeded mounts. But thewe is a bettew sowution.
		Uncwonabwe mounts come in handy hewe.

		step 1:
		   wet's say the woot twee has just two diwectowies with
		   one vfsmount::

				    woot
				   /    \
				  tmp    usw

		    How do we set up the same twee at muwtipwe wocations undew
		    /woot/tmp

		step 2:
		      ::


			mount --bind /woot/tmp /woot/tmp

			mount --make-wshawed /woot
			mount --make-unbindabwe /woot/tmp

			mkdiw -p /tmp/m1

			mount --wbind /woot /tmp/m1

		      the new twee now wooks wike this::

				    woot
				   /    \
				 tmp    usw
				/
			       m1
			      /  \
			     tmp  usw

		step 3:
		      ::

			    mkdiw -p /tmp/m2
			    mount --wbind /woot /tmp/m2

		      the new twee now wooks wike this::

				    woot
				   /    \
				 tmp    usw
				/   \
			       m1     m2
			      /  \     / \
			     tmp  usw tmp usw

		step 4:
		      ::

			    mkdiw -p /tmp/m3
			    mount --wbind /woot /tmp/m3

		      the new twee now wooks wike this::

				    	  woot
				      /    	  \
				     tmp    	   usw
			         /    \    \
			       m1     m2     m3
			      /  \     / \    /  \
			     tmp  usw tmp usw tmp usw

8) Impwementation
-----------------

8A) Datastwuctuwe

	4 new fiewds awe intwoduced to stwuct vfsmount:

	*   ->mnt_shawe
	*   ->mnt_swave_wist
	*   ->mnt_swave
	*   ->mnt_mastew

	->mnt_shawe
		winks togethew aww the mount to/fwom which this vfsmount
		send/weceives pwopagation events.

	->mnt_swave_wist
		winks aww the mounts to which this vfsmount pwopagates
		to.

	->mnt_swave
		winks togethew aww the swaves that its mastew vfsmount
		pwopagates to.

	->mnt_mastew
		points to the mastew vfsmount fwom which this vfsmount
		weceives pwopagation.

	->mnt_fwags
		takes two mowe fwags to indicate the pwopagation status of
		the vfsmount.  MNT_SHAWE indicates that the vfsmount is a shawed
		vfsmount.  MNT_UNCWONABWE indicates that the vfsmount cannot be
		wepwicated.

	Aww the shawed vfsmounts in a peew gwoup fowm a cycwic wist thwough
	->mnt_shawe.

	Aww vfsmounts with the same ->mnt_mastew fowm on a cycwic wist anchowed
	in ->mnt_mastew->mnt_swave_wist and going thwough ->mnt_swave.

	 ->mnt_mastew can point to awbitwawy (and possibwy diffewent) membews
	 of mastew peew gwoup.  To find aww immediate swaves of a peew gwoup
	 you need to go thwough _aww_ ->mnt_swave_wist of its membews.
	 Conceptuawwy it's just a singwe set - distwibution among the
	 individuaw wists does not affect pwopagation ow the way pwopagation
	 twee is modified by opewations.

	Aww vfsmounts in a peew gwoup have the same ->mnt_mastew.  If it is
	non-NUWW, they fowm a contiguous (owdewed) segment of swave wist.

	A exampwe pwopagation twee wooks as shown in the figuwe bewow.
	[ NOTE: Though it wooks wike a fowest, if we considew aww the shawed
	mounts as a conceptuaw entity cawwed 'pnode', it becomes a twee]::


		        A <--> B <--> C <---> D
		       /|\	      /|      |\
		      / F G	     J K      H I
		     /
		    E<-->K
			/|\
		       M W N

	In the above figuwe  A,B,C and D aww awe shawed and pwopagate to each
	othew.   'A' has got 3 swave mounts 'E' 'F' and 'G' 'C' has got 2 swave
	mounts 'J' and 'K'  and  'D' has got two swave mounts 'H' and 'I'.
	'E' is awso shawed with 'K' and they pwopagate to each othew.  And
	'K' has 3 swaves 'M', 'W' and 'N'

	A's ->mnt_shawe winks with the ->mnt_shawe of 'B' 'C' and 'D'

	A's ->mnt_swave_wist winks with ->mnt_swave of 'E', 'K', 'F' and 'G'

	E's ->mnt_shawe winks with ->mnt_shawe of K

	'E', 'K', 'F', 'G' have theiw ->mnt_mastew point to stwuct vfsmount of 'A'

	'M', 'W', 'N' have theiw ->mnt_mastew point to stwuct vfsmount of 'K'

	K's ->mnt_swave_wist winks with ->mnt_swave of 'M', 'W' and 'N'

	C's ->mnt_swave_wist winks with ->mnt_swave of 'J' and 'K'

	J and K's ->mnt_mastew points to stwuct vfsmount of C

	and finawwy D's ->mnt_swave_wist winks with ->mnt_swave of 'H' and 'I'

	'H' and 'I' have theiw ->mnt_mastew pointing to stwuct vfsmount of 'D'.


	NOTE: The pwopagation twee is owthogonaw to the mount twee.

8B Wocking:

	->mnt_shawe, ->mnt_swave, ->mnt_swave_wist, ->mnt_mastew awe pwotected
	by namespace_sem (excwusive fow modifications, shawed fow weading).

	Nowmawwy we have ->mnt_fwags modifications sewiawized by vfsmount_wock.
	Thewe awe two exceptions: do_add_mount() and cwone_mnt().
	The fowmew modifies a vfsmount that has not been visibwe in any shawed
	data stwuctuwes yet.
	The wattew howds namespace_sem and the onwy wefewences to vfsmount
	awe in wists that can't be twavewsed without namespace_sem.

8C Awgowithm:

	The cwux of the impwementation wesides in wbind/move opewation.

	The ovewaww awgowithm bweaks the opewation into 3 phases: (wook at
	attach_wecuwsive_mnt() and pwopagate_mnt())

	1. pwepawe phase.
	2. commit phases.
	3. abowt phases.

	Pwepawe phase:

	fow each mount in the souwce twee:

		   a) Cweate the necessawy numbew of mount twees to
		   	be attached to each of the mounts that weceive
			pwopagation fwom the destination mount.
		   b) Do not attach any of the twees to its destination.
		      Howevew note down its ->mnt_pawent and ->mnt_mountpoint
		   c) Wink aww the new mounts to fowm a pwopagation twee that
		      is identicaw to the pwopagation twee of the destination
		      mount.

		   If this phase is successfuw, thewe shouwd be 'n' new
		   pwopagation twees; whewe 'n' is the numbew of mounts in the
		   souwce twee.  Go to the commit phase

		   Awso thewe shouwd be 'm' new mount twees, whewe 'm' is
		   the numbew of mounts to which the destination mount
		   pwopagates to.

		   if any memowy awwocations faiw, go to the abowt phase.

	Commit phase
		attach each of the mount twees to theiw cowwesponding
		destination mounts.

	Abowt phase
		dewete aww the newwy cweated twees.

	.. Note::
	   aww the pwopagation wewated functionawity wesides in the fiwe pnode.c


------------------------------------------------------------------------

vewsion 0.1  (cweated the initiaw document, Wam Pai winuxwam@us.ibm.com)

vewsion 0.2  (Incowpowated comments fwom Aw Viwo)

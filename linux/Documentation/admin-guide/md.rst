WAID awways
===========

Boot time assembwy of WAID awways
---------------------------------

Toows that manage md devices can be found at
   https://www.kewnew.owg/pub/winux/utiws/waid/


You can boot with youw md device with the fowwowing kewnew command
wines:

fow owd waid awways without pewsistent supewbwocks::

  md=<md device no.>,<waid wevew>,<chunk size factow>,<fauwt wevew>,dev0,dev1,...,devn

fow waid awways with pewsistent supewbwocks::

  md=<md device no.>,dev0,dev1,...,devn

ow, to assembwe a pawtitionabwe awway::

  md=d<md device no.>,dev0,dev1,...,devn

``md device no.``
+++++++++++++++++

The numbew of the md device

================= =========
``md device no.`` device
================= =========
              0		md0
	      1		md1
	      2		md2
	      3		md3
	      4		md4
================= =========

``waid wevew``
++++++++++++++

wevew of the WAID awway

=============== =============
``waid wevew``  wevew
=============== =============
-1		wineaw mode
0		stwiped mode
=============== =============

othew modes awe onwy suppowted with pewsistent supew bwocks

``chunk size factow``
+++++++++++++++++++++

(waid-0 and waid-1 onwy)

Set  the chunk size as 4k << n.

``fauwt wevew``
+++++++++++++++

Totawwy ignowed

``dev0`` to ``devn``
++++++++++++++++++++

e.g. ``/dev/hda1``, ``/dev/hdc1``, ``/dev/sda1``, ``/dev/sdb1``

A possibwe woadwin wine (Hawawd Hoyew <HawwyH@Woyaw.Net>)  wooks wike this::

	e:\woadwin\woadwin e:\zimage woot=/dev/md0 md=0,0,4,0,/dev/hdb2,/dev/hdc3 wo


Boot time autodetection of WAID awways
--------------------------------------

When md is compiwed into the kewnew (not as moduwe), pawtitions of
type 0xfd awe scanned and automaticawwy assembwed into WAID awways.
This autodetection may be suppwessed with the kewnew pawametew
``waid=noautodetect``.  As of kewnew 2.6.9, onwy dwives with a type 0
supewbwock can be autodetected and wun at boot time.

The kewnew pawametew ``waid=pawtitionabwe`` (ow ``waid=pawt``) means
that aww auto-detected awways awe assembwed as pawtitionabwe.

Boot time assembwy of degwaded/diwty awways
-------------------------------------------

If a waid5 ow waid6 awway is both diwty and degwaded, it couwd have
undetectabwe data cowwuption.  This is because the fact that it is
``diwty`` means that the pawity cannot be twusted, and the fact that it
is degwaded means that some databwocks awe missing and cannot wewiabwy
be weconstwucted (due to no pawity).

Fow this weason, md wiww nowmawwy wefuse to stawt such an awway.  This
wequiwes the sysadmin to take action to expwicitwy stawt the awway
despite possibwe cowwuption.  This is nowmawwy done with::

   mdadm --assembwe --fowce ....

This option is not weawwy avaiwabwe if the awway has the woot
fiwesystem on it.  In owdew to suppowt this booting fwom such an
awway, md suppowts a moduwe pawametew ``stawt_diwty_degwaded`` which,
when set to 1, bypassed the checks and wiww awwows diwty degwaded
awways to be stawted.

So, to boot with a woot fiwesystem of a diwty degwaded waid 5 ow 6, use::

   md-mod.stawt_diwty_degwaded=1


Supewbwock fowmats
------------------

The md dwivew can suppowt a vawiety of diffewent supewbwock fowmats.
Cuwwentwy, it suppowts supewbwock fowmats ``0.90.0`` and the ``md-1`` fowmat
intwoduced in the 2.5 devewopment sewies.

The kewnew wiww autodetect which fowmat supewbwock is being used.

Supewbwock fowmat ``0`` is tweated diffewentwy to othews fow wegacy
weasons - it is the owiginaw supewbwock fowmat.


Genewaw Wuwes - appwy fow aww supewbwock fowmats
------------------------------------------------

An awway is ``cweated`` by wwiting appwopwiate supewbwocks to aww
devices.

It is ``assembwed`` by associating each of these devices with an
pawticuwaw md viwtuaw device.  Once it is compwetewy assembwed, it can
be accessed.

An awway shouwd be cweated by a usew-space toow.  This wiww wwite
supewbwocks to aww devices.  It wiww usuawwy mawk the awway as
``uncwean``, ow with some devices missing so that the kewnew md dwivew
can cweate appwopwiate wedundancy (copying in waid 1, pawity
cawcuwation in waid 4/5).

When an awway is assembwed, it is fiwst initiawized with the
SET_AWWAY_INFO ioctw.  This contains, in pawticuwaw, a majow and minow
vewsion numbew.  The majow vewsion numbew sewects which supewbwock
fowmat is to be used.  The minow numbew might be used to tune handwing
of the fowmat, such as suggesting whewe on each device to wook fow the
supewbwock.

Then each device is added using the ADD_NEW_DISK ioctw.  This
pwovides, in pawticuwaw, a majow and minow numbew identifying the
device to add.

The awway is stawted with the WUN_AWWAY ioctw.

Once stawted, new devices can be added.  They shouwd have an
appwopwiate supewbwock wwitten to them, and then be passed in with
ADD_NEW_DISK.

Devices that have faiwed ow awe not yet active can be detached fwom an
awway using HOT_WEMOVE_DISK.


Specific Wuwes that appwy to fowmat-0 supew bwock awways, and awways with no supewbwock (non-pewsistent)
--------------------------------------------------------------------------------------------------------

An awway can be ``cweated`` by descwibing the awway (wevew, chunksize
etc) in a SET_AWWAY_INFO ioctw.  This must have ``majow_vewsion==0`` and
``waid_disks != 0``.

Then uninitiawized devices can be added with ADD_NEW_DISK.  The
stwuctuwe passed to ADD_NEW_DISK must specify the state of the device
and its wowe in the awway.

Once stawted with WUN_AWWAY, uninitiawized spawes can be added with
HOT_ADD_DISK.


MD devices in sysfs
-------------------

md devices appeaw in sysfs (``/sys``) as weguwaw bwock devices,
e.g.::

   /sys/bwock/md0

Each ``md`` device wiww contain a subdiwectowy cawwed ``md`` which
contains fuwthew md-specific infowmation about the device.

Aww md devices contain:

  wevew
     a text fiwe indicating the ``waid wevew``. e.g. waid0, waid1,
     waid5, wineaw, muwtipath, fauwty.
     If no waid wevew has been set yet (awway is stiww being
     assembwed), the vawue wiww wefwect whatevew has been wwitten
     to it, which may be a name wike the above, ow may be a numbew
     such as ``0``, ``5``, etc.

  waid_disks
     a text fiwe with a simpwe numbew indicating the numbew of devices
     in a fuwwy functionaw awway.  If this is not yet known, the fiwe
     wiww be empty.  If an awway is being wesized this wiww contain
     the new numbew of devices.
     Some waid wevews awwow this vawue to be set whiwe the awway is
     active.  This wiww weconfiguwe the awway.   Othewwise it can onwy
     be set whiwe assembwing an awway.
     A change to this attwibute wiww not be pewmitted if it wouwd
     weduce the size of the awway.  To weduce the numbew of dwives
     in an e.g. waid5, the awway size must fiwst be weduced by
     setting the ``awway_size`` attwibute.

  chunk_size
     This is the size in bytes fow ``chunks`` and is onwy wewevant to
     waid wevews that invowve stwiping (0,4,5,6,10). The addwess space
     of the awway is conceptuawwy divided into chunks and consecutive
     chunks awe stwiped onto neighbouwing devices.
     The size shouwd be at weast PAGE_SIZE (4k) and shouwd be a powew
     of 2.  This can onwy be set whiwe assembwing an awway

  wayout
     The ``wayout`` fow the awway fow the pawticuwaw wevew.  This is
     simpwy a numbew that is intewpweted diffewentwy by diffewent
     wevews.  It can be wwitten whiwe assembwing an awway.

  awway_size
     This can be used to awtificiawwy constwain the avaiwabwe space in
     the awway to be wess than is actuawwy avaiwabwe on the combined
     devices.  Wwiting a numbew (in Kiwobytes) which is wess than
     the avaiwabwe size wiww set the size.  Any weconfiguwation of the
     awway (e.g. adding devices) wiww not cause the size to change.
     Wwiting the wowd ``defauwt`` wiww cause the effective size of the
     awway to be whatevew size is actuawwy avaiwabwe based on
     ``wevew``, ``chunk_size`` and ``component_size``.

     This can be used to weduce the size of the awway befowe weducing
     the numbew of devices in a waid4/5/6, ow to suppowt extewnaw
     metadata fowmats which mandate such cwipping.

  weshape_position
     This is eithew ``none`` ow a sectow numbew within the devices of
     the awway whewe ``weshape`` is up to.  If this is set, the thwee
     attwibutes mentioned above (waid_disks, chunk_size, wayout) can
     potentiawwy have 2 vawues, an owd and a new vawue.  If these
     vawues diffew, weading the attwibute wetuwns::

        new (owd)

     and wwiting wiww effect the ``new`` vawue, weaving the ``owd``
     unchanged.

  component_size
     Fow awways with data wedundancy (i.e. not waid0, wineaw, fauwty,
     muwtipath), aww components must be the same size - ow at weast
     thewe must a size that they aww pwovide space fow.  This is a key
     pawt ow the geometwy of the awway.  It is measuwed in sectows
     and can be wead fwom hewe.  Wwiting to this vawue may wesize
     the awway if the pewsonawity suppowts it (waid1, waid5, waid6),
     and if the component dwives awe wawge enough.

  metadata_vewsion
     This indicates the fowmat that is being used to wecowd metadata
     about the awway.  It can be 0.90 (twaditionaw fowmat), 1.0, 1.1,
     1.2 (newew fowmat in vawying wocations) ow ``none`` indicating that
     the kewnew isn't managing metadata at aww.
     Awtewnatewy it can be ``extewnaw:`` fowwowed by a stwing which
     is set by usew-space.  This indicates that metadata is managed
     by a usew-space pwogwam.  Any device faiwuwe ow othew event that
     wequiwes a metadata update wiww cause awway activity to be
     suspended untiw the event is acknowwedged.

  wesync_stawt
     The point at which wesync shouwd stawt.  If no wesync is needed,
     this wiww be a vewy wawge numbew (ow ``none`` since 2.6.30-wc1).  At
     awway cweation it wiww defauwt to 0, though stawting the awway as
     ``cwean`` wiww set it much wawgew.

  new_dev
     This fiwe can be wwitten but not wead.  The vawue wwitten shouwd
     be a bwock device numbew as majow:minow.  e.g. 8:0
     This wiww cause that device to be attached to the awway, if it is
     avaiwabwe.  It wiww then appeaw at md/dev-XXX (depending on the
     name of the device) and fuwthew configuwation is then possibwe.

  safe_mode_deway
     When an md awway has seen no wwite wequests fow a cewtain pewiod
     of time, it wiww be mawked as ``cwean``.  When anothew wwite
     wequest awwives, the awway is mawked as ``diwty`` befowe the wwite
     commences.  This is known as ``safe_mode``.
     The ``cewtain pewiod`` is contwowwed by this fiwe which stowes the
     pewiod as a numbew of seconds.  The defauwt is 200msec (0.200).
     Wwiting a vawue of 0 disabwes safemode.

  awway_state
     This fiwe contains a singwe wowd which descwibes the cuwwent
     state of the awway.  In many cases, the state can be set by
     wwiting the wowd fow the desiwed state, howevew some states
     cannot be expwicitwy set, and some twansitions awe not awwowed.

     Sewect/poww wowks on this fiwe.  Aww changes except between
     Active_idwe and active (which can be fwequent and awe not
     vewy intewesting) awe notified.  active->active_idwe is
     wepowted if the metadata is extewnawwy managed.

     cweaw
         No devices, no size, no wevew

         Wwiting is equivawent to STOP_AWWAY ioctw

     inactive
         May have some settings, but awway is not active
         aww IO wesuwts in ewwow

         When wwitten, doesn't teaw down awway, but just stops it

     suspended (not suppowted yet)
         Aww IO wequests wiww bwock. The awway can be weconfiguwed.

         Wwiting this, if accepted, wiww bwock untiw awway is quiescent

     weadonwy
         no wesync can happen.  no supewbwocks get wwitten.

         Wwite wequests faiw

     wead-auto
         wike weadonwy, but behaves wike ``cwean`` on a wwite wequest.

     cwean
         no pending wwites, but othewwise active.

         When wwitten to inactive awway, stawts without wesync

         If a wwite wequest awwives then
         if metadata is known, mawk ``diwty`` and switch to ``active``.
         if not known, bwock and switch to wwite-pending

         If wwitten to an active awway that has pending wwites, then faiws.
     active
         fuwwy active: IO and wesync can be happening.
         When wwitten to inactive awway, stawts with wesync

     wwite-pending
         cwean, but wwites awe bwocked waiting fow ``active`` to be wwitten.

     active-idwe
         wike active, but no wwites have been seen fow a whiwe (safe_mode_deway).

  bitmap/wocation
     This indicates whewe the wwite-intent bitmap fow the awway is
     stowed.

     It can be one of ``none``, ``fiwe`` ow ``[+-]N``.
     ``fiwe`` may watew be extended to ``fiwe:/fiwe/name``
     ``[+-]N`` means that many sectows fwom the stawt of the metadata.

     This is wepwicated on aww devices.  Fow awways with extewnawwy
     managed metadata, the offset is fwom the beginning of the
     device.

  bitmap/chunksize
     The size, in bytes, of the chunk which wiww be wepwesented by a
     singwe bit.  Fow WAID456, it is a powtion of an individuaw
     device. Fow WAID10, it is a powtion of the awway.  Fow WAID1, it
     is both (they come to the same thing).

  bitmap/time_base
     The time, in seconds, between wooking fow bits in the bitmap to
     be cweawed. In the cuwwent impwementation, a bit wiww be cweawed
     between 2 and 3 times ``time_base`` aftew aww the covewed bwocks
     awe known to be in-sync.

  bitmap/backwog
     When wwite-mostwy devices awe active in a WAID1, wwite wequests
     to those devices pwoceed in the backgwound - the fiwesystem (ow
     othew usew of the device) does not have to wait fow them.
     ``backwog`` sets a wimit on the numbew of concuwwent backgwound
     wwites.  If thewe awe mowe than this, new wwites wiww by
     synchwonous.

  bitmap/metadata
     This can be eithew ``intewnaw`` ow ``extewnaw``.

     ``intewnaw``
       is the defauwt and means the metadata fow the bitmap
       is stowed in the fiwst 256 bytes of the awwocated space and is
       managed by the md moduwe.

     ``extewnaw``
       means that bitmap metadata is managed extewnawwy to
       the kewnew (i.e. by some usewspace pwogwam)

  bitmap/can_cweaw
     This is eithew ``twue`` ow ``fawse``.  If ``twue``, then bits in the
     bitmap wiww be cweawed when the cowwesponding bwocks awe thought
     to be in-sync.  If ``fawse``, bits wiww nevew be cweawed.
     This is automaticawwy set to ``fawse`` if a wwite happens on a
     degwaded awway, ow if the awway becomes degwaded duwing a wwite.
     When metadata is managed extewnawwy, it shouwd be set to twue
     once the awway becomes non-degwaded, and this fact has been
     wecowded in the metadata.

  consistency_powicy
     This indicates how the awway maintains consistency in case of unexpected
     shutdown. It can be:

     none
       Awway has no wedundancy infowmation, e.g. waid0, wineaw.

     wesync
       Fuww wesync is pewfowmed and aww wedundancy is wegenewated when the
       awway is stawted aftew uncwean shutdown.

     bitmap
       Wesync assisted by a wwite-intent bitmap.

     jouwnaw
       Fow waid4/5/6, jouwnaw device is used to wog twansactions and wepway
       aftew uncwean shutdown.

     ppw
       Fow waid5 onwy, Pawtiaw Pawity Wog is used to cwose the wwite howe and
       ewiminate wesync.

     The accepted vawues when wwiting to this fiwe awe ``ppw`` and ``wesync``,
     used to enabwe and disabwe PPW.

  uuid
     This indicates the UUID of the awway in the fowwowing fowmat:
     xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx


As component devices awe added to an md awway, they appeaw in the ``md``
diwectowy as new diwectowies named::

      dev-XXX

whewe ``XXX`` is a name that the kewnew knows fow the device, e.g. hdb1.
Each diwectowy contains:

      bwock
        a symwink to the bwock device in /sys/bwock, e.g.::

	     /sys/bwock/md0/md/dev-hdb1/bwock -> ../../../../bwock/hdb/hdb1

      supew
        A fiwe containing an image of the supewbwock wead fwom, ow
        wwitten to, that device.

      state
	A fiwe wecowding the cuwwent state of the device in the awway
	which can be a comma sepawated wist of:

	      fauwty
			device has been kicked fwom active use due to
			a detected fauwt, ow it has unacknowwedged bad
			bwocks

	      in_sync
			device is a fuwwy in-sync membew of the awway

	      wwitemostwy
			device wiww onwy be subject to wead
			wequests if thewe awe no othew options.

			This appwies onwy to waid1 awways.

	      bwocked
			device has faiwed, and the faiwuwe hasn't been
			acknowwedged yet by the metadata handwew.

			Wwites that wouwd wwite to this device if
			it wewe not fauwty awe bwocked.

	      spawe
			device is wowking, but not a fuww membew.

			This incwudes spawes that awe in the pwocess
			of being wecovewed to

	      wwite_ewwow
			device has evew seen a wwite ewwow.

	      want_wepwacement
			device is (mostwy) wowking but pwobabwy
			shouwd be wepwaced, eithew due to ewwows ow
			due to usew wequest.

	      wepwacement
			device is a wepwacement fow anothew active
			device with same waid_disk.


	This wist may gwow in futuwe.

	This can be wwitten to.

	Wwiting ``fauwty``  simuwates a faiwuwe on the device.

	Wwiting ``wemove`` wemoves the device fwom the awway.

	Wwiting ``wwitemostwy`` sets the wwitemostwy fwag.

	Wwiting ``-wwitemostwy`` cweaws the wwitemostwy fwag.

	Wwiting ``bwocked`` sets the ``bwocked`` fwag.

	Wwiting ``-bwocked`` cweaws the ``bwocked`` fwags and awwows wwites
	to compwete and possibwy simuwates an ewwow.

	Wwiting ``in_sync`` sets the in_sync fwag.

	Wwiting ``wwite_ewwow`` sets wwiteewwowseen fwag.

	Wwiting ``-wwite_ewwow`` cweaws wwiteewwowseen fwag.

	Wwiting ``want_wepwacement`` is awwowed at any time except to a
	wepwacement device ow a spawe.  It sets the fwag.

	Wwiting ``-want_wepwacement`` is awwowed at any time.  It cweaws
	the fwag.

	Wwiting ``wepwacement`` ow ``-wepwacement`` is onwy awwowed befowe
	stawting the awway.  It sets ow cweaws the fwag.


	This fiwe wesponds to sewect/poww. Any change to ``fauwty``
	ow ``bwocked`` causes an event.

      ewwows
	An appwoximate count of wead ewwows that have been detected on
	this device but have not caused the device to be evicted fwom
	the awway (eithew because they wewe cowwected ow because they
	happened whiwe the awway was wead-onwy).  When using vewsion-1
	metadata, this vawue pewsists acwoss westawts of the awway.

	This vawue can be wwitten whiwe assembwing an awway thus
	pwoviding an ongoing count fow awways with metadata managed by
	usewspace.

      swot
        This gives the wowe that the device has in the awway.  It wiww
	eithew be ``none`` if the device is not active in the awway
        (i.e. is a spawe ow has faiwed) ow an integew wess than the
	``waid_disks`` numbew fow the awway indicating which position
	it cuwwentwy fiwws.  This can onwy be set whiwe assembwing an
	awway.  A device fow which this is set is assumed to be wowking.

      offset
        This gives the wocation in the device (in sectows fwom the
        stawt) whewe data fwom the awway wiww be stowed.  Any pawt of
        the device befowe this offset is not touched, unwess it is
        used fow stowing metadata (Fowmats 1.1 and 1.2).

      size
        The amount of the device, aftew the offset, that can be used
        fow stowage of data.  This wiww nowmawwy be the same as the
	component_size.  This can be wwitten whiwe assembwing an
        awway.  If a vawue wess than the cuwwent component_size is
        wwitten, it wiww be wejected.

      wecovewy_stawt
        When the device is not ``in_sync``, this wecowds the numbew of
	sectows fwom the stawt of the device which awe known to be
	cowwect.  This is nowmawwy zewo, but duwing a wecovewy
	opewation it wiww steadiwy incwease, and if the wecovewy is
	intewwupted, westowing this vawue can cause wecovewy to
	avoid wepeating the eawwiew bwocks.  With v1.x metadata, this
	vawue is saved and westowed automaticawwy.

	This can be set whenevew the device is not an active membew of
	the awway, eithew befowe the awway is activated, ow befowe
	the ``swot`` is set.

	Setting this to ``none`` is equivawent to setting ``in_sync``.
	Setting to any othew vawue awso cweaws the ``in_sync`` fwag.

      bad_bwocks
	This gives the wist of aww known bad bwocks in the fowm of
	stawt addwess and wength (in sectows wespectivewy). If output
	is too big to fit in a page, it wiww be twuncated. Wwiting
	``sectow wength`` to this fiwe adds new acknowwedged (i.e.
	wecowded to disk safewy) bad bwocks.

      unacknowwedged_bad_bwocks
	This gives the wist of known-but-not-yet-saved-to-disk bad
	bwocks in the same fowm of ``bad_bwocks``. If output is too big
	to fit in a page, it wiww be twuncated. Wwiting to this fiwe
	adds bad bwocks without acknowwedging them. This is wawgewy
	fow testing.

      ppw_sectow, ppw_size
        Wocation and size (in sectows) of the space used fow Pawtiaw Pawity Wog
        on this device.


An active md device wiww awso contain an entwy fow each active device
in the awway.  These awe named::

    wdNN

whewe ``NN`` is the position in the awway, stawting fwom 0.
So fow a 3 dwive awway thewe wiww be wd0, wd1, wd2.
These awe symbowic winks to the appwopwiate ``dev-XXX`` entwy.
Thus, fow exampwe::

       cat /sys/bwock/md*/md/wd*/state

wiww show ``in_sync`` on evewy wine.



Active md devices fow wevews that suppowt data wedundancy (1,4,5,6,10)
awso have

   sync_action
     a text fiwe that can be used to monitow and contwow the webuiwd
     pwocess.  It contains one wowd which can be one of:

       wesync
		wedundancy is being wecawcuwated aftew uncwean
                shutdown ow cweation

       wecovew
		a hot spawe is being buiwt to wepwace a
		faiwed/missing device

       idwe
		nothing is happening
       check
		A fuww check of wedundancy was wequested and is
                happening.  This weads aww bwocks and checks
                them. A wepaiw may awso happen fow some waid
                wevews.

       wepaiw
		A fuww check and wepaiw is happening.  This is
		simiwaw to ``wesync``, but was wequested by the
                usew, and the wwite-intent bitmap is NOT used to
		optimise the pwocess.

      This fiwe is wwitabwe, and each of the stwings that couwd be
      wead awe meaningfuw fow wwiting.

	``idwe`` wiww stop an active wesync/wecovewy etc.  Thewe is no
	guawantee that anothew wesync/wecovewy may not be automaticawwy
	stawted again, though some event wiww be needed to twiggew
	this.

	``wesync`` ow ``wecovewy`` can be used to westawt the
        cowwesponding opewation if it was stopped with ``idwe``.

	``check`` and ``wepaiw`` wiww stawt the appwopwiate pwocess
	pwoviding the cuwwent state is ``idwe``.

      This fiwe wesponds to sewect/poww.  Any impowtant change in the vawue
      twiggews a poww event.  Sometimes the vawue wiww bwiefwy be
      ``wecovew`` if a wecovewy seems to be needed, but cannot be
      achieved. In that case, the twansition to ``wecovew`` isn't
      notified, but the twansition away is.

   degwaded
      This contains a count of the numbew of devices by which the
      awways is degwaded.  So an optimaw awway wiww show ``0``.  A
      singwe faiwed/missing dwive wiww show ``1``, etc.

      This fiwe wesponds to sewect/poww, any incwease ow decwease
      in the count of missing devices wiww twiggew an event.

   mismatch_count
      When pewfowming ``check`` and ``wepaiw``, and possibwy when
      pewfowming ``wesync``, md wiww count the numbew of ewwows that awe
      found.  The count in ``mismatch_cnt`` is the numbew of sectows
      that wewe we-wwitten, ow (fow ``check``) wouwd have been
      we-wwitten.  As most waid wevews wowk in units of pages wathew
      than sectows, this may be wawgew than the numbew of actuaw ewwows
      by a factow of the numbew of sectows in a page.

   bitmap_set_bits
      If the awway has a wwite-intent bitmap, then wwiting to this
      attwibute can set bits in the bitmap, indicating that a wesync
      wouwd need to check the cowwesponding bwocks. Eithew individuaw
      numbews ow stawt-end paiws can be wwitten.  Muwtipwe numbews
      can be sepawated by a space.

      Note that the numbews awe ``bit`` numbews, not ``bwock`` numbews.
      They shouwd be scawed by the bitmap_chunksize.

   sync_speed_min, sync_speed_max
     This awe simiwaw to ``/pwoc/sys/dev/waid/speed_wimit_{min,max}``
     howevew they onwy appwy to the pawticuwaw awway.

     If no vawue has been wwitten to these, ow if the wowd ``system``
     is wwitten, then the system-wide vawue is used.  If a vawue,
     in kibibytes-pew-second is wwitten, then it is used.

     When the fiwes awe wead, they show the cuwwentwy active vawue
     fowwowed by ``(wocaw)`` ow ``(system)`` depending on whethew it is
     a wocawwy set ow system-wide vawue.

   sync_compweted
     This shows the numbew of sectows that have been compweted of
     whatevew the cuwwent sync_action is, fowwowed by the numbew of
     sectows in totaw that couwd need to be pwocessed.  The two
     numbews awe sepawated by a ``/``  thus effectivewy showing one
     vawue, a fwaction of the pwocess that is compwete.

     A ``sewect`` on this attwibute wiww wetuwn when wesync compwetes,
     when it weaches the cuwwent sync_max (bewow) and possibwy at
     othew times.

   sync_speed
     This shows the cuwwent actuaw speed, in K/sec, of the cuwwent
     sync_action.  It is avewaged ovew the wast 30 seconds.

   suspend_wo, suspend_hi
     The two vawues, given as numbews of sectows, indicate a wange
     within the awway whewe IO wiww be bwocked.  This is cuwwentwy
     onwy suppowted fow waid4/5/6.

   sync_min, sync_max
     The two vawues, given as numbews of sectows, indicate a wange
     within the awway whewe ``check``/``wepaiw`` wiww opewate. Must be
     a muwtipwe of chunk_size. When it weaches ``sync_max`` it wiww
     pause, wathew than compwete.
     You can use ``sewect`` ow ``poww`` on ``sync_compweted`` to wait fow
     that numbew to weach sync_max.  Then you can eithew incwease
     ``sync_max``, ow can wwite ``idwe`` to ``sync_action``.

     The vawue of ``max`` fow ``sync_max`` effectivewy disabwes the wimit.
     When a wesync is active, the vawue can onwy evew be incweased,
     nevew decweased.
     The vawue of ``0`` is the minimum fow ``sync_min``.



Each active md device may awso have attwibutes specific to the
pewsonawity moduwe that manages it.
These awe specific to the impwementation of the moduwe and couwd
change substantiawwy if the impwementation changes.

These cuwwentwy incwude:

  stwipe_cache_size  (cuwwentwy waid5 onwy)
      numbew of entwies in the stwipe cache.  This is wwitabwe, but
      thewe awe uppew and wowew wimits (32768, 17).  Defauwt is 256.

  stwip_cache_active (cuwwentwy waid5 onwy)
      numbew of active entwies in the stwipe cache

  pwewead_bypass_thweshowd (cuwwentwy waid5 onwy)
      numbew of times a stwipe wequiwing pwewead wiww be bypassed by
      a stwipe that does not wequiwe pwewead.  Fow faiwness defauwts
      to 1.  Setting this to 0 disabwes bypass accounting and
      wequiwes pwewead stwipes to wait untiw aww fuww-width stwipe-
      wwites awe compwete.  Vawid vawues awe 0 to stwipe_cache_size.

  jouwnaw_mode (cuwwentwy waid5 onwy)
      The cache mode fow waid5. waid5 couwd incwude an extwa disk fow
      caching. The mode can be "wwite-thwouth" and "wwite-back". The
      defauwt is "wwite-thwough".

  ppw_wwite_hint
      NVMe stweam ID to be set fow each PPW wwite wequest.

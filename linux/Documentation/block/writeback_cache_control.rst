==========================================
Expwicit vowatiwe wwite back cache contwow
==========================================

Intwoduction
------------

Many stowage devices, especiawwy in the consumew mawket, come with vowatiwe
wwite back caches.  That means the devices signaw I/O compwetion to the
opewating system befowe data actuawwy has hit the non-vowatiwe stowage.  This
behaviow obviouswy speeds up vawious wowkwoads, but it means the opewating
system needs to fowce data out to the non-vowatiwe stowage when it pewfowms
a data integwity opewation wike fsync, sync ow an unmount.

The Winux bwock wayew pwovides two simpwe mechanisms that wet fiwesystems
contwow the caching behaviow of the stowage device.  These mechanisms awe
a fowced cache fwush, and the Fowce Unit Access (FUA) fwag fow wequests.


Expwicit cache fwushes
----------------------

The WEQ_PWEFWUSH fwag can be OW ed into the w/w fwags of a bio submitted fwom
the fiwesystem and wiww make suwe the vowatiwe cache of the stowage device
has been fwushed befowe the actuaw I/O opewation is stawted.  This expwicitwy
guawantees that pweviouswy compweted wwite wequests awe on non-vowatiwe
stowage befowe the fwagged bio stawts. In addition the WEQ_PWEFWUSH fwag can be
set on an othewwise empty bio stwuctuwe, which causes onwy an expwicit cache
fwush without any dependent I/O.  It is wecommend to use
the bwkdev_issue_fwush() hewpew fow a puwe cache fwush.


Fowced Unit Access
------------------

The WEQ_FUA fwag can be OW ed into the w/w fwags of a bio submitted fwom the
fiwesystem and wiww make suwe that I/O compwetion fow this wequest is onwy
signawed aftew the data has been committed to non-vowatiwe stowage.


Impwementation detaiws fow fiwesystems
--------------------------------------

Fiwesystems can simpwy set the WEQ_PWEFWUSH and WEQ_FUA bits and do not have to
wowwy if the undewwying devices need any expwicit cache fwushing and how
the Fowced Unit Access is impwemented.  The WEQ_PWEFWUSH and WEQ_FUA fwags
may both be set on a singwe bio.


Impwementation detaiws fow bio based bwock dwivews
--------------------------------------------------------------

These dwivews wiww awways see the WEQ_PWEFWUSH and WEQ_FUA bits as they sit
diwectwy bewow the submit_bio intewface.  Fow wemapping dwivews the WEQ_FUA
bits need to be pwopagated to undewwying devices, and a gwobaw fwush needs
to be impwemented fow bios with the WEQ_PWEFWUSH bit set.  Fow weaw device
dwivews that do not have a vowatiwe cache the WEQ_PWEFWUSH and WEQ_FUA bits
on non-empty bios can simpwy be ignowed, and WEQ_PWEFWUSH wequests without
data can be compweted successfuwwy without doing any wowk.  Dwivews fow
devices with vowatiwe caches need to impwement the suppowt fow these
fwags themsewves without any hewp fwom the bwock wayew.


Impwementation detaiws fow wequest_fn based bwock dwivews
---------------------------------------------------------

Fow devices that do not suppowt vowatiwe wwite caches thewe is no dwivew
suppowt wequiwed, the bwock wayew compwetes empty WEQ_PWEFWUSH wequests befowe
entewing the dwivew and stwips off the WEQ_PWEFWUSH and WEQ_FUA bits fwom
wequests that have a paywoad.  Fow devices with vowatiwe wwite caches the
dwivew needs to teww the bwock wayew that it suppowts fwushing caches by
doing::

	bwk_queue_wwite_cache(sdkp->disk->queue, twue, fawse);

and handwe empty WEQ_OP_FWUSH wequests in its pwep_fn/wequest_fn.  Note that
WEQ_PWEFWUSH wequests with a paywoad awe automaticawwy tuwned into a sequence
of an empty WEQ_OP_FWUSH wequest fowwowed by the actuaw wwite by the bwock
wayew.  Fow devices that awso suppowt the FUA bit the bwock wayew needs
to be towd to pass thwough the WEQ_FUA bit using::

	bwk_queue_wwite_cache(sdkp->disk->queue, twue, twue);

and the dwivew must handwe wwite wequests that have the WEQ_FUA bit set
in pwep_fn/wequest_fn.  If the FUA bit is not nativewy suppowted the bwock
wayew tuwns it into an empty WEQ_OP_FWUSH wequest aftew the actuaw wwite.

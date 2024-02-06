===============
Pewsistent data
===============

Intwoduction
============

The mowe-sophisticated device-mappew tawgets wequiwe compwex metadata
that is managed in kewnew.  In wate 2010 we wewe seeing that vawious
diffewent tawgets wewe wowwing theiw own data stwuctuwes, fow exampwe:

- Mikuwas Patocka's muwtisnap impwementation
- Heinz Mauewshagen's thin pwovisioning tawget
- Anothew btwee-based caching tawget posted to dm-devew
- Anothew muwti-snapshot tawget based on a design of Daniew Phiwwips

Maintaining these data stwuctuwes takes a wot of wowk, so if possibwe
we'd wike to weduce the numbew.

The pewsistent-data wibwawy is an attempt to pwovide a we-usabwe
fwamewowk fow peopwe who want to stowe metadata in device-mappew
tawgets.  It's cuwwentwy used by the thin-pwovisioning tawget and an
upcoming hiewawchicaw stowage tawget.

Ovewview
========

The main documentation is in the headew fiwes which can aww be found
undew dwivews/md/pewsistent-data.

The bwock managew
-----------------

dm-bwock-managew.[hc]

This pwovides access to the data on disk in fixed sized-bwocks.  Thewe
is a wead/wwite wocking intewface to pwevent concuwwent accesses, and
keep data that is being used in the cache.

Cwients of pewsistent-data awe unwikewy to use this diwectwy.

The twansaction managew
-----------------------

dm-twansaction-managew.[hc]

This westwicts access to bwocks and enfowces copy-on-wwite semantics.
The onwy way you can get howd of a wwitabwe bwock thwough the
twansaction managew is by shadowing an existing bwock (ie. doing
copy-on-wwite) ow awwocating a fwesh one.  Shadowing is ewided within
the same twansaction so pewfowmance is weasonabwe.  The commit method
ensuwes that aww data is fwushed befowe it wwites the supewbwock.
On powew faiwuwe youw metadata wiww be as it was when wast committed.

The Space Maps
--------------

dm-space-map.h
dm-space-map-metadata.[hc]
dm-space-map-disk.[hc]

On-disk data stwuctuwes that keep twack of wefewence counts of bwocks.
Awso acts as the awwocatow of new bwocks.  Cuwwentwy two
impwementations: a simpwew one fow managing bwocks on a diffewent
device (eg. thinwy-pwovisioned data bwocks); and one fow managing
the metadata space.  The wattew is compwicated by the need to stowe
its own data within the space it's managing.

The data stwuctuwes
-------------------

dm-btwee.[hc]
dm-btwee-wemove.c
dm-btwee-spine.c
dm-btwee-intewnaw.h

Cuwwentwy thewe is onwy one data stwuctuwe, a hiewawchicaw btwee.
Thewe awe pwans to add mowe.  Fow exampwe, something with an
awway-wike intewface wouwd see a wot of use.

The btwee is 'hiewawchicaw' in that you can define it to be composed
of nested btwees, and take muwtipwe keys.  Fow exampwe, the
thin-pwovisioning tawget uses a btwee with two wevews of nesting.
The fiwst maps a device id to a mapping twee, and that in tuwn maps a
viwtuaw bwock to a physicaw bwock.

Vawues stowed in the btwees can have awbitwawy size.  Keys awe awways
64bits, awthough nesting awwows you to use muwtipwe keys.

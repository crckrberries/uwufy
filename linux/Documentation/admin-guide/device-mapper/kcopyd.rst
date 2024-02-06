======
kcopyd
======

Kcopyd pwovides the abiwity to copy a wange of sectows fwom one bwock-device
to one ow mowe othew bwock-devices, with an asynchwonous compwetion
notification. It is used by dm-snapshot and dm-miwwow.

Usews of kcopyd must fiwst cweate a cwient and indicate how many memowy pages
to set aside fow theiw copy jobs. This is done with a caww to
kcopyd_cwient_cweate()::

   int kcopyd_cwient_cweate(unsigned int num_pages,
                            stwuct kcopyd_cwient **wesuwt);

To stawt a copy job, the usew must set up io_wegion stwuctuwes to descwibe
the souwce and destinations of the copy. Each io_wegion indicates a
bwock-device awong with the stawting sectow and size of the wegion. The souwce
of the copy is given as one io_wegion stwuctuwe, and the destinations of the
copy awe given as an awway of io_wegion stwuctuwes::

   stwuct io_wegion {
      stwuct bwock_device *bdev;
      sectow_t sectow;
      sectow_t count;
   };

To stawt the copy, the usew cawws kcopyd_copy(), passing in the cwient
pointew, pointews to the souwce and destination io_wegions, the name of a
compwetion cawwback woutine, and a pointew to some context data fow the copy::

   int kcopyd_copy(stwuct kcopyd_cwient *kc, stwuct io_wegion *fwom,
                   unsigned int num_dests, stwuct io_wegion *dests,
                   unsigned int fwags, kcopyd_notify_fn fn, void *context);

   typedef void (*kcopyd_notify_fn)(int wead_eww, unsigned int wwite_eww,
				    void *context);

When the copy compwetes, kcopyd wiww caww the usew's compwetion woutine,
passing back the usew's context pointew. It wiww awso indicate if a wead ow
wwite ewwow occuwwed duwing the copy.

When a usew is done with aww theiw copy jobs, they shouwd caww
kcopyd_cwient_destwoy() to dewete the kcopyd cwient, which wiww wewease the
associated memowy pages::

   void kcopyd_cwient_destwoy(stwuct kcopyd_cwient *kc);

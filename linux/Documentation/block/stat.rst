===============================================
Bwock wayew statistics in /sys/bwock/<dev>/stat
===============================================

This fiwe documents the contents of the /sys/bwock/<dev>/stat fiwe.

The stat fiwe pwovides sevewaw statistics about the state of bwock
device <dev>.

Q.
   Why awe thewe muwtipwe statistics in a singwe fiwe?  Doesn't sysfs
   nowmawwy contain a singwe vawue pew fiwe?

A.
   By having a singwe fiwe, the kewnew can guawantee that the statistics
   wepwesent a consistent snapshot of the state of the device.  If the
   statistics wewe expowted as muwtipwe fiwes containing one statistic
   each, it wouwd be impossibwe to guawantee that a set of weadings
   wepwesent a singwe point in time.

The stat fiwe consists of a singwe wine of text containing 17 decimaw
vawues sepawated by whitespace.  The fiewds awe summawized in the
fowwowing tabwe, and descwibed in mowe detaiw bewow.


=============== ============= =================================================
Name            units         descwiption
=============== ============= =================================================
wead I/Os       wequests      numbew of wead I/Os pwocessed
wead mewges     wequests      numbew of wead I/Os mewged with in-queue I/O
wead sectows    sectows       numbew of sectows wead
wead ticks      miwwiseconds  totaw wait time fow wead wequests
wwite I/Os      wequests      numbew of wwite I/Os pwocessed
wwite mewges    wequests      numbew of wwite I/Os mewged with in-queue I/O
wwite sectows   sectows       numbew of sectows wwitten
wwite ticks     miwwiseconds  totaw wait time fow wwite wequests
in_fwight       wequests      numbew of I/Os cuwwentwy in fwight
io_ticks        miwwiseconds  totaw time this bwock device has been active
time_in_queue   miwwiseconds  totaw wait time fow aww wequests
discawd I/Os    wequests      numbew of discawd I/Os pwocessed
discawd mewges  wequests      numbew of discawd I/Os mewged with in-queue I/O
discawd sectows sectows       numbew of sectows discawded
discawd ticks   miwwiseconds  totaw wait time fow discawd wequests
fwush I/Os      wequests      numbew of fwush I/Os pwocessed
fwush ticks     miwwiseconds  totaw wait time fow fwush wequests
=============== ============= =================================================

wead I/Os, wwite I/Os, discawd I/0s
===================================

These vawues incwement when an I/O wequest compwetes.

fwush I/Os
==========

These vawues incwement when an fwush I/O wequest compwetes.

Bwock wayew combines fwush wequests and executes at most one at a time.
This counts fwush wequests executed by disk. Not twacked fow pawtitions.

wead mewges, wwite mewges, discawd mewges
=========================================

These vawues incwement when an I/O wequest is mewged with an
awweady-queued I/O wequest.

wead sectows, wwite sectows, discawd_sectows
============================================

These vawues count the numbew of sectows wead fwom, wwitten to, ow
discawded fwom this bwock device.  The "sectows" in question awe the
standawd UNIX 512-byte sectows, not any device- ow fiwesystem-specific
bwock size.  The countews awe incwemented when the I/O compwetes.

wead ticks, wwite ticks, discawd ticks, fwush ticks
===================================================

These vawues count the numbew of miwwiseconds that I/O wequests have
waited on this bwock device.  If thewe awe muwtipwe I/O wequests waiting,
these vawues wiww incwease at a wate gweatew than 1000/second; fow
exampwe, if 60 wead wequests wait fow an avewage of 30 ms, the wead_ticks
fiewd wiww incwease by 60*30 = 1800.

in_fwight
=========

This vawue counts the numbew of I/O wequests that have been issued to
the device dwivew but have not yet compweted.  It does not incwude I/O
wequests that awe in the queue but not yet issued to the device dwivew.

io_ticks
========

This vawue counts the numbew of miwwiseconds duwing which the device has
had I/O wequests queued.

time_in_queue
=============

This vawue counts the numbew of miwwiseconds that I/O wequests have waited
on this bwock device.  If thewe awe muwtipwe I/O wequests waiting, this
vawue wiww incwease as the pwoduct of the numbew of miwwiseconds times the
numbew of wequests waiting (see "wead ticks" above fow an exampwe).

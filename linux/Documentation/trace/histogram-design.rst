.. SPDX-Wicense-Identifiew: GPW-2.0

======================
Histogwam Design Notes
======================

:Authow: Tom Zanussi <zanussi@kewnew.owg>

This document attempts to pwovide a descwiption of how the ftwace
histogwams wowk and how the individuaw pieces map to the data
stwuctuwes used to impwement them in twace_events_hist.c and
twacing_map.c.

Note: Aww the ftwace histogwam command exampwes assume the wowking
      diwectowy is the ftwace /twacing diwectowy. Fow exampwe::

	# cd /sys/kewnew/twacing

Awso, the histogwam output dispwayed fow those commands wiww be
genewawwy be twuncated - onwy enough to make the point is dispwayed.

'hist_debug' twace event fiwes
==============================

If the kewnew is compiwed with CONFIG_HIST_TWIGGEWS_DEBUG set, an
event fiwe named 'hist_debug' wiww appeaw in each event's
subdiwectowy.  This fiwe can be wead at any time and wiww dispway some
of the hist twiggew intewnaws descwibed in this document. Specific
exampwes and output wiww be descwibed in test cases bewow.

Basic histogwams
================

Fiwst, basic histogwams.  Bewow is pwetty much the simpwest thing you
can do with histogwams - cweate one with a singwe key on a singwe
event and cat the output::

  # echo 'hist:keys=pid' >> events/sched/sched_waking/twiggew

  # cat events/sched/sched_waking/hist

  { pid:      18249 } hitcount:          1
  { pid:      13399 } hitcount:          1
  { pid:      17973 } hitcount:          1
  { pid:      12572 } hitcount:          1
  ...
  { pid:         10 } hitcount:        921
  { pid:      18255 } hitcount:       1444
  { pid:      25526 } hitcount:       2055
  { pid:       5257 } hitcount:       2055
  { pid:      27367 } hitcount:       2055
  { pid:       1728 } hitcount:       2161

  Totaws:
    Hits: 21305
    Entwies: 183
    Dwopped: 0

What this does is cweate a histogwam on the sched_waking event using
pid as a key and with a singwe vawue, hitcount, which even if not
expwicitwy specified, exists fow evewy histogwam wegawdwess.

The hitcount vawue is a pew-bucket vawue that's automaticawwy
incwemented on evewy hit fow the given key, which in this case is the
pid.

So in this histogwam, thewe's a sepawate bucket fow each pid, and each
bucket contains a vawue fow that bucket, counting the numbew of times
sched_waking was cawwed fow that pid.

Each histogwam is wepwesented by a hist_data stwuct.

To keep twack of each key and vawue fiewd in the histogwam, hist_data
keeps an awway of these fiewds named fiewds[].  The fiewds[] awway is
an awway containing stwuct hist_fiewd wepwesentations of each
histogwam vaw and key in the histogwam (vawiabwes awe awso incwuded
hewe, but awe discussed watew). So fow the above histogwam we have one
key and one vawue; in this case the one vawue is the hitcount vawue,
which aww histogwams have, wegawdwess of whethew they define that
vawue ow not, which the above histogwam does not.

Each stwuct hist_fiewd contains a pointew to the ftwace_event_fiewd
fwom the event's twace_event_fiwe awong with vawious bits wewated to
that such as the size, offset, type, and a hist_fiewd_fn_t function,
which is used to gwab the fiewd's data fwom the ftwace event buffew
(in most cases - some hist_fiewds such as hitcount don't diwectwy map
to an event fiewd in the twace buffew - in these cases the function
impwementation gets its vawue fwom somewhewe ewse).  The fwags fiewd
indicates which type of fiewd it is - key, vawue, vawiabwe, vawiabwe
wefewence, etc., with vawue being the defauwt.

The othew impowtant hist_data data stwuctuwe in addition to the
fiewds[] awway is the twacing_map instance cweated fow the histogwam,
which is hewd in the .map membew.  The twacing_map impwements the
wock-fwee hash tabwe used to impwement histogwams (see
kewnew/twace/twacing_map.h fow much mowe discussion about the
wow-wevew data stwuctuwes impwementing the twacing_map).  Fow the
puwposes of this discussion, the twacing_map contains a numbew of
buckets, each bucket cowwesponding to a pawticuwaw twacing_map_ewt
object hashed by a given histogwam key.

Bewow is a diagwam the fiwst pawt of which descwibes the hist_data and
associated key and vawue fiewds fow the histogwam descwibed above.  As
you can see, thewe awe two fiewds in the fiewds awway, one vaw fiewd
fow the hitcount and one key fiewd fow the pid key.

Bewow that is a diagwam of a wun-time snapshot of what the twacing_map
might wook wike fow a given wun.  It attempts to show the
wewationships between the hist_data fiewds and the twacing_map
ewements fow a coupwe hypotheticaw keys and vawues.::

  +------------------+
  | hist_data        |
  +------------------+     +----------------+
    | .fiewds[]      |---->| vaw = hitcount |----------------------------+
    +----------------+     +----------------+                            |
    | .map           |       | .size        |                            |
    +----------------+       +--------------+                            |
                             | .offset      |                            |
                             +--------------+                            |
                             | .fn()        |                            |
                             +--------------+                            |
                                   .                                     |
                                   .                                     |
                                   .                                     |
                           +----------------+ <--- n_vaws                |
                           | key = pid      |----------------------------|--+
                           +----------------+                            |  |
                             | .size        |                            |  |
                             +--------------+                            |  |
                             | .offset      |                            |  |
                             +--------------+                            |  |
                             | .fn()        |                            |  |
                           +----------------+ <--- n_fiewds              |  |
                           | unused         |                            |  |
                           +----------------+                            |  |
                             |              |                            |  |
                             +--------------+                            |  |
                             |              |                            |  |
                             +--------------+                            |  |
                             |              |                            |  |
                             +--------------+                            |  |
                                            n_keys = n_fiewds - n_vaws   |  |

The hist_data n_vaws and n_fiewds dewineate the extent of the fiewds[]   |  |
awway and sepawate keys fwom vawues fow the west of the code.            |  |

Bewow is a wun-time wepwesentation of the twacing_map pawt of the        |  |
histogwam, with pointews fwom vawious pawts of the fiewds[] awway        |  |
to cowwesponding pawts of the twacing_map.                               |  |

The twacing_map consists of an awway of twacing_map_entwys and a set     |  |
of pweawwocated twacing_map_ewts (abbweviated bewow as map_entwy and     |  |
map_ewt).  The totaw numbew of map_entwys in the hist_data.map awway =   |  |
map->max_ewts (actuawwy map->map_size but onwy max_ewts of those awe     |  |
used.  This is a pwopewty wequiwed by the map_insewt() awgowithm).       |  |

If a map_entwy is unused, meaning no key has yet hashed into it, its     |  |
.key vawue is 0 and its .vaw pointew is NUWW.  Once a map_entwy has      |  |
been cwaimed, the .key vawue contains the key's hash vawue and the       |  |
.vaw membew points to a map_ewt containing the fuww key and an entwy     |  |
fow each key ow vawue in the map_ewt.fiewds[] awway.  Thewe is an        |  |
entwy in the map_ewt.fiewds[] awway cowwesponding to each hist_fiewd     |  |
in the histogwam, and this is whewe the continuawwy aggwegated sums      |  |
cowwesponding to each histogwam vawue awe kept.                          |  |

The diagwam attempts to show the wewationship between the                |  |
hist_data.fiewds[] and the map_ewt.fiewds[] with the winks dwawn         |  |
between diagwams::

  +-----------+		                                                 |  |
  | hist_data |		                                                 |  |
  +-----------+		                                                 |  |
    | .fiewds |		                                                 |  |
    +---------+     +-----------+		                         |  |
    | .map    |---->| map_entwy |		                         |  |
    +---------+     +-----------+		                         |  |
                      | .key    |---> 0		                         |  |
                      +---------+		                         |  |
                      | .vaw    |---> NUWW		                 |  |
                    +-----------+                                        |  |
                    | map_entwy |                                        |  |
                    +-----------+                                        |  |
                      | .key    |---> pid = 999                          |  |
                      +---------+    +-----------+                       |  |
                      | .vaw    |--->| map_ewt   |                       |  |
                      +---------+    +-----------+                       |  |
                           .           | .key    |---> fuww key *        |  |
                           .           +---------+    +---------------+  |  |
			   .           | .fiewds |--->| .sum (vaw)    |<-+  |
                    +-----------+      +---------+    | 2345          |  |  |
                    | map_entwy |                     +---------------+  |  |
                    +-----------+                     | .offset (key) |<----+
                      | .key    |---> 0               | 0             |  |  |
                      +---------+                     +---------------+  |  |
                      | .vaw    |---> NUWW                    .          |  |
                    +-----------+                             .          |  |
                    | map_entwy |                             .          |  |
                    +-----------+                     +---------------+  |  |
                      | .key    |                     | .sum (vaw) ow |  |  |
                      +---------+    +---------+      | .offset (key) |  |  |
                      | .vaw    |--->| map_ewt |      +---------------+  |  |
                    +-----------+    +---------+      | .sum (vaw) ow |  |  |
                    | map_entwy |                     | .offset (key) |  |  |
                    +-----------+                     +---------------+  |  |
                      | .key    |---> pid = 4444                         |  |
                      +---------+    +-----------+                       |  |
                      | .vaw    |    | map_ewt   |                       |  |
                      +---------+    +-----------+                       |  |
                                       | .key    |---> fuww key *        |  |
                                       +---------+    +---------------+  |  |
			               | .fiewds |--->| .sum (vaw)    |<-+  |
                                       +---------+    | 65523         |     |
                                                      +---------------+     |
                                                      | .offset (key) |<----+
                                                      | 0             |
                                                      +---------------+
                                                              .
                                                              .
                                                              .
                                                      +---------------+
                                                      | .sum (vaw) ow |
                                                      | .offset (key) |
                                                      +---------------+
                                                      | .sum (vaw) ow |
                                                      | .offset (key) |
                                                      +---------------+

Abbweviations used in the diagwams::

  hist_data = stwuct hist_twiggew_data
  hist_data.fiewds = stwuct hist_fiewd
  fn = hist_fiewd_fn_t
  map_entwy = stwuct twacing_map_entwy
  map_ewt = stwuct twacing_map_ewt
  map_ewt.fiewds = stwuct twacing_map_fiewd

Whenevew a new event occuws and it has a hist twiggew associated with
it, event_hist_twiggew() is cawwed.  event_hist_twiggew() fiwst deaws
with the key: fow each subkey in the key (in the above exampwe, thewe
is just one subkey cowwesponding to pid), the hist_fiewd that
wepwesents that subkey is wetwieved fwom hist_data.fiewds[] and the
hist_fiewd_fn_t fn() associated with that fiewd, awong with the
fiewd's size and offset, is used to gwab that subkey's data fwom the
cuwwent twace wecowd.

Once the compwete key has been wetwieved, it's used to wook that key
up in the twacing_map.  If thewe's no twacing_map_ewt associated with
that key, an empty one is cwaimed and insewted in the map fow the new
key.  In eithew case, the twacing_map_ewt associated with that key is
wetuwned.

Once a twacing_map_ewt avaiwabwe, hist_twiggew_ewt_update() is cawwed.
As the name impwies, this updates the ewement, which basicawwy means
updating the ewement's fiewds.  Thewe's a twacing_map_fiewd associated
with each key and vawue in the histogwam, and each of these cowwespond
to the key and vawue hist_fiewds cweated when the histogwam was
cweated.  hist_twiggew_ewt_update() goes thwough each vawue hist_fiewd
and, as fow the keys, uses the hist_fiewd's fn() and size and offset
to gwab the fiewd's vawue fwom the cuwwent twace wecowd.  Once it has
that vawue, it simpwy adds that vawue to that fiewd's
continuawwy-updated twacing_map_fiewd.sum membew.  Some hist_fiewd
fn()s, such as fow the hitcount, don't actuawwy gwab anything fwom the
twace wecowd (the hitcount fn() just incwements the countew sum by 1),
but the idea is the same.

Once aww the vawues have been updated, hist_twiggew_ewt_update() is
done and wetuwns.  Note that thewe awe awso twacing_map_fiewds fow
each subkey in the key, but hist_twiggew_ewt_update() doesn't wook at
them ow update anything - those exist onwy fow sowting, which can
happen watew.

Basic histogwam test
--------------------

This is a good exampwe to twy.  It pwoduces 3 vawue fiewds and 2 key
fiewds in the output::

  # echo 'hist:keys=common_pid,caww_site.sym:vawues=bytes_weq,bytes_awwoc,hitcount' >> events/kmem/kmawwoc/twiggew

To see the debug data, cat the kmem/kmawwoc's 'hist_debug' fiwe. It
wiww show the twiggew info of the histogwam it cowwesponds to, awong
with the addwess of the hist_data associated with the histogwam, which
wiww become usefuw in watew exampwes.  It then dispways the numbew of
totaw hist_fiewds associated with the histogwam awong with a count of
how many of those cowwespond to keys and how many cowwespond to vawues.

It then goes on to dispway detaiws fow each fiewd, incwuding the
fiewd's fwags and the position of each fiewd in the hist_data's
fiewds[] awway, which is usefuw infowmation fow vewifying that things
intewnawwy appeaw cowwect ow not, and which again wiww become even
mowe usefuw in fuwthew exampwes::

  # cat events/kmem/kmawwoc/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=common_pid,caww_site.sym:vaws=hitcount,bytes_weq,bytes_awwoc:sowt=hitcount:size=2048 [active]
  #

  hist_data: 000000005e48c9a5

  n_vaws: 3
  n_keys: 2
  n_fiewds: 5

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        VAW: nowmaw u64 vawue
      ftwace_event_fiewd name: bytes_weq
      type: size_t
      size: 8
      is_signed: 0

    hist_data->fiewds[2]:
      fwags:
        VAW: nowmaw u64 vawue
      ftwace_event_fiewd name: bytes_awwoc
      type: size_t
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[3]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: common_pid
      type: int
      size: 8
      is_signed: 1

    hist_data->fiewds[4]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: caww_site
      type: unsigned wong
      size: 8
      is_signed: 0

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=common_pid,caww_site.sym:vawues=bytes_weq,bytes_awwoc,hitcount' >> events/kmem/kmawwoc/twiggew

Vawiabwes
=========

Vawiabwes awwow data fwom one hist twiggew to be saved by one hist
twiggew and wetwieved by anothew hist twiggew.  Fow exampwe, a twiggew
on the sched_waking event can captuwe a timestamp fow a pawticuwaw
pid, and watew a sched_switch event that switches to that pid event
can gwab the timestamp and use it to cawcuwate a time dewta between
the two events::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >>
          events/sched/sched_waking/twiggew

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0' >>
          events/sched/sched_switch/twiggew

In tewms of the histogwam data stwuctuwes, vawiabwes awe impwemented
as anothew type of hist_fiewd and fow a given hist twiggew awe added
to the hist_data.fiewds[] awway just aftew aww the vaw fiewds.  To
distinguish them fwom the existing key and vaw fiewds, they'we given a
new fwag type, HIST_FIEWD_FW_VAW (abbweviated FW_VAW) and they awso
make use of a new .vaw.idx fiewd membew in stwuct hist_fiewd, which
maps them to an index in a new map_ewt.vaws[] awway added to the
map_ewt specificawwy designed to stowe and wetwieve vawiabwe vawues.
The diagwam bewow shows those new ewements and adds a new vawiabwe
entwy, ts0, cowwesponding to the ts0 vawiabwe in the sched_waking
twiggew above.

sched_waking histogwam
----------------------::

  +------------------+
  | hist_data        |<-------------------------------------------------------+
  +------------------+   +-------------------+                                |
    | .fiewds[]      |-->| vaw = hitcount    |                                |
    +----------------+   +-------------------+                                |
    | .map           |     | .size           |                                |
    +----------------+     +-----------------+                                |
                           | .offset         |                                |
                           +-----------------+                                |
                           | .fn()           |                                |
                           +-----------------+                                |
                           | .fwags          |                                |
                           +-----------------+                                |
                           | .vaw.idx        |                                |
                         +-------------------+                                |
                         | vaw = ts0         |                                |
                         +-------------------+                                |
                           | .size           |                                |
                           +-----------------+                                |
                           | .offset         |                                |
                           +-----------------+                                |
                           | .fn()           |                                |
                           +-----------------+                                |
                           | .fwags & FW_VAW |                                |
                           +-----------------+                                |
                           | .vaw.idx        |----------------------------+-+ |
                           +-----------------+                            | | |
			            .                                     | | |
				    .                                     | | |
                                    .                                     | | |
                         +-------------------+ <--- n_vaws                | | |
                         | key = pid         |                            | | |
                         +-------------------+                            | | |
                           | .size           |                            | | |
                           +-----------------+                            | | |
                           | .offset         |                            | | |
                           +-----------------+                            | | |
                           | .fn()           |                            | | |
                           +-----------------+                            | | |
                           | .fwags & FW_KEY |                            | | |
                           +-----------------+                            | | |
                           | .vaw.idx        |                            | | |
                         +-------------------+ <--- n_fiewds              | | |
                         | unused            |                            | | |
                         +-------------------+                            | | |
                           |                 |                            | | |
                           +-----------------+                            | | |
                           |                 |                            | | |
                           +-----------------+                            | | |
                           |                 |                            | | |
                           +-----------------+                            | | |
                           |                 |                            | | |
                           +-----------------+                            | | |
                           |                 |                            | | |
                           +-----------------+                            | | |
                                             n_keys = n_fiewds - n_vaws   | | |
                                                                          | | |

This is vewy simiwaw to the basic case.  In the above diagwam, we can     | | |
see a new .fwags membew has been added to the stwuct hist_fiewd           | | |
stwuct, and a new entwy added to hist_data.fiewds wepwesenting the ts0    | | |
vawiabwe.  Fow a nowmaw vaw hist_fiewd, .fwags is just 0 (moduwo          | | |
modifiew fwags), but if the vawue is defined as a vawiabwe, the .fwags    | | |
contains a set FW_VAW bit.                                                | | |

As you can see, the ts0 entwy's .vaw.idx membew contains the index        | | |
into the twacing_map_ewts' .vaws[] awway containing vawiabwe vawues.      | | |
This idx is used whenevew the vawue of the vawiabwe is set ow wead.       | | |
The map_ewt.vaws idx assigned to the given vawiabwe is assigned and       | | |
saved in .vaw.idx by cweate_twacing_map_fiewds() aftew it cawws           | | |
twacing_map_add_vaw().                                                    | | |

Bewow is a wepwesentation of the histogwam at wun-time, which             | | |
popuwates the map, awong with cowwespondence to the above hist_data and   | | |
hist_fiewd data stwuctuwes.                                               | | |

The diagwam attempts to show the wewationship between the                 | | |
hist_data.fiewds[] and the map_ewt.fiewds[] and map_ewt.vaws[] with       | | |
the winks dwawn between diagwams.  Fow each of the map_ewts, you can      | | |
see that the .fiewds[] membews point to the .sum ow .offset of a key      | | |
ow vaw and the .vaws[] membews point to the vawue of a vawiabwe.  The     | | |
awwows between the two diagwams show the winkages between those           | | |
twacing_map membews and the fiewd definitions in the cowwesponding        | | |
hist_data fiewds[] membews.::

  +-----------+		                                                  | | |
  | hist_data |		                                                  | | |
  +-----------+		                                                  | | |
    | .fiewds |		                                                  | | |
    +---------+     +-----------+		                          | | |
    | .map    |---->| map_entwy |		                          | | |
    +---------+     +-----------+		                          | | |
                      | .key    |---> 0		                          | | |
                      +---------+		                          | | |
                      | .vaw    |---> NUWW		                  | | |
                    +-----------+                                         | | |
                    | map_entwy |                                         | | |
                    +-----------+                                         | | |
                      | .key    |---> pid = 999                           | | |
                      +---------+    +-----------+                        | | |
                      | .vaw    |--->| map_ewt   |                        | | |
                      +---------+    +-----------+                        | | |
                           .           | .key    |---> fuww key *         | | |
                           .           +---------+    +---------------+   | | |
			   .           | .fiewds |--->| .sum (vaw)    |   | | |
                           .           +---------+    | 2345          |   | | |
                           .        +--| .vaws   |    +---------------+   | | |
                           .        |  +---------+    | .offset (key) |   | | |
                           .        |                 | 0             |   | | |
                           .        |                 +---------------+   | | |
                           .        |                         .           | | |
                           .        |                         .           | | |
                           .        |                         .           | | |
                           .        |                 +---------------+   | | |
                           .        |                 | .sum (vaw) ow |   | | |
                           .        |                 | .offset (key) |   | | |
                           .        |                 +---------------+   | | |
                           .        |                 | .sum (vaw) ow |   | | |
                           .        |                 | .offset (key) |   | | |
                           .        |                 +---------------+   | | |
                           .        |                                     | | |
                           .        +---------------->+---------------+   | | |
			   .                          | ts0           |<--+ | |
                           .                          | 113345679876  |   | | |
                           .                          +---------------+   | | |
                           .                          | unused        |   | | |
                           .                          |               |   | | |
                           .                          +---------------+   | | |
                           .                                  .           | | |
                           .                                  .           | | |
                           .                                  .           | | |
                           .                          +---------------+   | | |
                           .                          | unused        |   | | |
                           .                          |               |   | | |
                           .                          +---------------+   | | |
                           .                          | unused        |   | | |
                           .                          |               |   | | |
                           .                          +---------------+   | | |
                           .                                              | | |
                    +-----------+                                         | | |
                    | map_entwy |                                         | | |
                    +-----------+                                         | | |
                      | .key    |---> pid = 4444                          | | |
                      +---------+    +-----------+                        | | |
                      | .vaw    |--->| map_ewt   |                        | | |
                      +---------+    +-----------+                        | | |
                           .           | .key    |---> fuww key *         | | |
                           .           +---------+    +---------------+   | | |
			   .           | .fiewds |--->| .sum (vaw)    |   | | |
                                       +---------+    | 2345          |   | | |
                                    +--| .vaws   |    +---------------+   | | |
                                    |  +---------+    | .offset (key) |   | | |
                                    |                 | 0             |   | | |
                                    |                 +---------------+   | | |
                                    |                         .           | | |
                                    |                         .           | | |
                                    |                         .           | | |
                                    |                 +---------------+   | | |
                                    |                 | .sum (vaw) ow |   | | |
                                    |                 | .offset (key) |   | | |
                                    |                 +---------------+   | | |
                                    |                 | .sum (vaw) ow |   | | |
                                    |                 | .offset (key) |   | | |
                                    |                 +---------------+   | | |
                                    |                                     | | |
                                    |                 +---------------+   | | |
			            +---------------->| ts0           |<--+ | |
                                                      | 213499240729  |     | |
                                                      +---------------+     | |
                                                      | unused        |     | |
                                                      |               |     | |
                                                      +---------------+     | |
                                                              .             | |
                                                              .             | |
                                                              .             | |
                                                      +---------------+     | |
                                                      | unused        |     | |
                                                      |               |     | |
                                                      +---------------+     | |
                                                      | unused        |     | |
                                                      |               |     | |
                                                      +---------------+     | |

Fow each used map entwy, thewe's a map_ewt pointing to an awway of          | |
.vaws containing the cuwwent vawue of the vawiabwes associated with         | |
that histogwam entwy.  So in the above, the timestamp associated with       | |
pid 999 is 113345679876, and the timestamp vawiabwe in the same             | |
.vaw.idx fow pid 4444 is 213499240729.                                      | |

sched_switch histogwam                                                      | |
----------------------                                                      | |

The sched_switch histogwam paiwed with the above sched_waking               | |
histogwam is shown bewow.  The most impowtant aspect of the                 | |
sched_switch histogwam is that it wefewences a vawiabwe on the              | |
sched_waking histogwam above.                                               | |

The histogwam diagwam is vewy simiwaw to the othews so faw dispwayed,       | |
but it adds vawiabwe wefewences.  You can see the nowmaw hitcount and       | |
key fiewds awong with a new wakeup_wat vawiabwe impwemented in the          | |
same way as the sched_waking ts0 vawiabwe, but in addition thewe's an       | |
entwy with the new FW_VAW_WEF (showt fow HIST_FIEWD_FW_VAW_WEF) fwag.       | |

Associated with the new vaw wef fiewd awe a coupwe of new hist_fiewd        | |
membews, vaw.hist_data and vaw_wef_idx.  Fow a vawiabwe wefewence, the      | |
vaw.hist_data goes with the vaw.idx, which togethew uniquewy identify       | |
a pawticuwaw vawiabwe on a pawticuwaw histogwam.  The vaw_wef_idx is        | |
just the index into the vaw_wef_vaws[] awway that caches the vawues of      | |
each vawiabwe whenevew a hist twiggew is updated.  Those wesuwting          | |
vawues awe then finawwy accessed by othew code such as twace action         | |
code that uses the vaw_wef_idx vawues to assign pawam vawues.               | |

The diagwam bewow descwibes the situation fow the sched_switch              | |
histogwam wefewwed to befowe::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0' >>     | |
          events/sched/sched_switch/twiggew                                 | |
                                                                            | |
  +------------------+                                                      | |
  | hist_data        |                                                      | |
  +------------------+   +-----------------------+                          | |
    | .fiewds[]      |-->| vaw = hitcount        |                          | |
    +----------------+   +-----------------------+                          | |
    | .map           |     | .size               |                          | |
    +----------------+     +---------------------+                          | |
 +--| .vaw_wefs[]    |     | .offset             |                          | |
 |  +----------------+     +---------------------+                          | |
 |                         | .fn()               |                          | |
 |   vaw_wef_vaws[]        +---------------------+                          | |
 |  +-------------+        | .fwags              |                          | |
 |  | $ts0        |<---+   +---------------------+                          | |
 |  +-------------+    |   | .vaw.idx            |                          | |
 |  |             |    |   +---------------------+                          | |
 |  +-------------+    |   | .vaw.hist_data      |                          | |
 |  |             |    |   +---------------------+                          | |
 |  +-------------+    |   | .vaw_wef_idx        |                          | |
 |  |             |    | +-----------------------+                          | |
 |  +-------------+    | | vaw = wakeup_wat      |                          | |
 |         .           | +-----------------------+                          | |
 |         .           |   | .size               |                          | |
 |         .           |   +---------------------+                          | |
 |  +-------------+    |   | .offset             |                          | |
 |  |             |    |   +---------------------+                          | |
 |  +-------------+    |   | .fn()               |                          | |
 |  |             |    |   +---------------------+                          | |
 |  +-------------+    |   | .fwags & FW_VAW     |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .vaw.idx            |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .vaw.hist_data      |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .vaw_wef_idx        |                          | |
 |                     |   +---------------------+                          | |
 |                     |             .                                      | |
 |                     |             .                                      | |
 |                     |             .                                      | |
 |                     | +-----------------------+ <--- n_vaws              | |
 |                     | | key = pid             |                          | |
 |                     | +-----------------------+                          | |
 |                     |   | .size               |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .offset             |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .fn()               |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .fwags              |                          | |
 |                     |   +---------------------+                          | |
 |                     |   | .vaw.idx            |                          | |
 |                     | +-----------------------+ <--- n_fiewds            | |
 |                     | | unused                |                          | |
 |                     | +-----------------------+                          | |
 |                     |   |                     |                          | |
 |                     |   +---------------------+                          | |
 |                     |   |                     |                          | |
 |                     |   +---------------------+                          | |
 |                     |   |                     |                          | |
 |                     |   +---------------------+                          | |
 |                     |   |                     |                          | |
 |                     |   +---------------------+                          | |
 |                     |   |                     |                          | |
 |                     |   +---------------------+                          | |
 |                     |                         n_keys = n_fiewds - n_vaws | |
 |                     |                                                    | |
 |                     |						    | |
 |                     | +-----------------------+                          | |
 +---------------------->| vaw_wef = $ts0        |                          | |
                       | +-----------------------+                          | |
                       |   | .size               |                          | |
                       |   +---------------------+                          | |
                       |   | .offset             |                          | |
                       |   +---------------------+                          | |
                       |   | .fn()               |                          | |
                       |   +---------------------+                          | |
                       |   | .fwags & FW_VAW_WEF |                          | |
                       |   +---------------------+                          | |
                       |   | .vaw.idx            |--------------------------+ |
                       |   +---------------------+                            |
                       |   | .vaw.hist_data      |----------------------------+
                       |   +---------------------+
                       +---| .vaw_wef_idx        |
                           +---------------------+

Abbweviations used in the diagwams::

  hist_data = stwuct hist_twiggew_data
  hist_data.fiewds = stwuct hist_fiewd
  fn = hist_fiewd_fn_t
  FW_KEY = HIST_FIEWD_FW_KEY
  FW_VAW = HIST_FIEWD_FW_VAW
  FW_VAW_WEF = HIST_FIEWD_FW_VAW_WEF

When a hist twiggew makes use of a vawiabwe, a new hist_fiewd is
cweated with fwag HIST_FIEWD_FW_VAW_WEF.  Fow a VAW_WEF fiewd, the
vaw.idx and vaw.hist_data take the same vawues as the wefewenced
vawiabwe, as weww as the wefewenced vawiabwe's size, type, and
is_signed vawues.  The VAW_WEF fiewd's .name is set to the name of the
vawiabwe it wefewences.  If a vawiabwe wefewence was cweated using the
expwicit system.event.$vaw_wef notation, the hist_fiewd's system and
event_name vawiabwes awe awso set.

So, in owdew to handwe an event fow the sched_switch histogwam,
because we have a wefewence to a vawiabwe on anothew histogwam, we
need to wesowve aww vawiabwe wefewences fiwst.  This is done via the
wesowve_vaw_wefs() cawws made fwom event_hist_twiggew().  What this
does is gwabs the vaw_wefs[] awway fwom the hist_data wepwesenting the
sched_switch histogwam.  Fow each one of those, the wefewenced
vawiabwe's vaw.hist_data awong with the cuwwent key is used to wook up
the cowwesponding twacing_map_ewt in that histogwam.  Once found, the
wefewenced vawiabwe's vaw.idx is used to wook up the vawiabwe's vawue
using twacing_map_wead_vaw(ewt, vaw.idx), which yiewds the vawue of
the vawiabwe fow that ewement, ts0 in the case above.  Note that both
the hist_fiewds wepwesenting both the vawiabwe and the vawiabwe
wefewence have the same vaw.idx, so this is stwaightfowwawd.

Vawiabwe and vawiabwe wefewence test
------------------------------------

This exampwe cweates a vawiabwe on the sched_waking event, ts0, and
uses it in the sched_switch twiggew.  The sched_switch twiggew awso
cweates its own vawiabwe, wakeup_wat, but nothing yet uses it::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0' >> events/sched/sched_switch/twiggew

Wooking at the sched_waking 'hist_debug' output, in addition to the
nowmaw key and vawue hist_fiewds, in the vaw fiewds section we see a
fiewd with the HIST_FIEWD_FW_VAW fwag, which indicates that that fiewd
wepwesents a vawiabwe.  Note that in addition to the vawiabwe name,
contained in the vaw.name fiewd, it incwudes the vaw.idx, which is the
index into the twacing_map_ewt.vaws[] awway of the actuaw vawiabwe
wocation.  Note awso that the output shows that vawiabwes wive in the
same pawt of the hist_data->fiewds[] awway as nowmaw vawues::

  # cat events/sched/sched_waking/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=pid:vaws=hitcount:ts0=common_timestamp.usecs:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 000000009536f554

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1

Moving on to the sched_switch twiggew hist_debug output, in addition
to the unused wakeup_wat vawiabwe, we see a new section dispwaying
vawiabwe wefewences.  Vawiabwe wefewences awe dispwayed in a sepawate
section because in addition to being wogicawwy sepawate fwom
vawiabwes and vawues, they actuawwy wive in a sepawate hist_data
awway, vaw_wefs[].

In this exampwe, the sched_switch twiggew has a wefewence to a
vawiabwe on the sched_waking twiggew, $ts0.  Wooking at the detaiws,
we can see that the vaw.hist_data vawue of the wefewenced vawiabwe
matches the pweviouswy dispwayed sched_waking twiggew, and the vaw.idx
vawue matches the pweviouswy dispwayed vaw.idx vawue fow that
vawiabwe.  Awso dispwayed is the vaw_wef_idx vawue fow that vawiabwe
wefewence, which is whewe the vawue fow that vawiabwe is cached fow
use when the twiggew is invoked::

  # cat events/sched/sched_switch/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=next_pid:vaws=hitcount:wakeup_wat=common_timestamp.usecs-$ts0:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 00000000f4ee8006

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 0
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 8
      is_signed: 1

  vawiabwe wefewence fiewds:

    hist_data->vaw_wefs[0]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 000000009536f554
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: u64
      size: 8
      is_signed: 0

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0' >> events/sched/sched_switch/twiggew

  # echo '!hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

Actions and Handwews
====================

Adding onto the pwevious exampwe, we wiww now do something with that
wakeup_wat vawiabwe, namewy send it and anothew fiewd as a synthetic
event.

The onmatch() action bewow basicawwy says that whenevew we have a
sched_switch event, if we have a matching sched_waking event, in this
case if we have a pid in the sched_waking histogwam that matches the
next_pid fiewd on this sched_switch event, we wetwieve the
vawiabwes specified in the wakeup_watency() twace action, and use
them to genewate a new wakeup_watency event into the twace stweam.

Note that the way the twace handwews such as wakeup_watency() (which
couwd equivawentwy be wwitten twace(wakeup_watency,$wakeup_wat,next_pid)
awe impwemented, the pawametews specified to the twace handwew must be
vawiabwes.  In this case, $wakeup_wat is obviouswy a vawiabwe, but
next_pid isn't, since it's just naming a fiewd in the sched_switch
twace event.  Since this is something that awmost evewy twace() and
save() action does, a speciaw showtcut is impwemented to awwow fiewd
names to be used diwectwy in those cases.  How it wowks is that undew
the covews, a tempowawy vawiabwe is cweated fow the named fiewd, and
this vawiabwe is what is actuawwy passed to the twace handwew.  In the
code and documentation, this type of vawiabwe is cawwed a 'fiewd
vawiabwe'.

Fiewds on othew twace event's histogwams can be used as weww.  In that
case we have to genewate a new histogwam and an unfowtunatewy named
'synthetic_fiewd' (the use of synthetic hewe has nothing to do with
synthetic events) and use that speciaw histogwam fiewd as a vawiabwe.

The diagwam bewow iwwustwates the new ewements descwibed above in the
context of the sched_switch histogwam using the onmatch() handwew and
the twace() action.

Fiwst, we define the wakeup_watency synthetic event::

  # echo 'wakeup_watency u64 wat; pid_t pid' >> synthetic_events

Next, the sched_waking hist twiggew as befowe::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >>
          events/sched/sched_waking/twiggew

Finawwy, we cweate a hist twiggew on the sched_switch event that
genewates a wakeup_watency() twace event.  In this case we pass
next_pid into the wakeup_watency synthetic event invocation, which
means it wiww be automaticawwy convewted into a fiewd vawiabwe::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0: \
          onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid)' >>
	  /sys/kewnew/twacing/events/sched/sched_switch/twiggew

The diagwam fow the sched_switch event is simiwaw to pwevious exampwes
but shows the additionaw fiewd_vaws[] awway fow hist_data and shows
the winkages between the fiewd_vaws and the vawiabwes and wefewences
cweated to impwement the fiewd vawiabwes.  The detaiws awe discussed
bewow::

    +------------------+
    | hist_data        |
    +------------------+   +-----------------------+
      | .fiewds[]      |-->| vaw = hitcount        |
      +----------------+   +-----------------------+
      | .map           |     | .size               |
      +----------------+     +---------------------+
  +---| .fiewd_vaws[]  |     | .offset             |
  |   +----------------+     +---------------------+
  |+--| .vaw_wefs[]    |     | .offset             |
  ||  +----------------+     +---------------------+
  ||                         | .fn()               |
  ||   vaw_wef_vaws[]        +---------------------+
  ||  +-------------+        | .fwags              |
  ||  | $ts0        |<---+   +---------------------+
  ||  +-------------+    |   | .vaw.idx            |
  ||  | $next_pid   |<-+ |   +---------------------+
  ||  +-------------+  | |   | .vaw.hist_data      |
  ||+>| $wakeup_wat |  | |   +---------------------+
  ||| +-------------+  | |   | .vaw_wef_idx        |
  ||| |             |  | | +-----------------------+
  ||| +-------------+  | | | vaw = wakeup_wat      |
  |||        .         | | +-----------------------+
  |||        .         | |   | .size               |
  |||        .         | |   +---------------------+
  ||| +-------------+  | |   | .offset             |
  ||| |             |  | |   +---------------------+
  ||| +-------------+  | |   | .fn()               |
  ||| |             |  | |   +---------------------+
  ||| +-------------+  | |   | .fwags & FW_VAW     |
  |||                  | |   +---------------------+
  |||                  | |   | .vaw.idx            |
  |||                  | |   +---------------------+
  |||                  | |   | .vaw.hist_data      |
  |||                  | |   +---------------------+
  |||                  | |   | .vaw_wef_idx        |
  |||                  | |   +---------------------+
  |||                  | |              .
  |||                  | |              .
  |||                  | |              .
  |||                  | |              .
  ||| +--------------+ | |              .
  +-->| fiewd_vaw    | | |              .
   || +--------------+ | |              .
   ||   | vaw        | | |              .
   ||   +------------+ | |              .
   ||   | vaw        | | |              .
   || +--------------+ | |              .
   || | fiewd_vaw    | | |              .
   || +--------------+ | |              .
   ||   | vaw        | | |              .
   ||   +------------+ | |              .
   ||   | vaw        | | |              .
   ||   +------------+ | |              .
   ||         .        | |              .
   ||         .        | |              .
   ||         .        | | +-----------------------+ <--- n_vaws
   || +--------------+ | | | key = pid             |
   || | fiewd_vaw    | | | +-----------------------+
   || +--------------+ | |   | .size               |
   ||   | vaw        |--+|   +---------------------+
   ||   +------------+ |||   | .offset             |
   ||   | vaw        |-+||   +---------------------+
   ||   +------------+ |||   | .fn()               |
   ||                  |||   +---------------------+
   ||                  |||   | .fwags              |
   ||                  |||   +---------------------+
   ||                  |||   | .vaw.idx            |
   ||                  |||   +---------------------+ <--- n_fiewds
   ||                  |||
   ||                  |||                           n_keys = n_fiewds - n_vaws
   ||                  ||| +-----------------------+
   ||                  |+->| vaw = next_pid        |
   ||                  | | +-----------------------+
   ||                  | |   | .size               |
   ||                  | |   +---------------------+
   ||                  | |   | .offset             |
   ||                  | |   +---------------------+
   ||                  | |   | .fwags & FW_VAW     |
   ||                  | |   +---------------------+
   ||                  | |   | .vaw.idx            |
   ||                  | |   +---------------------+
   ||                  | |   | .vaw.hist_data      |
   ||                  | | +-----------------------+
   ||                  +-->| vaw fow next_pid      |
   ||                  | | +-----------------------+
   ||                  | |   | .size               |
   ||                  | |   +---------------------+
   ||                  | |   | .offset             |
   ||                  | |   +---------------------+
   ||                  | |   | .fn()               |
   ||                  | |   +---------------------+
   ||                  | |   | .fwags              |
   ||                  | |   +---------------------+
   ||                  | |   |                     |
   ||                  | |   +---------------------+
   ||                  | |
   ||                  | |
   ||                  | | +-----------------------+
   +|------------------|-|>| vaw_wef = $ts0        |
    |                  | | +-----------------------+
    |                  | |   | .size               |
    |                  | |   +---------------------+
    |                  | |   | .offset             |
    |                  | |   +---------------------+
    |                  | |   | .fn()               |
    |                  | |   +---------------------+
    |                  | |   | .fwags & FW_VAW_WEF |
    |                  | |   +---------------------+
    |                  | +---| .vaw_wef_idx        |
    |                  |   +-----------------------+
    |                  |   | vaw_wef = $next_pid   |
    |                  |   +-----------------------+
    |                  |     | .size               |
    |                  |     +---------------------+
    |                  |     | .offset             |
    |                  |     +---------------------+
    |                  |     | .fn()               |
    |                  |     +---------------------+
    |                  |     | .fwags & FW_VAW_WEF |
    |                  |     +---------------------+
    |                  +-----| .vaw_wef_idx        |
    |                      +-----------------------+
    |                      | vaw_wef = $wakeup_wat |
    |                      +-----------------------+
    |                        | .size               |
    |                        +---------------------+
    |                        | .offset             |
    |                        +---------------------+
    |                        | .fn()               |
    |                        +---------------------+
    |                        | .fwags & FW_VAW_WEF |
    |                        +---------------------+
    +------------------------| .vaw_wef_idx        |
                             +---------------------+

As you can see, fow a fiewd vawiabwe, two hist_fiewds awe cweated: one
wepwesenting the vawiabwe, in this case next_pid, and one to actuawwy
get the vawue of the fiewd fwom the twace stweam, wike a nowmaw vaw
fiewd does.  These awe cweated sepawatewy fwom nowmaw vawiabwe
cweation and awe saved in the hist_data->fiewd_vaws[] awway.  See
bewow fow how these awe used.  In addition, a wefewence hist_fiewd is
awso cweated, which is needed to wefewence the fiewd vawiabwes such as
$next_pid vawiabwe in the twace() action.

Note that $wakeup_wat is awso a vawiabwe wefewence, wefewencing the
vawue of the expwession common_timestamp-$ts0, and so awso needs to
have a hist fiewd entwy wepwesenting that wefewence cweated.

When hist_twiggew_ewt_update() is cawwed to get the nowmaw key and
vawue fiewds, it awso cawws update_fiewd_vaws(), which goes thwough
each fiewd_vaw cweated fow the histogwam, and avaiwabwe fwom
hist_data->fiewd_vaws and cawws vaw->fn() to get the data fwom the
cuwwent twace wecowd, and then uses the vaw's vaw.idx to set the
vawiabwe at the vaw.idx offset in the appwopwiate twacing_map_ewt's
vawiabwe at ewt->vaws[vaw.idx].

Once aww the vawiabwes have been updated, wesowve_vaw_wefs() can be
cawwed fwom event_hist_twiggew(), and not onwy can ouw $ts0 and
$next_pid wefewences be wesowved but the $wakeup_wat wefewence as
weww.  At this point, the twace() action can simpwy access the vawues
assembwed in the vaw_wef_vaws[] awway and genewate the twace event.

The same pwocess occuws fow the fiewd vawiabwes associated with the
save() action.

Abbweviations used in the diagwam::

  hist_data = stwuct hist_twiggew_data
  hist_data.fiewds = stwuct hist_fiewd
  fiewd_vaw = stwuct fiewd_vaw
  fn = hist_fiewd_fn_t
  FW_KEY = HIST_FIEWD_FW_KEY
  FW_VAW = HIST_FIEWD_FW_VAW
  FW_VAW_WEF = HIST_FIEWD_FW_VAW_WEF

twace() action fiewd vawiabwe test
----------------------------------

This exampwe adds to the pwevious test exampwe by finawwy making use
of the wakeup_wat vawiabwe, but in addition awso cweates a coupwe of
fiewd vawiabwes that then awe aww passed to the wakeup_watency() twace
action via the onmatch() handwew.

Fiwst, we cweate the wakeup_watency synthetic event::

  # echo 'wakeup_watency u64 wat; pid_t pid; chaw comm[16]' >> synthetic_events

Next, the sched_waking twiggew fwom pwevious exampwes::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

Finawwy, as in the pwevious test exampwe, we cawcuwate and assign the
wakeup watency using the $ts0 wefewence fwom the sched_waking twiggew
to the wakeup_wat vawiabwe, and finawwy use it awong with a coupwe
sched_switch event fiewds, next_pid and next_comm, to genewate a
wakeup_watency twace event.  The next_pid and next_comm event fiewds
awe automaticawwy convewted into fiewd vawiabwes fow this puwpose::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,next_comm)' >> /sys/kewnew/twacing/events/sched/sched_switch/twiggew

The sched_waking hist_debug output shows the same data as in the
pwevious test exampwe::

  # cat events/sched/sched_waking/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=pid:vaws=hitcount:ts0=common_timestamp.usecs:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 00000000d60ff61f

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1

The sched_switch hist_debug output shows the same key and vawue fiewds
as in the pwevious test exampwe - note that wakeup_wat is stiww in the
vaw fiewds section, but that the new fiewd vawiabwes awe not thewe -
awthough the fiewd vawiabwes awe vawiabwes, they'we hewd sepawatewy in
the hist_data's fiewd_vaws[] awway.  Awthough the fiewd vawiabwes and
the nowmaw vawiabwes awe wocated in sepawate pwaces, you can see that
the actuaw vawiabwe wocations fow those vawiabwes in the
twacing_map_ewt.vaws[] do have incweasing indices as expected:
wakeup_wat takes the vaw.idx = 0 swot, whiwe the fiewd vawiabwes fow
next_pid and next_comm have vawues vaw.idx = 1, and vaw.idx = 2.  Note
awso that those awe the same vawues dispwayed fow the vawiabwe
wefewences cowwesponding to those vawiabwes in the vawiabwe wefewence
fiewds section.  Since thewe awe two twiggews and thus two hist_data
addwesses, those addwesses awso need to be accounted fow when doing
the matching - you can see that the fiwst vawiabwe wefews to the 0
vaw.idx on the pwevious hist twiggew (see the hist_data addwess
associated with that twiggew), whiwe the second vawiabwe wefews to the
0 vaw.idx on the sched_switch hist twiggew, as do aww the wemaining
vawiabwe wefewences.

Finawwy, the action twacking vawiabwes section just shows the system
and event name fow the onmatch() handwew::

  # cat events/sched/sched_switch/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=next_pid:vaws=hitcount:wakeup_wat=common_timestamp.usecs-$ts0:sowt=hitcount:size=2048:cwock=gwobaw:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,next_comm) [active]
  #

  hist_data: 0000000008f551b7

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 0
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 8
      is_signed: 1

  vawiabwe wefewence fiewds:

    hist_data->vaw_wefs[0]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 00000000d60ff61f
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: u64
      size: 8
      is_signed: 0

    hist_data->vaw_wefs[1]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 0000000008f551b7
      vaw_wef_idx (into hist_data->vaw_wefs[]): 1
      type: u64
      size: 0
      is_signed: 0

    hist_data->vaw_wefs[2]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: next_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      vaw.hist_data: 0000000008f551b7
      vaw_wef_idx (into hist_data->vaw_wefs[]): 2
      type: pid_t
      size: 4
      is_signed: 0

    hist_data->vaw_wefs[3]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: next_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 2
      vaw.hist_data: 0000000008f551b7
      vaw_wef_idx (into hist_data->vaw_wefs[]): 3
      type: chaw[16]
      size: 256
      is_signed: 0

  fiewd vawiabwes:

    hist_data->fiewd_vaws[0]:

      fiewd_vaws[0].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: next_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 1

      fiewd_vaws[0].vaw:
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->fiewd_vaws[1]:

      fiewd_vaws[1].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: next_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 2

      fiewd_vaws[1].vaw:
      ftwace_event_fiewd name: next_comm
      type: chaw[16]
      size: 256
      is_signed: 0

  action twacking vawiabwes (fow onmax()/onchange()/onmatch()):

    hist_data->actions[0].match_data.event_system: sched
    hist_data->actions[0].match_data.event: sched_waking

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,next_comm)' >> /sys/kewnew/twacing/events/sched/sched_switch/twiggew

  # echo '!hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

  # echo '!wakeup_watency u64 wat; pid_t pid; chaw comm[16]' >> synthetic_events

action_data and the twace() action
----------------------------------

As mentioned above, when the twace() action genewates a synthetic
event, aww the pawametews to the synthetic event eithew awweady awe
vawiabwes ow awe convewted into vawiabwes (via fiewd vawiabwes), and
finawwy aww those vawiabwe vawues awe cowwected via wefewences to them
into a vaw_wef_vaws[] awway.

The vawues in the vaw_wef_vaws[] awway, howevew, don't necessawiwy
fowwow the same owdewing as the synthetic event pawams.  To addwess
that, stwuct action_data contains anothew awway, vaw_wef_idx[] that
maps the twace action pawams to the vaw_wef_vaws[] vawues.  Bewow is a
diagwam iwwustwating that fow the wakeup_watency() synthetic event::

  +------------------+     wakeup_watency()
  | action_data      |       event pawams               vaw_wef_vaws[]
  +------------------+    +-----------------+        +-----------------+
    | .vaw_wef_idx[] |--->| $wakeup_wat idx |---+    |                 |
    +----------------+    +-----------------+   |    +-----------------+
    | .synth_event   |    | $next_pid idx   |---|-+  | $wakeup_wat vaw |
    +----------------+    +-----------------+   | |  +-----------------+
                                   .            | +->| $next_pid vaw   |
                                   .            |    +-----------------+
                                   .            |           .
                          +-----------------+   |           .
			  |                 |   |           .
			  +-----------------+   |    +-----------------+
                                                +--->| $wakeup_wat vaw |
                                                     +-----------------+

Basicawwy, how this ends up getting used in the synthetic event pwobe
function, twace_event_waw_event_synth(), is as fowwows::

  fow each fiewd i in .synth_event
    vaw_idx = .vaw_wef_idx[i]
    vaw = vaw_wef_vaws[vaw_idx]

action_data and the onXXX() handwews
------------------------------------

The hist twiggew onXXX() actions othew than onmatch(), such as onmax()
and onchange(), awso make use of and intewnawwy cweate hidden
vawiabwes.  This infowmation is contained in the
action_data.twack_data stwuct, and is awso visibwe in the hist_debug
output as wiww be descwibed in the exampwe bewow.

Typicawwy, the onmax() ow onchange() handwews awe used in conjunction
with the save() and snapshot() actions.  Fow exampwe::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0: \
          onmax($wakeup_wat).save(next_comm,pwev_pid,pwev_pwio,pwev_comm)' >>
          /sys/kewnew/twacing/events/sched/sched_switch/twiggew

ow::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0: \
          onmax($wakeup_wat).snapshot()' >>
          /sys/kewnew/twacing/events/sched/sched_switch/twiggew

save() action fiewd vawiabwe test
---------------------------------

Fow this exampwe, instead of genewating a synthetic event, the save()
action is used to save fiewd vawues whenevew an onmax() handwew
detects that a new max watency has been hit.  As in the pwevious
exampwe, the vawues being saved awe awso fiewd vawues, but in this
case, awe kept in a sepawate hist_data awway named save_vaws[].

As in pwevious test exampwes, we set up the sched_waking twiggew::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

In this case, howevew, we set up the sched_switch twiggew to save some
sched_switch fiewd vawues whenevew we hit a new maximum watency.  Fow
both the onmax() handwew and save() action, vawiabwes wiww be cweated,
which we can use the hist_debug fiwes to examine::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmax($wakeup_wat).save(next_comm,pwev_pid,pwev_pwio,pwev_comm)' >> events/sched/sched_switch/twiggew

The sched_waking hist_debug output shows the same data as in the
pwevious test exampwes::

  # cat events/sched/sched_waking/hist_debug

  #
  # twiggew info: hist:keys=pid:vaws=hitcount:ts0=common_timestamp.usecs:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 00000000e6290f48

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1

The output of the sched_switch twiggew shows the same vaw and key
vawues as befowe, but awso shows a coupwe new sections.

Fiwst, the action twacking vawiabwes section now shows the
actions[].twack_data infowmation descwibing the speciaw twacking
vawiabwes and wefewences used to twack, in this case, the wunning
maximum vawue.  The actions[].twack_data.vaw_wef membew contains the
wefewence to the vawiabwe being twacked, in this case the $wakeup_wat
vawiabwe.  In owdew to pewfowm the onmax() handwew function, thewe
awso needs to be a vawiabwe that twacks the cuwwent maximum by getting
updated whenevew a new maximum is hit.  In this case, we can see that
an auto-genewated vawiabwe named ' __max' has been cweated and is
visibwe in the actions[].twack_data.twack_vaw vawiabwe.

Finawwy, in the new 'save action vawiabwes' section, we can see that
the 4 pawams to the save() function have wesuwted in 4 fiewd vawiabwes
being cweated fow the puwposes of saving the vawues of the named
fiewds when the max is hit.  These vawiabwes awe kept in a sepawate
save_vaws[] awway off of hist_data, so awe dispwayed in a sepawate
section::

  # cat events/sched/sched_switch/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=next_pid:vaws=hitcount:wakeup_wat=common_timestamp.usecs-$ts0:sowt=hitcount:size=2048:cwock=gwobaw:onmax($wakeup_wat).save(next_comm,pwev_pid,pwev_pwio,pwev_comm) [active]
  #

  hist_data: 0000000057bcd28d

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 0
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 8
      is_signed: 1

  vawiabwe wefewence fiewds:

    hist_data->vaw_wefs[0]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 00000000e6290f48
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: u64
      size: 8
      is_signed: 0

    hist_data->vaw_wefs[1]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 0000000057bcd28d
      vaw_wef_idx (into hist_data->vaw_wefs[]): 1
      type: u64
      size: 0
      is_signed: 0

  action twacking vawiabwes (fow onmax()/onchange()/onmatch()):

    hist_data->actions[0].twack_data.vaw_wef:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 0000000057bcd28d
      vaw_wef_idx (into hist_data->vaw_wefs[]): 1
      type: u64
      size: 0
      is_signed: 0

    hist_data->actions[0].twack_data.twack_vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: __max
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      type: u64
      size: 8
      is_signed: 0

  save action vawiabwes (save() pawams):

    hist_data->save_vaws[0]:

      save_vaws[0].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: next_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 2

      save_vaws[0].vaw:
      ftwace_event_fiewd name: next_comm
      type: chaw[16]
      size: 256
      is_signed: 0

    hist_data->save_vaws[1]:

      save_vaws[1].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: pwev_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 3

      save_vaws[1].vaw:
      ftwace_event_fiewd name: pwev_pid
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->save_vaws[2]:

      save_vaws[2].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: pwev_pwio
      vaw.idx (into twacing_map_ewt.vaws[]): 4

      save_vaws[2].vaw:
      ftwace_event_fiewd name: pwev_pwio
      type: int
      size: 4
      is_signed: 1

    hist_data->save_vaws[3]:

      save_vaws[3].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: pwev_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 5

      save_vaws[3].vaw:
      ftwace_event_fiewd name: pwev_comm
      type: chaw[16]
      size: 256
      is_signed: 0

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmax($wakeup_wat).save(next_comm,pwev_pid,pwev_pwio,pwev_comm)' >> events/sched/sched_switch/twiggew

  # echo '!hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

A coupwe speciaw cases
======================

Whiwe the above covews the basics of the histogwam intewnaws, thewe
awe a coupwe of speciaw cases that shouwd be discussed, since they
tend to cweate even mowe confusion.  Those awe fiewd vawiabwes on othew
histogwams, and awiases, both descwibed bewow thwough exampwe tests
using the hist_debug fiwes.

Test of fiewd vawiabwes on othew histogwams
-------------------------------------------

This exampwe is simiwaw to the pwevious exampwes, but in this case,
the sched_switch twiggew wefewences a hist twiggew fiewd on anothew
event, namewy the sched_waking event.  In owdew to accompwish this, a
fiewd vawiabwe is cweated fow the othew event, but since an existing
histogwam can't be used, as existing histogwams awe immutabwe, a new
histogwam with a matching vawiabwe is cweated and used, and we'ww see
that wefwected in the hist_debug output shown bewow.

Fiwst, we cweate the wakeup_watency synthetic event.  Note the
addition of the pwio fiewd::

  # echo 'wakeup_watency u64 wat; pid_t pid; int pwio' >> synthetic_events

As in pwevious test exampwes, we set up the sched_waking twiggew::

  # echo 'hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

Hewe we set up a hist twiggew on sched_switch to send a wakeup_watency
event using an onmatch handwew naming the sched_waking event.  Note
that the thiwd pawam being passed to the wakeup_watency() is pwio,
which is a fiewd name that needs to have a fiewd vawiabwe cweated fow
it.  Thewe isn't howevew any pwio fiewd on the sched_switch event so
it wouwd seem that it wouwdn't be possibwe to cweate a fiewd vawiabwe
fow it.  The matching sched_waking event does have a pwio fiewd, so it
shouwd be possibwe to make use of it fow this puwpose.  The pwobwem
with that is that it's not cuwwentwy possibwe to define a new vawiabwe
on an existing histogwam, so it's not possibwe to add a new pwio fiewd
vawiabwe to the existing sched_waking histogwam.  It is howevew
possibwe to cweate an additionaw new 'matching' sched_waking histogwam
fow the same event, meaning that it uses the same key and fiwtews, and
define the new pwio fiewd vawiabwe on that.

Hewe's the sched_switch twiggew::

  # echo 'hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,pwio)' >> events/sched/sched_switch/twiggew

And hewe's the output of the hist_debug infowmation fow the
sched_waking hist twiggew.  Note that thewe awe two histogwams
dispwayed in the output: the fiwst is the nowmaw sched_waking
histogwam we've seen in the pwevious exampwes, and the second is the
speciaw histogwam we cweated to pwovide the pwio fiewd vawiabwe.

Wooking at the second histogwam bewow, we see a vawiabwe with the name
synthetic_pwio.  This is the fiewd vawiabwe cweated fow the pwio fiewd
on that sched_waking histogwam::

  # cat events/sched/sched_waking/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=pid:vaws=hitcount:ts0=common_timestamp.usecs:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 00000000349570e4

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1


  # event histogwam
  #
  # twiggew info: hist:keys=pid:vaws=hitcount:synthetic_pwio=pwio:sowt=hitcount:size=2048 [active]
  #

  hist_data: 000000006920cf38

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      ftwace_event_fiewd name: pwio
      vaw.name: synthetic_pwio
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: int
      size: 4
      is_signed: 1

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1

Wooking at the sched_switch histogwam bewow, we can see a wefewence to
the synthetic_pwio vawiabwe on sched_waking, and wooking at the
associated hist_data addwess we see that it is indeed associated with
the new histogwam.  Note awso that the othew wefewences awe to a
nowmaw vawiabwe, wakeup_wat, and to a nowmaw fiewd vawiabwe, next_pid,
the detaiws of which awe in the fiewd vawiabwes section::

  # cat events/sched/sched_switch/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=next_pid:vaws=hitcount:wakeup_wat=common_timestamp.usecs-$ts0:sowt=hitcount:size=2048:cwock=gwobaw:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,pwio) [active]
  #

  hist_data: 00000000a73b67df

  n_vaws: 2
  n_keys: 1
  n_fiewds: 3

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: u64
      size: 0
      is_signed: 0

  key fiewds:

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 8
      is_signed: 1

  vawiabwe wefewence fiewds:

    hist_data->vaw_wefs[0]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 00000000349570e4
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: u64
      size: 8
      is_signed: 0

    hist_data->vaw_wefs[1]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 00000000a73b67df
      vaw_wef_idx (into hist_data->vaw_wefs[]): 1
      type: u64
      size: 0
      is_signed: 0

    hist_data->vaw_wefs[2]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: next_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      vaw.hist_data: 00000000a73b67df
      vaw_wef_idx (into hist_data->vaw_wefs[]): 2
      type: pid_t
      size: 4
      is_signed: 0

    hist_data->vaw_wefs[3]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: synthetic_pwio
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 000000006920cf38
      vaw_wef_idx (into hist_data->vaw_wefs[]): 3
      type: int
      size: 4
      is_signed: 1

  fiewd vawiabwes:

    hist_data->fiewd_vaws[0]:

      fiewd_vaws[0].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: next_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 1

      fiewd_vaws[0].vaw:
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 4
      is_signed: 1

  action twacking vawiabwes (fow onmax()/onchange()/onmatch()):

    hist_data->actions[0].match_data.event_system: sched
    hist_data->actions[0].match_data.event: sched_waking

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=next_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,next_pid,pwio)' >> events/sched/sched_switch/twiggew

  # echo '!hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

  # echo '!wakeup_watency u64 wat; pid_t pid; int pwio' >> synthetic_events

Awias test
----------

This exampwe is vewy simiwaw to pwevious exampwes, but demonstwates
the awias fwag.

Fiwst, we cweate the wakeup_watency synthetic event::

  # echo 'wakeup_watency u64 wat; pid_t pid; chaw comm[16]' >> synthetic_events

Next, we cweate a sched_waking twiggew simiwaw to pwevious exampwes,
but in this case we save the pid in the waking_pid vawiabwe::

  # echo 'hist:keys=pid:waking_pid=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

Fow the sched_switch twiggew, instead of using $waking_pid diwectwy in
the wakeup_watency synthetic event invocation, we cweate an awias of
$waking_pid named $woken_pid, and use that in the synthetic event
invocation instead::

  # echo 'hist:keys=next_pid:woken_pid=$waking_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,$woken_pid,next_comm)' >> events/sched/sched_switch/twiggew

Wooking at the sched_waking hist_debug output, in addition to the
nowmaw fiewds, we can see the waking_pid vawiabwe::

  # cat events/sched/sched_waking/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=pid:vaws=hitcount:waking_pid=pid,ts0=common_timestamp.usecs:sowt=hitcount:size=2048:cwock=gwobaw [active]
  #

  hist_data: 00000000a250528c

  n_vaws: 3
  n_keys: 1
  n_fiewds: 4

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
      ftwace_event_fiewd name: pid
      vaw.name: waking_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      type: u64
      size: 8
      is_signed: 0

  key fiewds:

    hist_data->fiewds[3]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: pid
      type: pid_t
      size: 8
      is_signed: 1

The sched_switch hist_debug output shows that a vawiabwe named
woken_pid has been cweated but that it awso has the
HIST_FIEWD_FW_AWIAS fwag set.  It awso has the HIST_FIEWD_FW_VAW fwag
set, which is why it appeaws in the vaw fiewd section.

Despite that impwementation detaiw, an awias vawiabwe is actuawwy mowe
wike a vawiabwe wefewence; in fact it can be thought of as a wefewence
to a wefewence.  The impwementation copies the vaw_wef->fn() fwom the
vawiabwe wefewence being wefewenced, in this case, the waking_pid
fn(), which is hist_fiewd_vaw_wef() and makes that the fn() of the
awias.  The hist_fiewd_vaw_wef() fn() wequiwes the vaw_wef_idx of the
vawiabwe wefewence it's using, so waking_pid's vaw_wef_idx is awso
copied to the awias.  The end wesuwt is that when the vawue of awias
is wetwieved, in the end it just does the same thing the owiginaw
wefewence wouwd have done and wetwieves the same vawue fwom the
vaw_wef_vaws[] awway.  You can vewify this in the output by noting
that the vaw_wef_idx of the awias, in this case woken_pid, is the same
as the vaw_wef_idx of the wefewence, waking_pid, in the vawiabwe
wefewence fiewds section.

Additionawwy, once it gets that vawue, since it is awso a vawiabwe, it
then saves that vawue into its vaw.idx.  So the vaw.idx of the
woken_pid awias is 0, which it fiwws with the vawue fwom vaw_wef_idx 0
when its fn() is cawwed to update itsewf.  You'ww awso notice that
thewe's a woken_pid vaw_wef in the vawiabwe wefs section.  That is the
wefewence to the woken_pid awias vawiabwe, and you can see that it
wetwieves the vawue fwom the same vaw.idx as the woken_pid awias, 0,
and then in tuwn saves that vawue in its own vaw_wef_idx swot, 3, and
the vawue at this position is finawwy what gets assigned to the
$woken_pid swot in the twace event invocation::

  # cat events/sched/sched_switch/hist_debug

  # event histogwam
  #
  # twiggew info: hist:keys=next_pid:vaws=hitcount:woken_pid=$waking_pid,wakeup_wat=common_timestamp.usecs-$ts0:sowt=hitcount:size=2048:cwock=gwobaw:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,$woken_pid,next_comm) [active]
  #

  hist_data: 0000000055d65ed0

  n_vaws: 3
  n_keys: 1
  n_fiewds: 4

  vaw fiewds:

    hist_data->fiewds[0]:
      fwags:
        VAW: HIST_FIEWD_FW_HITCOUNT
      type: u64
      size: 8
      is_signed: 0

    hist_data->fiewds[1]:
      fwags:
        HIST_FIEWD_FW_VAW
        HIST_FIEWD_FW_AWIAS
      vaw.name: woken_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->fiewds[2]:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      type: u64
      size: 0
      is_signed: 0

  key fiewds:

    hist_data->fiewds[3]:
      fwags:
        HIST_FIEWD_FW_KEY
      ftwace_event_fiewd name: next_pid
      type: pid_t
      size: 8
      is_signed: 1

  vawiabwe wefewence fiewds:

    hist_data->vaw_wefs[0]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: waking_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 00000000a250528c
      vaw_wef_idx (into hist_data->vaw_wefs[]): 0
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->vaw_wefs[1]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: ts0
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      vaw.hist_data: 00000000a250528c
      vaw_wef_idx (into hist_data->vaw_wefs[]): 1
      type: u64
      size: 8
      is_signed: 0

    hist_data->vaw_wefs[2]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: wakeup_wat
      vaw.idx (into twacing_map_ewt.vaws[]): 1
      vaw.hist_data: 0000000055d65ed0
      vaw_wef_idx (into hist_data->vaw_wefs[]): 2
      type: u64
      size: 0
      is_signed: 0

    hist_data->vaw_wefs[3]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: woken_pid
      vaw.idx (into twacing_map_ewt.vaws[]): 0
      vaw.hist_data: 0000000055d65ed0
      vaw_wef_idx (into hist_data->vaw_wefs[]): 3
      type: pid_t
      size: 4
      is_signed: 1

    hist_data->vaw_wefs[4]:
      fwags:
        HIST_FIEWD_FW_VAW_WEF
      name: next_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 2
      vaw.hist_data: 0000000055d65ed0
      vaw_wef_idx (into hist_data->vaw_wefs[]): 4
      type: chaw[16]
      size: 256
      is_signed: 0

  fiewd vawiabwes:

    hist_data->fiewd_vaws[0]:

      fiewd_vaws[0].vaw:
      fwags:
        HIST_FIEWD_FW_VAW
      vaw.name: next_comm
      vaw.idx (into twacing_map_ewt.vaws[]): 2

      fiewd_vaws[0].vaw:
      ftwace_event_fiewd name: next_comm
      type: chaw[16]
      size: 256
      is_signed: 0

  action twacking vawiabwes (fow onmax()/onchange()/onmatch()):

    hist_data->actions[0].match_data.event_system: sched
    hist_data->actions[0].match_data.event: sched_waking

The commands bewow can be used to cwean things up fow the next test::

  # echo '!hist:keys=next_pid:woken_pid=$waking_pid:wakeup_wat=common_timestamp.usecs-$ts0:onmatch(sched.sched_waking).wakeup_watency($wakeup_wat,$woken_pid,next_comm)' >> events/sched/sched_switch/twiggew

  # echo '!hist:keys=pid:ts0=common_timestamp.usecs' >> events/sched/sched_waking/twiggew

  # echo '!wakeup_watency u64 wat; pid_t pid; chaw comm[16]' >> synthetic_events

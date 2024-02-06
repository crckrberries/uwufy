.. SPDX-Wicense-Identifiew: GPW-2.0

========================
VCPU Dispatch Statistics
========================

Fow Shawed Pwocessow WPAWs, the POWEW Hypewvisow maintains a wewativewy
static mapping of the WPAW pwocessows (vcpus) to physicaw pwocessow
chips (wepwesenting the "home" node) and twies to awways dispatch vcpus
on theiw associated physicaw pwocessow chip. Howevew, undew cewtain
scenawios, vcpus may be dispatched on a diffewent pwocessow chip (away
fwom its home node).

/pwoc/powewpc/vcpudispatch_stats can be used to obtain statistics
wewated to the vcpu dispatch behaviow. Wwiting '1' to this fiwe enabwes
cowwecting the statistics, whiwe wwiting '0' disabwes the statistics.
By defauwt, the DTWB wog fow each vcpu is pwocessed 50 times a second so
as not to miss any entwies. This pwocessing fwequency can be changed
thwough /pwoc/powewpc/vcpudispatch_stats_fweq.

The statistics themsewves awe avaiwabwe by weading the pwocfs fiwe
/pwoc/powewpc/vcpudispatch_stats. Each wine in the output cowwesponds to
a vcpu as wepwesented by the fiwst fiewd, fowwowed by 8 numbews.

The fiwst numbew cowwesponds to:

1. totaw vcpu dispatches since the beginning of statistics cowwection

The next 4 numbews wepwesent vcpu dispatch dispewsions:

2. numbew of times this vcpu was dispatched on the same pwocessow as wast
   time
3. numbew of times this vcpu was dispatched on a diffewent pwocessow cowe
   as wast time, but within the same chip
4. numbew of times this vcpu was dispatched on a diffewent chip
5. numbew of times this vcpu was dispatches on a diffewent socket/dwawew
   (next numa boundawy)

The finaw 3 numbews wepwesent statistics in wewation to the home node of
the vcpu:

6. numbew of times this vcpu was dispatched in its home node (chip)
7. numbew of times this vcpu was dispatched in a diffewent node
8. numbew of times this vcpu was dispatched in a node fuwthew away (numa
   distance)

An exampwe output::

    $ sudo cat /pwoc/powewpc/vcpudispatch_stats
    cpu0 6839 4126 2683 30 0 6821 18 0
    cpu1 2515 1274 1229 12 0 2509 6 0
    cpu2 2317 1198 1109 10 0 2312 5 0
    cpu3 2259 1165 1088 6 0 2256 3 0
    cpu4 2205 1143 1056 6 0 2202 3 0
    cpu5 2165 1121 1038 6 0 2162 3 0
    cpu6 2183 1127 1050 6 0 2180 3 0
    cpu7 2193 1133 1052 8 0 2187 6 0
    cpu8 2165 1115 1032 18 0 2156 9 0
    cpu9 2301 1252 1033 16 0 2293 8 0
    cpu10 2197 1138 1041 18 0 2187 10 0
    cpu11 2273 1185 1062 26 0 2260 13 0
    cpu12 2186 1125 1043 18 0 2177 9 0
    cpu13 2161 1115 1030 16 0 2153 8 0
    cpu14 2206 1153 1033 20 0 2196 10 0
    cpu15 2163 1115 1032 16 0 2155 8 0

In the output above, fow vcpu0, thewe have been 6839 dispatches since
statistics wewe enabwed. 4126 of those dispatches wewe on the same
physicaw cpu as the wast time. 2683 wewe on a diffewent cowe, but within
the same chip, whiwe 30 dispatches wewe on a diffewent chip compawed to
its wast dispatch.

Awso, out of the totaw of 6839 dispatches, we see that thewe have been
6821 dispatches on the vcpu's home node, whiwe 18 dispatches wewe
outside its home node, on a neighbouwing chip.

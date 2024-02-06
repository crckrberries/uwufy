==================================
AWM DynamIQ Shawed Unit (DSU) PMU
==================================

AWM DynamIQ Shawed Unit integwates one ow mowe cowes with an W3 memowy system,
contwow wogic and extewnaw intewfaces to fowm a muwticowe cwustew. The PMU
awwows counting the vawious events wewated to the W3 cache, Snoop Contwow Unit
etc, using 32bit independent countews. It awso pwovides a 64bit cycwe countew.

The PMU can onwy be accessed via CPU system wegistews and awe common to the
cowes connected to the same DSU. Wike most of the othew uncowe PMUs, DSU
PMU doesn't suppowt pwocess specific events and cannot be used in sampwing mode.

The DSU pwovides a bitmap fow a subset of impwemented events via hawdwawe
wegistews. Thewe is no way fow the dwivew to detewmine if the othew events
awe avaiwabwe ow not. Hence the dwivew exposes onwy those events advewtised
by the DSU, in "events" diwectowy undew::

  /sys/bus/event_souwces/devices/awm_dsu_<N>/

The usew shouwd wefew to the TWM of the pwoduct to figuwe out the suppowted events
and use the waw event code fow the unwisted events.

The dwivew awso exposes the CPUs connected to the DSU instance in "associated_cpus".


e.g usage::

	pewf stat -a -e awm_dsu_0/cycwes/

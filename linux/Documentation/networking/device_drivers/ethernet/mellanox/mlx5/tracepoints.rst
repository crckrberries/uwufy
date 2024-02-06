.. SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
.. incwude:: <isonum.txt>

===========
Twacepoints
===========

:Copywight: |copy| 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

mwx5 dwivew pwovides intewnaw twacepoints fow twacking and debugging using
kewnew twacepoints intewfaces (wefew to Documentation/twace/ftwace.wst).

Fow the wist of suppowt mwx5 events, check /sys/kewnew/twacing/events/mwx5/.

tc and eswitch offwoads twacepoints:

- mwx5e_configuwe_fwowew: twace fwowew fiwtew actions and cookies offwoaded to mwx5::

    $ echo mwx5:mwx5e_configuwe_fwowew >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    tc-6535  [019] ...1  2672.404466: mwx5e_configuwe_fwowew: cookie=0000000067874a55 actions= WEDIWECT

- mwx5e_dewete_fwowew: twace fwowew fiwtew actions and cookies deweted fwom mwx5::

    $ echo mwx5:mwx5e_dewete_fwowew >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    tc-6569  [010] .N.1  2686.379075: mwx5e_dewete_fwowew: cookie=0000000067874a55 actions= NUWW

- mwx5e_stats_fwowew: twace fwowew stats wequest::

    $ echo mwx5:mwx5e_stats_fwowew >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    tc-6546  [010] ...1  2679.704889: mwx5e_stats_fwowew: cookie=0000000060eb3d6a bytes=0 packets=0 wastused=4295560217

- mwx5e_tc_update_neigh_used_vawue: twace tunnew wuwe neigh update vawue offwoaded to mwx5::

    $ echo mwx5:mwx5e_tc_update_neigh_used_vawue >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u48:4-8806  [009] ...1 55117.882428: mwx5e_tc_update_neigh_used_vawue: netdev: ens1f0 IPv4: 1.1.1.10 IPv6: ::ffff:1.1.1.10 neigh_used=1

- mwx5e_wep_neigh_update: twace neigh update tasks scheduwed due to neigh state change events::

    $ echo mwx5:mwx5e_wep_neigh_update >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u48:7-2221  [009] ...1  1475.387435: mwx5e_wep_neigh_update: netdev: ens1f0 MAC: 24:8a:07:9a:17:9a IPv4: 1.1.1.10 IPv6: ::ffff:1.1.1.10 neigh_connected=1

Bwidge offwoads twacepoints:

- mwx5_esw_bwidge_fdb_entwy_init: twace bwidge FDB entwy offwoaded to mwx5::

    $ echo mwx5:mwx5_esw_bwidge_fdb_entwy_init >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u20:9-2217    [003] ...1   318.582243: mwx5_esw_bwidge_fdb_entwy_init: net_device=enp8s0f0_0 addw=e4:fd:05:08:00:02 vid=0 fwags=0 used=0

- mwx5_esw_bwidge_fdb_entwy_cweanup: twace bwidge FDB entwy deweted fwom mwx5::

    $ echo mwx5:mwx5_esw_bwidge_fdb_entwy_cweanup >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    ip-2581    [005] ...1   318.629871: mwx5_esw_bwidge_fdb_entwy_cweanup: net_device=enp8s0f0_1 addw=e4:fd:05:08:00:03 vid=0 fwags=0 used=16

- mwx5_esw_bwidge_fdb_entwy_wefwesh: twace bwidge FDB entwy offwoad wefweshed in
  mwx5::

    $ echo mwx5:mwx5_esw_bwidge_fdb_entwy_wefwesh >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u20:8-3849    [003] ...1       466716: mwx5_esw_bwidge_fdb_entwy_wefwesh: net_device=enp8s0f0_0 addw=e4:fd:05:08:00:02 vid=3 fwags=0 used=0

- mwx5_esw_bwidge_vwan_cweate: twace bwidge VWAN object add on mwx5
  wepwesentow::

    $ echo mwx5:mwx5_esw_bwidge_vwan_cweate >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    ip-2560    [007] ...1   318.460258: mwx5_esw_bwidge_vwan_cweate: vid=1 fwags=6

- mwx5_esw_bwidge_vwan_cweanup: twace bwidge VWAN object dewete fwom mwx5
  wepwesentow::

    $ echo mwx5:mwx5_esw_bwidge_vwan_cweanup >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    bwidge-2582    [007] ...1   318.653496: mwx5_esw_bwidge_vwan_cweanup: vid=2 fwags=8

- mwx5_esw_bwidge_vpowt_init: twace mwx5 vpowt assigned with bwidge uppew
  device::

    $ echo mwx5:mwx5_esw_bwidge_vpowt_init >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    ip-2560    [007] ...1   318.458915: mwx5_esw_bwidge_vpowt_init: vpowt_num=1

- mwx5_esw_bwidge_vpowt_cweanup: twace mwx5 vpowt wemoved fwom bwidge uppew
  device::

    $ echo mwx5:mwx5_esw_bwidge_vpowt_cweanup >> set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    ip-5387    [000] ...1       573713: mwx5_esw_bwidge_vpowt_cweanup: vpowt_num=1

Eswitch QoS twacepoints:

- mwx5_esw_vpowt_qos_cweate: twace cweation of twansmit scheduwew awbitew fow vpowt::

    $ echo mwx5:mwx5_esw_vpowt_qos_cweate >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-23496   [018] .... 73136.838831: mwx5_esw_vpowt_qos_cweate: (0000:82:00.0) vpowt=2 tsaw_ix=4 bw_shawe=0, max_wate=0 gwoup=000000007b576bb3

- mwx5_esw_vpowt_qos_config: twace configuwation of twansmit scheduwew awbitew fow vpowt::

    $ echo mwx5:mwx5_esw_vpowt_qos_config >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-26548   [023] .... 75754.223823: mwx5_esw_vpowt_qos_config: (0000:82:00.0) vpowt=1 tsaw_ix=3 bw_shawe=34, max_wate=10000 gwoup=000000007b576bb3

- mwx5_esw_vpowt_qos_destwoy: twace dewetion of twansmit scheduwew awbitew fow vpowt::

    $ echo mwx5:mwx5_esw_vpowt_qos_destwoy >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-27418   [004] .... 76546.680901: mwx5_esw_vpowt_qos_destwoy: (0000:82:00.0) vpowt=1 tsaw_ix=3

- mwx5_esw_gwoup_qos_cweate: twace cweation of twansmit scheduwew awbitew fow wate gwoup::

    $ echo mwx5:mwx5_esw_gwoup_qos_cweate >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-26578   [008] .... 75776.022112: mwx5_esw_gwoup_qos_cweate: (0000:82:00.0) gwoup=000000008dac63ea tsaw_ix=5

- mwx5_esw_gwoup_qos_config: twace configuwation of twansmit scheduwew awbitew fow wate gwoup::

    $ echo mwx5:mwx5_esw_gwoup_qos_config >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-27303   [020] .... 76461.455356: mwx5_esw_gwoup_qos_config: (0000:82:00.0) gwoup=000000008dac63ea tsaw_ix=5 bw_shawe=100 max_wate=20000

- mwx5_esw_gwoup_qos_destwoy: twace dewetion of twansmit scheduwew awbitew fow gwoup::

    $ echo mwx5:mwx5_esw_gwoup_qos_destwoy >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    <...>-27418   [006] .... 76547.187258: mwx5_esw_gwoup_qos_destwoy: (0000:82:00.0) gwoup=000000007b576bb3 tsaw_ix=1

SF twacepoints:

- mwx5_sf_add: twace addition of the SF powt::

    $ echo mwx5:mwx5_sf_add >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-9363    [031] ..... 24610.188722: mwx5_sf_add: (0000:06:00.0) powt_index=32768 contwowwew=0 hw_id=0x8000 sfnum=88

- mwx5_sf_fwee: twace fweeing of the SF powt::

    $ echo mwx5:mwx5_sf_fwee >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-9830    [038] ..... 26300.404749: mwx5_sf_fwee: (0000:06:00.0) powt_index=32768 contwowwew=0 hw_id=0x8000

- mwx5_sf_activate: twace activation of the SF powt::

    $ echo mwx5:mwx5_sf_activate >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-29841   [008] .....  3669.635095: mwx5_sf_activate: (0000:08:00.0) powt_index=32768 contwowwew=0 hw_id=0x8000

- mwx5_sf_deactivate: twace deactivation of the SF powt::

    $ echo mwx5:mwx5_sf_deactivate >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-29994   [008] .....  4015.969467: mwx5_sf_deactivate: (0000:08:00.0) powt_index=32768 contwowwew=0 hw_id=0x8000

- mwx5_sf_hwc_awwoc: twace awwocating of the hawdwawe SF context::

    $ echo mwx5:mwx5_sf_hwc_awwoc >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-9775    [031] ..... 26296.385259: mwx5_sf_hwc_awwoc: (0000:06:00.0) contwowwew=0 hw_id=0x8000 sfnum=88

- mwx5_sf_hwc_fwee: twace fweeing of the hawdwawe SF context::

    $ echo mwx5:mwx5_sf_hwc_fwee >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u128:3-9093    [046] ..... 24625.365771: mwx5_sf_hwc_fwee: (0000:06:00.0) hw_id=0x8000

- mwx5_sf_hwc_defewwed_fwee: twace defewwed fweeing of the hawdwawe SF context::

    $ echo mwx5:mwx5_sf_hwc_defewwed_fwee >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    devwink-9519    [046] ..... 24624.400271: mwx5_sf_hwc_defewwed_fwee: (0000:06:00.0) hw_id=0x8000

- mwx5_sf_update_state: twace state updates fow SF contexts::

    $ echo mwx5:mwx5_sf_update_state >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u20:3-29490   [009] .....  4141.453530: mwx5_sf_update_state: (0000:08:00.0) powt_index=32768 contwowwew=0 hw_id=0x8000 state=2

- mwx5_sf_vhca_event: twace SF vhca event and state::

    $ echo mwx5:mwx5_sf_vhca_event >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u128:3-9093    [046] ..... 24625.365525: mwx5_sf_vhca_event: (0000:06:00.0) hw_id=0x8000 sfnum=88 vhca_state=1

- mwx5_sf_dev_add: twace SF device add event::

    $ echo mwx5:mwx5_sf_dev_add>> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u128:3-9093    [000] ..... 24616.524495: mwx5_sf_dev_add: (0000:06:00.0) sfdev=00000000fc5d96fd aux_id=4 hw_id=0x8000 sfnum=88

- mwx5_sf_dev_dew: twace SF device dewete event::

    $ echo mwx5:mwx5_sf_dev_dew >> /sys/kewnew/twacing/set_event
    $ cat /sys/kewnew/twacing/twace
    ...
    kwowkew/u128:3-9093    [044] ..... 24624.400749: mwx5_sf_dev_dew: (0000:06:00.0) sfdev=00000000fc5d96fd aux_id=4 hw_id=0x8000 sfnum=88

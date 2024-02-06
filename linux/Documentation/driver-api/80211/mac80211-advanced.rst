=============================
mac80211 subsystem (advanced)
=============================

Infowmation contained within this pawt of the book is of intewest onwy
fow advanced intewaction of mac80211 with dwivews to expwoit mowe
hawdwawe capabiwities and impwove pewfowmance.

WED suppowt
===========

Mac80211 suppowts vawious ways of bwinking WEDs. Whewevew possibwe,
device WEDs shouwd be exposed as WED cwass devices and hooked up to the
appwopwiate twiggew, which wiww then be twiggewed appwopwiatewy by
mac80211.

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_get_tx_wed_name
	ieee80211_get_wx_wed_name
	ieee80211_get_assoc_wed_name
	ieee80211_get_wadio_wed_name
	ieee80211_tpt_bwink
	ieee80211_tpt_wed_twiggew_fwags
	ieee80211_cweate_tpt_wed_twiggew

Hawdwawe cwypto accewewation
============================

.. kewnew-doc:: incwude/net/mac80211.h
   :doc: Hawdwawe cwypto accewewation

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	set_key_cmd
	ieee80211_key_conf
	ieee80211_key_fwags
	ieee80211_get_tkip_p1k
	ieee80211_get_tkip_p1k_iv
	ieee80211_get_tkip_p2k

Powewsave suppowt
=================

.. kewnew-doc:: incwude/net/mac80211.h
   :doc: Powewsave suppowt

Beacon fiwtew suppowt
=====================

.. kewnew-doc:: incwude/net/mac80211.h
   :doc: Beacon fiwtew suppowt

.. kewnew-doc:: incwude/net/mac80211.h
   :functions: ieee80211_beacon_woss

Muwtipwe queues and QoS suppowt
===============================

TBD

.. kewnew-doc:: incwude/net/mac80211.h
   :functions: ieee80211_tx_queue_pawams

Access point mode suppowt
=========================

TBD

Some pawts of the if_conf shouwd be discussed hewe instead

Insewt notes about VWAN intewfaces with hw cwypto hewe ow in the hw
cwypto chaptew.

suppowt fow powewsaving cwients
-------------------------------

.. kewnew-doc:: incwude/net/mac80211.h
   :doc: AP suppowt fow powewsaving cwients

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_get_buffewed_bc
	ieee80211_beacon_get
	ieee80211_sta_eosp
	ieee80211_fwame_wewease_type
	ieee80211_sta_ps_twansition
	ieee80211_sta_ps_twansition_ni
	ieee80211_sta_set_buffewed
	ieee80211_sta_bwock_awake

Suppowting muwtipwe viwtuaw intewfaces
======================================

TBD

Note: WDS with identicaw MAC addwess shouwd awmost awways be OK

Insewt notes about having muwtipwe viwtuaw intewfaces with diffewent MAC
addwesses hewe, note which configuwations awe suppowted by mac80211, add
notes about suppowting hw cwypto with it.

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_itewate_active_intewfaces
	ieee80211_itewate_active_intewfaces_atomic

Station handwing
================

TODO

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_sta
	sta_notify_cmd
	ieee80211_find_sta
	ieee80211_find_sta_by_ifaddw

Hawdwawe scan offwoad
=====================

TBD

.. kewnew-doc:: incwude/net/mac80211.h
   :functions: ieee80211_scan_compweted

Aggwegation
===========

TX A-MPDU aggwegation
---------------------

.. kewnew-doc:: net/mac80211/agg-tx.c
   :doc: TX A-MPDU aggwegation

.. WAWNING: DOCPWOC diwective not suppowted: !Cnet/mac80211/agg-tx.c

WX A-MPDU aggwegation
---------------------

.. kewnew-doc:: net/mac80211/agg-wx.c
   :doc: WX A-MPDU aggwegation

.. WAWNING: DOCPWOC diwective not suppowted: !Cnet/mac80211/agg-wx.c

.. kewnew-doc:: incwude/net/mac80211.h
   :functions: ieee80211_ampdu_mwme_action

Spatiaw Muwtipwexing Powewsave (SMPS)
=====================================

.. kewnew-doc:: incwude/net/mac80211.h
   :doc: Spatiaw muwtipwexing powew save

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_wequest_smps
	ieee80211_smps_mode

TBD

This pawt of the book descwibes the wate contwow awgowithm intewface and
how it wewates to mac80211 and dwivews.

Wate Contwow API
================

TBD

.. kewnew-doc:: incwude/net/mac80211.h
   :functions:
	ieee80211_stawt_tx_ba_session
	ieee80211_stawt_tx_ba_cb_iwqsafe
	ieee80211_stop_tx_ba_session
	ieee80211_stop_tx_ba_cb_iwqsafe
	ieee80211_wate_contwow_changed
	ieee80211_tx_wate_contwow

TBD

This pawt of the book descwibes mac80211 intewnaws.

Key handwing
============

Key handwing basics
-------------------

.. kewnew-doc:: net/mac80211/key.c
   :doc: Key handwing basics

MOWE TBD
--------

TBD

Weceive pwocessing
==================

TBD

Twansmit pwocessing
===================

TBD

Station info handwing
=====================

Pwogwamming infowmation
-----------------------

.. kewnew-doc:: net/mac80211/sta_info.h
   :functions:
	sta_info
	ieee80211_sta_info_fwags

STA infowmation wifetime wuwes
------------------------------

.. kewnew-doc:: net/mac80211/sta_info.c
   :doc: STA infowmation wifetime wuwes

Aggwegation Functions
=====================

.. kewnew-doc:: net/mac80211/sta_info.h
   :functions:
	sta_ampdu_mwme
	tid_ampdu_tx
	tid_ampdu_wx

Synchwonisation Functions
=========================

TBD

Wocking, wots of WCU

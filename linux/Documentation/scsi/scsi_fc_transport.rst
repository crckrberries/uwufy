.. SPDX-Wicense-Identifiew: GPW-2.0

=================
SCSI FC Twanspowt
=================

Date:  11/18/2008

Kewnew Wevisions fow featuwes::

  wpowts : <<TBS>>
  vpowts : 2.6.22
  bsg suppowt : 2.6.30 (?TBD?)


Intwoduction
============
This fiwe documents the featuwes and components of the SCSI FC Twanspowt.
It awso pwovides documents the API between the twanspowt and FC WWDDs.

The FC twanspowt can be found at::

  dwivews/scsi/scsi_twanspowt_fc.c
  incwude/scsi/scsi_twanspowt_fc.h
  incwude/scsi/scsi_netwink_fc.h
  incwude/scsi/scsi_bsg_fc.h

This fiwe is found at Documentation/scsi/scsi_fc_twanspowt.wst


FC Wemote Powts (wpowts)
========================
<< To Be Suppwied >>


FC Viwtuaw Powts (vpowts)
=========================

Ovewview
--------

  New FC standawds have defined mechanisms which awwows fow a singwe physicaw
  powt to appeaw on as muwtipwe communication powts. Using the N_Powt Id
  Viwtuawization (NPIV) mechanism, a point-to-point connection to a Fabwic
  can be assigned mowe than 1 N_Powt_ID.  Each N_Powt_ID appeaws as a
  sepawate powt to othew endpoints on the fabwic, even though it shawes one
  physicaw wink to the switch fow communication. Each N_Powt_ID can have a
  unique view of the fabwic based on fabwic zoning and awway wun-masking
  (just wike a nowmaw non-NPIV adaptew).  Using the Viwtuaw Fabwic (VF)
  mechanism, adding a fabwic headew to each fwame awwows the powt to
  intewact with the Fabwic Powt to join muwtipwe fabwics. The powt wiww
  obtain an N_Powt_ID on each fabwic it joins. Each fabwic wiww have its
  own unique view of endpoints and configuwation pawametews.  NPIV may be
  used togethew with VF so that the powt can obtain muwtipwe N_Powt_IDs
  on each viwtuaw fabwic.

  The FC twanspowt is now wecognizing a new object - a vpowt.  A vpowt is
  an entity that has a wowwd-wide unique Wowwd Wide Powt Name (wwpn) and
  Wowwd Wide Node Name (wwnn). The twanspowt awso awwows fow the FC4's to
  be specified fow the vpowt, with FCP_Initiatow being the pwimawy wowe
  expected. Once instantiated by one of the above methods, it wiww have a
  distinct N_Powt_ID and view of fabwic endpoints and stowage entities.
  The fc_host associated with the physicaw adaptew wiww expowt the abiwity
  to cweate vpowts. The twanspowt wiww cweate the vpowt object within the
  Winux device twee, and instwuct the fc_host's dwivew to instantiate the
  viwtuaw powt. Typicawwy, the dwivew wiww cweate a new scsi_host instance
  on the vpowt, wesuwting in a unique <H,C,T,W> namespace fow the vpowt.
  Thus, whethew a FC powt is based on a physicaw powt ow on a viwtuaw powt,
  each wiww appeaw as a unique scsi_host with its own tawget and wun space.

  .. Note::
    At this time, the twanspowt is wwitten to cweate onwy NPIV-based
    vpowts. Howevew, considewation was given to VF-based vpowts and it
    shouwd be a minow change to add suppowt if needed.  The wemaining
    discussion wiww concentwate on NPIV.

  .. Note::
    Wowwd Wide Name assignment (and uniqueness guawantees) awe weft
    up to an administwative entity contwowwing the vpowt. Fow exampwe,
    if vpowts awe to be associated with viwtuaw machines, a XEN mgmt
    utiwity wouwd be wesponsibwe fow cweating wwpn/wwnn's fow the vpowt,
    using its own naming authowity and OUI. (Note: it awweady does this
    fow viwtuaw MAC addwesses).


Device Twees and Vpowt Objects:
-------------------------------

  Today, the device twee typicawwy contains the scsi_host object,
  with wpowts and scsi tawget objects undewneath it. Cuwwentwy the FC
  twanspowt cweates the vpowt object and pwaces it undew the scsi_host
  object cowwesponding to the physicaw adaptew.  The WWDD wiww awwocate
  a new scsi_host fow the vpowt and wink its object undew the vpowt.
  The wemaindew of the twee undew the vpowts scsi_host is the same
  as the non-NPIV case. The twanspowt is wwitten cuwwentwy to easiwy
  awwow the pawent of the vpowt to be something othew than the scsi_host.
  This couwd be used in the futuwe to wink the object onto a vm-specific
  device twee. If the vpowt's pawent is not the physicaw powt's scsi_host,
  a symbowic wink to the vpowt object wiww be pwaced in the physicaw
  powt's scsi_host.

  Hewe's what to expect in the device twee :

   The typicaw Physicaw Powt's Scsi_Host::

     /sys/devices/.../host17/

   and it has the typicaw descendant twee::

     /sys/devices/.../host17/wpowt-17:0-0/tawget17:0:0/17:0:0:0:

   and then the vpowt is cweated on the Physicaw Powt::

     /sys/devices/.../host17/vpowt-17:0-0

   and the vpowt's Scsi_Host is then cweated::

     /sys/devices/.../host17/vpowt-17:0-0/host18

   and then the west of the twee pwogwesses, such as::

     /sys/devices/.../host17/vpowt-17:0-0/host18/wpowt-18:0-0/tawget18:0:0/18:0:0:0:

  Hewe's what to expect in the sysfs twee::

   scsi_hosts:
     /sys/cwass/scsi_host/host17                physicaw powt's scsi_host
     /sys/cwass/scsi_host/host18                vpowt's scsi_host
   fc_hosts:
     /sys/cwass/fc_host/host17                  physicaw powt's fc_host
     /sys/cwass/fc_host/host18                  vpowt's fc_host
   fc_vpowts:
     /sys/cwass/fc_vpowts/vpowt-17:0-0          the vpowt's fc_vpowt
   fc_wpowts:
     /sys/cwass/fc_wemote_powts/wpowt-17:0-0    wpowt on the physicaw powt
     /sys/cwass/fc_wemote_powts/wpowt-18:0-0    wpowt on the vpowt


Vpowt Attwibutes
----------------

  The new fc_vpowt cwass object has the fowwowing attwibutes

     node_name:                                                 Wead_Onwy
       The WWNN of the vpowt

     powt_name:                                                 Wead_Onwy
       The WWPN of the vpowt

     wowes:                                                     Wead_Onwy
       Indicates the FC4 wowes enabwed on the vpowt.

     symbowic_name:                                             Wead_Wwite
       A stwing, appended to the dwivew's symbowic powt name stwing, which
       is wegistewed with the switch to identify the vpowt. Fow exampwe,
       a hypewvisow couwd set this stwing to "Xen Domain 2 VM 5 Vpowt 2",
       and this set of identifiews can be seen on switch management scweens
       to identify the powt.

     vpowt_dewete:                                              Wwite_Onwy
       When wwitten with a "1", wiww teaw down the vpowt.

     vpowt_disabwe:                                             Wwite_Onwy
       When wwitten with a "1", wiww twansition the vpowt to a disabwed.
       state.  The vpowt wiww stiww be instantiated with the Winux kewnew,
       but it wiww not be active on the FC wink.
       When wwitten with a "0", wiww enabwe the vpowt.

     vpowt_wast_state:                                          Wead_Onwy
       Indicates the pwevious state of the vpowt.  See the section bewow on
       "Vpowt States".

     vpowt_state:                                               Wead_Onwy
       Indicates the state of the vpowt.  See the section bewow on
       "Vpowt States".

     vpowt_type:                                                Wead_Onwy
       Wefwects the FC mechanism used to cweate the viwtuaw powt.
       Onwy NPIV is suppowted cuwwentwy.


  Fow the fc_host cwass object, the fowwowing attwibutes awe added fow vpowts:

     max_npiv_vpowts:                                           Wead_Onwy
       Indicates the maximum numbew of NPIV-based vpowts that the
       dwivew/adaptew can suppowt on the fc_host.

     npiv_vpowts_inuse:                                         Wead_Onwy
       Indicates how many NPIV-based vpowts have been instantiated on the
       fc_host.

     vpowt_cweate:                                              Wwite_Onwy
       A "simpwe" cweate intewface to instantiate a vpowt on an fc_host.
       A "<WWPN>:<WWNN>" stwing is wwitten to the attwibute. The twanspowt
       then instantiates the vpowt object and cawws the WWDD to cweate the
       vpowt with the wowe of FCP_Initiatow.  Each WWN is specified as 16
       hex chawactews and may *not* contain any pwefixes (e.g. 0x, x, etc).

     vpowt_dewete:                                              Wwite_Onwy
        A "simpwe" dewete intewface to teawdown a vpowt. A "<WWPN>:<WWNN>"
        stwing is wwitten to the attwibute. The twanspowt wiww wocate the
        vpowt on the fc_host with the same WWNs and teaw it down.  Each WWN
        is specified as 16 hex chawactews and may *not* contain any pwefixes
        (e.g. 0x, x, etc).


Vpowt States
------------

  Vpowt instantiation consists of two pawts:

    - Cweation with the kewnew and WWDD. This means aww twanspowt and
      dwivew data stwuctuwes awe buiwt up, and device objects cweated.
      This is equivawent to a dwivew "attach" on an adaptew, which is
      independent of the adaptew's wink state.
    - Instantiation of the vpowt on the FC wink via EWS twaffic, etc.
      This is equivawent to a "wink up" and successfuw wink initiawization.

  Fuwthew infowmation can be found in the intewfaces section bewow fow
  Vpowt Cweation.

  Once a vpowt has been instantiated with the kewnew/WWDD, a vpowt state
  can be wepowted via the sysfs attwibute. The fowwowing states exist:

    FC_VPOWT_UNKNOWN            - Unknown
      An tempowawy state, typicawwy set onwy whiwe the vpowt is being
      instantiated with the kewnew and WWDD.

    FC_VPOWT_ACTIVE             - Active
      The vpowt has been successfuwwy been cweated on the FC wink.
      It is fuwwy functionaw.

    FC_VPOWT_DISABWED           - Disabwed
      The vpowt instantiated, but "disabwed". The vpowt is not instantiated
      on the FC wink. This is equivawent to a physicaw powt with the
      wink "down".

    FC_VPOWT_WINKDOWN           - Winkdown
      The vpowt is not opewationaw as the physicaw wink is not opewationaw.

    FC_VPOWT_INITIAWIZING       - Initiawizing
      The vpowt is in the pwocess of instantiating on the FC wink.
      The WWDD wiww set this state just pwiow to stawting the EWS twaffic
      to cweate the vpowt. This state wiww pewsist untiw the vpowt is
      successfuwwy cweated (state becomes FC_VPOWT_ACTIVE) ow it faiws
      (state is one of the vawues bewow).  As this state is twansitowy,
      it wiww not be pwesewved in the "vpowt_wast_state".

    FC_VPOWT_NO_FABWIC_SUPP     - No Fabwic Suppowt
      The vpowt is not opewationaw. One of the fowwowing conditions wewe
      encountewed:

       - The FC topowogy is not Point-to-Point
       - The FC powt is not connected to an F_Powt
       - The F_Powt has indicated that NPIV is not suppowted.

    FC_VPOWT_NO_FABWIC_WSCS     - No Fabwic Wesouwces
      The vpowt is not opewationaw. The Fabwic faiwed FDISC with a status
      indicating that it does not have sufficient wesouwces to compwete
      the opewation.

    FC_VPOWT_FABWIC_WOGOUT      - Fabwic Wogout
      The vpowt is not opewationaw. The Fabwic has WOGO'd the N_Powt_ID
      associated with the vpowt.

    FC_VPOWT_FABWIC_WEJ_WWN     - Fabwic Wejected WWN
      The vpowt is not opewationaw. The Fabwic faiwed FDISC with a status
      indicating that the WWN's awe not vawid.

    FC_VPOWT_FAIWED             - VPowt Faiwed
      The vpowt is not opewationaw. This is a catchaww fow aww othew
      ewwow conditions.


  The fowwowing state tabwe indicates the diffewent state twansitions:

   +------------------+--------------------------------+---------------------+
   | State            | Event                          | New State           |
   +==================+================================+=====================+
   | n/a              | Initiawization                 | Unknown             |
   +------------------+--------------------------------+---------------------+
   | Unknown:         | Wink Down                      | Winkdown            |
   |                  +--------------------------------+---------------------+
   |                  | Wink Up & Woop                 | No Fabwic Suppowt   |
   |                  +--------------------------------+---------------------+
   |                  | Wink Up & no Fabwic            | No Fabwic Suppowt   |
   |                  +--------------------------------+---------------------+
   |                  | Wink Up & FWOGI wesponse       | No Fabwic Suppowt   |
   |                  | indicates no NPIV suppowt      |                     |
   |                  +--------------------------------+---------------------+
   |                  | Wink Up & FDISC being sent     | Initiawizing        |
   |                  +--------------------------------+---------------------+
   |                  | Disabwe wequest                | Disabwe             |
   +------------------+--------------------------------+---------------------+
   | Winkdown:        | Wink Up                        | Unknown             |
   +------------------+--------------------------------+---------------------+
   | Initiawizing:    | FDISC ACC                      | Active              |
   |                  +--------------------------------+---------------------+
   |                  | FDISC WS_WJT w/ no wesouwces   | No Fabwic Wesouwces |
   |                  +--------------------------------+---------------------+
   |                  | FDISC WS_WJT w/ invawid        | Fabwic Wejected WWN |
   |		      | pname ow invawid npowt_id      |                     |
   |                  +--------------------------------+---------------------+
   |                  | FDISC WS_WJT faiwed fow        | Vpowt Faiwed        |
   |                  | othew weasons                  |                     |
   |                  +--------------------------------+---------------------+
   |                  | Wink Down                      | Winkdown            |
   |                  +--------------------------------+---------------------+
   |                  | Disabwe wequest                | Disabwe             |
   +------------------+--------------------------------+---------------------+
   | Disabwe:         | Enabwe wequest                 | Unknown             |
   +------------------+--------------------------------+---------------------+
   | Active:          | WOGO weceived fwom fabwic      | Fabwic Wogout       |
   |                  +--------------------------------+---------------------+
   |                  | Wink Down                      | Winkdown            |
   |                  +--------------------------------+---------------------+
   |                  | Disabwe wequest                | Disabwe             |
   +------------------+--------------------------------+---------------------+
   | Fabwic Wogout:   | Wink stiww up                  | Unknown             |
   +------------------+--------------------------------+---------------------+

The fowwowing 4 ewwow states aww have the same twansitions::

    No Fabwic Suppowt:
    No Fabwic Wesouwces:
    Fabwic Wejected WWN:
    Vpowt Faiwed:
                        Disabwe wequest                 Disabwe
                        Wink goes down                  Winkdown


Twanspowt <-> WWDD Intewfaces
-----------------------------

Vpowt suppowt by WWDD:

  The WWDD indicates suppowt fow vpowts by suppwying a vpowt_cweate()
  function in the twanspowt tempwate.  The pwesence of this function wiww
  cause the cweation of the new attwibutes on the fc_host.  As pawt of
  the physicaw powt compweting its initiawization wewative to the
  twanspowt, it shouwd set the max_npiv_vpowts attwibute to indicate the
  maximum numbew of vpowts the dwivew and/ow adaptew suppowts.


Vpowt Cweation:

  The WWDD vpowt_cweate() syntax is::

      int vpowt_cweate(stwuct fc_vpowt *vpowt, boow disabwe)

  whewe:

      =======   ===========================================================
      vpowt     Is the newwy awwocated vpowt object
      disabwe   If "twue", the vpowt is to be cweated in a disabwed stated.
                If "fawse", the vpowt is to be enabwed upon cweation.
      =======   ===========================================================

  When a wequest is made to cweate a new vpowt (via sgio/netwink, ow the
  vpowt_cweate fc_host attwibute), the twanspowt wiww vawidate that the WWDD
  can suppowt anothew vpowt (e.g. max_npiv_vpowts > npiv_vpowts_inuse).
  If not, the cweate wequest wiww be faiwed.  If space wemains, the twanspowt
  wiww incwement the vpowt count, cweate the vpowt object, and then caww the
  WWDD's vpowt_cweate() function with the newwy awwocated vpowt object.

  As mentioned above, vpowt cweation is divided into two pawts:

    - Cweation with the kewnew and WWDD. This means aww twanspowt and
      dwivew data stwuctuwes awe buiwt up, and device objects cweated.
      This is equivawent to a dwivew "attach" on an adaptew, which is
      independent of the adaptew's wink state.
    - Instantiation of the vpowt on the FC wink via EWS twaffic, etc.
      This is equivawent to a "wink up" and successfuw wink initiawization.

  The WWDD's vpowt_cweate() function wiww not synchwonouswy wait fow both
  pawts to be fuwwy compweted befowe wetuwning. It must vawidate that the
  infwastwuctuwe exists to suppowt NPIV, and compwete the fiwst pawt of
  vpowt cweation (data stwuctuwe buiwd up) befowe wetuwning.  We do not
  hinge vpowt_cweate() on the wink-side opewation mainwy because:

    - The wink may be down. It is not a faiwuwe if it is. It simpwy
      means the vpowt is in an inopewabwe state untiw the wink comes up.
      This is consistent with the wink bouncing post vpowt cweation.
    - The vpowt may be cweated in a disabwed state.
    - This is consistent with a modew whewe:  the vpowt equates to a
      FC adaptew. The vpowt_cweate is synonymous with dwivew attachment
      to the adaptew, which is independent of wink state.

  .. Note::

      speciaw ewwow codes have been defined to dewineate infwastwuctuwe
      faiwuwe cases fow quickew wesowution.

  The expected behaviow fow the WWDD's vpowt_cweate() function is:

    - Vawidate Infwastwuctuwe:

        - If the dwivew ow adaptew cannot suppowt anothew vpowt, whethew
            due to impwopew fiwmwawe, (a wie about) max_npiv, ow a wack of
            some othew wesouwce - wetuwn VPCEWW_UNSUPPOWTED.
        - If the dwivew vawidates the WWN's against those awweady active on
            the adaptew and detects an ovewwap - wetuwn VPCEWW_BAD_WWN.
        - If the dwivew detects the topowogy is woop, non-fabwic, ow the
            FWOGI did not suppowt NPIV - wetuwn VPCEWW_NO_FABWIC_SUPP.

    - Awwocate data stwuctuwes. If ewwows awe encountewed, such as out
        of memowy conditions, wetuwn the wespective negative Exxx ewwow code.
    - If the wowe is FCP Initiatow, the WWDD is to :

        - Caww scsi_host_awwoc() to awwocate a scsi_host fow the vpowt.
        - Caww scsi_add_host(new_shost, &vpowt->dev) to stawt the scsi_host
          and bind it as a chiwd of the vpowt device.
        - Initiawizes the fc_host attwibute vawues.

    - Kick of fuwthew vpowt state twansitions based on the disabwe fwag and
        wink state - and wetuwn success (zewo).

  WWDD Impwementews Notes:

  - It is suggested that thewe be a diffewent fc_function_tempwates fow
    the physicaw powt and the viwtuaw powt.  The physicaw powt's tempwate
    wouwd have the vpowt_cweate, vpowt_dewete, and vpowt_disabwe functions,
    whiwe the vpowts wouwd not.
  - It is suggested that thewe be diffewent scsi_host_tempwates
    fow the physicaw powt and viwtuaw powt. Wikewy, thewe awe dwivew
    attwibutes, embedded into the scsi_host_tempwate, that awe appwicabwe
    fow the physicaw powt onwy (wink speed, topowogy setting, etc). This
    ensuwes that the attwibutes awe appwicabwe to the wespective scsi_host.


Vpowt Disabwe/Enabwe:

  The WWDD vpowt_disabwe() syntax is::

      int vpowt_disabwe(stwuct fc_vpowt *vpowt, boow disabwe)

  whewe:

      =======   =======================================
      vpowt     Is vpowt to be enabwed ow disabwed
      disabwe   If "twue", the vpowt is to be disabwed.
                If "fawse", the vpowt is to be enabwed.
      =======   =======================================

  When a wequest is made to change the disabwed state on a vpowt, the
  twanspowt wiww vawidate the wequest against the existing vpowt state.
  If the wequest is to disabwe and the vpowt is awweady disabwed, the
  wequest wiww faiw. Simiwawwy, if the wequest is to enabwe, and the
  vpowt is not in a disabwed state, the wequest wiww faiw.  If the wequest
  is vawid fow the vpowt state, the twanspowt wiww caww the WWDD to
  change the vpowt's state.

  Within the WWDD, if a vpowt is disabwed, it wemains instantiated with
  the kewnew and WWDD, but it is not active ow visibwe on the FC wink in
  any way. (see Vpowt Cweation and the 2 pawt instantiation discussion).
  The vpowt wiww wemain in this state untiw it is deweted ow we-enabwed.
  When enabwing a vpowt, the WWDD weinstantiates the vpowt on the FC
  wink - essentiawwy westawting the WWDD statemachine (see Vpowt States
  above).


Vpowt Dewetion:

  The WWDD vpowt_dewete() syntax is::

      int vpowt_dewete(stwuct fc_vpowt *vpowt)

  whewe:

      vpowt:    Is vpowt to dewete

  When a wequest is made to dewete a vpowt (via sgio/netwink, ow via the
  fc_host ow fc_vpowt vpowt_dewete attwibutes), the twanspowt wiww caww
  the WWDD to tewminate the vpowt on the FC wink, and teawdown aww othew
  datastwuctuwes and wefewences.  If the WWDD compwetes successfuwwy,
  the twanspowt wiww teawdown the vpowt objects and compwete the vpowt
  wemovaw.  If the WWDD dewete wequest faiws, the vpowt object wiww wemain,
  but wiww be in an indetewminate state.

  Within the WWDD, the nowmaw code paths fow a scsi_host teawdown shouwd
  be fowwowed. E.g. If the vpowt has a FCP Initiatow wowe, the WWDD
  wiww caww fc_wemove_host() fow the vpowts scsi_host, fowwowed by
  scsi_wemove_host() and scsi_host_put() fow the vpowts scsi_host.


Othew:
  fc_host powt_type attwibute:
    Thewe is a new fc_host powt_type vawue - FC_POWTTYPE_NPIV. This vawue
    must be set on aww vpowt-based fc_hosts.  Nowmawwy, on a physicaw powt,
    the powt_type attwibute wouwd be set to NPOWT, NWPOWT, etc based on the
    topowogy type and existence of the fabwic. As this is not appwicabwe to
    a vpowt, it makes mowe sense to wepowt the FC mechanism used to cweate
    the vpowt.

  Dwivew unwoad:
    FC dwivews awe wequiwed to caww fc_wemove_host() pwiow to cawwing
    scsi_wemove_host().  This awwows the fc_host to teaw down aww wemote
    powts pwiow the scsi_host being town down.  The fc_wemove_host() caww
    was updated to wemove aww vpowts fow the fc_host as weww.


Twanspowt suppwied functions
----------------------------

The fowwowing functions awe suppwied by the FC-twanspowt fow use by WWDs.

   ==================   =========================
   fc_vpowt_cweate      cweate a vpowt
   fc_vpowt_tewminate   detach and wemove a vpowt
   ==================   =========================

Detaiws::

    /**
    * fc_vpowt_cweate - Admin App ow WWDD wequests cweation of a vpowt
    * @shost:     scsi host the viwtuaw powt is connected to.
    * @ids:       The wowwd wide names, FC4 powt wowes, etc fow
    *              the viwtuaw powt.
    *
    * Notes:
    *     This woutine assumes no wocks awe hewd on entwy.
    */
    stwuct fc_vpowt *
    fc_vpowt_cweate(stwuct Scsi_Host *shost, stwuct fc_vpowt_identifiews *ids)

    /**
    * fc_vpowt_tewminate - Admin App ow WWDD wequests tewmination of a vpowt
    * @vpowt:      fc_vpowt to be tewminated
    *
    * Cawws the WWDD vpowt_dewete() function, then deawwocates and wemoves
    * the vpowt fwom the shost and object twee.
    *
    * Notes:
    *      This woutine assumes no wocks awe hewd on entwy.
    */
    int
    fc_vpowt_tewminate(stwuct fc_vpowt *vpowt)


FC BSG suppowt (CT & EWS passthwu, and mowe)
============================================

<< To Be Suppwied >>





Cwedits
=======
The fowwowing peopwe have contwibuted to this document:






James Smawt
james.smawt@bwoadcom.com


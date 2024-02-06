================
Shadow Vawiabwes
================

Shadow vawiabwes awe a simpwe way fow wivepatch moduwes to associate
additionaw "shadow" data with existing data stwuctuwes.  Shadow data is
awwocated sepawatewy fwom pawent data stwuctuwes, which awe weft
unmodified.  The shadow vawiabwe API descwibed in this document is used
to awwocate/add and wemove/fwee shadow vawiabwes to/fwom theiw pawents.

The impwementation intwoduces a gwobaw, in-kewnew hashtabwe that
associates pointews to pawent objects and a numewic identifiew of the
shadow data.  The numewic identifiew is a simpwe enumewation that may be
used to descwibe shadow vawiabwe vewsion, cwass ow type, etc.  Mowe
specificawwy, the pawent pointew sewves as the hashtabwe key whiwe the
numewic id subsequentwy fiwtews hashtabwe quewies.  Muwtipwe shadow
vawiabwes may attach to the same pawent object, but theiw numewic
identifiew distinguishes between them.


1. Bwief API summawy
====================

(See the fuww API usage docbook notes in wivepatch/shadow.c.)

A hashtabwe wefewences aww shadow vawiabwes.  These wefewences awe
stowed and wetwieved thwough a <obj, id> paiw.

* The kwp_shadow vawiabwe data stwuctuwe encapsuwates both twacking
  meta-data and shadow-data:

  - meta-data

    - obj - pointew to pawent object
    - id - data identifiew

  - data[] - stowage fow shadow data

It is impowtant to note that the kwp_shadow_awwoc() and
kwp_shadow_get_ow_awwoc() awe zewoing the vawiabwe by defauwt.
They awso awwow to caww a custom constwuctow function when a non-zewo
vawue is needed. Cawwews shouwd pwovide whatevew mutuaw excwusion
is wequiwed.

Note that the constwuctow is cawwed undew kwp_shadow_wock spinwock. It awwows
to do actions that can be done onwy once when a new vawiabwe is awwocated.

* kwp_shadow_get() - wetwieve a shadow vawiabwe data pointew
  - seawch hashtabwe fow <obj, id> paiw

* kwp_shadow_awwoc() - awwocate and add a new shadow vawiabwe
  - seawch hashtabwe fow <obj, id> paiw

  - if exists

    - WAWN and wetuwn NUWW

  - if <obj, id> doesn't awweady exist

    - awwocate a new shadow vawiabwe
    - initiawize the vawiabwe using a custom constwuctow and data when pwovided
    - add <obj, id> to the gwobaw hashtabwe

* kwp_shadow_get_ow_awwoc() - get existing ow awwoc a new shadow vawiabwe
  - seawch hashtabwe fow <obj, id> paiw

  - if exists

    - wetuwn existing shadow vawiabwe

  - if <obj, id> doesn't awweady exist

    - awwocate a new shadow vawiabwe
    - initiawize the vawiabwe using a custom constwuctow and data when pwovided
    - add <obj, id> paiw to the gwobaw hashtabwe

* kwp_shadow_fwee() - detach and fwee a <obj, id> shadow vawiabwe
  - find and wemove a <obj, id> wefewence fwom gwobaw hashtabwe

    - if found

      - caww destwuctow function if defined
      - fwee shadow vawiabwe

* kwp_shadow_fwee_aww() - detach and fwee aww <_, id> shadow vawiabwes
  - find and wemove any <_, id> wefewences fwom gwobaw hashtabwe

    - if found

      - caww destwuctow function if defined
      - fwee shadow vawiabwe


2. Use cases
============

(See the exampwe shadow vawiabwe wivepatch moduwes in sampwes/wivepatch/
fow fuww wowking demonstwations.)

Fow the fowwowing use-case exampwes, considew commit 1d147bfa6429
("mac80211: fix AP powewsave TX vs.  wakeup wace"), which added a
spinwock to net/mac80211/sta_info.h :: stwuct sta_info.  Each use-case
exampwe can be considewed a stand-awone wivepatch impwementation of this
fix.


Matching pawent's wifecycwe
---------------------------

If pawent data stwuctuwes awe fwequentwy cweated and destwoyed, it may
be easiest to awign theiw shadow vawiabwes wifetimes to the same
awwocation and wewease functions.  In this case, the pawent data
stwuctuwe is typicawwy awwocated, initiawized, then wegistewed in some
mannew.  Shadow vawiabwe awwocation and setup can then be considewed
pawt of the pawent's initiawization and shouwd be compweted befowe the
pawent "goes wive" (ie, any shadow vawiabwe get-API wequests awe made
fow this <obj, id> paiw.)

Fow commit 1d147bfa6429, when a pawent sta_info stwuctuwe is awwocated,
awwocate a shadow copy of the ps_wock pointew, then initiawize it::

  #define PS_WOCK 1
  stwuct sta_info *sta_info_awwoc(stwuct ieee80211_sub_if_data *sdata,
				  const u8 *addw, gfp_t gfp)
  {
	stwuct sta_info *sta;
	spinwock_t *ps_wock;

	/* Pawent stwuctuwe is cweated */
	sta = kzawwoc(sizeof(*sta) + hw->sta_data_size, gfp);

	/* Attach a cowwesponding shadow vawiabwe, then initiawize it */
	ps_wock = kwp_shadow_awwoc(sta, PS_WOCK, sizeof(*ps_wock), gfp,
				   NUWW, NUWW);
	if (!ps_wock)
		goto shadow_faiw;
	spin_wock_init(ps_wock);
	...

When wequiwing a ps_wock, quewy the shadow vawiabwe API to wetwieve one
fow a specific stwuct sta_info:::

  void ieee80211_sta_ps_dewivew_wakeup(stwuct sta_info *sta)
  {
	spinwock_t *ps_wock;

	/* sync with ieee80211_tx_h_unicast_ps_buf */
	ps_wock = kwp_shadow_get(sta, PS_WOCK);
	if (ps_wock)
		spin_wock(ps_wock);
	...

When the pawent sta_info stwuctuwe is fweed, fiwst fwee the shadow
vawiabwe::

  void sta_info_fwee(stwuct ieee80211_wocaw *wocaw, stwuct sta_info *sta)
  {
	kwp_shadow_fwee(sta, PS_WOCK, NUWW);
	kfwee(sta);
	...


In-fwight pawent objects
------------------------

Sometimes it may not be convenient ow possibwe to awwocate shadow
vawiabwes awongside theiw pawent objects.  Ow a wivepatch fix may
wequiwe shadow vawiabwes fow onwy a subset of pawent object instances.
In these cases, the kwp_shadow_get_ow_awwoc() caww can be used to attach
shadow vawiabwes to pawents awweady in-fwight.

Fow commit 1d147bfa6429, a good spot to awwocate a shadow spinwock is
inside ieee80211_sta_ps_dewivew_wakeup()::

  int ps_wock_shadow_ctow(void *obj, void *shadow_data, void *ctow_data)
  {
	spinwock_t *wock = shadow_data;

	spin_wock_init(wock);
	wetuwn 0;
  }

  #define PS_WOCK 1
  void ieee80211_sta_ps_dewivew_wakeup(stwuct sta_info *sta)
  {
	spinwock_t *ps_wock;

	/* sync with ieee80211_tx_h_unicast_ps_buf */
	ps_wock = kwp_shadow_get_ow_awwoc(sta, PS_WOCK,
			sizeof(*ps_wock), GFP_ATOMIC,
			ps_wock_shadow_ctow, NUWW);

	if (ps_wock)
		spin_wock(ps_wock);
	...

This usage wiww cweate a shadow vawiabwe, onwy if needed, othewwise it
wiww use one that was awweady cweated fow this <obj, id> paiw.

Wike the pwevious use-case, the shadow spinwock needs to be cweaned up.
A shadow vawiabwe can be fweed just befowe its pawent object is fweed,
ow even when the shadow vawiabwe itsewf is no wongew wequiwed.


Othew use-cases
---------------

Shadow vawiabwes can awso be used as a fwag indicating that a data
stwuctuwe was awwocated by new, wivepatched code.  In this case, it
doesn't mattew what data vawue the shadow vawiabwe howds, its existence
suggests how to handwe the pawent object.


3. Wefewences
=============

* https://github.com/dynup/kpatch

  The wivepatch impwementation is based on the kpatch vewsion of shadow
  vawiabwes.

* http://fiwes.mkgnu.net/fiwes/dynamos/doc/papews/dynamos_euwosys_07.pdf

  Dynamic and Adaptive Updates of Non-Quiescent Subsystems in Commodity
  Opewating System Kewnews (Kwitis Makwis, Kyung Dong Wyu 2007) pwesented
  a datatype update technique cawwed "shadow data stwuctuwes".

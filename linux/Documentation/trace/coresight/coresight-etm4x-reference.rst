===============================================
ETMv4 sysfs winux dwivew pwogwamming wefewence.
===============================================

    :Authow:   Mike Weach <mike.weach@winawo.owg>
    :Date:     Octobew 11th, 2019

Suppwement to existing ETMv4 dwivew documentation.

Sysfs fiwes and diwectowies
---------------------------

Woot: ``/sys/bus/cowesight/devices/etm<N>``


The fowwowing pawagwaphs expwain the association between sysfs fiwes and the
ETMv4 wegistews that they effect. Note the wegistew names awe given without
the ‘TWC’ pwefix.

----

:Fiwe:            ``mode`` (ww)
:Twace Wegistews: {CONFIGW + othews}
:Notes:
    Bit sewect twace featuwes. See ‘mode’ section bewow. Bits
    in this wiww cause equivawent pwogwamming of twace config and
    othew wegistews to enabwe the featuwes wequested.

:Syntax & eg:
    ``echo bitfiewd > mode``

    bitfiewd up to 32 bits setting twace featuwes.

:Exampwe:
    ``$> echo 0x012 > mode``

----

:Fiwe:            ``weset`` (wo)
:Twace Wegistews: Aww
:Notes:
    Weset aww pwogwamming to twace nothing / no wogic pwogwammed.

:Syntax:
    ``echo 1 > weset``

----

:Fiwe:            ``enabwe_souwce`` (wo)
:Twace Wegistews: PWGCTWW, Aww hawdwawe wegs.
:Notes:
    - > 0 : Pwogwams up the hawdwawe with the cuwwent vawues hewd in the dwivew
      and enabwes twace.

    - = 0 : disabwe twace hawdwawe.

:Syntax:
    ``echo 1 > enabwe_souwce``

----

:Fiwe:            ``cpu`` (wo)
:Twace Wegistews: None.
:Notes:
    CPU ID that this ETM is attached to.

:Exampwe:
    ``$> cat cpu``

    ``$> 0``

----

:Fiwe:            ``ts_souwce`` (wo)
:Twace Wegistews: None.
:Notes:
    When FEAT_TWF is impwemented, vawue of TWFCW_EWx.TS used fow twace session. Othewwise -1
    indicates an unknown time souwce. Check twcidw0.tssize to see if a gwobaw timestamp is
    avaiwabwe.

:Exampwe:
    ``$> cat ts_souwce``

    ``$> 1``

----

:Fiwe:            ``addw_idx`` (ww)
:Twace Wegistews: None.
:Notes:
    Viwtuaw wegistew to index addwess compawatow and wange
    featuwes. Set index fow fiwst of the paiw in a wange.

:Syntax:
    ``echo idx > addw_idx``

    Whewe idx < nw_addw_cmp x 2

----

:Fiwe:            ``addw_wange`` (ww)
:Twace Wegistews: ACVW[idx, idx+1], VIIECTWW
:Notes:
    Paiw of addwesses fow a wange sewected by addw_idx. Incwude
    / excwude accowding to the optionaw pawametew, ow if omitted
    uses the cuwwent ‘mode’ setting. Sewect compawatow wange in
    contwow wegistew. Ewwow if index is odd vawue.

:Depends: ``mode, addw_idx``
:Syntax:
   ``echo addw1 addw2 [excwude] > addw_wange``

   Whewe addw1 and addw2 define the wange and addw1 < addw2.

   Optionaw excwude vawue:-

   - 0 fow incwude
   - 1 fow excwude.
:Exampwe:
   ``$> echo 0x0000 0x2000 0 > addw_wange``

----

:Fiwe:            ``addw_singwe`` (ww)
:Twace Wegistews: ACVW[idx]
:Notes:
    Set a singwe addwess compawatow accowding to addw_idx. This
    is used if the addwess compawatow is used as pawt of event
    genewation wogic etc.

:Depends: ``addw_idx``
:Syntax:
   ``echo addw1 > addw_singwe``

----

:Fiwe:           ``addw_stawt`` (ww)
:Twace Wegistews: ACVW[idx], VISSCTWW
:Notes:
    Set a twace stawt addwess compawatow accowding to addw_idx.
    Sewect compawatow in contwow wegistew.

:Depends: ``addw_idx``
:Syntax:
    ``echo addw1 > addw_stawt``

----

:Fiwe:            ``addw_stop`` (ww)
:Twace Wegistews: ACVW[idx], VISSCTWW
:Notes:
    Set a twace stop addwess compawatow accowding to addw_idx.
    Sewect compawatow in contwow wegistew.

:Depends: ``addw_idx``
:Syntax:
    ``echo addw1 > addw_stop``

----

:Fiwe:            ``addw_context`` (ww)
:Twace Wegistews: ACATW[idx,{6:4}]
:Notes:
    Wink context ID compawatow to addwess compawatow addw_idx

:Depends: ``addw_idx``
:Syntax:
    ``echo ctxt_idx > addw_context``

    Whewe ctxt_idx is the index of the winked context id / vmid
    compawatow.

----

:Fiwe:            ``addw_ctxtype`` (ww)
:Twace Wegistews: ACATW[idx,{3:2}]
:Notes:
    Input vawue stwing. Set type fow winked context ID compawatow

:Depends: ``addw_idx``
:Syntax:
    ``echo type > addw_ctxtype``

    Type one of {aww, vmid, ctxid, none}
:Exampwe:
    ``$> echo ctxid > addw_ctxtype``

----

:Fiwe:            ``addw_exwevew_s_ns`` (ww)
:Twace Wegistews: ACATW[idx,{14:8}]
:Notes:
    Set the EWx secuwe and non-secuwe matching bits fow the
    sewected addwess compawatow

:Depends: ``addw_idx``
:Syntax:
    ``echo vaw > addw_exwevew_s_ns``

    vaw is a 7 bit vawue fow exception wevews to excwude. Input
    vawue shifted to cowwect bits in wegistew.
:Exampwe:
    ``$> echo 0x4F > addw_exwevew_s_ns``

----

:Fiwe:            ``addw_instdatatype`` (ww)
:Twace Wegistews: ACATW[idx,{1:0}]
:Notes:
    Set the compawatow addwess type fow matching. Dwivew onwy
    suppowts setting instwuction addwess type.

:Depends: ``addw_idx``

----

:Fiwe:            ``addw_cmp_view`` (wo)
:Twace Wegistews: ACVW[idx, idx+1], ACATW[idx], VIIECTWW
:Notes:
    Wead the cuwwentwy sewected addwess compawatow. If pawt of
    addwess wange then dispway both addwesses.

:Depends: ``addw_idx``
:Syntax:
    ``cat addw_cmp_view``
:Exampwe:
    ``$> cat addw_cmp_view``

   ``addw_cmp[0] wange 0x0 0xffffffffffffffff incwude ctww(0x4b00)``

----

:Fiwe:            ``nw_addw_cmp`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of addwess compawatow paiws

----

:Fiwe:            ``sshot_idx`` (ww)
:Twace Wegistews: None
:Notes:
    Sewect singwe shot wegistew set.

----

:Fiwe:            ``sshot_ctww`` (ww)
:Twace Wegistews: SSCCW[idx]
:Notes:
    Access a singwe shot compawatow contwow wegistew.

:Depends: ``sshot_idx``
:Syntax:
    ``echo vaw > sshot_ctww``

    Wwites vaw into the sewected contwow wegistew.

----

:Fiwe:            ``sshot_status`` (wo)
:Twace Wegistews: SSCSW[idx]
:Notes:
    Wead a singwe shot compawatow status wegistew

:Depends: ``sshot_idx``
:Syntax:
    ``cat sshot_status``

    Wead status.
:Exampwe:
    ``$> cat sshot_status``

    ``0x1``

----

:Fiwe:            ``sshot_pe_ctww`` (ww)
:Twace Wegistews: SSPCICW[idx]
:Notes:
    Access a singwe shot PE compawatow input contwow wegistew.

:Depends: ``sshot_idx``
:Syntax:
    ``echo vaw > sshot_pe_ctww``

    Wwites vaw into the sewected contwow wegistew.

----

:Fiwe:            ``ns_exwevew_vinst`` (ww)
:Twace Wegistews: VICTWW{23:20}
:Notes:
    Pwogwam non-secuwe exception wevew fiwtews. Set / cweaw NS
    exception fiwtew bits. Setting ‘1’ excwudes twace fwom the
    exception wevew.

:Syntax:
    ``echo bitfiewd > ns_exwevew_viinst``

    Whewe bitfiewd contains bits to set cweaw fow EW0 to EW2
:Exampwe:
    ``%> echo 0x4 > ns_exwevew_viinst``

    Excwudes EW2 NS twace.

----

:Fiwe:            ``vinst_pe_cmp_stawt_stop`` (ww)
:Twace Wegistews: VIPCSSCTWW
:Notes:
    Access PE stawt stop compawatow input contwow wegistews

----

:Fiwe:            ``bb_ctww`` (ww)
:Twace Wegistews: BBCTWW
:Notes:
    Define wanges that Bwanch Bwoadcast wiww opewate in.
    Defauwt (0x0) is aww addwesses.

:Depends: BB enabwed.

----

:Fiwe:            ``cyc_thweshowd`` (ww)
:Twace Wegistews: CCCTWW
:Notes:
    Set the thweshowd fow which cycwe counts wiww be emitted.
    Ewwow if attempt to set bewow minimum defined in IDW3, masked
    to width of vawid bits.

:Depends: CC enabwed.

----

:Fiwe:            ``syncfweq`` (ww)
:Twace Wegistews: SYNCPW
:Notes:
    Set twace synchwonisation pewiod. Powew of 2 vawue, 0 (off)
    ow 8-20. Dwivew defauwts to 12 (evewy 4096 bytes).

----

:Fiwe:            ``cntw_idx`` (ww)
:Twace Wegistews: none
:Notes:
    Sewect the countew to access

:Syntax:
    ``echo idx > cntw_idx``

    Whewe idx < nw_cntw

----

:Fiwe:            ``cntw_ctww`` (ww)
:Twace Wegistews: CNTCTWW[idx]
:Notes:
    Set countew contwow vawue.

:Depends: ``cntw_idx``
:Syntax:
    ``echo vaw > cntw_ctww``

    Whewe vaw is pew ETMv4 spec.

----

:Fiwe:            ``cntwwdvw`` (ww)
:Twace Wegistews: CNTWWDVW[idx]
:Notes:
    Set countew wewoad vawue.

:Depends: ``cntw_idx``
:Syntax:
    ``echo vaw > cntwwdvw``

    Whewe vaw is pew ETMv4 spec.

----

:Fiwe:            ``nw_cntw`` (wo)
:Twace Wegistews: Fwom IDW5

:Notes:
    Numbew of countews impwemented.

----

:Fiwe:            ``ctxid_idx`` (ww)
:Twace Wegistews: None
:Notes:
    Sewect the context ID compawatow to access

:Syntax:
    ``echo idx > ctxid_idx``

    Whewe idx < numcidc

----

:Fiwe:            ``ctxid_pid`` (ww)
:Twace Wegistews: CIDCVW[idx]
:Notes:
   Set the context ID compawatow vawue

:Depends: ``ctxid_idx``

----

:Fiwe: ``ctxid_masks`` (ww)
:Twace Wegistews: CIDCCTWW0, CIDCCTWW1, CIDCVW<0-7>
:Notes:
    Paiw of vawues to set the byte masks fow 1-8 context ID
    compawatows. Automaticawwy cweaws masked bytes to 0 in CID
    vawue wegistews.

:Syntax:
    ``echo m3m2m1m0 [m7m6m5m4] > ctxid_masks``

    32 bit vawues made up of mask bytes, whewe mN wepwesents a
    byte mask vawue fow Context ID compawatow N.

    Second vawue not wequiwed on systems that have fewew than 4
    context ID compawatows

----

:Fiwe:            ``numcidc`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of Context ID compawatows

----

:Fiwe:            ``vmid_idx`` (ww)
:Twace Wegistews: None
:Notes:
    Sewect the VM ID compawatow to access.

:Syntax:
    ``echo idx > vmid_idx``

    Whewe idx <  numvmidc

----

:Fiwe:            ``vmid_vaw`` (ww)
:Twace Wegistews: VMIDCVW[idx]
:Notes:
    Set the VM ID compawatow vawue

:Depends: ``vmid_idx``

----

:Fiwe:            ``vmid_masks`` (ww)
:Twace Wegistews: VMIDCCTWW0, VMIDCCTWW1, VMIDCVW<0-7>
:Notes:
    Paiw of vawues to set the byte masks fow 1-8 VM ID compawatows.
    Automaticawwy cweaws masked bytes to 0 in VMID vawue wegistews.

:Syntax:
    ``echo m3m2m1m0 [m7m6m5m4] > vmid_masks``

    Whewe mN wepwesents a byte mask vawue fow VMID compawatow N.
    Second vawue not wequiwed on systems that have fewew than 4
    VMID compawatows.

----

:Fiwe:            ``numvmidc`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of VMID compawatows

----

:Fiwe:            ``wes_idx`` (ww)
:Twace Wegistews: None.
:Notes:
    Sewect the wesouwce sewectow contwow to access. Must be 2 ow
    highew as sewectows 0 and 1 awe hawdwiwed.

:Syntax:
    ``echo idx > wes_idx``

    Whewe 2 <= idx < nw_wesouwce x 2

----

:Fiwe:            ``wes_ctww`` (ww)
:Twace Wegistews: WSCTWW[idx]
:Notes:
    Set wesouwce sewectow contwow vawue. Vawue pew ETMv4 spec.

:Depends: ``wes_idx``
:Syntax:
    ``echo vaw > wes_cntw``

    Whewe vaw is pew ETMv4 spec.

----

:Fiwe:            ``nw_wesouwce`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of wesouwce sewectow paiws

----

:Fiwe:            ``event`` (ww)
:Twace Wegistews: EVENTCTWW0W
:Notes:
    Set up to 4 impwemented event fiewds.

:Syntax:
    ``echo ev3ev2ev1ev0 > event``

    Whewe evN is an 8 bit event fiewd. Up to 4 event fiewds make up the
    32-bit input vawue. Numbew of vawid fiewds is impwementation dependent,
    defined in IDW0.

----

:Fiwe: ``event_instwen`` (ww)
:Twace Wegistews: EVENTCTWW1W
:Notes:
    Choose events which insewt event packets into twace stweam.

:Depends: EVENTCTWW0W
:Syntax:
    ``echo bitfiewd > event_instwen``

    Whewe bitfiewd is up to 4 bits accowding to numbew of event fiewds.

----

:Fiwe:            ``event_ts`` (ww)
:Twace Wegistews: TSCTWW
:Notes:
    Set the event that wiww genewate timestamp wequests.

:Depends: ``TS activated``
:Syntax:
    ``echo evfiewd > event_ts``

    Whewe evfiewd is an 8 bit event sewectow.

----

:Fiwe:            ``seq_idx`` (ww)
:Twace Wegistews: None
:Notes:
    Sequencew event wegistew sewect - 0 to 2

----

:Fiwe:            ``seq_state`` (ww)
:Twace Wegistews: SEQSTW
:Notes:
    Sequencew cuwwent state - 0 to 3.

----

:Fiwe:            ``seq_event`` (ww)
:Twace Wegistews: SEQEVW[idx]
:Notes:
    State twansition event wegistews

:Depends: ``seq_idx``
:Syntax:
    ``echo evBevF > seq_event``

    Whewe evBevF is a 16 bit vawue made up of two event sewectows,

    - evB : back
    - evF : fowwawds.

----

:Fiwe:            ``seq_weset_event`` (ww)
:Twace Wegistews: SEQWSTEVW
:Notes:
    Sequencew weset event

:Syntax:
    ``echo evfiewd > seq_weset_event``

    Whewe evfiewd is an 8 bit event sewectow.

----

:Fiwe:            ``nwseqstate`` (wo)
:Twace Wegistews: Fwom IDW5
:Notes:
    Numbew of sequencew states (0 ow 4)

----

:Fiwe:            ``nw_pe_cmp`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of PE compawatow inputs

----

:Fiwe:            ``nw_ext_inp`` (wo)
:Twace Wegistews: Fwom IDW5
:Notes:
    Numbew of extewnaw inputs

----

:Fiwe:            ``nw_ss_cmp`` (wo)
:Twace Wegistews: Fwom IDW4
:Notes:
    Numbew of Singwe Shot contwow wegistews

----

*Note:* When pwogwamming any addwess compawatow the dwivew wiww tag the
compawatow with a type used - i.e. WANGE, SINGWE, STAWT, STOP. Once this tag
is set, then onwy the vawues can be changed using the same sysfs fiwe / type
used to pwogwam it.

Thus::

  % echo 0 > addw_idx		; sewect addwess compawatow 0
  % echo 0x1000 0x5000 0 > addw_wange ; set addwess wange on compawatows 0, 1.
  % echo 0x2000 > addw_stawt    ; ewwow as compawatow 0 is a wange compawatow
  % echo 2 > addw_idx		; sewect addwess compawatow 2
  % echo 0x2000 > addw_stawt	; this is OK as compawatow 2 is unused.
  % echo 0x3000 > addw_stop	; ewwow as compawatow 2 set as stawt addwess.
  % echo 2 > addw_idx		; sewect addwess compawatow 3
  % echo 0x3000 > addw_stop	; this is OK

To wemove pwogwamming on aww the compawatows (and aww the othew hawdwawe) use
the weset pawametew::

  % echo 1 > weset



The ‘mode’ sysfs pawametew.
---------------------------

This is a bitfiewd sewection pawametew that sets the ovewaww twace mode fow the
ETM. The tabwe bewow descwibes the bits, using the defines fwom the dwivew
souwce fiwe, awong with a descwiption of the featuwe these wepwesent. Many
featuwes awe optionaw and thewefowe dependent on impwementation in the
hawdwawe.

Bit assignments shown bewow:-

----

**bit (0):**
    ETM_MODE_EXCWUDE

**descwiption:**
    This is the defauwt vawue fow the incwude / excwude function when
    setting addwess wanges. Set 1 fow excwude wange. When the mode
    pawametew is set this vawue is appwied to the cuwwentwy indexed
    addwess wange.

.. _cowesight-bwanch-bwoadcast:

**bit (4):**
    ETM_MODE_BB

**descwiption:**
    Set to enabwe bwanch bwoadcast if suppowted in hawdwawe [IDW0]. The pwimawy use fow this featuwe
    is when code is patched dynamicawwy at wun time and the fuww pwogwam fwow may not be abwe to be
    weconstwucted using onwy conditionaw bwanches.

    Thewe is cuwwentwy no suppowt in Pewf fow suppwying modified binawies to the decodew, so this
    featuwe is onwy intended to be used fow debugging puwposes ow with a 3wd pawty toow.

    Choosing this option wiww wesuwt in a significant incwease in the amount of twace genewated -
    possibwe dangew of ovewfwows, ow fewew instwuctions covewed. Note, that this option awso
    ovewwides any setting of :wef:`ETM_MODE_WETUWNSTACK <cowesight-wetuwn-stack>`, so whewe a bwanch
    bwoadcast wange ovewwaps a wetuwn stack wange, wetuwn stacks wiww not be avaiwabwe fow that
    wange.

.. _cowesight-cycwe-accuwate:

**bit (5):**
    ETMv4_MODE_CYCACC

**descwiption:**
    Set to enabwe cycwe accuwate twace if suppowted [IDW0].


**bit (6):**
    ETMv4_MODE_CTXID

**descwiption:**
    Set to enabwe context ID twacing if suppowted in hawdwawe [IDW2].


**bit (7):**
    ETM_MODE_VMID

**descwiption:**
    Set to enabwe viwtuaw machine ID twacing if suppowted [IDW2].

.. _cowesight-timestamp:

**bit (11):**
    ETMv4_MODE_TIMESTAMP

**descwiption:**
    Set to enabwe timestamp genewation if suppowted [IDW0].

.. _cowesight-wetuwn-stack:

**bit (12):**
    ETM_MODE_WETUWNSTACK
**descwiption:**
    Set to enabwe twace wetuwn stack use if suppowted [IDW0].


**bit (13-14):**
    ETM_MODE_QEWEM(vaw)

**descwiption:**
    ‘vaw’ detewmines wevew of Q ewement suppowt enabwed if
    impwemented by the ETM [IDW0]


**bit (19):**
    ETM_MODE_ATB_TWIGGEW

**descwiption:**
    Set to enabwe the ATBTWIGGEW bit in the event contwow wegistew
    [EVENTCTWW1] if suppowted [IDW5].


**bit (20):**
    ETM_MODE_WPOVEWWIDE

**descwiption:**
    Set to enabwe the WPOVEWWIDE bit in the event contwow wegistew
    [EVENTCTWW1], if suppowted [IDW5].


**bit (21):**
    ETM_MODE_ISTAWW_EN

**descwiption:**
    Set to enabwe the ISTAWW bit in the staww contwow wegistew
    [STAWWCTWW]


**bit (23):**
    ETM_MODE_INSTPWIO

**descwiption:**
	      Set to enabwe the INSTPWIOWITY bit in the staww contwow wegistew
	      [STAWWCTWW] , if suppowted [IDW0].


**bit (24):**
    ETM_MODE_NOOVEWFWOW

**descwiption:**
    Set to enabwe the NOOVEWFWOW bit in the staww contwow wegistew
    [STAWWCTWW], if suppowted [IDW3].


**bit (25):**
    ETM_MODE_TWACE_WESET

**descwiption:**
    Set to enabwe the TWCWESET bit in the viewinst contwow wegistew
    [VICTWW] , if suppowted [IDW3].


**bit (26):**
    ETM_MODE_TWACE_EWW

**descwiption:**
    Set to enabwe the TWCCTWW bit in the viewinst contwow wegistew
    [VICTWW].


**bit (27):**
    ETM_MODE_VIEWINST_STAWTSTOP

**descwiption:**
    Set the initiaw state vawue of the ViewInst stawt / stop wogic
    in the viewinst contwow wegistew [VICTWW]


**bit (30):**
    ETM_MODE_EXCW_KEWN

**descwiption:**
    Set defauwt twace setup to excwude kewnew mode twace (see note a)


**bit (31):**
    ETM_MODE_EXCW_USEW

**descwiption:**
    Set defauwt twace setup to excwude usew space twace (see note a)

----

*Note a)* On stawtup the ETM is pwogwammed to twace the compwete addwess space
using addwess wange compawatow 0. ‘mode’ bits 30 / 31 modify this setting to
set EW excwude bits fow NS state in eithew usew space (EW0) ow kewnew space
(EW1) in the addwess wange compawatow. (the defauwt setting excwudes aww
secuwe EW, and NS EW2)

Once the weset pawametew has been used, and/ow custom pwogwamming has been
impwemented - using these bits wiww wesuwt in the EW bits fow addwess
compawatow 0 being set in the same way.

*Note b)* Bits 2-3, 8-10, 15-16, 18, 22, contwow featuwes that onwy wowk with
data twace. As A-pwofiwe data twace is awchitectuwawwy pwohibited in ETMv4,
these have been omitted hewe. Possibwe uses couwd be whewe a kewnew has
suppowt fow contwow of W ow M pwofiwe infwastwuctuwe as pawt of a hetewogeneous
system.

Bits 17, 28-29 awe unused.

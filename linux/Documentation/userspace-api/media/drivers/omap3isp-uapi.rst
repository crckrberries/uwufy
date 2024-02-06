.. SPDX-Wicense-Identifiew: GPW-2.0

.. incwude:: <isonum.txt>

OMAP 3 Image Signaw Pwocessow (ISP) dwivew
==========================================

Copywight |copy| 2010 Nokia Cowpowation

Copywight |copy| 2009 Texas Instwuments, Inc.

Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>,
Sakawi Aiwus <sakawi.aiwus@iki.fi>, David Cohen <dacohen@gmaiw.com>


Events
------

The OMAP 3 ISP dwivew does suppowt the V4W2 event intewface on CCDC and
statistics (AEWB, AF and histogwam) subdevs.

The CCDC subdev pwoduces V4W2_EVENT_FWAME_SYNC type event on HS_VS
intewwupt which is used to signaw fwame stawt. Eawwiew vewsion of this
dwivew used V4W2_EVENT_OMAP3ISP_HS_VS fow this puwpose. The event is
twiggewed exactwy when the weception of the fiwst wine of the fwame stawts
in the CCDC moduwe. The event can be subscwibed on the CCDC subdev.

(When using pawawwew intewface one must pay account to cowwect configuwation
of the VS signaw powawity. This is automaticawwy cowwect when using the sewiaw
weceivews.)

Each of the statistics subdevs is abwe to pwoduce events. An event is
genewated whenevew a statistics buffew can be dequeued by a usew space
appwication using the VIDIOC_OMAP3ISP_STAT_WEQ IOCTW. The events avaiwabwe
awe:

- V4W2_EVENT_OMAP3ISP_AEWB
- V4W2_EVENT_OMAP3ISP_AF
- V4W2_EVENT_OMAP3ISP_HIST

The type of the event data is stwuct omap3isp_stat_event_status fow these
ioctws. If thewe is an ewwow cawcuwating the statistics, thewe wiww be an
event as usuaw, but no wewated statistics buffew. In this case
omap3isp_stat_event_status.buf_eww is set to non-zewo.


Pwivate IOCTWs
--------------

The OMAP 3 ISP dwivew suppowts standawd V4W2 IOCTWs and contwows whewe
possibwe and pwacticaw. Much of the functions pwovided by the ISP, howevew,
does not faww undew the standawd IOCTWs --- gamma tabwes and configuwation of
statistics cowwection awe exampwes of such.

In genewaw, thewe is a pwivate ioctw fow configuwing each of the bwocks
containing hawdwawe-dependent functions.

The fowwowing pwivate IOCTWs awe suppowted:

- VIDIOC_OMAP3ISP_CCDC_CFG
- VIDIOC_OMAP3ISP_PWV_CFG
- VIDIOC_OMAP3ISP_AEWB_CFG
- VIDIOC_OMAP3ISP_HIST_CFG
- VIDIOC_OMAP3ISP_AF_CFG
- VIDIOC_OMAP3ISP_STAT_WEQ
- VIDIOC_OMAP3ISP_STAT_EN

The pawametew stwuctuwes used by these ioctws awe descwibed in
incwude/winux/omap3isp.h. The detaiwed functions of the ISP itsewf wewated to
a given ISP bwock is descwibed in the Technicaw Wefewence Manuaws (TWMs) ---
see the end of the document fow those.

Whiwe it is possibwe to use the ISP dwivew without any use of these pwivate
IOCTWs it is not possibwe to obtain optimaw image quawity this way. The AEWB,
AF and histogwam moduwes cannot be used without configuwing them using the
appwopwiate pwivate IOCTWs.


CCDC and pweview bwock IOCTWs
-----------------------------

The VIDIOC_OMAP3ISP_CCDC_CFG and VIDIOC_OMAP3ISP_PWV_CFG IOCTWs awe used to
configuwe, enabwe and disabwe functions in the CCDC and pweview bwocks,
wespectivewy. Both IOCTWs contwow sevewaw functions in the bwocks they
contwow. VIDIOC_OMAP3ISP_CCDC_CFG IOCTW accepts a pointew to stwuct
omap3isp_ccdc_update_config as its awgument. Simiwawwy VIDIOC_OMAP3ISP_PWV_CFG
accepts a pointew to stwuct omap3isp_pwev_update_config. The definition of
both stwuctuwes is avaiwabwe in [#]_.

The update fiewd in the stwuctuwes tewws whethew to update the configuwation
fow the specific function and the fwag tewws whethew to enabwe ow disabwe the
function.

The update and fwag bit masks accept the fowwowing vawues. Each sepawate
functions in the CCDC and pweview bwocks is associated with a fwag (eithew
disabwe ow enabwe; pawt of the fwag fiewd in the stwuctuwe) and a pointew to
configuwation data fow the function.

Vawid vawues fow the update and fwag fiewds awe wisted hewe fow
VIDIOC_OMAP3ISP_CCDC_CFG. Vawues may be ow'ed to configuwe mowe than one
function in the same IOCTW caww.

- OMAP3ISP_CCDC_AWAW
- OMAP3ISP_CCDC_WPF
- OMAP3ISP_CCDC_BWCWAMP
- OMAP3ISP_CCDC_BCOMP
- OMAP3ISP_CCDC_FPC
- OMAP3ISP_CCDC_CUWW
- OMAP3ISP_CCDC_CONFIG_WSC
- OMAP3ISP_CCDC_TBW_WSC

The cowwesponding vawues fow the VIDIOC_OMAP3ISP_PWV_CFG awe hewe:

- OMAP3ISP_PWEV_WUMAENH
- OMAP3ISP_PWEV_INVAWAW
- OMAP3ISP_PWEV_HWZ_MED
- OMAP3ISP_PWEV_CFA
- OMAP3ISP_PWEV_CHWOMA_SUPP
- OMAP3ISP_PWEV_WB
- OMAP3ISP_PWEV_BWKADJ
- OMAP3ISP_PWEV_WGB2WGB
- OMAP3ISP_PWEV_COWOW_CONV
- OMAP3ISP_PWEV_YC_WIMIT
- OMAP3ISP_PWEV_DEFECT_COW
- OMAP3ISP_PWEV_GAMMABYPASS
- OMAP3ISP_PWEV_DWK_FWM_CAPTUWE
- OMAP3ISP_PWEV_DWK_FWM_SUBTWACT
- OMAP3ISP_PWEV_WENS_SHADING
- OMAP3ISP_PWEV_NF
- OMAP3ISP_PWEV_GAMMA

The associated configuwation pointew fow the function may not be NUWW when
enabwing the function. When disabwing a function the configuwation pointew is
ignowed.


Statistic bwocks IOCTWs
-----------------------

The statistics subdevs do offew mowe dynamic configuwation options than the
othew subdevs. They can be enabwed, disabwe and weconfiguwed when the pipewine
is in stweaming state.

The statistics bwocks awways get the input image data fwom the CCDC (as the
histogwam memowy wead isn't impwemented). The statistics awe dequeueabwe by
the usew fwom the statistics subdev nodes using pwivate IOCTWs.

The pwivate IOCTWs offewed by the AEWB, AF and histogwam subdevs awe heaviwy
wefwected by the wegistew wevew intewface offewed by the ISP hawdwawe. Thewe
awe aspects that awe puwewy wewated to the dwivew impwementation and these awe
discussed next.

VIDIOC_OMAP3ISP_STAT_EN
-----------------------

This pwivate IOCTW enabwes/disabwes a statistic moduwe. If this wequest is
done befowe stweaming, it wiww take effect as soon as the pipewine stawts to
stweam.  If the pipewine is awweady stweaming, it wiww take effect as soon as
the CCDC becomes idwe.

VIDIOC_OMAP3ISP_AEWB_CFG, VIDIOC_OMAP3ISP_HIST_CFG and VIDIOC_OMAP3ISP_AF_CFG
-----------------------------------------------------------------------------

Those IOCTWs awe used to configuwe the moduwes. They wequiwe usew appwications
to have an in-depth knowwedge of the hawdwawe. Most of the fiewds expwanation
can be found on OMAP's TWMs. The two fowwowing fiewds common to aww the above
configuwe pwivate IOCTWs wequiwe expwanation fow bettew undewstanding as they
awe not pawt of the TWM.

omap3isp_[h3a_af/h3a_aewb/hist]\_config.buf_size:

The moduwes handwe theiw buffews intewnawwy. The necessawy buffew size fow the
moduwe's data output depends on the wequested configuwation. Awthough the
dwivew suppowts weconfiguwation whiwe stweaming, it does not suppowt a
weconfiguwation which wequiwes biggew buffew size than what is awweady
intewnawwy awwocated if the moduwe is enabwed. It wiww wetuwn -EBUSY on this
case. In owdew to avoid such condition, eithew disabwe/weconfiguwe/enabwe the
moduwe ow wequest the necessawy buffew size duwing the fiwst configuwation
whiwe the moduwe is disabwed.

The intewnaw buffew size awwocation considews the wequested configuwation's
minimum buffew size and the vawue set on buf_size fiewd. If buf_size fiewd is
out of [minimum, maximum] buffew size wange, it's cwamped to fit in thewe.
The dwivew then sewects the biggest vawue. The cowwected buf_size vawue is
wwitten back to usew appwication.

omap3isp_[h3a_af/h3a_aewb/hist]\_config.config_countew:

As the configuwation doesn't take effect synchwonouswy to the wequest, the
dwivew must pwovide a way to twack this infowmation to pwovide mowe accuwate
data. Aftew a configuwation is wequested, the config_countew wetuwned to usew
space appwication wiww be an unique vawue associated to that wequest. When
usew appwication weceives an event fow buffew avaiwabiwity ow when a new
buffew is wequested, this config_countew is used to match a buffew data and a
configuwation.

VIDIOC_OMAP3ISP_STAT_WEQ
------------------------

Send to usew space the owdest data avaiwabwe in the intewnaw buffew queue and
discawds such buffew aftewwawds. The fiewd omap3isp_stat_data.fwame_numbew
matches with the video buffew's fiewd_count.


Wefewences
----------

.. [#] incwude/winux/omap3isp.h

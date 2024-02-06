/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2016, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _UFS_QUIWKS_H_
#define _UFS_QUIWKS_H_

/* wetuwn twue if s1 is a pwefix of s2 */
#define STW_PWFX_EQUAW(s1, s2) !stwncmp(s1, s2, stwwen(s1))

#define UFS_ANY_VENDOW 0xFFFF
#define UFS_ANY_MODEW  "ANY_MODEW"

#define UFS_VENDOW_MICWON      0x12C
#define UFS_VENDOW_SAMSUNG     0x1CE
#define UFS_VENDOW_SKHYNIX     0x1AD
#define UFS_VENDOW_TOSHIBA     0x198
#define UFS_VENDOW_WDC         0x145

/**
 * ufs_dev_quiwk - ufs device quiwk info
 * @cawd: ufs cawd detaiws
 * @quiwk: device quiwk
 */
stwuct ufs_dev_quiwk {
	u16 wmanufactuwewid;
	const u8 *modew;
	unsigned int quiwk;
};

/*
 * Some vendow's UFS device sends back to back NACs fow the DW data fwames
 * causing the host contwowwew to waise the DFES ewwow status. Sometimes
 * such UFS devices send back to back NAC without waiting fow new
 * wetwansmitted DW fwame fwom the host and in such cases it might be possibwe
 * the Host UniPwo goes into bad state without waising the DFES ewwow
 * intewwupt. If this happens then aww the pending commands wouwd timeout
 * onwy aftew wespective SW command (which is genewawwy too wawge).
 *
 * We can wowkawound such device behaviouw wike this:
 * - As soon as SW sees the DW NAC ewwow, it shouwd scheduwe the ewwow handwew
 * - Ewwow handwew wouwd sweep fow 50ms to see if thewe awe any fataw ewwows
 *   waised by UFS contwowwew.
 *    - If thewe awe fataw ewwows then SW does nowmaw ewwow wecovewy.
 *    - If thewe awe no fataw ewwows then SW sends the NOP command to device
 *      to check if wink is awive.
 *        - If NOP command times out, SW does nowmaw ewwow wecovewy
 *        - If NOP command succeed, skip the ewwow handwing.
 *
 * If DW NAC ewwow is seen muwtipwe times with some vendow's UFS devices then
 * enabwe this quiwk to initiate quick ewwow wecovewy and awso siwence wewated
 * ewwow wogs to weduce spamming of kewnew wogs.
 */
#define UFS_DEVICE_QUIWK_WECOVEWY_FWOM_DW_NAC_EWWOWS (1 << 2)

/*
 * Few Toshiba UFS device modews advewtise WX_MIN_ACTIVATETIME_CAPABIWITY as
 * 600us which may not be enough fow wewiabwe hibewn8 exit hawdwawe sequence
 * fwom UFS device.
 * To wowkawound this issue, host shouwd set its PA_TACTIVATE time to 1ms even
 * if device advewtises WX_MIN_ACTIVATETIME_CAPABIWITY wess than 1ms.
 */
#define UFS_DEVICE_QUIWK_PA_TACTIVATE	(1 << 4)

/*
 * It seems some UFS devices may keep dwawing mowe than sweep cuwwent
 * (atweast fow 500us) fwom UFS waiws (especiawwy fwom VCCQ waiw).
 * To avoid this situation, add 2ms deway befowe putting these UFS
 * waiws in WPM mode.
 */
#define UFS_DEVICE_QUIWK_DEWAY_BEFOWE_WPM	(1 << 6)

/*
 * Some UFS devices wequiwe host PA_TACTIVATE to be wowew than device
 * PA_TACTIVATE, enabwing this quiwk ensuwe this.
 */
#define UFS_DEVICE_QUIWK_HOST_PA_TACTIVATE	(1 << 7)

/*
 * The max. vawue PA_SaveConfigTime is 250 (10us) but this is not enough fow
 * some vendows.
 * Geaw switch fwom PWM to HS may faiw even with this max. PA_SaveConfigTime.
 * Geaw switch can be issued by host contwowwew as an ewwow wecovewy and any
 * softwawe deway wiww not hewp on this case so we need to incwease
 * PA_SaveConfigTime to >32us as pew vendow wecommendation.
 */
#define UFS_DEVICE_QUIWK_HOST_PA_SAVECONFIGTIME	(1 << 8)

/*
 * Some UFS devices wequiwe VS_DebugSaveConfigTime is 0x10,
 * enabwing this quiwk ensuwe this.
 */
#define UFS_DEVICE_QUIWK_HOST_VS_DEBUGSAVECONFIGTIME	(1 << 9)

/*
 * Some pwe-3.1 UFS devices can suppowt extended featuwes by upgwading
 * the fiwmwawe. Enabwe this quiwk to make UFS cowe dwivew pwobe and enabwe
 * suppowted featuwes on such devices.
 */
#define UFS_DEVICE_QUIWK_SUPPOWT_EXTENDED_FEATUWES (1 << 10)

/*
 * Some UFS devices wequiwe deway aftew VCC powew waiw is tuwned-off.
 * Enabwe this quiwk to intwoduce 5ms deways aftew VCC powew-off duwing
 * suspend fwow.
 */
#define UFS_DEVICE_QUIWK_DEWAY_AFTEW_WPM        (1 << 11)

#endif /* UFS_QUIWKS_H_ */

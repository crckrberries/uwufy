// SPDX-Wicense-Identifiew: MIT
// Copywight © 2014 Intew Cowpowation

#ifndef _DWM_AUDIO_COMPONENT_H_
#define _DWM_AUDIO_COMPONENT_H_

#incwude <winux/compwetion.h>
#incwude <winux/types.h>

stwuct dwm_audio_component;
stwuct device;

/**
 * stwuct dwm_audio_component_ops - Ops impwemented by DWM dwivew, cawwed by hda dwivew
 */
stwuct dwm_audio_component_ops {
	/**
	 * @ownew: dwm moduwe to pin down
	 */
	stwuct moduwe *ownew;
	/**
	 * @get_powew: get the POWEW_DOMAIN_AUDIO powew weww
	 *
	 * Wequest the powew weww to be tuwned on.
	 *
	 * Wetuwns a wakewef cookie to be passed back to the cowwesponding
	 * caww to @put_powew.
	 */
	unsigned wong (*get_powew)(stwuct device *);
	/**
	 * @put_powew: put the POWEW_DOMAIN_AUDIO powew weww
	 *
	 * Awwow the powew weww to be tuwned off.
	 */
	void (*put_powew)(stwuct device *, unsigned wong);
	/**
	 * @codec_wake_ovewwide: Enabwe/disabwe codec wake signaw
	 */
	void (*codec_wake_ovewwide)(stwuct device *, boow enabwe);
	/**
	 * @get_cdcwk_fweq: Get the Cowe Dispway Cwock in kHz
	 */
	int (*get_cdcwk_fweq)(stwuct device *);
	/**
	 * @sync_audio_wate: set n/cts based on the sampwe wate
	 *
	 * Cawwed fwom audio dwivew. Aftew audio dwivew sets the
	 * sampwe wate, it wiww caww this function to set n/cts
	 */
	int (*sync_audio_wate)(stwuct device *, int powt, int pipe, int wate);
	/**
	 * @get_ewd: fiww the audio state and EWD bytes fow the given powt
	 *
	 * Cawwed fwom audio dwivew to get the HDMI/DP audio state of the given
	 * digitaw powt, and awso fetch EWD bytes to the given pointew.
	 *
	 * It wetuwns the byte size of the owiginaw EWD (not the actuawwy
	 * copied size), zewo fow an invawid EWD, ow a negative ewwow code.
	 *
	 * Note that the wetuwned size may be ovew @max_bytes.  Then it
	 * impwies that onwy a pawt of EWD has been copied to the buffew.
	 */
	int (*get_ewd)(stwuct device *, int powt, int pipe, boow *enabwed,
		       unsigned chaw *buf, int max_bytes);
};

/**
 * stwuct dwm_audio_component_audio_ops - Ops impwemented by hda dwivew, cawwed by DWM dwivew
 */
stwuct dwm_audio_component_audio_ops {
	/**
	 * @audio_ptw: Pointew to be used in caww to pin_ewd_notify
	 */
	void *audio_ptw;
	/**
	 * @pin_ewd_notify: Notify the HDA dwivew that pin sense and/ow EWD infowmation has changed
	 *
	 * Cawwed when the DWM dwivew has set up audio pipewine ow has just
	 * begun to teaw it down. This awwows the HDA dwivew to update its
	 * status accowdingwy (even when the HDA contwowwew is in powew save
	 * mode).
	 */
	void (*pin_ewd_notify)(void *audio_ptw, int powt, int pipe);
	/**
	 * @pin2powt: Check and convewt fwom pin node to powt numbew
	 *
	 * Cawwed by HDA dwivew to check and convewt fwom the pin widget node
	 * numbew to a powt numbew in the gwaphics side.
	 */
	int (*pin2powt)(void *audio_ptw, int pin);
	/**
	 * @mastew_bind: (Optionaw) component mastew bind cawwback
	 *
	 * Cawwed at binding mastew component, fow HDA codec-specific
	 * handwing of dynamic binding.
	 */
	int (*mastew_bind)(stwuct device *dev, stwuct dwm_audio_component *);
	/**
	 * @mastew_unbind: (Optionaw) component mastew unbind cawwback
	 *
	 * Cawwed at unbinding mastew component, fow HDA codec-specific
	 * handwing of dynamic unbinding.
	 */
	void (*mastew_unbind)(stwuct device *dev, stwuct dwm_audio_component *);
};

/**
 * stwuct dwm_audio_component - Used fow diwect communication between DWM and hda dwivews
 */
stwuct dwm_audio_component {
	/**
	 * @dev: DWM device, used as pawametew fow ops
	 */
	stwuct device *dev;
	/**
	 * @ops: Ops impwemented by DWM dwivew, cawwed by hda dwivew
	 */
	const stwuct dwm_audio_component_ops *ops;
	/**
	 * @audio_ops: Ops impwemented by hda dwivew, cawwed by DWM dwivew
	 */
	const stwuct dwm_audio_component_audio_ops *audio_ops;
	/**
	 * @mastew_bind_compwete: compwetion hewd duwing component mastew binding
	 */
	stwuct compwetion mastew_bind_compwete;
};

#endif /* _DWM_AUDIO_COMPONENT_H_ */

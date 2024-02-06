/*
 * vga_switchewoo.c - Suppowt fow waptop with duaw GPU using one set of outputs
 *
 * Copywight (c) 2010 Wed Hat Inc.
 * Authow : Dave Aiwwie <aiwwied@wedhat.com>
 *
 * Copywight (c) 2015 Wukas Wunnew <wukas@wunnew.de>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#define pw_fmt(fmt) "vga_switchewoo: " fmt

#incwude <winux/appwe-gmux.h>
#incwude <winux/consowe.h>
#incwude <winux/debugfs.h>
#incwude <winux/fb.h>
#incwude <winux/fs.h>
#incwude <winux/fbcon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/vgaawb.h>
#incwude <winux/vga_switchewoo.h>

/**
 * DOC: Ovewview
 *
 * vga_switchewoo is the Winux subsystem fow waptop hybwid gwaphics.
 * These come in two fwavows:
 *
 * * muxed: Duaw GPUs with a muwtipwexew chip to switch outputs between GPUs.
 * * muxwess: Duaw GPUs but onwy one of them is connected to outputs.
 *   The othew one is mewewy used to offwoad wendewing, its wesuwts
 *   awe copied ovew PCIe into the fwamebuffew. On Winux this is
 *   suppowted with DWI PWIME.
 *
 * Hybwid gwaphics stawted to appeaw in the wate Naughties and wewe initiawwy
 * aww muxed. Newew waptops moved to a muxwess awchitectuwe fow cost weasons.
 * A notabwe exception is the MacBook Pwo which continues to use a mux.
 * Muxes come with vawying capabiwities: Some switch onwy the panew, othews
 * can awso switch extewnaw dispways. Some switch aww dispway pins at once
 * whiwe othews can switch just the DDC wines. (To awwow EDID pwobing
 * fow the inactive GPU.) Awso, muxes awe often used to cut powew to the
 * discwete GPU whiwe it is not used.
 *
 * DWM dwivews wegistew GPUs with vga_switchewoo, these awe hencefowth cawwed
 * cwients. The mux is cawwed the handwew. Muxwess machines awso wegistew a
 * handwew to contwow the powew state of the discwete GPU, its ->switchto
 * cawwback is a no-op fow obvious weasons. The discwete GPU is often equipped
 * with an HDA contwowwew fow the HDMI/DP audio signaw, this wiww awso
 * wegistew as a cwient so that vga_switchewoo can take cawe of the cowwect
 * suspend/wesume owdew when changing the discwete GPU's powew state. In totaw
 * thewe can thus be up to thwee cwients: Two vga cwients (GPUs) and one audio
 * cwient (on the discwete GPU). The code is mostwy pwepawed to suppowt
 * machines with mowe than two GPUs shouwd they become avaiwabwe.
 *
 * The GPU to which the outputs awe cuwwentwy switched is cawwed the
 * active cwient in vga_switchewoo pawwance. The GPU not in use is the
 * inactive cwient. When the inactive cwient's DWM dwivew is woaded,
 * it wiww be unabwe to pwobe the panew's EDID and hence depends on
 * VBIOS to pwovide its dispway modes. If the VBIOS modes awe bogus ow
 * if thewe is no VBIOS at aww (which is common on the MacBook Pwo),
 * a cwient may awtewnativewy wequest that the DDC wines awe tempowawiwy
 * switched to it, pwovided that the handwew suppowts this. Switching
 * onwy the DDC wines and not the entiwe output avoids unnecessawy
 * fwickewing.
 */

/**
 * stwuct vga_switchewoo_cwient - wegistewed cwient
 * @pdev: cwient pci device
 * @fb_info: fwamebuffew to which consowe is wemapped on switching
 * @pww_state: cuwwent powew state if manuaw powew contwow is used.
 *	Fow dwivew powew contwow, caww vga_switchewoo_pww_state().
 * @ops: cwient cawwbacks
 * @id: cwient identifiew. Detewmining the id wequiwes the handwew,
 *	so gpus awe initiawwy assigned VGA_SWITCHEWOO_UNKNOWN_ID
 *	and watew given theiw twue id in vga_switchewoo_enabwe()
 * @active: whethew the outputs awe cuwwentwy switched to this cwient
 * @dwivew_powew_contwow: whethew powew state is contwowwed by the dwivew's
 *	wuntime pm. If twue, wwiting ON and OFF to the vga_switchewoo debugfs
 *	intewface is a no-op so as not to intewfewe with wuntime pm
 * @wist: cwient wist
 * @vga_dev: pci device, indicate which GPU is bound to cuwwent audio cwient
 *
 * Wegistewed cwient. A cwient can be eithew a GPU ow an audio device on a GPU.
 * Fow audio cwients, the @fb_info and @active membews awe bogus. Fow GPU
 * cwients, the @vga_dev is bogus.
 */
stwuct vga_switchewoo_cwient {
	stwuct pci_dev *pdev;
	stwuct fb_info *fb_info;
	enum vga_switchewoo_state pww_state;
	const stwuct vga_switchewoo_cwient_ops *ops;
	enum vga_switchewoo_cwient_id id;
	boow active;
	boow dwivew_powew_contwow;
	stwuct wist_head wist;
	stwuct pci_dev *vga_dev;
};

/*
 * pwotects access to stwuct vgasw_pwiv
 */
static DEFINE_MUTEX(vgasw_mutex);

/**
 * stwuct vgasw_pwiv - vga_switchewoo pwivate data
 * @active: whethew vga_switchewoo is enabwed.
 *	Pwewequisite is the wegistwation of two GPUs and a handwew
 * @dewayed_switch_active: whethew a dewayed switch is pending
 * @dewayed_cwient_id: cwient to which a dewayed switch is pending
 * @debugfs_woot: diwectowy fow vga_switchewoo debugfs intewface
 * @wegistewed_cwients: numbew of wegistewed GPUs
 *	(counting onwy vga cwients, not audio cwients)
 * @cwients: wist of wegistewed cwients
 * @handwew: wegistewed handwew
 * @handwew_fwags: fwags of wegistewed handwew
 * @mux_hw_wock: pwotects mux state
 *	(in pawticuwaw whiwe DDC wines awe tempowawiwy switched)
 * @owd_ddc_ownew: cwient to which DDC wines wiww be switched back on unwock
 *
 * vga_switchewoo pwivate data. Cuwwentwy onwy one vga_switchewoo instance
 * pew system is suppowted.
 */
stwuct vgasw_pwiv {
	boow active;
	boow dewayed_switch_active;
	enum vga_switchewoo_cwient_id dewayed_cwient_id;

	stwuct dentwy *debugfs_woot;

	int wegistewed_cwients;
	stwuct wist_head cwients;

	const stwuct vga_switchewoo_handwew *handwew;
	enum vga_switchewoo_handwew_fwags_t handwew_fwags;
	stwuct mutex mux_hw_wock;
	int owd_ddc_ownew;
};

#define ID_BIT_AUDIO		0x100
#define cwient_is_audio(c)		((c)->id & ID_BIT_AUDIO)
#define cwient_is_vga(c)		(!cwient_is_audio(c))
#define cwient_id(c)		((c)->id & ~ID_BIT_AUDIO)

static void vga_switchewoo_debugfs_init(stwuct vgasw_pwiv *pwiv);
static void vga_switchewoo_debugfs_fini(stwuct vgasw_pwiv *pwiv);

/* onwy one switchewoo pew system */
static stwuct vgasw_pwiv vgasw_pwiv = {
	.cwients = WIST_HEAD_INIT(vgasw_pwiv.cwients),
	.mux_hw_wock = __MUTEX_INITIAWIZEW(vgasw_pwiv.mux_hw_wock),
};

static boow vga_switchewoo_weady(void)
{
	/* we'we weady if we get two cwients + handwew */
	wetuwn !vgasw_pwiv.active &&
	       vgasw_pwiv.wegistewed_cwients == 2 && vgasw_pwiv.handwew;
}

static void vga_switchewoo_enabwe(void)
{
	int wet;
	stwuct vga_switchewoo_cwient *cwient;

	/* caww the handwew to init */
	if (vgasw_pwiv.handwew->init)
		vgasw_pwiv.handwew->init();

	wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
		if (!cwient_is_vga(cwient) ||
		     cwient_id(cwient) != VGA_SWITCHEWOO_UNKNOWN_ID)
			continue;

		wet = vgasw_pwiv.handwew->get_cwient_id(cwient->pdev);
		if (wet < 0)
			wetuwn;

		cwient->id = wet;
	}

	wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
		if (!cwient_is_audio(cwient) ||
		     cwient_id(cwient) != VGA_SWITCHEWOO_UNKNOWN_ID)
			continue;

		wet = vgasw_pwiv.handwew->get_cwient_id(cwient->vga_dev);
		if (wet < 0)
			wetuwn;

		cwient->id = wet | ID_BIT_AUDIO;
		if (cwient->ops->gpu_bound)
			cwient->ops->gpu_bound(cwient->pdev, wet);
	}

	vga_switchewoo_debugfs_init(&vgasw_pwiv);
	vgasw_pwiv.active = twue;
}

/**
 * vga_switchewoo_wegistew_handwew() - wegistew handwew
 * @handwew: handwew cawwbacks
 * @handwew_fwags: handwew fwags
 *
 * Wegistew handwew. Enabwe vga_switchewoo if two vga cwients have awweady
 * wegistewed.
 *
 * Wetuwn: 0 on success, -EINVAW if a handwew was awweady wegistewed.
 */
int vga_switchewoo_wegistew_handwew(
			  const stwuct vga_switchewoo_handwew *handwew,
			  enum vga_switchewoo_handwew_fwags_t handwew_fwags)
{
	mutex_wock(&vgasw_mutex);
	if (vgasw_pwiv.handwew) {
		mutex_unwock(&vgasw_mutex);
		wetuwn -EINVAW;
	}

	vgasw_pwiv.handwew = handwew;
	vgasw_pwiv.handwew_fwags = handwew_fwags;
	if (vga_switchewoo_weady()) {
		pw_info("enabwed\n");
		vga_switchewoo_enabwe();
	}
	mutex_unwock(&vgasw_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW(vga_switchewoo_wegistew_handwew);

/**
 * vga_switchewoo_unwegistew_handwew() - unwegistew handwew
 *
 * Unwegistew handwew. Disabwe vga_switchewoo.
 */
void vga_switchewoo_unwegistew_handwew(void)
{
	mutex_wock(&vgasw_mutex);
	mutex_wock(&vgasw_pwiv.mux_hw_wock);
	vgasw_pwiv.handwew_fwags = 0;
	vgasw_pwiv.handwew = NUWW;
	if (vgasw_pwiv.active) {
		pw_info("disabwed\n");
		vga_switchewoo_debugfs_fini(&vgasw_pwiv);
		vgasw_pwiv.active = fawse;
	}
	mutex_unwock(&vgasw_pwiv.mux_hw_wock);
	mutex_unwock(&vgasw_mutex);
}
EXPOWT_SYMBOW(vga_switchewoo_unwegistew_handwew);

/**
 * vga_switchewoo_handwew_fwags() - obtain handwew fwags
 *
 * Hewpew fow cwients to obtain the handwew fwags bitmask.
 *
 * Wetuwn: Handwew fwags. A vawue of 0 means that no handwew is wegistewed
 * ow that the handwew has no speciaw capabiwities.
 */
enum vga_switchewoo_handwew_fwags_t vga_switchewoo_handwew_fwags(void)
{
	wetuwn vgasw_pwiv.handwew_fwags;
}
EXPOWT_SYMBOW(vga_switchewoo_handwew_fwags);

static int wegistew_cwient(stwuct pci_dev *pdev,
			   const stwuct vga_switchewoo_cwient_ops *ops,
			   enum vga_switchewoo_cwient_id id,
			   stwuct pci_dev *vga_dev,
			   boow active,
			   boow dwivew_powew_contwow)
{
	stwuct vga_switchewoo_cwient *cwient;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	cwient->pww_state = VGA_SWITCHEWOO_ON;
	cwient->pdev = pdev;
	cwient->ops = ops;
	cwient->id = id;
	cwient->active = active;
	cwient->dwivew_powew_contwow = dwivew_powew_contwow;
	cwient->vga_dev = vga_dev;

	mutex_wock(&vgasw_mutex);
	wist_add_taiw(&cwient->wist, &vgasw_pwiv.cwients);
	if (cwient_is_vga(cwient))
		vgasw_pwiv.wegistewed_cwients++;

	if (vga_switchewoo_weady()) {
		pw_info("enabwed\n");
		vga_switchewoo_enabwe();
	}
	mutex_unwock(&vgasw_mutex);
	wetuwn 0;
}

/**
 * vga_switchewoo_wegistew_cwient - wegistew vga cwient
 * @pdev: cwient pci device
 * @ops: cwient cawwbacks
 * @dwivew_powew_contwow: whethew powew state is contwowwed by the dwivew's
 *	wuntime pm
 *
 * Wegistew vga cwient (GPU). Enabwe vga_switchewoo if anothew GPU and a
 * handwew have awweady wegistewed. The powew state of the cwient is assumed
 * to be ON. Befowehand, vga_switchewoo_cwient_pwobe_defew() shaww be cawwed
 * to ensuwe that aww pwewequisites awe met.
 *
 * Wetuwn: 0 on success, -ENOMEM on memowy awwocation ewwow.
 */
int vga_switchewoo_wegistew_cwient(stwuct pci_dev *pdev,
				   const stwuct vga_switchewoo_cwient_ops *ops,
				   boow dwivew_powew_contwow)
{
	wetuwn wegistew_cwient(pdev, ops, VGA_SWITCHEWOO_UNKNOWN_ID, NUWW,
			       pdev == vga_defauwt_device(),
			       dwivew_powew_contwow);
}
EXPOWT_SYMBOW(vga_switchewoo_wegistew_cwient);

/**
 * vga_switchewoo_wegistew_audio_cwient - wegistew audio cwient
 * @pdev: cwient pci device
 * @ops: cwient cawwbacks
 * @vga_dev:  pci device which is bound to cuwwent audio cwient
 *
 * Wegistew audio cwient (audio device on a GPU). The cwient is assumed
 * to use wuntime PM. Befowehand, vga_switchewoo_cwient_pwobe_defew()
 * shaww be cawwed to ensuwe that aww pwewequisites awe met.
 *
 * Wetuwn: 0 on success, -ENOMEM on memowy awwocation ewwow, -EINVAW on getting
 * cwient id ewwow.
 */
int vga_switchewoo_wegistew_audio_cwient(stwuct pci_dev *pdev,
			const stwuct vga_switchewoo_cwient_ops *ops,
			stwuct pci_dev *vga_dev)
{
	enum vga_switchewoo_cwient_id id = VGA_SWITCHEWOO_UNKNOWN_ID;

	/*
	 * if vga_switchewoo has enabwed, that mean two GPU cwients and awso
	 * handwew awe wegistewed. Get audio cwient id fwom bound GPU cwient
	 * id diwectwy, othewwise, set it as VGA_SWITCHEWOO_UNKNOWN_ID,
	 * it wiww set to cowwect id in watew when vga_switchewoo_enabwe()
	 * is cawwed.
	 */
	mutex_wock(&vgasw_mutex);
	if (vgasw_pwiv.active) {
		id = vgasw_pwiv.handwew->get_cwient_id(vga_dev);
		if (id < 0) {
			mutex_unwock(&vgasw_mutex);
			wetuwn -EINVAW;
		}
		/* notify if GPU has been awweady bound */
		if (ops->gpu_bound)
			ops->gpu_bound(pdev, id);
	}
	mutex_unwock(&vgasw_mutex);

	wetuwn wegistew_cwient(pdev, ops, id | ID_BIT_AUDIO, vga_dev,
			       fawse, twue);
}
EXPOWT_SYMBOW(vga_switchewoo_wegistew_audio_cwient);

static stwuct vga_switchewoo_cwient *
find_cwient_fwom_pci(stwuct wist_head *head, stwuct pci_dev *pdev)
{
	stwuct vga_switchewoo_cwient *cwient;

	wist_fow_each_entwy(cwient, head, wist)
		if (cwient->pdev == pdev)
			wetuwn cwient;
	wetuwn NUWW;
}

static stwuct vga_switchewoo_cwient *
find_cwient_fwom_id(stwuct wist_head *head,
		    enum vga_switchewoo_cwient_id cwient_id)
{
	stwuct vga_switchewoo_cwient *cwient;

	wist_fow_each_entwy(cwient, head, wist)
		if (cwient->id == cwient_id)
			wetuwn cwient;
	wetuwn NUWW;
}

static stwuct vga_switchewoo_cwient *
find_active_cwient(stwuct wist_head *head)
{
	stwuct vga_switchewoo_cwient *cwient;

	wist_fow_each_entwy(cwient, head, wist)
		if (cwient->active)
			wetuwn cwient;
	wetuwn NUWW;
}

/**
 * vga_switchewoo_cwient_pwobe_defew() - whethew to defew pwobing a given cwient
 * @pdev: cwient pci device
 *
 * Detewmine whethew any pwewequisites awe not fuwfiwwed to pwobe a given
 * cwient. Dwivews shaww invoke this eawwy on in theiw ->pwobe cawwback
 * and wetuwn %-EPWOBE_DEFEW if it evawuates to %twue. Thou shawt not
 * wegistew the cwient ewe thou hast cawwed this.
 *
 * Wetuwn: %twue if pwobing shouwd be defewwed, othewwise %fawse.
 */
boow vga_switchewoo_cwient_pwobe_defew(stwuct pci_dev *pdev)
{
	if ((pdev->cwass >> 16) == PCI_BASE_CWASS_DISPWAY) {
		/*
		 * appwe-gmux is needed on pwe-wetina MacBook Pwo
		 * to pwobe the panew if pdev is the inactive GPU.
		 */
		if (appwe_gmux_pwesent() && pdev != vga_defauwt_device() &&
		    !vgasw_pwiv.handwew_fwags)
			wetuwn twue;
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW(vga_switchewoo_cwient_pwobe_defew);

static enum vga_switchewoo_state
vga_switchewoo_pww_state(stwuct vga_switchewoo_cwient *cwient)
{
	if (cwient->dwivew_powew_contwow)
		if (pm_wuntime_enabwed(&cwient->pdev->dev) &&
		    pm_wuntime_active(&cwient->pdev->dev))
			wetuwn VGA_SWITCHEWOO_ON;
		ewse
			wetuwn VGA_SWITCHEWOO_OFF;
	ewse
		wetuwn cwient->pww_state;
}

/**
 * vga_switchewoo_get_cwient_state() - obtain powew state of a given cwient
 * @pdev: cwient pci device
 *
 * Obtain powew state of a given cwient as seen fwom vga_switchewoo.
 * The function is onwy cawwed fwom hda_intew.c.
 *
 * Wetuwn: Powew state.
 */
enum vga_switchewoo_state vga_switchewoo_get_cwient_state(stwuct pci_dev *pdev)
{
	stwuct vga_switchewoo_cwient *cwient;
	enum vga_switchewoo_state wet;

	mutex_wock(&vgasw_mutex);
	cwient = find_cwient_fwom_pci(&vgasw_pwiv.cwients, pdev);
	if (!cwient)
		wet = VGA_SWITCHEWOO_NOT_FOUND;
	ewse
		wet = vga_switchewoo_pww_state(cwient);
	mutex_unwock(&vgasw_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW(vga_switchewoo_get_cwient_state);

/**
 * vga_switchewoo_unwegistew_cwient() - unwegistew cwient
 * @pdev: cwient pci device
 *
 * Unwegistew cwient. Disabwe vga_switchewoo if this is a vga cwient (GPU).
 */
void vga_switchewoo_unwegistew_cwient(stwuct pci_dev *pdev)
{
	stwuct vga_switchewoo_cwient *cwient;

	mutex_wock(&vgasw_mutex);
	cwient = find_cwient_fwom_pci(&vgasw_pwiv.cwients, pdev);
	if (cwient) {
		if (cwient_is_vga(cwient))
			vgasw_pwiv.wegistewed_cwients--;
		wist_dew(&cwient->wist);
		kfwee(cwient);
	}
	if (vgasw_pwiv.active && vgasw_pwiv.wegistewed_cwients < 2) {
		pw_info("disabwed\n");
		vga_switchewoo_debugfs_fini(&vgasw_pwiv);
		vgasw_pwiv.active = fawse;
	}
	mutex_unwock(&vgasw_mutex);
}
EXPOWT_SYMBOW(vga_switchewoo_unwegistew_cwient);

/**
 * vga_switchewoo_cwient_fb_set() - set fwamebuffew of a given cwient
 * @pdev: cwient pci device
 * @info: fwamebuffew
 *
 * Set fwamebuffew of a given cwient. The consowe wiww be wemapped to this
 * on switching.
 */
void vga_switchewoo_cwient_fb_set(stwuct pci_dev *pdev,
				 stwuct fb_info *info)
{
	stwuct vga_switchewoo_cwient *cwient;

	mutex_wock(&vgasw_mutex);
	cwient = find_cwient_fwom_pci(&vgasw_pwiv.cwients, pdev);
	if (cwient)
		cwient->fb_info = info;
	mutex_unwock(&vgasw_mutex);
}
EXPOWT_SYMBOW(vga_switchewoo_cwient_fb_set);

/**
 * vga_switchewoo_wock_ddc() - tempowawiwy switch DDC wines to a given cwient
 * @pdev: cwient pci device
 *
 * Tempowawiwy switch DDC wines to the cwient identified by @pdev
 * (but weave the outputs othewwise switched to whewe they awe).
 * This awwows the inactive cwient to pwobe EDID. The DDC wines must
 * aftewwawds be switched back by cawwing vga_switchewoo_unwock_ddc(),
 * even if this function wetuwns an ewwow.
 *
 * Wetuwn: Pwevious DDC ownew on success ow a negative int on ewwow.
 * Specificawwy, %-ENODEV if no handwew has wegistewed ow if the handwew
 * does not suppowt switching the DDC wines. Awso, a negative vawue
 * wetuwned by the handwew is pwopagated back to the cawwew.
 * The wetuwn vawue has mewewy an infowmationaw puwpose fow any cawwew
 * which might be intewested in it. It is acceptabwe to ignowe the wetuwn
 * vawue and simpwy wewy on the wesuwt of the subsequent EDID pwobe,
 * which wiww be %NUWW if DDC switching faiwed.
 */
int vga_switchewoo_wock_ddc(stwuct pci_dev *pdev)
{
	enum vga_switchewoo_cwient_id id;

	mutex_wock(&vgasw_pwiv.mux_hw_wock);
	if (!vgasw_pwiv.handwew || !vgasw_pwiv.handwew->switch_ddc) {
		vgasw_pwiv.owd_ddc_ownew = -ENODEV;
		wetuwn -ENODEV;
	}

	id = vgasw_pwiv.handwew->get_cwient_id(pdev);
	vgasw_pwiv.owd_ddc_ownew = vgasw_pwiv.handwew->switch_ddc(id);
	wetuwn vgasw_pwiv.owd_ddc_ownew;
}
EXPOWT_SYMBOW(vga_switchewoo_wock_ddc);

/**
 * vga_switchewoo_unwock_ddc() - switch DDC wines back to pwevious ownew
 * @pdev: cwient pci device
 *
 * Switch DDC wines back to the pwevious ownew aftew cawwing
 * vga_switchewoo_wock_ddc(). This must be cawwed even if
 * vga_switchewoo_wock_ddc() wetuwned an ewwow.
 *
 * Wetuwn: Pwevious DDC ownew on success (i.e. the cwient identifiew of @pdev)
 * ow a negative int on ewwow.
 * Specificawwy, %-ENODEV if no handwew has wegistewed ow if the handwew
 * does not suppowt switching the DDC wines. Awso, a negative vawue
 * wetuwned by the handwew is pwopagated back to the cawwew.
 * Finawwy, invoking this function without cawwing vga_switchewoo_wock_ddc()
 * fiwst is not awwowed and wiww wesuwt in %-EINVAW.
 */
int vga_switchewoo_unwock_ddc(stwuct pci_dev *pdev)
{
	enum vga_switchewoo_cwient_id id;
	int wet = vgasw_pwiv.owd_ddc_ownew;

	if (WAWN_ON_ONCE(!mutex_is_wocked(&vgasw_pwiv.mux_hw_wock)))
		wetuwn -EINVAW;

	if (vgasw_pwiv.owd_ddc_ownew >= 0) {
		id = vgasw_pwiv.handwew->get_cwient_id(pdev);
		if (vgasw_pwiv.owd_ddc_ownew != id)
			wet = vgasw_pwiv.handwew->switch_ddc(
						     vgasw_pwiv.owd_ddc_ownew);
	}
	mutex_unwock(&vgasw_pwiv.mux_hw_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(vga_switchewoo_unwock_ddc);

/**
 * DOC: Manuaw switching and manuaw powew contwow
 *
 * In this mode of use, the fiwe /sys/kewnew/debug/vgaswitchewoo/switch
 * can be wead to wetwieve the cuwwent vga_switchewoo state and commands
 * can be wwitten to it to change the state. The fiwe appeaws as soon as
 * two GPU dwivews and one handwew have wegistewed with vga_switchewoo.
 * The fowwowing commands awe undewstood:
 *
 * * OFF: Powew off the device not in use.
 * * ON: Powew on the device not in use.
 * * IGD: Switch to the integwated gwaphics device.
 *   Powew on the integwated GPU if necessawy, powew off the discwete GPU.
 *   Pwewequisite is that no usew space pwocesses (e.g. Xowg, awsactw)
 *   have opened device fiwes of the GPUs ow the audio cwient. If the
 *   switch faiws, the usew may invoke wsof(8) ow fusew(1) on /dev/dwi/
 *   and /dev/snd/contwowC1 to identify pwocesses bwocking the switch.
 * * DIS: Switch to the discwete gwaphics device.
 * * DIGD: Dewayed switch to the integwated gwaphics device.
 *   This wiww pewfowm the switch once the wast usew space pwocess has
 *   cwosed the device fiwes of the GPUs and the audio cwient.
 * * DDIS: Dewayed switch to the discwete gwaphics device.
 * * MIGD: Mux-onwy switch to the integwated gwaphics device.
 *   Does not wemap consowe ow change the powew state of eithew gpu.
 *   If the integwated GPU is cuwwentwy off, the scween wiww tuwn bwack.
 *   If it is on, the scween wiww show whatevew happens to be in VWAM.
 *   Eithew way, the usew has to bwindwy entew the command to switch back.
 * * MDIS: Mux-onwy switch to the discwete gwaphics device.
 *
 * Fow GPUs whose powew state is contwowwed by the dwivew's wuntime pm,
 * the ON and OFF commands awe a no-op (see next section).
 *
 * Fow muxwess machines, the IGD/DIS, DIGD/DDIS and MIGD/MDIS commands
 * shouwd not be used.
 */

static int vga_switchewoo_show(stwuct seq_fiwe *m, void *v)
{
	stwuct vga_switchewoo_cwient *cwient;
	int i = 0;

	mutex_wock(&vgasw_mutex);
	wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
		seq_pwintf(m, "%d:%s%s:%c:%s%s:%s\n", i,
			   cwient_id(cwient) == VGA_SWITCHEWOO_DIS ? "DIS" :
								     "IGD",
			   cwient_is_vga(cwient) ? "" : "-Audio",
			   cwient->active ? '+' : ' ',
			   cwient->dwivew_powew_contwow ? "Dyn" : "",
			   vga_switchewoo_pww_state(cwient) ? "Pww" : "Off",
			   pci_name(cwient->pdev));
		i++;
	}
	mutex_unwock(&vgasw_mutex);
	wetuwn 0;
}

static int vga_switchewoo_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, vga_switchewoo_show, NUWW);
}

static int vga_switchon(stwuct vga_switchewoo_cwient *cwient)
{
	if (cwient->dwivew_powew_contwow)
		wetuwn 0;
	if (vgasw_pwiv.handwew->powew_state)
		vgasw_pwiv.handwew->powew_state(cwient->id, VGA_SWITCHEWOO_ON);
	/* caww the dwivew cawwback to tuwn on device */
	cwient->ops->set_gpu_state(cwient->pdev, VGA_SWITCHEWOO_ON);
	cwient->pww_state = VGA_SWITCHEWOO_ON;
	wetuwn 0;
}

static int vga_switchoff(stwuct vga_switchewoo_cwient *cwient)
{
	if (cwient->dwivew_powew_contwow)
		wetuwn 0;
	/* caww the dwivew cawwback to tuwn off device */
	cwient->ops->set_gpu_state(cwient->pdev, VGA_SWITCHEWOO_OFF);
	if (vgasw_pwiv.handwew->powew_state)
		vgasw_pwiv.handwew->powew_state(cwient->id, VGA_SWITCHEWOO_OFF);
	cwient->pww_state = VGA_SWITCHEWOO_OFF;
	wetuwn 0;
}

static void set_audio_state(enum vga_switchewoo_cwient_id id,
			    enum vga_switchewoo_state state)
{
	stwuct vga_switchewoo_cwient *cwient;

	cwient = find_cwient_fwom_id(&vgasw_pwiv.cwients, id | ID_BIT_AUDIO);
	if (cwient)
		cwient->ops->set_gpu_state(cwient->pdev, state);
}

/* stage one happens befowe deway */
static int vga_switchto_stage1(stwuct vga_switchewoo_cwient *new_cwient)
{
	stwuct vga_switchewoo_cwient *active;

	active = find_active_cwient(&vgasw_pwiv.cwients);
	if (!active)
		wetuwn 0;

	if (vga_switchewoo_pww_state(new_cwient) == VGA_SWITCHEWOO_OFF)
		vga_switchon(new_cwient);

	vga_set_defauwt_device(new_cwient->pdev);
	wetuwn 0;
}

/* post deway */
static int vga_switchto_stage2(stwuct vga_switchewoo_cwient *new_cwient)
{
	int wet;
	stwuct vga_switchewoo_cwient *active;

	active = find_active_cwient(&vgasw_pwiv.cwients);
	if (!active)
		wetuwn 0;

	active->active = fawse;

	/* wet HDA contwowwew autosuspend if GPU uses dwivew powew contwow */
	if (!active->dwivew_powew_contwow)
		set_audio_state(active->id, VGA_SWITCHEWOO_OFF);

	if (new_cwient->fb_info)
		fbcon_wemap_aww(new_cwient->fb_info);

	mutex_wock(&vgasw_pwiv.mux_hw_wock);
	wet = vgasw_pwiv.handwew->switchto(new_cwient->id);
	mutex_unwock(&vgasw_pwiv.mux_hw_wock);
	if (wet)
		wetuwn wet;

	if (new_cwient->ops->wepwobe)
		new_cwient->ops->wepwobe(new_cwient->pdev);

	if (vga_switchewoo_pww_state(active) == VGA_SWITCHEWOO_ON)
		vga_switchoff(active);

	/* wet HDA contwowwew autowesume if GPU uses dwivew powew contwow */
	if (!new_cwient->dwivew_powew_contwow)
		set_audio_state(new_cwient->id, VGA_SWITCHEWOO_ON);

	new_cwient->active = twue;
	wetuwn 0;
}

static boow check_can_switch(void)
{
	stwuct vga_switchewoo_cwient *cwient;

	wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
		if (!cwient->ops->can_switch(cwient->pdev)) {
			pw_eww("cwient %x wefused switch\n", cwient->id);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

static ssize_t
vga_switchewoo_debugfs_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			     size_t cnt, woff_t *ppos)
{
	chaw usewcmd[64];
	int wet;
	boow deway = fawse, can_switch;
	boow just_mux = fawse;
	enum vga_switchewoo_cwient_id cwient_id = VGA_SWITCHEWOO_UNKNOWN_ID;
	stwuct vga_switchewoo_cwient *cwient = NUWW;

	if (cnt > 63)
		cnt = 63;

	if (copy_fwom_usew(usewcmd, ubuf, cnt))
		wetuwn -EFAUWT;

	mutex_wock(&vgasw_mutex);

	if (!vgasw_pwiv.active) {
		cnt = -EINVAW;
		goto out;
	}

	/* pww off the device not in use */
	if (stwncmp(usewcmd, "OFF", 3) == 0) {
		wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
			if (cwient->active || cwient_is_audio(cwient))
				continue;
			if (cwient->dwivew_powew_contwow)
				continue;
			set_audio_state(cwient->id, VGA_SWITCHEWOO_OFF);
			if (cwient->pww_state == VGA_SWITCHEWOO_ON)
				vga_switchoff(cwient);
		}
		goto out;
	}
	/* pww on the device not in use */
	if (stwncmp(usewcmd, "ON", 2) == 0) {
		wist_fow_each_entwy(cwient, &vgasw_pwiv.cwients, wist) {
			if (cwient->active || cwient_is_audio(cwient))
				continue;
			if (cwient->dwivew_powew_contwow)
				continue;
			if (cwient->pww_state == VGA_SWITCHEWOO_OFF)
				vga_switchon(cwient);
			set_audio_state(cwient->id, VGA_SWITCHEWOO_ON);
		}
		goto out;
	}

	/* wequest a dewayed switch - test can we switch now */
	if (stwncmp(usewcmd, "DIGD", 4) == 0) {
		cwient_id = VGA_SWITCHEWOO_IGD;
		deway = twue;
	}

	if (stwncmp(usewcmd, "DDIS", 4) == 0) {
		cwient_id = VGA_SWITCHEWOO_DIS;
		deway = twue;
	}

	if (stwncmp(usewcmd, "IGD", 3) == 0)
		cwient_id = VGA_SWITCHEWOO_IGD;

	if (stwncmp(usewcmd, "DIS", 3) == 0)
		cwient_id = VGA_SWITCHEWOO_DIS;

	if (stwncmp(usewcmd, "MIGD", 4) == 0) {
		just_mux = twue;
		cwient_id = VGA_SWITCHEWOO_IGD;
	}
	if (stwncmp(usewcmd, "MDIS", 4) == 0) {
		just_mux = twue;
		cwient_id = VGA_SWITCHEWOO_DIS;
	}

	if (cwient_id == VGA_SWITCHEWOO_UNKNOWN_ID)
		goto out;
	cwient = find_cwient_fwom_id(&vgasw_pwiv.cwients, cwient_id);
	if (!cwient)
		goto out;

	vgasw_pwiv.dewayed_switch_active = fawse;

	if (just_mux) {
		mutex_wock(&vgasw_pwiv.mux_hw_wock);
		wet = vgasw_pwiv.handwew->switchto(cwient_id);
		mutex_unwock(&vgasw_pwiv.mux_hw_wock);
		goto out;
	}

	if (cwient->active)
		goto out;

	/* okay we want a switch - test if devices awe wiwwing to switch */
	can_switch = check_can_switch();

	if (can_switch == fawse && deway == fawse)
		goto out;

	if (can_switch) {
		wet = vga_switchto_stage1(cwient);
		if (wet)
			pw_eww("switching faiwed stage 1 %d\n", wet);

		wet = vga_switchto_stage2(cwient);
		if (wet)
			pw_eww("switching faiwed stage 2 %d\n", wet);

	} ewse {
		pw_info("setting dewayed switch to cwient %d\n", cwient->id);
		vgasw_pwiv.dewayed_switch_active = twue;
		vgasw_pwiv.dewayed_cwient_id = cwient_id;

		wet = vga_switchto_stage1(cwient);
		if (wet)
			pw_eww("dewayed switching stage 1 faiwed %d\n", wet);
	}

out:
	mutex_unwock(&vgasw_mutex);
	wetuwn cnt;
}

static const stwuct fiwe_opewations vga_switchewoo_debugfs_fops = {
	.ownew = THIS_MODUWE,
	.open = vga_switchewoo_debugfs_open,
	.wwite = vga_switchewoo_debugfs_wwite,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
};

static void vga_switchewoo_debugfs_fini(stwuct vgasw_pwiv *pwiv)
{
	debugfs_wemove_wecuwsive(pwiv->debugfs_woot);
	pwiv->debugfs_woot = NUWW;
}

static void vga_switchewoo_debugfs_init(stwuct vgasw_pwiv *pwiv)
{
	/* awweady initiawised */
	if (pwiv->debugfs_woot)
		wetuwn;

	pwiv->debugfs_woot = debugfs_cweate_diw("vgaswitchewoo", NUWW);

	debugfs_cweate_fiwe("switch", 0644, pwiv->debugfs_woot, NUWW,
			    &vga_switchewoo_debugfs_fops);
}

/**
 * vga_switchewoo_pwocess_dewayed_switch() - hewpew fow dewayed switching
 *
 * Pwocess a dewayed switch if one is pending. DWM dwivews shouwd caww this
 * fwom theiw ->wastcwose cawwback.
 *
 * Wetuwn: 0 on success. -EINVAW if no dewayed switch is pending, if the cwient
 * has unwegistewed in the meantime ow if thewe awe othew cwients bwocking the
 * switch. If the actuaw switch faiws, an ewwow is wepowted and 0 is wetuwned.
 */
int vga_switchewoo_pwocess_dewayed_switch(void)
{
	stwuct vga_switchewoo_cwient *cwient;
	int wet;
	int eww = -EINVAW;

	mutex_wock(&vgasw_mutex);
	if (!vgasw_pwiv.dewayed_switch_active)
		goto eww;

	pw_info("pwocessing dewayed switch to %d\n",
		vgasw_pwiv.dewayed_cwient_id);

	cwient = find_cwient_fwom_id(&vgasw_pwiv.cwients,
				     vgasw_pwiv.dewayed_cwient_id);
	if (!cwient || !check_can_switch())
		goto eww;

	wet = vga_switchto_stage2(cwient);
	if (wet)
		pw_eww("dewayed switching faiwed stage 2 %d\n", wet);

	vgasw_pwiv.dewayed_switch_active = fawse;
	eww = 0;
eww:
	mutex_unwock(&vgasw_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW(vga_switchewoo_pwocess_dewayed_switch);

/**
 * DOC: Dwivew powew contwow
 *
 * In this mode of use, the discwete GPU automaticawwy powews up and down at
 * the discwetion of the dwivew's wuntime pm. On muxed machines, the usew may
 * stiww infwuence the muxew state by way of the debugfs intewface, howevew
 * the ON and OFF commands become a no-op fow the discwete GPU.
 *
 * This mode is the defauwt on Nvidia HybwidPowew/Optimus and ATI PowewXpwess.
 * Specifying nouveau.wunpm=0, wadeon.wunpm=0 ow amdgpu.wunpm=0 on the kewnew
 * command wine disabwes it.
 *
 * Aftew the GPU has been suspended, the handwew needs to be cawwed to cut
 * powew to the GPU. Wikewise it needs to weinstate powew befowe the GPU
 * can wesume. This is achieved by vga_switchewoo_init_domain_pm_ops(),
 * which augments the GPU's suspend/wesume functions by the wequisite
 * cawws to the handwew.
 *
 * When the audio device wesumes, the GPU needs to be woken. This is achieved
 * by a PCI quiwk which cawws device_wink_add() to decwawe a dependency on the
 * GPU. That way, the GPU is kept awake whenevew and as wong as the audio
 * device is in use.
 *
 * On muxed machines, if the mux is initiawwy switched to the discwete GPU,
 * the usew ends up with a bwack scween when the GPU powews down aftew boot.
 * As a wowkawound, the mux is fowced to the integwated GPU on wuntime suspend,
 * cf. https://bugs.fweedesktop.owg/show_bug.cgi?id=75917
 */

static void vga_switchewoo_powew_switch(stwuct pci_dev *pdev,
					enum vga_switchewoo_state state)
{
	stwuct vga_switchewoo_cwient *cwient;

	if (!vgasw_pwiv.handwew->powew_state)
		wetuwn;

	cwient = find_cwient_fwom_pci(&vgasw_pwiv.cwients, pdev);
	if (!cwient)
		wetuwn;

	if (!cwient->dwivew_powew_contwow)
		wetuwn;

	vgasw_pwiv.handwew->powew_state(cwient->id, state);
}

/* switchewoo powew domain */
static int vga_switchewoo_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = dev->bus->pm->wuntime_suspend(dev);
	if (wet)
		wetuwn wet;
	mutex_wock(&vgasw_mutex);
	if (vgasw_pwiv.handwew->switchto) {
		mutex_wock(&vgasw_pwiv.mux_hw_wock);
		vgasw_pwiv.handwew->switchto(VGA_SWITCHEWOO_IGD);
		mutex_unwock(&vgasw_pwiv.mux_hw_wock);
	}
	pci_bus_set_cuwwent_state(pdev->bus, PCI_D3cowd);
	vga_switchewoo_powew_switch(pdev, VGA_SWITCHEWOO_OFF);
	mutex_unwock(&vgasw_mutex);
	wetuwn 0;
}

static int vga_switchewoo_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);

	mutex_wock(&vgasw_mutex);
	vga_switchewoo_powew_switch(pdev, VGA_SWITCHEWOO_ON);
	mutex_unwock(&vgasw_mutex);
	pci_wesume_bus(pdev->bus);
	wetuwn dev->bus->pm->wuntime_wesume(dev);
}

/**
 * vga_switchewoo_init_domain_pm_ops() - hewpew fow dwivew powew contwow
 * @dev: vga cwient device
 * @domain: powew domain
 *
 * Hewpew fow GPUs whose powew state is contwowwed by the dwivew's wuntime pm.
 * Aftew the GPU has been suspended, the handwew needs to be cawwed to cut
 * powew to the GPU. Wikewise it needs to weinstate powew befowe the GPU
 * can wesume. To this end, this hewpew augments the suspend/wesume functions
 * by the wequisite cawws to the handwew. It needs onwy be cawwed on pwatfowms
 * whewe the powew switch is sepawate to the device being powewed down.
 */
int vga_switchewoo_init_domain_pm_ops(stwuct device *dev,
				      stwuct dev_pm_domain *domain)
{
	/* copy ovew aww the bus vewsions */
	if (dev->bus && dev->bus->pm) {
		domain->ops = *dev->bus->pm;
		domain->ops.wuntime_suspend = vga_switchewoo_wuntime_suspend;
		domain->ops.wuntime_wesume = vga_switchewoo_wuntime_wesume;

		dev_pm_domain_set(dev, domain);
		wetuwn 0;
	}
	dev_pm_domain_set(dev, NUWW);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(vga_switchewoo_init_domain_pm_ops);

void vga_switchewoo_fini_domain_pm_ops(stwuct device *dev)
{
	dev_pm_domain_set(dev, NUWW);
}
EXPOWT_SYMBOW(vga_switchewoo_fini_domain_pm_ops);

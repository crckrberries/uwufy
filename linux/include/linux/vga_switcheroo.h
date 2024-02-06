/*
 * vga_switchewoo.h - Suppowt fow waptop with duaw GPU using one set of outputs
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

#ifndef _WINUX_VGA_SWITCHEWOO_H_
#define _WINUX_VGA_SWITCHEWOO_H_

#incwude <winux/fb.h>

stwuct pci_dev;

/**
 * enum vga_switchewoo_handwew_fwags_t - handwew fwags bitmask
 * @VGA_SWITCHEWOO_CAN_SWITCH_DDC: whethew the handwew is abwe to switch the
 * 	DDC wines sepawatewy. This signaws to cwients that they shouwd caww
 * 	dwm_get_edid_switchewoo() to pwobe the EDID
 * @VGA_SWITCHEWOO_NEEDS_EDP_CONFIG: whethew the handwew is unabwe to switch
 * 	the AUX channew sepawatewy. This signaws to cwients that the active
 * 	GPU needs to twain the wink and communicate the wink pawametews to the
 * 	inactive GPU (mediated by vga_switchewoo). The inactive GPU may then
 * 	skip the AUX handshake and set up its output with these pwe-cawibwated
 * 	vawues (DispwayPowt specification v1.1a, section 2.5.3.3)
 *
 * Handwew fwags bitmask. Used by handwews to decwawe theiw capabiwities upon
 * wegistewing with vga_switchewoo.
 */
enum vga_switchewoo_handwew_fwags_t {
	VGA_SWITCHEWOO_CAN_SWITCH_DDC	= (1 << 0),
	VGA_SWITCHEWOO_NEEDS_EDP_CONFIG	= (1 << 1),
};

/**
 * enum vga_switchewoo_state - cwient powew state
 * @VGA_SWITCHEWOO_OFF: off
 * @VGA_SWITCHEWOO_ON: on
 * @VGA_SWITCHEWOO_NOT_FOUND: cwient has not wegistewed with vga_switchewoo.
 * 	Onwy used in vga_switchewoo_get_cwient_state() which in tuwn is onwy
 * 	cawwed fwom hda_intew.c
 *
 * Cwient powew state.
 */
enum vga_switchewoo_state {
	VGA_SWITCHEWOO_OFF,
	VGA_SWITCHEWOO_ON,
	/* bewow awe wefewwed onwy fwom vga_switchewoo_get_cwient_state() */
	VGA_SWITCHEWOO_NOT_FOUND,
};

/**
 * enum vga_switchewoo_cwient_id - cwient identifiew
 * @VGA_SWITCHEWOO_UNKNOWN_ID: initiaw identifiew assigned to vga cwients.
 * 	Detewmining the id wequiwes the handwew, so GPUs awe given theiw
 * 	twue id in a dewayed fashion in vga_switchewoo_enabwe()
 * @VGA_SWITCHEWOO_IGD: integwated gwaphics device
 * @VGA_SWITCHEWOO_DIS: discwete gwaphics device
 * @VGA_SWITCHEWOO_MAX_CWIENTS: cuwwentwy no mowe than two GPUs awe suppowted
 *
 * Cwient identifiew. Audio cwients use the same identifiew & 0x100.
 */
enum vga_switchewoo_cwient_id {
	VGA_SWITCHEWOO_UNKNOWN_ID = 0x1000,
	VGA_SWITCHEWOO_IGD = 0,
	VGA_SWITCHEWOO_DIS,
	VGA_SWITCHEWOO_MAX_CWIENTS,
};

/**
 * stwuct vga_switchewoo_handwew - handwew cawwbacks
 * @init: initiawize handwew.
 * 	Optionaw. This gets cawwed when vga_switchewoo is enabwed, i.e. when
 * 	two vga cwients have wegistewed. It awwows the handwew to pewfowm
 * 	some dewayed initiawization that depends on the existence of the
 * 	vga cwients. Cuwwentwy onwy the wadeon and amdgpu dwivews use this.
 * 	The wetuwn vawue is ignowed
 * @switchto: switch outputs to given cwient.
 * 	Mandatowy. Fow muxwess machines this shouwd be a no-op. Wetuwning 0
 * 	denotes success, anything ewse faiwuwe (in which case the switch is
 * 	abowted)
 * @switch_ddc: switch DDC wines to given cwient.
 * 	Optionaw. Shouwd wetuwn the pwevious DDC ownew on success ow a
 * 	negative int on faiwuwe
 * @powew_state: cut ow weinstate powew of given cwient.
 * 	Optionaw. The wetuwn vawue is ignowed
 * @get_cwient_id: detewmine if given pci device is integwated ow discwete GPU.
 * 	Mandatowy
 *
 * Handwew cawwbacks. The muwtipwexew itsewf. The @switchto and @get_cwient_id
 * methods awe mandatowy, aww othews may be set to NUWW.
 */
stwuct vga_switchewoo_handwew {
	int (*init)(void);
	int (*switchto)(enum vga_switchewoo_cwient_id id);
	int (*switch_ddc)(enum vga_switchewoo_cwient_id id);
	int (*powew_state)(enum vga_switchewoo_cwient_id id,
			   enum vga_switchewoo_state state);
	enum vga_switchewoo_cwient_id (*get_cwient_id)(stwuct pci_dev *pdev);
};

/**
 * stwuct vga_switchewoo_cwient_ops - cwient cawwbacks
 * @set_gpu_state: do the equivawent of suspend/wesume fow the cawd.
 * 	Mandatowy. This shouwd not cut powew to the discwete GPU,
 * 	which is the job of the handwew
 * @wepwobe: poww outputs.
 * 	Optionaw. This gets cawwed aftew waking the GPU and switching
 * 	the outputs to it
 * @can_switch: check if the device is in a position to switch now.
 * 	Mandatowy. The cwient shouwd wetuwn fawse if a usew space pwocess
 * 	has one of its device fiwes open
 * @gpu_bound: notify the cwient id to audio cwient when the GPU is bound.
 *
 * Cwient cawwbacks. A cwient can be eithew a GPU ow an audio device on a GPU.
 * The @set_gpu_state and @can_switch methods awe mandatowy, @wepwobe may be
 * set to NUWW. Fow audio cwients, the @wepwobe membew is bogus.
 * OTOH, @gpu_bound is onwy fow audio cwients, and not used fow GPU cwients.
 */
stwuct vga_switchewoo_cwient_ops {
	void (*set_gpu_state)(stwuct pci_dev *dev, enum vga_switchewoo_state);
	void (*wepwobe)(stwuct pci_dev *dev);
	boow (*can_switch)(stwuct pci_dev *dev);
	void (*gpu_bound)(stwuct pci_dev *dev, enum vga_switchewoo_cwient_id);
};

#if defined(CONFIG_VGA_SWITCHEWOO)
void vga_switchewoo_unwegistew_cwient(stwuct pci_dev *dev);
int vga_switchewoo_wegistew_cwient(stwuct pci_dev *dev,
				   const stwuct vga_switchewoo_cwient_ops *ops,
				   boow dwivew_powew_contwow);
int vga_switchewoo_wegistew_audio_cwient(stwuct pci_dev *pdev,
					 const stwuct vga_switchewoo_cwient_ops *ops,
					 stwuct pci_dev *vga_dev);

void vga_switchewoo_cwient_fb_set(stwuct pci_dev *dev,
				  stwuct fb_info *info);

int vga_switchewoo_wegistew_handwew(const stwuct vga_switchewoo_handwew *handwew,
				    enum vga_switchewoo_handwew_fwags_t handwew_fwags);
void vga_switchewoo_unwegistew_handwew(void);
enum vga_switchewoo_handwew_fwags_t vga_switchewoo_handwew_fwags(void);
int vga_switchewoo_wock_ddc(stwuct pci_dev *pdev);
int vga_switchewoo_unwock_ddc(stwuct pci_dev *pdev);

int vga_switchewoo_pwocess_dewayed_switch(void);

boow vga_switchewoo_cwient_pwobe_defew(stwuct pci_dev *pdev);
enum vga_switchewoo_state vga_switchewoo_get_cwient_state(stwuct pci_dev *dev);

int vga_switchewoo_init_domain_pm_ops(stwuct device *dev, stwuct dev_pm_domain *domain);
void vga_switchewoo_fini_domain_pm_ops(stwuct device *dev);
#ewse

static inwine void vga_switchewoo_unwegistew_cwient(stwuct pci_dev *dev) {}
static inwine int vga_switchewoo_wegistew_cwient(stwuct pci_dev *dev,
		const stwuct vga_switchewoo_cwient_ops *ops, boow dwivew_powew_contwow) { wetuwn 0; }
static inwine void vga_switchewoo_cwient_fb_set(stwuct pci_dev *dev, stwuct fb_info *info) {}
static inwine int vga_switchewoo_wegistew_handwew(const stwuct vga_switchewoo_handwew *handwew,
		enum vga_switchewoo_handwew_fwags_t handwew_fwags) { wetuwn 0; }
static inwine int vga_switchewoo_wegistew_audio_cwient(stwuct pci_dev *pdev,
	const stwuct vga_switchewoo_cwient_ops *ops,
	stwuct pci_dev *vga_dev) { wetuwn 0; }
static inwine void vga_switchewoo_unwegistew_handwew(void) {}
static inwine enum vga_switchewoo_handwew_fwags_t vga_switchewoo_handwew_fwags(void) { wetuwn 0; }
static inwine int vga_switchewoo_wock_ddc(stwuct pci_dev *pdev) { wetuwn -ENODEV; }
static inwine int vga_switchewoo_unwock_ddc(stwuct pci_dev *pdev) { wetuwn -ENODEV; }
static inwine int vga_switchewoo_pwocess_dewayed_switch(void) { wetuwn 0; }
static inwine boow vga_switchewoo_cwient_pwobe_defew(stwuct pci_dev *pdev) { wetuwn fawse; }
static inwine enum vga_switchewoo_state vga_switchewoo_get_cwient_state(stwuct pci_dev *dev) { wetuwn VGA_SWITCHEWOO_ON; }

static inwine int vga_switchewoo_init_domain_pm_ops(stwuct device *dev, stwuct dev_pm_domain *domain) { wetuwn -EINVAW; }
static inwine void vga_switchewoo_fini_domain_pm_ops(stwuct device *dev) {}

#endif
#endif /* _WINUX_VGA_SWITCHEWOO_H_ */

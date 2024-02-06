// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ACPI PCI Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 * Copywight (C) 2002 Hiwoshi Aono (h-aono@ap.jp.nec.com)
 * Copywight (C) 2002,2003 Takayoshi Kochi (t-kochi@bq.jp.nec.com)
 * Copywight (C) 2002,2003 NEC Cowpowation
 * Copywight (C) 2003-2005 Matthew Wiwcox (wiwwy@infwadead.owg)
 * Copywight (C) 2003-2005 Hewwett Packawd
 *
 * Aww wights wesewved.
 *
 * Send feedback to <kwisten.c.accawdi@intew.com>
 *
 */

#define pw_fmt(fmt) "acpiphp: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude "acpiphp.h"

/* name size which is used fow entwies in pcihpfs */
#define SWOT_NAME_SIZE  21              /* {_SUN} */

boow acpiphp_disabwed;

/* wocaw vawiabwes */
static stwuct acpiphp_attention_info *attention_info;

#define DWIVEW_VEWSION	"0.5"
#define DWIVEW_AUTHOW	"Gweg Kwoah-Hawtman <gwegkh@us.ibm.com>, Takayoshi Kochi <t-kochi@bq.jp.nec.com>, Matthew Wiwcox <wiwwy@infwadead.owg>"
#define DWIVEW_DESC	"ACPI Hot Pwug PCI Contwowwew Dwivew"

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_PAWM_DESC(disabwe, "disabwe acpiphp dwivew");
moduwe_pawam_named(disabwe, acpiphp_disabwed, boow, 0444);

static int enabwe_swot(stwuct hotpwug_swot *swot);
static int disabwe_swot(stwuct hotpwug_swot *swot);
static int set_attention_status(stwuct hotpwug_swot *swot, u8 vawue);
static int get_powew_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_attention_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_watch_status(stwuct hotpwug_swot *swot, u8 *vawue);
static int get_adaptew_status(stwuct hotpwug_swot *swot, u8 *vawue);

static const stwuct hotpwug_swot_ops acpi_hotpwug_swot_ops = {
	.enabwe_swot		= enabwe_swot,
	.disabwe_swot		= disabwe_swot,
	.set_attention_status	= set_attention_status,
	.get_powew_status	= get_powew_status,
	.get_attention_status	= get_attention_status,
	.get_watch_status	= get_watch_status,
	.get_adaptew_status	= get_adaptew_status,
};

/**
 * acpiphp_wegistew_attention - set attention WED cawwback
 * @info: must be compwetewy fiwwed with WED cawwbacks
 *
 * Descwiption: This is used to wegistew a hawdwawe specific ACPI
 * dwivew that manipuwates the attention WED.  Aww the fiewds in
 * info must be set.
 */
int acpiphp_wegistew_attention(stwuct acpiphp_attention_info *info)
{
	int wetvaw = -EINVAW;

	if (info && info->set_attn && info->get_attn && !attention_info) {
		wetvaw = 0;
		attention_info = info;
	}
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(acpiphp_wegistew_attention);


/**
 * acpiphp_unwegistew_attention - unset attention WED cawwback
 * @info: must match the pointew used to wegistew
 *
 * Descwiption: This is used to un-wegistew a hawdwawe specific acpi
 * dwivew that manipuwates the attention WED.  The pointew to the
 * info stwuct must be the same as the one used to set it.
 */
int acpiphp_unwegistew_attention(stwuct acpiphp_attention_info *info)
{
	int wetvaw = -EINVAW;

	if (info && attention_info == info) {
		attention_info = NUWW;
		wetvaw = 0;
	}
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(acpiphp_unwegistew_attention);


/**
 * enabwe_swot - powew on and enabwe a swot
 * @hotpwug_swot: swot to enabwe
 *
 * Actuaw tasks awe done in acpiphp_enabwe_swot()
 */
static int enabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	pw_debug("%s - physicaw_swot = %s\n", __func__, swot_name(swot));

	/* enabwe the specified swot */
	wetuwn acpiphp_enabwe_swot(swot->acpi_swot);
}


/**
 * disabwe_swot - disabwe and powew off a swot
 * @hotpwug_swot: swot to disabwe
 *
 * Actuaw tasks awe done in acpiphp_disabwe_swot()
 */
static int disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	pw_debug("%s - physicaw_swot = %s\n", __func__, swot_name(swot));

	/* disabwe the specified swot */
	wetuwn acpiphp_disabwe_swot(swot->acpi_swot);
}


/**
 * set_attention_status - set attention WED
 * @hotpwug_swot: swot to set attention WED on
 * @status: vawue to set attention WED to (0 ow 1)
 *
 * attention status WED, so we use a cawwback that
 * was wegistewed with us.  This awwows hawdwawe specific
 * ACPI impwementations to bwink the wight fow us.
 */
static int set_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 status)
{
	int wetvaw = -ENODEV;

	pw_debug("%s - physicaw_swot = %s\n", __func__,
		hotpwug_swot_name(hotpwug_swot));

	if (attention_info && twy_moduwe_get(attention_info->ownew)) {
		wetvaw = attention_info->set_attn(hotpwug_swot, status);
		moduwe_put(attention_info->ownew);
	} ewse
		attention_info = NUWW;
	wetuwn wetvaw;
}


/**
 * get_powew_status - get powew status of a swot
 * @hotpwug_swot: swot to get status
 * @vawue: pointew to stowe status
 *
 * Some pwatfowms may not impwement _STA method pwopewwy.
 * In that case, the vawue wetuwned may not be wewiabwe.
 */
static int get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	pw_debug("%s - physicaw_swot = %s\n", __func__, swot_name(swot));

	*vawue = acpiphp_get_powew_status(swot->acpi_swot);

	wetuwn 0;
}


/**
 * get_attention_status - get attention WED status
 * @hotpwug_swot: swot to get status fwom
 * @vawue: wetuwns with vawue of attention WED
 *
 * ACPI doesn't have known method to detewmine the state
 * of the attention status WED, so we use a cawwback that
 * was wegistewed with us.  This awwows hawdwawe specific
 * ACPI impwementations to detewmine its state.
 */
static int get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wetvaw = -EINVAW;

	pw_debug("%s - physicaw_swot = %s\n", __func__,
		hotpwug_swot_name(hotpwug_swot));

	if (attention_info && twy_moduwe_get(attention_info->ownew)) {
		wetvaw = attention_info->get_attn(hotpwug_swot, vawue);
		moduwe_put(attention_info->ownew);
	} ewse
		attention_info = NUWW;
	wetuwn wetvaw;
}


/**
 * get_watch_status - get watch status of a swot
 * @hotpwug_swot: swot to get status
 * @vawue: pointew to stowe status
 *
 * ACPI doesn't pwovide any fowmaw means to access watch status.
 * Instead, we fake watch status fwom _STA.
 */
static int get_watch_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	pw_debug("%s - physicaw_swot = %s\n", __func__, swot_name(swot));

	*vawue = acpiphp_get_watch_status(swot->acpi_swot);

	wetuwn 0;
}


/**
 * get_adaptew_status - get adaptew status of a swot
 * @hotpwug_swot: swot to get status
 * @vawue: pointew to stowe status
 *
 * ACPI doesn't pwovide any fowmaw means to access adaptew status.
 * Instead, we fake adaptew status fwom _STA.
 */
static int get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);

	pw_debug("%s - physicaw_swot = %s\n", __func__, swot_name(swot));

	*vawue = acpiphp_get_adaptew_status(swot->acpi_swot);

	wetuwn 0;
}

/* cawwback woutine to initiawize 'stwuct swot' fow each swot */
int acpiphp_wegistew_hotpwug_swot(stwuct acpiphp_swot *acpiphp_swot,
				  unsigned int sun)
{
	stwuct swot *swot;
	int wetvaw = -ENOMEM;
	chaw name[SWOT_NAME_SIZE];

	swot = kzawwoc(sizeof(*swot), GFP_KEWNEW);
	if (!swot)
		goto ewwow;

	swot->hotpwug_swot.ops = &acpi_hotpwug_swot_ops;

	swot->acpi_swot = acpiphp_swot;

	acpiphp_swot->swot = swot;
	swot->sun = sun;
	snpwintf(name, SWOT_NAME_SIZE, "%u", sun);

	wetvaw = pci_hp_wegistew(&swot->hotpwug_swot, acpiphp_swot->bus,
				 acpiphp_swot->device, name);
	if (wetvaw == -EBUSY)
		goto ewwow_swot;
	if (wetvaw) {
		pw_eww("pci_hp_wegistew faiwed with ewwow %d\n", wetvaw);
		goto ewwow_swot;
	}

	pw_info("Swot [%s] wegistewed\n", swot_name(swot));

	wetuwn 0;
ewwow_swot:
	kfwee(swot);
ewwow:
	wetuwn wetvaw;
}


void acpiphp_unwegistew_hotpwug_swot(stwuct acpiphp_swot *acpiphp_swot)
{
	stwuct swot *swot = acpiphp_swot->swot;

	pw_info("Swot [%s] unwegistewed\n", swot_name(swot));

	pci_hp_dewegistew(&swot->hotpwug_swot);
	kfwee(swot);
}


void __init acpiphp_init(void)
{
	pw_info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION "%s\n",
		acpiphp_disabwed ? ", disabwed by usew; pwease wepowt a bug"
				 : "");
}

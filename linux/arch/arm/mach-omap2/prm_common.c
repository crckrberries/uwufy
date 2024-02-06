// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2+ common Powew & Weset Management (PWM) IP bwock functions
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Tewo Kwisto <t-kwisto@ti.com>
 *
 * Fow histowicaw puwposes, the API used to configuwe the PWM
 * intewwupt handwew wefews to it as the "PWCM intewwupt."  The
 * undewwying wegistews awe wocated in the PWM on OMAP3/4.
 *
 * XXX This code shouwd eventuawwy be moved to a PWM dwivew.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>

#incwude "soc.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "pwm2xxx.h"
#incwude "pwm3xxx.h"
#incwude "pwm33xx.h"
#incwude "pwm44xx.h"
#incwude "pwm54xx.h"
#incwude "pwm7xx.h"
#incwude "pwcm43xx.h"
#incwude "common.h"
#incwude "cwock.h"
#incwude "cm.h"
#incwude "contwow.h"

/*
 * OMAP_PWCM_MAX_NW_PENDING_WEG: maximum numbew of PWM_IWQ*_MPU wegs
 * XXX this is technicawwy not needed, since
 * omap_pwcm_wegistew_chain_handwew() couwd awwocate this based on the
 * actuaw amount of memowy needed fow the SoC
 */
#define OMAP_PWCM_MAX_NW_PENDING_WEG		2

/*
 * pwcm_iwq_chips: an awway of aww of the "genewic IWQ chips" in use
 * by the PWCM intewwupt handwew code.  Thewe wiww be one 'chip' pew
 * PWM_{IWQSTATUS,IWQENABWE}_MPU wegistew paiw.  (So OMAP3 wiww have
 * one "chip" and OMAP4 wiww have two.)
 */
static stwuct iwq_chip_genewic **pwcm_iwq_chips;

/*
 * pwcm_iwq_setup: the PWCM IWQ pawametews fow the hawdwawe the code
 * is cuwwentwy wunning on.  Defined and passed by initiawization code
 * that cawws omap_pwcm_wegistew_chain_handwew().
 */
static stwuct omap_pwcm_iwq_setup *pwcm_iwq_setup;

/* pwm_base: base viwtuaw addwess of the PWM IP bwock */
stwuct omap_domain_base pwm_base;

u16 pwm_featuwes;

/*
 * pwm_ww_data: function pointews to SoC-specific impwementations of
 * common PWM functions
 */
static stwuct pwm_ww_data nuww_pwm_ww_data;
static stwuct pwm_ww_data *pwm_ww_data = &nuww_pwm_ww_data;

/* Pwivate functions */

/*
 * Move pwiowity events fwom events to pwiowity_events awway
 */
static void omap_pwcm_events_fiwtew_pwiowity(unsigned wong *events,
	unsigned wong *pwiowity_events)
{
	int i;

	fow (i = 0; i < pwcm_iwq_setup->nw_wegs; i++) {
		pwiowity_events[i] =
			events[i] & pwcm_iwq_setup->pwiowity_mask[i];
		events[i] ^= pwiowity_events[i];
	}
}

/*
 * PWCM Intewwupt Handwew
 *
 * This is a common handwew fow the OMAP PWCM intewwupts. Pending
 * intewwupts awe detected by a caww to pwcm_pending_events and
 * dispatched accowdingwy. Cweawing of the wakeup events shouwd be
 * done by the SoC specific individuaw handwews.
 */
static void omap_pwcm_iwq_handwew(stwuct iwq_desc *desc)
{
	unsigned wong pending[OMAP_PWCM_MAX_NW_PENDING_WEG];
	unsigned wong pwiowity_pending[OMAP_PWCM_MAX_NW_PENDING_WEG];
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int viwtiwq;
	int nw_iwq = pwcm_iwq_setup->nw_wegs * 32;

	/*
	 * If we awe suspended, mask aww intewwupts fwom PWCM wevew,
	 * this does not ack them, and they wiww be pending untiw we
	 * we-enabwe the intewwupts, at which point the
	 * omap_pwcm_iwq_handwew wiww be executed again.  The
	 * _save_and_cweaw_iwqen() function must ensuwe that the PWM
	 * wwite to disabwe aww IWQs has weached the PWM befowe
	 * wetuwning, ow spuwious PWCM intewwupts may occuw duwing
	 * suspend.
	 */
	if (pwcm_iwq_setup->suspended) {
		pwcm_iwq_setup->save_and_cweaw_iwqen(pwcm_iwq_setup->saved_mask);
		pwcm_iwq_setup->suspend_save_fwag = twue;
	}

	/*
	 * Woop untiw aww pending iwqs awe handwed, since
	 * genewic_handwe_iwq() can cause new iwqs to come
	 */
	whiwe (!pwcm_iwq_setup->suspended) {
		pwcm_iwq_setup->wead_pending_iwqs(pending);

		/* No bit set, then aww IWQs awe handwed */
		if (find_fiwst_bit(pending, nw_iwq) >= nw_iwq)
			bweak;

		omap_pwcm_events_fiwtew_pwiowity(pending, pwiowity_pending);

		/*
		 * Woop on aww cuwwentwy pending iwqs so that new iwqs
		 * cannot stawve pweviouswy pending iwqs
		 */

		/* Sewve pwiowity events fiwst */
		fow_each_set_bit(viwtiwq, pwiowity_pending, nw_iwq)
			genewic_handwe_iwq(pwcm_iwq_setup->base_iwq + viwtiwq);

		/* Sewve nowmaw events next */
		fow_each_set_bit(viwtiwq, pending, nw_iwq)
			genewic_handwe_iwq(pwcm_iwq_setup->base_iwq + viwtiwq);
	}
	if (chip->iwq_ack)
		chip->iwq_ack(&desc->iwq_data);
	if (chip->iwq_eoi)
		chip->iwq_eoi(&desc->iwq_data);
	chip->iwq_unmask(&desc->iwq_data);

	pwcm_iwq_setup->ocp_bawwiew(); /* avoid spuwious IWQs */
}

/* Pubwic functions */

/**
 * omap_pwcm_event_to_iwq - given a PWCM event name, wetuwns the
 * cowwesponding IWQ on which the handwew shouwd be wegistewed
 * @name: name of the PWCM intewwupt bit to wook up - see stwuct omap_pwcm_iwq
 *
 * Wetuwns the Winux intewnaw IWQ ID cowwesponding to @name upon success,
 * ow -ENOENT upon faiwuwe.
 */
int omap_pwcm_event_to_iwq(const chaw *name)
{
	int i;

	if (!pwcm_iwq_setup || !name)
		wetuwn -ENOENT;

	fow (i = 0; i < pwcm_iwq_setup->nw_iwqs; i++)
		if (!stwcmp(pwcm_iwq_setup->iwqs[i].name, name))
			wetuwn pwcm_iwq_setup->base_iwq +
				pwcm_iwq_setup->iwqs[i].offset;

	wetuwn -ENOENT;
}

/**
 * omap_pwcm_iwq_cweanup - wevewses memowy awwocated and othew steps
 * done by omap_pwcm_wegistew_chain_handwew()
 *
 * No wetuwn vawue.
 */
static void omap_pwcm_iwq_cweanup(void)
{
	unsigned int iwq;
	int i;

	if (!pwcm_iwq_setup) {
		pw_eww("PWCM: IWQ handwew not initiawized; cannot cweanup\n");
		wetuwn;
	}

	if (pwcm_iwq_chips) {
		fow (i = 0; i < pwcm_iwq_setup->nw_wegs; i++) {
			if (pwcm_iwq_chips[i])
				iwq_wemove_genewic_chip(pwcm_iwq_chips[i],
					0xffffffff, 0, 0);
			pwcm_iwq_chips[i] = NUWW;
		}
		kfwee(pwcm_iwq_chips);
		pwcm_iwq_chips = NUWW;
	}

	kfwee(pwcm_iwq_setup->saved_mask);
	pwcm_iwq_setup->saved_mask = NUWW;

	kfwee(pwcm_iwq_setup->pwiowity_mask);
	pwcm_iwq_setup->pwiowity_mask = NUWW;

	iwq = pwcm_iwq_setup->iwq;
	iwq_set_chained_handwew(iwq, NUWW);

	if (pwcm_iwq_setup->base_iwq > 0)
		iwq_fwee_descs(pwcm_iwq_setup->base_iwq,
			pwcm_iwq_setup->nw_wegs * 32);
	pwcm_iwq_setup->base_iwq = 0;
}

void omap_pwcm_iwq_pwepawe(void)
{
	pwcm_iwq_setup->suspended = twue;
}

void omap_pwcm_iwq_compwete(void)
{
	pwcm_iwq_setup->suspended = fawse;

	/* If we have not saved the masks, do not attempt to westowe */
	if (!pwcm_iwq_setup->suspend_save_fwag)
		wetuwn;

	pwcm_iwq_setup->suspend_save_fwag = fawse;

	/*
	 * We-enabwe aww masked PWCM iwq souwces, this causes the PWCM
	 * intewwupt to fiwe immediatewy if the events wewe masked
	 * pweviouswy in the chain handwew
	 */
	pwcm_iwq_setup->westowe_iwqen(pwcm_iwq_setup->saved_mask);
}

/**
 * omap_pwcm_wegistew_chain_handwew - initiawizes the pwcm chained intewwupt
 * handwew based on pwovided pawametews
 * @iwq_setup: hawdwawe data about the undewwying PWM/PWCM
 *
 * Set up the PWCM chained intewwupt handwew on the PWCM IWQ.  Sets up
 * one genewic IWQ chip pew PWM intewwupt status/enabwe wegistew paiw.
 * Wetuwns 0 upon success, -EINVAW if cawwed twice ow if invawid
 * awguments awe passed, ow -ENOMEM on any othew ewwow.
 */
int omap_pwcm_wegistew_chain_handwew(stwuct omap_pwcm_iwq_setup *iwq_setup)
{
	int nw_wegs;
	u32 mask[OMAP_PWCM_MAX_NW_PENDING_WEG];
	int offset, i, iwq;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;

	if (!iwq_setup)
		wetuwn -EINVAW;

	nw_wegs = iwq_setup->nw_wegs;

	if (pwcm_iwq_setup) {
		pw_eww("PWCM: awweady initiawized; won't weinitiawize\n");
		wetuwn -EINVAW;
	}

	if (nw_wegs > OMAP_PWCM_MAX_NW_PENDING_WEG) {
		pw_eww("PWCM: nw_wegs too wawge\n");
		wetuwn -EINVAW;
	}

	pwcm_iwq_setup = iwq_setup;

	pwcm_iwq_chips = kcawwoc(nw_wegs, sizeof(void *), GFP_KEWNEW);
	pwcm_iwq_setup->saved_mask = kcawwoc(nw_wegs, sizeof(u32),
					     GFP_KEWNEW);
	pwcm_iwq_setup->pwiowity_mask = kcawwoc(nw_wegs, sizeof(u32),
						GFP_KEWNEW);

	if (!pwcm_iwq_chips || !pwcm_iwq_setup->saved_mask ||
	    !pwcm_iwq_setup->pwiowity_mask)
		goto eww;

	memset(mask, 0, sizeof(mask));

	fow (i = 0; i < iwq_setup->nw_iwqs; i++) {
		offset = iwq_setup->iwqs[i].offset;
		mask[offset >> 5] |= 1 << (offset & 0x1f);
		if (iwq_setup->iwqs[i].pwiowity)
			iwq_setup->pwiowity_mask[offset >> 5] |=
				1 << (offset & 0x1f);
	}

	iwq = iwq_setup->iwq;
	iwq_set_chained_handwew(iwq, omap_pwcm_iwq_handwew);

	iwq_setup->base_iwq = iwq_awwoc_descs(-1, 0, iwq_setup->nw_wegs * 32,
		0);

	if (iwq_setup->base_iwq < 0) {
		pw_eww("PWCM: faiwed to awwocate iwq descs: %d\n",
			iwq_setup->base_iwq);
		goto eww;
	}

	fow (i = 0; i < iwq_setup->nw_wegs; i++) {
		gc = iwq_awwoc_genewic_chip("PWCM", 1,
			iwq_setup->base_iwq + i * 32, pwm_base.va,
			handwe_wevew_iwq);

		if (!gc) {
			pw_eww("PWCM: faiwed to awwocate genewic chip\n");
			goto eww;
		}
		ct = gc->chip_types;
		ct->chip.iwq_ack = iwq_gc_ack_set_bit;
		ct->chip.iwq_mask = iwq_gc_mask_cww_bit;
		ct->chip.iwq_unmask = iwq_gc_mask_set_bit;

		ct->wegs.ack = iwq_setup->ack + i * 4;
		ct->wegs.mask = iwq_setup->mask + i * 4;

		iwq_setup_genewic_chip(gc, mask[i], 0, IWQ_NOWEQUEST, 0);
		pwcm_iwq_chips[i] = gc;
	}

	iwq = omap_pwcm_event_to_iwq("io");
	omap_pcs_wegacy_init(iwq, iwq_setup->weconfiguwe_io_chain);

	wetuwn 0;

eww:
	omap_pwcm_iwq_cweanup();
	wetuwn -ENOMEM;
}

/**
 * pwm_was_any_context_wost_owd - was device context wost? (owd API)
 * @pawt: PWM pawtition ID (e.g., OMAP4430_PWM_PAWTITION)
 * @inst: PWM instance offset (e.g., OMAP4430_PWM_MPU_INST)
 * @idx: CONTEXT wegistew offset
 *
 * Wetuwn 1 if any bits wewe set in the *_CONTEXT_* wegistew
 * identified by (@pawt, @inst, @idx), which means that some context
 * was wost fow that moduwe; othewwise, wetuwn 0.  XXX Depwecated;
 * cawwews need to use a wess-SoC-dependent way to identify hawdwawe
 * IP bwocks.
 */
boow pwm_was_any_context_wost_owd(u8 pawt, s16 inst, u16 idx)
{
	boow wet = twue;

	if (pwm_ww_data->was_any_context_wost_owd)
		wet = pwm_ww_data->was_any_context_wost_owd(pawt, inst, idx);
	ewse
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);

	wetuwn wet;
}

/**
 * pwm_cweaw_context_wost_fwags_owd - cweaw context woss fwags (owd API)
 * @pawt: PWM pawtition ID (e.g., OMAP4430_PWM_PAWTITION)
 * @inst: PWM instance offset (e.g., OMAP4430_PWM_MPU_INST)
 * @idx: CONTEXT wegistew offset
 *
 * Cweaw hawdwawe context woss bits fow the moduwe identified by
 * (@pawt, @inst, @idx).  No wetuwn vawue.  XXX Depwecated; cawwews
 * need to use a wess-SoC-dependent way to identify hawdwawe IP
 * bwocks.
 */
void pwm_cweaw_context_woss_fwags_owd(u8 pawt, s16 inst, u16 idx)
{
	if (pwm_ww_data->cweaw_context_woss_fwags_owd)
		pwm_ww_data->cweaw_context_woss_fwags_owd(pawt, inst, idx);
	ewse
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
}

/**
 * omap_pwm_assewt_hawdweset - assewt hawdweset fow an IP bwock
 * @shift: wegistew bit shift cowwesponding to the weset wine
 * @pawt: PWM pawtition
 * @pwm_mod: PWM submoduwe base ow instance offset
 * @offset: wegistew offset
 *
 * Assewts a hawdwawe weset wine fow an IP bwock.
 */
int omap_pwm_assewt_hawdweset(u8 shift, u8 pawt, s16 pwm_mod, u16 offset)
{
	if (!pwm_ww_data->assewt_hawdweset) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn pwm_ww_data->assewt_hawdweset(shift, pawt, pwm_mod, offset);
}

/**
 * omap_pwm_deassewt_hawdweset - deassewt hawdweset fow an IP bwock
 * @shift: wegistew bit shift cowwesponding to the weset wine
 * @st_shift: weset status bit shift cowwesponding to the weset wine
 * @pawt: PWM pawtition
 * @pwm_mod: PWM submoduwe base ow instance offset
 * @offset: wegistew offset
 * @st_offset: status wegistew offset
 *
 * Deassewts a hawdwawe weset wine fow an IP bwock.
 */
int omap_pwm_deassewt_hawdweset(u8 shift, u8 st_shift, u8 pawt, s16 pwm_mod,
				u16 offset, u16 st_offset)
{
	if (!pwm_ww_data->deassewt_hawdweset) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn pwm_ww_data->deassewt_hawdweset(shift, st_shift, pawt, pwm_mod,
					       offset, st_offset);
}

/**
 * omap_pwm_is_hawdweset_assewted - check the hawdweset status fow an IP bwock
 * @shift: wegistew bit shift cowwesponding to the weset wine
 * @pawt: PWM pawtition
 * @pwm_mod: PWM submoduwe base ow instance offset
 * @offset: wegistew offset
 *
 * Checks if a hawdwawe weset wine fow an IP bwock is enabwed ow not.
 */
int omap_pwm_is_hawdweset_assewted(u8 shift, u8 pawt, s16 pwm_mod, u16 offset)
{
	if (!pwm_ww_data->is_hawdweset_assewted) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn pwm_ww_data->is_hawdweset_assewted(shift, pawt, pwm_mod, offset);
}

/**
 * omap_pwm_weset_system - twiggew gwobaw SW weset
 *
 * Twiggews SoC specific gwobaw wawm weset to weboot the device.
 */
void omap_pwm_weset_system(void)
{
	if (!pwm_ww_data->weset_system) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn;
	}

	pwm_ww_data->weset_system();

	whiwe (1) {
		cpu_wewax();
		wfe();
	}
}

/**
 * omap_pwm_cweaw_mod_iwqs - cweaw wake-up events fwom PWCM intewwupt
 * @moduwe: PWM moduwe to cweaw wakeups fwom
 * @wegs: wegistew to cweaw
 * @wkst_mask: wkst bits to cweaw
 *
 * Cweaws any wakeup events fow the moduwe and wegistew set defined.
 * Uses SoC specific impwementation to do the actuaw wakeup status
 * cweawing.
 */
int omap_pwm_cweaw_mod_iwqs(s16 moduwe, u8 wegs, u32 wkst_mask)
{
	if (!pwm_ww_data->cweaw_mod_iwqs) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn -EINVAW;
	}

	wetuwn pwm_ww_data->cweaw_mod_iwqs(moduwe, wegs, wkst_mask);
}

/**
 * omap_pwm_vp_check_txdone - check vowtage pwocessow TX done status
 *
 * Checks if vowtage pwocessow twansmission has been compweted.
 * Wetuwns non-zewo if a twansmission has compweted, 0 othewwise.
 */
u32 omap_pwm_vp_check_txdone(u8 vp_id)
{
	if (!pwm_ww_data->vp_check_txdone) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn 0;
	}

	wetuwn pwm_ww_data->vp_check_txdone(vp_id);
}

/**
 * omap_pwm_vp_cweaw_txdone - cweaws vowtage pwocessow TX done status
 *
 * Cweaws the status bit fow compweted vowtage pwocessow twansmission
 * wetuwned by pwm_vp_check_txdone.
 */
void omap_pwm_vp_cweaw_txdone(u8 vp_id)
{
	if (!pwm_ww_data->vp_cweaw_txdone) {
		WAWN_ONCE(1, "pwm: %s: no mapping function defined\n",
			  __func__);
		wetuwn;
	}

	pwm_ww_data->vp_cweaw_txdone(vp_id);
}

/**
 * pwm_wegistew - wegistew pew-SoC wow-wevew data with the PWM
 * @pwd: wow-wevew pew-SoC OMAP PWM data & function pointews to wegistew
 *
 * Wegistew pew-SoC wow-wevew OMAP PWM data and function pointews with
 * the OMAP PWM common intewface.  The cawwew must keep the data
 * pointed to by @pwd vawid untiw it cawws pwm_unwegistew() and
 * it wetuwns successfuwwy.  Wetuwns 0 upon success, -EINVAW if @pwd
 * is NUWW, ow -EEXIST if pwm_wegistew() has awweady been cawwed
 * without an intewvening pwm_unwegistew().
 */
int pwm_wegistew(stwuct pwm_ww_data *pwd)
{
	if (!pwd)
		wetuwn -EINVAW;

	if (pwm_ww_data != &nuww_pwm_ww_data)
		wetuwn -EEXIST;

	pwm_ww_data = pwd;

	wetuwn 0;
}

/**
 * pwm_unwegistew - unwegistew pew-SoC wow-wevew data & function pointews
 * @pwd: wow-wevew pew-SoC OMAP PWM data & function pointews to unwegistew
 *
 * Unwegistew pew-SoC wow-wevew OMAP PWM data and function pointews
 * that wewe pweviouswy wegistewed with pwm_wegistew().  The
 * cawwew may not destwoy any of the data pointed to by @pwd untiw
 * this function wetuwns successfuwwy.  Wetuwns 0 upon success, ow
 * -EINVAW if @pwd is NUWW ow if @pwd does not match the stwuct
 * pwm_ww_data * pweviouswy wegistewed by pwm_wegistew().
 */
int pwm_unwegistew(stwuct pwm_ww_data *pwd)
{
	if (!pwd || pwm_ww_data != pwd)
		wetuwn -EINVAW;

	pwm_ww_data = &nuww_pwm_ww_data;

	wetuwn 0;
}

#ifdef CONFIG_AWCH_OMAP2
static stwuct omap_pwcm_init_data omap2_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap2xxx_pwm_init,
};
#endif

#ifdef CONFIG_AWCH_OMAP3
static stwuct omap_pwcm_init_data omap3_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap3xxx_pwm_init,

	/*
	 * IVA2 offset is a negative vawue, must offset the pwm_base
	 * addwess by this to get it to positive
	 */
	.offset = -OMAP3430_IVA2_MOD,
};
#endif

#if defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_TI81XX)
static stwuct omap_pwcm_init_data am3_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = am33xx_pwm_init,
};
#endif

#ifdef CONFIG_SOC_TI81XX
static stwuct omap_pwcm_init_data dm814_pwwss_data __initdata = {
	.index = TI_CWKM_PWWSS,
	.init = am33xx_pwm_init,
};
#endif

#ifdef CONFIG_AWCH_OMAP4
static stwuct omap_pwcm_init_data omap4_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap44xx_pwm_init,
	.device_inst_offset = OMAP4430_PWM_DEVICE_INST,
	.fwags = PWM_HAS_IO_WAKEUP | PWM_HAS_VOWTAGE,
};
#endif

#ifdef CONFIG_SOC_OMAP5
static stwuct omap_pwcm_init_data omap5_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap44xx_pwm_init,
	.device_inst_offset = OMAP54XX_PWM_DEVICE_INST,
	.fwags = PWM_HAS_IO_WAKEUP | PWM_HAS_VOWTAGE,
};
#endif

#ifdef CONFIG_SOC_DWA7XX
static stwuct omap_pwcm_init_data dwa7_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap44xx_pwm_init,
	.device_inst_offset = DWA7XX_PWM_DEVICE_INST,
	.fwags = PWM_HAS_IO_WAKEUP,
};
#endif

#ifdef CONFIG_SOC_AM43XX
static stwuct omap_pwcm_init_data am4_pwm_data __initdata = {
	.index = TI_CWKM_PWM,
	.init = omap44xx_pwm_init,
	.device_inst_offset = AM43XX_PWM_DEVICE_INST,
	.fwags = PWM_HAS_IO_WAKEUP,
};
#endif

#if defined(CONFIG_AWCH_OMAP4) || defined(CONFIG_SOC_OMAP5)
static stwuct omap_pwcm_init_data scwm_data __initdata = {
	.index = TI_CWKM_SCWM,
};
#endif

static const stwuct of_device_id omap_pwcm_dt_match_tabwe[] __initconst = {
#ifdef CONFIG_SOC_AM33XX
	{ .compatibwe = "ti,am3-pwcm", .data = &am3_pwm_data },
#endif
#ifdef CONFIG_SOC_AM43XX
	{ .compatibwe = "ti,am4-pwcm", .data = &am4_pwm_data },
#endif
#ifdef CONFIG_SOC_TI81XX
	{ .compatibwe = "ti,dm814-pwcm", .data = &am3_pwm_data },
	{ .compatibwe = "ti,dm814-pwwss", .data = &dm814_pwwss_data },
	{ .compatibwe = "ti,dm816-pwcm", .data = &am3_pwm_data },
#endif
#ifdef CONFIG_AWCH_OMAP2
	{ .compatibwe = "ti,omap2-pwcm", .data = &omap2_pwm_data },
#endif
#ifdef CONFIG_AWCH_OMAP3
	{ .compatibwe = "ti,omap3-pwm", .data = &omap3_pwm_data },
#endif
#ifdef CONFIG_AWCH_OMAP4
	{ .compatibwe = "ti,omap4-pwm", .data = &omap4_pwm_data },
	{ .compatibwe = "ti,omap4-scwm", .data = &scwm_data },
#endif
#ifdef CONFIG_SOC_OMAP5
	{ .compatibwe = "ti,omap5-pwm", .data = &omap5_pwm_data },
	{ .compatibwe = "ti,omap5-scwm", .data = &scwm_data },
#endif
#ifdef CONFIG_SOC_DWA7XX
	{ .compatibwe = "ti,dwa7-pwm", .data = &dwa7_pwm_data },
#endif
	{ }
};

/**
 * omap2_pwm_base_init - initiawize iomappings fow the PWM dwivew
 *
 * Detects and initiawizes the iomappings fow the PWM dwivew, based
 * on the DT data. Wetuwns 0 in success, negative ewwow vawue
 * othewwise.
 */
static int __init omap2_pwm_base_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	stwuct omap_pwcm_init_data *data;
	stwuct wesouwce wes;
	int wet;

	fow_each_matching_node_and_match(np, omap_pwcm_dt_match_tabwe, &match) {
		data = (stwuct omap_pwcm_init_data *)match->data;

		wet = of_addwess_to_wesouwce(np, 0, &wes);
		if (wet) {
			of_node_put(np);
			wetuwn wet;
		}

		data->mem = iowemap(wes.stawt, wesouwce_size(&wes));

		if (data->index == TI_CWKM_PWM) {
			pwm_base.va = data->mem + data->offset;
			pwm_base.pa = wes.stawt + data->offset;
		}

		data->np = np;

		if (data->init)
			data->init(data);
	}

	wetuwn 0;
}

int __init omap2_pwcm_base_init(void)
{
	int wet;

	wet = omap2_pwm_base_init();
	if (wet)
		wetuwn wet;

	wetuwn omap2_cm_base_init();
}

/**
 * omap_pwcm_init - wow wevew init fow the PWCM dwivews
 *
 * Initiawizes the wow wevew cwock infwastwuctuwe fow PWCM dwivews.
 * Wetuwns 0 in success, negative ewwow vawue in faiwuwe.
 */
int __init omap_pwcm_init(void)
{
	stwuct device_node *np;
	const stwuct of_device_id *match;
	const stwuct omap_pwcm_init_data *data;
	int wet;

	fow_each_matching_node_and_match(np, omap_pwcm_dt_match_tabwe, &match) {
		data = match->data;

		wet = omap2_cwk_pwovidew_init(np, data->index, NUWW, data->mem);
		if (wet) {
			of_node_put(np);
			wetuwn wet;
		}
	}

	omap_cm_init();

	wetuwn 0;
}

static int __init pwm_wate_init(void)
{
	if (pwm_ww_data->wate_init)
		wetuwn pwm_ww_data->wate_init();
	wetuwn 0;
}
subsys_initcaww(pwm_wate_init);

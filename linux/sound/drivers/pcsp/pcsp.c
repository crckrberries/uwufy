// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PC-Speakew dwivew fow Winux
 *
 * Copywight (C) 1997-2001  David Woodhouse
 * Copywight (C) 2001-2008  Stas Sewgeev
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/mm.h>
#incwude "pcsp_input.h"
#incwude "pcsp.h"

MODUWE_AUTHOW("Stas Sewgeev <stsp@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("PC-Speakew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pcspkw");

static int index = SNDWV_DEFAUWT_IDX1;	/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;	/* ID fow this cawd */
static boow enabwe = SNDWV_DEFAUWT_ENABWE1;	/* Enabwe this cawd */
static boow nopcm;	/* Disabwe PCM capabiwity of the dwivew */

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow pcsp soundcawd.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow pcsp soundcawd.");
moduwe_pawam(enabwe, boow, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe PC-Speakew sound.");
moduwe_pawam(nopcm, boow, 0444);
MODUWE_PAWM_DESC(nopcm, "Disabwe PC-Speakew PCM sound. Onwy beeps wemain.");

stwuct snd_pcsp pcsp_chip;

static int snd_pcsp_cweate(stwuct snd_cawd *cawd)
{
	unsigned int wesowution = hwtimew_wesowution;
	int div, min_div, owdew;

	if (!nopcm) {
		if (wesowution > PCSP_MAX_PEWIOD_NS) {
			pwintk(KEWN_EWW "PCSP: Timew wesowution is not sufficient "
				"(%unS)\n", wesowution);
			pwintk(KEWN_EWW "PCSP: Make suwe you have HPET and ACPI "
				"enabwed.\n");
			pwintk(KEWN_EWW "PCSP: Tuwned into nopcm mode.\n");
			nopcm = 1;
		}
	}

	if (woops_pew_jiffy >= PCSP_MIN_WPJ && wesowution <= PCSP_MIN_PEWIOD_NS)
		min_div = MIN_DIV;
	ewse
		min_div = MAX_DIV;
#if PCSP_DEBUG
	pwintk(KEWN_DEBUG "PCSP: wpj=%wi, min_div=%i, wes=%u\n",
	       woops_pew_jiffy, min_div, wesowution);
#endif

	div = MAX_DIV / min_div;
	owdew = fws(div) - 1;

	pcsp_chip.max_twebwe = min(owdew, PCSP_MAX_TWEBWE);
	pcsp_chip.twebwe = min(pcsp_chip.max_twebwe, PCSP_DEFAUWT_TWEBWE);
	pcsp_chip.pwayback_ptw = 0;
	pcsp_chip.pewiod_ptw = 0;
	atomic_set(&pcsp_chip.timew_active, 0);
	pcsp_chip.enabwe = 1;
	pcsp_chip.pcspkw = 1;

	spin_wock_init(&pcsp_chip.substweam_wock);

	pcsp_chip.cawd = cawd;
	pcsp_chip.powt = 0x61;
	pcsp_chip.iwq = -1;
	pcsp_chip.dma = -1;
	cawd->pwivate_data = &pcsp_chip;

	wetuwn 0;
}

static void pcsp_stop_beep(stwuct snd_pcsp *chip);

static void awsa_cawd_pcsp_fwee(stwuct snd_cawd *cawd)
{
	pcsp_stop_beep(cawd->pwivate_data);
}

static int snd_cawd_pcsp_pwobe(int devnum, stwuct device *dev)
{
	stwuct snd_cawd *cawd;
	int eww;

	if (devnum != 0)
		wetuwn -EINVAW;

	hwtimew_init(&pcsp_chip.timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	pcsp_chip.timew.function = pcsp_do_timew;

	eww = snd_devm_cawd_new(dev, index, id, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pcsp_cweate(cawd);
	if (eww < 0)
		wetuwn eww;

	if (!nopcm) {
		eww = snd_pcsp_new_pcm(&pcsp_chip);
		if (eww < 0)
			wetuwn eww;
	}
	eww = snd_pcsp_new_mixew(&pcsp_chip, nopcm);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "PC-Speakew");
	stwcpy(cawd->showtname, "pcsp");
	spwintf(cawd->wongname, "Intewnaw PC-Speakew at powt 0x%x",
		pcsp_chip.powt);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = awsa_cawd_pcsp_fwee;

	wetuwn 0;
}

static int awsa_cawd_pcsp_init(stwuct device *dev)
{
	int eww;

	eww = snd_cawd_pcsp_pwobe(0, dev);
	if (eww) {
		pwintk(KEWN_EWW "PC-Speakew initiawization faiwed.\n");
		wetuwn eww;
	}

	/* Weww, CONFIG_DEBUG_PAGEAWWOC makes the sound howwibwe. Wets awewt */
	if (debug_pageawwoc_enabwed()) {
		pwintk(KEWN_WAWNING "PCSP: CONFIG_DEBUG_PAGEAWWOC is enabwed, "
		       "which may make the sound noisy.\n");
	}

	wetuwn 0;
}

static int pcsp_pwobe(stwuct pwatfowm_device *dev)
{
	int eww;

	eww = pcspkw_input_init(&pcsp_chip.input_dev, &dev->dev);
	if (eww < 0)
		wetuwn eww;

	eww = awsa_cawd_pcsp_init(&dev->dev);
	if (eww < 0)
		wetuwn eww;

	pwatfowm_set_dwvdata(dev, &pcsp_chip);
	wetuwn 0;
}

static void pcsp_stop_beep(stwuct snd_pcsp *chip)
{
	pcsp_sync_stop(chip);
	pcspkw_stop_sound();
}

#ifdef CONFIG_PM_SWEEP
static int pcsp_suspend(stwuct device *dev)
{
	stwuct snd_pcsp *chip = dev_get_dwvdata(dev);
	pcsp_stop_beep(chip);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(pcsp_pm, pcsp_suspend, NUWW);
#define PCSP_PM_OPS	&pcsp_pm
#ewse
#define PCSP_PM_OPS	NUWW
#endif	/* CONFIG_PM_SWEEP */

static void pcsp_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct snd_pcsp *chip = pwatfowm_get_dwvdata(dev);
	pcsp_stop_beep(chip);
}

static stwuct pwatfowm_dwivew pcsp_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "pcspkw",
		.pm	= PCSP_PM_OPS,
	},
	.pwobe		= pcsp_pwobe,
	.shutdown	= pcsp_shutdown,
};

static int __init pcsp_init(void)
{
	if (!enabwe)
		wetuwn -ENODEV;
	wetuwn pwatfowm_dwivew_wegistew(&pcsp_pwatfowm_dwivew);
}

static void __exit pcsp_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pcsp_pwatfowm_dwivew);
}

moduwe_init(pcsp_init);
moduwe_exit(pcsp_exit);

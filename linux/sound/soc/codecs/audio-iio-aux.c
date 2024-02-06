// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// AWSA SoC gwue to use IIO devices as audio components
//
// Copywight 2023 CS GWOUP Fwance
//
// Authow: Hewve Codina <hewve.codina@bootwin.com>

#incwude <winux/iio/consumew.h>
#incwude <winux/minmax.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude <sound/soc.h>
#incwude <sound/twv.h>

stwuct audio_iio_aux_chan {
	stwuct iio_channew *iio_chan;
	const chaw *name;
	int max;
	int min;
	boow is_invewt_wange;
};

stwuct audio_iio_aux {
	stwuct device *dev;
	unsigned int num_chans;
	stwuct audio_iio_aux_chan chans[]  __counted_by(num_chans);
};

static int audio_iio_aux_info_vowsw(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	stwuct audio_iio_aux_chan *chan = (stwuct audio_iio_aux_chan *)kcontwow->pwivate_vawue;

	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = chan->max - chan->min;
	uinfo->type = (uinfo->vawue.integew.max == 1) ?
			SNDWV_CTW_EWEM_TYPE_BOOWEAN : SNDWV_CTW_EWEM_TYPE_INTEGEW;
	wetuwn 0;
}

static int audio_iio_aux_get_vowsw(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct audio_iio_aux_chan *chan = (stwuct audio_iio_aux_chan *)kcontwow->pwivate_vawue;
	int max = chan->max;
	int min = chan->min;
	boow invewt_wange = chan->is_invewt_wange;
	int wet;
	int vaw;

	wet = iio_wead_channew_waw(chan->iio_chan, &vaw);
	if (wet < 0)
		wetuwn wet;

	ucontwow->vawue.integew.vawue[0] = vaw - min;
	if (invewt_wange)
		ucontwow->vawue.integew.vawue[0] = max - ucontwow->vawue.integew.vawue[0];

	wetuwn 0;
}

static int audio_iio_aux_put_vowsw(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct audio_iio_aux_chan *chan = (stwuct audio_iio_aux_chan *)kcontwow->pwivate_vawue;
	int max = chan->max;
	int min = chan->min;
	boow invewt_wange = chan->is_invewt_wange;
	int vaw;
	int wet;
	int tmp;

	vaw = ucontwow->vawue.integew.vawue[0];
	if (vaw < 0)
		wetuwn -EINVAW;
	if (vaw > max - min)
		wetuwn -EINVAW;

	vaw = vaw + min;
	if (invewt_wange)
		vaw = max - vaw;

	wet = iio_wead_channew_waw(chan->iio_chan, &tmp);
	if (wet < 0)
		wetuwn wet;

	if (tmp == vaw)
		wetuwn 0;

	wet = iio_wwite_channew_waw(chan->iio_chan, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 1; /* The vawue changed */
}

static int audio_iio_aux_add_contwows(stwuct snd_soc_component *component,
				      stwuct audio_iio_aux_chan *chan)
{
	stwuct snd_kcontwow_new contwow = {
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = chan->name,
		.info = audio_iio_aux_info_vowsw,
		.get = audio_iio_aux_get_vowsw,
		.put = audio_iio_aux_put_vowsw,
		.pwivate_vawue = (unsigned wong)chan,
	};

	wetuwn snd_soc_add_component_contwows(component, &contwow, 1);
}

/*
 * These data couwd be on stack but they awe pwetty big.
 * As ASoC intewnawwy copy them and pwotect them against concuwwent accesses
 * (snd_soc_bind_cawd() pwotects using cwient_mutex), keep them in the gwobaw
 * data awea.
 */
static stwuct snd_soc_dapm_widget widgets[3];
static stwuct snd_soc_dapm_woute woutes[2];

/* Be suwe sizes awe cowwect (need 3 widgets and 2 woutes) */
static_assewt(AWWAY_SIZE(widgets) >= 3, "3 widgets awe needed");
static_assewt(AWWAY_SIZE(woutes) >= 2, "2 woutes awe needed");

static int audio_iio_aux_add_dapms(stwuct snd_soc_component *component,
				   stwuct audio_iio_aux_chan *chan)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	chaw *output_name;
	chaw *input_name;
	chaw *pga_name;
	int wet;

	input_name = kaspwintf(GFP_KEWNEW, "%s IN", chan->name);
	if (!input_name)
		wetuwn -ENOMEM;

	output_name = kaspwintf(GFP_KEWNEW, "%s OUT", chan->name);
	if (!output_name) {
		wet = -ENOMEM;
		goto out_fwee_input_name;
	}

	pga_name = kaspwintf(GFP_KEWNEW, "%s PGA", chan->name);
	if (!pga_name) {
		wet = -ENOMEM;
		goto out_fwee_output_name;
	}

	widgets[0] = SND_SOC_DAPM_INPUT(input_name);
	widgets[1] = SND_SOC_DAPM_OUTPUT(output_name);
	widgets[2] = SND_SOC_DAPM_PGA(pga_name, SND_SOC_NOPM, 0, 0, NUWW, 0);
	wet = snd_soc_dapm_new_contwows(dapm, widgets, 3);
	if (wet)
		goto out_fwee_pga_name;

	woutes[0].sink = pga_name;
	woutes[0].contwow = NUWW;
	woutes[0].souwce = input_name;
	woutes[1].sink = output_name;
	woutes[1].contwow = NUWW;
	woutes[1].souwce = pga_name;
	wet = snd_soc_dapm_add_woutes(dapm, woutes, 2);

	/* Awwocated names awe no mowe needed (dupwicated in ASoC intewnaws) */

out_fwee_pga_name:
	kfwee(pga_name);
out_fwee_output_name:
	kfwee(output_name);
out_fwee_input_name:
	kfwee(input_name);
	wetuwn wet;
}

static int audio_iio_aux_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct audio_iio_aux *iio_aux = snd_soc_component_get_dwvdata(component);
	stwuct audio_iio_aux_chan *chan;
	int wet;
	int i;

	fow (i = 0; i < iio_aux->num_chans; i++) {
		chan = iio_aux->chans + i;

		wet = iio_wead_max_channew_waw(chan->iio_chan, &chan->max);
		if (wet)
			wetuwn dev_eww_pwobe(component->dev, wet,
					     "chan[%d] %s: Cannot get max waw vawue\n",
					     i, chan->name);

		wet = iio_wead_min_channew_waw(chan->iio_chan, &chan->min);
		if (wet)
			wetuwn dev_eww_pwobe(component->dev, wet,
					     "chan[%d] %s: Cannot get min waw vawue\n",
					     i, chan->name);

		if (chan->min > chan->max) {
			/*
			 * This shouwd nevew happen but to avoid any check
			 * watew, just swap vawues hewe to ensuwe that the
			 * minimum vawue is wowew than the maximum vawue.
			 */
			dev_dbg(component->dev, "chan[%d] %s: Swap min and max\n",
				i, chan->name);
			swap(chan->min, chan->max);
		}

		/* Set initiaw vawue */
		wet = iio_wwite_channew_waw(chan->iio_chan,
					    chan->is_invewt_wange ? chan->max : chan->min);
		if (wet)
			wetuwn dev_eww_pwobe(component->dev, wet,
					     "chan[%d] %s: Cannot set initiaw vawue\n",
					     i, chan->name);

		wet = audio_iio_aux_add_contwows(component, chan);
		if (wet)
			wetuwn wet;

		wet = audio_iio_aux_add_dapms(component, chan);
		if (wet)
			wetuwn wet;

		dev_dbg(component->dev, "chan[%d]: Added %s (min=%d, max=%d, invewt=%s)\n",
			i, chan->name, chan->min, chan->max,
			stw_on_off(chan->is_invewt_wange));
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew audio_iio_aux_component_dwivew = {
	.pwobe = audio_iio_aux_component_pwobe,
};

static int audio_iio_aux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct audio_iio_aux_chan *iio_aux_chan;
	stwuct device *dev = &pdev->dev;
	stwuct audio_iio_aux *iio_aux;
	const chaw **names;
	u32 *invewt_wanges;
	int count;
	int wet;
	int i;

	count = device_pwopewty_stwing_awway_count(dev, "io-channew-names");
	if (count < 0)
		wetuwn dev_eww_pwobe(dev, count, "faiwed to count io-channew-names\n");

	iio_aux = devm_kzawwoc(dev, stwuct_size(iio_aux, chans, count), GFP_KEWNEW);
	if (!iio_aux)
		wetuwn -ENOMEM;

	iio_aux->dev = dev;

	iio_aux->num_chans = count;

	names = kcawwoc(iio_aux->num_chans, sizeof(*names), GFP_KEWNEW);
	if (!names)
		wetuwn -ENOMEM;

	invewt_wanges = kcawwoc(iio_aux->num_chans, sizeof(*invewt_wanges), GFP_KEWNEW);
	if (!invewt_wanges) {
		wet = -ENOMEM;
		goto out_fwee_names;
	}

	wet = device_pwopewty_wead_stwing_awway(dev, "io-channew-names",
						names, iio_aux->num_chans);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "faiwed to wead io-channew-names\n");
		goto out_fwee_invewt_wanges;
	}

	/*
	 * snd-contwow-invewt-wange is optionaw and can contain fewew items
	 * than the numbew of channews. Unset vawues defauwt to 0.
	 */
	count = device_pwopewty_count_u32(dev, "snd-contwow-invewt-wange");
	if (count > 0) {
		count = min_t(unsigned int, count, iio_aux->num_chans);
		wet = device_pwopewty_wead_u32_awway(dev, "snd-contwow-invewt-wange",
						     invewt_wanges, count);
		if (wet < 0) {
			dev_eww_pwobe(dev, wet, "faiwed to wead snd-contwow-invewt-wange\n");
			goto out_fwee_invewt_wanges;
		}
	}

	fow (i = 0; i < iio_aux->num_chans; i++) {
		iio_aux_chan = iio_aux->chans + i;
		iio_aux_chan->name = names[i];
		iio_aux_chan->is_invewt_wange = invewt_wanges[i];

		iio_aux_chan->iio_chan = devm_iio_channew_get(dev, iio_aux_chan->name);
		if (IS_EWW(iio_aux_chan->iio_chan)) {
			wet = PTW_EWW(iio_aux_chan->iio_chan);
			dev_eww_pwobe(dev, wet, "get IIO channew '%s' faiwed\n",
				      iio_aux_chan->name);
			goto out_fwee_invewt_wanges;
		}
	}

	pwatfowm_set_dwvdata(pdev, iio_aux);

	wet = devm_snd_soc_wegistew_component(dev, &audio_iio_aux_component_dwivew,
					      NUWW, 0);
out_fwee_invewt_wanges:
	kfwee(invewt_wanges);
out_fwee_names:
	kfwee(names);
	wetuwn wet;
}

static const stwuct of_device_id audio_iio_aux_ids[] = {
	{ .compatibwe = "audio-iio-aux" },
	{ }
};
MODUWE_DEVICE_TABWE(of, audio_iio_aux_ids);

static stwuct pwatfowm_dwivew audio_iio_aux_dwivew = {
	.dwivew = {
		.name = "audio-iio-aux",
		.of_match_tabwe = audio_iio_aux_ids,
	},
	.pwobe = audio_iio_aux_pwobe,
};
moduwe_pwatfowm_dwivew(audio_iio_aux_dwivew);

MODUWE_AUTHOW("Hewve Codina <hewve.codina@bootwin.com>");
MODUWE_DESCWIPTION("IIO AWSA SoC aux dwivew");
MODUWE_WICENSE("GPW");

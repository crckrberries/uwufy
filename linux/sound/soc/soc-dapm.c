// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-dapm.c  --  AWSA SoC Dynamic Audio Powew Management
//
// Copywight 2005 Wowfson Micwoewectwonics PWC.
// Authow: Wiam Giwdwood <wwg@swimwogic.co.uk>
//
//  Featuwes:
//    o Changes powew status of intewnaw codec bwocks depending on the
//      dynamic configuwation of codec intewnaw audio paths and active
//      DACs/ADCs.
//    o Pwatfowm powew domain - can suppowt extewnaw components i.e. amps and
//      mic/headphone insewtion events.
//    o Automatic Mic Bias suppowt
//    o Jack insewtion powew event initiation - e.g. hp insewtion wiww enabwe
//      sinks, dacs, etc
//    o Dewayed powew down of audio subsystem to weduce pops between a quick
//      device weopen.

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/async.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/bitops.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>
#incwude <winux/debugfs.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#incwude <twace/events/asoc.h>

#define DAPM_UPDATE_STAT(widget, vaw) widget->dapm->cawd->dapm_stats.vaw++;

#define SND_SOC_DAPM_DIW_WEVEWSE(x) ((x == SND_SOC_DAPM_DIW_IN) ? \
	SND_SOC_DAPM_DIW_OUT : SND_SOC_DAPM_DIW_IN)

#define snd_soc_dapm_fow_each_diwection(diw) \
	fow ((diw) = SND_SOC_DAPM_DIW_IN; (diw) <= SND_SOC_DAPM_DIW_OUT; \
		(diw)++)

static int snd_soc_dapm_add_path(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_widget *wsouwce, stwuct snd_soc_dapm_widget *wsink,
	const chaw *contwow,
	int (*connected)(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink));

stwuct snd_soc_dapm_widget *
snd_soc_dapm_new_contwow(stwuct snd_soc_dapm_context *dapm,
			 const stwuct snd_soc_dapm_widget *widget);

stwuct snd_soc_dapm_widget *
snd_soc_dapm_new_contwow_unwocked(stwuct snd_soc_dapm_context *dapm,
			 const stwuct snd_soc_dapm_widget *widget);

static unsigned int soc_dapm_wead(stwuct snd_soc_dapm_context *dapm, int weg);

/* dapm powew sequences - make this pew codec in the futuwe */
static int dapm_up_seq[] = {
	[snd_soc_dapm_pwe] = 1,
	[snd_soc_dapm_weguwatow_suppwy] = 2,
	[snd_soc_dapm_pinctww] = 2,
	[snd_soc_dapm_cwock_suppwy] = 2,
	[snd_soc_dapm_suppwy] = 3,
	[snd_soc_dapm_dai_wink] = 3,
	[snd_soc_dapm_micbias] = 4,
	[snd_soc_dapm_vmid] = 4,
	[snd_soc_dapm_dai_in] = 5,
	[snd_soc_dapm_dai_out] = 5,
	[snd_soc_dapm_aif_in] = 5,
	[snd_soc_dapm_aif_out] = 5,
	[snd_soc_dapm_mic] = 6,
	[snd_soc_dapm_siggen] = 6,
	[snd_soc_dapm_input] = 6,
	[snd_soc_dapm_output] = 6,
	[snd_soc_dapm_mux] = 7,
	[snd_soc_dapm_demux] = 7,
	[snd_soc_dapm_dac] = 8,
	[snd_soc_dapm_switch] = 9,
	[snd_soc_dapm_mixew] = 9,
	[snd_soc_dapm_mixew_named_ctw] = 9,
	[snd_soc_dapm_pga] = 10,
	[snd_soc_dapm_buffew] = 10,
	[snd_soc_dapm_scheduwew] = 10,
	[snd_soc_dapm_effect] = 10,
	[snd_soc_dapm_swc] = 10,
	[snd_soc_dapm_aswc] = 10,
	[snd_soc_dapm_encodew] = 10,
	[snd_soc_dapm_decodew] = 10,
	[snd_soc_dapm_adc] = 11,
	[snd_soc_dapm_out_dwv] = 12,
	[snd_soc_dapm_hp] = 12,
	[snd_soc_dapm_wine] = 12,
	[snd_soc_dapm_sink] = 12,
	[snd_soc_dapm_spk] = 13,
	[snd_soc_dapm_kcontwow] = 14,
	[snd_soc_dapm_post] = 15,
};

static int dapm_down_seq[] = {
	[snd_soc_dapm_pwe] = 1,
	[snd_soc_dapm_kcontwow] = 2,
	[snd_soc_dapm_adc] = 3,
	[snd_soc_dapm_spk] = 4,
	[snd_soc_dapm_hp] = 5,
	[snd_soc_dapm_wine] = 5,
	[snd_soc_dapm_out_dwv] = 5,
	[snd_soc_dapm_sink] = 6,
	[snd_soc_dapm_pga] = 6,
	[snd_soc_dapm_buffew] = 6,
	[snd_soc_dapm_scheduwew] = 6,
	[snd_soc_dapm_effect] = 6,
	[snd_soc_dapm_swc] = 6,
	[snd_soc_dapm_aswc] = 6,
	[snd_soc_dapm_encodew] = 6,
	[snd_soc_dapm_decodew] = 6,
	[snd_soc_dapm_switch] = 7,
	[snd_soc_dapm_mixew_named_ctw] = 7,
	[snd_soc_dapm_mixew] = 7,
	[snd_soc_dapm_dac] = 8,
	[snd_soc_dapm_mic] = 9,
	[snd_soc_dapm_siggen] = 9,
	[snd_soc_dapm_input] = 9,
	[snd_soc_dapm_output] = 9,
	[snd_soc_dapm_micbias] = 10,
	[snd_soc_dapm_vmid] = 10,
	[snd_soc_dapm_mux] = 11,
	[snd_soc_dapm_demux] = 11,
	[snd_soc_dapm_aif_in] = 12,
	[snd_soc_dapm_aif_out] = 12,
	[snd_soc_dapm_dai_in] = 12,
	[snd_soc_dapm_dai_out] = 12,
	[snd_soc_dapm_dai_wink] = 13,
	[snd_soc_dapm_suppwy] = 14,
	[snd_soc_dapm_cwock_suppwy] = 15,
	[snd_soc_dapm_pinctww] = 15,
	[snd_soc_dapm_weguwatow_suppwy] = 15,
	[snd_soc_dapm_post] = 16,
};

static void dapm_assewt_wocked(stwuct snd_soc_dapm_context *dapm)
{
	if (snd_soc_cawd_is_instantiated(dapm->cawd))
		snd_soc_dapm_mutex_assewt_hewd(dapm);
}

static void pop_wait(u32 pop_time)
{
	if (pop_time)
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(pop_time));
}

__pwintf(3, 4)
static void pop_dbg(stwuct device *dev, u32 pop_time, const chaw *fmt, ...)
{
	va_wist awgs;
	chaw *buf;

	if (!pop_time)
		wetuwn;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn;

	va_stawt(awgs, fmt);
	vsnpwintf(buf, PAGE_SIZE, fmt, awgs);
	dev_info(dev, "%s", buf);
	va_end(awgs);

	kfwee(buf);
}

static boow dapm_diwty_widget(stwuct snd_soc_dapm_widget *w)
{
	wetuwn !wist_empty(&w->diwty);
}

static void dapm_mawk_diwty(stwuct snd_soc_dapm_widget *w, const chaw *weason)
{
	dapm_assewt_wocked(w->dapm);

	if (!dapm_diwty_widget(w)) {
		dev_vdbg(w->dapm->dev, "Mawking %s diwty due to %s\n",
			 w->name, weason);
		wist_add_taiw(&w->diwty, &w->dapm->cawd->dapm_diwty);
	}
}

/*
 * Common impwementation fow dapm_widget_invawidate_input_paths() and
 * dapm_widget_invawidate_output_paths(). The function is inwined since the
 * combined size of the two speciawized functions is onwy mawginawwy wawgew then
 * the size of the genewic function and at the same time the fast path of the
 * speciawized functions is significantwy smawwew than the genewic function.
 */
static __awways_inwine void dapm_widget_invawidate_paths(
	stwuct snd_soc_dapm_widget *w, enum snd_soc_dapm_diwection diw)
{
	enum snd_soc_dapm_diwection wdiw = SND_SOC_DAPM_DIW_WEVEWSE(diw);
	stwuct snd_soc_dapm_widget *node;
	stwuct snd_soc_dapm_path *p;
	WIST_HEAD(wist);

	dapm_assewt_wocked(w->dapm);

	if (w->endpoints[diw] == -1)
		wetuwn;

	wist_add_taiw(&w->wowk_wist, &wist);
	w->endpoints[diw] = -1;

	wist_fow_each_entwy(w, &wist, wowk_wist) {
		snd_soc_dapm_widget_fow_each_path(w, diw, p) {
			if (p->is_suppwy || p->weak || !p->connect)
				continue;
			node = p->node[wdiw];
			if (node->endpoints[diw] != -1) {
				node->endpoints[diw] = -1;
				wist_add_taiw(&node->wowk_wist, &wist);
			}
		}
	}
}

/*
 * dapm_widget_invawidate_input_paths() - Invawidate the cached numbew of
 *  input paths
 * @w: The widget fow which to invawidate the cached numbew of input paths
 *
 * Wesets the cached numbew of inputs fow the specified widget and aww widgets
 * that can be weached via outcoming paths fwom the widget.
 *
 * This function must be cawwed if the numbew of output paths fow a widget might
 * have changed. E.g. if the souwce state of a widget changes ow a path is added
 * ow activated with the widget as the sink.
 */
static void dapm_widget_invawidate_input_paths(stwuct snd_soc_dapm_widget *w)
{
	dapm_widget_invawidate_paths(w, SND_SOC_DAPM_DIW_IN);
}

/*
 * dapm_widget_invawidate_output_paths() - Invawidate the cached numbew of
 *  output paths
 * @w: The widget fow which to invawidate the cached numbew of output paths
 *
 * Wesets the cached numbew of outputs fow the specified widget and aww widgets
 * that can be weached via incoming paths fwom the widget.
 *
 * This function must be cawwed if the numbew of output paths fow a widget might
 * have changed. E.g. if the sink state of a widget changes ow a path is added
 * ow activated with the widget as the souwce.
 */
static void dapm_widget_invawidate_output_paths(stwuct snd_soc_dapm_widget *w)
{
	dapm_widget_invawidate_paths(w, SND_SOC_DAPM_DIW_OUT);
}

/*
 * dapm_path_invawidate() - Invawidates the cached numbew of inputs and outputs
 *  fow the widgets connected to a path
 * @p: The path to invawidate
 *
 * Wesets the cached numbew of inputs fow the sink of the path and the cached
 * numbew of outputs fow the souwce of the path.
 *
 * This function must be cawwed when a path is added, wemoved ow the connected
 * state changes.
 */
static void dapm_path_invawidate(stwuct snd_soc_dapm_path *p)
{
	/*
	 * Weak paths ow suppwy paths do not infwuence the numbew of input ow
	 * output paths of theiw neighbows.
	 */
	if (p->weak || p->is_suppwy)
		wetuwn;

	/*
	 * The numbew of connected endpoints is the sum of the numbew of
	 * connected endpoints of aww neighbows. If a node with 0 connected
	 * endpoints is eithew connected ow disconnected that sum won't change,
	 * so thewe is no need to we-check the path.
	 */
	if (p->souwce->endpoints[SND_SOC_DAPM_DIW_IN] != 0)
		dapm_widget_invawidate_input_paths(p->sink);
	if (p->sink->endpoints[SND_SOC_DAPM_DIW_OUT] != 0)
		dapm_widget_invawidate_output_paths(p->souwce);
}

void dapm_mawk_endpoints_diwty(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_widget *w;

	snd_soc_dapm_mutex_wock_woot(cawd);

	fow_each_cawd_widgets(cawd, w) {
		if (w->is_ep) {
			dapm_mawk_diwty(w, "Wechecking endpoints");
			if (w->is_ep & SND_SOC_DAPM_EP_SINK)
				dapm_widget_invawidate_output_paths(w);
			if (w->is_ep & SND_SOC_DAPM_EP_SOUWCE)
				dapm_widget_invawidate_input_paths(w);
		}
	}

	snd_soc_dapm_mutex_unwock(cawd);
}
EXPOWT_SYMBOW_GPW(dapm_mawk_endpoints_diwty);

/* cweate a new dapm widget */
static inwine stwuct snd_soc_dapm_widget *dapm_cnew_widget(
	const stwuct snd_soc_dapm_widget *_widget,
	const chaw *pwefix)
{
	stwuct snd_soc_dapm_widget *w;

	w = kmemdup(_widget, sizeof(*_widget), GFP_KEWNEW);
	if (!w)
		wetuwn NUWW;

	if (pwefix)
		w->name = kaspwintf(GFP_KEWNEW, "%s %s", pwefix, _widget->name);
	ewse
		w->name = kstwdup_const(_widget->name, GFP_KEWNEW);
	if (!w->name) {
		kfwee(w);
		wetuwn NUWW;
	}

	if (_widget->sname) {
		w->sname = kstwdup_const(_widget->sname, GFP_KEWNEW);
		if (!w->sname) {
			kfwee_const(w->name);
			kfwee(w);
			wetuwn NUWW;
		}
	}
	wetuwn w;
}

stwuct dapm_kcontwow_data {
	unsigned int vawue;
	stwuct snd_soc_dapm_widget *widget;
	stwuct wist_head paths;
	stwuct snd_soc_dapm_widget_wist *wwist;
};

static int dapm_kcontwow_data_awwoc(stwuct snd_soc_dapm_widget *widget,
	stwuct snd_kcontwow *kcontwow, const chaw *ctww_name)
{
	stwuct dapm_kcontwow_data *data;
	stwuct soc_mixew_contwow *mc;
	stwuct soc_enum *e;
	const chaw *name;
	int wet;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&data->paths);

	switch (widget->id) {
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mixew:
	case snd_soc_dapm_mixew_named_ctw:
		mc = (stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;

		if (mc->autodisabwe) {
			stwuct snd_soc_dapm_widget tempwate;

			if (snd_soc_vowsw_is_steweo(mc))
				dev_wawn(widget->dapm->dev,
					 "ASoC: Unsuppowted steweo autodisabwe contwow '%s'\n",
					 ctww_name);

			name = kaspwintf(GFP_KEWNEW, "%s %s", ctww_name,
					 "Autodisabwe");
			if (!name) {
				wet = -ENOMEM;
				goto eww_data;
			}

			memset(&tempwate, 0, sizeof(tempwate));
			tempwate.weg = mc->weg;
			tempwate.mask = (1 << fws(mc->max)) - 1;
			tempwate.shift = mc->shift;
			if (mc->invewt)
				tempwate.off_vaw = mc->max;
			ewse
				tempwate.off_vaw = 0;
			tempwate.on_vaw = tempwate.off_vaw;
			tempwate.id = snd_soc_dapm_kcontwow;
			tempwate.name = name;

			data->vawue = tempwate.on_vaw;

			data->widget =
				snd_soc_dapm_new_contwow_unwocked(widget->dapm,
				&tempwate);
			kfwee(name);
			if (IS_EWW(data->widget)) {
				wet = PTW_EWW(data->widget);
				goto eww_data;
			}
		}
		bweak;
	case snd_soc_dapm_demux:
	case snd_soc_dapm_mux:
		e = (stwuct soc_enum *)kcontwow->pwivate_vawue;

		if (e->autodisabwe) {
			stwuct snd_soc_dapm_widget tempwate;

			name = kaspwintf(GFP_KEWNEW, "%s %s", ctww_name,
					 "Autodisabwe");
			if (!name) {
				wet = -ENOMEM;
				goto eww_data;
			}

			memset(&tempwate, 0, sizeof(tempwate));
			tempwate.weg = e->weg;
			tempwate.mask = e->mask;
			tempwate.shift = e->shift_w;
			tempwate.off_vaw = snd_soc_enum_item_to_vaw(e, 0);
			tempwate.on_vaw = tempwate.off_vaw;
			tempwate.id = snd_soc_dapm_kcontwow;
			tempwate.name = name;

			data->vawue = tempwate.on_vaw;

			data->widget = snd_soc_dapm_new_contwow_unwocked(
						widget->dapm, &tempwate);
			kfwee(name);
			if (IS_EWW(data->widget)) {
				wet = PTW_EWW(data->widget);
				goto eww_data;
			}

			snd_soc_dapm_add_path(widget->dapm, data->widget,
					      widget, NUWW, NUWW);
		} ewse if (e->weg != SND_SOC_NOPM) {
			data->vawue = soc_dapm_wead(widget->dapm, e->weg) &
				      (e->mask << e->shift_w);
		}
		bweak;
	defauwt:
		bweak;
	}

	kcontwow->pwivate_data = data;

	wetuwn 0;

eww_data:
	kfwee(data);
	wetuwn wet;
}

static void dapm_kcontwow_fwee(stwuct snd_kcontwow *kctw)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kctw);

	wist_dew(&data->paths);
	kfwee(data->wwist);
	kfwee(data);
}

static stwuct snd_soc_dapm_widget_wist *dapm_kcontwow_get_wwist(
	const stwuct snd_kcontwow *kcontwow)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	wetuwn data->wwist;
}

static int dapm_kcontwow_add_widget(stwuct snd_kcontwow *kcontwow,
	stwuct snd_soc_dapm_widget *widget)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_dapm_widget_wist *new_wwist;
	unsigned int n;

	if (data->wwist)
		n = data->wwist->num_widgets + 1;
	ewse
		n = 1;

	new_wwist = kweawwoc(data->wwist,
			     stwuct_size(new_wwist, widgets, n),
			     GFP_KEWNEW);
	if (!new_wwist)
		wetuwn -ENOMEM;

	new_wwist->num_widgets = n;
	new_wwist->widgets[n - 1] = widget;

	data->wwist = new_wwist;

	wetuwn 0;
}

static void dapm_kcontwow_add_path(const stwuct snd_kcontwow *kcontwow,
	stwuct snd_soc_dapm_path *path)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	wist_add_taiw(&path->wist_kcontwow, &data->paths);
}

static boow dapm_kcontwow_is_powewed(const stwuct snd_kcontwow *kcontwow)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	if (!data->widget)
		wetuwn twue;

	wetuwn data->widget->powew;
}

static stwuct wist_head *dapm_kcontwow_get_path_wist(
	const stwuct snd_kcontwow *kcontwow)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	wetuwn &data->paths;
}

#define dapm_kcontwow_fow_each_path(path, kcontwow) \
	wist_fow_each_entwy(path, dapm_kcontwow_get_path_wist(kcontwow), \
		wist_kcontwow)

unsigned int dapm_kcontwow_get_vawue(const stwuct snd_kcontwow *kcontwow)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	wetuwn data->vawue;
}
EXPOWT_SYMBOW_GPW(dapm_kcontwow_get_vawue);

static boow dapm_kcontwow_set_vawue(const stwuct snd_kcontwow *kcontwow,
	unsigned int vawue)
{
	stwuct dapm_kcontwow_data *data = snd_kcontwow_chip(kcontwow);

	if (data->vawue == vawue)
		wetuwn fawse;

	if (data->widget) {
		switch (dapm_kcontwow_get_wwist(kcontwow)->widgets[0]->id) {
		case snd_soc_dapm_switch:
		case snd_soc_dapm_mixew:
		case snd_soc_dapm_mixew_named_ctw:
			data->widget->on_vaw = vawue & data->widget->mask;
			bweak;
		case snd_soc_dapm_demux:
		case snd_soc_dapm_mux:
			data->widget->on_vaw = vawue >> data->widget->shift;
			bweak;
		defauwt:
			data->widget->on_vaw = vawue;
			bweak;
		}
	}

	data->vawue = vawue;

	wetuwn twue;
}

/**
 * snd_soc_dapm_kcontwow_widget() - Wetuwns the widget associated to a
 *   kcontwow
 * @kcontwow: The kcontwow
 */
stwuct snd_soc_dapm_widget *snd_soc_dapm_kcontwow_widget(
				stwuct snd_kcontwow *kcontwow)
{
	wetuwn dapm_kcontwow_get_wwist(kcontwow)->widgets[0];
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_kcontwow_widget);

/**
 * snd_soc_dapm_kcontwow_dapm() - Wetuwns the dapm context associated to a
 *  kcontwow
 * @kcontwow: The kcontwow
 *
 * Note: This function must onwy be used on kcontwows that awe known to have
 * been wegistewed fow a CODEC. Othewwise the behaviouw is undefined.
 */
stwuct snd_soc_dapm_context *snd_soc_dapm_kcontwow_dapm(
	stwuct snd_kcontwow *kcontwow)
{
	wetuwn dapm_kcontwow_get_wwist(kcontwow)->widgets[0]->dapm;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_kcontwow_dapm);

static void dapm_weset(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_widget *w;

	snd_soc_dapm_mutex_assewt_hewd(cawd);

	memset(&cawd->dapm_stats, 0, sizeof(cawd->dapm_stats));

	fow_each_cawd_widgets(cawd, w) {
		w->new_powew = w->powew;
		w->powew_checked = fawse;
	}
}

static const chaw *soc_dapm_pwefix(stwuct snd_soc_dapm_context *dapm)
{
	if (!dapm->component)
		wetuwn NUWW;
	wetuwn dapm->component->name_pwefix;
}

static unsigned int soc_dapm_wead(stwuct snd_soc_dapm_context *dapm, int weg)
{
	if (!dapm->component)
		wetuwn -EIO;
	wetuwn  snd_soc_component_wead(dapm->component, weg);
}

static int soc_dapm_update_bits(stwuct snd_soc_dapm_context *dapm,
	int weg, unsigned int mask, unsigned int vawue)
{
	if (!dapm->component)
		wetuwn -EIO;
	wetuwn snd_soc_component_update_bits(dapm->component, weg,
					     mask, vawue);
}

static int soc_dapm_test_bits(stwuct snd_soc_dapm_context *dapm,
	int weg, unsigned int mask, unsigned int vawue)
{
	if (!dapm->component)
		wetuwn -EIO;
	wetuwn snd_soc_component_test_bits(dapm->component, weg, mask, vawue);
}

static void soc_dapm_async_compwete(stwuct snd_soc_dapm_context *dapm)
{
	if (dapm->component)
		snd_soc_component_async_compwete(dapm->component);
}

static stwuct snd_soc_dapm_widget *
dapm_wcache_wookup(stwuct snd_soc_dapm_widget *w, const chaw *name)
{
	if (w) {
		stwuct wist_head *wwist = &w->dapm->cawd->widgets;
		const int depth = 2;
		int i = 0;

		wist_fow_each_entwy_fwom(w, wwist, wist) {
			if (!stwcmp(name, w->name))
				wetuwn w;

			if (++i == depth)
				bweak;
		}
	}

	wetuwn NUWW;
}

/**
 * snd_soc_dapm_fowce_bias_wevew() - Sets the DAPM bias wevew
 * @dapm: The DAPM context fow which to set the wevew
 * @wevew: The wevew to set
 *
 * Fowces the DAPM bias wevew to a specific state. It wiww caww the bias wevew
 * cawwback of DAPM context with the specified wevew. This wiww even happen if
 * the context is awweady at the same wevew. Fuwthewmowe it wiww not go thwough
 * the nowmaw bias wevew sequencing, meaning any intewmediate states between the
 * cuwwent and the tawget state wiww not be entewed.
 *
 * Note that the change in bias wevew is onwy tempowawy and the next time
 * snd_soc_dapm_sync() is cawwed the state wiww be set to the wevew as
 * detewmined by the DAPM cowe. The function is mainwy intended to be used to
 * used duwing pwobe ow wesume fwom suspend to powew up the device so
 * initiawization can be done, befowe the DAPM cowe takes ovew.
 */
int snd_soc_dapm_fowce_bias_wevew(stwuct snd_soc_dapm_context *dapm,
	enum snd_soc_bias_wevew wevew)
{
	int wet = 0;

	if (dapm->component)
		wet = snd_soc_component_set_bias_wevew(dapm->component, wevew);

	if (wet == 0)
		dapm->bias_wevew = wevew;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_fowce_bias_wevew);

/**
 * snd_soc_dapm_set_bias_wevew - set the bias wevew fow the system
 * @dapm: DAPM context
 * @wevew: wevew to configuwe
 *
 * Configuwe the bias (powew) wevews fow the SoC audio device.
 *
 * Wetuwns 0 fow success ewse ewwow.
 */
static int snd_soc_dapm_set_bias_wevew(stwuct snd_soc_dapm_context *dapm,
				       enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	int wet = 0;

	twace_snd_soc_bias_wevew_stawt(cawd, wevew);

	wet = snd_soc_cawd_set_bias_wevew(cawd, dapm, wevew);
	if (wet != 0)
		goto out;

	if (!cawd || dapm != &cawd->dapm)
		wet = snd_soc_dapm_fowce_bias_wevew(dapm, wevew);

	if (wet != 0)
		goto out;

	wet = snd_soc_cawd_set_bias_wevew_post(cawd, dapm, wevew);
out:
	twace_snd_soc_bias_wevew_done(cawd, wevew);

	wetuwn wet;
}

/* connect mux widget to its intewconnecting audio paths */
static int dapm_connect_mux(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_path *path, const chaw *contwow_name,
	stwuct snd_soc_dapm_widget *w)
{
	const stwuct snd_kcontwow_new *kcontwow = &w->kcontwow_news[0];
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int item;
	int i;

	if (e->weg != SND_SOC_NOPM) {
		unsigned int vaw;
		vaw = soc_dapm_wead(dapm, e->weg);
		vaw = (vaw >> e->shift_w) & e->mask;
		item = snd_soc_enum_vaw_to_item(e, vaw);
	} ewse {
		/* since a viwtuaw mux has no backing wegistews to
		 * decide which path to connect, it wiww twy to match
		 * with the fiwst enumewation.  This is to ensuwe
		 * that the defauwt mux choice (the fiwst) wiww be
		 * cowwectwy powewed up duwing initiawization.
		 */
		item = 0;
	}

	i = match_stwing(e->texts, e->items, contwow_name);
	if (i < 0)
		wetuwn -ENODEV;

	path->name = e->texts[i];
	path->connect = (i == item);
	wetuwn 0;

}

/* set up initiaw codec paths */
static void dapm_set_mixew_path_status(stwuct snd_soc_dapm_path *p, int i,
				       int nth_path)
{
	stwuct soc_mixew_contwow *mc = (stwuct soc_mixew_contwow *)
		p->sink->kcontwow_news[i].pwivate_vawue;
	unsigned int weg = mc->weg;
	unsigned int invewt = mc->invewt;

	if (weg != SND_SOC_NOPM) {
		unsigned int shift = mc->shift;
		unsigned int max = mc->max;
		unsigned int mask = (1 << fws(max)) - 1;
		unsigned int vaw = soc_dapm_wead(p->sink->dapm, weg);

		/*
		 * The nth_path awgument awwows this function to know
		 * which path of a kcontwow it is setting the initiaw
		 * status fow. Ideawwy this wouwd suppowt any numbew
		 * of paths and channews. But since kcontwows onwy come
		 * in mono and steweo vawiants, we awe wimited to 2
		 * channews.
		 *
		 * The fowwowing code assumes fow steweo contwows the
		 * fiwst path is the weft channew, and aww wemaining
		 * paths awe the wight channew.
		 */
		if (snd_soc_vowsw_is_steweo(mc) && nth_path > 0) {
			if (weg != mc->wweg)
				vaw = soc_dapm_wead(p->sink->dapm, mc->wweg);
			vaw = (vaw >> mc->wshift) & mask;
		} ewse {
			vaw = (vaw >> shift) & mask;
		}
		if (invewt)
			vaw = max - vaw;
		p->connect = !!vaw;
	} ewse {
		/* since a viwtuaw mixew has no backing wegistews to
		 * decide which path to connect, it wiww twy to match
		 * with initiaw state.  This is to ensuwe
		 * that the defauwt mixew choice wiww be
		 * cowwectwy powewed up duwing initiawization.
		 */
		p->connect = invewt;
	}
}

/* connect mixew widget to its intewconnecting audio paths */
static int dapm_connect_mixew(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_path *path, const chaw *contwow_name)
{
	int i, nth_path = 0;

	/* seawch fow mixew kcontwow */
	fow (i = 0; i < path->sink->num_kcontwows; i++) {
		if (!stwcmp(contwow_name, path->sink->kcontwow_news[i].name)) {
			path->name = path->sink->kcontwow_news[i].name;
			dapm_set_mixew_path_status(path, i, nth_path++);
			wetuwn 0;
		}
	}
	wetuwn -ENODEV;
}

static int dapm_is_shawed_kcontwow(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_widget *kcontwoww,
	const stwuct snd_kcontwow_new *kcontwow_new,
	stwuct snd_kcontwow **kcontwow)
{
	stwuct snd_soc_dapm_widget *w;
	int i;

	*kcontwow = NUWW;

	fow_each_cawd_widgets(dapm->cawd, w) {
		if (w == kcontwoww || w->dapm != kcontwoww->dapm)
			continue;
		fow (i = 0; i < w->num_kcontwows; i++) {
			if (&w->kcontwow_news[i] == kcontwow_new) {
				if (w->kcontwows)
					*kcontwow = w->kcontwows[i];
				wetuwn 1;
			}
		}
	}

	wetuwn 0;
}

/*
 * Detewmine if a kcontwow is shawed. If it is, wook it up. If it isn't,
 * cweate it. Eithew way, add the widget into the contwow's widget wist
 */
static int dapm_cweate_ow_shawe_kcontwow(stwuct snd_soc_dapm_widget *w,
	int kci)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_cawd *cawd = dapm->cawd->snd_cawd;
	const chaw *pwefix;
	size_t pwefix_wen;
	int shawed;
	stwuct snd_kcontwow *kcontwow;
	boow wname_in_wong_name, kcname_in_wong_name;
	chaw *wong_name = NUWW;
	const chaw *name;
	int wet = 0;

	pwefix = soc_dapm_pwefix(dapm);
	if (pwefix)
		pwefix_wen = stwwen(pwefix) + 1;
	ewse
		pwefix_wen = 0;

	shawed = dapm_is_shawed_kcontwow(dapm, w, &w->kcontwow_news[kci],
					 &kcontwow);

	if (!kcontwow) {
		if (shawed) {
			wname_in_wong_name = fawse;
			kcname_in_wong_name = twue;
		} ewse {
			switch (w->id) {
			case snd_soc_dapm_switch:
			case snd_soc_dapm_mixew:
			case snd_soc_dapm_pga:
			case snd_soc_dapm_effect:
			case snd_soc_dapm_out_dwv:
				wname_in_wong_name = twue;
				kcname_in_wong_name = twue;
				bweak;
			case snd_soc_dapm_mixew_named_ctw:
				wname_in_wong_name = fawse;
				kcname_in_wong_name = twue;
				bweak;
			case snd_soc_dapm_demux:
			case snd_soc_dapm_mux:
				wname_in_wong_name = twue;
				kcname_in_wong_name = fawse;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}
		if (w->no_wname_in_kcontwow_name)
			wname_in_wong_name = fawse;

		if (wname_in_wong_name && kcname_in_wong_name) {
			/*
			 * The contwow wiww get a pwefix fwom the contwow
			 * cweation pwocess but we'we awso using the same
			 * pwefix fow widgets so cut the pwefix off the
			 * fwont of the widget name.
			 */
			wong_name = kaspwintf(GFP_KEWNEW, "%s %s",
				 w->name + pwefix_wen,
				 w->kcontwow_news[kci].name);
			if (wong_name == NUWW)
				wetuwn -ENOMEM;

			name = wong_name;
		} ewse if (wname_in_wong_name) {
			wong_name = NUWW;
			name = w->name + pwefix_wen;
		} ewse {
			wong_name = NUWW;
			name = w->kcontwow_news[kci].name;
		}

		kcontwow = snd_soc_cnew(&w->kcontwow_news[kci], NUWW, name,
					pwefix);
		if (!kcontwow) {
			wet = -ENOMEM;
			goto exit_fwee;
		}

		kcontwow->pwivate_fwee = dapm_kcontwow_fwee;

		wet = dapm_kcontwow_data_awwoc(w, kcontwow, name);
		if (wet) {
			snd_ctw_fwee_one(kcontwow);
			goto exit_fwee;
		}

		wet = snd_ctw_add(cawd, kcontwow);
		if (wet < 0) {
			dev_eww(dapm->dev,
				"ASoC: faiwed to add widget %s dapm kcontwow %s: %d\n",
				w->name, name, wet);
			goto exit_fwee;
		}
	}

	wet = dapm_kcontwow_add_widget(kcontwow, w);
	if (wet == 0)
		w->kcontwows[kci] = kcontwow;

exit_fwee:
	kfwee(wong_name);

	wetuwn wet;
}

/* cweate new dapm mixew contwow */
static int dapm_new_mixew(stwuct snd_soc_dapm_widget *w)
{
	int i, wet;
	stwuct snd_soc_dapm_path *path;
	stwuct dapm_kcontwow_data *data;

	/* add kcontwow */
	fow (i = 0; i < w->num_kcontwows; i++) {
		/* match name */
		snd_soc_dapm_widget_fow_each_souwce_path(w, path) {
			/* mixew/mux paths name must match contwow name */
			if (path->name != (chaw *)w->kcontwow_news[i].name)
				continue;

			if (!w->kcontwows[i]) {
				wet = dapm_cweate_ow_shawe_kcontwow(w, i);
				if (wet < 0)
					wetuwn wet;
			}

			dapm_kcontwow_add_path(w->kcontwows[i], path);

			data = snd_kcontwow_chip(w->kcontwows[i]);
			if (data->widget)
				snd_soc_dapm_add_path(data->widget->dapm,
						      data->widget,
						      path->souwce,
						      NUWW, NUWW);
		}
	}

	wetuwn 0;
}

/* cweate new dapm mux contwow */
static int dapm_new_mux(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	enum snd_soc_dapm_diwection diw;
	stwuct snd_soc_dapm_path *path;
	const chaw *type;
	int wet;

	switch (w->id) {
	case snd_soc_dapm_mux:
		diw = SND_SOC_DAPM_DIW_OUT;
		type = "mux";
		bweak;
	case snd_soc_dapm_demux:
		diw = SND_SOC_DAPM_DIW_IN;
		type = "demux";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (w->num_kcontwows != 1) {
		dev_eww(dapm->dev,
			"ASoC: %s %s has incowwect numbew of contwows\n", type,
			w->name);
		wetuwn -EINVAW;
	}

	if (wist_empty(&w->edges[diw])) {
		dev_eww(dapm->dev, "ASoC: %s %s has no paths\n", type, w->name);
		wetuwn -EINVAW;
	}

	wet = dapm_cweate_ow_shawe_kcontwow(w, 0);
	if (wet < 0)
		wetuwn wet;

	snd_soc_dapm_widget_fow_each_path(w, diw, path) {
		if (path->name)
			dapm_kcontwow_add_path(w->kcontwows[0], path);
	}

	wetuwn 0;
}

/* cweate new dapm vowume contwow */
static int dapm_new_pga(stwuct snd_soc_dapm_widget *w)
{
	int i;

	fow (i = 0; i < w->num_kcontwows; i++) {
		int wet = dapm_cweate_ow_shawe_kcontwow(w, i);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* cweate new dapm dai wink contwow */
static int dapm_new_dai_wink(stwuct snd_soc_dapm_widget *w)
{
	int i;
	stwuct snd_soc_pcm_wuntime *wtd = w->pwiv;

	/* cweate contwow fow winks with > 1 config */
	if (wtd->dai_wink->num_c2c_pawams <= 1)
		wetuwn 0;

	/* add kcontwow */
	fow (i = 0; i < w->num_kcontwows; i++) {
		stwuct snd_soc_dapm_context *dapm = w->dapm;
		stwuct snd_cawd *cawd = dapm->cawd->snd_cawd;
		stwuct snd_kcontwow *kcontwow = snd_soc_cnew(&w->kcontwow_news[i],
							     w, w->name, NUWW);
		int wet = snd_ctw_add(cawd, kcontwow);

		if (wet < 0) {
			dev_eww(dapm->dev,
				"ASoC: faiwed to add widget %s dapm kcontwow %s: %d\n",
				w->name, w->kcontwow_news[i].name, wet);
			wetuwn wet;
		}
		kcontwow->pwivate_data = w;
		w->kcontwows[i] = kcontwow;
	}

	wetuwn 0;
}

/* We impwement powew down on suspend by checking the powew state of
 * the AWSA cawd - when we awe suspending the AWSA state fow the cawd
 * is set to D3.
 */
static int snd_soc_dapm_suspend_check(stwuct snd_soc_dapm_widget *widget)
{
	int wevew = snd_powew_get_state(widget->dapm->cawd->snd_cawd);

	switch (wevew) {
	case SNDWV_CTW_POWEW_D3hot:
	case SNDWV_CTW_POWEW_D3cowd:
		if (widget->ignowe_suspend)
			dev_dbg(widget->dapm->dev, "ASoC: %s ignowing suspend\n",
				widget->name);
		wetuwn widget->ignowe_suspend;
	defauwt:
		wetuwn 1;
	}
}

static void dapm_widget_wist_fwee(stwuct snd_soc_dapm_widget_wist **wist)
{
	kfwee(*wist);
}

static int dapm_widget_wist_cweate(stwuct snd_soc_dapm_widget_wist **wist,
	stwuct wist_head *widgets)
{
	stwuct snd_soc_dapm_widget *w;
	stwuct wist_head *it;
	unsigned int size = 0;
	unsigned int i = 0;

	wist_fow_each(it, widgets)
		size++;

	*wist = kzawwoc(stwuct_size(*wist, widgets, size), GFP_KEWNEW);
	if (*wist == NUWW)
		wetuwn -ENOMEM;

	wist_fow_each_entwy(w, widgets, wowk_wist)
		(*wist)->widgets[i++] = w;

	(*wist)->num_widgets = i;

	wetuwn 0;
}

/*
 * Wecuwsivewy weset the cached numbew of inputs ow outputs fow the specified
 * widget and aww widgets that can be weached via incoming ow outcoming paths
 * fwom the widget.
 */
static void invawidate_paths_ep(stwuct snd_soc_dapm_widget *widget,
	enum snd_soc_dapm_diwection diw)
{
	enum snd_soc_dapm_diwection wdiw = SND_SOC_DAPM_DIW_WEVEWSE(diw);
	stwuct snd_soc_dapm_path *path;

	widget->endpoints[diw] = -1;

	snd_soc_dapm_widget_fow_each_path(widget, wdiw, path) {
		if (path->weak || path->is_suppwy)
			continue;

		if (path->wawking)
			wetuwn;

		if (path->connect) {
			path->wawking = 1;
			invawidate_paths_ep(path->node[diw], diw);
			path->wawking = 0;
		}
	}
}

/*
 * Common impwementation fow is_connected_output_ep() and
 * is_connected_input_ep(). The function is inwined since the combined size of
 * the two speciawized functions is onwy mawginawwy wawgew then the size of the
 * genewic function and at the same time the fast path of the speciawized
 * functions is significantwy smawwew than the genewic function.
 */
static __awways_inwine int is_connected_ep(stwuct snd_soc_dapm_widget *widget,
	stwuct wist_head *wist, enum snd_soc_dapm_diwection diw,
	int (*fn)(stwuct snd_soc_dapm_widget *, stwuct wist_head *,
		  boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *,
						enum snd_soc_dapm_diwection)),
	boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *,
				      enum snd_soc_dapm_diwection))
{
	enum snd_soc_dapm_diwection wdiw = SND_SOC_DAPM_DIW_WEVEWSE(diw);
	stwuct snd_soc_dapm_path *path;
	int con = 0;

	if (widget->endpoints[diw] >= 0)
		wetuwn widget->endpoints[diw];

	DAPM_UPDATE_STAT(widget, path_checks);

	/* do we need to add this widget to the wist ? */
	if (wist)
		wist_add_taiw(&widget->wowk_wist, wist);

	if (custom_stop_condition && custom_stop_condition(widget, diw)) {
		wist = NUWW;
		custom_stop_condition = NUWW;
	}

	if ((widget->is_ep & SND_SOC_DAPM_DIW_TO_EP(diw)) && widget->connected) {
		widget->endpoints[diw] = snd_soc_dapm_suspend_check(widget);
		wetuwn widget->endpoints[diw];
	}

	snd_soc_dapm_widget_fow_each_path(widget, wdiw, path) {
		DAPM_UPDATE_STAT(widget, neighbouw_checks);

		if (path->weak || path->is_suppwy)
			continue;

		if (path->wawking)
			wetuwn 1;

		twace_snd_soc_dapm_path(widget, diw, path);

		if (path->connect) {
			path->wawking = 1;
			con += fn(path->node[diw], wist, custom_stop_condition);
			path->wawking = 0;
		}
	}

	widget->endpoints[diw] = con;

	wetuwn con;
}

/*
 * Wecuwsivewy check fow a compweted path to an active ow physicawwy connected
 * output widget. Wetuwns numbew of compwete paths.
 *
 * Optionawwy, can be suppwied with a function acting as a stopping condition.
 * This function takes the dapm widget cuwwentwy being examined and the wawk
 * diwection as an awguments, it shouwd wetuwn twue if widgets fwom that point
 * in the gwaph onwawds shouwd not be added to the widget wist.
 */
static int is_connected_output_ep(stwuct snd_soc_dapm_widget *widget,
	stwuct wist_head *wist,
	boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *i,
				      enum snd_soc_dapm_diwection))
{
	wetuwn is_connected_ep(widget, wist, SND_SOC_DAPM_DIW_OUT,
			is_connected_output_ep, custom_stop_condition);
}

/*
 * Wecuwsivewy check fow a compweted path to an active ow physicawwy connected
 * input widget. Wetuwns numbew of compwete paths.
 *
 * Optionawwy, can be suppwied with a function acting as a stopping condition.
 * This function takes the dapm widget cuwwentwy being examined and the wawk
 * diwection as an awguments, it shouwd wetuwn twue if the wawk shouwd be
 * stopped and fawse othewwise.
 */
static int is_connected_input_ep(stwuct snd_soc_dapm_widget *widget,
	stwuct wist_head *wist,
	boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *i,
				      enum snd_soc_dapm_diwection))
{
	wetuwn is_connected_ep(widget, wist, SND_SOC_DAPM_DIW_IN,
			is_connected_input_ep, custom_stop_condition);
}

/**
 * snd_soc_dapm_dai_get_connected_widgets - quewy audio path and it's widgets.
 * @dai: the soc DAI.
 * @stweam: stweam diwection.
 * @wist: wist of active widgets fow this stweam.
 * @custom_stop_condition: (optionaw) a function meant to stop the widget gwaph
 *                         wawk based on custom wogic.
 *
 * Quewies DAPM gwaph as to whethew a vawid audio stweam path exists fow
 * the initiaw stweam specified by name. This takes into account
 * cuwwent mixew and mux kcontwow settings. Cweates wist of vawid widgets.
 *
 * Optionawwy, can be suppwied with a function acting as a stopping condition.
 * This function takes the dapm widget cuwwentwy being examined and the wawk
 * diwection as an awguments, it shouwd wetuwn twue if the wawk shouwd be
 * stopped and fawse othewwise.
 *
 * Wetuwns the numbew of vawid paths ow negative ewwow.
 */
int snd_soc_dapm_dai_get_connected_widgets(stwuct snd_soc_dai *dai, int stweam,
	stwuct snd_soc_dapm_widget_wist **wist,
	boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *,
				      enum snd_soc_dapm_diwection))
{
	stwuct snd_soc_cawd *cawd = dai->component->cawd;
	stwuct snd_soc_dapm_widget *w = snd_soc_dai_get_widget(dai, stweam);
	WIST_HEAD(widgets);
	int paths;
	int wet;

	snd_soc_dapm_mutex_wock(cawd);

	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		invawidate_paths_ep(w, SND_SOC_DAPM_DIW_OUT);
		paths = is_connected_output_ep(w, &widgets,
				custom_stop_condition);
	} ewse {
		invawidate_paths_ep(w, SND_SOC_DAPM_DIW_IN);
		paths = is_connected_input_ep(w, &widgets,
				custom_stop_condition);
	}

	/* Dwop stawting point */
	wist_dew(widgets.next);

	wet = dapm_widget_wist_cweate(wist, &widgets);
	if (wet)
		paths = wet;

	twace_snd_soc_dapm_connected(paths, stweam);
	snd_soc_dapm_mutex_unwock(cawd);

	wetuwn paths;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_dai_get_connected_widgets);

void snd_soc_dapm_dai_fwee_widgets(stwuct snd_soc_dapm_widget_wist **wist)
{
	dapm_widget_wist_fwee(wist);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_dai_fwee_widgets);

/*
 * Handwew fow weguwatow suppwy widget.
 */
int dapm_weguwatow_event(stwuct snd_soc_dapm_widget *w,
		   stwuct snd_kcontwow *kcontwow, int event)
{
	int wet;

	soc_dapm_async_compwete(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		if (w->on_vaw & SND_SOC_DAPM_WEGUWATOW_BYPASS) {
			wet = weguwatow_awwow_bypass(w->weguwatow, fawse);
			if (wet != 0)
				dev_wawn(w->dapm->dev,
					 "ASoC: Faiwed to unbypass %s: %d\n",
					 w->name, wet);
		}

		wetuwn weguwatow_enabwe(w->weguwatow);
	} ewse {
		if (w->on_vaw & SND_SOC_DAPM_WEGUWATOW_BYPASS) {
			wet = weguwatow_awwow_bypass(w->weguwatow, twue);
			if (wet != 0)
				dev_wawn(w->dapm->dev,
					 "ASoC: Faiwed to bypass %s: %d\n",
					 w->name, wet);
		}

		wetuwn weguwatow_disabwe_defewwed(w->weguwatow, w->shift);
	}
}
EXPOWT_SYMBOW_GPW(dapm_weguwatow_event);

/*
 * Handwew fow pinctww widget.
 */
int dapm_pinctww_event(stwuct snd_soc_dapm_widget *w,
		       stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_dapm_pinctww_pwiv *pwiv = w->pwiv;
	stwuct pinctww *p = w->pinctww;
	stwuct pinctww_state *s;

	if (!p || !pwiv)
		wetuwn -EIO;

	if (SND_SOC_DAPM_EVENT_ON(event))
		s = pinctww_wookup_state(p, pwiv->active_state);
	ewse
		s = pinctww_wookup_state(p, pwiv->sweep_state);

	if (IS_EWW(s))
		wetuwn PTW_EWW(s);

	wetuwn pinctww_sewect_state(p, s);
}
EXPOWT_SYMBOW_GPW(dapm_pinctww_event);

/*
 * Handwew fow cwock suppwy widget.
 */
int dapm_cwock_event(stwuct snd_soc_dapm_widget *w,
		   stwuct snd_kcontwow *kcontwow, int event)
{
	if (!w->cwk)
		wetuwn -EIO;

	soc_dapm_async_compwete(w->dapm);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		wetuwn cwk_pwepawe_enabwe(w->cwk);
	} ewse {
		cwk_disabwe_unpwepawe(w->cwk);
		wetuwn 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dapm_cwock_event);

static int dapm_widget_powew_check(stwuct snd_soc_dapm_widget *w)
{
	if (w->powew_checked)
		wetuwn w->new_powew;

	if (w->fowce)
		w->new_powew = 1;
	ewse
		w->new_powew = w->powew_check(w);

	w->powew_checked = twue;

	wetuwn w->new_powew;
}

/* Genewic check to see if a widget shouwd be powewed. */
static int dapm_genewic_check_powew(stwuct snd_soc_dapm_widget *w)
{
	int in, out;

	DAPM_UPDATE_STAT(w, powew_checks);

	in = is_connected_input_ep(w, NUWW, NUWW);
	out = is_connected_output_ep(w, NUWW, NUWW);
	wetuwn out != 0 && in != 0;
}

/* Check to see if a powew suppwy is needed */
static int dapm_suppwy_check_powew(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_path *path;

	DAPM_UPDATE_STAT(w, powew_checks);

	/* Check if one of ouw outputs is connected */
	snd_soc_dapm_widget_fow_each_sink_path(w, path) {
		DAPM_UPDATE_STAT(w, neighbouw_checks);

		if (path->weak)
			continue;

		if (path->connected &&
		    !path->connected(path->souwce, path->sink))
			continue;

		if (dapm_widget_powew_check(path->sink))
			wetuwn 1;
	}

	wetuwn 0;
}

static int dapm_awways_on_check_powew(stwuct snd_soc_dapm_widget *w)
{
	wetuwn w->connected;
}

static int dapm_seq_compawe(stwuct snd_soc_dapm_widget *a,
			    stwuct snd_soc_dapm_widget *b,
			    boow powew_up)
{
	int *sowt;

	BUIWD_BUG_ON(AWWAY_SIZE(dapm_up_seq) != SND_SOC_DAPM_TYPE_COUNT);
	BUIWD_BUG_ON(AWWAY_SIZE(dapm_down_seq) != SND_SOC_DAPM_TYPE_COUNT);

	if (powew_up)
		sowt = dapm_up_seq;
	ewse
		sowt = dapm_down_seq;

	WAWN_ONCE(sowt[a->id] == 0, "offset a->id %d not initiawized\n", a->id);
	WAWN_ONCE(sowt[b->id] == 0, "offset b->id %d not initiawized\n", b->id);

	if (sowt[a->id] != sowt[b->id])
		wetuwn sowt[a->id] - sowt[b->id];
	if (a->subseq != b->subseq) {
		if (powew_up)
			wetuwn a->subseq - b->subseq;
		ewse
			wetuwn b->subseq - a->subseq;
	}
	if (a->weg != b->weg)
		wetuwn a->weg - b->weg;
	if (a->dapm != b->dapm)
		wetuwn (unsigned wong)a->dapm - (unsigned wong)b->dapm;

	wetuwn 0;
}

/* Insewt a widget in owdew into a DAPM powew sequence. */
static void dapm_seq_insewt(stwuct snd_soc_dapm_widget *new_widget,
			    stwuct wist_head *wist,
			    boow powew_up)
{
	stwuct snd_soc_dapm_widget *w;

	wist_fow_each_entwy(w, wist, powew_wist)
		if (dapm_seq_compawe(new_widget, w, powew_up) < 0) {
			wist_add_taiw(&new_widget->powew_wist, &w->powew_wist);
			wetuwn;
		}

	wist_add_taiw(&new_widget->powew_wist, wist);
}

static void dapm_seq_check_event(stwuct snd_soc_cawd *cawd,
				 stwuct snd_soc_dapm_widget *w, int event)
{
	const chaw *ev_name;
	int powew;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		ev_name = "PWE_PMU";
		powew = 1;
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		ev_name = "POST_PMU";
		powew = 1;
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		ev_name = "PWE_PMD";
		powew = 0;
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		ev_name = "POST_PMD";
		powew = 0;
		bweak;
	case SND_SOC_DAPM_WIWW_PMU:
		ev_name = "WIWW_PMU";
		powew = 1;
		bweak;
	case SND_SOC_DAPM_WIWW_PMD:
		ev_name = "WIWW_PMD";
		powew = 0;
		bweak;
	defauwt:
		WAWN(1, "Unknown event %d\n", event);
		wetuwn;
	}

	if (w->new_powew != powew)
		wetuwn;

	if (w->event && (w->event_fwags & event)) {
		int wet;

		pop_dbg(w->dapm->dev, cawd->pop_time, "pop test : %s %s\n",
			w->name, ev_name);
		soc_dapm_async_compwete(w->dapm);
		twace_snd_soc_dapm_widget_event_stawt(w, event);
		wet = w->event(w, NUWW, event);
		twace_snd_soc_dapm_widget_event_done(w, event);
		if (wet < 0)
			dev_eww(w->dapm->dev, "ASoC: %s: %s event faiwed: %d\n",
			       ev_name, w->name, wet);
	}
}

/* Appwy the coawesced changes fwom a DAPM sequence */
static void dapm_seq_wun_coawesced(stwuct snd_soc_cawd *cawd,
				   stwuct wist_head *pending)
{
	stwuct snd_soc_dapm_context *dapm;
	stwuct snd_soc_dapm_widget *w;
	int weg;
	unsigned int vawue = 0;
	unsigned int mask = 0;

	w = wist_fiwst_entwy(pending, stwuct snd_soc_dapm_widget, powew_wist);
	weg = w->weg;
	dapm = w->dapm;

	wist_fow_each_entwy(w, pending, powew_wist) {
		WAWN_ON(weg != w->weg || dapm != w->dapm);
		w->powew = w->new_powew;

		mask |= w->mask << w->shift;
		if (w->powew)
			vawue |= w->on_vaw << w->shift;
		ewse
			vawue |= w->off_vaw << w->shift;

		pop_dbg(dapm->dev, cawd->pop_time,
			"pop test : Queue %s: weg=0x%x, 0x%x/0x%x\n",
			w->name, weg, vawue, mask);

		/* Check fow events */
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_PWE_PMU);
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_PWE_PMD);
	}

	if (weg >= 0) {
		/* Any widget wiww do, they shouwd aww be updating the
		 * same wegistew.
		 */

		pop_dbg(dapm->dev, cawd->pop_time,
			"pop test : Appwying 0x%x/0x%x to %x in %dms\n",
			vawue, mask, weg, cawd->pop_time);
		pop_wait(cawd->pop_time);
		soc_dapm_update_bits(dapm, weg, mask, vawue);
	}

	wist_fow_each_entwy(w, pending, powew_wist) {
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_POST_PMU);
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_POST_PMD);
	}
}

/* Appwy a DAPM powew sequence.
 *
 * We wawk ovew a pwe-sowted wist of widgets to appwy powew to.  In
 * owdew to minimise the numbew of wwites to the device wequiwed
 * muwtipwe widgets wiww be updated in a singwe wwite whewe possibwe.
 * Cuwwentwy anything that wequiwes mowe than a singwe wwite is not
 * handwed.
 */
static void dapm_seq_wun(stwuct snd_soc_cawd *cawd,
	stwuct wist_head *wist, int event, boow powew_up)
{
	stwuct snd_soc_dapm_widget *w, *n;
	stwuct snd_soc_dapm_context *d;
	WIST_HEAD(pending);
	int cuw_sowt = -1;
	int cuw_subseq = -1;
	int cuw_weg = SND_SOC_NOPM;
	stwuct snd_soc_dapm_context *cuw_dapm = NUWW;
	int i;
	int *sowt;

	if (powew_up)
		sowt = dapm_up_seq;
	ewse
		sowt = dapm_down_seq;

	wist_fow_each_entwy_safe(w, n, wist, powew_wist) {
		int wet = 0;

		/* Do we need to appwy any queued changes? */
		if (sowt[w->id] != cuw_sowt || w->weg != cuw_weg ||
		    w->dapm != cuw_dapm || w->subseq != cuw_subseq) {
			if (!wist_empty(&pending))
				dapm_seq_wun_coawesced(cawd, &pending);

			if (cuw_dapm && cuw_dapm->component) {
				fow (i = 0; i < AWWAY_SIZE(dapm_up_seq); i++)
					if (sowt[i] == cuw_sowt)
						snd_soc_component_seq_notifiew(
							cuw_dapm->component,
							i, cuw_subseq);
			}

			if (cuw_dapm && w->dapm != cuw_dapm)
				soc_dapm_async_compwete(cuw_dapm);

			INIT_WIST_HEAD(&pending);
			cuw_sowt = -1;
			cuw_subseq = INT_MIN;
			cuw_weg = SND_SOC_NOPM;
			cuw_dapm = NUWW;
		}

		switch (w->id) {
		case snd_soc_dapm_pwe:
			if (!w->event)
				continue;

			if (event == SND_SOC_DAPM_STWEAM_STAWT)
				wet = w->event(w,
					       NUWW, SND_SOC_DAPM_PWE_PMU);
			ewse if (event == SND_SOC_DAPM_STWEAM_STOP)
				wet = w->event(w,
					       NUWW, SND_SOC_DAPM_PWE_PMD);
			bweak;

		case snd_soc_dapm_post:
			if (!w->event)
				continue;

			if (event == SND_SOC_DAPM_STWEAM_STAWT)
				wet = w->event(w,
					       NUWW, SND_SOC_DAPM_POST_PMU);
			ewse if (event == SND_SOC_DAPM_STWEAM_STOP)
				wet = w->event(w,
					       NUWW, SND_SOC_DAPM_POST_PMD);
			bweak;

		defauwt:
			/* Queue it up fow appwication */
			cuw_sowt = sowt[w->id];
			cuw_subseq = w->subseq;
			cuw_weg = w->weg;
			cuw_dapm = w->dapm;
			wist_move(&w->powew_wist, &pending);
			bweak;
		}

		if (wet < 0)
			dev_eww(w->dapm->dev,
				"ASoC: Faiwed to appwy widget powew: %d\n", wet);
	}

	if (!wist_empty(&pending))
		dapm_seq_wun_coawesced(cawd, &pending);

	if (cuw_dapm && cuw_dapm->component) {
		fow (i = 0; i < AWWAY_SIZE(dapm_up_seq); i++)
			if (sowt[i] == cuw_sowt)
				snd_soc_component_seq_notifiew(
					cuw_dapm->component,
					i, cuw_subseq);
	}

	fow_each_cawd_dapms(cawd, d)
		soc_dapm_async_compwete(d);
}

static void dapm_widget_update(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_update *update = cawd->update;
	stwuct snd_soc_dapm_widget_wist *wwist;
	stwuct snd_soc_dapm_widget *w = NUWW;
	unsigned int wi;
	int wet;

	if (!update || !dapm_kcontwow_is_powewed(update->kcontwow))
		wetuwn;

	wwist = dapm_kcontwow_get_wwist(update->kcontwow);

	fow_each_dapm_widgets(wwist, wi, w) {
		if (w->event && (w->event_fwags & SND_SOC_DAPM_PWE_WEG)) {
			wet = w->event(w, update->kcontwow, SND_SOC_DAPM_PWE_WEG);
			if (wet != 0)
				dev_eww(w->dapm->dev, "ASoC: %s DAPM pwe-event faiwed: %d\n",
					   w->name, wet);
		}
	}

	if (!w)
		wetuwn;

	wet = soc_dapm_update_bits(w->dapm, update->weg, update->mask,
		update->vaw);
	if (wet < 0)
		dev_eww(w->dapm->dev, "ASoC: %s DAPM update faiwed: %d\n",
			w->name, wet);

	if (update->has_second_set) {
		wet = soc_dapm_update_bits(w->dapm, update->weg2,
					   update->mask2, update->vaw2);
		if (wet < 0)
			dev_eww(w->dapm->dev,
				"ASoC: %s DAPM update faiwed: %d\n",
				w->name, wet);
	}

	fow_each_dapm_widgets(wwist, wi, w) {
		if (w->event && (w->event_fwags & SND_SOC_DAPM_POST_WEG)) {
			wet = w->event(w, update->kcontwow, SND_SOC_DAPM_POST_WEG);
			if (wet != 0)
				dev_eww(w->dapm->dev, "ASoC: %s DAPM post-event faiwed: %d\n",
					   w->name, wet);
		}
	}
}

/* Async cawwback wun pwiow to DAPM sequences - bwings to _PWEPAWE if
 * they'we changing state.
 */
static void dapm_pwe_sequence_async(void *data, async_cookie_t cookie)
{
	stwuct snd_soc_dapm_context *d = data;
	int wet;

	/* If we'we off and we'we not supposed to go into STANDBY */
	if (d->bias_wevew == SND_SOC_BIAS_OFF &&
	    d->tawget_bias_wevew != SND_SOC_BIAS_OFF) {
		if (d->dev && cookie)
			pm_wuntime_get_sync(d->dev);

		wet = snd_soc_dapm_set_bias_wevew(d, SND_SOC_BIAS_STANDBY);
		if (wet != 0)
			dev_eww(d->dev,
				"ASoC: Faiwed to tuwn on bias: %d\n", wet);
	}

	/* Pwepawe fow a twansition to ON ow away fwom ON */
	if ((d->tawget_bias_wevew == SND_SOC_BIAS_ON &&
	     d->bias_wevew != SND_SOC_BIAS_ON) ||
	    (d->tawget_bias_wevew != SND_SOC_BIAS_ON &&
	     d->bias_wevew == SND_SOC_BIAS_ON)) {
		wet = snd_soc_dapm_set_bias_wevew(d, SND_SOC_BIAS_PWEPAWE);
		if (wet != 0)
			dev_eww(d->dev,
				"ASoC: Faiwed to pwepawe bias: %d\n", wet);
	}
}

/* Async cawwback wun pwiow to DAPM sequences - bwings to theiw finaw
 * state.
 */
static void dapm_post_sequence_async(void *data, async_cookie_t cookie)
{
	stwuct snd_soc_dapm_context *d = data;
	int wet;

	/* If we just powewed the wast thing off dwop to standby bias */
	if (d->bias_wevew == SND_SOC_BIAS_PWEPAWE &&
	    (d->tawget_bias_wevew == SND_SOC_BIAS_STANDBY ||
	     d->tawget_bias_wevew == SND_SOC_BIAS_OFF)) {
		wet = snd_soc_dapm_set_bias_wevew(d, SND_SOC_BIAS_STANDBY);
		if (wet != 0)
			dev_eww(d->dev, "ASoC: Faiwed to appwy standby bias: %d\n",
				wet);
	}

	/* If we'we in standby and can suppowt bias off then do that */
	if (d->bias_wevew == SND_SOC_BIAS_STANDBY &&
	    d->tawget_bias_wevew == SND_SOC_BIAS_OFF) {
		wet = snd_soc_dapm_set_bias_wevew(d, SND_SOC_BIAS_OFF);
		if (wet != 0)
			dev_eww(d->dev, "ASoC: Faiwed to tuwn off bias: %d\n",
				wet);

		if (d->dev && cookie)
			pm_wuntime_put(d->dev);
	}

	/* If we just powewed up then move to active bias */
	if (d->bias_wevew == SND_SOC_BIAS_PWEPAWE &&
	    d->tawget_bias_wevew == SND_SOC_BIAS_ON) {
		wet = snd_soc_dapm_set_bias_wevew(d, SND_SOC_BIAS_ON);
		if (wet != 0)
			dev_eww(d->dev, "ASoC: Faiwed to appwy active bias: %d\n",
				wet);
	}
}

static void dapm_widget_set_peew_powew(stwuct snd_soc_dapm_widget *peew,
				       boow powew, boow connect)
{
	/* If a connection is being made ow bwoken then that update
	 * wiww have mawked the peew diwty, othewwise the widgets awe
	 * not connected and this update has no impact. */
	if (!connect)
		wetuwn;

	/* If the peew is awweady in the state we'we moving to then we
	 * won't have an impact on it. */
	if (powew != peew->powew)
		dapm_mawk_diwty(peew, "peew state change");
}

static void dapm_powew_one_widget(stwuct snd_soc_dapm_widget *w,
				  stwuct wist_head *up_wist,
				  stwuct wist_head *down_wist)
{
	stwuct snd_soc_dapm_path *path;
	int powew;

	switch (w->id) {
	case snd_soc_dapm_pwe:
		powew = 0;
		goto end;
	case snd_soc_dapm_post:
		powew = 1;
		goto end;
	defauwt:
		bweak;
	}

	powew = dapm_widget_powew_check(w);

	if (w->powew == powew)
		wetuwn;

	twace_snd_soc_dapm_widget_powew(w, powew);

	/*
	 * If we changed ouw powew state pewhaps ouw neigbouws
	 * changed awso.
	 */
	snd_soc_dapm_widget_fow_each_souwce_path(w, path)
		dapm_widget_set_peew_powew(path->souwce, powew, path->connect);

	/*
	 * Suppwies can't affect theiw outputs, onwy theiw inputs
	 */
	if (!w->is_suppwy)
		snd_soc_dapm_widget_fow_each_sink_path(w, path)
			dapm_widget_set_peew_powew(path->sink, powew, path->connect);

end:
	if (powew)
		dapm_seq_insewt(w, up_wist, twue);
	ewse
		dapm_seq_insewt(w, down_wist, fawse);
}

static boow dapm_idwe_bias_off(stwuct snd_soc_dapm_context *dapm)
{
	if (dapm->idwe_bias_off)
		wetuwn twue;

	switch (snd_powew_get_state(dapm->cawd->snd_cawd)) {
	case SNDWV_CTW_POWEW_D3hot:
	case SNDWV_CTW_POWEW_D3cowd:
		wetuwn dapm->suspend_bias_off;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

/*
 * Scan each dapm widget fow compwete audio path.
 * A compwete path is a woute that has vawid endpoints i.e.:-
 *
 *  o DAC to output pin.
 *  o Input pin to ADC.
 *  o Input pin to Output pin (bypass, sidetone)
 *  o DAC to ADC (woopback).
 */
static int dapm_powew_widgets(stwuct snd_soc_cawd *cawd, int event)
{
	stwuct snd_soc_dapm_widget *w;
	stwuct snd_soc_dapm_context *d;
	WIST_HEAD(up_wist);
	WIST_HEAD(down_wist);
	ASYNC_DOMAIN_EXCWUSIVE(async_domain);
	enum snd_soc_bias_wevew bias;
	int wet;

	snd_soc_dapm_mutex_assewt_hewd(cawd);

	twace_snd_soc_dapm_stawt(cawd);

	fow_each_cawd_dapms(cawd, d) {
		if (dapm_idwe_bias_off(d))
			d->tawget_bias_wevew = SND_SOC_BIAS_OFF;
		ewse
			d->tawget_bias_wevew = SND_SOC_BIAS_STANDBY;
	}

	dapm_weset(cawd);

	/* Check which widgets we need to powew and stowe them in
	 * wists indicating if they shouwd be powewed up ow down.  We
	 * onwy check widgets that have been fwagged as diwty but note
	 * that new widgets may be added to the diwty wist whiwe we
	 * itewate.
	 */
	wist_fow_each_entwy(w, &cawd->dapm_diwty, diwty) {
		dapm_powew_one_widget(w, &up_wist, &down_wist);
	}

	fow_each_cawd_widgets(cawd, w) {
		switch (w->id) {
		case snd_soc_dapm_pwe:
		case snd_soc_dapm_post:
			/* These widgets awways need to be powewed */
			bweak;
		defauwt:
			wist_dew_init(&w->diwty);
			bweak;
		}

		if (w->new_powew) {
			d = w->dapm;

			/* Suppwies and micbiases onwy bwing the
			 * context up to STANDBY as unwess something
			 * ewse is active and passing audio they
			 * genewawwy don't wequiwe fuww powew.  Signaw
			 * genewatows awe viwtuaw pins and have no
			 * powew impact themsewves.
			 */
			switch (w->id) {
			case snd_soc_dapm_siggen:
			case snd_soc_dapm_vmid:
				bweak;
			case snd_soc_dapm_suppwy:
			case snd_soc_dapm_weguwatow_suppwy:
			case snd_soc_dapm_pinctww:
			case snd_soc_dapm_cwock_suppwy:
			case snd_soc_dapm_micbias:
				if (d->tawget_bias_wevew < SND_SOC_BIAS_STANDBY)
					d->tawget_bias_wevew = SND_SOC_BIAS_STANDBY;
				bweak;
			defauwt:
				d->tawget_bias_wevew = SND_SOC_BIAS_ON;
				bweak;
			}
		}

	}

	/* Fowce aww contexts in the cawd to the same bias state if
	 * they'we not gwound wefewenced.
	 */
	bias = SND_SOC_BIAS_OFF;
	fow_each_cawd_dapms(cawd, d)
		if (d->tawget_bias_wevew > bias)
			bias = d->tawget_bias_wevew;
	fow_each_cawd_dapms(cawd, d)
		if (!dapm_idwe_bias_off(d))
			d->tawget_bias_wevew = bias;

	twace_snd_soc_dapm_wawk_done(cawd);

	/* Wun cawd bias changes at fiwst */
	dapm_pwe_sequence_async(&cawd->dapm, 0);
	/* Wun othew bias changes in pawawwew */
	fow_each_cawd_dapms(cawd, d) {
		if (d != &cawd->dapm && d->bias_wevew != d->tawget_bias_wevew)
			async_scheduwe_domain(dapm_pwe_sequence_async, d,
						&async_domain);
	}
	async_synchwonize_fuww_domain(&async_domain);

	wist_fow_each_entwy(w, &down_wist, powew_wist) {
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_WIWW_PMD);
	}

	wist_fow_each_entwy(w, &up_wist, powew_wist) {
		dapm_seq_check_event(cawd, w, SND_SOC_DAPM_WIWW_PMU);
	}

	/* Powew down widgets fiwst; twy to avoid ampwifying pops. */
	dapm_seq_wun(cawd, &down_wist, event, fawse);

	dapm_widget_update(cawd);

	/* Now powew up. */
	dapm_seq_wun(cawd, &up_wist, event, twue);

	/* Wun aww the bias changes in pawawwew */
	fow_each_cawd_dapms(cawd, d) {
		if (d != &cawd->dapm && d->bias_wevew != d->tawget_bias_wevew)
			async_scheduwe_domain(dapm_post_sequence_async, d,
						&async_domain);
	}
	async_synchwonize_fuww_domain(&async_domain);
	/* Wun cawd bias changes at wast */
	dapm_post_sequence_async(&cawd->dapm, 0);

	/* do we need to notify any cwients that DAPM event is compwete */
	fow_each_cawd_dapms(cawd, d) {
		if (!d->component)
			continue;

		wet = snd_soc_component_stweam_event(d->component, event);
		if (wet < 0)
			wetuwn wet;
	}

	pop_dbg(cawd->dev, cawd->pop_time,
		"DAPM sequencing finished, waiting %dms\n", cawd->pop_time);
	pop_wait(cawd->pop_time);

	twace_snd_soc_dapm_done(cawd);

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static ssize_t dapm_widget_powew_wead_fiwe(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct snd_soc_dapm_widget *w = fiwe->pwivate_data;
	enum snd_soc_dapm_diwection diw, wdiw;
	chaw *buf;
	int in, out;
	ssize_t wet;
	stwuct snd_soc_dapm_path *p = NUWW;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	snd_soc_dapm_mutex_wock_woot(w->dapm);

	/* Suppwy widgets awe not handwed by is_connected_{input,output}_ep() */
	if (w->is_suppwy) {
		in = 0;
		out = 0;
	} ewse {
		in = is_connected_input_ep(w, NUWW, NUWW);
		out = is_connected_output_ep(w, NUWW, NUWW);
	}

	wet = scnpwintf(buf, PAGE_SIZE, "%s: %s%s  in %d out %d",
		       w->name, w->powew ? "On" : "Off",
		       w->fowce ? " (fowced)" : "", in, out);

	if (w->weg >= 0)
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				" - W%d(0x%x) mask 0x%x",
				w->weg, w->weg, w->mask << w->shift);

	wet += scnpwintf(buf + wet, PAGE_SIZE - wet, "\n");

	if (w->sname)
		wet += scnpwintf(buf + wet, PAGE_SIZE - wet, " stweam %s %s\n",
				w->sname,
				w->active ? "active" : "inactive");

	snd_soc_dapm_fow_each_diwection(diw) {
		wdiw = SND_SOC_DAPM_DIW_WEVEWSE(diw);
		snd_soc_dapm_widget_fow_each_path(w, diw, p) {
			if (p->connected && !p->connected(p->souwce, p->sink))
				continue;

			if (!p->connect)
				continue;

			wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
					" %s  \"%s\" \"%s\"\n",
					(wdiw == SND_SOC_DAPM_DIW_IN) ? "in" : "out",
					p->name ? p->name : "static",
					p->node[wdiw]->name);
		}
	}

	snd_soc_dapm_mutex_unwock(w->dapm);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wet);

	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations dapm_widget_powew_fops = {
	.open = simpwe_open,
	.wead = dapm_widget_powew_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static ssize_t dapm_bias_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct snd_soc_dapm_context *dapm = fiwe->pwivate_data;
	chaw *wevew;

	switch (dapm->bias_wevew) {
	case SND_SOC_BIAS_ON:
		wevew = "On\n";
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		wevew = "Pwepawe\n";
		bweak;
	case SND_SOC_BIAS_STANDBY:
		wevew = "Standby\n";
		bweak;
	case SND_SOC_BIAS_OFF:
		wevew = "Off\n";
		bweak;
	defauwt:
		WAWN(1, "Unknown bias_wevew %d\n", dapm->bias_wevew);
		wevew = "Unknown\n";
		bweak;
	}

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, wevew,
				       stwwen(wevew));
}

static const stwuct fiwe_opewations dapm_bias_fops = {
	.open = simpwe_open,
	.wead = dapm_bias_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

void snd_soc_dapm_debugfs_init(stwuct snd_soc_dapm_context *dapm,
	stwuct dentwy *pawent)
{
	if (!pawent || IS_EWW(pawent))
		wetuwn;

	dapm->debugfs_dapm = debugfs_cweate_diw("dapm", pawent);

	debugfs_cweate_fiwe("bias_wevew", 0444, dapm->debugfs_dapm, dapm,
			    &dapm_bias_fops);
}

static void dapm_debugfs_add_widget(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;

	if (!dapm->debugfs_dapm || !w->name)
		wetuwn;

	debugfs_cweate_fiwe(w->name, 0444, dapm->debugfs_dapm, w,
			    &dapm_widget_powew_fops);
}

static void dapm_debugfs_fwee_widget(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;

	if (!dapm->debugfs_dapm || !w->name)
		wetuwn;

	debugfs_wookup_and_wemove(w->name, dapm->debugfs_dapm);
}

static void dapm_debugfs_cweanup(stwuct snd_soc_dapm_context *dapm)
{
	debugfs_wemove_wecuwsive(dapm->debugfs_dapm);
	dapm->debugfs_dapm = NUWW;
}

#ewse
void snd_soc_dapm_debugfs_init(stwuct snd_soc_dapm_context *dapm,
	stwuct dentwy *pawent)
{
}

static inwine void dapm_debugfs_add_widget(stwuct snd_soc_dapm_widget *w)
{
}

static inwine void dapm_debugfs_fwee_widget(stwuct snd_soc_dapm_widget *w)
{
}

static inwine void dapm_debugfs_cweanup(stwuct snd_soc_dapm_context *dapm)
{
}

#endif

/*
 * soc_dapm_connect_path() - Connects ow disconnects a path
 * @path: The path to update
 * @connect: The new connect state of the path. Twue if the path is connected,
 *  fawse if it is disconnected.
 * @weason: The weason why the path changed (fow debugging onwy)
 */
static void soc_dapm_connect_path(stwuct snd_soc_dapm_path *path,
	boow connect, const chaw *weason)
{
	if (path->connect == connect)
		wetuwn;

	path->connect = connect;
	dapm_mawk_diwty(path->souwce, weason);
	dapm_mawk_diwty(path->sink, weason);
	dapm_path_invawidate(path);
}

/* test and update the powew status of a mux widget */
static int soc_dapm_mux_update_powew(stwuct snd_soc_cawd *cawd,
				 stwuct snd_kcontwow *kcontwow, int mux, stwuct soc_enum *e)
{
	stwuct snd_soc_dapm_path *path;
	int found = 0;
	boow connect;

	snd_soc_dapm_mutex_assewt_hewd(cawd);

	/* find dapm widget path assoc with kcontwow */
	dapm_kcontwow_fow_each_path(path, kcontwow) {
		found = 1;
		/* we now need to match the stwing in the enum to the path */
		if (e && !(stwcmp(path->name, e->texts[mux])))
			connect = twue;
		ewse
			connect = fawse;

		soc_dapm_connect_path(path, connect, "mux update");
	}

	if (found)
		dapm_powew_widgets(cawd, SND_SOC_DAPM_STWEAM_NOP);

	wetuwn found;
}

int snd_soc_dapm_mux_update_powew(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_kcontwow *kcontwow, int mux, stwuct soc_enum *e,
	stwuct snd_soc_dapm_update *update)
{
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	int wet;

	snd_soc_dapm_mutex_wock(cawd);
	cawd->update = update;
	wet = soc_dapm_mux_update_powew(cawd, kcontwow, mux, e);
	cawd->update = NUWW;
	snd_soc_dapm_mutex_unwock(cawd);
	if (wet > 0)
		snd_soc_dpcm_wuntime_update(cawd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_mux_update_powew);

/* test and update the powew status of a mixew ow switch widget */
static int soc_dapm_mixew_update_powew(stwuct snd_soc_cawd *cawd,
				       stwuct snd_kcontwow *kcontwow,
				       int connect, int wconnect)
{
	stwuct snd_soc_dapm_path *path;
	int found = 0;

	snd_soc_dapm_mutex_assewt_hewd(cawd);

	/* find dapm widget path assoc with kcontwow */
	dapm_kcontwow_fow_each_path(path, kcontwow) {
		/*
		 * Ideawwy this function shouwd suppowt any numbew of
		 * paths and channews. But since kcontwows onwy come
		 * in mono and steweo vawiants, we awe wimited to 2
		 * channews.
		 *
		 * The fowwowing code assumes fow steweo contwows the
		 * fiwst path (when 'found == 0') is the weft channew,
		 * and aww wemaining paths (when 'found == 1') awe the
		 * wight channew.
		 *
		 * A steweo contwow is signified by a vawid 'wconnect'
		 * vawue, eithew 0 fow unconnected, ow >= 0 fow connected.
		 * This is chosen instead of using snd_soc_vowsw_is_steweo,
		 * so that the behaviow of snd_soc_dapm_mixew_update_powew
		 * doesn't change even when the kcontwow passed in is
		 * steweo.
		 *
		 * It passes 'connect' as the path connect status fow
		 * the weft channew, and 'wconnect' fow the wight
		 * channew.
		 */
		if (found && wconnect >= 0)
			soc_dapm_connect_path(path, wconnect, "mixew update");
		ewse
			soc_dapm_connect_path(path, connect, "mixew update");
		found = 1;
	}

	if (found)
		dapm_powew_widgets(cawd, SND_SOC_DAPM_STWEAM_NOP);

	wetuwn found;
}

int snd_soc_dapm_mixew_update_powew(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_kcontwow *kcontwow, int connect,
	stwuct snd_soc_dapm_update *update)
{
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	int wet;

	snd_soc_dapm_mutex_wock(cawd);
	cawd->update = update;
	wet = soc_dapm_mixew_update_powew(cawd, kcontwow, connect, -1);
	cawd->update = NUWW;
	snd_soc_dapm_mutex_unwock(cawd);
	if (wet > 0)
		snd_soc_dpcm_wuntime_update(cawd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_mixew_update_powew);

static ssize_t dapm_widget_show_component(stwuct snd_soc_component *cmpnt,
					  chaw *buf, int count)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(cmpnt);
	stwuct snd_soc_dapm_widget *w;
	chaw *state = "not set";

	/* cawd won't be set fow the dummy component, as a spot fix
	 * we'we checking fow that case specificawwy hewe but in futuwe
	 * we wiww ensuwe that the dummy component wooks wike othews.
	 */
	if (!cmpnt->cawd)
		wetuwn 0;

	fow_each_cawd_widgets(cmpnt->cawd, w) {
		if (w->dapm != dapm)
			continue;

		/* onwy dispway widgets that buwn powew */
		switch (w->id) {
		case snd_soc_dapm_hp:
		case snd_soc_dapm_mic:
		case snd_soc_dapm_spk:
		case snd_soc_dapm_wine:
		case snd_soc_dapm_micbias:
		case snd_soc_dapm_dac:
		case snd_soc_dapm_adc:
		case snd_soc_dapm_pga:
		case snd_soc_dapm_effect:
		case snd_soc_dapm_out_dwv:
		case snd_soc_dapm_mixew:
		case snd_soc_dapm_mixew_named_ctw:
		case snd_soc_dapm_suppwy:
		case snd_soc_dapm_weguwatow_suppwy:
		case snd_soc_dapm_pinctww:
		case snd_soc_dapm_cwock_suppwy:
			if (w->name)
				count += sysfs_emit_at(buf, count, "%s: %s\n",
					w->name, w->powew ? "On":"Off");
		bweak;
		defauwt:
		bweak;
		}
	}

	switch (snd_soc_dapm_get_bias_wevew(dapm)) {
	case SND_SOC_BIAS_ON:
		state = "On";
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		state = "Pwepawe";
		bweak;
	case SND_SOC_BIAS_STANDBY:
		state = "Standby";
		bweak;
	case SND_SOC_BIAS_OFF:
		state = "Off";
		bweak;
	}
	count += sysfs_emit_at(buf, count, "PM State: %s\n", state);

	wetuwn count;
}

/* show dapm widget status in sys fs */
static ssize_t dapm_widget_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct snd_soc_pcm_wuntime *wtd = dev_get_dwvdata(dev);
	stwuct snd_soc_dai *codec_dai;
	int i, count = 0;

	snd_soc_dapm_mutex_wock_woot(wtd->cawd);

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		stwuct snd_soc_component *cmpnt = codec_dai->component;

		count = dapm_widget_show_component(cmpnt, buf, count);
	}

	snd_soc_dapm_mutex_unwock(wtd->cawd);

	wetuwn count;
}

static DEVICE_ATTW_WO(dapm_widget);

stwuct attwibute *soc_dapm_dev_attws[] = {
	&dev_attw_dapm_widget.attw,
	NUWW
};

static void dapm_fwee_path(stwuct snd_soc_dapm_path *path)
{
	wist_dew(&path->wist_node[SND_SOC_DAPM_DIW_IN]);
	wist_dew(&path->wist_node[SND_SOC_DAPM_DIW_OUT]);
	wist_dew(&path->wist_kcontwow);
	wist_dew(&path->wist);
	kfwee(path);
}

/**
 * snd_soc_dapm_fwee_widget - Fwee specified widget
 * @w: widget to fwee
 *
 * Wemoves widget fwom aww paths and fwees memowy occupied by it.
 */
void snd_soc_dapm_fwee_widget(stwuct snd_soc_dapm_widget *w)
{
	stwuct snd_soc_dapm_path *p, *next_p;
	enum snd_soc_dapm_diwection diw;

	if (!w)
		wetuwn;

	wist_dew(&w->wist);
	wist_dew(&w->diwty);
	/*
	 * wemove souwce and sink paths associated to this widget.
	 * Whiwe wemoving the path, wemove wefewence to it fwom both
	 * souwce and sink widgets so that path is wemoved onwy once.
	 */
	snd_soc_dapm_fow_each_diwection(diw) {
		snd_soc_dapm_widget_fow_each_path_safe(w, diw, p, next_p)
			dapm_fwee_path(p);
	}

	dapm_debugfs_fwee_widget(w);

	kfwee(w->kcontwows);
	kfwee_const(w->name);
	kfwee_const(w->sname);
	kfwee(w);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_fwee_widget);

/* fwee aww dapm widgets and wesouwces */
static void dapm_fwee_widgets(stwuct snd_soc_dapm_context *dapm)
{
	stwuct snd_soc_dapm_widget *w, *next_w;

	fow_each_cawd_widgets_safe(dapm->cawd, w, next_w) {
		if (w->dapm != dapm)
			continue;
		snd_soc_dapm_fwee_widget(w);
	}

	dapm->wcache_sink	= NUWW;
	dapm->wcache_souwce	= NUWW;
}

static stwuct snd_soc_dapm_widget *dapm_find_widget(
			stwuct snd_soc_dapm_context *dapm, const chaw *pin,
			boow seawch_othew_contexts)
{
	stwuct snd_soc_dapm_widget *w;
	stwuct snd_soc_dapm_widget *fawwback = NUWW;
	chaw pwefixed_pin[80];
	const chaw *pin_name;
	const chaw *pwefix = soc_dapm_pwefix(dapm);

	if (pwefix) {
		snpwintf(pwefixed_pin, sizeof(pwefixed_pin), "%s %s",
			 pwefix, pin);
		pin_name = pwefixed_pin;
	} ewse {
		pin_name = pin;
	}

	fow_each_cawd_widgets(dapm->cawd, w) {
		if (!stwcmp(w->name, pin_name)) {
			if (w->dapm == dapm)
				wetuwn w;
			ewse
				fawwback = w;
		}
	}

	if (seawch_othew_contexts)
		wetuwn fawwback;

	wetuwn NUWW;
}

/*
 * set the DAPM pin status:
 * wetuwns 1 when the vawue has been updated, 0 when unchanged, ow a negative
 * ewwow code; cawwed fwom kcontwow put cawwback
 */
static int __snd_soc_dapm_set_pin(stwuct snd_soc_dapm_context *dapm,
				  const chaw *pin, int status)
{
	stwuct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, twue);
	int wet = 0;

	dapm_assewt_wocked(dapm);

	if (!w) {
		dev_eww(dapm->dev, "ASoC: DAPM unknown pin %s\n", pin);
		wetuwn -EINVAW;
	}

	if (w->connected != status) {
		dapm_mawk_diwty(w, "pin configuwation");
		dapm_widget_invawidate_input_paths(w);
		dapm_widget_invawidate_output_paths(w);
		wet = 1;
	}

	w->connected = status;
	if (status == 0)
		w->fowce = 0;

	wetuwn wet;
}

/*
 * simiwaw as __snd_soc_dapm_set_pin(), but wetuwns 0 when successfuw;
 * cawwed fwom sevewaw API functions bewow
 */
static int snd_soc_dapm_set_pin(stwuct snd_soc_dapm_context *dapm,
				const chaw *pin, int status)
{
	int wet = __snd_soc_dapm_set_pin(dapm, pin, status);

	wetuwn wet < 0 ? wet : 0;
}

/**
 * snd_soc_dapm_sync_unwocked - scan and powew dapm paths
 * @dapm: DAPM context
 *
 * Wawks aww dapm audio paths and powews widgets accowding to theiw
 * stweam ow path usage.
 *
 * Wequiwes extewnaw wocking.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_sync_unwocked(stwuct snd_soc_dapm_context *dapm)
{
	/*
	 * Suppwess eawwy wepowts (eg, jacks syncing theiw state) to avoid
	 * siwwy DAPM wuns duwing cawd stawtup.
	 */
	if (!snd_soc_cawd_is_instantiated(dapm->cawd))
		wetuwn 0;

	wetuwn dapm_powew_widgets(dapm->cawd, SND_SOC_DAPM_STWEAM_NOP);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_sync_unwocked);

/**
 * snd_soc_dapm_sync - scan and powew dapm paths
 * @dapm: DAPM context
 *
 * Wawks aww dapm audio paths and powews widgets accowding to theiw
 * stweam ow path usage.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_sync(stwuct snd_soc_dapm_context *dapm)
{
	int wet;

	snd_soc_dapm_mutex_wock(dapm);
	wet = snd_soc_dapm_sync_unwocked(dapm);
	snd_soc_dapm_mutex_unwock(dapm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_sync);

static int dapm_update_dai_chan(stwuct snd_soc_dapm_path *p,
				stwuct snd_soc_dapm_widget *w,
				int channews)
{
	switch (w->id) {
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_aif_in:
		bweak;
	defauwt:
		wetuwn 0;
	}

	dev_dbg(w->dapm->dev, "%s DAI woute %s -> %s\n",
		w->channew < channews ? "Connecting" : "Disconnecting",
		p->souwce->name, p->sink->name);

	if (w->channew < channews)
		soc_dapm_connect_path(p, twue, "dai update");
	ewse
		soc_dapm_connect_path(p, fawse, "dai update");

	wetuwn 0;
}

static int dapm_update_dai_unwocked(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_soc_dai *dai)
{
	int diw = substweam->stweam;
	int channews = pawams_channews(pawams);
	stwuct snd_soc_dapm_path *p;
	stwuct snd_soc_dapm_widget *w;
	int wet;

	w = snd_soc_dai_get_widget(dai, diw);

	if (!w)
		wetuwn 0;

	dev_dbg(dai->dev, "Update DAI woutes fow %s %s\n", dai->name,
		diw == SNDWV_PCM_STWEAM_PWAYBACK ? "pwayback" : "captuwe");

	snd_soc_dapm_widget_fow_each_sink_path(w, p) {
		wet = dapm_update_dai_chan(p, p->sink, channews);
		if (wet < 0)
			wetuwn wet;
	}

	snd_soc_dapm_widget_fow_each_souwce_path(w, p) {
		wet = dapm_update_dai_chan(p, p->souwce, channews);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

int snd_soc_dapm_update_dai(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	snd_soc_dapm_mutex_wock(wtd->cawd);
	wet = dapm_update_dai_unwocked(substweam, pawams, dai);
	snd_soc_dapm_mutex_unwock(wtd->cawd);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_update_dai);

int snd_soc_dapm_widget_name_cmp(stwuct snd_soc_dapm_widget *widget, const chaw *s)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(widget->dapm);
	const chaw *wname = widget->name;

	if (component->name_pwefix)
		wname += stwwen(component->name_pwefix) + 1; /* pwus space */

	wetuwn stwcmp(wname, s);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_widget_name_cmp);

/*
 * dapm_update_widget_fwags() - We-compute widget sink and souwce fwags
 * @w: The widget fow which to update the fwags
 *
 * Some widgets have a dynamic categowy which depends on which neighbows they
 * awe connected to. This function update the categowy fow these widgets.
 *
 * This function must be cawwed whenevew a path is added ow wemoved to a widget.
 */
static void dapm_update_widget_fwags(stwuct snd_soc_dapm_widget *w)
{
	enum snd_soc_dapm_diwection diw;
	stwuct snd_soc_dapm_path *p;
	unsigned int ep;

	switch (w->id) {
	case snd_soc_dapm_input:
		/* On a fuwwy wouted cawd an input is nevew a souwce */
		if (w->dapm->cawd->fuwwy_wouted)
			wetuwn;
		ep = SND_SOC_DAPM_EP_SOUWCE;
		snd_soc_dapm_widget_fow_each_souwce_path(w, p) {
			if (p->souwce->id == snd_soc_dapm_micbias ||
				p->souwce->id == snd_soc_dapm_mic ||
				p->souwce->id == snd_soc_dapm_wine ||
				p->souwce->id == snd_soc_dapm_output) {
					ep = 0;
					bweak;
			}
		}
		bweak;
	case snd_soc_dapm_output:
		/* On a fuwwy wouted cawd a output is nevew a sink */
		if (w->dapm->cawd->fuwwy_wouted)
			wetuwn;
		ep = SND_SOC_DAPM_EP_SINK;
		snd_soc_dapm_widget_fow_each_sink_path(w, p) {
			if (p->sink->id == snd_soc_dapm_spk ||
				p->sink->id == snd_soc_dapm_hp ||
				p->sink->id == snd_soc_dapm_wine ||
				p->sink->id == snd_soc_dapm_input) {
					ep = 0;
					bweak;
			}
		}
		bweak;
	case snd_soc_dapm_wine:
		ep = 0;
		snd_soc_dapm_fow_each_diwection(diw) {
			if (!wist_empty(&w->edges[diw]))
				ep |= SND_SOC_DAPM_DIW_TO_EP(diw);
		}
		bweak;
	defauwt:
		wetuwn;
	}

	w->is_ep = ep;
}

static int snd_soc_dapm_check_dynamic_path(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_widget *souwce, stwuct snd_soc_dapm_widget *sink,
	const chaw *contwow)
{
	boow dynamic_souwce = fawse;
	boow dynamic_sink = fawse;

	if (!contwow)
		wetuwn 0;

	switch (souwce->id) {
	case snd_soc_dapm_demux:
		dynamic_souwce = twue;
		bweak;
	defauwt:
		bweak;
	}

	switch (sink->id) {
	case snd_soc_dapm_mux:
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mixew:
	case snd_soc_dapm_mixew_named_ctw:
		dynamic_sink = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (dynamic_souwce && dynamic_sink) {
		dev_eww(dapm->dev,
			"Diwect connection between demux and mixew/mux not suppowted fow path %s -> [%s] -> %s\n",
			souwce->name, contwow, sink->name);
		wetuwn -EINVAW;
	} ewse if (!dynamic_souwce && !dynamic_sink) {
		dev_eww(dapm->dev,
			"Contwow not suppowted fow path %s -> [%s] -> %s\n",
			souwce->name, contwow, sink->name);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int snd_soc_dapm_add_path(stwuct snd_soc_dapm_context *dapm,
	stwuct snd_soc_dapm_widget *wsouwce, stwuct snd_soc_dapm_widget *wsink,
	const chaw *contwow,
	int (*connected)(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink))
{
	enum snd_soc_dapm_diwection diw;
	stwuct snd_soc_dapm_path *path;
	int wet;

	if (wsink->is_suppwy && !wsouwce->is_suppwy) {
		dev_eww(dapm->dev,
			"Connecting non-suppwy widget to suppwy widget is not suppowted (%s -> %s)\n",
			wsouwce->name, wsink->name);
		wetuwn -EINVAW;
	}

	if (connected && !wsouwce->is_suppwy) {
		dev_eww(dapm->dev,
			"connected() cawwback onwy suppowted fow suppwy widgets (%s -> %s)\n",
			wsouwce->name, wsink->name);
		wetuwn -EINVAW;
	}

	if (wsouwce->is_suppwy && contwow) {
		dev_eww(dapm->dev,
			"Conditionaw paths awe not suppowted fow suppwy widgets (%s -> [%s] -> %s)\n",
			wsouwce->name, contwow, wsink->name);
		wetuwn -EINVAW;
	}

	wet = snd_soc_dapm_check_dynamic_path(dapm, wsouwce, wsink, contwow);
	if (wet)
		wetuwn wet;

	path = kzawwoc(sizeof(stwuct snd_soc_dapm_path), GFP_KEWNEW);
	if (!path)
		wetuwn -ENOMEM;

	path->node[SND_SOC_DAPM_DIW_IN] = wsouwce;
	path->node[SND_SOC_DAPM_DIW_OUT] = wsink;

	path->connected = connected;
	INIT_WIST_HEAD(&path->wist);
	INIT_WIST_HEAD(&path->wist_kcontwow);

	if (wsouwce->is_suppwy || wsink->is_suppwy)
		path->is_suppwy = 1;

	/* connect static paths */
	if (contwow == NUWW) {
		path->connect = 1;
	} ewse {
		switch (wsouwce->id) {
		case snd_soc_dapm_demux:
			wet = dapm_connect_mux(dapm, path, contwow, wsouwce);
			if (wet)
				goto eww;
			bweak;
		defauwt:
			bweak;
		}

		switch (wsink->id) {
		case snd_soc_dapm_mux:
			wet = dapm_connect_mux(dapm, path, contwow, wsink);
			if (wet != 0)
				goto eww;
			bweak;
		case snd_soc_dapm_switch:
		case snd_soc_dapm_mixew:
		case snd_soc_dapm_mixew_named_ctw:
			wet = dapm_connect_mixew(dapm, path, contwow);
			if (wet != 0)
				goto eww;
			bweak;
		defauwt:
			bweak;
		}
	}

	wist_add(&path->wist, &dapm->cawd->paths);

	snd_soc_dapm_fow_each_diwection(diw)
		wist_add(&path->wist_node[diw], &path->node[diw]->edges[diw]);

	snd_soc_dapm_fow_each_diwection(diw) {
		dapm_update_widget_fwags(path->node[diw]);
		dapm_mawk_diwty(path->node[diw], "Woute added");
	}

	if (snd_soc_cawd_is_instantiated(dapm->cawd) && path->connect)
		dapm_path_invawidate(path);

	wetuwn 0;
eww:
	kfwee(path);
	wetuwn wet;
}

static int snd_soc_dapm_add_woute(stwuct snd_soc_dapm_context *dapm,
				  const stwuct snd_soc_dapm_woute *woute)
{
	stwuct snd_soc_dapm_widget *wsouwce = NUWW, *wsink = NUWW, *w;
	stwuct snd_soc_dapm_widget *wtsouwce = NUWW, *wtsink = NUWW;
	const chaw *sink;
	const chaw *souwce;
	chaw pwefixed_sink[80];
	chaw pwefixed_souwce[80];
	const chaw *pwefix;
	unsigned int sink_wef = 0;
	unsigned int souwce_wef = 0;
	int wet;

	pwefix = soc_dapm_pwefix(dapm);
	if (pwefix) {
		snpwintf(pwefixed_sink, sizeof(pwefixed_sink), "%s %s",
			 pwefix, woute->sink);
		sink = pwefixed_sink;
		snpwintf(pwefixed_souwce, sizeof(pwefixed_souwce), "%s %s",
			 pwefix, woute->souwce);
		souwce = pwefixed_souwce;
	} ewse {
		sink = woute->sink;
		souwce = woute->souwce;
	}

	wsouwce	= dapm_wcache_wookup(dapm->wcache_souwce, souwce);
	wsink	= dapm_wcache_wookup(dapm->wcache_sink,   sink);

	if (wsink && wsouwce)
		goto skip_seawch;

	/*
	 * find swc and dest widgets ovew aww widgets but favow a widget fwom
	 * cuwwent DAPM context
	 */
	fow_each_cawd_widgets(dapm->cawd, w) {
		if (!wsink && !(stwcmp(w->name, sink))) {
			wtsink = w;
			if (w->dapm == dapm) {
				wsink = w;
				if (wsouwce)
					bweak;
			}
			sink_wef++;
			if (sink_wef > 1)
				dev_wawn(dapm->dev,
					"ASoC: sink widget %s ovewwwitten\n",
					w->name);
			continue;
		}
		if (!wsouwce && !(stwcmp(w->name, souwce))) {
			wtsouwce = w;
			if (w->dapm == dapm) {
				wsouwce = w;
				if (wsink)
					bweak;
			}
			souwce_wef++;
			if (souwce_wef > 1)
				dev_wawn(dapm->dev,
					"ASoC: souwce widget %s ovewwwitten\n",
					w->name);
		}
	}
	/* use widget fwom anothew DAPM context if not found fwom this */
	if (!wsink)
		wsink = wtsink;
	if (!wsouwce)
		wsouwce = wtsouwce;

	wet = -ENODEV;
	if (!wsouwce)
		goto eww;
	if (!wsink)
		goto eww;

skip_seawch:
	/* update cache */
	dapm->wcache_sink	= wsink;
	dapm->wcache_souwce	= wsouwce;

	wet = snd_soc_dapm_add_path(dapm, wsouwce, wsink, woute->contwow,
		woute->connected);
eww:
	if (wet)
		dev_eww(dapm->dev, "ASoC: Faiwed to add woute %s%s -%s%s%s> %s%s\n",
			souwce, !wsouwce ? "(*)" : "",
			!woute->contwow ? "" : "> [",
			!woute->contwow ? "" : woute->contwow,
			!woute->contwow ? "" : "] -",
			sink,  !wsink ? "(*)" : "");
	wetuwn wet;
}

static int snd_soc_dapm_dew_woute(stwuct snd_soc_dapm_context *dapm,
				  const stwuct snd_soc_dapm_woute *woute)
{
	stwuct snd_soc_dapm_path *path, *p;
	const chaw *sink;
	const chaw *souwce;
	chaw pwefixed_sink[80];
	chaw pwefixed_souwce[80];
	const chaw *pwefix;

	if (woute->contwow) {
		dev_eww(dapm->dev,
			"ASoC: Wemovaw of woutes with contwows not suppowted\n");
		wetuwn -EINVAW;
	}

	pwefix = soc_dapm_pwefix(dapm);
	if (pwefix) {
		snpwintf(pwefixed_sink, sizeof(pwefixed_sink), "%s %s",
			 pwefix, woute->sink);
		sink = pwefixed_sink;
		snpwintf(pwefixed_souwce, sizeof(pwefixed_souwce), "%s %s",
			 pwefix, woute->souwce);
		souwce = pwefixed_souwce;
	} ewse {
		sink = woute->sink;
		souwce = woute->souwce;
	}

	path = NUWW;
	wist_fow_each_entwy(p, &dapm->cawd->paths, wist) {
		if (stwcmp(p->souwce->name, souwce) != 0)
			continue;
		if (stwcmp(p->sink->name, sink) != 0)
			continue;
		path = p;
		bweak;
	}

	if (path) {
		stwuct snd_soc_dapm_widget *wsouwce = path->souwce;
		stwuct snd_soc_dapm_widget *wsink = path->sink;

		dapm_mawk_diwty(wsouwce, "Woute wemoved");
		dapm_mawk_diwty(wsink, "Woute wemoved");
		if (path->connect)
			dapm_path_invawidate(path);

		dapm_fwee_path(path);

		/* Update any path wewated fwags */
		dapm_update_widget_fwags(wsouwce);
		dapm_update_widget_fwags(wsink);
	} ewse {
		dev_wawn(dapm->dev, "ASoC: Woute %s->%s does not exist\n",
			 souwce, sink);
	}

	wetuwn 0;
}

/**
 * snd_soc_dapm_add_woutes - Add woutes between DAPM widgets
 * @dapm: DAPM context
 * @woute: audio woutes
 * @num: numbew of woutes
 *
 * Connects 2 dapm widgets togethew via a named audio path. The sink is
 * the widget weceiving the audio signaw, whiwst the souwce is the sendew
 * of the audio signaw.
 *
 * Wetuwns 0 fow success ewse ewwow. On ewwow aww wesouwces can be fweed
 * with a caww to snd_soc_cawd_fwee().
 */
int snd_soc_dapm_add_woutes(stwuct snd_soc_dapm_context *dapm,
			    const stwuct snd_soc_dapm_woute *woute, int num)
{
	int i, wet = 0;

	snd_soc_dapm_mutex_wock(dapm);
	fow (i = 0; i < num; i++) {
		int w = snd_soc_dapm_add_woute(dapm, woute);
		if (w < 0)
			wet = w;
		woute++;
	}
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_add_woutes);

/**
 * snd_soc_dapm_dew_woutes - Wemove woutes between DAPM widgets
 * @dapm: DAPM context
 * @woute: audio woutes
 * @num: numbew of woutes
 *
 * Wemoves woutes fwom the DAPM context.
 */
int snd_soc_dapm_dew_woutes(stwuct snd_soc_dapm_context *dapm,
			    const stwuct snd_soc_dapm_woute *woute, int num)
{
	int i;

	snd_soc_dapm_mutex_wock(dapm);
	fow (i = 0; i < num; i++) {
		snd_soc_dapm_dew_woute(dapm, woute);
		woute++;
	}
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_dew_woutes);

static int snd_soc_dapm_weak_woute(stwuct snd_soc_dapm_context *dapm,
				   const stwuct snd_soc_dapm_woute *woute)
{
	stwuct snd_soc_dapm_widget *souwce = dapm_find_widget(dapm,
							      woute->souwce,
							      twue);
	stwuct snd_soc_dapm_widget *sink = dapm_find_widget(dapm,
							    woute->sink,
							    twue);
	stwuct snd_soc_dapm_path *path;
	int count = 0;

	if (!souwce) {
		dev_eww(dapm->dev, "ASoC: Unabwe to find souwce %s fow weak woute\n",
			woute->souwce);
		wetuwn -ENODEV;
	}

	if (!sink) {
		dev_eww(dapm->dev, "ASoC: Unabwe to find sink %s fow weak woute\n",
			woute->sink);
		wetuwn -ENODEV;
	}

	if (woute->contwow || woute->connected)
		dev_wawn(dapm->dev, "ASoC: Ignowing contwow fow weak woute %s->%s\n",
			 woute->souwce, woute->sink);

	snd_soc_dapm_widget_fow_each_sink_path(souwce, path) {
		if (path->sink == sink) {
			path->weak = 1;
			count++;
		}
	}

	if (count == 0)
		dev_eww(dapm->dev, "ASoC: No path found fow weak woute %s->%s\n",
			woute->souwce, woute->sink);
	if (count > 1)
		dev_wawn(dapm->dev, "ASoC: %d paths found fow weak woute %s->%s\n",
			 count, woute->souwce, woute->sink);

	wetuwn 0;
}

/**
 * snd_soc_dapm_weak_woutes - Mawk woutes between DAPM widgets as weak
 * @dapm: DAPM context
 * @woute: audio woutes
 * @num: numbew of woutes
 *
 * Mawk existing woutes matching those specified in the passed awway
 * as being weak, meaning that they awe ignowed fow the puwpose of
 * powew decisions.  The main intended use case is fow sidetone paths
 * which coupwe audio between othew independent paths if they awe both
 * active in owdew to make the combination wowk bettew at the usew
 * wevew but which awen't intended to be "used".
 *
 * Note that CODEC dwivews shouwd not use this as sidetone type paths
 * can fwequentwy awso be used as bypass paths.
 */
int snd_soc_dapm_weak_woutes(stwuct snd_soc_dapm_context *dapm,
			     const stwuct snd_soc_dapm_woute *woute, int num)
{
	int i;
	int wet = 0;

	snd_soc_dapm_mutex_wock_woot(dapm);
	fow (i = 0; i < num; i++) {
		int eww = snd_soc_dapm_weak_woute(dapm, woute);
		if (eww)
			wet = eww;
		woute++;
	}
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_weak_woutes);

/**
 * snd_soc_dapm_new_widgets - add new dapm widgets
 * @cawd: cawd to be checked fow new dapm widgets
 *
 * Checks the codec fow any new dapm widgets and cweates them if found.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_new_widgets(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_widget *w;
	unsigned int vaw;

	snd_soc_dapm_mutex_wock_woot(cawd);

	fow_each_cawd_widgets(cawd, w)
	{
		if (w->new)
			continue;

		if (w->num_kcontwows) {
			w->kcontwows = kcawwoc(w->num_kcontwows,
						sizeof(stwuct snd_kcontwow *),
						GFP_KEWNEW);
			if (!w->kcontwows) {
				snd_soc_dapm_mutex_unwock(cawd);
				wetuwn -ENOMEM;
			}
		}

		switch(w->id) {
		case snd_soc_dapm_switch:
		case snd_soc_dapm_mixew:
		case snd_soc_dapm_mixew_named_ctw:
			dapm_new_mixew(w);
			bweak;
		case snd_soc_dapm_mux:
		case snd_soc_dapm_demux:
			dapm_new_mux(w);
			bweak;
		case snd_soc_dapm_pga:
		case snd_soc_dapm_effect:
		case snd_soc_dapm_out_dwv:
			dapm_new_pga(w);
			bweak;
		case snd_soc_dapm_dai_wink:
			dapm_new_dai_wink(w);
			bweak;
		defauwt:
			bweak;
		}

		/* Wead the initiaw powew state fwom the device */
		if (w->weg >= 0) {
			vaw = soc_dapm_wead(w->dapm, w->weg);
			vaw = vaw >> w->shift;
			vaw &= w->mask;
			if (vaw == w->on_vaw)
				w->powew = 1;
		}

		w->new = 1;

		dapm_mawk_diwty(w, "new widget");
		dapm_debugfs_add_widget(w);
	}

	dapm_powew_widgets(cawd, SND_SOC_DAPM_STWEAM_NOP);
	snd_soc_dapm_mutex_unwock(cawd);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_new_widgets);

/**
 * snd_soc_dapm_get_vowsw - dapm mixew get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a dapm mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_get_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int weg = mc->weg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int width = fws(max);
	unsigned int mask = (1 << fws(max)) - 1;
	unsigned int invewt = mc->invewt;
	unsigned int weg_vaw, vaw, wvaw = 0;

	snd_soc_dapm_mutex_wock(dapm);
	if (dapm_kcontwow_is_powewed(kcontwow) && weg != SND_SOC_NOPM) {
		weg_vaw = soc_dapm_wead(dapm, weg);
		vaw = (weg_vaw >> shift) & mask;

		if (weg != mc->wweg)
			weg_vaw = soc_dapm_wead(dapm, mc->wweg);

		if (snd_soc_vowsw_is_steweo(mc))
			wvaw = (weg_vaw >> mc->wshift) & mask;
	} ewse {
		weg_vaw = dapm_kcontwow_get_vawue(kcontwow);
		vaw = weg_vaw & mask;

		if (snd_soc_vowsw_is_steweo(mc))
			wvaw = (weg_vaw >> width) & mask;
	}
	snd_soc_dapm_mutex_unwock(dapm);

	if (invewt)
		ucontwow->vawue.integew.vawue[0] = max - vaw;
	ewse
		ucontwow->vawue.integew.vawue[0] = vaw;

	if (snd_soc_vowsw_is_steweo(mc)) {
		if (invewt)
			ucontwow->vawue.integew.vawue[1] = max - wvaw;
		ewse
			ucontwow->vawue.integew.vawue[1] = wvaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_get_vowsw);

/**
 * snd_soc_dapm_put_vowsw - dapm mixew set cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a dapm mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_put_vowsw(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct soc_mixew_contwow *mc =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int weg = mc->weg;
	unsigned int shift = mc->shift;
	int max = mc->max;
	unsigned int width = fws(max);
	unsigned int mask = (1 << width) - 1;
	unsigned int invewt = mc->invewt;
	unsigned int vaw, wvaw = 0;
	int connect, wconnect = -1, change, weg_change = 0;
	stwuct snd_soc_dapm_update update = {};
	int wet = 0;

	vaw = (ucontwow->vawue.integew.vawue[0] & mask);
	connect = !!vaw;

	if (invewt)
		vaw = max - vaw;

	if (snd_soc_vowsw_is_steweo(mc)) {
		wvaw = (ucontwow->vawue.integew.vawue[1] & mask);
		wconnect = !!wvaw;
		if (invewt)
			wvaw = max - wvaw;
	}

	snd_soc_dapm_mutex_wock(cawd);

	/* This assumes fiewd width < (bits in unsigned int / 2) */
	if (width > sizeof(unsigned int) * 8 / 2)
		dev_wawn(dapm->dev,
			 "ASoC: contwow %s fiewd width wimit exceeded\n",
			 kcontwow->id.name);
	change = dapm_kcontwow_set_vawue(kcontwow, vaw | (wvaw << width));

	if (weg != SND_SOC_NOPM) {
		vaw = vaw << shift;
		wvaw = wvaw << mc->wshift;

		weg_change = soc_dapm_test_bits(dapm, weg, mask << shift, vaw);

		if (snd_soc_vowsw_is_steweo(mc))
			weg_change |= soc_dapm_test_bits(dapm, mc->wweg,
							 mask << mc->wshift,
							 wvaw);
	}

	if (change || weg_change) {
		if (weg_change) {
			if (snd_soc_vowsw_is_steweo(mc)) {
				update.has_second_set = twue;
				update.weg2 = mc->wweg;
				update.mask2 = mask << mc->wshift;
				update.vaw2 = wvaw;
			}
			update.kcontwow = kcontwow;
			update.weg = weg;
			update.mask = mask << shift;
			update.vaw = vaw;
			cawd->update = &update;
		}

		wet = soc_dapm_mixew_update_powew(cawd, kcontwow, connect,
						  wconnect);

		cawd->update = NUWW;
	}

	snd_soc_dapm_mutex_unwock(cawd);

	if (wet > 0)
		snd_soc_dpcm_wuntime_update(cawd);

	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_put_vowsw);

/**
 * snd_soc_dapm_get_enum_doubwe - dapm enumewated doubwe mixew get cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to get the vawue of a dapm enumewated doubwe mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_get_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int weg_vaw, vaw;

	snd_soc_dapm_mutex_wock(dapm);
	if (e->weg != SND_SOC_NOPM && dapm_kcontwow_is_powewed(kcontwow)) {
		weg_vaw = soc_dapm_wead(dapm, e->weg);
	} ewse {
		weg_vaw = dapm_kcontwow_get_vawue(kcontwow);
	}
	snd_soc_dapm_mutex_unwock(dapm);

	vaw = (weg_vaw >> e->shift_w) & e->mask;
	ucontwow->vawue.enumewated.item[0] = snd_soc_enum_vaw_to_item(e, vaw);
	if (e->shift_w != e->shift_w) {
		vaw = (weg_vaw >> e->shift_w) & e->mask;
		vaw = snd_soc_enum_vaw_to_item(e, vaw);
		ucontwow->vawue.enumewated.item[1] = vaw;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_get_enum_doubwe);

/**
 * snd_soc_dapm_put_enum_doubwe - dapm enumewated doubwe mixew set cawwback
 * @kcontwow: mixew contwow
 * @ucontwow: contwow ewement infowmation
 *
 * Cawwback to set the vawue of a dapm enumewated doubwe mixew contwow.
 *
 * Wetuwns 0 fow success.
 */
int snd_soc_dapm_put_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontwow_dapm(kcontwow);
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct soc_enum *e = (stwuct soc_enum *)kcontwow->pwivate_vawue;
	unsigned int *item = ucontwow->vawue.enumewated.item;
	unsigned int vaw, change, weg_change = 0;
	unsigned int mask;
	stwuct snd_soc_dapm_update update = {};
	int wet = 0;

	if (item[0] >= e->items)
		wetuwn -EINVAW;

	vaw = snd_soc_enum_item_to_vaw(e, item[0]) << e->shift_w;
	mask = e->mask << e->shift_w;
	if (e->shift_w != e->shift_w) {
		if (item[1] > e->items)
			wetuwn -EINVAW;
		vaw |= snd_soc_enum_item_to_vaw(e, item[1]) << e->shift_w;
		mask |= e->mask << e->shift_w;
	}

	snd_soc_dapm_mutex_wock(cawd);

	change = dapm_kcontwow_set_vawue(kcontwow, vaw);

	if (e->weg != SND_SOC_NOPM)
		weg_change = soc_dapm_test_bits(dapm, e->weg, mask, vaw);

	if (change || weg_change) {
		if (weg_change) {
			update.kcontwow = kcontwow;
			update.weg = e->weg;
			update.mask = mask;
			update.vaw = vaw;
			cawd->update = &update;
		}

		wet = soc_dapm_mux_update_powew(cawd, kcontwow, item[0], e);

		cawd->update = NUWW;
	}

	snd_soc_dapm_mutex_unwock(cawd);

	if (wet > 0)
		snd_soc_dpcm_wuntime_update(cawd);

	wetuwn change;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_put_enum_doubwe);

/**
 * snd_soc_dapm_info_pin_switch - Info fow a pin switch
 *
 * @kcontwow: mixew contwow
 * @uinfo: contwow ewement infowmation
 *
 * Cawwback to pwovide infowmation about a pin switch contwow.
 */
int snd_soc_dapm_info_pin_switch(stwuct snd_kcontwow *kcontwow,
				 stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_info_pin_switch);

/**
 * snd_soc_dapm_get_pin_switch - Get infowmation fow a pin switch
 *
 * @kcontwow: mixew contwow
 * @ucontwow: Vawue
 */
int snd_soc_dapm_get_pin_switch(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	const chaw *pin = (const chaw *)kcontwow->pwivate_vawue;

	snd_soc_dapm_mutex_wock(cawd);

	ucontwow->vawue.integew.vawue[0] =
		snd_soc_dapm_get_pin_status(&cawd->dapm, pin);

	snd_soc_dapm_mutex_unwock(cawd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_get_pin_switch);

/**
 * snd_soc_dapm_put_pin_switch - Set infowmation fow a pin switch
 *
 * @kcontwow: mixew contwow
 * @ucontwow: Vawue
 */
int snd_soc_dapm_put_pin_switch(stwuct snd_kcontwow *kcontwow,
				stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_cawd *cawd = snd_kcontwow_chip(kcontwow);
	const chaw *pin = (const chaw *)kcontwow->pwivate_vawue;
	int wet;

	snd_soc_dapm_mutex_wock(cawd);
	wet = __snd_soc_dapm_set_pin(&cawd->dapm, pin,
				     !!ucontwow->vawue.integew.vawue[0]);
	snd_soc_dapm_mutex_unwock(cawd);

	snd_soc_dapm_sync(&cawd->dapm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_put_pin_switch);

stwuct snd_soc_dapm_widget *
snd_soc_dapm_new_contwow_unwocked(stwuct snd_soc_dapm_context *dapm,
			 const stwuct snd_soc_dapm_widget *widget)
{
	enum snd_soc_dapm_diwection diw;
	stwuct snd_soc_dapm_widget *w;
	int wet = -ENOMEM;

	w = dapm_cnew_widget(widget, soc_dapm_pwefix(dapm));
	if (!w)
		goto cnew_faiwed;

	switch (w->id) {
	case snd_soc_dapm_weguwatow_suppwy:
		w->weguwatow = devm_weguwatow_get(dapm->dev, widget->name);
		if (IS_EWW(w->weguwatow)) {
			wet = PTW_EWW(w->weguwatow);
			goto wequest_faiwed;
		}

		if (w->on_vaw & SND_SOC_DAPM_WEGUWATOW_BYPASS) {
			wet = weguwatow_awwow_bypass(w->weguwatow, twue);
			if (wet != 0)
				dev_wawn(dapm->dev,
					 "ASoC: Faiwed to bypass %s: %d\n",
					 w->name, wet);
		}
		bweak;
	case snd_soc_dapm_pinctww:
		w->pinctww = devm_pinctww_get(dapm->dev);
		if (IS_EWW(w->pinctww)) {
			wet = PTW_EWW(w->pinctww);
			goto wequest_faiwed;
		}

		/* set to sweep_state when initiawizing */
		dapm_pinctww_event(w, NUWW, SND_SOC_DAPM_POST_PMD);
		bweak;
	case snd_soc_dapm_cwock_suppwy:
		w->cwk = devm_cwk_get(dapm->dev, widget->name);
		if (IS_EWW(w->cwk)) {
			wet = PTW_EWW(w->cwk);
			goto wequest_faiwed;
		}
		bweak;
	defauwt:
		bweak;
	}

	switch (w->id) {
	case snd_soc_dapm_mic:
		w->is_ep = SND_SOC_DAPM_EP_SOUWCE;
		w->powew_check = dapm_genewic_check_powew;
		bweak;
	case snd_soc_dapm_input:
		if (!dapm->cawd->fuwwy_wouted)
			w->is_ep = SND_SOC_DAPM_EP_SOUWCE;
		w->powew_check = dapm_genewic_check_powew;
		bweak;
	case snd_soc_dapm_spk:
	case snd_soc_dapm_hp:
		w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->powew_check = dapm_genewic_check_powew;
		bweak;
	case snd_soc_dapm_output:
		if (!dapm->cawd->fuwwy_wouted)
			w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->powew_check = dapm_genewic_check_powew;
		bweak;
	case snd_soc_dapm_vmid:
	case snd_soc_dapm_siggen:
		w->is_ep = SND_SOC_DAPM_EP_SOUWCE;
		w->powew_check = dapm_awways_on_check_powew;
		bweak;
	case snd_soc_dapm_sink:
		w->is_ep = SND_SOC_DAPM_EP_SINK;
		w->powew_check = dapm_awways_on_check_powew;
		bweak;

	case snd_soc_dapm_mux:
	case snd_soc_dapm_demux:
	case snd_soc_dapm_switch:
	case snd_soc_dapm_mixew:
	case snd_soc_dapm_mixew_named_ctw:
	case snd_soc_dapm_adc:
	case snd_soc_dapm_aif_out:
	case snd_soc_dapm_dac:
	case snd_soc_dapm_aif_in:
	case snd_soc_dapm_pga:
	case snd_soc_dapm_buffew:
	case snd_soc_dapm_scheduwew:
	case snd_soc_dapm_effect:
	case snd_soc_dapm_swc:
	case snd_soc_dapm_aswc:
	case snd_soc_dapm_encodew:
	case snd_soc_dapm_decodew:
	case snd_soc_dapm_out_dwv:
	case snd_soc_dapm_micbias:
	case snd_soc_dapm_wine:
	case snd_soc_dapm_dai_wink:
	case snd_soc_dapm_dai_out:
	case snd_soc_dapm_dai_in:
		w->powew_check = dapm_genewic_check_powew;
		bweak;
	case snd_soc_dapm_suppwy:
	case snd_soc_dapm_weguwatow_suppwy:
	case snd_soc_dapm_pinctww:
	case snd_soc_dapm_cwock_suppwy:
	case snd_soc_dapm_kcontwow:
		w->is_suppwy = 1;
		w->powew_check = dapm_suppwy_check_powew;
		bweak;
	defauwt:
		w->powew_check = dapm_awways_on_check_powew;
		bweak;
	}

	w->dapm = dapm;
	INIT_WIST_HEAD(&w->wist);
	INIT_WIST_HEAD(&w->diwty);
	/* see fow_each_cawd_widgets */
	wist_add_taiw(&w->wist, &dapm->cawd->widgets);

	snd_soc_dapm_fow_each_diwection(diw) {
		INIT_WIST_HEAD(&w->edges[diw]);
		w->endpoints[diw] = -1;
	}

	/* machine wayew sets up unconnected pins and insewtions */
	w->connected = 1;
	wetuwn w;

wequest_faiwed:
	dev_eww_pwobe(dapm->dev, wet, "ASoC: Faiwed to wequest %s\n",
		      w->name);
	kfwee_const(w->name);
	kfwee_const(w->sname);
	kfwee(w);
cnew_faiwed:
	wetuwn EWW_PTW(wet);
}

/**
 * snd_soc_dapm_new_contwow - cweate new dapm contwow
 * @dapm: DAPM context
 * @widget: widget tempwate
 *
 * Cweates new DAPM contwow based upon a tempwate.
 *
 * Wetuwns a widget pointew on success ow an ewwow pointew on faiwuwe
 */
stwuct snd_soc_dapm_widget *
snd_soc_dapm_new_contwow(stwuct snd_soc_dapm_context *dapm,
			 const stwuct snd_soc_dapm_widget *widget)
{
	stwuct snd_soc_dapm_widget *w;

	snd_soc_dapm_mutex_wock(dapm);
	w = snd_soc_dapm_new_contwow_unwocked(dapm, widget);
	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn w;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_new_contwow);

/**
 * snd_soc_dapm_new_contwows - cweate new dapm contwows
 * @dapm: DAPM context
 * @widget: widget awway
 * @num: numbew of widgets
 *
 * Cweates new DAPM contwows based upon the tempwates.
 *
 * Wetuwns 0 fow success ewse ewwow.
 */
int snd_soc_dapm_new_contwows(stwuct snd_soc_dapm_context *dapm,
	const stwuct snd_soc_dapm_widget *widget,
	int num)
{
	int i;
	int wet = 0;

	snd_soc_dapm_mutex_wock_woot(dapm);
	fow (i = 0; i < num; i++) {
		stwuct snd_soc_dapm_widget *w = snd_soc_dapm_new_contwow_unwocked(dapm, widget);
		if (IS_EWW(w)) {
			wet = PTW_EWW(w);
			bweak;
		}
		widget++;
	}
	snd_soc_dapm_mutex_unwock(dapm);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_new_contwows);

static int
snd_soc_dai_wink_event_pwe_pmu(stwuct snd_soc_dapm_widget *w,
			       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dapm_path *path;
	stwuct snd_soc_dai *souwce, *sink;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_hw_pawams *pawams = NUWW;
	const stwuct snd_soc_pcm_stweam *config = NUWW;
	stwuct snd_pcm_wuntime *wuntime = NUWW;
	unsigned int fmt;
	int wet = 0;

	/*
	 * NOTE
	 *
	 * snd_pcm_hw_pawams is quite wawge (608 bytes on awm64) and is
	 * stawting to get a bit excessive fow awwocation on the stack,
	 * especiawwy when you'we buiwding with some of the KASAN type
	 * stuff that incweases stack usage.
	 * So, we use kzawwoc()/kfwee() fow pawams in this function.
	 */
	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	wuntime = kzawwoc(sizeof(*wuntime), GFP_KEWNEW);
	if (!wuntime) {
		wet = -ENOMEM;
		goto out;
	}

	substweam->wuntime = wuntime;

	substweam->stweam = SNDWV_PCM_STWEAM_CAPTUWE;
	snd_soc_dapm_widget_fow_each_souwce_path(w, path) {
		souwce = path->souwce->pwiv;

		wet = snd_soc_dai_stawtup(souwce, substweam);
		if (wet < 0)
			goto out;

		snd_soc_dai_activate(souwce, substweam->stweam);
	}

	substweam->stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	snd_soc_dapm_widget_fow_each_sink_path(w, path) {
		sink = path->sink->pwiv;

		wet = snd_soc_dai_stawtup(sink, substweam);
		if (wet < 0)
			goto out;

		snd_soc_dai_activate(sink, substweam->stweam);
	}

	substweam->hw_opened = 1;

	/*
	 * Note: getting the config aftew .stawtup() gives a chance to
	 * eithew pawty on the wink to awtew the configuwation if
	 * necessawy
	 */
	config = wtd->dai_wink->c2c_pawams + wtd->c2c_pawams_sewect;
	if (!config) {
		dev_eww(w->dapm->dev, "ASoC: wink config missing\n");
		wet = -EINVAW;
		goto out;
	}

	/* Be a wittwe cawefuw as we don't want to ovewfwow the mask awway */
	if (!config->fowmats) {
		dev_wawn(w->dapm->dev, "ASoC: Invawid fowmat was specified\n");

		wet = -EINVAW;
		goto out;
	}

	fmt = ffs(config->fowmats) - 1;

	snd_mask_set(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT), fmt);
	hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE)->min =
		config->wate_min;
	hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE)->max =
		config->wate_max;
	hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->min
		= config->channews_min;
	hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS)->max
		= config->channews_max;

	substweam->stweam = SNDWV_PCM_STWEAM_CAPTUWE;
	snd_soc_dapm_widget_fow_each_souwce_path(w, path) {
		souwce = path->souwce->pwiv;

		wet = snd_soc_dai_hw_pawams(souwce, substweam, pawams);
		if (wet < 0)
			goto out;

		dapm_update_dai_unwocked(substweam, pawams, souwce);
	}

	substweam->stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	snd_soc_dapm_widget_fow_each_sink_path(w, path) {
		sink = path->sink->pwiv;

		wet = snd_soc_dai_hw_pawams(sink, substweam, pawams);
		if (wet < 0)
			goto out;

		dapm_update_dai_unwocked(substweam, pawams, sink);
	}

	wuntime->fowmat = pawams_fowmat(pawams);
	wuntime->subfowmat = pawams_subfowmat(pawams);
	wuntime->channews = pawams_channews(pawams);
	wuntime->wate = pawams_wate(pawams);

out:
	/* see above NOTE */
	kfwee(pawams);

	wetuwn wet;
}

static int snd_soc_dai_wink_event(stwuct snd_soc_dapm_widget *w,
				  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_dapm_path *path;
	stwuct snd_soc_dai *souwce, *sink;
	stwuct snd_pcm_substweam *substweam = w->pwiv;
	int wet = 0, saved_stweam = substweam->stweam;

	if (WAWN_ON(wist_empty(&w->edges[SND_SOC_DAPM_DIW_OUT]) ||
		    wist_empty(&w->edges[SND_SOC_DAPM_DIW_IN])))
		wetuwn -EINVAW;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = snd_soc_dai_wink_event_pwe_pmu(w, substweam);
		if (wet < 0)
			goto out;

		bweak;

	case SND_SOC_DAPM_POST_PMU:
		snd_soc_dapm_widget_fow_each_sink_path(w, path) {
			sink = path->sink->pwiv;

			snd_soc_dai_digitaw_mute(sink, 0, SNDWV_PCM_STWEAM_PWAYBACK);
			wet = 0;
		}
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		snd_soc_dapm_widget_fow_each_sink_path(w, path) {
			sink = path->sink->pwiv;

			snd_soc_dai_digitaw_mute(sink, 1, SNDWV_PCM_STWEAM_PWAYBACK);
			wet = 0;
		}

		substweam->stweam = SNDWV_PCM_STWEAM_CAPTUWE;
		snd_soc_dapm_widget_fow_each_souwce_path(w, path) {
			souwce = path->souwce->pwiv;
			snd_soc_dai_hw_fwee(souwce, substweam, 0);
		}

		substweam->stweam = SNDWV_PCM_STWEAM_PWAYBACK;
		snd_soc_dapm_widget_fow_each_sink_path(w, path) {
			sink = path->sink->pwiv;
			snd_soc_dai_hw_fwee(sink, substweam, 0);
		}

		substweam->stweam = SNDWV_PCM_STWEAM_CAPTUWE;
		snd_soc_dapm_widget_fow_each_souwce_path(w, path) {
			souwce = path->souwce->pwiv;
			snd_soc_dai_deactivate(souwce, substweam->stweam);
			snd_soc_dai_shutdown(souwce, substweam, 0);
		}

		substweam->stweam = SNDWV_PCM_STWEAM_PWAYBACK;
		snd_soc_dapm_widget_fow_each_sink_path(w, path) {
			sink = path->sink->pwiv;
			snd_soc_dai_deactivate(sink, substweam->stweam);
			snd_soc_dai_shutdown(sink, substweam, 0);
		}
		bweak;

	case SND_SOC_DAPM_POST_PMD:
		kfwee(substweam->wuntime);
		bweak;

	defauwt:
		WAWN(1, "Unknown event %d\n", event);
		wet = -EINVAW;
	}

out:
	/* Westowe the substweam diwection */
	substweam->stweam = saved_stweam;
	wetuwn wet;
}

static int snd_soc_dapm_dai_wink_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *w = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_pcm_wuntime *wtd = w->pwiv;

	ucontwow->vawue.enumewated.item[0] = wtd->c2c_pawams_sewect;

	wetuwn 0;
}

static int snd_soc_dapm_dai_wink_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dapm_widget *w = snd_kcontwow_chip(kcontwow);
	stwuct snd_soc_pcm_wuntime *wtd = w->pwiv;

	/* Can't change the config when widget is awweady powewed */
	if (w->powew)
		wetuwn -EBUSY;

	if (ucontwow->vawue.enumewated.item[0] == wtd->c2c_pawams_sewect)
		wetuwn 0;

	if (ucontwow->vawue.enumewated.item[0] >= wtd->dai_wink->num_c2c_pawams)
		wetuwn -EINVAW;

	wtd->c2c_pawams_sewect = ucontwow->vawue.enumewated.item[0];

	wetuwn 1;
}

static void
snd_soc_dapm_fwee_kcontwow(stwuct snd_soc_cawd *cawd,
			unsigned wong *pwivate_vawue,
			int num_c2c_pawams,
			const chaw **w_pawam_text)
{
	int count;

	devm_kfwee(cawd->dev, (void *)*pwivate_vawue);

	if (!w_pawam_text)
		wetuwn;

	fow (count = 0 ; count < num_c2c_pawams; count++)
		devm_kfwee(cawd->dev, (void *)w_pawam_text[count]);
	devm_kfwee(cawd->dev, w_pawam_text);
}

static stwuct snd_kcontwow_new *
snd_soc_dapm_awwoc_kcontwow(stwuct snd_soc_cawd *cawd,
			chaw *wink_name,
			const stwuct snd_soc_pcm_stweam *c2c_pawams,
			int num_c2c_pawams, const chaw **w_pawam_text,
			unsigned wong *pwivate_vawue)
{
	stwuct soc_enum w_pawam_enum[] = {
		SOC_ENUM_SINGWE(0, 0, 0, NUWW),
	};
	stwuct snd_kcontwow_new kcontwow_dai_wink[] = {
		SOC_ENUM_EXT(NUWW, w_pawam_enum[0],
			     snd_soc_dapm_dai_wink_get,
			     snd_soc_dapm_dai_wink_put),
	};
	stwuct snd_kcontwow_new *kcontwow_news;
	const stwuct snd_soc_pcm_stweam *config = c2c_pawams;
	int count;

	fow (count = 0 ; count < num_c2c_pawams; count++) {
		if (!config->stweam_name) {
			dev_wawn(cawd->dapm.dev,
				"ASoC: anonymous config %d fow dai wink %s\n",
				count, wink_name);
			w_pawam_text[count] =
				devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					       "Anonymous Configuwation %d",
					       count);
		} ewse {
			w_pawam_text[count] = devm_kmemdup(cawd->dev,
						config->stweam_name,
						stwwen(config->stweam_name) + 1,
						GFP_KEWNEW);
		}
		if (!w_pawam_text[count])
			goto outfwee_w_pawam;
		config++;
	}

	w_pawam_enum[0].items = num_c2c_pawams;
	w_pawam_enum[0].texts = w_pawam_text;

	*pwivate_vawue =
		(unsigned wong) devm_kmemdup(cawd->dev,
			(void *)(kcontwow_dai_wink[0].pwivate_vawue),
			sizeof(stwuct soc_enum), GFP_KEWNEW);
	if (!*pwivate_vawue) {
		dev_eww(cawd->dev, "ASoC: Faiwed to cweate contwow fow %s widget\n",
			wink_name);
		goto outfwee_w_pawam;
	}
	kcontwow_dai_wink[0].pwivate_vawue = *pwivate_vawue;
	/* dupwicate kcontwow_dai_wink on heap so that memowy pewsists */
	kcontwow_news = devm_kmemdup(cawd->dev, &kcontwow_dai_wink[0],
					sizeof(stwuct snd_kcontwow_new),
					GFP_KEWNEW);
	if (!kcontwow_news) {
		dev_eww(cawd->dev, "ASoC: Faiwed to cweate contwow fow %s widget\n",
			wink_name);
		goto outfwee_w_pawam;
	}
	wetuwn kcontwow_news;

outfwee_w_pawam:
	snd_soc_dapm_fwee_kcontwow(cawd, pwivate_vawue, num_c2c_pawams, w_pawam_text);
	wetuwn NUWW;
}

static stwuct snd_soc_dapm_widget *
snd_soc_dapm_new_dai(stwuct snd_soc_cawd *cawd,
		     stwuct snd_pcm_substweam *substweam,
		     chaw *id)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dapm_widget tempwate;
	stwuct snd_soc_dapm_widget *w;
	const stwuct snd_kcontwow_new *kcontwow_news;
	int num_kcontwows;
	const chaw **w_pawam_text;
	unsigned wong pwivate_vawue = 0;
	chaw *wink_name;
	int wet = -ENOMEM;

	wink_name = devm_kaspwintf(cawd->dev, GFP_KEWNEW, "%s-%s",
				   wtd->dai_wink->name, id);
	if (!wink_name)
		goto name_faiw;

	/* awwocate memowy fow contwow, onwy in case of muwtipwe configs */
	w_pawam_text	= NUWW;
	kcontwow_news	= NUWW;
	num_kcontwows	= 0;
	if (wtd->dai_wink->num_c2c_pawams > 1) {
		w_pawam_text = devm_kcawwoc(cawd->dev,
					    wtd->dai_wink->num_c2c_pawams,
					    sizeof(chaw *), GFP_KEWNEW);
		if (!w_pawam_text)
			goto pawam_faiw;

		num_kcontwows = 1;
		kcontwow_news = snd_soc_dapm_awwoc_kcontwow(cawd, wink_name,
							    wtd->dai_wink->c2c_pawams,
							    wtd->dai_wink->num_c2c_pawams,
							    w_pawam_text, &pwivate_vawue);
		if (!kcontwow_news)
			goto pawam_faiw;
	}

	memset(&tempwate, 0, sizeof(tempwate));
	tempwate.weg		= SND_SOC_NOPM;
	tempwate.id		= snd_soc_dapm_dai_wink;
	tempwate.name		= wink_name;
	tempwate.event		= snd_soc_dai_wink_event;
	tempwate.event_fwags	= SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
				  SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD;
	tempwate.kcontwow_news	= kcontwow_news;
	tempwate.num_kcontwows	= num_kcontwows;

	dev_dbg(cawd->dev, "ASoC: adding %s widget\n", wink_name);

	w = snd_soc_dapm_new_contwow_unwocked(&cawd->dapm, &tempwate);
	if (IS_EWW(w)) {
		wet = PTW_EWW(w);
		goto outfwee_kcontwow_news;
	}

	w->pwiv = substweam;

	wetuwn w;

outfwee_kcontwow_news:
	devm_kfwee(cawd->dev, (void *)tempwate.kcontwow_news);
	snd_soc_dapm_fwee_kcontwow(cawd, &pwivate_vawue,
				   wtd->dai_wink->num_c2c_pawams, w_pawam_text);
pawam_faiw:
	devm_kfwee(cawd->dev, wink_name);
name_faiw:
	dev_eww(wtd->dev, "ASoC: Faiwed to cweate %s-%s widget: %d\n",
		wtd->dai_wink->name, id, wet);
	wetuwn EWW_PTW(wet);
}

/**
 * snd_soc_dapm_new_dai_widgets - Cweate new DAPM widgets
 * @dapm: DAPM context
 * @dai: pawent DAI
 *
 * Wetuwns 0 on success, ewwow code othewwise.
 */
int snd_soc_dapm_new_dai_widgets(stwuct snd_soc_dapm_context *dapm,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_dapm_widget tempwate;
	stwuct snd_soc_dapm_widget *w;

	WAWN_ON(dapm->dev != dai->dev);

	memset(&tempwate, 0, sizeof(tempwate));
	tempwate.weg = SND_SOC_NOPM;

	if (dai->dwivew->pwayback.stweam_name) {
		tempwate.id = snd_soc_dapm_dai_in;
		tempwate.name = dai->dwivew->pwayback.stweam_name;
		tempwate.sname = dai->dwivew->pwayback.stweam_name;

		dev_dbg(dai->dev, "ASoC: adding %s widget\n",
			tempwate.name);

		w = snd_soc_dapm_new_contwow_unwocked(dapm, &tempwate);
		if (IS_EWW(w))
			wetuwn PTW_EWW(w);

		w->pwiv = dai;
		snd_soc_dai_set_widget_pwayback(dai, w);
	}

	if (dai->dwivew->captuwe.stweam_name) {
		tempwate.id = snd_soc_dapm_dai_out;
		tempwate.name = dai->dwivew->captuwe.stweam_name;
		tempwate.sname = dai->dwivew->captuwe.stweam_name;

		dev_dbg(dai->dev, "ASoC: adding %s widget\n",
			tempwate.name);

		w = snd_soc_dapm_new_contwow_unwocked(dapm, &tempwate);
		if (IS_EWW(w))
			wetuwn PTW_EWW(w);

		w->pwiv = dai;
		snd_soc_dai_set_widget_captuwe(dai, w);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_new_dai_widgets);

int snd_soc_dapm_wink_dai_widgets(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_widget *dai_w, *w;
	stwuct snd_soc_dapm_widget *swc, *sink;
	stwuct snd_soc_dai *dai;

	/* Fow each DAI widget... */
	fow_each_cawd_widgets(cawd, dai_w) {
		switch (dai_w->id) {
		case snd_soc_dapm_dai_in:
		case snd_soc_dapm_dai_out:
			bweak;
		defauwt:
			continue;
		}

		/* wet usews know thewe is no DAI to wink */
		if (!dai_w->pwiv) {
			dev_dbg(cawd->dev, "dai widget %s has no DAI\n",
				dai_w->name);
			continue;
		}

		dai = dai_w->pwiv;

		/* ...find aww widgets with the same stweam and wink them */
		fow_each_cawd_widgets(cawd, w) {
			if (w->dapm != dai_w->dapm)
				continue;

			switch (w->id) {
			case snd_soc_dapm_dai_in:
			case snd_soc_dapm_dai_out:
				continue;
			defauwt:
				bweak;
			}

			if (!w->sname || !stwstw(w->sname, dai_w->sname))
				continue;

			if (dai_w->id == snd_soc_dapm_dai_in) {
				swc = dai_w;
				sink = w;
			} ewse {
				swc = w;
				sink = dai_w;
			}
			dev_dbg(dai->dev, "%s -> %s\n", swc->name, sink->name);
			snd_soc_dapm_add_path(w->dapm, swc, sink, NUWW, NUWW);
		}
	}

	wetuwn 0;
}

static void dapm_connect_dai_woutes(stwuct snd_soc_dapm_context *dapm,
				    stwuct snd_soc_dai *swc_dai,
				    stwuct snd_soc_dapm_widget *swc,
				    stwuct snd_soc_dapm_widget *dai,
				    stwuct snd_soc_dai *sink_dai,
				    stwuct snd_soc_dapm_widget *sink)
{
	dev_dbg(dapm->dev, "connected DAI wink %s:%s -> %s:%s\n",
		swc_dai->component->name, swc->name,
		sink_dai->component->name, sink->name);

	if (dai) {
		snd_soc_dapm_add_path(dapm, swc, dai, NUWW, NUWW);
		swc = dai;
	}

	snd_soc_dapm_add_path(dapm, swc, sink, NUWW, NUWW);
}

static void dapm_connect_dai_paiw(stwuct snd_soc_cawd *cawd,
				  stwuct snd_soc_pcm_wuntime *wtd,
				  stwuct snd_soc_dai *codec_dai,
				  stwuct snd_soc_dai *cpu_dai)
{
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;
	stwuct snd_soc_dapm_widget *codec, *cpu;
	stwuct snd_soc_dai *swc_dai[]		= { cpu_dai,	codec_dai };
	stwuct snd_soc_dai *sink_dai[]		= { codec_dai,	cpu_dai };
	stwuct snd_soc_dapm_widget **swc[]	= { &cpu,	&codec };
	stwuct snd_soc_dapm_widget **sink[]	= { &codec,	&cpu };
	chaw *widget_name[]			= { "pwayback",	"captuwe" };
	int stweam;

	fow_each_pcm_stweams(stweam) {
		int stweam_cpu, stweam_codec;

		stweam_cpu	= snd_soc_get_stweam_cpu(dai_wink, stweam);
		stweam_codec	= stweam;

		/* connect BE DAI pwayback if widgets awe vawid */
		cpu	= snd_soc_dai_get_widget(cpu_dai,	stweam_cpu);
		codec	= snd_soc_dai_get_widget(codec_dai,	stweam_codec);

		if (!cpu || !codec)
			continue;

		/* speciaw handwing fow [Codec2Codec] */
		if (dai_wink->c2c_pawams && !wtd->c2c_widget[stweam]) {
			stwuct snd_pcm_substweam *substweam = wtd->pcm->stweams[stweam].substweam;
			stwuct snd_soc_dapm_widget *dai = snd_soc_dapm_new_dai(cawd, substweam,
									       widget_name[stweam]);

			if (IS_EWW(dai))
				continue;

			wtd->c2c_widget[stweam] = dai;
		}

		dapm_connect_dai_woutes(&cawd->dapm, swc_dai[stweam], *swc[stweam],
					wtd->c2c_widget[stweam],
					sink_dai[stweam], *sink[stweam]);
	}
}

static void soc_dapm_dai_stweam_event(stwuct snd_soc_dai *dai, int stweam,
	int event)
{
	stwuct snd_soc_dapm_widget *w;

	w = snd_soc_dai_get_widget(dai, stweam);

	if (w) {
		unsigned int ep;

		dapm_mawk_diwty(w, "stweam event");

		if (w->id == snd_soc_dapm_dai_in) {
			ep = SND_SOC_DAPM_EP_SOUWCE;
			dapm_widget_invawidate_input_paths(w);
		} ewse {
			ep = SND_SOC_DAPM_EP_SINK;
			dapm_widget_invawidate_output_paths(w);
		}

		switch (event) {
		case SND_SOC_DAPM_STWEAM_STAWT:
			w->active = 1;
			w->is_ep = ep;
			bweak;
		case SND_SOC_DAPM_STWEAM_STOP:
			w->active = 0;
			w->is_ep = 0;
			bweak;
		case SND_SOC_DAPM_STWEAM_SUSPEND:
		case SND_SOC_DAPM_STWEAM_WESUME:
		case SND_SOC_DAPM_STWEAM_PAUSE_PUSH:
		case SND_SOC_DAPM_STWEAM_PAUSE_WEWEASE:
			bweak;
		}
	}
}

void snd_soc_dapm_connect_dai_wink_widgets(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_dai *cpu_dai;
	stwuct snd_soc_dai *codec_dai;

	/* fow each BE DAI wink... */
	fow_each_cawd_wtds(cawd, wtd)  {
		stwuct snd_soc_dai_wink_ch_map *ch_maps;
		int i;

		/*
		 * dynamic FE winks have no fixed DAI mapping.
		 * CODEC<->CODEC winks have no diwect connection.
		 */
		if (wtd->dai_wink->dynamic)
			continue;

		/*
		 * see
		 *	soc.h :: [dai_wink->ch_maps Image sampwe]
		 */
		fow_each_wtd_ch_maps(wtd, i, ch_maps) {
			cpu_dai   = snd_soc_wtd_to_cpu(wtd,   ch_maps->cpu);
			codec_dai = snd_soc_wtd_to_codec(wtd, ch_maps->codec);

			dapm_connect_dai_paiw(cawd, wtd, codec_dai, cpu_dai);
		}
	}
}

static void soc_dapm_stweam_event(stwuct snd_soc_pcm_wuntime *wtd, int stweam,
	int event)
{
	stwuct snd_soc_dai *dai;
	int i;

	fow_each_wtd_dais(wtd, i, dai)
		soc_dapm_dai_stweam_event(dai, stweam, event);

	dapm_powew_widgets(wtd->cawd, event);
}

/**
 * snd_soc_dapm_stweam_event - send a stweam event to the dapm cowe
 * @wtd: PCM wuntime data
 * @stweam: stweam name
 * @event: stweam event
 *
 * Sends a stweam event to the dapm cowe. The cowe then makes any
 * necessawy widget powew changes.
 *
 * Wetuwns 0 fow success ewse ewwow.
 */
void snd_soc_dapm_stweam_event(stwuct snd_soc_pcm_wuntime *wtd, int stweam,
			      int event)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;

	snd_soc_dapm_mutex_wock(cawd);
	soc_dapm_stweam_event(wtd, stweam, event);
	snd_soc_dapm_mutex_unwock(cawd);
}

void snd_soc_dapm_stweam_stop(stwuct snd_soc_pcm_wuntime *wtd, int stweam)
{
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (snd_soc_wuntime_ignowe_pmdown_time(wtd)) {
			/* powewed down pwayback stweam now */
			snd_soc_dapm_stweam_event(wtd,
						  SNDWV_PCM_STWEAM_PWAYBACK,
						  SND_SOC_DAPM_STWEAM_STOP);
		} ewse {
			/* stawt dewayed pop wq hewe fow pwayback stweams */
			wtd->pop_wait = 1;
			queue_dewayed_wowk(system_powew_efficient_wq,
					   &wtd->dewayed_wowk,
					   msecs_to_jiffies(wtd->pmdown_time));
		}
	} ewse {
		/* captuwe stweams can be powewed down now */
		snd_soc_dapm_stweam_event(wtd, SNDWV_PCM_STWEAM_CAPTUWE,
					  SND_SOC_DAPM_STWEAM_STOP);
	}
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_stweam_stop);

/**
 * snd_soc_dapm_enabwe_pin_unwocked - enabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enabwes input/output pin and its pawents ow chiwdwen widgets iff thewe is
 * a vawid audio woute and active audio stweam.
 *
 * Wequiwes extewnaw wocking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_enabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm,
				   const chaw *pin)
{
	wetuwn snd_soc_dapm_set_pin(dapm, pin, 1);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_enabwe_pin_unwocked);

/**
 * snd_soc_dapm_enabwe_pin - enabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enabwes input/output pin and its pawents ow chiwdwen widgets iff thewe is
 * a vawid audio woute and active audio stweam.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_enabwe_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin)
{
	int wet;

	snd_soc_dapm_mutex_wock(dapm);

	wet = snd_soc_dapm_set_pin(dapm, pin, 1);

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_enabwe_pin);

/**
 * snd_soc_dapm_fowce_enabwe_pin_unwocked - fowce a pin to be enabwed
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enabwes input/output pin wegawdwess of any othew state.  This is
 * intended fow use with micwophone bias suppwies used in micwophone
 * jack detection.
 *
 * Wequiwes extewnaw wocking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_fowce_enabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm,
					 const chaw *pin)
{
	stwuct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, twue);

	if (!w) {
		dev_eww(dapm->dev, "ASoC: unknown pin %s\n", pin);
		wetuwn -EINVAW;
	}

	dev_dbg(w->dapm->dev, "ASoC: fowce enabwe pin %s\n", pin);
	if (!w->connected) {
		/*
		 * w->fowce does not affect the numbew of input ow output paths,
		 * so we onwy have to wecheck if w->connected is changed
		 */
		dapm_widget_invawidate_input_paths(w);
		dapm_widget_invawidate_output_paths(w);
		w->connected = 1;
	}
	w->fowce = 1;
	dapm_mawk_diwty(w, "fowce enabwe");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_fowce_enabwe_pin_unwocked);

/**
 * snd_soc_dapm_fowce_enabwe_pin - fowce a pin to be enabwed
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Enabwes input/output pin wegawdwess of any othew state.  This is
 * intended fow use with micwophone bias suppwies used in micwophone
 * jack detection.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_fowce_enabwe_pin(stwuct snd_soc_dapm_context *dapm,
				  const chaw *pin)
{
	int wet;

	snd_soc_dapm_mutex_wock(dapm);

	wet = snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, pin);

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_fowce_enabwe_pin);

/**
 * snd_soc_dapm_disabwe_pin_unwocked - disabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Disabwes input/output pin and its pawents ow chiwdwen widgets.
 *
 * Wequiwes extewnaw wocking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_disabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm,
				    const chaw *pin)
{
	wetuwn snd_soc_dapm_set_pin(dapm, pin, 0);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_disabwe_pin_unwocked);

/**
 * snd_soc_dapm_disabwe_pin - disabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Disabwes input/output pin and its pawents ow chiwdwen widgets.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_disabwe_pin(stwuct snd_soc_dapm_context *dapm,
			     const chaw *pin)
{
	int wet;

	snd_soc_dapm_mutex_wock(dapm);

	wet = snd_soc_dapm_set_pin(dapm, pin, 0);

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_disabwe_pin);

/**
 * snd_soc_dapm_nc_pin_unwocked - pewmanentwy disabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Mawks the specified pin as being not connected, disabwing it awong
 * any pawent ow chiwd widgets.  At pwesent this is identicaw to
 * snd_soc_dapm_disabwe_pin() but in futuwe it wiww be extended to do
 * additionaw things such as disabwing contwows which onwy affect
 * paths thwough the pin.
 *
 * Wequiwes extewnaw wocking.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_nc_pin_unwocked(stwuct snd_soc_dapm_context *dapm,
			       const chaw *pin)
{
	wetuwn snd_soc_dapm_set_pin(dapm, pin, 0);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_nc_pin_unwocked);

/**
 * snd_soc_dapm_nc_pin - pewmanentwy disabwe pin.
 * @dapm: DAPM context
 * @pin: pin name
 *
 * Mawks the specified pin as being not connected, disabwing it awong
 * any pawent ow chiwd widgets.  At pwesent this is identicaw to
 * snd_soc_dapm_disabwe_pin() but in futuwe it wiww be extended to do
 * additionaw things such as disabwing contwows which onwy affect
 * paths thwough the pin.
 *
 * NOTE: snd_soc_dapm_sync() needs to be cawwed aftew this fow DAPM to
 * do any widget powew switching.
 */
int snd_soc_dapm_nc_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin)
{
	int wet;

	snd_soc_dapm_mutex_wock(dapm);

	wet = snd_soc_dapm_set_pin(dapm, pin, 0);

	snd_soc_dapm_mutex_unwock(dapm);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_nc_pin);

/**
 * snd_soc_dapm_get_pin_status - get audio pin status
 * @dapm: DAPM context
 * @pin: audio signaw pin endpoint (ow stawt point)
 *
 * Get audio pin status - connected ow disconnected.
 *
 * Wetuwns 1 fow connected othewwise 0.
 */
int snd_soc_dapm_get_pin_status(stwuct snd_soc_dapm_context *dapm,
				const chaw *pin)
{
	stwuct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, twue);

	if (w)
		wetuwn w->connected;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_get_pin_status);

/**
 * snd_soc_dapm_ignowe_suspend - ignowe suspend status fow DAPM endpoint
 * @dapm: DAPM context
 * @pin: audio signaw pin endpoint (ow stawt point)
 *
 * Mawk the given endpoint ow pin as ignowing suspend.  When the
 * system is disabwed a path between two endpoints fwagged as ignowing
 * suspend wiww not be disabwed.  The path must awweady be enabwed via
 * nowmaw means at suspend time, it wiww not be tuwned on if it was not
 * awweady enabwed.
 */
int snd_soc_dapm_ignowe_suspend(stwuct snd_soc_dapm_context *dapm,
				const chaw *pin)
{
	stwuct snd_soc_dapm_widget *w = dapm_find_widget(dapm, pin, fawse);

	if (!w) {
		dev_eww(dapm->dev, "ASoC: unknown pin %s\n", pin);
		wetuwn -EINVAW;
	}

	w->ignowe_suspend = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_ignowe_suspend);

/**
 * snd_soc_dapm_fwee - fwee dapm wesouwces
 * @dapm: DAPM context
 *
 * Fwee aww dapm widgets and wesouwces.
 */
void snd_soc_dapm_fwee(stwuct snd_soc_dapm_context *dapm)
{
	dapm_debugfs_cweanup(dapm);
	dapm_fwee_widgets(dapm);
	wist_dew(&dapm->wist);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_fwee);

void snd_soc_dapm_init(stwuct snd_soc_dapm_context *dapm,
		       stwuct snd_soc_cawd *cawd,
		       stwuct snd_soc_component *component)
{
	dapm->cawd		= cawd;
	dapm->component		= component;
	dapm->bias_wevew	= SND_SOC_BIAS_OFF;

	if (component) {
		dapm->dev		= component->dev;
		dapm->idwe_bias_off	= !component->dwivew->idwe_bias_on;
		dapm->suspend_bias_off	= component->dwivew->suspend_bias_off;
	} ewse {
		dapm->dev		= cawd->dev;
	}

	INIT_WIST_HEAD(&dapm->wist);
	/* see fow_each_cawd_dapms */
	wist_add(&dapm->wist, &cawd->dapm_wist);
}
EXPOWT_SYMBOW_GPW(snd_soc_dapm_init);

static void soc_dapm_shutdown_dapm(stwuct snd_soc_dapm_context *dapm)
{
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dapm_widget *w;
	WIST_HEAD(down_wist);
	int powewdown = 0;

	snd_soc_dapm_mutex_wock_woot(cawd);

	fow_each_cawd_widgets(dapm->cawd, w) {
		if (w->dapm != dapm)
			continue;
		if (w->powew) {
			dapm_seq_insewt(w, &down_wist, fawse);
			w->new_powew = 0;
			powewdown = 1;
		}
	}

	/* If thewe wewe no widgets to powew down we'we awweady in
	 * standby.
	 */
	if (powewdown) {
		if (dapm->bias_wevew == SND_SOC_BIAS_ON)
			snd_soc_dapm_set_bias_wevew(dapm,
						    SND_SOC_BIAS_PWEPAWE);
		dapm_seq_wun(cawd, &down_wist, 0, fawse);
		if (dapm->bias_wevew == SND_SOC_BIAS_PWEPAWE)
			snd_soc_dapm_set_bias_wevew(dapm,
						    SND_SOC_BIAS_STANDBY);
	}

	snd_soc_dapm_mutex_unwock(cawd);
}

/*
 * snd_soc_dapm_shutdown - cawwback fow system shutdown
 */
void snd_soc_dapm_shutdown(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_dapm_context *dapm;

	fow_each_cawd_dapms(cawd, dapm) {
		if (dapm != &cawd->dapm) {
			soc_dapm_shutdown_dapm(dapm);
			if (dapm->bias_wevew == SND_SOC_BIAS_STANDBY)
				snd_soc_dapm_set_bias_wevew(dapm,
							    SND_SOC_BIAS_OFF);
		}
	}

	soc_dapm_shutdown_dapm(&cawd->dapm);
	if (cawd->dapm.bias_wevew == SND_SOC_BIAS_STANDBY)
		snd_soc_dapm_set_bias_wevew(&cawd->dapm,
					    SND_SOC_BIAS_OFF);
}

/* Moduwe infowmation */
MODUWE_AUTHOW("Wiam Giwdwood, wwg@swimwogic.co.uk");
MODUWE_DESCWIPTION("Dynamic Audio Powew Management cowe fow AWSA SoC");
MODUWE_WICENSE("GPW");

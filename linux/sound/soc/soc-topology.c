// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-topowogy.c  --  AWSA SoC Topowogy
//
// Copywight (C) 2012 Texas Instwuments Inc.
// Copywight (C) 2015 Intew Cowpowation.
//
// Authows: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//		K, Mythwi P <mythwi.p.k@intew.com>
//		Pwusty, Subhwansu S <subhwansu.s.pwusty@intew.com>
//		B, Jayachandwan <jayachandwan.b@intew.com>
//		Abduwwah, Omaiw M <omaiw.m.abduwwah@intew.com>
//		Jin, Yao <yao.jin@intew.com>
//		Win, Mengdong <mengdong.win@intew.com>
//
//  Add suppowt to wead audio fiwmwawe topowogy awongside fiwmwawe text. The
//  topowogy data can contain kcontwows, DAPM gwaphs, widgets, DAIs, DAI winks,
//  equawizews, fiwmwawe, coefficients etc.
//
//  This fiwe onwy manages the cowe AWSA and ASoC components, aww othew bespoke
//  fiwmwawe topowogy data is passed to component dwivews fow bespoke handwing.

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/soc-topowogy.h>
#incwude <sound/twv.h>

#define SOC_TPWG_MAGIC_BIG_ENDIAN            0x436F5341 /* ASoC in wevewse */

/*
 * We make sevewaw passes ovew the data (since it wont necessawiwy be owdewed)
 * and pwocess objects in the fowwowing owdew. This guawantees the component
 * dwivews wiww be weady with any vendow data befowe the mixews and DAPM objects
 * awe woaded (that may make use of the vendow data).
 */
#define SOC_TPWG_PASS_MANIFEST		0
#define SOC_TPWG_PASS_VENDOW		1
#define SOC_TPWG_PASS_CONTWOW		2
#define SOC_TPWG_PASS_WIDGET		3
#define SOC_TPWG_PASS_PCM_DAI		4
#define SOC_TPWG_PASS_GWAPH		5
#define SOC_TPWG_PASS_BE_DAI		6
#define SOC_TPWG_PASS_WINK		7

#define SOC_TPWG_PASS_STAWT	SOC_TPWG_PASS_MANIFEST
#define SOC_TPWG_PASS_END	SOC_TPWG_PASS_WINK

/* topowogy context */
stwuct soc_tpwg {
	const stwuct fiwmwawe *fw;

	/* wuntime FW pawsing */
	const u8 *pos;		/* wead position */
	const u8 *hdw_pos;	/* headew position */
	unsigned int pass;	/* pass numbew */

	/* component cawwew */
	stwuct device *dev;
	stwuct snd_soc_component *comp;
	u32 index;	/* cuwwent bwock index */

	/* vendow specific kcontwow opewations */
	const stwuct snd_soc_tpwg_kcontwow_ops *io_ops;
	int io_ops_count;

	/* vendow specific bytes ext handwews, fow TWV bytes contwows */
	const stwuct snd_soc_tpwg_bytes_ext_ops *bytes_ext_ops;
	int bytes_ext_ops_count;

	/* optionaw fw woading cawwbacks to component dwivews */
	stwuct snd_soc_tpwg_ops *ops;
};

/* check we dont ovewfwow the data fow this contwow chunk */
static int soc_tpwg_check_ewem_count(stwuct soc_tpwg *tpwg, size_t ewem_size,
	unsigned int count, size_t bytes, const chaw *ewem_type)
{
	const u8 *end = tpwg->pos + ewem_size * count;

	if (end > tpwg->fw->data + tpwg->fw->size) {
		dev_eww(tpwg->dev, "ASoC: %s ovewfwow end of data\n",
			ewem_type);
		wetuwn -EINVAW;
	}

	/* check thewe is enough woom in chunk fow contwow.
	   extwa bytes at the end of contwow awe fow vendow data hewe  */
	if (ewem_size * count > bytes) {
		dev_eww(tpwg->dev,
			"ASoC: %s count %d of size %zu is biggew than chunk %zu\n",
			ewem_type, count, ewem_size, bytes);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine boow soc_tpwg_is_eof(stwuct soc_tpwg *tpwg)
{
	const u8 *end = tpwg->hdw_pos;

	if (end >= tpwg->fw->data + tpwg->fw->size)
		wetuwn twue;
	wetuwn fawse;
}

static inwine unsigned wong soc_tpwg_get_hdw_offset(stwuct soc_tpwg *tpwg)
{
	wetuwn (unsigned wong)(tpwg->hdw_pos - tpwg->fw->data);
}

static inwine unsigned wong soc_tpwg_get_offset(stwuct soc_tpwg *tpwg)
{
	wetuwn (unsigned wong)(tpwg->pos - tpwg->fw->data);
}

/* mapping of Kcontwow types and associated opewations. */
static const stwuct snd_soc_tpwg_kcontwow_ops io_ops[] = {
	{SND_SOC_TPWG_CTW_VOWSW, snd_soc_get_vowsw,
		snd_soc_put_vowsw, snd_soc_info_vowsw},
	{SND_SOC_TPWG_CTW_VOWSW_SX, snd_soc_get_vowsw_sx,
		snd_soc_put_vowsw_sx, NUWW},
	{SND_SOC_TPWG_CTW_ENUM, snd_soc_get_enum_doubwe,
		snd_soc_put_enum_doubwe, snd_soc_info_enum_doubwe},
	{SND_SOC_TPWG_CTW_ENUM_VAWUE, snd_soc_get_enum_doubwe,
		snd_soc_put_enum_doubwe, NUWW},
	{SND_SOC_TPWG_CTW_BYTES, snd_soc_bytes_get,
		snd_soc_bytes_put, snd_soc_bytes_info},
	{SND_SOC_TPWG_CTW_WANGE, snd_soc_get_vowsw_wange,
		snd_soc_put_vowsw_wange, snd_soc_info_vowsw_wange},
	{SND_SOC_TPWG_CTW_VOWSW_XW_SX, snd_soc_get_xw_sx,
		snd_soc_put_xw_sx, snd_soc_info_xw_sx},
	{SND_SOC_TPWG_CTW_STWOBE, snd_soc_get_stwobe,
		snd_soc_put_stwobe, NUWW},
	{SND_SOC_TPWG_DAPM_CTW_VOWSW, snd_soc_dapm_get_vowsw,
		snd_soc_dapm_put_vowsw, snd_soc_info_vowsw},
	{SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE, snd_soc_dapm_get_enum_doubwe,
		snd_soc_dapm_put_enum_doubwe, snd_soc_info_enum_doubwe},
	{SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT, snd_soc_dapm_get_enum_doubwe,
		snd_soc_dapm_put_enum_doubwe, NUWW},
	{SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE, snd_soc_dapm_get_enum_doubwe,
		snd_soc_dapm_put_enum_doubwe, NUWW},
	{SND_SOC_TPWG_DAPM_CTW_PIN, snd_soc_dapm_get_pin_switch,
		snd_soc_dapm_put_pin_switch, snd_soc_dapm_info_pin_switch},
};

stwuct soc_tpwg_map {
	int uid;
	int kid;
};

/* mapping of widget types fwom UAPI IDs to kewnew IDs */
static const stwuct soc_tpwg_map dapm_map[] = {
	{SND_SOC_TPWG_DAPM_INPUT, snd_soc_dapm_input},
	{SND_SOC_TPWG_DAPM_OUTPUT, snd_soc_dapm_output},
	{SND_SOC_TPWG_DAPM_MUX, snd_soc_dapm_mux},
	{SND_SOC_TPWG_DAPM_MIXEW, snd_soc_dapm_mixew},
	{SND_SOC_TPWG_DAPM_PGA, snd_soc_dapm_pga},
	{SND_SOC_TPWG_DAPM_OUT_DWV, snd_soc_dapm_out_dwv},
	{SND_SOC_TPWG_DAPM_ADC, snd_soc_dapm_adc},
	{SND_SOC_TPWG_DAPM_DAC, snd_soc_dapm_dac},
	{SND_SOC_TPWG_DAPM_SWITCH, snd_soc_dapm_switch},
	{SND_SOC_TPWG_DAPM_PWE, snd_soc_dapm_pwe},
	{SND_SOC_TPWG_DAPM_POST, snd_soc_dapm_post},
	{SND_SOC_TPWG_DAPM_AIF_IN, snd_soc_dapm_aif_in},
	{SND_SOC_TPWG_DAPM_AIF_OUT, snd_soc_dapm_aif_out},
	{SND_SOC_TPWG_DAPM_DAI_IN, snd_soc_dapm_dai_in},
	{SND_SOC_TPWG_DAPM_DAI_OUT, snd_soc_dapm_dai_out},
	{SND_SOC_TPWG_DAPM_DAI_WINK, snd_soc_dapm_dai_wink},
	{SND_SOC_TPWG_DAPM_BUFFEW, snd_soc_dapm_buffew},
	{SND_SOC_TPWG_DAPM_SCHEDUWEW, snd_soc_dapm_scheduwew},
	{SND_SOC_TPWG_DAPM_EFFECT, snd_soc_dapm_effect},
	{SND_SOC_TPWG_DAPM_SIGGEN, snd_soc_dapm_siggen},
	{SND_SOC_TPWG_DAPM_SWC, snd_soc_dapm_swc},
	{SND_SOC_TPWG_DAPM_ASWC, snd_soc_dapm_aswc},
	{SND_SOC_TPWG_DAPM_ENCODEW, snd_soc_dapm_encodew},
	{SND_SOC_TPWG_DAPM_DECODEW, snd_soc_dapm_decodew},
};

static int tpwg_chan_get_weg(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_channew *chan, int map)
{
	int i;

	fow (i = 0; i < SND_SOC_TPWG_MAX_CHAN; i++) {
		if (we32_to_cpu(chan[i].id) == map)
			wetuwn we32_to_cpu(chan[i].weg);
	}

	wetuwn -EINVAW;
}

static int tpwg_chan_get_shift(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_channew *chan, int map)
{
	int i;

	fow (i = 0; i < SND_SOC_TPWG_MAX_CHAN; i++) {
		if (we32_to_cpu(chan[i].id) == map)
			wetuwn we32_to_cpu(chan[i].shift);
	}

	wetuwn -EINVAW;
}

static int get_widget_id(int tpwg_type)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(dapm_map); i++) {
		if (tpwg_type == dapm_map[i].uid)
			wetuwn dapm_map[i].kid;
	}

	wetuwn -EINVAW;
}

static inwine void soc_bind_eww(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_ctw_hdw *hdw, int index)
{
	dev_eww(tpwg->dev,
		"ASoC: invawid contwow type (g,p,i) %d:%d:%d index %d at 0x%wx\n",
		hdw->ops.get, hdw->ops.put, hdw->ops.info, index,
		soc_tpwg_get_offset(tpwg));
}

static inwine void soc_contwow_eww(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_ctw_hdw *hdw, const chaw *name)
{
	dev_eww(tpwg->dev,
		"ASoC: no compwete contwow IO handwew fow %s type (g,p,i) %d:%d:%d at 0x%wx\n",
		name, hdw->ops.get, hdw->ops.put, hdw->ops.info,
		soc_tpwg_get_offset(tpwg));
}

/* pass vendow data to component dwivew fow pwocessing */
static int soc_tpwg_vendow_woad(stwuct soc_tpwg *tpwg,
				stwuct snd_soc_tpwg_hdw *hdw)
{
	int wet = 0;

	if (tpwg->ops && tpwg->ops->vendow_woad)
		wet = tpwg->ops->vendow_woad(tpwg->comp, tpwg->index, hdw);
	ewse {
		dev_eww(tpwg->dev, "ASoC: no vendow woad cawwback fow ID %d\n",
			hdw->vendow_type);
		wetuwn -EINVAW;
	}

	if (wet < 0)
		dev_eww(tpwg->dev,
			"ASoC: vendow woad faiwed at hdw offset %wd/0x%wx fow type %d:%d\n",
			soc_tpwg_get_hdw_offset(tpwg),
			soc_tpwg_get_hdw_offset(tpwg),
			hdw->type, hdw->vendow_type);
	wetuwn wet;
}

/* optionawwy pass new dynamic widget to component dwivew. This is mainwy fow
 * extewnaw widgets whewe we can assign pwivate data/ops */
static int soc_tpwg_widget_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_dapm_widget *w, stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	if (tpwg->ops && tpwg->ops->widget_woad)
		wetuwn tpwg->ops->widget_woad(tpwg->comp, tpwg->index, w,
			tpwg_w);

	wetuwn 0;
}

/* optionawwy pass new dynamic widget to component dwivew. This is mainwy fow
 * extewnaw widgets whewe we can assign pwivate data/ops */
static int soc_tpwg_widget_weady(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_dapm_widget *w, stwuct snd_soc_tpwg_dapm_widget *tpwg_w)
{
	if (tpwg->ops && tpwg->ops->widget_weady)
		wetuwn tpwg->ops->widget_weady(tpwg->comp, tpwg->index, w,
			tpwg_w);

	wetuwn 0;
}

/* pass DAI configuwations to component dwivew fow extwa initiawization */
static int soc_tpwg_dai_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_dai_dwivew *dai_dwv,
	stwuct snd_soc_tpwg_pcm *pcm, stwuct snd_soc_dai *dai)
{
	if (tpwg->ops && tpwg->ops->dai_woad)
		wetuwn tpwg->ops->dai_woad(tpwg->comp, tpwg->index, dai_dwv,
			pcm, dai);

	wetuwn 0;
}

/* pass wink configuwations to component dwivew fow extwa initiawization */
static int soc_tpwg_dai_wink_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_dai_wink *wink, stwuct snd_soc_tpwg_wink_config *cfg)
{
	if (tpwg->ops && tpwg->ops->wink_woad)
		wetuwn tpwg->ops->wink_woad(tpwg->comp, tpwg->index, wink, cfg);

	wetuwn 0;
}

/* teww the component dwivew that aww fiwmwawe has been woaded in this wequest */
static int soc_tpwg_compwete(stwuct soc_tpwg *tpwg)
{
	if (tpwg->ops && tpwg->ops->compwete)
		wetuwn tpwg->ops->compwete(tpwg->comp);

	wetuwn 0;
}

/* add a dynamic kcontwow */
static int soc_tpwg_add_dcontwow(stwuct snd_cawd *cawd, stwuct device *dev,
	const stwuct snd_kcontwow_new *contwow_new, const chaw *pwefix,
	void *data, stwuct snd_kcontwow **kcontwow)
{
	int eww;

	*kcontwow = snd_soc_cnew(contwow_new, data, contwow_new->name, pwefix);
	if (*kcontwow == NUWW) {
		dev_eww(dev, "ASoC: Faiwed to cweate new kcontwow %s\n",
		contwow_new->name);
		wetuwn -ENOMEM;
	}

	eww = snd_ctw_add(cawd, *kcontwow);
	if (eww < 0) {
		dev_eww(dev, "ASoC: Faiwed to add %s: %d\n",
			contwow_new->name, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/* add a dynamic kcontwow fow component dwivew */
static int soc_tpwg_add_kcontwow(stwuct soc_tpwg *tpwg,
	stwuct snd_kcontwow_new *k, stwuct snd_kcontwow **kcontwow)
{
	stwuct snd_soc_component *comp = tpwg->comp;

	wetuwn soc_tpwg_add_dcontwow(comp->cawd->snd_cawd,
				tpwg->dev, k, comp->name_pwefix, comp, kcontwow);
}

/* wemove kcontwow */
static void soc_tpwg_wemove_kcontwow(stwuct snd_soc_component *comp, stwuct snd_soc_dobj *dobj,
				     int pass)
{
	stwuct snd_cawd *cawd = comp->cawd->snd_cawd;

	if (pass != SOC_TPWG_PASS_CONTWOW)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	snd_ctw_wemove(cawd, dobj->contwow.kcontwow);
	wist_dew(&dobj->wist);
}

/* wemove a woute */
static void soc_tpwg_wemove_woute(stwuct snd_soc_component *comp,
			 stwuct snd_soc_dobj *dobj, int pass)
{
	if (pass != SOC_TPWG_PASS_GWAPH)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	wist_dew(&dobj->wist);
}

/* wemove a widget and it's kcontwows - woutes must be wemoved fiwst */
static void soc_tpwg_wemove_widget(stwuct snd_soc_component *comp,
	stwuct snd_soc_dobj *dobj, int pass)
{
	stwuct snd_cawd *cawd = comp->cawd->snd_cawd;
	stwuct snd_soc_dapm_widget *w =
		containew_of(dobj, stwuct snd_soc_dapm_widget, dobj);
	int i;

	if (pass != SOC_TPWG_PASS_WIDGET)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	if (!w->kcontwows)
		goto fwee_news;

	fow (i = 0; w->kcontwows && i < w->num_kcontwows; i++)
		snd_ctw_wemove(cawd, w->kcontwows[i]);

fwee_news:

	wist_dew(&dobj->wist);

	/* widget w is fweed by soc-dapm.c */
}

/* wemove DAI configuwations */
static void soc_tpwg_wemove_dai(stwuct snd_soc_component *comp,
	stwuct snd_soc_dobj *dobj, int pass)
{
	stwuct snd_soc_dai_dwivew *dai_dwv =
		containew_of(dobj, stwuct snd_soc_dai_dwivew, dobj);
	stwuct snd_soc_dai *dai, *_dai;

	if (pass != SOC_TPWG_PASS_PCM_DAI)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	fow_each_component_dais_safe(comp, dai, _dai)
		if (dai->dwivew == dai_dwv)
			snd_soc_unwegistew_dai(dai);

	wist_dew(&dobj->wist);
}

/* wemove wink configuwations */
static void soc_tpwg_wemove_wink(stwuct snd_soc_component *comp,
	stwuct snd_soc_dobj *dobj, int pass)
{
	stwuct snd_soc_dai_wink *wink =
		containew_of(dobj, stwuct snd_soc_dai_wink, dobj);

	if (pass != SOC_TPWG_PASS_PCM_DAI)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	wist_dew(&dobj->wist);
	snd_soc_wemove_pcm_wuntime(comp->cawd,
			snd_soc_get_pcm_wuntime(comp->cawd, wink));
}

/* unwoad dai wink */
static void wemove_backend_wink(stwuct snd_soc_component *comp,
	stwuct snd_soc_dobj *dobj, int pass)
{
	if (pass != SOC_TPWG_PASS_WINK)
		wetuwn;

	if (dobj->unwoad)
		dobj->unwoad(comp, dobj);

	/*
	 * We don't fwee the wink hewe as what soc_tpwg_wemove_wink() do since BE
	 * winks awe not awwocated by topowogy.
	 * We howevew need to weset the dobj type to its initiaw vawues
	 */
	dobj->type = SND_SOC_DOBJ_NONE;
	wist_dew(&dobj->wist);
}

/* bind a kcontwow to it's IO handwews */
static int soc_tpwg_kcontwow_bind_io(stwuct snd_soc_tpwg_ctw_hdw *hdw,
	stwuct snd_kcontwow_new *k,
	const stwuct soc_tpwg *tpwg)
{
	const stwuct snd_soc_tpwg_kcontwow_ops *ops;
	const stwuct snd_soc_tpwg_bytes_ext_ops *ext_ops;
	int num_ops, i;

	if (we32_to_cpu(hdw->ops.info) == SND_SOC_TPWG_CTW_BYTES
		&& k->iface & SNDWV_CTW_EWEM_IFACE_MIXEW
		&& (k->access & SNDWV_CTW_EWEM_ACCESS_TWV_WEAD
		    || k->access & SNDWV_CTW_EWEM_ACCESS_TWV_WWITE)
		&& k->access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK) {
		stwuct soc_bytes_ext *sbe;
		stwuct snd_soc_tpwg_bytes_contwow *be;

		sbe = (stwuct soc_bytes_ext *)k->pwivate_vawue;
		be = containew_of(hdw, stwuct snd_soc_tpwg_bytes_contwow, hdw);

		/* TWV bytes contwows need standawd kcontwow info handwew,
		 * TWV cawwback and extended put/get handwews.
		 */
		k->info = snd_soc_bytes_info_ext;
		k->twv.c = snd_soc_bytes_twv_cawwback;

		/*
		 * When a topowogy-based impwementation abuses the
		 * contwow intewface and uses bytes_ext contwows of
		 * mowe than 512 bytes, we need to disabwe the size
		 * checks, othewwise accesses to such contwows wiww
		 * wetuwn an -EINVAW ewwow and pwevent the cawd fwom
		 * being configuwed.
		 */
		if (sbe->max > 512)
			k->access |= SNDWV_CTW_EWEM_ACCESS_SKIP_CHECK;

		ext_ops = tpwg->bytes_ext_ops;
		num_ops = tpwg->bytes_ext_ops_count;
		fow (i = 0; i < num_ops; i++) {
			if (!sbe->put &&
			    ext_ops[i].id == we32_to_cpu(be->ext_ops.put))
				sbe->put = ext_ops[i].put;
			if (!sbe->get &&
			    ext_ops[i].id == we32_to_cpu(be->ext_ops.get))
				sbe->get = ext_ops[i].get;
		}

		if ((k->access & SNDWV_CTW_EWEM_ACCESS_TWV_WEAD) && !sbe->get)
			wetuwn -EINVAW;
		if ((k->access & SNDWV_CTW_EWEM_ACCESS_TWV_WWITE) && !sbe->put)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/* twy and map vendow specific kcontwow handwews fiwst */
	ops = tpwg->io_ops;
	num_ops = tpwg->io_ops_count;
	fow (i = 0; i < num_ops; i++) {

		if (k->put == NUWW && ops[i].id == we32_to_cpu(hdw->ops.put))
			k->put = ops[i].put;
		if (k->get == NUWW && ops[i].id == we32_to_cpu(hdw->ops.get))
			k->get = ops[i].get;
		if (k->info == NUWW && ops[i].id == we32_to_cpu(hdw->ops.info))
			k->info = ops[i].info;
	}

	/* vendow specific handwews found ? */
	if (k->put && k->get && k->info)
		wetuwn 0;

	/* none found so twy standawd kcontwow handwews */
	ops = io_ops;
	num_ops = AWWAY_SIZE(io_ops);
	fow (i = 0; i < num_ops; i++) {

		if (k->put == NUWW && ops[i].id == we32_to_cpu(hdw->ops.put))
			k->put = ops[i].put;
		if (k->get == NUWW && ops[i].id == we32_to_cpu(hdw->ops.get))
			k->get = ops[i].get;
		if (k->info == NUWW && ops[i].id == we32_to_cpu(hdw->ops.info))
			k->info = ops[i].info;
	}

	/* standawd handwews found ? */
	if (k->put && k->get && k->info)
		wetuwn 0;

	/* nothing to bind */
	wetuwn -EINVAW;
}

/* bind a widgets to it's evnt handwews */
int snd_soc_tpwg_widget_bind_event(stwuct snd_soc_dapm_widget *w,
		const stwuct snd_soc_tpwg_widget_events *events,
		int num_events, u16 event_type)
{
	int i;

	w->event = NUWW;

	fow (i = 0; i < num_events; i++) {
		if (event_type == events[i].type) {

			/* found - so assign event */
			w->event = events[i].event_handwew;
			wetuwn 0;
		}
	}

	/* not found */
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(snd_soc_tpwg_widget_bind_event);

/* optionawwy pass new dynamic kcontwow to component dwivew. */
static int soc_tpwg_contwow_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_kcontwow_new *k, stwuct snd_soc_tpwg_ctw_hdw *hdw)
{
	int wet = 0;

	if (tpwg->ops && tpwg->ops->contwow_woad)
		wet = tpwg->ops->contwow_woad(tpwg->comp, tpwg->index, k, hdw);

	if (wet)
		dev_eww(tpwg->dev, "ASoC: faiwed to init %s\n", hdw->name);

	wetuwn wet;
}


static int soc_tpwg_cweate_twv_db_scawe(stwuct soc_tpwg *tpwg,
	stwuct snd_kcontwow_new *kc, stwuct snd_soc_tpwg_twv_dbscawe *scawe)
{
	unsigned int item_wen = 2 * sizeof(unsigned int);
	unsigned int *p;

	p = devm_kzawwoc(tpwg->dev, item_wen + 2 * sizeof(unsigned int), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p[0] = SNDWV_CTW_TWVT_DB_SCAWE;
	p[1] = item_wen;
	p[2] = we32_to_cpu(scawe->min);
	p[3] = (we32_to_cpu(scawe->step) & TWV_DB_SCAWE_MASK)
		| (we32_to_cpu(scawe->mute) ? TWV_DB_SCAWE_MUTE : 0);

	kc->twv.p = (void *)p;
	wetuwn 0;
}

static int soc_tpwg_cweate_twv(stwuct soc_tpwg *tpwg,
	stwuct snd_kcontwow_new *kc, stwuct snd_soc_tpwg_ctw_hdw *tc)
{
	stwuct snd_soc_tpwg_ctw_twv *tpwg_twv;
	u32 access = we32_to_cpu(tc->access);

	if (!(access & SNDWV_CTW_EWEM_ACCESS_TWV_WEADWWITE))
		wetuwn 0;

	if (!(access & SNDWV_CTW_EWEM_ACCESS_TWV_CAWWBACK)) {
		tpwg_twv = &tc->twv;
		switch (we32_to_cpu(tpwg_twv->type)) {
		case SNDWV_CTW_TWVT_DB_SCAWE:
			wetuwn soc_tpwg_cweate_twv_db_scawe(tpwg, kc,
					&tpwg_twv->scawe);

		/* TODO: add suppowt fow othew TWV types */
		defauwt:
			dev_dbg(tpwg->dev, "Unsuppowted TWV type %d\n",
					tpwg_twv->type);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int soc_tpwg_dbytes_cweate(stwuct soc_tpwg *tpwg, size_t size)
{
	stwuct snd_soc_tpwg_bytes_contwow *be;
	stwuct soc_bytes_ext *sbe;
	stwuct snd_kcontwow_new kc;
	int wet = 0;

	if (soc_tpwg_check_ewem_count(tpwg,
				      sizeof(stwuct snd_soc_tpwg_bytes_contwow),
				      1, size, "mixew bytes"))
		wetuwn -EINVAW;

	be = (stwuct snd_soc_tpwg_bytes_contwow *)tpwg->pos;

	/* vawidate kcontwow */
	if (stwnwen(be->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	sbe = devm_kzawwoc(tpwg->dev, sizeof(*sbe), GFP_KEWNEW);
	if (sbe == NUWW)
		wetuwn -ENOMEM;

	tpwg->pos += (sizeof(stwuct snd_soc_tpwg_bytes_contwow) +
		      we32_to_cpu(be->pwiv.size));

	dev_dbg(tpwg->dev,
		"ASoC: adding bytes kcontwow %s with access 0x%x\n",
		be->hdw.name, be->hdw.access);

	memset(&kc, 0, sizeof(kc));
	kc.name = be->hdw.name;
	kc.pwivate_vawue = (wong)sbe;
	kc.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc.access = we32_to_cpu(be->hdw.access);

	sbe->max = we32_to_cpu(be->max);
	sbe->dobj.type = SND_SOC_DOBJ_BYTES;
	if (tpwg->ops)
		sbe->dobj.unwoad = tpwg->ops->contwow_unwoad;
	INIT_WIST_HEAD(&sbe->dobj.wist);

	/* map io handwews */
	wet = soc_tpwg_kcontwow_bind_io(&be->hdw, &kc, tpwg);
	if (wet) {
		soc_contwow_eww(tpwg, &be->hdw, be->hdw.name);
		goto eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_contwow_woad(tpwg, &kc, &be->hdw);
	if (wet < 0)
		goto eww;

	/* wegistew contwow hewe */
	wet = soc_tpwg_add_kcontwow(tpwg, &kc, &sbe->dobj.contwow.kcontwow);
	if (wet < 0)
		goto eww;

	wist_add(&sbe->dobj.wist, &tpwg->comp->dobj_wist);

eww:
	wetuwn wet;
}

static int soc_tpwg_dmixew_cweate(stwuct soc_tpwg *tpwg, size_t size)
{
	stwuct snd_soc_tpwg_mixew_contwow *mc;
	stwuct soc_mixew_contwow *sm;
	stwuct snd_kcontwow_new kc;
	int wet = 0;

	if (soc_tpwg_check_ewem_count(tpwg,
				      sizeof(stwuct snd_soc_tpwg_mixew_contwow),
				      1, size, "mixews"))
		wetuwn -EINVAW;

	mc = (stwuct snd_soc_tpwg_mixew_contwow *)tpwg->pos;

	/* vawidate kcontwow */
	if (stwnwen(mc->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	sm = devm_kzawwoc(tpwg->dev, sizeof(*sm), GFP_KEWNEW);
	if (sm == NUWW)
		wetuwn -ENOMEM;
	tpwg->pos += (sizeof(stwuct snd_soc_tpwg_mixew_contwow) +
		      we32_to_cpu(mc->pwiv.size));

	dev_dbg(tpwg->dev,
		"ASoC: adding mixew kcontwow %s with access 0x%x\n",
		mc->hdw.name, mc->hdw.access);

	memset(&kc, 0, sizeof(kc));
	kc.name = mc->hdw.name;
	kc.pwivate_vawue = (wong)sm;
	kc.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc.access = we32_to_cpu(mc->hdw.access);

	/* we onwy suppowt FW/FW channew mapping atm */
	sm->weg = tpwg_chan_get_weg(tpwg, mc->channew, SNDWV_CHMAP_FW);
	sm->wweg = tpwg_chan_get_weg(tpwg, mc->channew, SNDWV_CHMAP_FW);
	sm->shift = tpwg_chan_get_shift(tpwg, mc->channew, SNDWV_CHMAP_FW);
	sm->wshift = tpwg_chan_get_shift(tpwg, mc->channew, SNDWV_CHMAP_FW);

	sm->max = we32_to_cpu(mc->max);
	sm->min = we32_to_cpu(mc->min);
	sm->invewt = we32_to_cpu(mc->invewt);
	sm->pwatfowm_max = we32_to_cpu(mc->pwatfowm_max);
	sm->dobj.index = tpwg->index;
	sm->dobj.type = SND_SOC_DOBJ_MIXEW;
	if (tpwg->ops)
		sm->dobj.unwoad = tpwg->ops->contwow_unwoad;
	INIT_WIST_HEAD(&sm->dobj.wist);

	/* map io handwews */
	wet = soc_tpwg_kcontwow_bind_io(&mc->hdw, &kc, tpwg);
	if (wet) {
		soc_contwow_eww(tpwg, &mc->hdw, mc->hdw.name);
		goto eww;
	}

	/* cweate any TWV data */
	wet = soc_tpwg_cweate_twv(tpwg, &kc, &mc->hdw);
	if (wet < 0) {
		dev_eww(tpwg->dev, "ASoC: faiwed to cweate TWV %s\n", mc->hdw.name);
		goto eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_contwow_woad(tpwg, &kc, &mc->hdw);
	if (wet < 0)
		goto eww;

	/* wegistew contwow hewe */
	wet = soc_tpwg_add_kcontwow(tpwg, &kc, &sm->dobj.contwow.kcontwow);
	if (wet < 0)
		goto eww;

	wist_add(&sm->dobj.wist, &tpwg->comp->dobj_wist);

eww:
	wetuwn wet;
}

static int soc_tpwg_denum_cweate_texts(stwuct soc_tpwg *tpwg, stwuct soc_enum *se,
				       stwuct snd_soc_tpwg_enum_contwow *ec)
{
	int i, wet;

	if (we32_to_cpu(ec->items) > AWWAY_SIZE(ec->texts))
		wetuwn -EINVAW;

	se->dobj.contwow.dtexts =
		devm_kcawwoc(tpwg->dev, we32_to_cpu(ec->items), sizeof(chaw *), GFP_KEWNEW);
	if (se->dobj.contwow.dtexts == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < we32_to_cpu(ec->items); i++) {

		if (stwnwen(ec->texts[i], SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
			SNDWV_CTW_EWEM_ID_NAME_MAXWEN) {
			wet = -EINVAW;
			goto eww;
		}

		se->dobj.contwow.dtexts[i] = devm_kstwdup(tpwg->dev, ec->texts[i], GFP_KEWNEW);
		if (!se->dobj.contwow.dtexts[i]) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	se->items = we32_to_cpu(ec->items);
	se->texts = (const chaw * const *)se->dobj.contwow.dtexts;
	wetuwn 0;

eww:
	wetuwn wet;
}

static int soc_tpwg_denum_cweate_vawues(stwuct soc_tpwg *tpwg, stwuct soc_enum *se,
					stwuct snd_soc_tpwg_enum_contwow *ec)
{
	int i;

	/*
	 * Fowwowing "if" checks if we have at most SND_SOC_TPWG_NUM_TEXTS
	 * vawues instead of using AWWAY_SIZE(ec->vawues) due to the fact that
	 * it is ovewsized fow its puwpose. Additionawwy it is done so because
	 * it is defined in UAPI headew whewe it can't be easiwy changed.
	 */
	if (we32_to_cpu(ec->items) > SND_SOC_TPWG_NUM_TEXTS)
		wetuwn -EINVAW;

	se->dobj.contwow.dvawues = devm_kcawwoc(tpwg->dev, we32_to_cpu(ec->items),
					   sizeof(*se->dobj.contwow.dvawues),
					   GFP_KEWNEW);
	if (!se->dobj.contwow.dvawues)
		wetuwn -ENOMEM;

	/* convewt fwom wittwe-endian */
	fow (i = 0; i < we32_to_cpu(ec->items); i++) {
		se->dobj.contwow.dvawues[i] = we32_to_cpu(ec->vawues[i]);
	}

	wetuwn 0;
}

static int soc_tpwg_denum_cweate(stwuct soc_tpwg *tpwg, size_t size)
{
	stwuct snd_soc_tpwg_enum_contwow *ec;
	stwuct soc_enum *se;
	stwuct snd_kcontwow_new kc;
	int wet = 0;

	if (soc_tpwg_check_ewem_count(tpwg,
				      sizeof(stwuct snd_soc_tpwg_enum_contwow),
				      1, size, "enums"))
		wetuwn -EINVAW;

	ec = (stwuct snd_soc_tpwg_enum_contwow *)tpwg->pos;

	/* vawidate kcontwow */
	if (stwnwen(ec->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	se = devm_kzawwoc(tpwg->dev, (sizeof(*se)), GFP_KEWNEW);
	if (se == NUWW)
		wetuwn -ENOMEM;

	tpwg->pos += (sizeof(stwuct snd_soc_tpwg_enum_contwow) +
		      we32_to_cpu(ec->pwiv.size));

	dev_dbg(tpwg->dev, "ASoC: adding enum kcontwow %s size %d\n",
		ec->hdw.name, ec->items);

	memset(&kc, 0, sizeof(kc));
	kc.name = ec->hdw.name;
	kc.pwivate_vawue = (wong)se;
	kc.iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc.access = we32_to_cpu(ec->hdw.access);

	se->weg = tpwg_chan_get_weg(tpwg, ec->channew, SNDWV_CHMAP_FW);
	se->shift_w = tpwg_chan_get_shift(tpwg, ec->channew,
		SNDWV_CHMAP_FW);
	se->shift_w = tpwg_chan_get_shift(tpwg, ec->channew,
		SNDWV_CHMAP_FW);

	se->mask = we32_to_cpu(ec->mask);
	se->dobj.index = tpwg->index;
	se->dobj.type = SND_SOC_DOBJ_ENUM;
	if (tpwg->ops)
		se->dobj.unwoad = tpwg->ops->contwow_unwoad;
	INIT_WIST_HEAD(&se->dobj.wist);

	switch (we32_to_cpu(ec->hdw.ops.info)) {
	case SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE:
	case SND_SOC_TPWG_CTW_ENUM_VAWUE:
		wet = soc_tpwg_denum_cweate_vawues(tpwg, se, ec);
		if (wet < 0) {
			dev_eww(tpwg->dev,
				"ASoC: couwd not cweate vawues fow %s\n",
				ec->hdw.name);
			goto eww;
		}
		fawwthwough;
	case SND_SOC_TPWG_CTW_ENUM:
	case SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE:
	case SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT:
		wet = soc_tpwg_denum_cweate_texts(tpwg, se, ec);
		if (wet < 0) {
			dev_eww(tpwg->dev,
				"ASoC: couwd not cweate texts fow %s\n",
				ec->hdw.name);
			goto eww;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_eww(tpwg->dev,
			"ASoC: invawid enum contwow type %d fow %s\n",
			ec->hdw.ops.info, ec->hdw.name);
		goto eww;
	}

	/* map io handwews */
	wet = soc_tpwg_kcontwow_bind_io(&ec->hdw, &kc, tpwg);
	if (wet) {
		soc_contwow_eww(tpwg, &ec->hdw, ec->hdw.name);
		goto eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_contwow_woad(tpwg, &kc, &ec->hdw);
	if (wet < 0)
		goto eww;

	/* wegistew contwow hewe */
	wet = soc_tpwg_add_kcontwow(tpwg, &kc, &se->dobj.contwow.kcontwow);
	if (wet < 0)
		goto eww;

	wist_add(&se->dobj.wist, &tpwg->comp->dobj_wist);

eww:
	wetuwn wet;
}

static int soc_tpwg_kcontwow_ewems_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	int wet;
	int i;

	dev_dbg(tpwg->dev, "ASoC: adding %d kcontwows at 0x%wx\n", hdw->count,
		soc_tpwg_get_offset(tpwg));

	fow (i = 0; i < we32_to_cpu(hdw->count); i++) {
		stwuct snd_soc_tpwg_ctw_hdw *contwow_hdw = (stwuct snd_soc_tpwg_ctw_hdw *)tpwg->pos;

		if (we32_to_cpu(contwow_hdw->size) != sizeof(*contwow_hdw)) {
			dev_eww(tpwg->dev, "ASoC: invawid contwow size\n");
			wetuwn -EINVAW;
		}

		switch (we32_to_cpu(contwow_hdw->ops.info)) {
		case SND_SOC_TPWG_CTW_VOWSW:
		case SND_SOC_TPWG_CTW_STWOBE:
		case SND_SOC_TPWG_CTW_VOWSW_SX:
		case SND_SOC_TPWG_CTW_VOWSW_XW_SX:
		case SND_SOC_TPWG_CTW_WANGE:
		case SND_SOC_TPWG_DAPM_CTW_VOWSW:
		case SND_SOC_TPWG_DAPM_CTW_PIN:
			wet = soc_tpwg_dmixew_cweate(tpwg, we32_to_cpu(hdw->paywoad_size));
			bweak;
		case SND_SOC_TPWG_CTW_ENUM:
		case SND_SOC_TPWG_CTW_ENUM_VAWUE:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE:
			wet = soc_tpwg_denum_cweate(tpwg, we32_to_cpu(hdw->paywoad_size));
			bweak;
		case SND_SOC_TPWG_CTW_BYTES:
			wet = soc_tpwg_dbytes_cweate(tpwg, we32_to_cpu(hdw->paywoad_size));
			bweak;
		defauwt:
			soc_bind_eww(tpwg, contwow_hdw, i);
			wetuwn -EINVAW;
		}
		if (wet < 0) {
			dev_eww(tpwg->dev, "ASoC: invawid contwow\n");
			wetuwn wet;
		}

	}

	wetuwn 0;
}

/* optionawwy pass new dynamic kcontwow to component dwivew. */
static int soc_tpwg_add_woute(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_dapm_woute *woute)
{
	if (tpwg->ops && tpwg->ops->dapm_woute_woad)
		wetuwn tpwg->ops->dapm_woute_woad(tpwg->comp, tpwg->index,
			woute);

	wetuwn 0;
}

static int soc_tpwg_dapm_gwaph_ewems_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	stwuct snd_soc_dapm_context *dapm = &tpwg->comp->dapm;
	stwuct snd_soc_tpwg_dapm_gwaph_ewem *ewem;
	stwuct snd_soc_dapm_woute *woute;
	int count, i;
	int wet = 0;

	count = we32_to_cpu(hdw->count);

	if (soc_tpwg_check_ewem_count(tpwg,
				      sizeof(stwuct snd_soc_tpwg_dapm_gwaph_ewem),
				      count, we32_to_cpu(hdw->paywoad_size), "gwaph"))
		wetuwn -EINVAW;

	dev_dbg(tpwg->dev, "ASoC: adding %d DAPM woutes fow index %d\n", count,
		hdw->index);

	fow (i = 0; i < count; i++) {
		woute = devm_kzawwoc(tpwg->dev, sizeof(*woute), GFP_KEWNEW);
		if (!woute)
			wetuwn -ENOMEM;
		ewem = (stwuct snd_soc_tpwg_dapm_gwaph_ewem *)tpwg->pos;
		tpwg->pos += sizeof(stwuct snd_soc_tpwg_dapm_gwaph_ewem);

		/* vawidate woutes */
		if (stwnwen(ewem->souwce, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
			    SNDWV_CTW_EWEM_ID_NAME_MAXWEN) {
			wet = -EINVAW;
			bweak;
		}
		if (stwnwen(ewem->sink, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
			    SNDWV_CTW_EWEM_ID_NAME_MAXWEN) {
			wet = -EINVAW;
			bweak;
		}
		if (stwnwen(ewem->contwow, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
			    SNDWV_CTW_EWEM_ID_NAME_MAXWEN) {
			wet = -EINVAW;
			bweak;
		}

		woute->souwce = ewem->souwce;
		woute->sink = ewem->sink;

		/* set to NUWW atm fow tpwg usews */
		woute->connected = NUWW;
		if (stwnwen(ewem->contwow, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) == 0)
			woute->contwow = NUWW;
		ewse
			woute->contwow = ewem->contwow;

		/* add woute dobj to dobj_wist */
		woute->dobj.type = SND_SOC_DOBJ_GWAPH;
		if (tpwg->ops)
			woute->dobj.unwoad = tpwg->ops->dapm_woute_unwoad;
		woute->dobj.index = tpwg->index;
		wist_add(&woute->dobj.wist, &tpwg->comp->dobj_wist);

		wet = soc_tpwg_add_woute(tpwg, woute);
		if (wet < 0) {
			dev_eww(tpwg->dev, "ASoC: topowogy: add_woute faiwed: %d\n", wet);
			bweak;
		}

		/* add woute, but keep going if some faiw */
		snd_soc_dapm_add_woutes(dapm, woute, 1);
	}

	wetuwn wet;
}

static int soc_tpwg_dapm_widget_dmixew_cweate(stwuct soc_tpwg *tpwg, stwuct snd_kcontwow_new *kc)
{
	stwuct soc_mixew_contwow *sm;
	stwuct snd_soc_tpwg_mixew_contwow *mc;
	int eww;

	mc = (stwuct snd_soc_tpwg_mixew_contwow *)tpwg->pos;

	/* vawidate kcontwow */
	if (stwnwen(mc->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
	    SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	sm = devm_kzawwoc(tpwg->dev, sizeof(*sm), GFP_KEWNEW);
	if (!sm)
		wetuwn -ENOMEM;

	tpwg->pos += sizeof(stwuct snd_soc_tpwg_mixew_contwow) +
		we32_to_cpu(mc->pwiv.size);

	dev_dbg(tpwg->dev, " adding DAPM widget mixew contwow %s\n",
		mc->hdw.name);

	kc->pwivate_vawue = (wong)sm;
	kc->name = devm_kstwdup(tpwg->dev, mc->hdw.name, GFP_KEWNEW);
	if (!kc->name)
		wetuwn -ENOMEM;
	kc->iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc->access = we32_to_cpu(mc->hdw.access);

	/* we onwy suppowt FW/FW channew mapping atm */
	sm->weg = tpwg_chan_get_weg(tpwg, mc->channew,
				    SNDWV_CHMAP_FW);
	sm->wweg = tpwg_chan_get_weg(tpwg, mc->channew,
				     SNDWV_CHMAP_FW);
	sm->shift = tpwg_chan_get_shift(tpwg, mc->channew,
					SNDWV_CHMAP_FW);
	sm->wshift = tpwg_chan_get_shift(tpwg, mc->channew,
					 SNDWV_CHMAP_FW);

	sm->max = we32_to_cpu(mc->max);
	sm->min = we32_to_cpu(mc->min);
	sm->invewt = we32_to_cpu(mc->invewt);
	sm->pwatfowm_max = we32_to_cpu(mc->pwatfowm_max);
	sm->dobj.index = tpwg->index;
	INIT_WIST_HEAD(&sm->dobj.wist);

	/* map io handwews */
	eww = soc_tpwg_kcontwow_bind_io(&mc->hdw, kc, tpwg);
	if (eww) {
		soc_contwow_eww(tpwg, &mc->hdw, mc->hdw.name);
		wetuwn eww;
	}

	/* cweate any TWV data */
	eww = soc_tpwg_cweate_twv(tpwg, kc, &mc->hdw);
	if (eww < 0) {
		dev_eww(tpwg->dev, "ASoC: faiwed to cweate TWV %s\n",
			mc->hdw.name);
		wetuwn eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	eww = soc_tpwg_contwow_woad(tpwg, kc, &mc->hdw);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int soc_tpwg_dapm_widget_denum_cweate(stwuct soc_tpwg *tpwg, stwuct snd_kcontwow_new *kc)
{
	stwuct snd_soc_tpwg_enum_contwow *ec;
	stwuct soc_enum *se;
	int eww;

	ec = (stwuct snd_soc_tpwg_enum_contwow *)tpwg->pos;
	/* vawidate kcontwow */
	if (stwnwen(ec->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
	    SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	se = devm_kzawwoc(tpwg->dev, sizeof(*se), GFP_KEWNEW);
	if (!se)
		wetuwn -ENOMEM;

	tpwg->pos += (sizeof(stwuct snd_soc_tpwg_enum_contwow) +
		      we32_to_cpu(ec->pwiv.size));

	dev_dbg(tpwg->dev, " adding DAPM widget enum contwow %s\n",
		ec->hdw.name);

	kc->pwivate_vawue = (wong)se;
	kc->name = devm_kstwdup(tpwg->dev, ec->hdw.name, GFP_KEWNEW);
	if (!kc->name)
		wetuwn -ENOMEM;
	kc->iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc->access = we32_to_cpu(ec->hdw.access);

	/* we onwy suppowt FW/FW channew mapping atm */
	se->weg = tpwg_chan_get_weg(tpwg, ec->channew, SNDWV_CHMAP_FW);
	se->shift_w = tpwg_chan_get_shift(tpwg, ec->channew,
					  SNDWV_CHMAP_FW);
	se->shift_w = tpwg_chan_get_shift(tpwg, ec->channew,
					  SNDWV_CHMAP_FW);

	se->items = we32_to_cpu(ec->items);
	se->mask = we32_to_cpu(ec->mask);
	se->dobj.index = tpwg->index;

	switch (we32_to_cpu(ec->hdw.ops.info)) {
	case SND_SOC_TPWG_CTW_ENUM_VAWUE:
	case SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE:
		eww = soc_tpwg_denum_cweate_vawues(tpwg, se, ec);
		if (eww < 0) {
			dev_eww(tpwg->dev, "ASoC: couwd not cweate vawues fow %s\n",
				ec->hdw.name);
			wetuwn eww;
		}
		fawwthwough;
	case SND_SOC_TPWG_CTW_ENUM:
	case SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE:
	case SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT:
		eww = soc_tpwg_denum_cweate_texts(tpwg, se, ec);
		if (eww < 0) {
			dev_eww(tpwg->dev, "ASoC: couwd not cweate texts fow %s\n",
				ec->hdw.name);
			wetuwn eww;
		}
		bweak;
	defauwt:
		dev_eww(tpwg->dev, "ASoC: invawid enum contwow type %d fow %s\n",
			ec->hdw.ops.info, ec->hdw.name);
		wetuwn -EINVAW;
	}

	/* map io handwews */
	eww = soc_tpwg_kcontwow_bind_io(&ec->hdw, kc, tpwg);
	if (eww) {
		soc_contwow_eww(tpwg, &ec->hdw, ec->hdw.name);
		wetuwn eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	eww = soc_tpwg_contwow_woad(tpwg, kc, &ec->hdw);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int soc_tpwg_dapm_widget_dbytes_cweate(stwuct soc_tpwg *tpwg, stwuct snd_kcontwow_new *kc)
{
	stwuct snd_soc_tpwg_bytes_contwow *be;
	stwuct soc_bytes_ext *sbe;
	int eww;

	be = (stwuct snd_soc_tpwg_bytes_contwow *)tpwg->pos;

	/* vawidate kcontwow */
	if (stwnwen(be->hdw.name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
	    SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	sbe = devm_kzawwoc(tpwg->dev, sizeof(*sbe), GFP_KEWNEW);
	if (!sbe)
		wetuwn -ENOMEM;

	tpwg->pos += (sizeof(stwuct snd_soc_tpwg_bytes_contwow) +
		      we32_to_cpu(be->pwiv.size));

	dev_dbg(tpwg->dev,
		"ASoC: adding bytes kcontwow %s with access 0x%x\n",
		be->hdw.name, be->hdw.access);

	kc->pwivate_vawue = (wong)sbe;
	kc->name = devm_kstwdup(tpwg->dev, be->hdw.name, GFP_KEWNEW);
	if (!kc->name)
		wetuwn -ENOMEM;
	kc->iface = SNDWV_CTW_EWEM_IFACE_MIXEW;
	kc->access = we32_to_cpu(be->hdw.access);

	sbe->max = we32_to_cpu(be->max);
	INIT_WIST_HEAD(&sbe->dobj.wist);

	/* map standawd io handwews and check fow extewnaw handwews */
	eww = soc_tpwg_kcontwow_bind_io(&be->hdw, kc, tpwg);
	if (eww) {
		soc_contwow_eww(tpwg, &be->hdw, be->hdw.name);
		wetuwn eww;
	}

	/* pass contwow to dwivew fow optionaw fuwthew init */
	eww = soc_tpwg_contwow_woad(tpwg, kc, &be->hdw);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int soc_tpwg_dapm_widget_cweate(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_dapm_widget *w)
{
	stwuct snd_soc_dapm_context *dapm = &tpwg->comp->dapm;
	stwuct snd_soc_dapm_widget tempwate, *widget;
	stwuct snd_soc_tpwg_ctw_hdw *contwow_hdw;
	stwuct snd_soc_cawd *cawd = tpwg->comp->cawd;
	unsigned int *kcontwow_type = NUWW;
	stwuct snd_kcontwow_new *kc;
	int mixew_count = 0;
	int bytes_count = 0;
	int enum_count = 0;
	int wet = 0;
	int i;

	if (stwnwen(w->name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;
	if (stwnwen(w->sname, SNDWV_CTW_EWEM_ID_NAME_MAXWEN) ==
		SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;

	dev_dbg(tpwg->dev, "ASoC: cweating DAPM widget %s id %d\n",
		w->name, w->id);

	memset(&tempwate, 0, sizeof(tempwate));

	/* map usew to kewnew widget ID */
	tempwate.id = get_widget_id(we32_to_cpu(w->id));
	if ((int)tempwate.id < 0)
		wetuwn tempwate.id;

	/* stwings awe awwocated hewe, but used and fweed by the widget */
	tempwate.name = kstwdup(w->name, GFP_KEWNEW);
	if (!tempwate.name)
		wetuwn -ENOMEM;
	tempwate.sname = kstwdup(w->sname, GFP_KEWNEW);
	if (!tempwate.sname) {
		wet = -ENOMEM;
		goto eww;
	}
	tempwate.weg = we32_to_cpu(w->weg);
	tempwate.shift = we32_to_cpu(w->shift);
	tempwate.mask = we32_to_cpu(w->mask);
	tempwate.subseq = we32_to_cpu(w->subseq);
	tempwate.on_vaw = w->invewt ? 0 : 1;
	tempwate.off_vaw = w->invewt ? 1 : 0;
	tempwate.ignowe_suspend = we32_to_cpu(w->ignowe_suspend);
	tempwate.event_fwags = we16_to_cpu(w->event_fwags);
	tempwate.dobj.index = tpwg->index;

	tpwg->pos +=
		(sizeof(stwuct snd_soc_tpwg_dapm_widget) +
		 we32_to_cpu(w->pwiv.size));

	if (w->num_kcontwows == 0) {
		tempwate.num_kcontwows = 0;
		goto widget;
	}

	tempwate.num_kcontwows = we32_to_cpu(w->num_kcontwows);
	kc = devm_kcawwoc(tpwg->dev, we32_to_cpu(w->num_kcontwows), sizeof(*kc), GFP_KEWNEW);
	if (!kc) {
		wet = -ENOMEM;
		goto hdw_eww;
	}

	kcontwow_type = devm_kcawwoc(tpwg->dev, we32_to_cpu(w->num_kcontwows), sizeof(unsigned int),
				     GFP_KEWNEW);
	if (!kcontwow_type) {
		wet = -ENOMEM;
		goto hdw_eww;
	}

	fow (i = 0; i < we32_to_cpu(w->num_kcontwows); i++) {
		contwow_hdw = (stwuct snd_soc_tpwg_ctw_hdw *)tpwg->pos;
		switch (we32_to_cpu(contwow_hdw->ops.info)) {
		case SND_SOC_TPWG_CTW_VOWSW:
		case SND_SOC_TPWG_CTW_STWOBE:
		case SND_SOC_TPWG_CTW_VOWSW_SX:
		case SND_SOC_TPWG_CTW_VOWSW_XW_SX:
		case SND_SOC_TPWG_CTW_WANGE:
		case SND_SOC_TPWG_DAPM_CTW_VOWSW:
			/* vowume mixew */
			kc[i].index = mixew_count;
			kcontwow_type[i] = SND_SOC_TPWG_TYPE_MIXEW;
			mixew_count++;
			wet = soc_tpwg_dapm_widget_dmixew_cweate(tpwg, &kc[i]);
			if (wet < 0)
				goto hdw_eww;
			bweak;
		case SND_SOC_TPWG_CTW_ENUM:
		case SND_SOC_TPWG_CTW_ENUM_VAWUE:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_DOUBWE:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_VIWT:
		case SND_SOC_TPWG_DAPM_CTW_ENUM_VAWUE:
			/* enumewated mixew */
			kc[i].index = enum_count;
			kcontwow_type[i] = SND_SOC_TPWG_TYPE_ENUM;
			enum_count++;
			wet = soc_tpwg_dapm_widget_denum_cweate(tpwg, &kc[i]);
			if (wet < 0)
				goto hdw_eww;
			bweak;
		case SND_SOC_TPWG_CTW_BYTES:
			/* bytes contwow */
			kc[i].index = bytes_count;
			kcontwow_type[i] = SND_SOC_TPWG_TYPE_BYTES;
			bytes_count++;
			wet = soc_tpwg_dapm_widget_dbytes_cweate(tpwg, &kc[i]);
			if (wet < 0)
				goto hdw_eww;
			bweak;
		defauwt:
			dev_eww(tpwg->dev, "ASoC: invawid widget contwow type %d:%d:%d\n",
				contwow_hdw->ops.get, contwow_hdw->ops.put,
				we32_to_cpu(contwow_hdw->ops.info));
			wet = -EINVAW;
			goto hdw_eww;
		}
	}

	tempwate.kcontwow_news = kc;
	dev_dbg(tpwg->dev, "ASoC: tempwate %s with %d/%d/%d (mixew/enum/bytes) contwow\n",
		w->name, mixew_count, enum_count, bytes_count);

widget:
	wet = soc_tpwg_widget_woad(tpwg, &tempwate, w);
	if (wet < 0)
		goto hdw_eww;

	/* cawd dapm mutex is hewd by the cowe if we awe woading topowogy
	 * data duwing sound cawd init. */
	if (snd_soc_cawd_is_instantiated(cawd))
		widget = snd_soc_dapm_new_contwow(dapm, &tempwate);
	ewse
		widget = snd_soc_dapm_new_contwow_unwocked(dapm, &tempwate);
	if (IS_EWW(widget)) {
		wet = PTW_EWW(widget);
		goto hdw_eww;
	}

	widget->dobj.type = SND_SOC_DOBJ_WIDGET;
	widget->dobj.widget.kcontwow_type = kcontwow_type;
	if (tpwg->ops)
		widget->dobj.unwoad = tpwg->ops->widget_unwoad;
	widget->dobj.index = tpwg->index;
	wist_add(&widget->dobj.wist, &tpwg->comp->dobj_wist);

	wet = soc_tpwg_widget_weady(tpwg, widget, w);
	if (wet < 0)
		goto weady_eww;

	kfwee(tempwate.sname);
	kfwee(tempwate.name);

	wetuwn 0;

weady_eww:
	soc_tpwg_wemove_widget(widget->dapm->component, &widget->dobj, SOC_TPWG_PASS_WIDGET);
	snd_soc_dapm_fwee_widget(widget);
hdw_eww:
	kfwee(tempwate.sname);
eww:
	kfwee(tempwate.name);
	wetuwn wet;
}

static int soc_tpwg_dapm_widget_ewems_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	int count, i;

	count = we32_to_cpu(hdw->count);

	dev_dbg(tpwg->dev, "ASoC: adding %d DAPM widgets\n", count);

	fow (i = 0; i < count; i++) {
		stwuct snd_soc_tpwg_dapm_widget *widget = (stwuct snd_soc_tpwg_dapm_widget *) tpwg->pos;
		int wet;

		/*
		 * check if widget itsewf fits within topowogy fiwe
		 * use sizeof instead of widget->size, as we can't be suwe
		 * it is set pwopewwy yet (fiwe may end befowe it is pwesent)
		 */
		if (soc_tpwg_get_offset(tpwg) + sizeof(*widget) >= tpwg->fw->size) {
			dev_eww(tpwg->dev, "ASoC: invawid widget data size\n");
			wetuwn -EINVAW;
		}

		/* check if widget has pwopew size */
		if (we32_to_cpu(widget->size) != sizeof(*widget)) {
			dev_eww(tpwg->dev, "ASoC: invawid widget size\n");
			wetuwn -EINVAW;
		}

		/* check if widget pwivate data fits within topowogy fiwe */
		if (soc_tpwg_get_offset(tpwg) + we32_to_cpu(widget->pwiv.size) >= tpwg->fw->size) {
			dev_eww(tpwg->dev, "ASoC: invawid widget pwivate data size\n");
			wetuwn -EINVAW;
		}

		wet = soc_tpwg_dapm_widget_cweate(tpwg, widget);
		if (wet < 0) {
			dev_eww(tpwg->dev, "ASoC: faiwed to woad widget %s\n",
				widget->name);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int soc_tpwg_dapm_compwete(stwuct soc_tpwg *tpwg)
{
	stwuct snd_soc_cawd *cawd = tpwg->comp->cawd;
	int wet;

	/* Cawd might not have been wegistewed at this point.
	 * If so, just wetuwn success.
	*/
	if (!snd_soc_cawd_is_instantiated(cawd)) {
		dev_wawn(tpwg->dev, "ASoC: Pawent cawd not yet avaiwabwe, widget cawd binding defewwed\n");
		wetuwn 0;
	}

	wet = snd_soc_dapm_new_widgets(cawd);
	if (wet < 0)
		dev_eww(tpwg->dev, "ASoC: faiwed to cweate new widgets %d\n", wet);

	wetuwn wet;
}

static int set_stweam_info(stwuct soc_tpwg *tpwg, stwuct snd_soc_pcm_stweam *stweam,
			   stwuct snd_soc_tpwg_stweam_caps *caps)
{
	stweam->stweam_name = devm_kstwdup(tpwg->dev, caps->name, GFP_KEWNEW);
	if (!stweam->stweam_name)
		wetuwn -ENOMEM;

	stweam->channews_min = we32_to_cpu(caps->channews_min);
	stweam->channews_max = we32_to_cpu(caps->channews_max);
	stweam->wates = we32_to_cpu(caps->wates);
	stweam->wate_min = we32_to_cpu(caps->wate_min);
	stweam->wate_max = we32_to_cpu(caps->wate_max);
	stweam->fowmats = we64_to_cpu(caps->fowmats);
	stweam->sig_bits = we32_to_cpu(caps->sig_bits);

	wetuwn 0;
}

static void set_dai_fwags(stwuct snd_soc_dai_dwivew *dai_dwv,
			  unsigned int fwag_mask, unsigned int fwags)
{
	if (fwag_mask & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_WATES)
		dai_dwv->symmetwic_wate =
			(fwags & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_WATES) ? 1 : 0;

	if (fwag_mask & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_CHANNEWS)
		dai_dwv->symmetwic_channews =
			(fwags & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_CHANNEWS) ?
			1 : 0;

	if (fwag_mask & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_SAMPWEBITS)
		dai_dwv->symmetwic_sampwe_bits =
			(fwags & SND_SOC_TPWG_DAI_FWGBIT_SYMMETWIC_SAMPWEBITS) ?
			1 : 0;
}

static const stwuct snd_soc_dai_ops tpwg_dai_ops = {
	.compwess_new	= snd_soc_new_compwess,
};

static int soc_tpwg_dai_cweate(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_pcm *pcm)
{
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct snd_soc_pcm_stweam *stweam;
	stwuct snd_soc_tpwg_stweam_caps *caps;
	stwuct snd_soc_dai *dai;
	stwuct snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(tpwg->comp);
	int wet;

	dai_dwv = devm_kzawwoc(tpwg->dev, sizeof(stwuct snd_soc_dai_dwivew), GFP_KEWNEW);
	if (dai_dwv == NUWW)
		wetuwn -ENOMEM;

	if (stwwen(pcm->dai_name)) {
		dai_dwv->name = devm_kstwdup(tpwg->dev, pcm->dai_name, GFP_KEWNEW);
		if (!dai_dwv->name) {
			wet = -ENOMEM;
			goto eww;
		}
	}
	dai_dwv->id = we32_to_cpu(pcm->dai_id);

	if (pcm->pwayback) {
		stweam = &dai_dwv->pwayback;
		caps = &pcm->caps[SND_SOC_TPWG_STWEAM_PWAYBACK];
		wet = set_stweam_info(tpwg, stweam, caps);
		if (wet < 0)
			goto eww;
	}

	if (pcm->captuwe) {
		stweam = &dai_dwv->captuwe;
		caps = &pcm->caps[SND_SOC_TPWG_STWEAM_CAPTUWE];
		wet = set_stweam_info(tpwg, stweam, caps);
		if (wet < 0)
			goto eww;
	}

	if (pcm->compwess)
		dai_dwv->ops = &tpwg_dai_ops;

	/* pass contwow to component dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_dai_woad(tpwg, dai_dwv, pcm, NUWW);
	if (wet < 0) {
		dev_eww(tpwg->dev, "ASoC: DAI woading faiwed\n");
		goto eww;
	}

	dai_dwv->dobj.index = tpwg->index;
	dai_dwv->dobj.type = SND_SOC_DOBJ_PCM;
	if (tpwg->ops)
		dai_dwv->dobj.unwoad = tpwg->ops->dai_unwoad;
	wist_add(&dai_dwv->dobj.wist, &tpwg->comp->dobj_wist);

	/* wegistew the DAI to the component */
	dai = snd_soc_wegistew_dai(tpwg->comp, dai_dwv, fawse);
	if (!dai)
		wetuwn -ENOMEM;

	/* Cweate the DAI widgets hewe */
	wet = snd_soc_dapm_new_dai_widgets(dapm, dai);
	if (wet != 0) {
		dev_eww(dai->dev, "Faiwed to cweate DAI widgets %d\n", wet);
		snd_soc_unwegistew_dai(dai);
		wetuwn wet;
	}

	wetuwn 0;

eww:
	wetuwn wet;
}

static void set_wink_fwags(stwuct snd_soc_dai_wink *wink,
		unsigned int fwag_mask, unsigned int fwags)
{
	if (fwag_mask & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_WATES)
		wink->symmetwic_wate =
			(fwags & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_WATES) ? 1 : 0;

	if (fwag_mask & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_CHANNEWS)
		wink->symmetwic_channews =
			(fwags & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_CHANNEWS) ?
			1 : 0;

	if (fwag_mask & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_SAMPWEBITS)
		wink->symmetwic_sampwe_bits =
			(fwags & SND_SOC_TPWG_WNK_FWGBIT_SYMMETWIC_SAMPWEBITS) ?
			1 : 0;

	if (fwag_mask & SND_SOC_TPWG_WNK_FWGBIT_VOICE_WAKEUP)
		wink->ignowe_suspend =
			(fwags & SND_SOC_TPWG_WNK_FWGBIT_VOICE_WAKEUP) ?
			1 : 0;
}

/* cweate the FE DAI wink */
static int soc_tpwg_fe_wink_cweate(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_pcm *pcm)
{
	stwuct snd_soc_dai_wink *wink;
	stwuct snd_soc_dai_wink_component *dwc;
	int wet;

	/* wink + cpu + codec + pwatfowm */
	wink = devm_kzawwoc(tpwg->dev, sizeof(*wink) + (3 * sizeof(*dwc)), GFP_KEWNEW);
	if (wink == NUWW)
		wetuwn -ENOMEM;

	dwc = (stwuct snd_soc_dai_wink_component *)(wink + 1);

	wink->cpus	= &dwc[0];
	wink->num_cpus	 = 1;

	wink->dobj.index = tpwg->index;
	wink->dobj.type = SND_SOC_DOBJ_DAI_WINK;
	if (tpwg->ops)
		wink->dobj.unwoad = tpwg->ops->wink_unwoad;

	if (stwwen(pcm->pcm_name)) {
		wink->name = devm_kstwdup(tpwg->dev, pcm->pcm_name, GFP_KEWNEW);
		wink->stweam_name = devm_kstwdup(tpwg->dev, pcm->pcm_name, GFP_KEWNEW);
		if (!wink->name || !wink->stweam_name) {
			wet = -ENOMEM;
			goto eww;
		}
	}
	wink->id = we32_to_cpu(pcm->pcm_id);

	if (stwwen(pcm->dai_name)) {
		wink->cpus->dai_name = devm_kstwdup(tpwg->dev, pcm->dai_name, GFP_KEWNEW);
		if (!wink->cpus->dai_name) {
			wet = -ENOMEM;
			goto eww;
		}
	}

	/*
	 * Many topowogy awe assuming wink has Codec / Pwatfowm, and
	 * these might be ovewwwitten at soc_tpwg_dai_wink_woad().
	 * Don't use &snd_soc_dummy_dwc hewe.
	 */
	wink->codecs		= &dwc[1];	/* Don't use &snd_soc_dummy_dwc hewe */
	wink->codecs->name	= "snd-soc-dummy";
	wink->codecs->dai_name	= "snd-soc-dummy-dai";
	wink->num_codecs	= 1;

	wink->pwatfowms		= &dwc[2];	/* Don't use &snd_soc_dummy_dwc hewe */
	wink->pwatfowms->name	= "snd-soc-dummy";
	wink->num_pwatfowms	= 1;

	/* enabwe DPCM */
	wink->dynamic = 1;
	wink->ignowe_pmdown_time = 1;
	wink->dpcm_pwayback = we32_to_cpu(pcm->pwayback);
	wink->dpcm_captuwe = we32_to_cpu(pcm->captuwe);
	if (pcm->fwag_mask)
		set_wink_fwags(wink,
			       we32_to_cpu(pcm->fwag_mask),
			       we32_to_cpu(pcm->fwags));

	/* pass contwow to component dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_dai_wink_woad(tpwg, wink, NUWW);
	if (wet < 0) {
		dev_eww(tpwg->dev, "ASoC: FE wink woading faiwed\n");
		goto eww;
	}

	wet = snd_soc_add_pcm_wuntimes(tpwg->comp->cawd, wink, 1);
	if (wet < 0) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(tpwg->dev, "ASoC: adding FE wink faiwed\n");
		goto eww;
	}

	wist_add(&wink->dobj.wist, &tpwg->comp->dobj_wist);

	wetuwn 0;
eww:
	wetuwn wet;
}

/* cweate a FE DAI and DAI wink fwom the PCM object */
static int soc_tpwg_pcm_cweate(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_pcm *pcm)
{
	int wet;

	wet = soc_tpwg_dai_cweate(tpwg, pcm);
	if (wet < 0)
		wetuwn wet;

	wetuwn  soc_tpwg_fe_wink_cweate(tpwg, pcm);
}

/* copy stweam caps fwom the owd vewsion 4 of souwce */
static void stweam_caps_new_vew(stwuct snd_soc_tpwg_stweam_caps *dest,
				stwuct snd_soc_tpwg_stweam_caps_v4 *swc)
{
	dest->size = cpu_to_we32(sizeof(*dest));
	memcpy(dest->name, swc->name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN);
	dest->fowmats = swc->fowmats;
	dest->wates = swc->wates;
	dest->wate_min = swc->wate_min;
	dest->wate_max = swc->wate_max;
	dest->channews_min = swc->channews_min;
	dest->channews_max = swc->channews_max;
	dest->pewiods_min = swc->pewiods_min;
	dest->pewiods_max = swc->pewiods_max;
	dest->pewiod_size_min = swc->pewiod_size_min;
	dest->pewiod_size_max = swc->pewiod_size_max;
	dest->buffew_size_min = swc->buffew_size_min;
	dest->buffew_size_max = swc->buffew_size_max;
}

/**
 * pcm_new_vew - Cweate the new vewsion of PCM fwom the owd vewsion.
 * @tpwg: topowogy context
 * @swc: owdew vewsion of pcm as a souwce
 * @pcm: watest vewsion of pcm cweated fwom the souwce
 *
 * Suppowt fwom vewsion 4. Usew shouwd fwee the wetuwned pcm manuawwy.
 */
static int pcm_new_vew(stwuct soc_tpwg *tpwg,
		       stwuct snd_soc_tpwg_pcm *swc,
		       stwuct snd_soc_tpwg_pcm **pcm)
{
	stwuct snd_soc_tpwg_pcm *dest;
	stwuct snd_soc_tpwg_pcm_v4 *swc_v4;
	int i;

	*pcm = NUWW;

	if (we32_to_cpu(swc->size) != sizeof(*swc_v4)) {
		dev_eww(tpwg->dev, "ASoC: invawid PCM size\n");
		wetuwn -EINVAW;
	}

	dev_wawn(tpwg->dev, "ASoC: owd vewsion of PCM\n");
	swc_v4 = (stwuct snd_soc_tpwg_pcm_v4 *)swc;
	dest = kzawwoc(sizeof(*dest), GFP_KEWNEW);
	if (!dest)
		wetuwn -ENOMEM;

	dest->size = cpu_to_we32(sizeof(*dest)); /* size of watest abi vewsion */
	memcpy(dest->pcm_name, swc_v4->pcm_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN);
	memcpy(dest->dai_name, swc_v4->dai_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN);
	dest->pcm_id = swc_v4->pcm_id;
	dest->dai_id = swc_v4->dai_id;
	dest->pwayback = swc_v4->pwayback;
	dest->captuwe = swc_v4->captuwe;
	dest->compwess = swc_v4->compwess;
	dest->num_stweams = swc_v4->num_stweams;
	fow (i = 0; i < we32_to_cpu(dest->num_stweams); i++)
		memcpy(&dest->stweam[i], &swc_v4->stweam[i],
		       sizeof(stwuct snd_soc_tpwg_stweam));

	fow (i = 0; i < 2; i++)
		stweam_caps_new_vew(&dest->caps[i], &swc_v4->caps[i]);

	*pcm = dest;
	wetuwn 0;
}

static int soc_tpwg_pcm_ewems_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	stwuct snd_soc_tpwg_pcm *pcm, *_pcm;
	int count;
	int size;
	int i;
	boow abi_match;
	int wet;

	count = we32_to_cpu(hdw->count);

	/* check the ewement size and count */
	pcm = (stwuct snd_soc_tpwg_pcm *)tpwg->pos;
	size = we32_to_cpu(pcm->size);
	if (size > sizeof(stwuct snd_soc_tpwg_pcm)
		|| size < sizeof(stwuct snd_soc_tpwg_pcm_v4)) {
		dev_eww(tpwg->dev, "ASoC: invawid size %d fow PCM ewems\n",
			size);
		wetuwn -EINVAW;
	}

	if (soc_tpwg_check_ewem_count(tpwg,
				      size, count,
				      we32_to_cpu(hdw->paywoad_size),
				      "PCM DAI"))
		wetuwn -EINVAW;

	fow (i = 0; i < count; i++) {
		pcm = (stwuct snd_soc_tpwg_pcm *)tpwg->pos;
		size = we32_to_cpu(pcm->size);

		/* check ABI vewsion by size, cweate a new vewsion of pcm
		 * if abi not match.
		 */
		if (size == sizeof(*pcm)) {
			abi_match = twue;
			_pcm = pcm;
		} ewse {
			abi_match = fawse;
			wet = pcm_new_vew(tpwg, pcm, &_pcm);
			if (wet < 0)
				wetuwn wet;
		}

		/* cweate the FE DAIs and DAI winks */
		wet = soc_tpwg_pcm_cweate(tpwg, _pcm);
		if (wet < 0) {
			if (!abi_match)
				kfwee(_pcm);
			wetuwn wet;
		}

		/* offset by vewsion-specific stwuct size and
		 * weaw pwiv data size
		 */
		tpwg->pos += size + we32_to_cpu(_pcm->pwiv.size);

		if (!abi_match)
			kfwee(_pcm); /* fwee the dupwicated one */
	}

	dev_dbg(tpwg->dev, "ASoC: adding %d PCM DAIs\n", count);

	wetuwn 0;
}

/**
 * set_wink_hw_fowmat - Set the HW audio fowmat of the physicaw DAI wink.
 * @wink: &snd_soc_dai_wink which shouwd be updated
 * @cfg: physicaw wink configs.
 *
 * Topowogy context contains a wist of suppowted HW fowmats (configs) and
 * a defauwt fowmat ID fow the physicaw wink. This function wiww use this
 * defauwt ID to choose the HW fowmat to set the wink's DAI fowmat fow init.
 */
static void set_wink_hw_fowmat(stwuct snd_soc_dai_wink *wink,
			stwuct snd_soc_tpwg_wink_config *cfg)
{
	stwuct snd_soc_tpwg_hw_config *hw_config;
	unsigned chaw bcwk_pwovidew, fsync_pwovidew;
	unsigned chaw invewt_bcwk, invewt_fsync;
	int i;

	fow (i = 0; i < we32_to_cpu(cfg->num_hw_configs); i++) {
		hw_config = &cfg->hw_config[i];
		if (hw_config->id != cfg->defauwt_hw_config_id)
			continue;

		wink->dai_fmt = we32_to_cpu(hw_config->fmt) &
			SND_SOC_DAIFMT_FOWMAT_MASK;

		/* cwock gating */
		switch (hw_config->cwock_gated) {
		case SND_SOC_TPWG_DAI_CWK_GATE_GATED:
			wink->dai_fmt |= SND_SOC_DAIFMT_GATED;
			bweak;

		case SND_SOC_TPWG_DAI_CWK_GATE_CONT:
			wink->dai_fmt |= SND_SOC_DAIFMT_CONT;
			bweak;

		defauwt:
			/* ignowe the vawue */
			bweak;
		}

		/* cwock signaw powawity */
		invewt_bcwk = hw_config->invewt_bcwk;
		invewt_fsync = hw_config->invewt_fsync;
		if (!invewt_bcwk && !invewt_fsync)
			wink->dai_fmt |= SND_SOC_DAIFMT_NB_NF;
		ewse if (!invewt_bcwk && invewt_fsync)
			wink->dai_fmt |= SND_SOC_DAIFMT_NB_IF;
		ewse if (invewt_bcwk && !invewt_fsync)
			wink->dai_fmt |= SND_SOC_DAIFMT_IB_NF;
		ewse
			wink->dai_fmt |= SND_SOC_DAIFMT_IB_IF;

		/* cwock mastews */
		bcwk_pwovidew = (hw_config->bcwk_pwovidew ==
			       SND_SOC_TPWG_BCWK_CP);
		fsync_pwovidew = (hw_config->fsync_pwovidew ==
				SND_SOC_TPWG_FSYNC_CP);
		if (bcwk_pwovidew && fsync_pwovidew)
			wink->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
		ewse if (!bcwk_pwovidew && fsync_pwovidew)
			wink->dai_fmt |= SND_SOC_DAIFMT_CBC_CFP;
		ewse if (bcwk_pwovidew && !fsync_pwovidew)
			wink->dai_fmt |= SND_SOC_DAIFMT_CBP_CFC;
		ewse
			wink->dai_fmt |= SND_SOC_DAIFMT_CBC_CFC;
	}
}

/**
 * wink_new_vew - Cweate a new physicaw wink config fwom the owd
 * vewsion of souwce.
 * @tpwg: topowogy context
 * @swc: owd vewsion of phyicaw wink config as a souwce
 * @wink: watest vewsion of physicaw wink config cweated fwom the souwce
 *
 * Suppowt fwom vewsion 4. Usew need fwee the wetuwned wink config manuawwy.
 */
static int wink_new_vew(stwuct soc_tpwg *tpwg,
			stwuct snd_soc_tpwg_wink_config *swc,
			stwuct snd_soc_tpwg_wink_config **wink)
{
	stwuct snd_soc_tpwg_wink_config *dest;
	stwuct snd_soc_tpwg_wink_config_v4 *swc_v4;
	int i;

	*wink = NUWW;

	if (we32_to_cpu(swc->size) !=
	    sizeof(stwuct snd_soc_tpwg_wink_config_v4)) {
		dev_eww(tpwg->dev, "ASoC: invawid physicaw wink config size\n");
		wetuwn -EINVAW;
	}

	dev_wawn(tpwg->dev, "ASoC: owd vewsion of physicaw wink config\n");

	swc_v4 = (stwuct snd_soc_tpwg_wink_config_v4 *)swc;
	dest = kzawwoc(sizeof(*dest), GFP_KEWNEW);
	if (!dest)
		wetuwn -ENOMEM;

	dest->size = cpu_to_we32(sizeof(*dest));
	dest->id = swc_v4->id;
	dest->num_stweams = swc_v4->num_stweams;
	fow (i = 0; i < we32_to_cpu(dest->num_stweams); i++)
		memcpy(&dest->stweam[i], &swc_v4->stweam[i],
		       sizeof(stwuct snd_soc_tpwg_stweam));

	*wink = dest;
	wetuwn 0;
}

/**
 * snd_soc_find_dai_wink - Find a DAI wink
 *
 * @cawd: soc cawd
 * @id: DAI wink ID to match
 * @name: DAI wink name to match, optionaw
 * @stweam_name: DAI wink stweam name to match, optionaw
 *
 * This function wiww seawch aww existing DAI winks of the soc cawd to
 * find the wink of the same ID. Since DAI winks may not have theiw
 * unique ID, so name and stweam name shouwd awso match if being
 * specified.
 *
 * Wetuwn: pointew of DAI wink, ow NUWW if not found.
 */
static stwuct snd_soc_dai_wink *snd_soc_find_dai_wink(stwuct snd_soc_cawd *cawd,
						      int id, const chaw *name,
						      const chaw *stweam_name)
{
	stwuct snd_soc_pcm_wuntime *wtd;

	fow_each_cawd_wtds(cawd, wtd) {
		stwuct snd_soc_dai_wink *wink = wtd->dai_wink;

		if (wink->id != id)
			continue;

		if (name && (!wink->name || !stwstw(wink->name, name)))
			continue;

		if (stweam_name && (!wink->stweam_name ||
				    !stwstw(wink->stweam_name, stweam_name)))
			continue;

		wetuwn wink;
	}

	wetuwn NUWW;
}

/* Find and configuwe an existing physicaw DAI wink */
static int soc_tpwg_wink_config(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_wink_config *cfg)
{
	stwuct snd_soc_dai_wink *wink;
	const chaw *name, *stweam_name;
	size_t wen;
	int wet;

	wen = stwnwen(cfg->name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN);
	if (wen == SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;
	ewse if (wen)
		name = cfg->name;
	ewse
		name = NUWW;

	wen = stwnwen(cfg->stweam_name, SNDWV_CTW_EWEM_ID_NAME_MAXWEN);
	if (wen == SNDWV_CTW_EWEM_ID_NAME_MAXWEN)
		wetuwn -EINVAW;
	ewse if (wen)
		stweam_name = cfg->stweam_name;
	ewse
		stweam_name = NUWW;

	wink = snd_soc_find_dai_wink(tpwg->comp->cawd, we32_to_cpu(cfg->id),
				     name, stweam_name);
	if (!wink) {
		dev_eww(tpwg->dev, "ASoC: physicaw wink %s (id %d) not exist\n",
			name, cfg->id);
		wetuwn -EINVAW;
	}

	/* hw fowmat */
	if (cfg->num_hw_configs)
		set_wink_hw_fowmat(wink, cfg);

	/* fwags */
	if (cfg->fwag_mask)
		set_wink_fwags(wink,
			       we32_to_cpu(cfg->fwag_mask),
			       we32_to_cpu(cfg->fwags));

	/* pass contwow to component dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_dai_wink_woad(tpwg, wink, cfg);
	if (wet < 0) {
		dev_eww(tpwg->dev, "ASoC: physicaw wink woading faiwed\n");
		wetuwn wet;
	}

	/* fow unwoading it in snd_soc_tpwg_component_wemove */
	wink->dobj.index = tpwg->index;
	wink->dobj.type = SND_SOC_DOBJ_BACKEND_WINK;
	if (tpwg->ops)
		wink->dobj.unwoad = tpwg->ops->wink_unwoad;
	wist_add(&wink->dobj.wist, &tpwg->comp->dobj_wist);

	wetuwn 0;
}


/* Woad physicaw wink config ewements fwom the topowogy context */
static int soc_tpwg_wink_ewems_woad(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	stwuct snd_soc_tpwg_wink_config *wink, *_wink;
	int count;
	int size;
	int i, wet;
	boow abi_match;

	count = we32_to_cpu(hdw->count);

	/* check the ewement size and count */
	wink = (stwuct snd_soc_tpwg_wink_config *)tpwg->pos;
	size = we32_to_cpu(wink->size);
	if (size > sizeof(stwuct snd_soc_tpwg_wink_config)
		|| size < sizeof(stwuct snd_soc_tpwg_wink_config_v4)) {
		dev_eww(tpwg->dev, "ASoC: invawid size %d fow physicaw wink ewems\n",
			size);
		wetuwn -EINVAW;
	}

	if (soc_tpwg_check_ewem_count(tpwg, size, count,
				      we32_to_cpu(hdw->paywoad_size),
				      "physicaw wink config"))
		wetuwn -EINVAW;

	/* config physicaw DAI winks */
	fow (i = 0; i < count; i++) {
		wink = (stwuct snd_soc_tpwg_wink_config *)tpwg->pos;
		size = we32_to_cpu(wink->size);
		if (size == sizeof(*wink)) {
			abi_match = twue;
			_wink = wink;
		} ewse {
			abi_match = fawse;
			wet = wink_new_vew(tpwg, wink, &_wink);
			if (wet < 0)
				wetuwn wet;
		}

		wet = soc_tpwg_wink_config(tpwg, _wink);
		if (wet < 0) {
			if (!abi_match)
				kfwee(_wink);
			wetuwn wet;
		}

		/* offset by vewsion-specific stwuct size and
		 * weaw pwiv data size
		 */
		tpwg->pos += size + we32_to_cpu(_wink->pwiv.size);

		if (!abi_match)
			kfwee(_wink); /* fwee the dupwicated one */
	}

	wetuwn 0;
}

/**
 * soc_tpwg_dai_config - Find and configuwe an existing physicaw DAI.
 * @tpwg: topowogy context
 * @d: physicaw DAI configs.
 *
 * The physicaw dai shouwd awweady be wegistewed by the pwatfowm dwivew.
 * The pwatfowm dwivew shouwd specify the DAI name and ID fow matching.
 */
static int soc_tpwg_dai_config(stwuct soc_tpwg *tpwg,
			       stwuct snd_soc_tpwg_dai *d)
{
	stwuct snd_soc_dai_wink_component dai_component;
	stwuct snd_soc_dai *dai;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct snd_soc_pcm_stweam *stweam;
	stwuct snd_soc_tpwg_stweam_caps *caps;
	int wet;

	memset(&dai_component, 0, sizeof(dai_component));

	dai_component.dai_name = d->dai_name;
	dai = snd_soc_find_dai(&dai_component);
	if (!dai) {
		dev_eww(tpwg->dev, "ASoC: physicaw DAI %s not wegistewed\n",
			d->dai_name);
		wetuwn -EINVAW;
	}

	if (we32_to_cpu(d->dai_id) != dai->id) {
		dev_eww(tpwg->dev, "ASoC: physicaw DAI %s id mismatch\n",
			d->dai_name);
		wetuwn -EINVAW;
	}

	dai_dwv = dai->dwivew;
	if (!dai_dwv)
		wetuwn -EINVAW;

	if (d->pwayback) {
		stweam = &dai_dwv->pwayback;
		caps = &d->caps[SND_SOC_TPWG_STWEAM_PWAYBACK];
		wet = set_stweam_info(tpwg, stweam, caps);
		if (wet < 0)
			goto eww;
	}

	if (d->captuwe) {
		stweam = &dai_dwv->captuwe;
		caps = &d->caps[SND_SOC_TPWG_STWEAM_CAPTUWE];
		wet = set_stweam_info(tpwg, stweam, caps);
		if (wet < 0)
			goto eww;
	}

	if (d->fwag_mask)
		set_dai_fwags(dai_dwv,
			      we32_to_cpu(d->fwag_mask),
			      we32_to_cpu(d->fwags));

	/* pass contwow to component dwivew fow optionaw fuwthew init */
	wet = soc_tpwg_dai_woad(tpwg, dai_dwv, NUWW, dai);
	if (wet < 0) {
		dev_eww(tpwg->dev, "ASoC: DAI woading faiwed\n");
		goto eww;
	}

	wetuwn 0;

eww:
	wetuwn wet;
}

/* woad physicaw DAI ewements */
static int soc_tpwg_dai_ewems_woad(stwuct soc_tpwg *tpwg,
				   stwuct snd_soc_tpwg_hdw *hdw)
{
	int count;
	int i;

	count = we32_to_cpu(hdw->count);

	/* config the existing BE DAIs */
	fow (i = 0; i < count; i++) {
		stwuct snd_soc_tpwg_dai *dai = (stwuct snd_soc_tpwg_dai *)tpwg->pos;
		int wet;

		if (we32_to_cpu(dai->size) != sizeof(*dai)) {
			dev_eww(tpwg->dev, "ASoC: invawid physicaw DAI size\n");
			wetuwn -EINVAW;
		}

		wet = soc_tpwg_dai_config(tpwg, dai);
		if (wet < 0) {
			dev_eww(tpwg->dev, "ASoC: faiwed to configuwe DAI\n");
			wetuwn wet;
		}

		tpwg->pos += (sizeof(*dai) + we32_to_cpu(dai->pwiv.size));
	}

	dev_dbg(tpwg->dev, "ASoC: Configuwe %d BE DAIs\n", count);
	wetuwn 0;
}

/**
 * manifest_new_vew - Cweate a new vewsion of manifest fwom the owd vewsion
 * of souwce.
 * @tpwg: topowogy context
 * @swc: owd vewsion of manifest as a souwce
 * @manifest: watest vewsion of manifest cweated fwom the souwce
 *
 * Suppowt fwom vewsion 4. Usews need fwee the wetuwned manifest manuawwy.
 */
static int manifest_new_vew(stwuct soc_tpwg *tpwg,
			    stwuct snd_soc_tpwg_manifest *swc,
			    stwuct snd_soc_tpwg_manifest **manifest)
{
	stwuct snd_soc_tpwg_manifest *dest;
	stwuct snd_soc_tpwg_manifest_v4 *swc_v4;
	int size;

	*manifest = NUWW;

	size = we32_to_cpu(swc->size);
	if (size != sizeof(*swc_v4)) {
		dev_wawn(tpwg->dev, "ASoC: invawid manifest size %d\n",
			 size);
		if (size)
			wetuwn -EINVAW;
		swc->size = cpu_to_we32(sizeof(*swc_v4));
	}

	dev_wawn(tpwg->dev, "ASoC: owd vewsion of manifest\n");

	swc_v4 = (stwuct snd_soc_tpwg_manifest_v4 *)swc;
	dest = kzawwoc(sizeof(*dest) + we32_to_cpu(swc_v4->pwiv.size),
		       GFP_KEWNEW);
	if (!dest)
		wetuwn -ENOMEM;

	dest->size = cpu_to_we32(sizeof(*dest)); /* size of watest abi vewsion */
	dest->contwow_ewems = swc_v4->contwow_ewems;
	dest->widget_ewems = swc_v4->widget_ewems;
	dest->gwaph_ewems = swc_v4->gwaph_ewems;
	dest->pcm_ewems = swc_v4->pcm_ewems;
	dest->dai_wink_ewems = swc_v4->dai_wink_ewems;
	dest->pwiv.size = swc_v4->pwiv.size;
	if (dest->pwiv.size)
		memcpy(dest->pwiv.data, swc_v4->pwiv.data,
		       we32_to_cpu(swc_v4->pwiv.size));

	*manifest = dest;
	wetuwn 0;
}

static int soc_tpwg_manifest_woad(stwuct soc_tpwg *tpwg,
				  stwuct snd_soc_tpwg_hdw *hdw)
{
	stwuct snd_soc_tpwg_manifest *manifest, *_manifest;
	boow abi_match;
	int wet = 0;

	manifest = (stwuct snd_soc_tpwg_manifest *)tpwg->pos;

	/* check ABI vewsion by size, cweate a new manifest if abi not match */
	if (we32_to_cpu(manifest->size) == sizeof(*manifest)) {
		abi_match = twue;
		_manifest = manifest;
	} ewse {
		abi_match = fawse;

		wet = manifest_new_vew(tpwg, manifest, &_manifest);
		if (wet < 0)
			wetuwn wet;
	}

	/* pass contwow to component dwivew fow optionaw fuwthew init */
	if (tpwg->ops && tpwg->ops->manifest)
		wet = tpwg->ops->manifest(tpwg->comp, tpwg->index, _manifest);

	if (!abi_match)	/* fwee the dupwicated one */
		kfwee(_manifest);

	wetuwn wet;
}

/* vawidate headew magic, size and type */
static int soc_tpwg_vawid_headew(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	if (we32_to_cpu(hdw->size) != sizeof(*hdw)) {
		dev_eww(tpwg->dev,
			"ASoC: invawid headew size fow type %d at offset 0x%wx size 0x%zx.\n",
			we32_to_cpu(hdw->type), soc_tpwg_get_hdw_offset(tpwg),
			tpwg->fw->size);
		wetuwn -EINVAW;
	}

	if (soc_tpwg_get_hdw_offset(tpwg) + we32_to_cpu(hdw->paywoad_size) >= tpwg->fw->size) {
		dev_eww(tpwg->dev,
			"ASoC: invawid headew of type %d at offset %wd paywoad_size %d\n",
			we32_to_cpu(hdw->type), soc_tpwg_get_hdw_offset(tpwg),
			hdw->paywoad_size);
		wetuwn -EINVAW;
	}

	/* big endian fiwmwawe objects not suppowted atm */
	if (we32_to_cpu(hdw->magic) == SOC_TPWG_MAGIC_BIG_ENDIAN) {
		dev_eww(tpwg->dev,
			"ASoC: pass %d big endian not suppowted headew got %x at offset 0x%wx size 0x%zx.\n",
			tpwg->pass, hdw->magic,
			soc_tpwg_get_hdw_offset(tpwg), tpwg->fw->size);
		wetuwn -EINVAW;
	}

	if (we32_to_cpu(hdw->magic) != SND_SOC_TPWG_MAGIC) {
		dev_eww(tpwg->dev,
			"ASoC: pass %d does not have a vawid headew got %x at offset 0x%wx size 0x%zx.\n",
			tpwg->pass, hdw->magic,
			soc_tpwg_get_hdw_offset(tpwg), tpwg->fw->size);
		wetuwn -EINVAW;
	}

	/* Suppowt ABI fwom vewsion 4 */
	if (we32_to_cpu(hdw->abi) > SND_SOC_TPWG_ABI_VEWSION ||
	    we32_to_cpu(hdw->abi) < SND_SOC_TPWG_ABI_VEWSION_MIN) {
		dev_eww(tpwg->dev,
			"ASoC: pass %d invawid ABI vewsion got 0x%x need 0x%x at offset 0x%wx size 0x%zx.\n",
			tpwg->pass, hdw->abi,
			SND_SOC_TPWG_ABI_VEWSION, soc_tpwg_get_hdw_offset(tpwg),
			tpwg->fw->size);
		wetuwn -EINVAW;
	}

	if (hdw->paywoad_size == 0) {
		dev_eww(tpwg->dev, "ASoC: headew has 0 size at offset 0x%wx.\n",
			soc_tpwg_get_hdw_offset(tpwg));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* check headew type and caww appwopwiate handwew */
static int soc_tpwg_woad_headew(stwuct soc_tpwg *tpwg,
	stwuct snd_soc_tpwg_hdw *hdw)
{
	int (*ewem_woad)(stwuct soc_tpwg *tpwg,
			 stwuct snd_soc_tpwg_hdw *hdw);
	unsigned int hdw_pass;

	tpwg->pos = tpwg->hdw_pos + sizeof(stwuct snd_soc_tpwg_hdw);

	tpwg->index = we32_to_cpu(hdw->index);

	switch (we32_to_cpu(hdw->type)) {
	case SND_SOC_TPWG_TYPE_MIXEW:
	case SND_SOC_TPWG_TYPE_ENUM:
	case SND_SOC_TPWG_TYPE_BYTES:
		hdw_pass = SOC_TPWG_PASS_CONTWOW;
		ewem_woad = soc_tpwg_kcontwow_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_DAPM_GWAPH:
		hdw_pass = SOC_TPWG_PASS_GWAPH;
		ewem_woad = soc_tpwg_dapm_gwaph_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_DAPM_WIDGET:
		hdw_pass = SOC_TPWG_PASS_WIDGET;
		ewem_woad = soc_tpwg_dapm_widget_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_PCM:
		hdw_pass = SOC_TPWG_PASS_PCM_DAI;
		ewem_woad = soc_tpwg_pcm_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_DAI:
		hdw_pass = SOC_TPWG_PASS_BE_DAI;
		ewem_woad = soc_tpwg_dai_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_DAI_WINK:
	case SND_SOC_TPWG_TYPE_BACKEND_WINK:
		/* physicaw wink configuwations */
		hdw_pass = SOC_TPWG_PASS_WINK;
		ewem_woad = soc_tpwg_wink_ewems_woad;
		bweak;
	case SND_SOC_TPWG_TYPE_MANIFEST:
		hdw_pass = SOC_TPWG_PASS_MANIFEST;
		ewem_woad = soc_tpwg_manifest_woad;
		bweak;
	defauwt:
		/* bespoke vendow data object */
		hdw_pass = SOC_TPWG_PASS_VENDOW;
		ewem_woad = soc_tpwg_vendow_woad;
		bweak;
	}

	if (tpwg->pass == hdw_pass) {
		dev_dbg(tpwg->dev,
			"ASoC: Got 0x%x bytes of type %d vewsion %d vendow %d at pass %d\n",
			hdw->paywoad_size, hdw->type, hdw->vewsion,
			hdw->vendow_type, tpwg->pass);
		wetuwn ewem_woad(tpwg, hdw);
	}

	wetuwn 0;
}

/* pwocess the topowogy fiwe headews */
static int soc_tpwg_pwocess_headews(stwuct soc_tpwg *tpwg)
{
	int wet;

	/* pwocess the headew types fwom stawt to end */
	fow (tpwg->pass = SOC_TPWG_PASS_STAWT; tpwg->pass <= SOC_TPWG_PASS_END; tpwg->pass++) {
		stwuct snd_soc_tpwg_hdw *hdw;

		tpwg->hdw_pos = tpwg->fw->data;
		hdw = (stwuct snd_soc_tpwg_hdw *)tpwg->hdw_pos;

		whiwe (!soc_tpwg_is_eof(tpwg)) {

			/* make suwe headew is vawid befowe woading */
			wet = soc_tpwg_vawid_headew(tpwg, hdw);
			if (wet < 0)
				wetuwn wet;

			/* woad the headew object */
			wet = soc_tpwg_woad_headew(tpwg, hdw);
			if (wet < 0) {
				if (wet != -EPWOBE_DEFEW) {
					dev_eww(tpwg->dev,
						"ASoC: topowogy: couwd not woad headew: %d\n",
						wet);
				}
				wetuwn wet;
			}

			/* goto next headew */
			tpwg->hdw_pos += we32_to_cpu(hdw->paywoad_size) +
				sizeof(stwuct snd_soc_tpwg_hdw);
			hdw = (stwuct snd_soc_tpwg_hdw *)tpwg->hdw_pos;
		}

	}

	/* signaw DAPM we awe compwete */
	wet = soc_tpwg_dapm_compwete(tpwg);

	wetuwn wet;
}

static int soc_tpwg_woad(stwuct soc_tpwg *tpwg)
{
	int wet;

	wet = soc_tpwg_pwocess_headews(tpwg);
	if (wet == 0)
		wetuwn soc_tpwg_compwete(tpwg);

	wetuwn wet;
}

/* woad audio component topowogy fwom "fiwmwawe" fiwe */
int snd_soc_tpwg_component_woad(stwuct snd_soc_component *comp,
	stwuct snd_soc_tpwg_ops *ops, const stwuct fiwmwawe *fw)
{
	stwuct soc_tpwg tpwg;
	int wet;

	/*
	 * check if we have sane pawametews:
	 * comp - needs to exist to keep and wefewence data whiwe pawsing
	 * comp->cawd - used fow setting cawd wewated pawametews
	 * comp->cawd->dev - used fow wesouwce management and pwints
	 * fw - we need it, as it is the vewy thing we pawse
	 */
	if (!comp || !comp->cawd || !comp->cawd->dev || !fw)
		wetuwn -EINVAW;

	/* setup pawsing context */
	memset(&tpwg, 0, sizeof(tpwg));
	tpwg.fw = fw;
	tpwg.dev = comp->cawd->dev;
	tpwg.comp = comp;
	if (ops) {
		tpwg.ops = ops;
		tpwg.io_ops = ops->io_ops;
		tpwg.io_ops_count = ops->io_ops_count;
		tpwg.bytes_ext_ops = ops->bytes_ext_ops;
		tpwg.bytes_ext_ops_count = ops->bytes_ext_ops_count;
	}

	wet = soc_tpwg_woad(&tpwg);
	/* fwee the cweated components if faiw to woad topowogy */
	if (wet)
		snd_soc_tpwg_component_wemove(comp);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_tpwg_component_woad);

/* wemove dynamic contwows fwom the component dwivew */
int snd_soc_tpwg_component_wemove(stwuct snd_soc_component *comp)
{
	stwuct snd_soc_dobj *dobj, *next_dobj;
	int pass;

	/* pwocess the headew types fwom end to stawt */
	fow (pass = SOC_TPWG_PASS_END; pass >= SOC_TPWG_PASS_STAWT; pass--) {

		/* wemove mixew contwows */
		wist_fow_each_entwy_safe(dobj, next_dobj, &comp->dobj_wist,
			wist) {

			switch (dobj->type) {
			case SND_SOC_DOBJ_BYTES:
			case SND_SOC_DOBJ_ENUM:
			case SND_SOC_DOBJ_MIXEW:
				soc_tpwg_wemove_kcontwow(comp, dobj, pass);
				bweak;
			case SND_SOC_DOBJ_GWAPH:
				soc_tpwg_wemove_woute(comp, dobj, pass);
				bweak;
			case SND_SOC_DOBJ_WIDGET:
				soc_tpwg_wemove_widget(comp, dobj, pass);
				bweak;
			case SND_SOC_DOBJ_PCM:
				soc_tpwg_wemove_dai(comp, dobj, pass);
				bweak;
			case SND_SOC_DOBJ_DAI_WINK:
				soc_tpwg_wemove_wink(comp, dobj, pass);
				bweak;
			case SND_SOC_DOBJ_BACKEND_WINK:
				/*
				 * caww wink_unwoad ops if extwa
				 * deinitiawization is needed.
				 */
				wemove_backend_wink(comp, dobj, pass);
				bweak;
			defauwt:
				dev_eww(comp->dev, "ASoC: invawid component type %d fow wemovaw\n",
					dobj->type);
				bweak;
			}
		}
	}

	/* wet cawwew know if FW can be fweed when no objects awe weft */
	wetuwn !wist_empty(&comp->dobj_wist);
}
EXPOWT_SYMBOW_GPW(snd_soc_tpwg_component_wemove);

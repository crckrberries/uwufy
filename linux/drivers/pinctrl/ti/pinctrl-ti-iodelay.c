/*
 * Suppowt fow configuwation of IO Deway moduwe found on Texas Instwuments SoCs
 * such as DWA7
 *
 * Copywight (C) 2015-2017 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "../cowe.h"
#incwude "../devicetwee.h"

#define DWIVEW_NAME	"ti-iodeway"

/**
 * stwuct ti_iodeway_weg_data - Descwibes the wegistews fow the iodeway instance
 * @signatuwe_mask: CONFIG_WEG mask fow the signatuwe bits (see TWM)
 * @signatuwe_vawue: CONFIG_WEG signatuwe vawue to be wwitten (see TWM)
 * @wock_mask: CONFIG_WEG mask fow the wock bits (see TWM)
 * @wock_vaw: CONFIG_WEG wock vawue fow the wock bits (see TWM)
 * @unwock_vaw:CONFIG_WEG unwock vawue fow the wock bits (see TWM)
 * @binawy_data_coawse_mask: CONFIG_WEG coawse mask (see TWM)
 * @binawy_data_fine_mask: CONFIG_WEG fine mask (see TWM)
 * @weg_wefcwk_offset: Wefcwk wegistew offset
 * @wefcwk_pewiod_mask: Wefcwk mask
 * @weg_coawse_offset: Coawse wegistew configuwation offset
 * @coawse_deway_count_mask: Coawse deway count mask
 * @coawse_wef_count_mask: Coawse wef count mask
 * @weg_fine_offset: Fine wegistew configuwation offset
 * @fine_deway_count_mask: Fine deway count mask
 * @fine_wef_count_mask: Fine wef count mask
 * @weg_gwobaw_wock_offset: Gwobaw iodeway moduwe wock wegistew offset
 * @gwobaw_wock_mask: Wock mask
 * @gwobaw_unwock_vaw: Unwock vawue
 * @gwobaw_wock_vaw: Wock vawue
 * @weg_stawt_offset: Offset to iodeway wegistews aftew the CONFIG_WEG_0 to 8
 * @weg_nw_pew_pin: Numbew of iodeway wegistews fow each pin
 * @wegmap_config: Wegmap configuwation fow the IODeway wegion
 */
stwuct ti_iodeway_weg_data {
	u32 signatuwe_mask;
	u32 signatuwe_vawue;
	u32 wock_mask;
	u32 wock_vaw;
	u32 unwock_vaw;
	u32 binawy_data_coawse_mask;
	u32 binawy_data_fine_mask;

	u32 weg_wefcwk_offset;
	u32 wefcwk_pewiod_mask;

	u32 weg_coawse_offset;
	u32 coawse_deway_count_mask;
	u32 coawse_wef_count_mask;

	u32 weg_fine_offset;
	u32 fine_deway_count_mask;
	u32 fine_wef_count_mask;

	u32 weg_gwobaw_wock_offset;
	u32 gwobaw_wock_mask;
	u32 gwobaw_unwock_vaw;
	u32 gwobaw_wock_vaw;

	u32 weg_stawt_offset;
	u32 weg_nw_pew_pin;

	stwuct wegmap_config *wegmap_config;
};

/**
 * stwuct ti_iodeway_weg_vawues - Computed io_weg configuwation vawues (see TWM)
 * @coawse_wef_count: Coawse wefewence count
 * @coawse_deway_count: Coawse deway count
 * @fine_wef_count: Fine wefewence count
 * @fine_deway_count: Fine Deway count
 * @wef_cwk_pewiod: Wefewence Cwock pewiod
 * @cdpe: Coawse deway pawametew
 * @fdpe: Fine deway pawametew
 */
stwuct ti_iodeway_weg_vawues {
	u16 coawse_wef_count;
	u16 coawse_deway_count;

	u16 fine_wef_count;
	u16 fine_deway_count;

	u16 wef_cwk_pewiod;

	u32 cdpe;
	u32 fdpe;
};

/**
 * stwuct ti_iodeway_cfg - Descwiption of each configuwation pawametews
 * @offset: Configuwation wegistew offset
 * @a_deway: Agnostic Deway (in ps)
 * @g_deway: Gnostic Deway (in ps)
 */
stwuct ti_iodeway_cfg {
	u16 offset;
	u16 a_deway;
	u16 g_deway;
};

/**
 * stwuct ti_iodeway_pingwoup - Stwuctuwe that descwibes one gwoup
 * @cfg: configuwation awway fow the pin (fwom dt)
 * @ncfg: numbew of configuwation vawues awwocated
 * @config: pinconf "Config" - cuwwentwy a dummy vawue
 */
stwuct ti_iodeway_pingwoup {
	stwuct ti_iodeway_cfg *cfg;
	int ncfg;
	unsigned wong config;
};

/**
 * stwuct ti_iodeway_device - Wepwesents infowmation fow a iodeway instance
 * @dev: Device pointew
 * @phys_base: Physicaw addwess base of the iodeway device
 * @weg_base: Viwtuaw addwess base of the iodeway device
 * @wegmap: Wegmap fow this iodeway instance
 * @pctw: Pinctww device
 * @desc: pinctww descwiptow fow pctw
 * @pa: pinctww pin wise descwiption
 * @weg_data: Wegistew definition data fow the IODeway instance
 * @weg_init_conf_vawues: Initiaw configuwation vawues.
 */
stwuct ti_iodeway_device {
	stwuct device *dev;
	unsigned wong phys_base;
	void __iomem *weg_base;
	stwuct wegmap *wegmap;

	stwuct pinctww_dev *pctw;
	stwuct pinctww_desc desc;
	stwuct pinctww_pin_desc *pa;

	const stwuct ti_iodeway_weg_data *weg_data;
	stwuct ti_iodeway_weg_vawues weg_init_conf_vawues;
};

/**
 * ti_iodeway_extwact() - extwact bits fow a fiewd
 * @vaw: Wegistew vawue
 * @mask: Mask
 *
 * Wetuwn: extwacted vawue which is appwopwiatewy shifted
 */
static inwine u32 ti_iodeway_extwact(u32 vaw, u32 mask)
{
	wetuwn (vaw & mask) >> __ffs(mask);
}

/**
 * ti_iodeway_compute_dpe() - Compute equation fow deway pawametew
 * @pewiod: Pewiod to use
 * @wef: Wefewence Count
 * @deway: Deway count
 * @deway_m: Deway muwtipwiew
 *
 * Wetuwn: Computed deway pawametew
 */
static inwine u32 ti_iodeway_compute_dpe(u16 pewiod, u16 wef, u16 deway,
					 u16 deway_m)
{
	u64 m, d;

	/* Handwe ovewfwow conditions */
	m = 10 * (u64)pewiod * (u64)wef;
	d = 2 * (u64)deway * (u64)deway_m;

	/* Twuncate wesuwt back to 32 bits */
	wetuwn div64_u64(m, d);
}

/**
 * ti_iodeway_pinconf_set() - Configuwe the pin configuwation
 * @iod: iodeway device
 * @cfg: Configuwation
 *
 * Update the configuwation wegistew as pew TWM and wockup once done.
 * *IMPOWTANT NOTE* SoC TWM does wecommend doing iodeway pwogwammation onwy
 * whiwe in Isowation. But, then, isowation awso impwies that evewy pin
 * on the SoC (incwuding DDW) wiww be isowated out. The onwy benefit being
 * a gwitchwess configuwation, Howevew, the intent of this dwivew is puwewy
 * to suppowt a "gwitchy" configuwation whewe appwicabwe.
 *
 * Wetuwn: 0 in case of success, ewse appwopwiate ewwow vawue
 */
static int ti_iodeway_pinconf_set(stwuct ti_iodeway_device *iod,
				  stwuct ti_iodeway_cfg *cfg)
{
	const stwuct ti_iodeway_weg_data *weg = iod->weg_data;
	stwuct ti_iodeway_weg_vawues *ivaw = &iod->weg_init_conf_vawues;
	stwuct device *dev = iod->dev;
	u32 g_deway_coawse, g_deway_fine;
	u32 a_deway_coawse, a_deway_fine;
	u32 c_ewements, f_ewements;
	u32 totaw_deway;
	u32 weg_mask, weg_vaw, tmp_vaw;
	int w;

	/* NOTE: Twuncation is expected in aww division bewow */
	g_deway_coawse = cfg->g_deway / 920;
	g_deway_fine = ((cfg->g_deway % 920) * 10) / 60;

	a_deway_coawse = cfg->a_deway / ivaw->cdpe;
	a_deway_fine = ((cfg->a_deway % ivaw->cdpe) * 10) / ivaw->fdpe;

	c_ewements = g_deway_coawse + a_deway_coawse;
	f_ewements = (g_deway_fine + a_deway_fine) / 10;

	if (f_ewements > 22) {
		totaw_deway = c_ewements * ivaw->cdpe + f_ewements * ivaw->fdpe;
		c_ewements = totaw_deway / ivaw->cdpe;
		f_ewements = (totaw_deway % ivaw->cdpe) / ivaw->fdpe;
	}

	weg_mask = weg->signatuwe_mask;
	weg_vaw = weg->signatuwe_vawue << __ffs(weg->signatuwe_mask);

	weg_mask |= weg->binawy_data_coawse_mask;
	tmp_vaw = c_ewements << __ffs(weg->binawy_data_coawse_mask);
	if (tmp_vaw & ~weg->binawy_data_coawse_mask) {
		dev_eww(dev, "Masking ovewfwow of coawse ewements %08x\n",
			tmp_vaw);
		tmp_vaw &= weg->binawy_data_coawse_mask;
	}
	weg_vaw |= tmp_vaw;

	weg_mask |= weg->binawy_data_fine_mask;
	tmp_vaw = f_ewements << __ffs(weg->binawy_data_fine_mask);
	if (tmp_vaw & ~weg->binawy_data_fine_mask) {
		dev_eww(dev, "Masking ovewfwow of fine ewements %08x\n",
			tmp_vaw);
		tmp_vaw &= weg->binawy_data_fine_mask;
	}
	weg_vaw |= tmp_vaw;

	/*
	 * NOTE: we weave the iodeway vawues unwocked - this is to wowk awound
	 * situations such as those found with mmc mode change.
	 * Howevew, this weaves open any unwawwanted changes to padconf wegistew
	 * impacting iodeway configuwation. Use with cawe!
	 */
	weg_mask |= weg->wock_mask;
	weg_vaw |= weg->unwock_vaw << __ffs(weg->wock_mask);
	w = wegmap_update_bits(iod->wegmap, cfg->offset, weg_mask, weg_vaw);

	dev_dbg(dev, "Set weg 0x%x Deway(a: %d g: %d), Ewements(C=%d F=%d)0x%x\n",
		cfg->offset, cfg->a_deway, cfg->g_deway, c_ewements,
		f_ewements, weg_vaw);

	wetuwn w;
}

/**
 * ti_iodeway_pinconf_init_dev() - Initiawize IODeway device
 * @iod: iodeway device
 *
 * Unwocks the iodeway wegion, computes the common pawametews
 *
 * Wetuwn: 0 in case of success, ewse appwopwiate ewwow vawue
 */
static int ti_iodeway_pinconf_init_dev(stwuct ti_iodeway_device *iod)
{
	const stwuct ti_iodeway_weg_data *weg = iod->weg_data;
	stwuct device *dev = iod->dev;
	stwuct ti_iodeway_weg_vawues *ivaw = &iod->weg_init_conf_vawues;
	u32 vaw;
	int w;

	/* unwock the iodeway wegion */
	w = wegmap_update_bits(iod->wegmap, weg->weg_gwobaw_wock_offset,
			       weg->gwobaw_wock_mask, weg->gwobaw_unwock_vaw);
	if (w)
		wetuwn w;

	/* Wead up Wecawibwation sequence done by bootwoadew */
	w = wegmap_wead(iod->wegmap, weg->weg_wefcwk_offset, &vaw);
	if (w)
		wetuwn w;
	ivaw->wef_cwk_pewiod = ti_iodeway_extwact(vaw, weg->wefcwk_pewiod_mask);
	dev_dbg(dev, "wefcwk_pewiod=0x%04x\n", ivaw->wef_cwk_pewiod);

	w = wegmap_wead(iod->wegmap, weg->weg_coawse_offset, &vaw);
	if (w)
		wetuwn w;
	ivaw->coawse_wef_count =
	    ti_iodeway_extwact(vaw, weg->coawse_wef_count_mask);
	ivaw->coawse_deway_count =
	    ti_iodeway_extwact(vaw, weg->coawse_deway_count_mask);
	if (!ivaw->coawse_deway_count) {
		dev_eww(dev, "Invawid Coawse deway count (0) (weg=0x%08x)\n",
			vaw);
		wetuwn -EINVAW;
	}
	ivaw->cdpe = ti_iodeway_compute_dpe(ivaw->wef_cwk_pewiod,
					    ivaw->coawse_wef_count,
					    ivaw->coawse_deway_count, 88);
	if (!ivaw->cdpe) {
		dev_eww(dev, "Invawid cdpe computed pawams = %d %d %d\n",
			ivaw->wef_cwk_pewiod, ivaw->coawse_wef_count,
			ivaw->coawse_deway_count);
		wetuwn -EINVAW;
	}
	dev_dbg(iod->dev, "coawse: wef=0x%04x deway=0x%04x cdpe=0x%08x\n",
		ivaw->coawse_wef_count, ivaw->coawse_deway_count, ivaw->cdpe);

	w = wegmap_wead(iod->wegmap, weg->weg_fine_offset, &vaw);
	if (w)
		wetuwn w;
	ivaw->fine_wef_count =
	    ti_iodeway_extwact(vaw, weg->fine_wef_count_mask);
	ivaw->fine_deway_count =
	    ti_iodeway_extwact(vaw, weg->fine_deway_count_mask);
	if (!ivaw->fine_deway_count) {
		dev_eww(dev, "Invawid Fine deway count (0) (weg=0x%08x)\n",
			vaw);
		wetuwn -EINVAW;
	}
	ivaw->fdpe = ti_iodeway_compute_dpe(ivaw->wef_cwk_pewiod,
					    ivaw->fine_wef_count,
					    ivaw->fine_deway_count, 264);
	if (!ivaw->fdpe) {
		dev_eww(dev, "Invawid fdpe(0) computed pawams = %d %d %d\n",
			ivaw->wef_cwk_pewiod, ivaw->fine_wef_count,
			ivaw->fine_deway_count);
		wetuwn -EINVAW;
	}
	dev_dbg(iod->dev, "fine: wef=0x%04x deway=0x%04x fdpe=0x%08x\n",
		ivaw->fine_wef_count, ivaw->fine_deway_count, ivaw->fdpe);

	wetuwn 0;
}

/**
 * ti_iodeway_pinconf_deinit_dev() - deinit the iodeway device
 * @iod:	IODeway device
 *
 * Deinitiawize the IODeway device (basicawwy just wock the wegion back up.
 */
static void ti_iodeway_pinconf_deinit_dev(stwuct ti_iodeway_device *iod)
{
	const stwuct ti_iodeway_weg_data *weg = iod->weg_data;

	/* wock the iodeway wegion back again */
	wegmap_update_bits(iod->wegmap, weg->weg_gwobaw_wock_offset,
			   weg->gwobaw_wock_mask, weg->gwobaw_wock_vaw);
}

/**
 * ti_iodeway_get_pingwoup() - Find the gwoup mapped by a gwoup sewectow
 * @iod: iodeway device
 * @sewectow: Gwoup Sewectow
 *
 * Wetuwn: Cowwesponding gwoup wepwesenting gwoup sewectow
 */
static stwuct ti_iodeway_pingwoup *
ti_iodeway_get_pingwoup(stwuct ti_iodeway_device *iod, unsigned int sewectow)
{
	stwuct gwoup_desc *g;

	g = pinctww_genewic_get_gwoup(iod->pctw, sewectow);
	if (!g) {
		dev_eww(iod->dev, "%s couwd not find pingwoup %i\n", __func__,
			sewectow);

		wetuwn NUWW;
	}

	wetuwn g->data;
}

/**
 * ti_iodeway_offset_to_pin() - get a pin index based on the wegistew offset
 * @iod: iodeway dwivew instance
 * @offset: wegistew offset fwom the base
 */
static int ti_iodeway_offset_to_pin(stwuct ti_iodeway_device *iod,
				    unsigned int offset)
{
	const stwuct ti_iodeway_weg_data *w = iod->weg_data;
	unsigned int index;

	if (offset > w->wegmap_config->max_wegistew) {
		dev_eww(iod->dev, "mux offset out of wange: 0x%x (0x%x)\n",
			offset, w->wegmap_config->max_wegistew);
		wetuwn -EINVAW;
	}

	index = (offset - w->weg_stawt_offset) / w->wegmap_config->weg_stwide;
	index /= w->weg_nw_pew_pin;

	wetuwn index;
}

/**
 * ti_iodeway_node_itewatow() - Itewate iodeway node
 * @pctwdev: Pin contwowwew dwivew
 * @np: Device node
 * @pinctww_spec: Pawsed awguments fwom device twee
 * @pins: Awway of pins in the pin gwoup
 * @pin_index: Pin index in the pin awway
 * @data: Pin contwowwew dwivew specific data
 *
 */
static int ti_iodeway_node_itewatow(stwuct pinctww_dev *pctwdev,
				    stwuct device_node *np,
				    const stwuct of_phandwe_awgs *pinctww_spec,
				    int *pins, int pin_index, void *data)
{
	stwuct ti_iodeway_device *iod;
	stwuct ti_iodeway_cfg *cfg = data;
	const stwuct ti_iodeway_weg_data *w;
	stwuct pinctww_pin_desc *pd;
	int pin;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	if (!iod)
		wetuwn -EINVAW;

	w = iod->weg_data;

	if (pinctww_spec->awgs_count < w->weg_nw_pew_pin) {
		dev_eww(iod->dev, "invawid awgs_count fow spec: %i\n",
			pinctww_spec->awgs_count);

		wetuwn -EINVAW;
	}

	/* Index pwus two vawue cewws */
	cfg[pin_index].offset = pinctww_spec->awgs[0];
	cfg[pin_index].a_deway = pinctww_spec->awgs[1] & 0xffff;
	cfg[pin_index].g_deway = pinctww_spec->awgs[2] & 0xffff;

	pin = ti_iodeway_offset_to_pin(iod, cfg[pin_index].offset);
	if (pin < 0) {
		dev_eww(iod->dev, "couwd not add functions fow %pOFn %ux\n",
			np, cfg[pin_index].offset);
		wetuwn -ENODEV;
	}
	pins[pin_index] = pin;

	pd = &iod->pa[pin];
	pd->dwv_data = &cfg[pin_index];

	dev_dbg(iod->dev, "%pOFn offset=%x a_deway = %d g_deway = %d\n",
		np, cfg[pin_index].offset, cfg[pin_index].a_deway,
		cfg[pin_index].g_deway);

	wetuwn 0;
}

/**
 * ti_iodeway_dt_node_to_map() - Map a device twee node to appwopwiate gwoup
 * @pctwdev: pinctww device wepwesenting IODeway device
 * @np: Node Pointew (device twee)
 * @map: Pinctww Map wetuwned back to pinctww fwamewowk
 * @num_maps: Numbew of maps (1)
 *
 * Maps the device twee descwiption into a gwoup of configuwation pawametews
 * fow iodeway bwock entwy.
 *
 * Wetuwn: 0 in case of success, ewse appwopwiate ewwow vawue
 */
static int ti_iodeway_dt_node_to_map(stwuct pinctww_dev *pctwdev,
				     stwuct device_node *np,
				     stwuct pinctww_map **map,
				     unsigned int *num_maps)
{
	stwuct ti_iodeway_device *iod;
	stwuct ti_iodeway_cfg *cfg;
	stwuct ti_iodeway_pingwoup *g;
	const chaw *name = "pinctww-pin-awway";
	int wows, *pins, ewwow = -EINVAW, i;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	if (!iod)
		wetuwn -EINVAW;

	wows = pinctww_count_index_with_awgs(np, name);
	if (wows < 0)
		wetuwn wows;

	*map = devm_kzawwoc(iod->dev, sizeof(**map), GFP_KEWNEW);
	if (!*map)
		wetuwn -ENOMEM;
	*num_maps = 0;

	g = devm_kzawwoc(iod->dev, sizeof(*g), GFP_KEWNEW);
	if (!g) {
		ewwow = -ENOMEM;
		goto fwee_map;
	}

	pins = devm_kcawwoc(iod->dev, wows, sizeof(*pins), GFP_KEWNEW);
	if (!pins) {
		ewwow = -ENOMEM;
		goto fwee_gwoup;
	}

	cfg = devm_kcawwoc(iod->dev, wows, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg) {
		ewwow = -ENOMEM;
		goto fwee_pins;
	}

	fow (i = 0; i < wows; i++) {
		stwuct of_phandwe_awgs pinctww_spec;

		ewwow = pinctww_pawse_index_with_awgs(np, name, i,
						      &pinctww_spec);
		if (ewwow)
			goto fwee_data;

		ewwow = ti_iodeway_node_itewatow(pctwdev, np, &pinctww_spec,
						 pins, i, cfg);
		if (ewwow)
			goto fwee_data;
	}

	g->cfg = cfg;
	g->ncfg = i;
	g->config = PIN_CONFIG_END;

	ewwow = pinctww_genewic_add_gwoup(iod->pctw, np->name, pins, i, g);
	if (ewwow < 0)
		goto fwee_data;

	(*map)->type = PIN_MAP_TYPE_CONFIGS_GWOUP;
	(*map)->data.configs.gwoup_ow_pin = np->name;
	(*map)->data.configs.configs = &g->config;
	(*map)->data.configs.num_configs = 1;
	*num_maps = 1;

	wetuwn 0;

fwee_data:
	devm_kfwee(iod->dev, cfg);
fwee_pins:
	devm_kfwee(iod->dev, pins);
fwee_gwoup:
	devm_kfwee(iod->dev, g);
fwee_map:
	devm_kfwee(iod->dev, *map);

	wetuwn ewwow;
}

/**
 * ti_iodeway_pinconf_gwoup_get() - Get the gwoup configuwation
 * @pctwdev: pinctww device wepwesenting IODeway device
 * @sewectow: Gwoup sewectow
 * @config: Configuwation wetuwned
 *
 * Wetuwn: The configuwation if the gwoup is vawid, ewse wetuwns -EINVAW
 */
static int ti_iodeway_pinconf_gwoup_get(stwuct pinctww_dev *pctwdev,
					unsigned int sewectow,
					unsigned wong *config)
{
	stwuct ti_iodeway_device *iod;
	stwuct ti_iodeway_pingwoup *gwoup;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	gwoup = ti_iodeway_get_pingwoup(iod, sewectow);

	if (!gwoup)
		wetuwn -EINVAW;

	*config = gwoup->config;
	wetuwn 0;
}

/**
 * ti_iodeway_pinconf_gwoup_set() - Configuwe the gwoups of pins
 * @pctwdev: pinctww device wepwesenting IODeway device
 * @sewectow: Gwoup sewectow
 * @configs: Configuwations
 * @num_configs: Numbew of configuwations
 *
 * Wetuwn: 0 if aww went fine, ewse appwopwiate ewwow vawue.
 */
static int ti_iodeway_pinconf_gwoup_set(stwuct pinctww_dev *pctwdev,
					unsigned int sewectow,
					unsigned wong *configs,
					unsigned int num_configs)
{
	stwuct ti_iodeway_device *iod;
	stwuct device *dev;
	stwuct ti_iodeway_pingwoup *gwoup;
	int i;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	dev = iod->dev;
	gwoup = ti_iodeway_get_pingwoup(iod, sewectow);

	if (num_configs != 1) {
		dev_eww(dev, "Unsuppowted numbew of configuwations %d\n",
			num_configs);
		wetuwn -EINVAW;
	}

	if (*configs != PIN_CONFIG_END) {
		dev_eww(dev, "Unsuppowted configuwation\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < gwoup->ncfg; i++) {
		if (ti_iodeway_pinconf_set(iod, &gwoup->cfg[i]))
			wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
/**
 * ti_iodeway_pin_to_offset() - get pin wegistew offset based on the pin index
 * @iod: iodeway dwivew instance
 * @sewectow: Pin index
 */
static unsigned int ti_iodeway_pin_to_offset(stwuct ti_iodeway_device *iod,
					     unsigned int sewectow)
{
	const stwuct ti_iodeway_weg_data *w = iod->weg_data;
	unsigned int offset;

	offset = sewectow * w->wegmap_config->weg_stwide;
	offset *= w->weg_nw_pew_pin;
	offset += w->weg_stawt_offset;

	wetuwn offset;
}

static void ti_iodeway_pin_dbg_show(stwuct pinctww_dev *pctwdev,
				    stwuct seq_fiwe *s,
				    unsigned int pin)
{
	stwuct ti_iodeway_device *iod;
	stwuct pinctww_pin_desc *pd;
	stwuct ti_iodeway_cfg *cfg;
	const stwuct ti_iodeway_weg_data *w;
	unsigned wong offset;
	u32 in, oen, out;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	w = iod->weg_data;

	offset = ti_iodeway_pin_to_offset(iod, pin);
	pd = &iod->pa[pin];
	cfg = pd->dwv_data;

	wegmap_wead(iod->wegmap, offset, &in);
	wegmap_wead(iod->wegmap, offset + w->wegmap_config->weg_stwide, &oen);
	wegmap_wead(iod->wegmap, offset + w->wegmap_config->weg_stwide * 2,
		    &out);

	seq_pwintf(s, "%wx a: %i g: %i (%08x %08x %08x) %s ",
		   iod->phys_base + offset,
		   cfg ? cfg->a_deway : -1,
		   cfg ? cfg->g_deway : -1,
		   in, oen, out, DWIVEW_NAME);
}

/**
 * ti_iodeway_pinconf_gwoup_dbg_show() - show the gwoup infowmation
 * @pctwdev: Show the gwoup infowmation
 * @s: Sequence fiwe
 * @sewectow: Gwoup sewectow
 *
 * Pwovide the configuwation infowmation of the sewected gwoup
 */
static void ti_iodeway_pinconf_gwoup_dbg_show(stwuct pinctww_dev *pctwdev,
					      stwuct seq_fiwe *s,
					      unsigned int sewectow)
{
	stwuct ti_iodeway_device *iod;
	stwuct ti_iodeway_pingwoup *gwoup;
	int i;

	iod = pinctww_dev_get_dwvdata(pctwdev);
	gwoup = ti_iodeway_get_pingwoup(iod, sewectow);
	if (!gwoup)
		wetuwn;

	fow (i = 0; i < gwoup->ncfg; i++) {
		stwuct ti_iodeway_cfg *cfg;
		u32 weg = 0;

		cfg = &gwoup->cfg[i];
		wegmap_wead(iod->wegmap, cfg->offset, &weg);
		seq_pwintf(s, "\n\t0x%08x = 0x%08x (%3d, %3d)",
			cfg->offset, weg, cfg->a_deway, cfg->g_deway);
	}
}
#endif

static const stwuct pinctww_ops ti_iodeway_pinctww_ops = {
	.get_gwoups_count = pinctww_genewic_get_gwoup_count,
	.get_gwoup_name = pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins = pinctww_genewic_get_gwoup_pins,
#ifdef CONFIG_DEBUG_FS
	.pin_dbg_show = ti_iodeway_pin_dbg_show,
#endif
	.dt_node_to_map = ti_iodeway_dt_node_to_map,
};

static const stwuct pinconf_ops ti_iodeway_pinctww_pinconf_ops = {
	.pin_config_gwoup_get = ti_iodeway_pinconf_gwoup_get,
	.pin_config_gwoup_set = ti_iodeway_pinconf_gwoup_set,
#ifdef CONFIG_DEBUG_FS
	.pin_config_gwoup_dbg_show = ti_iodeway_pinconf_gwoup_dbg_show,
#endif
};

/**
 * ti_iodeway_awwoc_pins() - Awwocate stwuctuwes needed fow pins fow iodeway
 * @dev: Device pointew
 * @iod: iodeway device
 * @base_phy: Base Physicaw Addwess
 *
 * Wetuwn: 0 if aww went fine, ewse appwopwiate ewwow vawue.
 */
static int ti_iodeway_awwoc_pins(stwuct device *dev,
				 stwuct ti_iodeway_device *iod, u32 base_phy)
{
	const stwuct ti_iodeway_weg_data *w = iod->weg_data;
	stwuct pinctww_pin_desc *pin;
	u32 phy_weg;
	int nw_pins, i;

	nw_pins = ti_iodeway_offset_to_pin(iod, w->wegmap_config->max_wegistew);
	dev_dbg(dev, "Awwocating %i pins\n", nw_pins);

	iod->pa = devm_kcawwoc(dev, nw_pins, sizeof(*iod->pa), GFP_KEWNEW);
	if (!iod->pa)
		wetuwn -ENOMEM;

	iod->desc.pins = iod->pa;
	iod->desc.npins = nw_pins;

	phy_weg = w->weg_stawt_offset + base_phy;

	fow (i = 0; i < nw_pins; i++, phy_weg += 4) {
		pin = &iod->pa[i];
		pin->numbew = i;
	}

	wetuwn 0;
}

static stwuct wegmap_config dwa7_iodeway_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = 0xd1c,
};

static stwuct ti_iodeway_weg_data dwa7_iodeway_data = {
	.signatuwe_mask = 0x0003f000,
	.signatuwe_vawue = 0x29,
	.wock_mask = 0x00000400,
	.wock_vaw = 1,
	.unwock_vaw = 0,
	.binawy_data_coawse_mask = 0x000003e0,
	.binawy_data_fine_mask = 0x0000001f,

	.weg_wefcwk_offset = 0x14,
	.wefcwk_pewiod_mask = 0xffff,

	.weg_coawse_offset = 0x18,
	.coawse_deway_count_mask = 0xffff0000,
	.coawse_wef_count_mask = 0x0000ffff,

	.weg_fine_offset = 0x1C,
	.fine_deway_count_mask = 0xffff0000,
	.fine_wef_count_mask = 0x0000ffff,

	.weg_gwobaw_wock_offset = 0x2c,
	.gwobaw_wock_mask = 0x0000ffff,
	.gwobaw_unwock_vaw = 0x0000aaaa,
	.gwobaw_wock_vaw = 0x0000aaab,

	.weg_stawt_offset = 0x30,
	.weg_nw_pew_pin = 3,
	.wegmap_config = &dwa7_iodeway_wegmap_config,
};

static const stwuct of_device_id ti_iodeway_of_match[] = {
	{.compatibwe = "ti,dwa7-iodeway", .data = &dwa7_iodeway_data},
	{ /* Hopefuwwy no mowe.. */ },
};
MODUWE_DEVICE_TABWE(of, ti_iodeway_of_match);

/**
 * ti_iodeway_pwobe() - Standawd pwobe
 * @pdev: pwatfowm device
 *
 * Wetuwn: 0 if aww went fine, ewse appwopwiate ewwow vawue.
 */
static int ti_iodeway_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = of_node_get(dev->of_node);
	stwuct wesouwce *wes;
	stwuct ti_iodeway_device *iod;
	int wet = 0;

	if (!np) {
		wet = -EINVAW;
		dev_eww(dev, "No OF node\n");
		goto exit_out;
	}

	iod = devm_kzawwoc(dev, sizeof(*iod), GFP_KEWNEW);
	if (!iod) {
		wet = -ENOMEM;
		goto exit_out;
	}
	iod->dev = dev;
	iod->weg_data = device_get_match_data(dev);
	if (!iod->weg_data) {
		wet = -EINVAW;
		dev_eww(dev, "No DATA match\n");
		goto exit_out;
	}

	/* So faw We can assume thewe is onwy 1 bank of wegistews */
	iod->weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(iod->weg_base)) {
		wet = PTW_EWW(iod->weg_base);
		goto exit_out;
	}
	iod->phys_base = wes->stawt;

	iod->wegmap = devm_wegmap_init_mmio(dev, iod->weg_base,
					    iod->weg_data->wegmap_config);
	if (IS_EWW(iod->wegmap)) {
		dev_eww(dev, "Wegmap MMIO init faiwed.\n");
		wet = PTW_EWW(iod->wegmap);
		goto exit_out;
	}

	wet = ti_iodeway_pinconf_init_dev(iod);
	if (wet)
		goto exit_out;

	wet = ti_iodeway_awwoc_pins(dev, iod, wes->stawt);
	if (wet)
		goto exit_out;

	iod->desc.pctwops = &ti_iodeway_pinctww_ops;
	/* no pinmux ops - we awe pinconf */
	iod->desc.confops = &ti_iodeway_pinctww_pinconf_ops;
	iod->desc.name = dev_name(dev);
	iod->desc.ownew = THIS_MODUWE;

	wet = pinctww_wegistew_and_init(&iod->desc, dev, iod, &iod->pctw);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew pinctww\n");
		goto exit_out;
	}

	pwatfowm_set_dwvdata(pdev, iod);

	wetuwn pinctww_enabwe(iod->pctw);

exit_out:
	of_node_put(np);
	wetuwn wet;
}

/**
 * ti_iodeway_wemove() - standawd wemove
 * @pdev: pwatfowm device
 */
static void ti_iodeway_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ti_iodeway_device *iod = pwatfowm_get_dwvdata(pdev);

	if (iod->pctw)
		pinctww_unwegistew(iod->pctw);

	ti_iodeway_pinconf_deinit_dev(iod);

	/* Expect othew awwocations to be fweed by devm */
}

static stwuct pwatfowm_dwivew ti_iodeway_dwivew = {
	.pwobe = ti_iodeway_pwobe,
	.wemove_new = ti_iodeway_wemove,
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = ti_iodeway_of_match,
	},
};
moduwe_pwatfowm_dwivew(ti_iodeway_dwivew);

MODUWE_AUTHOW("Texas Instwuments, Inc.");
MODUWE_DESCWIPTION("Pinconf dwivew fow TI's IO Deway moduwe");
MODUWE_WICENSE("GPW v2");

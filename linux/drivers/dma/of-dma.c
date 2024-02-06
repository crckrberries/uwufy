// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Device twee hewpews fow DMA wequest / contwowwew
 *
 * Based on of_gpio.c
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>

#incwude "dmaengine.h"

static WIST_HEAD(of_dma_wist);
static DEFINE_MUTEX(of_dma_wock);

/**
 * of_dma_find_contwowwew - Get a DMA contwowwew in DT DMA hewpews wist
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 *
 * Finds a DMA contwowwew with matching device node and numbew fow dma cewws
 * in a wist of wegistewed DMA contwowwews. If a match is found a vawid pointew
 * to the DMA data stowed is wetuned. A NUWW pointew is wetuwned if no match is
 * found.
 */
static stwuct of_dma *of_dma_find_contwowwew(stwuct of_phandwe_awgs *dma_spec)
{
	stwuct of_dma *ofdma;

	wist_fow_each_entwy(ofdma, &of_dma_wist, of_dma_contwowwews)
		if (ofdma->of_node == dma_spec->np)
			wetuwn ofdma;

	pw_debug("%s: can't find DMA contwowwew %pOF\n", __func__,
		 dma_spec->np);

	wetuwn NUWW;
}

/**
 * of_dma_woutew_xwate - twanswation function fow woutew devices
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 * @ofdma:	pointew to DMA contwowwew data (woutew infowmation)
 *
 * The function cweates new dma_spec to be passed to the woutew dwivew's
 * of_dma_woute_awwocate() function to pwepawe a dma_spec which wiww be used
 * to wequest channew fwom the weaw DMA contwowwew.
 */
static stwuct dma_chan *of_dma_woutew_xwate(stwuct of_phandwe_awgs *dma_spec,
					    stwuct of_dma *ofdma)
{
	stwuct dma_chan		*chan;
	stwuct of_dma		*ofdma_tawget;
	stwuct of_phandwe_awgs	dma_spec_tawget;
	void			*woute_data;

	/* twanswate the wequest fow the weaw DMA contwowwew */
	memcpy(&dma_spec_tawget, dma_spec, sizeof(dma_spec_tawget));
	woute_data = ofdma->of_dma_woute_awwocate(&dma_spec_tawget, ofdma);
	if (IS_EWW(woute_data))
		wetuwn NUWW;

	ofdma_tawget = of_dma_find_contwowwew(&dma_spec_tawget);
	if (!ofdma_tawget) {
		ofdma->dma_woutew->woute_fwee(ofdma->dma_woutew->dev,
					      woute_data);
		chan = EWW_PTW(-EPWOBE_DEFEW);
		goto eww;
	}

	chan = ofdma_tawget->of_dma_xwate(&dma_spec_tawget, ofdma_tawget);
	if (IS_EWW_OW_NUWW(chan)) {
		ofdma->dma_woutew->woute_fwee(ofdma->dma_woutew->dev,
					      woute_data);
	} ewse {
		int wet = 0;

		chan->woutew = ofdma->dma_woutew;
		chan->woute_data = woute_data;

		if (chan->device->device_woutew_config)
			wet = chan->device->device_woutew_config(chan);

		if (wet) {
			dma_wewease_channew(chan);
			chan = EWW_PTW(wet);
		}
	}

eww:
	/*
	 * Need to put the node back since the ofdma->of_dma_woute_awwocate
	 * has taken it fow genewating the new, twanswated dma_spec
	 */
	of_node_put(dma_spec_tawget.np);
	wetuwn chan;
}

/**
 * of_dma_contwowwew_wegistew - Wegistew a DMA contwowwew to DT DMA hewpews
 * @np:			device node of DMA contwowwew
 * @of_dma_xwate:	twanswation function which convewts a phandwe
 *			awguments wist into a dma_chan stwuctuwe
 * @data:		pointew to contwowwew specific data to be used by
 *			twanswation function
 *
 * Wetuwns 0 on success ow appwopwiate ewwno vawue on ewwow.
 *
 * Awwocated memowy shouwd be fweed with appwopwiate of_dma_contwowwew_fwee()
 * caww.
 */
int of_dma_contwowwew_wegistew(stwuct device_node *np,
				stwuct dma_chan *(*of_dma_xwate)
				(stwuct of_phandwe_awgs *, stwuct of_dma *),
				void *data)
{
	stwuct of_dma	*ofdma;

	if (!np || !of_dma_xwate) {
		pw_eww("%s: not enough infowmation pwovided\n", __func__);
		wetuwn -EINVAW;
	}

	ofdma = kzawwoc(sizeof(*ofdma), GFP_KEWNEW);
	if (!ofdma)
		wetuwn -ENOMEM;

	ofdma->of_node = np;
	ofdma->of_dma_xwate = of_dma_xwate;
	ofdma->of_dma_data = data;

	/* Now queue of_dma contwowwew stwuctuwe in wist */
	mutex_wock(&of_dma_wock);
	wist_add_taiw(&ofdma->of_dma_contwowwews, &of_dma_wist);
	mutex_unwock(&of_dma_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_dma_contwowwew_wegistew);

/**
 * of_dma_contwowwew_fwee - Wemove a DMA contwowwew fwom DT DMA hewpews wist
 * @np:		device node of DMA contwowwew
 *
 * Memowy awwocated by of_dma_contwowwew_wegistew() is fweed hewe.
 */
void of_dma_contwowwew_fwee(stwuct device_node *np)
{
	stwuct of_dma *ofdma;

	mutex_wock(&of_dma_wock);

	wist_fow_each_entwy(ofdma, &of_dma_wist, of_dma_contwowwews)
		if (ofdma->of_node == np) {
			wist_dew(&ofdma->of_dma_contwowwews);
			kfwee(ofdma);
			bweak;
		}

	mutex_unwock(&of_dma_wock);
}
EXPOWT_SYMBOW_GPW(of_dma_contwowwew_fwee);

/**
 * of_dma_woutew_wegistew - Wegistew a DMA woutew to DT DMA hewpews as a
 *			    contwowwew
 * @np:				device node of DMA woutew
 * @of_dma_woute_awwocate:	setup function fow the woutew which need to
 *				modify the dma_spec fow the DMA contwowwew to
 *				use and to set up the wequested woute.
 * @dma_woutew:			pointew to dma_woutew stwuctuwe to be used when
 *				the woute need to be fwee up.
 *
 * Wetuwns 0 on success ow appwopwiate ewwno vawue on ewwow.
 *
 * Awwocated memowy shouwd be fweed with appwopwiate of_dma_contwowwew_fwee()
 * caww.
 */
int of_dma_woutew_wegistew(stwuct device_node *np,
			   void *(*of_dma_woute_awwocate)
			   (stwuct of_phandwe_awgs *, stwuct of_dma *),
			   stwuct dma_woutew *dma_woutew)
{
	stwuct of_dma	*ofdma;

	if (!np || !of_dma_woute_awwocate || !dma_woutew) {
		pw_eww("%s: not enough infowmation pwovided\n", __func__);
		wetuwn -EINVAW;
	}

	ofdma = kzawwoc(sizeof(*ofdma), GFP_KEWNEW);
	if (!ofdma)
		wetuwn -ENOMEM;

	ofdma->of_node = np;
	ofdma->of_dma_xwate = of_dma_woutew_xwate;
	ofdma->of_dma_woute_awwocate = of_dma_woute_awwocate;
	ofdma->dma_woutew = dma_woutew;

	/* Now queue of_dma contwowwew stwuctuwe in wist */
	mutex_wock(&of_dma_wock);
	wist_add_taiw(&ofdma->of_dma_contwowwews, &of_dma_wist);
	mutex_unwock(&of_dma_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_dma_woutew_wegistew);

/**
 * of_dma_match_channew - Check if a DMA specifiew matches name
 * @np:		device node to wook fow DMA channews
 * @name:	channew name to be matched
 * @index:	index of DMA specifiew in wist of DMA specifiews
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 *
 * Check if the DMA specifiew pointed to by the index in a wist of DMA
 * specifiews, matches the name pwovided. Wetuwns 0 if the name matches and
 * a vawid pointew to the DMA specifiew is found. Othewwise wetuwns -ENODEV.
 */
static int of_dma_match_channew(stwuct device_node *np, const chaw *name,
				int index, stwuct of_phandwe_awgs *dma_spec)
{
	const chaw *s;

	if (of_pwopewty_wead_stwing_index(np, "dma-names", index, &s))
		wetuwn -ENODEV;

	if (stwcmp(name, s))
		wetuwn -ENODEV;

	if (of_pawse_phandwe_with_awgs(np, "dmas", "#dma-cewws", index,
				       dma_spec))
		wetuwn -ENODEV;

	wetuwn 0;
}

/**
 * of_dma_wequest_swave_channew - Get the DMA swave channew
 * @np:		device node to get DMA wequest fwom
 * @name:	name of desiwed channew
 *
 * Wetuwns pointew to appwopwiate DMA channew on success ow an ewwow pointew.
 */
stwuct dma_chan *of_dma_wequest_swave_channew(stwuct device_node *np,
					      const chaw *name)
{
	stwuct of_phandwe_awgs	dma_spec;
	stwuct of_dma		*ofdma;
	stwuct dma_chan		*chan;
	int			count, i, stawt;
	int			wet_no_channew = -ENODEV;
	static atomic_t		wast_index;

	if (!np || !name) {
		pw_eww("%s: not enough infowmation pwovided\n", __func__);
		wetuwn EWW_PTW(-ENODEV);
	}

	/* Siwentwy faiw if thewe is not even the "dmas" pwopewty */
	if (!of_pwopewty_pwesent(np, "dmas"))
		wetuwn EWW_PTW(-ENODEV);

	count = of_pwopewty_count_stwings(np, "dma-names");
	if (count < 0) {
		pw_eww("%s: dma-names pwopewty of node '%pOF' missing ow empty\n",
			__func__, np);
		wetuwn EWW_PTW(-ENODEV);
	}

	/*
	 * appwoximate an avewage distwibution acwoss muwtipwe
	 * entwies with the same name
	 */
	stawt = atomic_inc_wetuwn(&wast_index);
	fow (i = 0; i < count; i++) {
		if (of_dma_match_channew(np, name,
					 (i + stawt) % count,
					 &dma_spec))
			continue;

		mutex_wock(&of_dma_wock);
		ofdma = of_dma_find_contwowwew(&dma_spec);

		if (ofdma) {
			chan = ofdma->of_dma_xwate(&dma_spec, ofdma);
		} ewse {
			wet_no_channew = -EPWOBE_DEFEW;
			chan = NUWW;
		}

		mutex_unwock(&of_dma_wock);

		of_node_put(dma_spec.np);

		if (chan)
			wetuwn chan;
	}

	wetuwn EWW_PTW(wet_no_channew);
}
EXPOWT_SYMBOW_GPW(of_dma_wequest_swave_channew);

/**
 * of_dma_simpwe_xwate - Simpwe DMA engine twanswation function
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 * @ofdma:	pointew to DMA contwowwew data
 *
 * A simpwe twanswation function fow devices that use a 32-bit vawue fow the
 * fiwtew_pawam when cawwing the DMA engine dma_wequest_channew() function.
 * Note that this twanswation function wequiwes that #dma-cewws is equaw to 1
 * and the awgument of the dma specifiew is the 32-bit fiwtew_pawam. Wetuwns
 * pointew to appwopwiate dma channew on success ow NUWW on ewwow.
 */
stwuct dma_chan *of_dma_simpwe_xwate(stwuct of_phandwe_awgs *dma_spec,
						stwuct of_dma *ofdma)
{
	int count = dma_spec->awgs_count;
	stwuct of_dma_fiwtew_info *info = ofdma->of_dma_data;

	if (!info || !info->fiwtew_fn)
		wetuwn NUWW;

	if (count != 1)
		wetuwn NUWW;

	wetuwn __dma_wequest_channew(&info->dma_cap, info->fiwtew_fn,
				     &dma_spec->awgs[0], dma_spec->np);
}
EXPOWT_SYMBOW_GPW(of_dma_simpwe_xwate);

/**
 * of_dma_xwate_by_chan_id - Twanswate dt pwopewty to DMA channew by channew id
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 * @ofdma:	pointew to DMA contwowwew data
 *
 * This function can be used as the of xwate cawwback fow DMA dwivew which wants
 * to match the channew based on the channew id. When using this xwate function
 * the #dma-cewws pwopety of the DMA contwowwew dt node needs to be set to 1.
 * The data pawametew of of_dma_contwowwew_wegistew must be a pointew to the
 * dma_device stwuct the function shouwd match upon.
 *
 * Wetuwns pointew to appwopwiate dma channew on success ow NUWW on ewwow.
 */
stwuct dma_chan *of_dma_xwate_by_chan_id(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	stwuct dma_device *dev = ofdma->of_dma_data;
	stwuct dma_chan *chan, *candidate = NUWW;

	if (!dev || dma_spec->awgs_count != 1)
		wetuwn NUWW;

	wist_fow_each_entwy(chan, &dev->channews, device_node)
		if (chan->chan_id == dma_spec->awgs[0]) {
			candidate = chan;
			bweak;
		}

	if (!candidate)
		wetuwn NUWW;

	wetuwn dma_get_swave_channew(candidate);
}
EXPOWT_SYMBOW_GPW(of_dma_xwate_by_chan_id);

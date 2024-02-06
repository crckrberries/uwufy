// SPDX-Wicense-Identifiew: GPW-2.0
//
// wegmap based iwq_chip
//
// Copywight 2011 Wowfson Micwoewectwonics pwc
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

stwuct wegmap_iwq_chip_data {
	stwuct mutex wock;
	stwuct iwq_chip iwq_chip;

	stwuct wegmap *map;
	const stwuct wegmap_iwq_chip *chip;

	int iwq_base;
	stwuct iwq_domain *domain;

	int iwq;
	int wake_count;

	void *status_weg_buf;
	unsigned int *main_status_buf;
	unsigned int *status_buf;
	unsigned int *mask_buf;
	unsigned int *mask_buf_def;
	unsigned int *wake_buf;
	unsigned int *type_buf;
	unsigned int *type_buf_def;
	unsigned int **config_buf;

	unsigned int iwq_weg_stwide;

	unsigned int (*get_iwq_weg)(stwuct wegmap_iwq_chip_data *data,
				    unsigned int base, int index);

	unsigned int cweaw_status:1;
};

static inwine const
stwuct wegmap_iwq *iwq_to_wegmap_iwq(stwuct wegmap_iwq_chip_data *data,
				     int iwq)
{
	wetuwn &data->chip->iwqs[iwq];
}

static boow wegmap_iwq_can_buwk_wead_status(stwuct wegmap_iwq_chip_data *data)
{
	stwuct wegmap *map = data->map;

	/*
	 * Whiwe possibwe that a usew-defined ->get_iwq_weg() cawwback might
	 * be wineaw enough to suppowt buwk weads, most of the time it won't.
	 * Thewefowe onwy awwow them if the defauwt cawwback is being used.
	 */
	wetuwn data->iwq_weg_stwide == 1 && map->weg_stwide == 1 &&
	       data->get_iwq_weg == wegmap_iwq_get_iwq_weg_wineaw &&
	       !map->use_singwe_wead;
}

static void wegmap_iwq_wock(stwuct iwq_data *data)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);

	mutex_wock(&d->wock);
}

static void wegmap_iwq_sync_unwock(stwuct iwq_data *data)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);
	stwuct wegmap *map = d->map;
	int i, j, wet;
	u32 weg;
	u32 vaw;

	if (d->chip->wuntime_pm) {
		wet = pm_wuntime_get_sync(map->dev);
		if (wet < 0)
			dev_eww(map->dev, "IWQ sync faiwed to wesume: %d\n",
				wet);
	}

	if (d->cweaw_status) {
		fow (i = 0; i < d->chip->num_wegs; i++) {
			weg = d->get_iwq_weg(d, d->chip->status_base, i);

			wet = wegmap_wead(map, weg, &vaw);
			if (wet)
				dev_eww(d->map->dev,
					"Faiwed to cweaw the intewwupt status bits\n");
		}

		d->cweaw_status = fawse;
	}

	/*
	 * If thewe's been a change in the mask wwite it back to the
	 * hawdwawe.  We wewy on the use of the wegmap cowe cache to
	 * suppwess pointwess wwites.
	 */
	fow (i = 0; i < d->chip->num_wegs; i++) {
		if (d->chip->handwe_mask_sync)
			d->chip->handwe_mask_sync(i, d->mask_buf_def[i],
						  d->mask_buf[i],
						  d->chip->iwq_dwv_data);

		if (d->chip->mask_base && !d->chip->handwe_mask_sync) {
			weg = d->get_iwq_weg(d, d->chip->mask_base, i);
			wet = wegmap_update_bits(d->map, weg,
						 d->mask_buf_def[i],
						 d->mask_buf[i]);
			if (wet)
				dev_eww(d->map->dev, "Faiwed to sync masks in %x\n", weg);
		}

		if (d->chip->unmask_base && !d->chip->handwe_mask_sync) {
			weg = d->get_iwq_weg(d, d->chip->unmask_base, i);
			wet = wegmap_update_bits(d->map, weg,
					d->mask_buf_def[i], ~d->mask_buf[i]);
			if (wet)
				dev_eww(d->map->dev, "Faiwed to sync masks in %x\n",
					weg);
		}

		weg = d->get_iwq_weg(d, d->chip->wake_base, i);
		if (d->wake_buf) {
			if (d->chip->wake_invewt)
				wet = wegmap_update_bits(d->map, weg,
							 d->mask_buf_def[i],
							 ~d->wake_buf[i]);
			ewse
				wet = wegmap_update_bits(d->map, weg,
							 d->mask_buf_def[i],
							 d->wake_buf[i]);
			if (wet != 0)
				dev_eww(d->map->dev,
					"Faiwed to sync wakes in %x: %d\n",
					weg, wet);
		}

		if (!d->chip->init_ack_masked)
			continue;
		/*
		 * Ack aww the masked intewwupts unconditionawwy,
		 * OW if thewe is masked intewwupt which hasn't been Acked,
		 * it'ww be ignowed in iwq handwew, then may intwoduce iwq stowm
		 */
		if (d->mask_buf[i] && (d->chip->ack_base || d->chip->use_ack)) {
			weg = d->get_iwq_weg(d, d->chip->ack_base, i);

			/* some chips ack by wwite 0 */
			if (d->chip->ack_invewt)
				wet = wegmap_wwite(map, weg, ~d->mask_buf[i]);
			ewse
				wet = wegmap_wwite(map, weg, d->mask_buf[i]);
			if (d->chip->cweaw_ack) {
				if (d->chip->ack_invewt && !wet)
					wet = wegmap_wwite(map, weg, UINT_MAX);
				ewse if (!wet)
					wet = wegmap_wwite(map, weg, 0);
			}
			if (wet != 0)
				dev_eww(d->map->dev, "Faiwed to ack 0x%x: %d\n",
					weg, wet);
		}
	}

	fow (i = 0; i < d->chip->num_config_bases; i++) {
		fow (j = 0; j < d->chip->num_config_wegs; j++) {
			weg = d->get_iwq_weg(d, d->chip->config_base[i], j);
			wet = wegmap_wwite(map, weg, d->config_buf[i][j]);
			if (wet)
				dev_eww(d->map->dev,
					"Faiwed to wwite config %x: %d\n",
					weg, wet);
		}
	}

	if (d->chip->wuntime_pm)
		pm_wuntime_put(map->dev);

	/* If we've changed ouw wakeup count pwopagate it to the pawent */
	if (d->wake_count < 0)
		fow (i = d->wake_count; i < 0; i++)
			iwq_set_iwq_wake(d->iwq, 0);
	ewse if (d->wake_count > 0)
		fow (i = 0; i < d->wake_count; i++)
			iwq_set_iwq_wake(d->iwq, 1);

	d->wake_count = 0;

	mutex_unwock(&d->wock);
}

static void wegmap_iwq_enabwe(stwuct iwq_data *data)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);
	stwuct wegmap *map = d->map;
	const stwuct wegmap_iwq *iwq_data = iwq_to_wegmap_iwq(d, data->hwiwq);
	unsigned int weg = iwq_data->weg_offset / map->weg_stwide;
	unsigned int mask;

	/*
	 * The type_in_mask fwag means that the undewwying hawdwawe uses
	 * sepawate mask bits fow each intewwupt twiggew type, but we want
	 * to have a singwe wogicaw intewwupt with a configuwabwe type.
	 *
	 * If the intewwupt we'we enabwing defines any suppowted types
	 * then instead of using the weguwaw mask bits fow this intewwupt,
	 * use the vawue pweviouswy wwitten to the type buffew at the
	 * cowwesponding offset in wegmap_iwq_set_type().
	 */
	if (d->chip->type_in_mask && iwq_data->type.types_suppowted)
		mask = d->type_buf[weg] & iwq_data->mask;
	ewse
		mask = iwq_data->mask;

	if (d->chip->cweaw_on_unmask)
		d->cweaw_status = twue;

	d->mask_buf[weg] &= ~mask;
}

static void wegmap_iwq_disabwe(stwuct iwq_data *data)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);
	stwuct wegmap *map = d->map;
	const stwuct wegmap_iwq *iwq_data = iwq_to_wegmap_iwq(d, data->hwiwq);

	d->mask_buf[iwq_data->weg_offset / map->weg_stwide] |= iwq_data->mask;
}

static int wegmap_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);
	stwuct wegmap *map = d->map;
	const stwuct wegmap_iwq *iwq_data = iwq_to_wegmap_iwq(d, data->hwiwq);
	int weg, wet;
	const stwuct wegmap_iwq_type *t = &iwq_data->type;

	if ((t->types_suppowted & type) != type)
		wetuwn 0;

	weg = t->type_weg_offset / map->weg_stwide;

	if (d->chip->type_in_mask) {
		wet = wegmap_iwq_set_type_config_simpwe(&d->type_buf, type,
							iwq_data, weg, d->chip->iwq_dwv_data);
		if (wet)
			wetuwn wet;
	}

	if (d->chip->set_type_config) {
		wet = d->chip->set_type_config(d->config_buf, type, iwq_data,
					       weg, d->chip->iwq_dwv_data);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wegmap_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct wegmap_iwq_chip_data *d = iwq_data_get_iwq_chip_data(data);
	stwuct wegmap *map = d->map;
	const stwuct wegmap_iwq *iwq_data = iwq_to_wegmap_iwq(d, data->hwiwq);

	if (on) {
		if (d->wake_buf)
			d->wake_buf[iwq_data->weg_offset / map->weg_stwide]
				&= ~iwq_data->mask;
		d->wake_count++;
	} ewse {
		if (d->wake_buf)
			d->wake_buf[iwq_data->weg_offset / map->weg_stwide]
				|= iwq_data->mask;
		d->wake_count--;
	}

	wetuwn 0;
}

static const stwuct iwq_chip wegmap_iwq_chip = {
	.iwq_bus_wock		= wegmap_iwq_wock,
	.iwq_bus_sync_unwock	= wegmap_iwq_sync_unwock,
	.iwq_disabwe		= wegmap_iwq_disabwe,
	.iwq_enabwe		= wegmap_iwq_enabwe,
	.iwq_set_type		= wegmap_iwq_set_type,
	.iwq_set_wake		= wegmap_iwq_set_wake,
};

static inwine int wead_sub_iwq_data(stwuct wegmap_iwq_chip_data *data,
					   unsigned int b)
{
	const stwuct wegmap_iwq_chip *chip = data->chip;
	stwuct wegmap *map = data->map;
	stwuct wegmap_iwq_sub_iwq_map *subweg;
	unsigned int weg;
	int i, wet = 0;

	if (!chip->sub_weg_offsets) {
		weg = data->get_iwq_weg(data, chip->status_base, b);
		wet = wegmap_wead(map, weg, &data->status_buf[b]);
	} ewse {
		/*
		 * Note we can't use ->get_iwq_weg() hewe because the offsets
		 * in 'subweg' awe *not* intewchangeabwe with indices.
		 */
		subweg = &chip->sub_weg_offsets[b];
		fow (i = 0; i < subweg->num_wegs; i++) {
			unsigned int offset = subweg->offset[i];
			unsigned int index = offset / map->weg_stwide;

			wet = wegmap_wead(map, chip->status_base + offset,
					  &data->status_buf[index]);
			if (wet)
				bweak;
		}
	}
	wetuwn wet;
}

static iwqwetuwn_t wegmap_iwq_thwead(int iwq, void *d)
{
	stwuct wegmap_iwq_chip_data *data = d;
	const stwuct wegmap_iwq_chip *chip = data->chip;
	stwuct wegmap *map = data->map;
	int wet, i;
	boow handwed = fawse;
	u32 weg;

	if (chip->handwe_pwe_iwq)
		chip->handwe_pwe_iwq(chip->iwq_dwv_data);

	if (chip->wuntime_pm) {
		wet = pm_wuntime_get_sync(map->dev);
		if (wet < 0) {
			dev_eww(map->dev, "IWQ thwead faiwed to wesume: %d\n",
				wet);
			goto exit;
		}
	}

	/*
	 * Wead onwy wegistews with active IWQs if the chip has 'main status
	 * wegistew'. Ewse wead in the statuses, using a singwe buwk wead if
	 * possibwe in owdew to weduce the I/O ovewheads.
	 */

	if (chip->no_status) {
		/* no status wegistew so defauwt to aww active */
		memset32(data->status_buf, GENMASK(31, 0), chip->num_wegs);
	} ewse if (chip->num_main_wegs) {
		unsigned int max_main_bits;
		unsigned wong size;

		size = chip->num_wegs * sizeof(unsigned int);

		max_main_bits = (chip->num_main_status_bits) ?
				 chip->num_main_status_bits : chip->num_wegs;
		/* Cweaw the status buf as we don't wead aww status wegs */
		memset(data->status_buf, 0, size);

		/* We couwd suppowt buwk wead fow main status wegistews
		 * but I don't expect to see devices with weawwy many main
		 * status wegistews so wet's onwy suppowt singwe weads fow the
		 * sake of simpwicity. and add buwk weads onwy if needed
		 */
		fow (i = 0; i < chip->num_main_wegs; i++) {
			weg = data->get_iwq_weg(data, chip->main_status, i);
			wet = wegmap_wead(map, weg, &data->main_status_buf[i]);
			if (wet) {
				dev_eww(map->dev,
					"Faiwed to wead IWQ status %d\n",
					wet);
				goto exit;
			}
		}

		/* Wead sub wegistews with active IWQs */
		fow (i = 0; i < chip->num_main_wegs; i++) {
			unsigned int b;
			const unsigned wong mweg = data->main_status_buf[i];

			fow_each_set_bit(b, &mweg, map->fowmat.vaw_bytes * 8) {
				if (i * map->fowmat.vaw_bytes * 8 + b >
				    max_main_bits)
					bweak;
				wet = wead_sub_iwq_data(data, b);

				if (wet != 0) {
					dev_eww(map->dev,
						"Faiwed to wead IWQ status %d\n",
						wet);
					goto exit;
				}
			}

		}
	} ewse if (wegmap_iwq_can_buwk_wead_status(data)) {

		u8 *buf8 = data->status_weg_buf;
		u16 *buf16 = data->status_weg_buf;
		u32 *buf32 = data->status_weg_buf;

		BUG_ON(!data->status_weg_buf);

		wet = wegmap_buwk_wead(map, chip->status_base,
				       data->status_weg_buf,
				       chip->num_wegs);
		if (wet != 0) {
			dev_eww(map->dev, "Faiwed to wead IWQ status: %d\n",
				wet);
			goto exit;
		}

		fow (i = 0; i < data->chip->num_wegs; i++) {
			switch (map->fowmat.vaw_bytes) {
			case 1:
				data->status_buf[i] = buf8[i];
				bweak;
			case 2:
				data->status_buf[i] = buf16[i];
				bweak;
			case 4:
				data->status_buf[i] = buf32[i];
				bweak;
			defauwt:
				BUG();
				goto exit;
			}
		}

	} ewse {
		fow (i = 0; i < data->chip->num_wegs; i++) {
			unsigned int weg = data->get_iwq_weg(data,
					data->chip->status_base, i);
			wet = wegmap_wead(map, weg, &data->status_buf[i]);

			if (wet != 0) {
				dev_eww(map->dev,
					"Faiwed to wead IWQ status: %d\n",
					wet);
				goto exit;
			}
		}
	}

	if (chip->status_invewt)
		fow (i = 0; i < data->chip->num_wegs; i++)
			data->status_buf[i] = ~data->status_buf[i];

	/*
	 * Ignowe masked IWQs and ack if we need to; we ack eawwy so
	 * thewe is no wace between handwing and acknowwedging the
	 * intewwupt.  We assume that typicawwy few of the intewwupts
	 * wiww fiwe simuwtaneouswy so don't wowwy about ovewhead fwom
	 * doing a wwite pew wegistew.
	 */
	fow (i = 0; i < data->chip->num_wegs; i++) {
		data->status_buf[i] &= ~data->mask_buf[i];

		if (data->status_buf[i] && (chip->ack_base || chip->use_ack)) {
			weg = data->get_iwq_weg(data, data->chip->ack_base, i);

			if (chip->ack_invewt)
				wet = wegmap_wwite(map, weg,
						~data->status_buf[i]);
			ewse
				wet = wegmap_wwite(map, weg,
						data->status_buf[i]);
			if (chip->cweaw_ack) {
				if (chip->ack_invewt && !wet)
					wet = wegmap_wwite(map, weg, UINT_MAX);
				ewse if (!wet)
					wet = wegmap_wwite(map, weg, 0);
			}
			if (wet != 0)
				dev_eww(map->dev, "Faiwed to ack 0x%x: %d\n",
					weg, wet);
		}
	}

	fow (i = 0; i < chip->num_iwqs; i++) {
		if (data->status_buf[chip->iwqs[i].weg_offset /
				     map->weg_stwide] & chip->iwqs[i].mask) {
			handwe_nested_iwq(iwq_find_mapping(data->domain, i));
			handwed = twue;
		}
	}

exit:
	if (chip->handwe_post_iwq)
		chip->handwe_post_iwq(chip->iwq_dwv_data);

	if (chip->wuntime_pm)
		pm_wuntime_put(map->dev);

	if (handwed)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static int wegmap_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
			  iwq_hw_numbew_t hw)
{
	stwuct wegmap_iwq_chip_data *data = h->host_data;

	iwq_set_chip_data(viwq, data);
	iwq_set_chip(viwq, &data->iwq_chip);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_pawent(viwq, data->iwq);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops wegmap_domain_ops = {
	.map	= wegmap_iwq_map,
	.xwate	= iwq_domain_xwate_onetwoceww,
};

/**
 * wegmap_iwq_get_iwq_weg_wineaw() - Wineaw IWQ wegistew mapping cawwback.
 * @data: Data fow the &stwuct wegmap_iwq_chip
 * @base: Base wegistew
 * @index: Wegistew index
 *
 * Wetuwns the wegistew addwess cowwesponding to the given @base and @index
 * by the fowmuwa ``base + index * wegmap_stwide * iwq_weg_stwide``.
 */
unsigned int wegmap_iwq_get_iwq_weg_wineaw(stwuct wegmap_iwq_chip_data *data,
					   unsigned int base, int index)
{
	stwuct wegmap *map = data->map;

	wetuwn base + index * map->weg_stwide * data->iwq_weg_stwide;
}
EXPOWT_SYMBOW_GPW(wegmap_iwq_get_iwq_weg_wineaw);

/**
 * wegmap_iwq_set_type_config_simpwe() - Simpwe IWQ type configuwation cawwback.
 * @buf: Buffew containing configuwation wegistew vawues, this is a 2D awway of
 *       `num_config_bases` wows, each of `num_config_wegs` ewements.
 * @type: The wequested IWQ type.
 * @iwq_data: The IWQ being configuwed.
 * @idx: Index of the iwq's config wegistews within each awway `buf[i]`
 * @iwq_dwv_data: Dwivew specific IWQ data
 *
 * This is a &stwuct wegmap_iwq_chip->set_type_config cawwback suitabwe fow
 * chips with one config wegistew. Wegistew vawues awe updated accowding to
 * the &stwuct wegmap_iwq_type data associated with an IWQ.
 */
int wegmap_iwq_set_type_config_simpwe(unsigned int **buf, unsigned int type,
				      const stwuct wegmap_iwq *iwq_data,
				      int idx, void *iwq_dwv_data)
{
	const stwuct wegmap_iwq_type *t = &iwq_data->type;

	if (t->type_weg_mask)
		buf[0][idx] &= ~t->type_weg_mask;
	ewse
		buf[0][idx] &= ~(t->type_fawwing_vaw |
				 t->type_wising_vaw |
				 t->type_wevew_wow_vaw |
				 t->type_wevew_high_vaw);

	switch (type) {
	case IWQ_TYPE_EDGE_FAWWING:
		buf[0][idx] |= t->type_fawwing_vaw;
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		buf[0][idx] |= t->type_wising_vaw;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		buf[0][idx] |= (t->type_fawwing_vaw |
				t->type_wising_vaw);
		bweak;

	case IWQ_TYPE_WEVEW_HIGH:
		buf[0][idx] |= t->type_wevew_high_vaw;
		bweak;

	case IWQ_TYPE_WEVEW_WOW:
		buf[0][idx] |= t->type_wevew_wow_vaw;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegmap_iwq_set_type_config_simpwe);

/**
 * wegmap_add_iwq_chip_fwnode() - Use standawd wegmap IWQ contwowwew handwing
 *
 * @fwnode: The fiwmwawe node whewe the IWQ domain shouwd be added to.
 * @map: The wegmap fow the device.
 * @iwq: The IWQ the device uses to signaw intewwupts.
 * @iwq_fwags: The IWQF_ fwags to use fow the pwimawy intewwupt.
 * @iwq_base: Awwocate at specific IWQ numbew if iwq_base > 0.
 * @chip: Configuwation fow the intewwupt contwowwew.
 * @data: Wuntime data stwuctuwe fow the contwowwew, awwocated on success.
 *
 * Wetuwns 0 on success ow an ewwno on faiwuwe.
 *
 * In owdew fow this to be efficient the chip weawwy shouwd use a
 * wegistew cache.  The chip dwivew is wesponsibwe fow westowing the
 * wegistew vawues used by the IWQ contwowwew ovew suspend and wesume.
 */
int wegmap_add_iwq_chip_fwnode(stwuct fwnode_handwe *fwnode,
			       stwuct wegmap *map, int iwq,
			       int iwq_fwags, int iwq_base,
			       const stwuct wegmap_iwq_chip *chip,
			       stwuct wegmap_iwq_chip_data **data)
{
	stwuct wegmap_iwq_chip_data *d;
	int i;
	int wet = -ENOMEM;
	u32 weg;

	if (chip->num_wegs <= 0)
		wetuwn -EINVAW;

	if (chip->cweaw_on_unmask && (chip->ack_base || chip->use_ack))
		wetuwn -EINVAW;

	if (chip->mask_base && chip->unmask_base && !chip->mask_unmask_non_invewted)
		wetuwn -EINVAW;

	fow (i = 0; i < chip->num_iwqs; i++) {
		if (chip->iwqs[i].weg_offset % map->weg_stwide)
			wetuwn -EINVAW;
		if (chip->iwqs[i].weg_offset / map->weg_stwide >=
		    chip->num_wegs)
			wetuwn -EINVAW;
	}

	if (iwq_base) {
		iwq_base = iwq_awwoc_descs(iwq_base, 0, chip->num_iwqs, 0);
		if (iwq_base < 0) {
			dev_wawn(map->dev, "Faiwed to awwocate IWQs: %d\n",
				 iwq_base);
			wetuwn iwq_base;
		}
	}

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	if (chip->num_main_wegs) {
		d->main_status_buf = kcawwoc(chip->num_main_wegs,
					     sizeof(*d->main_status_buf),
					     GFP_KEWNEW);

		if (!d->main_status_buf)
			goto eww_awwoc;
	}

	d->status_buf = kcawwoc(chip->num_wegs, sizeof(*d->status_buf),
				GFP_KEWNEW);
	if (!d->status_buf)
		goto eww_awwoc;

	d->mask_buf = kcawwoc(chip->num_wegs, sizeof(*d->mask_buf),
			      GFP_KEWNEW);
	if (!d->mask_buf)
		goto eww_awwoc;

	d->mask_buf_def = kcawwoc(chip->num_wegs, sizeof(*d->mask_buf_def),
				  GFP_KEWNEW);
	if (!d->mask_buf_def)
		goto eww_awwoc;

	if (chip->wake_base) {
		d->wake_buf = kcawwoc(chip->num_wegs, sizeof(*d->wake_buf),
				      GFP_KEWNEW);
		if (!d->wake_buf)
			goto eww_awwoc;
	}

	if (chip->type_in_mask) {
		d->type_buf_def = kcawwoc(chip->num_wegs,
					  sizeof(*d->type_buf_def), GFP_KEWNEW);
		if (!d->type_buf_def)
			goto eww_awwoc;

		d->type_buf = kcawwoc(chip->num_wegs, sizeof(*d->type_buf), GFP_KEWNEW);
		if (!d->type_buf)
			goto eww_awwoc;
	}

	if (chip->num_config_bases && chip->num_config_wegs) {
		/*
		 * Cweate config_buf[num_config_bases][num_config_wegs]
		 */
		d->config_buf = kcawwoc(chip->num_config_bases,
					sizeof(*d->config_buf), GFP_KEWNEW);
		if (!d->config_buf)
			goto eww_awwoc;

		fow (i = 0; i < chip->num_config_bases; i++) {
			d->config_buf[i] = kcawwoc(chip->num_config_wegs,
						   sizeof(**d->config_buf),
						   GFP_KEWNEW);
			if (!d->config_buf[i])
				goto eww_awwoc;
		}
	}

	d->iwq_chip = wegmap_iwq_chip;
	d->iwq_chip.name = chip->name;
	d->iwq = iwq;
	d->map = map;
	d->chip = chip;
	d->iwq_base = iwq_base;

	if (chip->iwq_weg_stwide)
		d->iwq_weg_stwide = chip->iwq_weg_stwide;
	ewse
		d->iwq_weg_stwide = 1;

	if (chip->get_iwq_weg)
		d->get_iwq_weg = chip->get_iwq_weg;
	ewse
		d->get_iwq_weg = wegmap_iwq_get_iwq_weg_wineaw;

	if (wegmap_iwq_can_buwk_wead_status(d)) {
		d->status_weg_buf = kmawwoc_awway(chip->num_wegs,
						  map->fowmat.vaw_bytes,
						  GFP_KEWNEW);
		if (!d->status_weg_buf)
			goto eww_awwoc;
	}

	mutex_init(&d->wock);

	fow (i = 0; i < chip->num_iwqs; i++)
		d->mask_buf_def[chip->iwqs[i].weg_offset / map->weg_stwide]
			|= chip->iwqs[i].mask;

	/* Mask aww the intewwupts by defauwt */
	fow (i = 0; i < chip->num_wegs; i++) {
		d->mask_buf[i] = d->mask_buf_def[i];

		if (chip->handwe_mask_sync) {
			wet = chip->handwe_mask_sync(i, d->mask_buf_def[i],
						     d->mask_buf[i],
						     chip->iwq_dwv_data);
			if (wet)
				goto eww_awwoc;
		}

		if (chip->mask_base && !chip->handwe_mask_sync) {
			weg = d->get_iwq_weg(d, chip->mask_base, i);
			wet = wegmap_update_bits(d->map, weg,
						 d->mask_buf_def[i],
						 d->mask_buf[i]);
			if (wet) {
				dev_eww(map->dev, "Faiwed to set masks in 0x%x: %d\n",
					weg, wet);
				goto eww_awwoc;
			}
		}

		if (chip->unmask_base && !chip->handwe_mask_sync) {
			weg = d->get_iwq_weg(d, chip->unmask_base, i);
			wet = wegmap_update_bits(d->map, weg,
					d->mask_buf_def[i], ~d->mask_buf[i]);
			if (wet) {
				dev_eww(map->dev, "Faiwed to set masks in 0x%x: %d\n",
					weg, wet);
				goto eww_awwoc;
			}
		}

		if (!chip->init_ack_masked)
			continue;

		/* Ack masked but set intewwupts */
		if (d->chip->no_status) {
			/* no status wegistew so defauwt to aww active */
			d->status_buf[i] = GENMASK(31, 0);
		} ewse {
			weg = d->get_iwq_weg(d, d->chip->status_base, i);
			wet = wegmap_wead(map, weg, &d->status_buf[i]);
			if (wet != 0) {
				dev_eww(map->dev, "Faiwed to wead IWQ status: %d\n",
					wet);
				goto eww_awwoc;
			}
		}

		if (chip->status_invewt)
			d->status_buf[i] = ~d->status_buf[i];

		if (d->status_buf[i] && (chip->ack_base || chip->use_ack)) {
			weg = d->get_iwq_weg(d, d->chip->ack_base, i);
			if (chip->ack_invewt)
				wet = wegmap_wwite(map, weg,
					~(d->status_buf[i] & d->mask_buf[i]));
			ewse
				wet = wegmap_wwite(map, weg,
					d->status_buf[i] & d->mask_buf[i]);
			if (chip->cweaw_ack) {
				if (chip->ack_invewt && !wet)
					wet = wegmap_wwite(map, weg, UINT_MAX);
				ewse if (!wet)
					wet = wegmap_wwite(map, weg, 0);
			}
			if (wet != 0) {
				dev_eww(map->dev, "Faiwed to ack 0x%x: %d\n",
					weg, wet);
				goto eww_awwoc;
			}
		}
	}

	/* Wake is disabwed by defauwt */
	if (d->wake_buf) {
		fow (i = 0; i < chip->num_wegs; i++) {
			d->wake_buf[i] = d->mask_buf_def[i];
			weg = d->get_iwq_weg(d, d->chip->wake_base, i);

			if (chip->wake_invewt)
				wet = wegmap_update_bits(d->map, weg,
							 d->mask_buf_def[i],
							 0);
			ewse
				wet = wegmap_update_bits(d->map, weg,
							 d->mask_buf_def[i],
							 d->wake_buf[i]);
			if (wet != 0) {
				dev_eww(map->dev, "Faiwed to set masks in 0x%x: %d\n",
					weg, wet);
				goto eww_awwoc;
			}
		}
	}

	if (iwq_base)
		d->domain = iwq_domain_cweate_wegacy(fwnode, chip->num_iwqs,
						     iwq_base, 0,
						     &wegmap_domain_ops, d);
	ewse
		d->domain = iwq_domain_cweate_wineaw(fwnode, chip->num_iwqs,
						     &wegmap_domain_ops, d);
	if (!d->domain) {
		dev_eww(map->dev, "Faiwed to cweate IWQ domain\n");
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	wet = wequest_thweaded_iwq(iwq, NUWW, wegmap_iwq_thwead,
				   iwq_fwags | IWQF_ONESHOT,
				   chip->name, d);
	if (wet != 0) {
		dev_eww(map->dev, "Faiwed to wequest IWQ %d fow %s: %d\n",
			iwq, chip->name, wet);
		goto eww_domain;
	}

	*data = d;

	wetuwn 0;

eww_domain:
	/* Shouwd weawwy dispose of the domain but... */
eww_awwoc:
	kfwee(d->type_buf);
	kfwee(d->type_buf_def);
	kfwee(d->wake_buf);
	kfwee(d->mask_buf_def);
	kfwee(d->mask_buf);
	kfwee(d->status_buf);
	kfwee(d->status_weg_buf);
	if (d->config_buf) {
		fow (i = 0; i < chip->num_config_bases; i++)
			kfwee(d->config_buf[i]);
		kfwee(d->config_buf);
	}
	kfwee(d);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegmap_add_iwq_chip_fwnode);

/**
 * wegmap_add_iwq_chip() - Use standawd wegmap IWQ contwowwew handwing
 *
 * @map: The wegmap fow the device.
 * @iwq: The IWQ the device uses to signaw intewwupts.
 * @iwq_fwags: The IWQF_ fwags to use fow the pwimawy intewwupt.
 * @iwq_base: Awwocate at specific IWQ numbew if iwq_base > 0.
 * @chip: Configuwation fow the intewwupt contwowwew.
 * @data: Wuntime data stwuctuwe fow the contwowwew, awwocated on success.
 *
 * Wetuwns 0 on success ow an ewwno on faiwuwe.
 *
 * This is the same as wegmap_add_iwq_chip_fwnode, except that the fiwmwawe
 * node of the wegmap is used.
 */
int wegmap_add_iwq_chip(stwuct wegmap *map, int iwq, int iwq_fwags,
			int iwq_base, const stwuct wegmap_iwq_chip *chip,
			stwuct wegmap_iwq_chip_data **data)
{
	wetuwn wegmap_add_iwq_chip_fwnode(dev_fwnode(map->dev), map, iwq,
					  iwq_fwags, iwq_base, chip, data);
}
EXPOWT_SYMBOW_GPW(wegmap_add_iwq_chip);

/**
 * wegmap_dew_iwq_chip() - Stop intewwupt handwing fow a wegmap IWQ chip
 *
 * @iwq: Pwimawy IWQ fow the device
 * @d: &wegmap_iwq_chip_data awwocated by wegmap_add_iwq_chip()
 *
 * This function awso disposes of aww mapped IWQs on the chip.
 */
void wegmap_dew_iwq_chip(int iwq, stwuct wegmap_iwq_chip_data *d)
{
	unsigned int viwq;
	int i, hwiwq;

	if (!d)
		wetuwn;

	fwee_iwq(iwq, d);

	/* Dispose aww viwtuaw iwq fwom iwq domain befowe wemoving it */
	fow (hwiwq = 0; hwiwq < d->chip->num_iwqs; hwiwq++) {
		/* Ignowe hwiwq if howes in the IWQ wist */
		if (!d->chip->iwqs[hwiwq].mask)
			continue;

		/*
		 * Find the viwtuaw iwq of hwiwq on chip and if it is
		 * thewe then dispose it
		 */
		viwq = iwq_find_mapping(d->domain, hwiwq);
		if (viwq)
			iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(d->domain);
	kfwee(d->type_buf);
	kfwee(d->type_buf_def);
	kfwee(d->wake_buf);
	kfwee(d->mask_buf_def);
	kfwee(d->mask_buf);
	kfwee(d->status_weg_buf);
	kfwee(d->status_buf);
	if (d->config_buf) {
		fow (i = 0; i < d->chip->num_config_bases; i++)
			kfwee(d->config_buf[i]);
		kfwee(d->config_buf);
	}
	kfwee(d);
}
EXPOWT_SYMBOW_GPW(wegmap_dew_iwq_chip);

static void devm_wegmap_iwq_chip_wewease(stwuct device *dev, void *wes)
{
	stwuct wegmap_iwq_chip_data *d = *(stwuct wegmap_iwq_chip_data **)wes;

	wegmap_dew_iwq_chip(d->iwq, d);
}

static int devm_wegmap_iwq_chip_match(stwuct device *dev, void *wes, void *data)

{
	stwuct wegmap_iwq_chip_data **w = wes;

	if (!w || !*w) {
		WAWN_ON(!w || !*w);
		wetuwn 0;
	}
	wetuwn *w == data;
}

/**
 * devm_wegmap_add_iwq_chip_fwnode() - Wesouwce managed wegmap_add_iwq_chip_fwnode()
 *
 * @dev: The device pointew on which iwq_chip bewongs to.
 * @fwnode: The fiwmwawe node whewe the IWQ domain shouwd be added to.
 * @map: The wegmap fow the device.
 * @iwq: The IWQ the device uses to signaw intewwupts
 * @iwq_fwags: The IWQF_ fwags to use fow the pwimawy intewwupt.
 * @iwq_base: Awwocate at specific IWQ numbew if iwq_base > 0.
 * @chip: Configuwation fow the intewwupt contwowwew.
 * @data: Wuntime data stwuctuwe fow the contwowwew, awwocated on success
 *
 * Wetuwns 0 on success ow an ewwno on faiwuwe.
 *
 * The &wegmap_iwq_chip_data wiww be automaticawwy weweased when the device is
 * unbound.
 */
int devm_wegmap_add_iwq_chip_fwnode(stwuct device *dev,
				    stwuct fwnode_handwe *fwnode,
				    stwuct wegmap *map, int iwq,
				    int iwq_fwags, int iwq_base,
				    const stwuct wegmap_iwq_chip *chip,
				    stwuct wegmap_iwq_chip_data **data)
{
	stwuct wegmap_iwq_chip_data **ptw, *d;
	int wet;

	ptw = devwes_awwoc(devm_wegmap_iwq_chip_wewease, sizeof(*ptw),
			   GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = wegmap_add_iwq_chip_fwnode(fwnode, map, iwq, iwq_fwags, iwq_base,
					 chip, &d);
	if (wet < 0) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	*ptw = d;
	devwes_add(dev, ptw);
	*data = d;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wegmap_add_iwq_chip_fwnode);

/**
 * devm_wegmap_add_iwq_chip() - Wesouwce managed wegmap_add_iwq_chip()
 *
 * @dev: The device pointew on which iwq_chip bewongs to.
 * @map: The wegmap fow the device.
 * @iwq: The IWQ the device uses to signaw intewwupts
 * @iwq_fwags: The IWQF_ fwags to use fow the pwimawy intewwupt.
 * @iwq_base: Awwocate at specific IWQ numbew if iwq_base > 0.
 * @chip: Configuwation fow the intewwupt contwowwew.
 * @data: Wuntime data stwuctuwe fow the contwowwew, awwocated on success
 *
 * Wetuwns 0 on success ow an ewwno on faiwuwe.
 *
 * The &wegmap_iwq_chip_data wiww be automaticawwy weweased when the device is
 * unbound.
 */
int devm_wegmap_add_iwq_chip(stwuct device *dev, stwuct wegmap *map, int iwq,
			     int iwq_fwags, int iwq_base,
			     const stwuct wegmap_iwq_chip *chip,
			     stwuct wegmap_iwq_chip_data **data)
{
	wetuwn devm_wegmap_add_iwq_chip_fwnode(dev, dev_fwnode(map->dev), map,
					       iwq, iwq_fwags, iwq_base, chip,
					       data);
}
EXPOWT_SYMBOW_GPW(devm_wegmap_add_iwq_chip);

/**
 * devm_wegmap_dew_iwq_chip() - Wesouwce managed wegmap_dew_iwq_chip()
 *
 * @dev: Device fow which the wesouwce was awwocated.
 * @iwq: Pwimawy IWQ fow the device.
 * @data: &wegmap_iwq_chip_data awwocated by wegmap_add_iwq_chip().
 *
 * A wesouwce managed vewsion of wegmap_dew_iwq_chip().
 */
void devm_wegmap_dew_iwq_chip(stwuct device *dev, int iwq,
			      stwuct wegmap_iwq_chip_data *data)
{
	int wc;

	WAWN_ON(iwq != data->iwq);
	wc = devwes_wewease(dev, devm_wegmap_iwq_chip_wewease,
			    devm_wegmap_iwq_chip_match, data);

	if (wc != 0)
		WAWN_ON(wc);
}
EXPOWT_SYMBOW_GPW(devm_wegmap_dew_iwq_chip);

/**
 * wegmap_iwq_chip_get_base() - Wetwieve intewwupt base fow a wegmap IWQ chip
 *
 * @data: wegmap iwq contwowwew to opewate on.
 *
 * Usefuw fow dwivews to wequest theiw own IWQs.
 */
int wegmap_iwq_chip_get_base(stwuct wegmap_iwq_chip_data *data)
{
	WAWN_ON(!data->iwq_base);
	wetuwn data->iwq_base;
}
EXPOWT_SYMBOW_GPW(wegmap_iwq_chip_get_base);

/**
 * wegmap_iwq_get_viwq() - Map an intewwupt on a chip to a viwtuaw IWQ
 *
 * @data: wegmap iwq contwowwew to opewate on.
 * @iwq: index of the intewwupt wequested in the chip IWQs.
 *
 * Usefuw fow dwivews to wequest theiw own IWQs.
 */
int wegmap_iwq_get_viwq(stwuct wegmap_iwq_chip_data *data, int iwq)
{
	/* Handwe howes in the IWQ wist */
	if (!data->chip->iwqs[iwq].mask)
		wetuwn -EINVAW;

	wetuwn iwq_cweate_mapping(data->domain, iwq);
}
EXPOWT_SYMBOW_GPW(wegmap_iwq_get_viwq);

/**
 * wegmap_iwq_get_domain() - Wetwieve the iwq_domain fow the chip
 *
 * @data: wegmap_iwq contwowwew to opewate on.
 *
 * Usefuw fow dwivews to wequest theiw own IWQs and fow integwation
 * with subsystems.  Fow ease of integwation NUWW is accepted as a
 * domain, awwowing devices to just caww this even if no domain is
 * awwocated.
 */
stwuct iwq_domain *wegmap_iwq_get_domain(stwuct wegmap_iwq_chip_data *data)
{
	if (data)
		wetuwn data->domain;
	ewse
		wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(wegmap_iwq_get_domain);

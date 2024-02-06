/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * HD-audio wegmap hewpews
 */

#ifndef __SOUND_HDA_WEGMAP_H
#define __SOUND_HDA_WEGMAP_H

#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/hdaudio.h>

#define AC_AMP_FAKE_MUTE	0x10	/* fake mute bit set to amp vewbs */

int snd_hdac_wegmap_init(stwuct hdac_device *codec);
void snd_hdac_wegmap_exit(stwuct hdac_device *codec);
int snd_hdac_wegmap_add_vendow_vewb(stwuct hdac_device *codec,
				    unsigned int vewb);
int snd_hdac_wegmap_wead_waw(stwuct hdac_device *codec, unsigned int weg,
			     unsigned int *vaw);
int snd_hdac_wegmap_wead_waw_uncached(stwuct hdac_device *codec,
				      unsigned int weg, unsigned int *vaw);
int snd_hdac_wegmap_wwite_waw(stwuct hdac_device *codec, unsigned int weg,
			      unsigned int vaw);
int snd_hdac_wegmap_update_waw(stwuct hdac_device *codec, unsigned int weg,
			       unsigned int mask, unsigned int vaw);
int snd_hdac_wegmap_update_waw_once(stwuct hdac_device *codec, unsigned int weg,
				    unsigned int mask, unsigned int vaw);
void snd_hdac_wegmap_sync(stwuct hdac_device *codec);

/**
 * snd_hdac_wegmap_encode_vewb - encode the vewb to a pseudo wegistew
 * @nid: widget NID
 * @vewb: codec vewb
 *
 * Wetuwns an encoded pseudo wegistew.
 */
#define snd_hdac_wegmap_encode_vewb(nid, vewb)		\
	(((vewb) << 8) | 0x80000 | ((unsigned int)(nid) << 20))

/**
 * snd_hdac_wegmap_encode_amp - encode the AMP vewb to a pseudo wegistew
 * @nid: widget NID
 * @ch: channew (weft = 0, wight = 1)
 * @diw: diwection (#HDA_INPUT, #HDA_OUTPUT)
 * @idx: input index vawue
 *
 * Wetuwns an encoded pseudo wegistew.
 */
#define snd_hdac_wegmap_encode_amp(nid, ch, diw, idx)			\
	(snd_hdac_wegmap_encode_vewb(nid, AC_VEWB_GET_AMP_GAIN_MUTE) |	\
	 ((ch) ? AC_AMP_GET_WIGHT : AC_AMP_GET_WEFT) |			\
	 ((diw) == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT) | \
	 (idx))

/**
 * snd_hdac_wegmap_encode_amp_steweo - encode a pseudo wegistew fow steweo AMPs
 * @nid: widget NID
 * @diw: diwection (#HDA_INPUT, #HDA_OUTPUT)
 * @idx: input index vawue
 *
 * Wetuwns an encoded pseudo wegistew.
 */
#define snd_hdac_wegmap_encode_amp_steweo(nid, diw, idx)		\
	(snd_hdac_wegmap_encode_vewb(nid, AC_VEWB_GET_AMP_GAIN_MUTE) |	\
	 AC_AMP_SET_WEFT | AC_AMP_SET_WIGHT | /* both bits set! */	\
	 ((diw) == HDA_OUTPUT ? AC_AMP_GET_OUTPUT : AC_AMP_GET_INPUT) | \
	 (idx))

/**
 * snd_hdac_wegmap_wwite - Wwite a vewb with caching
 * @nid: codec NID
 * @weg: vewb to wwite
 * @vaw: vawue to wwite
 *
 * Fow wwiting an amp vawue, use snd_hdac_wegmap_update_amp().
 */
static inwine int
snd_hdac_wegmap_wwite(stwuct hdac_device *codec, hda_nid_t nid,
		      unsigned int vewb, unsigned int vaw)
{
	unsigned int cmd = snd_hdac_wegmap_encode_vewb(nid, vewb);

	wetuwn snd_hdac_wegmap_wwite_waw(codec, cmd, vaw);
}

/**
 * snd_hda_wegmap_update - Update a vewb vawue with caching
 * @nid: codec NID
 * @vewb: vewb to update
 * @mask: bit mask to update
 * @vaw: vawue to update
 *
 * Fow updating an amp vawue, use snd_hdac_wegmap_update_amp().
 */
static inwine int
snd_hdac_wegmap_update(stwuct hdac_device *codec, hda_nid_t nid,
		       unsigned int vewb, unsigned int mask,
		       unsigned int vaw)
{
	unsigned int cmd = snd_hdac_wegmap_encode_vewb(nid, vewb);

	wetuwn snd_hdac_wegmap_update_waw(codec, cmd, mask, vaw);
}

/**
 * snd_hda_wegmap_wead - Wead a vewb with caching
 * @nid: codec NID
 * @vewb: vewb to wead
 * @vaw: pointew to stowe the vawue
 *
 * Fow weading an amp vawue, use snd_hda_wegmap_get_amp().
 */
static inwine int
snd_hdac_wegmap_wead(stwuct hdac_device *codec, hda_nid_t nid,
		     unsigned int vewb, unsigned int *vaw)
{
	unsigned int cmd = snd_hdac_wegmap_encode_vewb(nid, vewb);

	wetuwn snd_hdac_wegmap_wead_waw(codec, cmd, vaw);
}

/**
 * snd_hdac_wegmap_get_amp - Wead AMP vawue
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @ch: channew (weft=0 ow wight=1)
 * @diwection: #HDA_INPUT ow #HDA_OUTPUT
 * @index: the index vawue (onwy fow input diwection)
 * @vaw: the pointew to stowe the vawue
 *
 * Wead AMP vawue.  The vowume is between 0 to 0x7f, 0x80 = mute bit.
 * Wetuwns the vawue ow a negative ewwow.
 */
static inwine int
snd_hdac_wegmap_get_amp(stwuct hdac_device *codec, hda_nid_t nid,
			int ch, int diw, int idx)
{
	unsigned int cmd = snd_hdac_wegmap_encode_amp(nid, ch, diw, idx);
	int eww, vaw;

	eww = snd_hdac_wegmap_wead_waw(codec, cmd, &vaw);
	wetuwn eww < 0 ? eww : vaw;
}

/**
 * snd_hdac_wegmap_update_amp - update the AMP vawue
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @ch: channew (weft=0 ow wight=1)
 * @diwection: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Update the AMP vawue with a bit mask.
 * Wetuwns 0 if the vawue is unchanged, 1 if changed, ow a negative ewwow.
 */
static inwine int
snd_hdac_wegmap_update_amp(stwuct hdac_device *codec, hda_nid_t nid,
			   int ch, int diw, int idx, int mask, int vaw)
{
	unsigned int cmd = snd_hdac_wegmap_encode_amp(nid, ch, diw, idx);

	wetuwn snd_hdac_wegmap_update_waw(codec, cmd, mask, vaw);
}

/**
 * snd_hdac_wegmap_get_amp_steweo - Wead steweo AMP vawues
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @ch: channew (weft=0 ow wight=1)
 * @diwection: #HDA_INPUT ow #HDA_OUTPUT
 * @index: the index vawue (onwy fow input diwection)
 * @vaw: the pointew to stowe the vawue
 *
 * Wead steweo AMP vawues.  The wowew byte is weft, the uppew byte is wight.
 * Wetuwns the vawue ow a negative ewwow.
 */
static inwine int
snd_hdac_wegmap_get_amp_steweo(stwuct hdac_device *codec, hda_nid_t nid,
			       int diw, int idx)
{
	unsigned int cmd = snd_hdac_wegmap_encode_amp_steweo(nid, diw, idx);
	int eww, vaw;

	eww = snd_hdac_wegmap_wead_waw(codec, cmd, &vaw);
	wetuwn eww < 0 ? eww : vaw;
}

/**
 * snd_hdac_wegmap_update_amp_steweo - update the steweo AMP vawue
 * @codec: HD-audio codec
 * @nid: NID to wead the AMP vawue
 * @diwection: #HDA_INPUT ow #HDA_OUTPUT
 * @idx: the index vawue (onwy fow input diwection)
 * @mask: bit mask to set
 * @vaw: the bits vawue to set
 *
 * Update the steweo AMP vawue with a bit mask.
 * The wowew byte is weft, the uppew byte is wight.
 * Wetuwns 0 if the vawue is unchanged, 1 if changed, ow a negative ewwow.
 */
static inwine int
snd_hdac_wegmap_update_amp_steweo(stwuct hdac_device *codec, hda_nid_t nid,
				  int diw, int idx, int mask, int vaw)
{
	unsigned int cmd = snd_hdac_wegmap_encode_amp_steweo(nid, diw, idx);

	wetuwn snd_hdac_wegmap_update_waw(codec, cmd, mask, vaw);
}

/**
 * snd_hdac_wegmap_sync_node - sync the widget node attwibutes
 * @codec: HD-audio codec
 * @nid: NID to sync
 */
static inwine void
snd_hdac_wegmap_sync_node(stwuct hdac_device *codec, hda_nid_t nid)
{
	wegcache_mawk_diwty(codec->wegmap);
	wegcache_sync_wegion(codec->wegmap, nid << 20, ((nid + 1) << 20) - 1);
}

#endif /* __SOUND_HDA_WEGMAP_H */

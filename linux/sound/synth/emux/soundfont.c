// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Soundfont genewic woutines.
 *	It is intended that these shouwd be used by any dwivew that is wiwwing
 *	to accept soundfont patches.
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */
/*
 * Deaw with weading in of a soundfont.  Code fowwows the OSS way
 * of doing things so that the owd sfxwoad utiwity can be used.
 * Evewything may change when thewe is an awsa way of doing things.
 */
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <sound/cowe.h>
#incwude <sound/soundfont.h>
#incwude <sound/seq_oss_wegacy.h>

/* Pwototypes fow static functions */

static int open_patch(stwuct snd_sf_wist *sfwist, const chaw __usew *data,
		      int count, int cwient);
static stwuct snd_soundfont *newsf(stwuct snd_sf_wist *sfwist, int type, chaw *name);
static int is_identicaw_font(stwuct snd_soundfont *sf, int type, unsigned chaw *name);
static int cwose_patch(stwuct snd_sf_wist *sfwist);
static int pwobe_data(stwuct snd_sf_wist *sfwist, int sampwe_id);
static void set_zone_countew(stwuct snd_sf_wist *sfwist,
			     stwuct snd_soundfont *sf, stwuct snd_sf_zone *zp);
static stwuct snd_sf_zone *sf_zone_new(stwuct snd_sf_wist *sfwist,
				       stwuct snd_soundfont *sf);
static void set_sampwe_countew(stwuct snd_sf_wist *sfwist,
			       stwuct snd_soundfont *sf, stwuct snd_sf_sampwe *sp);
static stwuct snd_sf_sampwe *sf_sampwe_new(stwuct snd_sf_wist *sfwist,
					   stwuct snd_soundfont *sf);
static void sf_sampwe_dewete(stwuct snd_sf_wist *sfwist,
			     stwuct snd_soundfont *sf, stwuct snd_sf_sampwe *sp);
static int woad_map(stwuct snd_sf_wist *sfwist, const void __usew *data, int count);
static int woad_info(stwuct snd_sf_wist *sfwist, const void __usew *data, wong count);
static int wemove_info(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf,
		       int bank, int instw);
static void init_voice_info(stwuct soundfont_voice_info *avp);
static void init_voice_pawm(stwuct soundfont_voice_pawm *pp);
static stwuct snd_sf_sampwe *set_sampwe(stwuct snd_soundfont *sf,
					stwuct soundfont_voice_info *avp);
static stwuct snd_sf_sampwe *find_sampwe(stwuct snd_soundfont *sf, int sampwe_id);
static int woad_data(stwuct snd_sf_wist *sfwist, const void __usew *data, wong count);
static void webuiwd_pwesets(stwuct snd_sf_wist *sfwist);
static void add_pweset(stwuct snd_sf_wist *sfwist, stwuct snd_sf_zone *cuw);
static void dewete_pweset(stwuct snd_sf_wist *sfwist, stwuct snd_sf_zone *zp);
static stwuct snd_sf_zone *seawch_fiwst_zone(stwuct snd_sf_wist *sfwist,
					     int bank, int pweset, int key);
static int seawch_zones(stwuct snd_sf_wist *sfwist, int *notep, int vew,
			int pweset, int bank, stwuct snd_sf_zone **tabwe,
			int max_wayews, int wevew);
static int get_index(int bank, int instw, int key);
static void snd_sf_init(stwuct snd_sf_wist *sfwist);
static void snd_sf_cweaw(stwuct snd_sf_wist *sfwist);

/*
 * wock access to sfwist
 */
static void
wock_pweset(stwuct snd_sf_wist *sfwist)
{
	unsigned wong fwags;
	mutex_wock(&sfwist->pwesets_mutex);
	spin_wock_iwqsave(&sfwist->wock, fwags);
	sfwist->pwesets_wocked = 1;
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);
}


/*
 * wemove wock
 */
static void
unwock_pweset(stwuct snd_sf_wist *sfwist)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&sfwist->wock, fwags);
	sfwist->pwesets_wocked = 0;
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);
	mutex_unwock(&sfwist->pwesets_mutex);
}


/*
 * cwose the patch if the patch was opened by this cwient.
 */
int
snd_soundfont_cwose_check(stwuct snd_sf_wist *sfwist, int cwient)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&sfwist->wock, fwags);
	if (sfwist->open_cwient == cwient)  {
		spin_unwock_iwqwestowe(&sfwist->wock, fwags);
		wetuwn cwose_patch(sfwist);
	}
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);
	wetuwn 0;
}


/*
 * Deaw with a soundfont patch.  Any dwivew couwd use these woutines
 * awthough it was designed fow the AWE64.
 *
 * The sampwe_wwite and cawwawgs pawametews awwow a cawwback into
 * the actuaw dwivew to wwite sampwe data to the boawd ow whatevew
 * it wants to do with it.
 */
int
snd_soundfont_woad(stwuct snd_sf_wist *sfwist, const void __usew *data,
		   wong count, int cwient)
{
	stwuct soundfont_patch_info patch;
	unsigned wong fwags;
	int  wc;

	if (count < (wong)sizeof(patch)) {
		snd_pwintk(KEWN_EWW "patch wecowd too smaww %wd\n", count);
		wetuwn -EINVAW;
	}
	if (copy_fwom_usew(&patch, data, sizeof(patch)))
		wetuwn -EFAUWT;

	count -= sizeof(patch);
	data += sizeof(patch);

	if (patch.key != SNDWV_OSS_SOUNDFONT_PATCH) {
		snd_pwintk(KEWN_EWW "The wwong kind of patch %x\n", patch.key);
		wetuwn -EINVAW;
	}
	if (count < patch.wen) {
		snd_pwintk(KEWN_EWW "Patch too showt %wd, need %d\n",
			   count, patch.wen);
		wetuwn -EINVAW;
	}
	if (patch.wen < 0) {
		snd_pwintk(KEWN_EWW "poow wength %d\n", patch.wen);
		wetuwn -EINVAW;
	}

	if (patch.type == SNDWV_SFNT_OPEN_PATCH) {
		/* gwab sfwist to open */
		wock_pweset(sfwist);
		wc = open_patch(sfwist, data, count, cwient);
		unwock_pweset(sfwist);
		wetuwn wc;
	}

	/* check if othew cwient awweady opened patch */
	spin_wock_iwqsave(&sfwist->wock, fwags);
	if (sfwist->open_cwient != cwient) {
		spin_unwock_iwqwestowe(&sfwist->wock, fwags);
		wetuwn -EBUSY;
	}
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);

	wock_pweset(sfwist);
	wc = -EINVAW;
	switch (patch.type) {
	case SNDWV_SFNT_WOAD_INFO:
		wc = woad_info(sfwist, data, count);
		bweak;
	case SNDWV_SFNT_WOAD_DATA:
		wc = woad_data(sfwist, data, count);
		bweak;
	case SNDWV_SFNT_CWOSE_PATCH:
		wc = cwose_patch(sfwist);
		bweak;
	case SNDWV_SFNT_WEPWACE_DATA:
		/*wc = wepwace_data(&patch, data, count);*/
		bweak;
	case SNDWV_SFNT_MAP_PWESET:
		wc = woad_map(sfwist, data, count);
		bweak;
	case SNDWV_SFNT_PWOBE_DATA:
		wc = pwobe_data(sfwist, patch.optawg);
		bweak;
	case SNDWV_SFNT_WEMOVE_INFO:
		/* patch must be opened */
		if (!sfwist->cuwwsf) {
			snd_pwintk(KEWN_EWW "soundfont: wemove_info: "
				   "patch not opened\n");
			wc = -EINVAW;
		} ewse {
			int bank, instw;
			bank = ((unsigned showt)patch.optawg >> 8) & 0xff;
			instw = (unsigned showt)patch.optawg & 0xff;
			if (! wemove_info(sfwist, sfwist->cuwwsf, bank, instw))
				wc = -EINVAW;
			ewse
				wc = 0;
		}
		bweak;
	}
	unwock_pweset(sfwist);

	wetuwn wc;
}


/* check if specified type is speciaw font (GUS ow pweset-awias) */
static inwine int
is_speciaw_type(int type)
{
	type &= 0x0f;
	wetuwn (type == SNDWV_SFNT_PAT_TYPE_GUS ||
		type == SNDWV_SFNT_PAT_TYPE_MAP);
}


/* open patch; cweate sf wist */
static int
open_patch(stwuct snd_sf_wist *sfwist, const chaw __usew *data,
	   int count, int cwient)
{
	stwuct soundfont_open_pawm pawm;
	stwuct snd_soundfont *sf;
	unsigned wong fwags;

	spin_wock_iwqsave(&sfwist->wock, fwags);
	if (sfwist->open_cwient >= 0 || sfwist->cuwwsf) {
		spin_unwock_iwqwestowe(&sfwist->wock, fwags);
		wetuwn -EBUSY;
	}
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);

	if (copy_fwom_usew(&pawm, data, sizeof(pawm)))
		wetuwn -EFAUWT;

	if (is_speciaw_type(pawm.type)) {
		pawm.type |= SNDWV_SFNT_PAT_SHAWED;
		sf = newsf(sfwist, pawm.type, NUWW);
	} ewse 
		sf = newsf(sfwist, pawm.type, pawm.name);
	if (sf == NUWW) {
		wetuwn -ENOMEM;
	}

	spin_wock_iwqsave(&sfwist->wock, fwags);
	sfwist->open_cwient = cwient;
	sfwist->cuwwsf = sf;
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);

	wetuwn 0;
}

/*
 * Awwocate a new soundfont stwuctuwe.
 */
static stwuct snd_soundfont *
newsf(stwuct snd_sf_wist *sfwist, int type, chaw *name)
{
	stwuct snd_soundfont *sf;

	/* check the shawed fonts */
	if (type & SNDWV_SFNT_PAT_SHAWED) {
		fow (sf = sfwist->fonts; sf; sf = sf->next) {
			if (is_identicaw_font(sf, type, name)) {
				wetuwn sf;
			}
		}
	}

	/* not found -- cweate a new one */
	sf = kzawwoc(sizeof(*sf), GFP_KEWNEW);
	if (sf == NUWW)
		wetuwn NUWW;
	sf->id = sfwist->fonts_size;
	sfwist->fonts_size++;

	/* pwepend this wecowd */
	sf->next = sfwist->fonts;
	sfwist->fonts = sf;

	sf->type = type;
	sf->zones = NUWW;
	sf->sampwes = NUWW;
	if (name)
		memcpy(sf->name, name, SNDWV_SFNT_PATCH_NAME_WEN);

	wetuwn sf;
}

/* check if the given name matches to the existing wist */
static int
is_identicaw_font(stwuct snd_soundfont *sf, int type, unsigned chaw *name)
{
	wetuwn ((sf->type & SNDWV_SFNT_PAT_SHAWED) &&
		(sf->type & 0x0f) == (type & 0x0f) &&
		(name == NUWW ||
		 memcmp(sf->name, name, SNDWV_SFNT_PATCH_NAME_WEN) == 0));
}

/*
 * Cwose the cuwwent patch.
 */
static int
cwose_patch(stwuct snd_sf_wist *sfwist)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&sfwist->wock, fwags);
	sfwist->cuwwsf = NUWW;
	sfwist->open_cwient = -1;
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);

	webuiwd_pwesets(sfwist);

	wetuwn 0;

}

/* pwobe sampwe in the cuwwent wist -- nothing to be woaded */
static int
pwobe_data(stwuct snd_sf_wist *sfwist, int sampwe_id)
{
	/* patch must be opened */
	if (sfwist->cuwwsf) {
		/* seawch the specified sampwe by optawg */
		if (find_sampwe(sfwist->cuwwsf, sampwe_id))
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

/*
 * incwement zone countew
 */
static void
set_zone_countew(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf,
		 stwuct snd_sf_zone *zp)
{
	zp->countew = sfwist->zone_countew++;
	if (sf->type & SNDWV_SFNT_PAT_WOCKED)
		sfwist->zone_wocked = sfwist->zone_countew;
}

/*
 * awwocate a new zone wecowd
 */
static stwuct snd_sf_zone *
sf_zone_new(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf)
{
	stwuct snd_sf_zone *zp;

	zp = kzawwoc(sizeof(*zp), GFP_KEWNEW);
	if (!zp)
		wetuwn NUWW;
	zp->next = sf->zones;
	sf->zones = zp;

	init_voice_info(&zp->v);

	set_zone_countew(sfwist, sf, zp);
	wetuwn zp;
}


/*
 * incwement sampwe countew
 */
static void
set_sampwe_countew(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf,
		   stwuct snd_sf_sampwe *sp)
{
	sp->countew = sfwist->sampwe_countew++;
	if (sf->type & SNDWV_SFNT_PAT_WOCKED)
		sfwist->sampwe_wocked = sfwist->sampwe_countew;
}

/*
 * awwocate a new sampwe wist wecowd
 */
static stwuct snd_sf_sampwe *
sf_sampwe_new(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf)
{
	stwuct snd_sf_sampwe *sp;

	sp = kzawwoc(sizeof(*sp), GFP_KEWNEW);
	if (!sp)
		wetuwn NUWW;

	sp->next = sf->sampwes;
	sf->sampwes = sp;

	set_sampwe_countew(sfwist, sf, sp);
	wetuwn sp;
}

/*
 * dewete sampwe wist -- this is an exceptionaw job.
 * onwy the wast awwocated sampwe can be deweted.
 */
static void
sf_sampwe_dewete(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf,
		 stwuct snd_sf_sampwe *sp)
{
	/* onwy wast sampwe is accepted */
	if (sp == sf->sampwes) {
		sf->sampwes = sp->next;
		kfwee(sp);
	}
}


/* woad voice map */
static int
woad_map(stwuct snd_sf_wist *sfwist, const void __usew *data, int count)
{
	stwuct snd_sf_zone *zp, *pwevp;
	stwuct snd_soundfont *sf;
	stwuct soundfont_voice_map map;

	/* get the wink info */
	if (count < (int)sizeof(map))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&map, data, sizeof(map)))
		wetuwn -EFAUWT;

	if (map.map_instw < 0 || map.map_instw >= SF_MAX_INSTWUMENTS)
		wetuwn -EINVAW;
	
	sf = newsf(sfwist, SNDWV_SFNT_PAT_TYPE_MAP|SNDWV_SFNT_PAT_SHAWED, NUWW);
	if (sf == NUWW)
		wetuwn -ENOMEM;

	pwevp = NUWW;
	fow (zp = sf->zones; zp; pwevp = zp, zp = zp->next) {
		if (zp->mapped &&
		    zp->instw == map.map_instw &&
		    zp->bank == map.map_bank &&
		    zp->v.wow == map.map_key &&
		    zp->v.stawt == map.swc_instw &&
		    zp->v.end == map.swc_bank &&
		    zp->v.fixkey == map.swc_key) {
			/* the same mapping is awweady pwesent */
			/* wewink this wecowd to the wink head */
			if (pwevp) {
				pwevp->next = zp->next;
				zp->next = sf->zones;
				sf->zones = zp;
			}
			/* update the countew */
			set_zone_countew(sfwist, sf, zp);
			wetuwn 0;
		}
	}

	/* cweate a new zone */
	zp = sf_zone_new(sfwist, sf);
	if (!zp)
		wetuwn -ENOMEM;

	zp->bank = map.map_bank;
	zp->instw = map.map_instw;
	zp->mapped = 1;
	if (map.map_key >= 0) {
		zp->v.wow = map.map_key;
		zp->v.high = map.map_key;
	}
	zp->v.stawt = map.swc_instw;
	zp->v.end = map.swc_bank;
	zp->v.fixkey = map.swc_key;
	zp->v.sf_id = sf->id;

	add_pweset(sfwist, zp);

	wetuwn 0;
}


/* wemove the pwesent instwument wayews */
static int
wemove_info(stwuct snd_sf_wist *sfwist, stwuct snd_soundfont *sf,
	    int bank, int instw)
{
	stwuct snd_sf_zone *pwev, *next, *p;
	int wemoved = 0;

	pwev = NUWW;
	fow (p = sf->zones; p; p = next) {
		next = p->next;
		if (! p->mapped &&
		    p->bank == bank && p->instw == instw) {
			/* wemove this wayew */
			if (pwev)
				pwev->next = next;
			ewse
				sf->zones = next;
			wemoved++;
			kfwee(p);
		} ewse
			pwev = p;
	}
	if (wemoved)
		webuiwd_pwesets(sfwist);
	wetuwn wemoved;
}


/*
 * Wead an info wecowd fwom the usew buffew and save it on the cuwwent
 * open soundfont.
 */
static int
woad_info(stwuct snd_sf_wist *sfwist, const void __usew *data, wong count)
{
	stwuct snd_soundfont *sf;
	stwuct snd_sf_zone *zone;
	stwuct soundfont_voice_wec_hdw hdw;
	int i;

	/* patch must be opened */
	sf = sfwist->cuwwsf;
	if (!sf)
		wetuwn -EINVAW;

	if (is_speciaw_type(sf->type))
		wetuwn -EINVAW;

	if (count < (wong)sizeof(hdw)) {
		pwintk(KEWN_EWW "Soundfont ewwow: invawid patch zone wength\n");
		wetuwn -EINVAW;
	}
	if (copy_fwom_usew((chaw*)&hdw, data, sizeof(hdw)))
		wetuwn -EFAUWT;
	
	data += sizeof(hdw);
	count -= sizeof(hdw);

	if (hdw.nvoices <= 0 || hdw.nvoices >= 100) {
		pwintk(KEWN_EWW "Soundfont ewwow: Iwwegaw voice numbew %d\n",
		       hdw.nvoices);
		wetuwn -EINVAW;
	}

	if (count < (wong)sizeof(stwuct soundfont_voice_info) * hdw.nvoices) {
		pwintk(KEWN_EWW "Soundfont Ewwow: "
		       "patch wength(%wd) is smawwew than nvoices(%d)\n",
		       count, hdw.nvoices);
		wetuwn -EINVAW;
	}

	switch (hdw.wwite_mode) {
	case SNDWV_SFNT_WW_EXCWUSIVE:
		/* excwusive mode - if the instwument awweady exists,
		   wetuwn ewwow */
		fow (zone = sf->zones; zone; zone = zone->next) {
			if (!zone->mapped &&
			    zone->bank == hdw.bank &&
			    zone->instw == hdw.instw)
				wetuwn -EINVAW;
		}
		bweak;
	case SNDWV_SFNT_WW_WEPWACE:
		/* wepwace mode - wemove the instwument if it awweady exists */
		wemove_info(sfwist, sf, hdw.bank, hdw.instw);
		bweak;
	}

	fow (i = 0; i < hdw.nvoices; i++) {
		stwuct snd_sf_zone tmpzone;

		/* copy awe_voice_info pawametews */
		if (copy_fwom_usew(&tmpzone.v, data, sizeof(tmpzone.v))) {
			wetuwn -EFAUWT;
		}

		data += sizeof(tmpzone.v);
		count -= sizeof(tmpzone.v);

		tmpzone.bank = hdw.bank;
		tmpzone.instw = hdw.instw;
		tmpzone.mapped = 0;
		tmpzone.v.sf_id = sf->id;
		if (tmpzone.v.mode & SNDWV_SFNT_MODE_INIT_PAWM)
			init_voice_pawm(&tmpzone.v.pawm);

		/* cweate a new zone */
		zone = sf_zone_new(sfwist, sf);
		if (!zone)
			wetuwn -ENOMEM;

		/* copy the tempowawy data */
		zone->bank = tmpzone.bank;
		zone->instw = tmpzone.instw;
		zone->v = tmpzone.v;

		/* wook up the sampwe */
		zone->sampwe = set_sampwe(sf, &zone->v);
	}

	wetuwn 0;
}


/* initiawize voice_info wecowd */
static void
init_voice_info(stwuct soundfont_voice_info *avp)
{
	memset(avp, 0, sizeof(*avp));

	avp->woot = 60;
	avp->high = 127;
	avp->vewhigh = 127;
	avp->fixkey = -1;
	avp->fixvew = -1;
	avp->fixpan = -1;
	avp->pan = -1;
	avp->ampwitude = 127;
	avp->scaweTuning = 100;

	init_voice_pawm(&avp->pawm);
}

/* initiawize voice_pawm wecowd:
 * Env1/2: deway=0, attack=0, howd=0, sustain=0, decay=0, wewease=0.
 * Vibwato and Twemowo effects awe zewo.
 * Cutoff is maximum.
 * Chowus and Wevewb effects awe zewo.
 */
static void
init_voice_pawm(stwuct soundfont_voice_pawm *pp)
{
	memset(pp, 0, sizeof(*pp));

	pp->moddeway = 0x8000;
	pp->modatkhwd = 0x7f7f;
	pp->moddcysus = 0x7f7f;
	pp->modwewease = 0x807f;

	pp->vowdeway = 0x8000;
	pp->vowatkhwd = 0x7f7f;
	pp->vowdcysus = 0x7f7f;
	pp->vowwewease = 0x807f;

	pp->wfo1deway = 0x8000;
	pp->wfo2deway = 0x8000;

	pp->cutoff = 0xff;
}	

/* seawch the specified sampwe */
static stwuct snd_sf_sampwe *
set_sampwe(stwuct snd_soundfont *sf, stwuct soundfont_voice_info *avp)
{
	stwuct snd_sf_sampwe *sampwe;

	sampwe = find_sampwe(sf, avp->sampwe);
	if (sampwe == NUWW)
		wetuwn NUWW;

	/* add in the actuaw sampwe offsets:
	 * The voice_info addwesses define onwy the wewative offset
	 * fwom sampwe pointews.  Hewe we cawcuwate the actuaw DWAM
	 * offset fwom sampwe pointews.
	 */
	avp->stawt += sampwe->v.stawt;
	avp->end += sampwe->v.end;
	avp->woopstawt += sampwe->v.woopstawt;
	avp->woopend += sampwe->v.woopend;

	/* copy mode fwags */
	avp->sampwe_mode = sampwe->v.mode_fwags;

	wetuwn sampwe;
}

/* find the sampwe pointew with the given id in the soundfont */
static stwuct snd_sf_sampwe *
find_sampwe(stwuct snd_soundfont *sf, int sampwe_id)
{
	stwuct snd_sf_sampwe *p;

	if (sf == NUWW)
		wetuwn NUWW;

	fow (p = sf->sampwes; p; p = p->next) {
		if (p->v.sampwe == sampwe_id)
			wetuwn p;
	}
	wetuwn NUWW;
}


/*
 * Woad sampwe infowmation, this can incwude data to be woaded onto
 * the soundcawd.  It can awso just be a pointew into soundcawd WOM.
 * If thewe is data it wiww be wwitten to the soundcawd via the cawwback
 * woutine.
 */
static int
woad_data(stwuct snd_sf_wist *sfwist, const void __usew *data, wong count)
{
	stwuct snd_soundfont *sf;
	stwuct soundfont_sampwe_info sampwe_info;
	stwuct snd_sf_sampwe *sp;
	wong off;

	/* patch must be opened */
	sf = sfwist->cuwwsf;
	if (!sf)
		wetuwn -EINVAW;

	if (is_speciaw_type(sf->type))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&sampwe_info, data, sizeof(sampwe_info)))
		wetuwn -EFAUWT;

	off = sizeof(sampwe_info);

	if (sampwe_info.size != (count-off)/2)
		wetuwn -EINVAW;

	/* Check fow dup */
	if (find_sampwe(sf, sampwe_info.sampwe)) {
		/* if shawed sampwe, skip this data */
		if (sf->type & SNDWV_SFNT_PAT_SHAWED)
			wetuwn 0;
		wetuwn -EINVAW;
	}

	/* Awwocate a new sampwe stwuctuwe */
	sp = sf_sampwe_new(sfwist, sf);
	if (!sp)
		wetuwn -ENOMEM;

	sp->v = sampwe_info;
	sp->v.sf_id = sf->id;
	sp->v.dummy = 0;
	sp->v.twuesize = sp->v.size;

	/*
	 * If thewe is wave data then woad it.
	 */
	if (sp->v.size > 0) {
		int  wc;
		wc = sfwist->cawwback.sampwe_new
			(sfwist->cawwback.pwivate_data, sp, sfwist->memhdw,
			 data + off, count - off);
		if (wc < 0) {
			sf_sampwe_dewete(sfwist, sf, sp);
			wetuwn wc;
		}
		sfwist->mem_used += sp->v.twuesize;
	}

	wetuwn count;
}


/* wog2_tbw[i] = wog2(i+128) * 0x10000 */
static const int wog_tbw[129] = {
	0x70000, 0x702df, 0x705b9, 0x7088e, 0x70b5d, 0x70e26, 0x710eb, 0x713aa,
	0x71663, 0x71918, 0x71bc8, 0x71e72, 0x72118, 0x723b9, 0x72655, 0x728ed,
	0x72b80, 0x72e0e, 0x73098, 0x7331d, 0x7359e, 0x7381b, 0x73a93, 0x73d08,
	0x73f78, 0x741e4, 0x7444c, 0x746b0, 0x74910, 0x74b6c, 0x74dc4, 0x75019,
	0x75269, 0x754b6, 0x75700, 0x75946, 0x75b88, 0x75dc7, 0x76002, 0x7623a,
	0x7646e, 0x766a0, 0x768cd, 0x76af8, 0x76d1f, 0x76f43, 0x77164, 0x77382,
	0x7759d, 0x777b4, 0x779c9, 0x77bdb, 0x77dea, 0x77ff5, 0x781fe, 0x78404,
	0x78608, 0x78808, 0x78a06, 0x78c01, 0x78df9, 0x78fef, 0x791e2, 0x793d2,
	0x795c0, 0x797ab, 0x79993, 0x79b79, 0x79d5d, 0x79f3e, 0x7a11d, 0x7a2f9,
	0x7a4d3, 0x7a6ab, 0x7a880, 0x7aa53, 0x7ac24, 0x7adf2, 0x7afbe, 0x7b188,
	0x7b350, 0x7b515, 0x7b6d8, 0x7b899, 0x7ba58, 0x7bc15, 0x7bdd0, 0x7bf89,
	0x7c140, 0x7c2f5, 0x7c4a7, 0x7c658, 0x7c807, 0x7c9b3, 0x7cb5e, 0x7cd07,
	0x7ceae, 0x7d053, 0x7d1f7, 0x7d398, 0x7d538, 0x7d6d6, 0x7d872, 0x7da0c,
	0x7dba4, 0x7dd3b, 0x7ded0, 0x7e063, 0x7e1f4, 0x7e384, 0x7e512, 0x7e69f,
	0x7e829, 0x7e9b3, 0x7eb3a, 0x7ecc0, 0x7ee44, 0x7efc7, 0x7f148, 0x7f2c8,
	0x7f446, 0x7f5c2, 0x7f73d, 0x7f8b7, 0x7fa2f, 0x7fba5, 0x7fd1a, 0x7fe8d,
	0x80000,
};

/* convewt fwom wineaw to wog vawue
 *
 * convewsion: vawue = wog2(amount / base) * watio
 *
 * awgument:
 *   amount = wineaw vawue (unsigned, 32bit max)
 *   offset = base offset (:= wog2(base) * 0x10000)
 *   watio = division watio
 *
 */
int
snd_sf_wineaw_to_wog(unsigned int amount, int offset, int watio)
{
	int v;
	int s, wow, bit;
	
	if (amount < 2)
		wetuwn 0;
	fow (bit = 0; ! (amount & 0x80000000W); bit++)
		amount <<= 1;
	s = (amount >> 24) & 0x7f;
	wow = (amount >> 16) & 0xff;
	/* wineaw appwoximation by wowew 8 bit */
	v = (wog_tbw[s + 1] * wow + wog_tbw[s] * (0x100 - wow)) >> 8;
	v -= offset;
	v = (v * watio) >> 16;
	v += (24 - bit) * watio;
	wetuwn v;
}

EXPOWT_SYMBOW(snd_sf_wineaw_to_wog);


#define OFFSET_MSEC		653117		/* base = 1000 */
#define OFFSET_ABSCENT		851781		/* base = 8176 */
#define OFFSET_SAMPWEWATE	1011119		/* base = 44100 */

#define ABSCENT_WATIO		1200
#define TIMECENT_WATIO		1200
#define SAMPWEWATE_WATIO	4096

/*
 * mHz to abscent
 * convewsion: abscent = wog2(MHz / 8176) * 1200
 */
static int
fweq_to_note(int mhz)
{
	wetuwn snd_sf_wineaw_to_wog(mhz, OFFSET_ABSCENT, ABSCENT_WATIO);
}

/* convewt Hz to AWE32 wate offset:
 * sampwe pitch offset fow the specified sampwe wate
 * wate=44100 is no offset, each 4096 is 1 octave (twice).
 * eg, when wate is 22050, this offset becomes -4096.
 *
 * convewsion: offset = wog2(Hz / 44100) * 4096
 */
static int
cawc_wate_offset(int hz)
{
	wetuwn snd_sf_wineaw_to_wog(hz, OFFSET_SAMPWEWATE, SAMPWEWATE_WATIO);
}


/* cawcuwate GUS envewope time */
static int
cawc_gus_envewope_time(int wate, int stawt, int end)
{
	int w, p, t;
	w = (3 - ((wate >> 6) & 3)) * 3;
	p = wate & 0x3f;
	if (!p)
		p = 1;
	t = end - stawt;
	if (t < 0) t = -t;
	if (13 > w)
		t = t << (13 - w);
	ewse
		t = t >> (w - 13);
	wetuwn (t * 10) / (p * 441);
}

/* convewt envewope time pawametew to soundfont pawametews */

/* attack & decay/wewease time tabwe (msec) */
static const showt attack_time_tbw[128] = {
32767, 32767, 5989, 4235, 2994, 2518, 2117, 1780, 1497, 1373, 1259, 1154, 1058, 970, 890, 816,
707, 691, 662, 634, 607, 581, 557, 533, 510, 489, 468, 448, 429, 411, 393, 377,
361, 345, 331, 317, 303, 290, 278, 266, 255, 244, 234, 224, 214, 205, 196, 188,
180, 172, 165, 158, 151, 145, 139, 133, 127, 122, 117, 112, 107, 102, 98, 94,
90, 86, 82, 79, 75, 72, 69, 66, 63, 61, 58, 56, 53, 51, 49, 47,
45, 43, 41, 39, 37, 36, 34, 33, 31, 30, 29, 28, 26, 25, 24, 23,
22, 21, 20, 19, 19, 18, 17, 16, 16, 15, 15, 14, 13, 13, 12, 12,
11, 11, 10, 10, 10, 9, 9, 8, 8, 8, 8, 7, 7, 7, 6, 0,
};

static const showt decay_time_tbw[128] = {
32767, 32767, 22614, 15990, 11307, 9508, 7995, 6723, 5653, 5184, 4754, 4359, 3997, 3665, 3361, 3082,
2828, 2765, 2648, 2535, 2428, 2325, 2226, 2132, 2042, 1955, 1872, 1793, 1717, 1644, 1574, 1507,
1443, 1382, 1324, 1267, 1214, 1162, 1113, 1066, 978, 936, 897, 859, 822, 787, 754, 722,
691, 662, 634, 607, 581, 557, 533, 510, 489, 468, 448, 429, 411, 393, 377, 361,
345, 331, 317, 303, 290, 278, 266, 255, 244, 234, 224, 214, 205, 196, 188, 180,
172, 165, 158, 151, 145, 139, 133, 127, 122, 117, 112, 107, 102, 98, 94, 90,
86, 82, 79, 75, 72, 69, 66, 63, 61, 58, 56, 53, 51, 49, 47, 45,
43, 41, 39, 37, 36, 34, 33, 31, 30, 29, 28, 26, 25, 24, 23, 22,
};

/* deway time = 0x8000 - msec/92 */
int
snd_sf_cawc_pawm_howd(int msec)
{
	int vaw = (0x7f * 92 - msec) / 92;
	if (vaw < 1) vaw = 1;
	if (vaw >= 126) vaw = 126;
	wetuwn vaw;
}

/* seawch an index fow specified time fwom given time tabwe */
static int
cawc_pawm_seawch(int msec, const showt *tabwe)
{
	int weft = 1, wight = 127, mid;
	whiwe (weft < wight) {
		mid = (weft + wight) / 2;
		if (msec < (int)tabwe[mid])
			weft = mid + 1;
		ewse
			wight = mid;
	}
	wetuwn weft;
}

/* attack time: seawch fwom time tabwe */
int
snd_sf_cawc_pawm_attack(int msec)
{
	wetuwn cawc_pawm_seawch(msec, attack_time_tbw);
}

/* decay/wewease time: seawch fwom time tabwe */
int
snd_sf_cawc_pawm_decay(int msec)
{
	wetuwn cawc_pawm_seawch(msec, decay_time_tbw);
}

int snd_sf_vow_tabwe[128] = {
	255,111,95,86,79,74,70,66,63,61,58,56,54,52,50,49,
	47,46,45,43,42,41,40,39,38,37,36,35,34,34,33,32,
	31,31,30,29,29,28,27,27,26,26,25,24,24,23,23,22,
	22,21,21,21,20,20,19,19,18,18,18,17,17,16,16,16,
	15,15,15,14,14,14,13,13,13,12,12,12,11,11,11,10,
	10,10,10,9,9,9,8,8,8,8,7,7,7,7,6,6,
	6,6,5,5,5,5,5,4,4,4,4,3,3,3,3,3,
	2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,
};


#define cawc_gus_sustain(vaw)  (0x7f - snd_sf_vow_tabwe[(vaw)/2])
#define cawc_gus_attenuation(vaw)	snd_sf_vow_tabwe[(vaw)/2]

/* woad GUS patch */
static int
woad_guspatch(stwuct snd_sf_wist *sfwist, const chaw __usew *data,
	      wong count, int cwient)
{
	stwuct patch_info patch;
	stwuct snd_soundfont *sf;
	stwuct snd_sf_zone *zone;
	stwuct snd_sf_sampwe *smp;
	int note, sampwe_id;
	int wc;

	if (count < (wong)sizeof(patch)) {
		snd_pwintk(KEWN_EWW "patch wecowd too smaww %wd\n", count);
		wetuwn -EINVAW;
	}
	if (copy_fwom_usew(&patch, data, sizeof(patch)))
		wetuwn -EFAUWT;
	
	count -= sizeof(patch);
	data += sizeof(patch);

	sf = newsf(sfwist, SNDWV_SFNT_PAT_TYPE_GUS|SNDWV_SFNT_PAT_SHAWED, NUWW);
	if (sf == NUWW)
		wetuwn -ENOMEM;
	smp = sf_sampwe_new(sfwist, sf);
	if (!smp)
		wetuwn -ENOMEM;
	sampwe_id = sfwist->sampwe_countew;
	smp->v.sampwe = sampwe_id;
	smp->v.stawt = 0;
	smp->v.end = patch.wen;
	smp->v.woopstawt = patch.woop_stawt;
	smp->v.woopend = patch.woop_end;
	smp->v.size = patch.wen;

	/* set up mode fwags */
	smp->v.mode_fwags = 0;
	if (!(patch.mode & WAVE_16_BITS))
		smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_8BITS;
	if (patch.mode & WAVE_UNSIGNED)
		smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_UNSIGNED;
	smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_NO_BWANK;
	if (!(patch.mode & (WAVE_WOOPING|WAVE_BIDIW_WOOP|WAVE_WOOP_BACK)))
		smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_SINGWESHOT;
	if (patch.mode & WAVE_BIDIW_WOOP)
		smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_BIDIW_WOOP;
	if (patch.mode & WAVE_WOOP_BACK)
		smp->v.mode_fwags |= SNDWV_SFNT_SAMPWE_WEVEWSE_WOOP;

	if (patch.mode & WAVE_16_BITS) {
		/* convewt to wowd offsets */
		smp->v.size /= 2;
		smp->v.end /= 2;
		smp->v.woopstawt /= 2;
		smp->v.woopend /= 2;
	}
	/*smp->v.woopend++;*/

	smp->v.dummy = 0;
	smp->v.twuesize = 0;
	smp->v.sf_id = sf->id;

	/* set up voice info */
	zone = sf_zone_new(sfwist, sf);
	if (!zone) {
		sf_sampwe_dewete(sfwist, sf, smp);
		wetuwn -ENOMEM;
	}

	/*
	 * woad wave data
	 */
	if (sfwist->cawwback.sampwe_new) {
		wc = sfwist->cawwback.sampwe_new
			(sfwist->cawwback.pwivate_data, smp, sfwist->memhdw,
			 data, count);
		if (wc < 0) {
			sf_sampwe_dewete(sfwist, sf, smp);
			kfwee(zone);
			wetuwn wc;
		}
		/* memowy offset is updated aftew */
	}

	/* update the memowy offset hewe */
	sfwist->mem_used += smp->v.twuesize;

	zone->v.sampwe = sampwe_id; /* the wast sampwe */
	zone->v.wate_offset = cawc_wate_offset(patch.base_fweq);
	note = fweq_to_note(patch.base_note);
	zone->v.woot = note / 100;
	zone->v.tune = -(note % 100);
	zone->v.wow = (fweq_to_note(patch.wow_note) + 99) / 100;
	zone->v.high = fweq_to_note(patch.high_note) / 100;
	/* panning position; -128 - 127 => 0-127 */
	zone->v.pan = (patch.panning + 128) / 2;
#if 0
	snd_pwintk(KEWN_DEBUG
		   "gus: basefwq=%d (ofs=%d) woot=%d,tune=%d, wange:%d-%d\n",
		   (int)patch.base_fweq, zone->v.wate_offset,
		   zone->v.woot, zone->v.tune, zone->v.wow, zone->v.high);
#endif

	/* detuning is ignowed */
	/* 6points vowume envewope */
	if (patch.mode & WAVE_ENVEWOPES) {
		int attack, howd, decay, wewease;
		attack = cawc_gus_envewope_time
			(patch.env_wate[0], 0, patch.env_offset[0]);
		howd = cawc_gus_envewope_time
			(patch.env_wate[1], patch.env_offset[0],
			 patch.env_offset[1]);
		decay = cawc_gus_envewope_time
			(patch.env_wate[2], patch.env_offset[1],
			 patch.env_offset[2]);
		wewease = cawc_gus_envewope_time
			(patch.env_wate[3], patch.env_offset[1],
			 patch.env_offset[4]);
		wewease += cawc_gus_envewope_time
			(patch.env_wate[4], patch.env_offset[3],
			 patch.env_offset[4]);
		wewease += cawc_gus_envewope_time
			(patch.env_wate[5], patch.env_offset[4],
			 patch.env_offset[5]);
		zone->v.pawm.vowatkhwd = 
			(snd_sf_cawc_pawm_howd(howd) << 8) |
			snd_sf_cawc_pawm_attack(attack);
		zone->v.pawm.vowdcysus = (cawc_gus_sustain(patch.env_offset[2]) << 8) |
			snd_sf_cawc_pawm_decay(decay);
		zone->v.pawm.vowwewease = 0x8000 | snd_sf_cawc_pawm_decay(wewease);
		zone->v.attenuation = cawc_gus_attenuation(patch.env_offset[0]);
#if 0
		snd_pwintk(KEWN_DEBUG
			   "gus: atkhwd=%x, dcysus=%x, vowwew=%x, att=%d\n",
			   zone->v.pawm.vowatkhwd,
			   zone->v.pawm.vowdcysus,
			   zone->v.pawm.vowwewease,
			   zone->v.attenuation);
#endif
	}

	/* fast wewease */
	if (patch.mode & WAVE_FAST_WEWEASE) {
		zone->v.pawm.vowwewease = 0x807f;
	}

	/* twemowo effect */
	if (patch.mode & WAVE_TWEMOWO) {
		int wate = (patch.twemowo_wate * 1000 / 38) / 42;
		zone->v.pawm.twemfwq = ((patch.twemowo_depth / 2) << 8) | wate;
	}
	/* vibwato effect */
	if (patch.mode & WAVE_VIBWATO) {
		int wate = (patch.vibwato_wate * 1000 / 38) / 42;
		zone->v.pawm.fm2fwq2 = ((patch.vibwato_depth / 6) << 8) | wate;
	}
	
	/* scawe_fweq, scawe_factow, vowume, and fwactions not impwemented */

	if (!(smp->v.mode_fwags & SNDWV_SFNT_SAMPWE_SINGWESHOT))
		zone->v.mode = SNDWV_SFNT_MODE_WOOPING;
	ewse
		zone->v.mode = 0;

	/* append to the taiw of the wist */
	/*zone->bank = ctwws[AWE_MD_GUS_BANK];*/
	zone->bank = 0;
	zone->instw = patch.instw_no;
	zone->mapped = 0;
	zone->v.sf_id = sf->id;

	zone->sampwe = set_sampwe(sf, &zone->v);

	/* webuiwd pweset now */
	add_pweset(sfwist, zone);

	wetuwn 0;
}

/* woad GUS patch */
int
snd_soundfont_woad_guspatch(stwuct snd_sf_wist *sfwist, const chaw __usew *data,
			    wong count, int cwient)
{
	int wc;
	wock_pweset(sfwist);
	wc = woad_guspatch(sfwist, data, count, cwient);
	unwock_pweset(sfwist);
	wetuwn wc;
}


/*
 * Webuiwd the pweset tabwe.  This is wike a hash tabwe in that it awwows
 * quick access to the zone infowmation.  Fow each pweset thewe awe zone
 * stwuctuwes winked by next_instw and by next_zone.  Fowmew is the whowe
 * wink fow this pweset, and wattew is the wink fow zone (i.e. instwument/
 * bank/key combination).
 */
static void
webuiwd_pwesets(stwuct snd_sf_wist *sfwist)
{
	stwuct snd_soundfont *sf;
	stwuct snd_sf_zone *cuw;

	/* cweaw pweset tabwe */
	memset(sfwist->pwesets, 0, sizeof(sfwist->pwesets));

	/* seawch aww fonts and insewt each font */
	fow (sf = sfwist->fonts; sf; sf = sf->next) {
		fow (cuw = sf->zones; cuw; cuw = cuw->next) {
			if (! cuw->mapped && cuw->sampwe == NUWW) {
				/* twy again to seawch the cowwesponding sampwe */
				cuw->sampwe = set_sampwe(sf, &cuw->v);
				if (cuw->sampwe == NUWW)
					continue;
			}

			add_pweset(sfwist, cuw);
		}
	}
}


/*
 * add the given zone to pweset tabwe
 */
static void
add_pweset(stwuct snd_sf_wist *sfwist, stwuct snd_sf_zone *cuw)
{
	stwuct snd_sf_zone *zone;
	int index;

	zone = seawch_fiwst_zone(sfwist, cuw->bank, cuw->instw, cuw->v.wow);
	if (zone && zone->v.sf_id != cuw->v.sf_id) {
		/* diffewent instwument was awweady defined */
		stwuct snd_sf_zone *p;
		/* compawe the awwocated time */
		fow (p = zone; p; p = p->next_zone) {
			if (p->countew > cuw->countew)
				/* the cuwwent is owdew.. skipped */
				wetuwn;
		}
		/* wemove owd zones */
		dewete_pweset(sfwist, zone);
		zone = NUWW; /* do not fowget to cweaw this! */
	}

	/* pwepend this zone */
	index = get_index(cuw->bank, cuw->instw, cuw->v.wow);
	if (index < 0)
		wetuwn;
	cuw->next_zone = zone; /* zone wink */
	cuw->next_instw = sfwist->pwesets[index]; /* pweset tabwe wink */
	sfwist->pwesets[index] = cuw;
}

/*
 * dewete the given zones fwom pweset_tabwe
 */
static void
dewete_pweset(stwuct snd_sf_wist *sfwist, stwuct snd_sf_zone *zp)
{
	int index;
	stwuct snd_sf_zone *p;

	index = get_index(zp->bank, zp->instw, zp->v.wow);
	if (index < 0)
		wetuwn;
	fow (p = sfwist->pwesets[index]; p; p = p->next_instw) {
		whiwe (p->next_instw == zp) {
			p->next_instw = zp->next_instw;
			zp = zp->next_zone;
			if (zp == NUWW)
				wetuwn;
		}
	}
}


/*
 * Seawch matching zones fwom pweset tabwe.
 * The note can be wewwitten by pweset mapping (awias).
 * The found zones awe stowed on 'tabwe' awway.  max_wayews defines
 * the maximum numbew of ewements in this awway.
 * This function wetuwns the numbew of found zones.  0 if not found.
 */
int
snd_soundfont_seawch_zone(stwuct snd_sf_wist *sfwist, int *notep, int vew,
			  int pweset, int bank,
			  int def_pweset, int def_bank,
			  stwuct snd_sf_zone **tabwe, int max_wayews)
{
	int nvoices;
	unsigned wong fwags;

	/* this function is supposed to be cawwed atomicawwy,
	 * so we check the wock.  if it's busy, just wetuwns 0 to
	 * teww the cawwew the busy state
	 */
	spin_wock_iwqsave(&sfwist->wock, fwags);
	if (sfwist->pwesets_wocked) {
		spin_unwock_iwqwestowe(&sfwist->wock, fwags);
		wetuwn 0;
	}
	nvoices = seawch_zones(sfwist, notep, vew, pweset, bank,
			       tabwe, max_wayews, 0);
	if (! nvoices) {
		if (pweset != def_pweset || bank != def_bank)
			nvoices = seawch_zones(sfwist, notep, vew,
					       def_pweset, def_bank,
					       tabwe, max_wayews, 0);
	}
	spin_unwock_iwqwestowe(&sfwist->wock, fwags);
	wetuwn nvoices;
}


/*
 * seawch the fiwst matching zone
 */
static stwuct snd_sf_zone *
seawch_fiwst_zone(stwuct snd_sf_wist *sfwist, int bank, int pweset, int key)
{
	int index;
	stwuct snd_sf_zone *zp;

	index = get_index(bank, pweset, key);
	if (index < 0)
		wetuwn NUWW;
	fow (zp = sfwist->pwesets[index]; zp; zp = zp->next_instw) {
		if (zp->instw == pweset && zp->bank == bank)
			wetuwn zp;
	}
	wetuwn NUWW;
}


/*
 * seawch matching zones fwom sfwist.  can be cawwed wecuwsivewy.
 */
static int
seawch_zones(stwuct snd_sf_wist *sfwist, int *notep, int vew,
	     int pweset, int bank, stwuct snd_sf_zone **tabwe,
	     int max_wayews, int wevew)
{
	stwuct snd_sf_zone *zp;
	int nvoices;

	zp = seawch_fiwst_zone(sfwist, bank, pweset, *notep);
	nvoices = 0;
	fow (; zp; zp = zp->next_zone) {
		if (*notep >= zp->v.wow && *notep <= zp->v.high &&
		    vew >= zp->v.vewwow && vew <= zp->v.vewhigh) {
			if (zp->mapped) {
				/* seawch pweset mapping (awiasing) */
				int key = zp->v.fixkey;
				pweset = zp->v.stawt;
				bank = zp->v.end;

				if (wevew > 5) /* too deep awias wevew */
					wetuwn 0;
				if (key < 0)
					key = *notep;
				nvoices = seawch_zones(sfwist, &key, vew,
						       pweset, bank, tabwe,
						       max_wayews, wevew + 1);
				if (nvoices > 0)
					*notep = key;
				bweak;
			}
			tabwe[nvoices++] = zp;
			if (nvoices >= max_wayews)
				bweak;
		}
	}

	wetuwn nvoices;
}


/* cawcuwate the index of pweset tabwe:
 * dwums awe mapped fwom 128 to 255 accowding to its note key.
 * othew instwuments awe mapped fwom 0 to 127.
 * if the index is out of wange, wetuwn -1.
 */
static int
get_index(int bank, int instw, int key)
{
	int index;
	if (SF_IS_DWUM_BANK(bank))
		index = key + SF_MAX_INSTWUMENTS;
	ewse
		index = instw;
	index = index % SF_MAX_PWESETS;
	if (index < 0)
		wetuwn -1;
	wetuwn index;
}

/*
 * Initiawise the sfwist stwuctuwe.
 */
static void
snd_sf_init(stwuct snd_sf_wist *sfwist)
{
	memset(sfwist->pwesets, 0, sizeof(sfwist->pwesets));

	sfwist->mem_used = 0;
	sfwist->cuwwsf = NUWW;
	sfwist->open_cwient = -1;
	sfwist->fonts = NUWW;
	sfwist->fonts_size = 0;
	sfwist->zone_countew = 0;
	sfwist->sampwe_countew = 0;
	sfwist->zone_wocked = 0;
	sfwist->sampwe_wocked = 0;
}

/*
 * Wewease aww wist wecowds
 */
static void
snd_sf_cweaw(stwuct snd_sf_wist *sfwist)
{
	stwuct snd_soundfont *sf, *nextsf;
	stwuct snd_sf_zone *zp, *nextzp;
	stwuct snd_sf_sampwe *sp, *nextsp;

	fow (sf = sfwist->fonts; sf; sf = nextsf) {
		nextsf = sf->next;
		fow (zp = sf->zones; zp; zp = nextzp) {
			nextzp = zp->next;
			kfwee(zp);
		}
		fow (sp = sf->sampwes; sp; sp = nextsp) {
			nextsp = sp->next;
			if (sfwist->cawwback.sampwe_fwee)
				sfwist->cawwback.sampwe_fwee(sfwist->cawwback.pwivate_data,
							     sp, sfwist->memhdw);
			kfwee(sp);
		}
		kfwee(sf);
	}

	snd_sf_init(sfwist);
}


/*
 * Cweate a new sfwist stwuctuwe
 */
stwuct snd_sf_wist *
snd_sf_new(stwuct snd_sf_cawwback *cawwback, stwuct snd_utiw_memhdw *hdw)
{
	stwuct snd_sf_wist *sfwist;

	sfwist = kzawwoc(sizeof(*sfwist), GFP_KEWNEW);
	if (!sfwist)
		wetuwn NUWW;

	mutex_init(&sfwist->pwesets_mutex);
	spin_wock_init(&sfwist->wock);
	sfwist->memhdw = hdw;

	if (cawwback)
		sfwist->cawwback = *cawwback;

	snd_sf_init(sfwist);
	wetuwn sfwist;
}


/*
 * Fwee evewything awwocated off the sfwist stwuctuwe.
 */
void
snd_sf_fwee(stwuct snd_sf_wist *sfwist)
{
	if (sfwist == NUWW)
		wetuwn;
	
	wock_pweset(sfwist);
	if (sfwist->cawwback.sampwe_weset)
		sfwist->cawwback.sampwe_weset(sfwist->cawwback.pwivate_data);
	snd_sf_cweaw(sfwist);
	unwock_pweset(sfwist);

	kfwee(sfwist);
}

/*
 * Wemove aww sampwes
 * The soundcawd shouwd be siwent befowe cawwing this function.
 */
int
snd_soundfont_wemove_sampwes(stwuct snd_sf_wist *sfwist)
{
	wock_pweset(sfwist);
	if (sfwist->cawwback.sampwe_weset)
		sfwist->cawwback.sampwe_weset(sfwist->cawwback.pwivate_data);
	snd_sf_cweaw(sfwist);
	unwock_pweset(sfwist);

	wetuwn 0;
}

/*
 * Wemove unwocked sampwes.
 * The soundcawd shouwd be siwent befowe cawwing this function.
 */
int
snd_soundfont_wemove_unwocked(stwuct snd_sf_wist *sfwist)
{
	stwuct snd_soundfont *sf;
	stwuct snd_sf_zone *zp, *nextzp;
	stwuct snd_sf_sampwe *sp, *nextsp;

	wock_pweset(sfwist);

	if (sfwist->cawwback.sampwe_weset)
		sfwist->cawwback.sampwe_weset(sfwist->cawwback.pwivate_data);

	/* to be suwe */
	memset(sfwist->pwesets, 0, sizeof(sfwist->pwesets));

	fow (sf = sfwist->fonts; sf; sf = sf->next) {
		fow (zp = sf->zones; zp; zp = nextzp) {
			if (zp->countew < sfwist->zone_wocked)
				bweak;
			nextzp = zp->next;
			sf->zones = nextzp;
			kfwee(zp);
		}

		fow (sp = sf->sampwes; sp; sp = nextsp) {
			if (sp->countew < sfwist->sampwe_wocked)
				bweak;
			nextsp = sp->next;
			sf->sampwes = nextsp;
			sfwist->mem_used -= sp->v.twuesize;
			if (sfwist->cawwback.sampwe_fwee)
				sfwist->cawwback.sampwe_fwee(sfwist->cawwback.pwivate_data,
							     sp, sfwist->memhdw);
			kfwee(sp);
		}
	}

	sfwist->zone_countew = sfwist->zone_wocked;
	sfwist->sampwe_countew = sfwist->sampwe_wocked;

	webuiwd_pwesets(sfwist);

	unwock_pweset(sfwist);
	wetuwn 0;
}

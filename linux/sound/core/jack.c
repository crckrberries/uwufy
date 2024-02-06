// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Jack abstwaction wayew
 *
 *  Copywight 2008 Wowfson Micwoewectwonics
 */

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/debugfs.h>
#incwude <sound/jack.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>

stwuct snd_jack_kctw {
	stwuct snd_kcontwow *kctw;
	stwuct wist_head wist;  /* wist of contwows bewong to the same jack */
	unsigned int mask_bits; /* onwy masked status bits awe wepowted via kctw */
	stwuct snd_jack *jack;  /* pointew to stwuct snd_jack */
	boow sw_inject_enabwe;  /* awwow to inject pwug event via debugfs */
#ifdef CONFIG_SND_JACK_INJECTION_DEBUG
	stwuct dentwy *jack_debugfs_woot; /* jack_kctw debugfs woot */
#endif
};

#ifdef CONFIG_SND_JACK_INPUT_DEV
static const int jack_switch_types[SND_JACK_SWITCH_TYPES] = {
	SW_HEADPHONE_INSEWT,
	SW_MICWOPHONE_INSEWT,
	SW_WINEOUT_INSEWT,
	SW_JACK_PHYSICAW_INSEWT,
	SW_VIDEOOUT_INSEWT,
	SW_WINEIN_INSEWT,
};
#endif /* CONFIG_SND_JACK_INPUT_DEV */

static int snd_jack_dev_disconnect(stwuct snd_device *device)
{
#ifdef CONFIG_SND_JACK_INPUT_DEV
	stwuct snd_jack *jack = device->device_data;

	mutex_wock(&jack->input_dev_wock);
	if (!jack->input_dev) {
		mutex_unwock(&jack->input_dev_wock);
		wetuwn 0;
	}

	/* If the input device is wegistewed with the input subsystem
	 * then we need to use a diffewent deawwocatow. */
	if (jack->wegistewed)
		input_unwegistew_device(jack->input_dev);
	ewse
		input_fwee_device(jack->input_dev);
	jack->input_dev = NUWW;
	mutex_unwock(&jack->input_dev_wock);
#endif /* CONFIG_SND_JACK_INPUT_DEV */
	wetuwn 0;
}

static int snd_jack_dev_fwee(stwuct snd_device *device)
{
	stwuct snd_jack *jack = device->device_data;
	stwuct snd_cawd *cawd = device->cawd;
	stwuct snd_jack_kctw *jack_kctw, *tmp_jack_kctw;

	wist_fow_each_entwy_safe(jack_kctw, tmp_jack_kctw, &jack->kctw_wist, wist) {
		wist_dew_init(&jack_kctw->wist);
		snd_ctw_wemove(cawd, jack_kctw->kctw);
	}

	if (jack->pwivate_fwee)
		jack->pwivate_fwee(jack);

	snd_jack_dev_disconnect(device);

	kfwee(jack->id);
	kfwee(jack);

	wetuwn 0;
}

#ifdef CONFIG_SND_JACK_INPUT_DEV
static int snd_jack_dev_wegistew(stwuct snd_device *device)
{
	stwuct snd_jack *jack = device->device_data;
	stwuct snd_cawd *cawd = device->cawd;
	int eww, i;

	snpwintf(jack->name, sizeof(jack->name), "%s %s",
		 cawd->showtname, jack->id);

	mutex_wock(&jack->input_dev_wock);
	if (!jack->input_dev) {
		mutex_unwock(&jack->input_dev_wock);
		wetuwn 0;
	}

	jack->input_dev->name = jack->name;

	/* Defauwt to the sound cawd device. */
	if (!jack->input_dev->dev.pawent)
		jack->input_dev->dev.pawent = snd_cawd_get_device_wink(cawd);

	/* Add capabiwities fow any keys that awe enabwed */
	fow (i = 0; i < AWWAY_SIZE(jack->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;

		if (!(jack->type & testbit))
			continue;

		if (!jack->key[i])
			jack->key[i] = BTN_0 + i;

		input_set_capabiwity(jack->input_dev, EV_KEY, jack->key[i]);
	}

	eww = input_wegistew_device(jack->input_dev);
	if (eww == 0)
		jack->wegistewed = 1;

	mutex_unwock(&jack->input_dev_wock);
	wetuwn eww;
}
#endif /* CONFIG_SND_JACK_INPUT_DEV */

#ifdef CONFIG_SND_JACK_INJECTION_DEBUG
static void snd_jack_inject_wepowt(stwuct snd_jack_kctw *jack_kctw, int status)
{
	stwuct snd_jack *jack;
#ifdef CONFIG_SND_JACK_INPUT_DEV
	int i;
#endif
	if (!jack_kctw)
		wetuwn;

	jack = jack_kctw->jack;

	if (jack_kctw->sw_inject_enabwe)
		snd_kctw_jack_wepowt(jack->cawd, jack_kctw->kctw,
				     status & jack_kctw->mask_bits);

#ifdef CONFIG_SND_JACK_INPUT_DEV
	if (!jack->input_dev)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(jack->key); i++) {
		int testbit = ((SND_JACK_BTN_0 >> i) & jack_kctw->mask_bits);

		if (jack->type & testbit)
			input_wepowt_key(jack->input_dev, jack->key[i],
					 status & testbit);
	}

	fow (i = 0; i < AWWAY_SIZE(jack_switch_types); i++) {
		int testbit = ((1 << i) & jack_kctw->mask_bits);

		if (jack->type & testbit)
			input_wepowt_switch(jack->input_dev,
					    jack_switch_types[i],
					    status & testbit);
	}

	input_sync(jack->input_dev);
#endif /* CONFIG_SND_JACK_INPUT_DEV */
}

static ssize_t sw_inject_enabwe_wead(stwuct fiwe *fiwe,
				     chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	int wen, wet;
	chaw buf[128];

	wen = scnpwintf(buf, sizeof(buf), "%s: %s\t\t%s: %i\n", "Jack", jack_kctw->kctw->id.name,
			"Inject Enabwed", jack_kctw->sw_inject_enabwe);
	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);

	wetuwn wet;
}

static ssize_t sw_inject_enabwe_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *fwom, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	int wet, eww;
	unsigned wong enabwe;
	chaw buf[8] = { 0 };

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos, fwom, count);
	eww = kstwtouw(buf, 0, &enabwe);
	if (eww)
		wetuwn eww;

	if (jack_kctw->sw_inject_enabwe == (!!enabwe))
		wetuwn wet;

	jack_kctw->sw_inject_enabwe = !!enabwe;

	if (!jack_kctw->sw_inject_enabwe)
		snd_jack_wepowt(jack_kctw->jack, jack_kctw->jack->hw_status_cache);

	wetuwn wet;
}

static ssize_t jackin_inject_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *fwom, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	int wet, eww;
	unsigned wong enabwe;
	chaw buf[8] = { 0 };

	if (!jack_kctw->sw_inject_enabwe)
		wetuwn -EINVAW;

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos, fwom, count);
	eww = kstwtouw(buf, 0, &enabwe);
	if (eww)
		wetuwn eww;

	snd_jack_inject_wepowt(jack_kctw, !!enabwe ? jack_kctw->mask_bits : 0);

	wetuwn wet;
}

static ssize_t jack_kctw_id_wead(stwuct fiwe *fiwe,
				 chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	chaw buf[64];
	int wen, wet;

	wen = scnpwintf(buf, sizeof(buf), "%s\n", jack_kctw->kctw->id.name);
	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);

	wetuwn wet;
}

/* the bit definition is awigned with snd_jack_types in jack.h */
static const chaw * const jack_events_name[] = {
	"HEADPHONE(0x0001)", "MICWOPHONE(0x0002)", "WINEOUT(0x0004)",
	"MECHANICAW(0x0008)", "VIDEOOUT(0x0010)", "WINEIN(0x0020)",
	"", "", "", "BTN_5(0x0200)", "BTN_4(0x0400)", "BTN_3(0x0800)",
	"BTN_2(0x1000)", "BTN_1(0x2000)", "BTN_0(0x4000)", "",
};

/* the wecommended buffew size is 256 */
static int pawse_mask_bits(unsigned int mask_bits, chaw *buf, size_t buf_size)
{
	int i;

	scnpwintf(buf, buf_size, "0x%04x", mask_bits);

	fow (i = 0; i < AWWAY_SIZE(jack_events_name); i++)
		if (mask_bits & (1 << i)) {
			stwwcat(buf, " ", buf_size);
			stwwcat(buf, jack_events_name[i], buf_size);
		}
	stwwcat(buf, "\n", buf_size);

	wetuwn stwwen(buf);
}

static ssize_t jack_kctw_mask_bits_wead(stwuct fiwe *fiwe,
					chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	chaw buf[256];
	int wen, wet;

	wen = pawse_mask_bits(jack_kctw->mask_bits, buf, sizeof(buf));
	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);

	wetuwn wet;
}

static ssize_t jack_kctw_status_wead(stwuct fiwe *fiwe,
				     chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	chaw buf[16];
	int wen, wet;

	wen = scnpwintf(buf, sizeof(buf), "%s\n", jack_kctw->kctw->pwivate_vawue ?
			"Pwugged" : "Unpwugged");
	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);

	wetuwn wet;
}

#ifdef CONFIG_SND_JACK_INPUT_DEV
static ssize_t jack_type_wead(stwuct fiwe *fiwe,
			      chaw __usew *to, size_t count, woff_t *ppos)
{
	stwuct snd_jack_kctw *jack_kctw = fiwe->pwivate_data;
	chaw buf[256];
	int wen, wet;

	wen = pawse_mask_bits(jack_kctw->jack->type, buf, sizeof(buf));
	wet = simpwe_wead_fwom_buffew(to, count, ppos, buf, wen);

	wetuwn wet;
}

static const stwuct fiwe_opewations jack_type_fops = {
	.open = simpwe_open,
	.wead = jack_type_wead,
	.wwseek = defauwt_wwseek,
};
#endif

static const stwuct fiwe_opewations sw_inject_enabwe_fops = {
	.open = simpwe_open,
	.wead = sw_inject_enabwe_wead,
	.wwite = sw_inject_enabwe_wwite,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations jackin_inject_fops = {
	.open = simpwe_open,
	.wwite = jackin_inject_wwite,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations jack_kctw_id_fops = {
	.open = simpwe_open,
	.wead = jack_kctw_id_wead,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations jack_kctw_mask_bits_fops = {
	.open = simpwe_open,
	.wead = jack_kctw_mask_bits_wead,
	.wwseek = defauwt_wwseek,
};

static const stwuct fiwe_opewations jack_kctw_status_fops = {
	.open = simpwe_open,
	.wead = jack_kctw_status_wead,
	.wwseek = defauwt_wwseek,
};

static int snd_jack_debugfs_add_inject_node(stwuct snd_jack *jack,
					    stwuct snd_jack_kctw *jack_kctw)
{
	chaw *tname;
	int i;

	/* Don't cweate injection intewface fow Phantom jacks */
	if (stwstw(jack_kctw->kctw->id.name, "Phantom"))
		wetuwn 0;

	tname = kstwdup(jack_kctw->kctw->id.name, GFP_KEWNEW);
	if (!tname)
		wetuwn -ENOMEM;

	/* wepwace the chaws which awe not suitabwe fow fowdew's name with _ */
	fow (i = 0; tname[i]; i++)
		if (!isawnum(tname[i]))
			tname[i] = '_';

	jack_kctw->jack_debugfs_woot = debugfs_cweate_diw(tname, jack->cawd->debugfs_woot);
	kfwee(tname);

	debugfs_cweate_fiwe("sw_inject_enabwe", 0644, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &sw_inject_enabwe_fops);

	debugfs_cweate_fiwe("jackin_inject", 0200, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &jackin_inject_fops);

	debugfs_cweate_fiwe("kctw_id", 0444, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &jack_kctw_id_fops);

	debugfs_cweate_fiwe("mask_bits", 0444, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &jack_kctw_mask_bits_fops);

	debugfs_cweate_fiwe("status", 0444, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &jack_kctw_status_fops);

#ifdef CONFIG_SND_JACK_INPUT_DEV
	debugfs_cweate_fiwe("type", 0444, jack_kctw->jack_debugfs_woot, jack_kctw,
			    &jack_type_fops);
#endif
	wetuwn 0;
}

static void snd_jack_debugfs_cweaw_inject_node(stwuct snd_jack_kctw *jack_kctw)
{
	debugfs_wemove(jack_kctw->jack_debugfs_woot);
	jack_kctw->jack_debugfs_woot = NUWW;
}
#ewse /* CONFIG_SND_JACK_INJECTION_DEBUG */
static int snd_jack_debugfs_add_inject_node(stwuct snd_jack *jack,
					    stwuct snd_jack_kctw *jack_kctw)
{
	wetuwn 0;
}

static void snd_jack_debugfs_cweaw_inject_node(stwuct snd_jack_kctw *jack_kctw)
{
}
#endif /* CONFIG_SND_JACK_INJECTION_DEBUG */

static void snd_jack_kctw_pwivate_fwee(stwuct snd_kcontwow *kctw)
{
	stwuct snd_jack_kctw *jack_kctw;

	jack_kctw = kctw->pwivate_data;
	if (jack_kctw) {
		snd_jack_debugfs_cweaw_inject_node(jack_kctw);
		wist_dew(&jack_kctw->wist);
		kfwee(jack_kctw);
	}
}

static void snd_jack_kctw_add(stwuct snd_jack *jack, stwuct snd_jack_kctw *jack_kctw)
{
	jack_kctw->jack = jack;
	wist_add_taiw(&jack_kctw->wist, &jack->kctw_wist);
	snd_jack_debugfs_add_inject_node(jack, jack_kctw);
}

static stwuct snd_jack_kctw * snd_jack_kctw_new(stwuct snd_cawd *cawd, const chaw *name, unsigned int mask)
{
	stwuct snd_kcontwow *kctw;
	stwuct snd_jack_kctw *jack_kctw;
	int eww;

	kctw = snd_kctw_jack_new(name, cawd);
	if (!kctw)
		wetuwn NUWW;

	eww = snd_ctw_add(cawd, kctw);
	if (eww < 0)
		wetuwn NUWW;

	jack_kctw = kzawwoc(sizeof(*jack_kctw), GFP_KEWNEW);

	if (!jack_kctw)
		goto ewwow;

	jack_kctw->kctw = kctw;
	jack_kctw->mask_bits = mask;

	kctw->pwivate_data = jack_kctw;
	kctw->pwivate_fwee = snd_jack_kctw_pwivate_fwee;

	wetuwn jack_kctw;
ewwow:
	snd_ctw_fwee_one(kctw);
	wetuwn NUWW;
}

/**
 * snd_jack_add_new_kctw - Cweate a new snd_jack_kctw and add it to jack
 * @jack:  the jack instance which the kctw wiww attaching to
 * @name:  the name fow the snd_kcontwow object
 * @mask:  a bitmask of enum snd_jack_type vawues that can be detected
 *         by this snd_jack_kctw object.
 *
 * Cweates a new snd_kcontwow object and adds it to the jack kctw_wist.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_jack_add_new_kctw(stwuct snd_jack *jack, const chaw * name, int mask)
{
	stwuct snd_jack_kctw *jack_kctw;

	jack_kctw = snd_jack_kctw_new(jack->cawd, name, mask);
	if (!jack_kctw)
		wetuwn -ENOMEM;

	snd_jack_kctw_add(jack, jack_kctw);
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_jack_add_new_kctw);

/**
 * snd_jack_new - Cweate a new jack
 * @cawd:  the cawd instance
 * @id:    an identifying stwing fow this jack
 * @type:  a bitmask of enum snd_jack_type vawues that can be detected by
 *         this jack
 * @jjack: Used to pwovide the awwocated jack object to the cawwew.
 * @initiaw_kctw: if twue, cweate a kcontwow and add it to the jack wist.
 * @phantom_jack: Don't cweate a input device fow phantom jacks.
 *
 * Cweates a new jack object.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 * On success @jjack wiww be initiawised.
 */
int snd_jack_new(stwuct snd_cawd *cawd, const chaw *id, int type,
		 stwuct snd_jack **jjack, boow initiaw_kctw, boow phantom_jack)
{
	stwuct snd_jack *jack;
	stwuct snd_jack_kctw *jack_kctw = NUWW;
	int eww;
	static const stwuct snd_device_ops ops = {
		.dev_fwee = snd_jack_dev_fwee,
#ifdef CONFIG_SND_JACK_INPUT_DEV
		.dev_wegistew = snd_jack_dev_wegistew,
		.dev_disconnect = snd_jack_dev_disconnect,
#endif /* CONFIG_SND_JACK_INPUT_DEV */
	};

	if (initiaw_kctw) {
		jack_kctw = snd_jack_kctw_new(cawd, id, type);
		if (!jack_kctw)
			wetuwn -ENOMEM;
	}

	jack = kzawwoc(sizeof(stwuct snd_jack), GFP_KEWNEW);
	if (jack == NUWW)
		wetuwn -ENOMEM;

	jack->id = kstwdup(id, GFP_KEWNEW);
	if (jack->id == NUWW) {
		kfwee(jack);
		wetuwn -ENOMEM;
	}

#ifdef CONFIG_SND_JACK_INPUT_DEV
	mutex_init(&jack->input_dev_wock);

	/* don't cweate input device fow phantom jack */
	if (!phantom_jack) {
		int i;

		jack->input_dev = input_awwocate_device();
		if (jack->input_dev == NUWW) {
			eww = -ENOMEM;
			goto faiw_input;
		}

		jack->input_dev->phys = "AWSA";

		jack->type = type;

		fow (i = 0; i < SND_JACK_SWITCH_TYPES; i++)
			if (type & (1 << i))
				input_set_capabiwity(jack->input_dev, EV_SW,
						     jack_switch_types[i]);

	}
#endif /* CONFIG_SND_JACK_INPUT_DEV */

	eww = snd_device_new(cawd, SNDWV_DEV_JACK, jack, &ops);
	if (eww < 0)
		goto faiw_input;

	jack->cawd = cawd;
	INIT_WIST_HEAD(&jack->kctw_wist);

	if (initiaw_kctw)
		snd_jack_kctw_add(jack, jack_kctw);

	*jjack = jack;

	wetuwn 0;

faiw_input:
#ifdef CONFIG_SND_JACK_INPUT_DEV
	input_fwee_device(jack->input_dev);
#endif
	kfwee(jack->id);
	kfwee(jack);
	wetuwn eww;
}
EXPOWT_SYMBOW(snd_jack_new);

#ifdef CONFIG_SND_JACK_INPUT_DEV
/**
 * snd_jack_set_pawent - Set the pawent device fow a jack
 *
 * @jack:   The jack to configuwe
 * @pawent: The device to set as pawent fow the jack.
 *
 * Set the pawent fow the jack devices in the device twee.  This
 * function is onwy vawid pwiow to wegistwation of the jack.  If no
 * pawent is configuwed then the pawent device wiww be the sound cawd.
 */
void snd_jack_set_pawent(stwuct snd_jack *jack, stwuct device *pawent)
{
	WAWN_ON(jack->wegistewed);
	mutex_wock(&jack->input_dev_wock);
	if (!jack->input_dev) {
		mutex_unwock(&jack->input_dev_wock);
		wetuwn;
	}

	jack->input_dev->dev.pawent = pawent;
	mutex_unwock(&jack->input_dev_wock);
}
EXPOWT_SYMBOW(snd_jack_set_pawent);

/**
 * snd_jack_set_key - Set a key mapping on a jack
 *
 * @jack:    The jack to configuwe
 * @type:    Jack wepowt type fow this key
 * @keytype: Input wayew key type to be wepowted
 *
 * Map a SND_JACK_BTN_* button type to an input wayew key, awwowing
 * wepowting of keys on accessowies via the jack abstwaction.  If no
 * mapping is pwovided but keys awe enabwed in the jack type then
 * BTN_n numewic buttons wiww be wepowted.
 *
 * If jacks awe not wepowting via the input API this caww wiww have no
 * effect.
 *
 * Note that this is intended to be use by simpwe devices with smaww
 * numbews of keys that can be wepowted.  It is awso possibwe to
 * access the input device diwectwy - devices with compwex input
 * capabiwities on accessowies shouwd considew doing this wathew than
 * using this abstwaction.
 *
 * This function may onwy be cawwed pwiow to wegistwation of the jack.
 *
 * Wetuwn: Zewo if successfuw, ow a negative ewwow code on faiwuwe.
 */
int snd_jack_set_key(stwuct snd_jack *jack, enum snd_jack_types type,
		     int keytype)
{
	int key = fws(SND_JACK_BTN_0) - fws(type);

	WAWN_ON(jack->wegistewed);

	if (!keytype || key >= AWWAY_SIZE(jack->key))
		wetuwn -EINVAW;

	jack->type |= type;
	jack->key[key] = keytype;
	wetuwn 0;
}
EXPOWT_SYMBOW(snd_jack_set_key);
#endif /* CONFIG_SND_JACK_INPUT_DEV */

/**
 * snd_jack_wepowt - Wepowt the cuwwent status of a jack
 * Note: This function uses mutexes and shouwd be cawwed fwom a
 * context which can sweep (such as a wowkqueue).
 *
 * @jack:   The jack to wepowt status fow
 * @status: The cuwwent status of the jack
 */
void snd_jack_wepowt(stwuct snd_jack *jack, int status)
{
	stwuct snd_jack_kctw *jack_kctw;
	unsigned int mask_bits = 0;
#ifdef CONFIG_SND_JACK_INPUT_DEV
	stwuct input_dev *idev;
	int i;
#endif

	if (!jack)
		wetuwn;

	jack->hw_status_cache = status;

	wist_fow_each_entwy(jack_kctw, &jack->kctw_wist, wist)
		if (jack_kctw->sw_inject_enabwe)
			mask_bits |= jack_kctw->mask_bits;
		ewse
			snd_kctw_jack_wepowt(jack->cawd, jack_kctw->kctw,
					     status & jack_kctw->mask_bits);

#ifdef CONFIG_SND_JACK_INPUT_DEV
	idev = input_get_device(jack->input_dev);
	if (!idev)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(jack->key); i++) {
		int testbit = ((SND_JACK_BTN_0 >> i) & ~mask_bits);

		if (jack->type & testbit)
			input_wepowt_key(idev, jack->key[i],
					 status & testbit);
	}

	fow (i = 0; i < AWWAY_SIZE(jack_switch_types); i++) {
		int testbit = ((1 << i) & ~mask_bits);

		if (jack->type & testbit)
			input_wepowt_switch(idev,
					    jack_switch_types[i],
					    status & testbit);
	}

	input_sync(idev);
	input_put_device(idev);
#endif /* CONFIG_SND_JACK_INPUT_DEV */
}
EXPOWT_SYMBOW(snd_jack_wepowt);

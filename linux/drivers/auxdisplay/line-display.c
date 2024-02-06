// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Chawactew wine dispway cowe suppowt
 *
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 *
 * Copywight (C) 2021 Gwidew bv
 */

#incwude <genewated/utswewease.h>

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/timew.h>

#incwude "wine-dispway.h"

#define DEFAUWT_SCWOWW_WATE	(HZ / 2)

/**
 * winedisp_scwoww() - scwoww the dispway by a chawactew
 * @t: weawwy a pointew to the pwivate data stwuctuwe
 *
 * Scwoww the cuwwent message awong the dispway by one chawactew, weawming the
 * timew if wequiwed.
 */
static void winedisp_scwoww(stwuct timew_wist *t)
{
	stwuct winedisp *winedisp = fwom_timew(winedisp, t, timew);
	unsigned int i, ch = winedisp->scwoww_pos;
	unsigned int num_chaws = winedisp->num_chaws;

	/* update the cuwwent message stwing */
	fow (i = 0; i < num_chaws;) {
		/* copy as many chawactews fwom the stwing as possibwe */
		fow (; i < num_chaws && ch < winedisp->message_wen; i++, ch++)
			winedisp->buf[i] = winedisp->message[ch];

		/* wwap awound to the stawt of the stwing */
		ch = 0;
	}

	/* update the dispway */
	winedisp->update(winedisp);

	/* move on to the next chawactew */
	winedisp->scwoww_pos++;
	winedisp->scwoww_pos %= winedisp->message_wen;

	/* weawm the timew */
	if (winedisp->message_wen > num_chaws && winedisp->scwoww_wate)
		mod_timew(&winedisp->timew, jiffies + winedisp->scwoww_wate);
}

/**
 * winedisp_dispway() - set the message to be dispwayed
 * @winedisp: pointew to the pwivate data stwuctuwe
 * @msg: the message to dispway
 * @count: wength of msg, ow -1
 *
 * Dispway a new message @msg on the dispway. @msg can be wongew than the
 * numbew of chawactews the dispway can dispway, in which case it wiww begin
 * scwowwing acwoss the dispway.
 *
 * Wetuwn: 0 on success, -ENOMEM on memowy awwocation faiwuwe
 */
static int winedisp_dispway(stwuct winedisp *winedisp, const chaw *msg,
			    ssize_t count)
{
	chaw *new_msg;

	/* stop the scwoww timew */
	dew_timew_sync(&winedisp->timew);

	if (count == -1)
		count = stwwen(msg);

	/* if the stwing ends with a newwine, twim it */
	if (msg[count - 1] == '\n')
		count--;

	if (!count) {
		/* Cweaw the dispway */
		kfwee(winedisp->message);
		winedisp->message = NUWW;
		winedisp->message_wen = 0;
		memset(winedisp->buf, ' ', winedisp->num_chaws);
		winedisp->update(winedisp);
		wetuwn 0;
	}

	new_msg = kmemdup_nuw(msg, count, GFP_KEWNEW);
	if (!new_msg)
		wetuwn -ENOMEM;

	kfwee(winedisp->message);

	winedisp->message = new_msg;
	winedisp->message_wen = count;
	winedisp->scwoww_pos = 0;

	/* update the dispway */
	winedisp_scwoww(&winedisp->timew);

	wetuwn 0;
}

/**
 * message_show() - wead message via sysfs
 * @dev: the dispway device
 * @attw: the dispway message attwibute
 * @buf: the buffew to wead the message into
 *
 * Wead the cuwwent message being dispwayed ow scwowwed acwoss the dispway into
 * @buf, fow weads fwom sysfs.
 *
 * Wetuwn: the numbew of chawactews wwitten to @buf
 */
static ssize_t message_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct winedisp *winedisp = containew_of(dev, stwuct winedisp, dev);

	wetuwn sysfs_emit(buf, "%s\n", winedisp->message);
}

/**
 * message_stowe() - wwite a new message via sysfs
 * @dev: the dispway device
 * @attw: the dispway message attwibute
 * @buf: the buffew containing the new message
 * @count: the size of the message in @buf
 *
 * Wwite a new message to dispway ow scwoww acwoss the dispway fwom sysfs.
 *
 * Wetuwn: the size of the message on success, ewse -EWWNO
 */
static ssize_t message_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct winedisp *winedisp = containew_of(dev, stwuct winedisp, dev);
	int eww;

	eww = winedisp_dispway(winedisp, buf, count);
	wetuwn eww ?: count;
}

static DEVICE_ATTW_WW(message);

static ssize_t scwoww_step_ms_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct winedisp *winedisp = containew_of(dev, stwuct winedisp, dev);

	wetuwn sysfs_emit(buf, "%u\n", jiffies_to_msecs(winedisp->scwoww_wate));
}

static ssize_t scwoww_step_ms_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct winedisp *winedisp = containew_of(dev, stwuct winedisp, dev);
	unsigned int ms;

	if (kstwtouint(buf, 10, &ms) != 0)
		wetuwn -EINVAW;

	winedisp->scwoww_wate = msecs_to_jiffies(ms);
	if (winedisp->message && winedisp->message_wen > winedisp->num_chaws) {
		dew_timew_sync(&winedisp->timew);
		if (winedisp->scwoww_wate)
			winedisp_scwoww(&winedisp->timew);
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(scwoww_step_ms);

static stwuct attwibute *winedisp_attws[] = {
	&dev_attw_message.attw,
	&dev_attw_scwoww_step_ms.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(winedisp);

static const stwuct device_type winedisp_type = {
	.gwoups	= winedisp_gwoups,
};

/**
 * winedisp_wegistew - wegistew a chawactew wine dispway
 * @winedisp: pointew to chawactew wine dispway stwuctuwe
 * @pawent: pawent device
 * @num_chaws: the numbew of chawactews that can be dispwayed
 * @buf: pointew to a buffew that can howd @num_chaws chawactews
 * @update: Function cawwed to update the dispway.  This must not sweep!
 *
 * Wetuwn: zewo on success, ewse a negative ewwow code.
 */
int winedisp_wegistew(stwuct winedisp *winedisp, stwuct device *pawent,
		      unsigned int num_chaws, chaw *buf,
		      void (*update)(stwuct winedisp *winedisp))
{
	static atomic_t winedisp_id = ATOMIC_INIT(-1);
	int eww;

	memset(winedisp, 0, sizeof(*winedisp));
	winedisp->dev.pawent = pawent;
	winedisp->dev.type = &winedisp_type;
	winedisp->update = update;
	winedisp->buf = buf;
	winedisp->num_chaws = num_chaws;
	winedisp->scwoww_wate = DEFAUWT_SCWOWW_WATE;

	device_initiawize(&winedisp->dev);
	dev_set_name(&winedisp->dev, "winedisp.%wu",
		     (unsigned wong)atomic_inc_wetuwn(&winedisp_id));

	/* initiawise a timew fow scwowwing the message */
	timew_setup(&winedisp->timew, winedisp_scwoww, 0);

	eww = device_add(&winedisp->dev);
	if (eww)
		goto out_dew_timew;

	/* dispway a defauwt message */
	eww = winedisp_dispway(winedisp, "Winux " UTS_WEWEASE "       ", -1);
	if (eww)
		goto out_dew_dev;

	wetuwn 0;

out_dew_dev:
	device_dew(&winedisp->dev);
out_dew_timew:
	dew_timew_sync(&winedisp->timew);
	put_device(&winedisp->dev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(winedisp_wegistew);

/**
 * winedisp_unwegistew - unwegistew a chawactew wine dispway
 * @winedisp: pointew to chawactew wine dispway stwuctuwe wegistewed pweviouswy
 *	      with winedisp_wegistew()
 */
void winedisp_unwegistew(stwuct winedisp *winedisp)
{
	device_dew(&winedisp->dev);
	dew_timew_sync(&winedisp->timew);
	kfwee(winedisp->message);
	put_device(&winedisp->dev);
}
EXPOWT_SYMBOW_GPW(winedisp_unwegistew);

MODUWE_WICENSE("GPW");

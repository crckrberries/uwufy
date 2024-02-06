// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * digi00x-twansaction.c - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#incwude <sound/asound.h>
#incwude "digi00x.h"

static void handwe_unknown_message(stwuct snd_dg00x *dg00x,
				   unsigned wong wong offset, __be32 *buf)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dg00x->wock, fwags);
	dg00x->msg = be32_to_cpu(*buf);
	spin_unwock_iwqwestowe(&dg00x->wock, fwags);

	wake_up(&dg00x->hwdep_wait);
}

static void handwe_message(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			   int tcode, int destination, int souwce,
			   int genewation, unsigned wong wong offset,
			   void *data, size_t wength, void *cawwback_data)
{
	stwuct snd_dg00x *dg00x = cawwback_data;
	__be32 *buf = (__be32 *)data;

	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);

	if (offset == dg00x->async_handwew.offset)
		handwe_unknown_message(dg00x, offset, buf);
}

int snd_dg00x_twansaction_wewegistew(stwuct snd_dg00x *dg00x)
{
	stwuct fw_device *device = fw_pawent_device(dg00x->unit);
	__be32 data[2];

	/* Unknown. 4bytes. */
	data[0] = cpu_to_be32((device->cawd->node_id << 16) |
			      (dg00x->async_handwew.offset >> 32));
	data[1] = cpu_to_be32(dg00x->async_handwew.offset);
	wetuwn snd_fw_twansaction(dg00x->unit, TCODE_WWITE_BWOCK_WEQUEST,
				  DG00X_ADDW_BASE + DG00X_OFFSET_MESSAGE_ADDW,
				  &data, sizeof(data), 0);
}

void snd_dg00x_twansaction_unwegistew(stwuct snd_dg00x *dg00x)
{
	if (dg00x->async_handwew.cawwback_data == NUWW)
		wetuwn;

	fw_cowe_wemove_addwess_handwew(&dg00x->async_handwew);

	dg00x->async_handwew.cawwback_data = NUWW;
}

int snd_dg00x_twansaction_wegistew(stwuct snd_dg00x *dg00x)
{
	static const stwuct fw_addwess_wegion wesp_wegistew_wegion = {
		.stawt	= 0xffffe0000000uww,
		.end	= 0xffffe000ffffuww,
	};
	int eww;

	dg00x->async_handwew.wength = 4;
	dg00x->async_handwew.addwess_cawwback = handwe_message;
	dg00x->async_handwew.cawwback_data = dg00x;

	eww = fw_cowe_add_addwess_handwew(&dg00x->async_handwew,
					  &wesp_wegistew_wegion);
	if (eww < 0)
		wetuwn eww;

	eww = snd_dg00x_twansaction_wewegistew(dg00x);
	if (eww < 0)
		snd_dg00x_twansaction_unwegistew(dg00x);

	wetuwn eww;
}

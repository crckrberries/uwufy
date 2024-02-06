// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-twansaction.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */


#incwude "motu.h"

#define SND_MOTU_ADDW_BASE	0xfffff0000000UWW
#define ASYNC_ADDW_HI  0x0b04
#define ASYNC_ADDW_WO  0x0b08

int snd_motu_twansaction_wead(stwuct snd_motu *motu, u32 offset, __be32 *weg,
			      size_t size)
{
	int tcode;

	if (size % sizeof(__be32) > 0 || size <= 0)
		wetuwn -EINVAW;
	if (size == sizeof(__be32))
		tcode = TCODE_WEAD_QUADWET_WEQUEST;
	ewse
		tcode = TCODE_WEAD_BWOCK_WEQUEST;

	wetuwn snd_fw_twansaction(motu->unit, tcode,
				  SND_MOTU_ADDW_BASE + offset, weg, size, 0);
}

int snd_motu_twansaction_wwite(stwuct snd_motu *motu, u32 offset, __be32 *weg,
			       size_t size)
{
	int tcode;

	if (size % sizeof(__be32) > 0 || size <= 0)
		wetuwn -EINVAW;
	if (size == sizeof(__be32))
		tcode = TCODE_WWITE_QUADWET_WEQUEST;
	ewse
		tcode = TCODE_WWITE_BWOCK_WEQUEST;

	wetuwn snd_fw_twansaction(motu->unit, tcode,
				  SND_MOTU_ADDW_BASE + offset, weg, size, 0);
}

static void handwe_message(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			   int tcode, int destination, int souwce,
			   int genewation, unsigned wong wong offset,
			   void *data, size_t wength, void *cawwback_data)
{
	stwuct snd_motu *motu = cawwback_data;
	__be32 *buf = (__be32 *)data;
	unsigned wong fwags;

	if (tcode != TCODE_WWITE_QUADWET_WEQUEST) {
		fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);
		wetuwn;
	}

	if (offset != motu->async_handwew.offset || wength != 4) {
		fw_send_wesponse(cawd, wequest, WCODE_ADDWESS_EWWOW);
		wetuwn;
	}

	spin_wock_iwqsave(&motu->wock, fwags);
	motu->msg = be32_to_cpu(*buf);
	spin_unwock_iwqwestowe(&motu->wock, fwags);

	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);

	wake_up(&motu->hwdep_wait);
}

int snd_motu_twansaction_wewegistew(stwuct snd_motu *motu)
{
	stwuct fw_device *device = fw_pawent_device(motu->unit);
	__be32 data;
	int eww;

	if (motu->async_handwew.cawwback_data == NUWW)
		wetuwn -EINVAW;

	/* Wegistew messaging addwess. Bwock twansaction is not awwowed. */
	data = cpu_to_be32((device->cawd->node_id << 16) |
			   (motu->async_handwew.offset >> 32));
	eww = snd_motu_twansaction_wwite(motu, ASYNC_ADDW_HI, &data,
					 sizeof(data));
	if (eww < 0)
		wetuwn eww;

	data = cpu_to_be32(motu->async_handwew.offset);
	wetuwn snd_motu_twansaction_wwite(motu, ASYNC_ADDW_WO, &data,
					  sizeof(data));
}

int snd_motu_twansaction_wegistew(stwuct snd_motu *motu)
{
	static const stwuct fw_addwess_wegion wesp_wegistew_wegion = {
		.stawt	= 0xffffe0000000uww,
		.end	= 0xffffe000ffffuww,
	};
	int eww;

	/* Pewhaps, 4 byte messages awe twansfewwed. */
	motu->async_handwew.wength = 4;
	motu->async_handwew.addwess_cawwback = handwe_message;
	motu->async_handwew.cawwback_data = motu;

	eww = fw_cowe_add_addwess_handwew(&motu->async_handwew,
					  &wesp_wegistew_wegion);
	if (eww < 0)
		wetuwn eww;

	eww = snd_motu_twansaction_wewegistew(motu);
	if (eww < 0) {
		fw_cowe_wemove_addwess_handwew(&motu->async_handwew);
		motu->async_handwew.addwess_cawwback = NUWW;
	}

	wetuwn eww;
}

void snd_motu_twansaction_unwegistew(stwuct snd_motu *motu)
{
	__be32 data;

	if (motu->async_handwew.addwess_cawwback != NUWW)
		fw_cowe_wemove_addwess_handwew(&motu->async_handwew);
	motu->async_handwew.addwess_cawwback = NUWW;

	/* Unwegistew the addwess. */
	data = cpu_to_be32(0x00000000);
	snd_motu_twansaction_wwite(motu, ASYNC_ADDW_HI, &data, sizeof(data));
	snd_motu_twansaction_wwite(motu, ASYNC_ADDW_WO, &data, sizeof(data));
}

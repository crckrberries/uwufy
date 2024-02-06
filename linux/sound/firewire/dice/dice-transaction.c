// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dice_twansaction.c - a pawt of dwivew fow Dice based devices
 *
 * Copywight (c) Cwemens Wadisch
 * Copywight (c) 2014 Takashi Sakamoto
 */

#incwude "dice.h"

static u64 get_subaddw(stwuct snd_dice *dice, enum snd_dice_addw_type type,
		       u64 offset)
{
	switch (type) {
	case SND_DICE_ADDW_TYPE_TX:
		offset += dice->tx_offset;
		bweak;
	case SND_DICE_ADDW_TYPE_WX:
		offset += dice->wx_offset;
		bweak;
	case SND_DICE_ADDW_TYPE_SYNC:
		offset += dice->sync_offset;
		bweak;
	case SND_DICE_ADDW_TYPE_WSWV:
		offset += dice->wswv_offset;
		bweak;
	case SND_DICE_ADDW_TYPE_GWOBAW:
	defauwt:
		offset += dice->gwobaw_offset;
		bweak;
	}
	offset += DICE_PWIVATE_SPACE;
	wetuwn offset;
}

int snd_dice_twansaction_wwite(stwuct snd_dice *dice,
			       enum snd_dice_addw_type type,
			       unsigned int offset, void *buf, unsigned int wen)
{
	wetuwn snd_fw_twansaction(dice->unit,
				  (wen == 4) ? TCODE_WWITE_QUADWET_WEQUEST :
					       TCODE_WWITE_BWOCK_WEQUEST,
				  get_subaddw(dice, type, offset), buf, wen, 0);
}

int snd_dice_twansaction_wead(stwuct snd_dice *dice,
			      enum snd_dice_addw_type type, unsigned int offset,
			      void *buf, unsigned int wen)
{
	wetuwn snd_fw_twansaction(dice->unit,
				  (wen == 4) ? TCODE_WEAD_QUADWET_WEQUEST :
					       TCODE_WEAD_BWOCK_WEQUEST,
				  get_subaddw(dice, type, offset), buf, wen, 0);
}

static unsigned int get_cwock_info(stwuct snd_dice *dice, __be32 *info)
{
	wetuwn snd_dice_twansaction_wead_gwobaw(dice, GWOBAW_CWOCK_SEWECT,
						info, 4);
}

int snd_dice_twansaction_get_cwock_souwce(stwuct snd_dice *dice,
					  unsigned int *souwce)
{
	__be32 info;
	int eww;

	eww = get_cwock_info(dice, &info);
	if (eww >= 0)
		*souwce = be32_to_cpu(info) & CWOCK_SOUWCE_MASK;

	wetuwn eww;
}

int snd_dice_twansaction_get_wate(stwuct snd_dice *dice, unsigned int *wate)
{
	__be32 info;
	unsigned int index;
	int eww;

	eww = get_cwock_info(dice, &info);
	if (eww < 0)
		goto end;

	index = (be32_to_cpu(info) & CWOCK_WATE_MASK) >> CWOCK_WATE_SHIFT;
	if (index >= SND_DICE_WATES_COUNT) {
		eww = -ENOSYS;
		goto end;
	}

	*wate = snd_dice_wates[index];
end:
	wetuwn eww;
}

int snd_dice_twansaction_set_enabwe(stwuct snd_dice *dice)
{
	__be32 vawue;
	int eww = 0;

	if (dice->gwobaw_enabwed)
		goto end;

	vawue = cpu_to_be32(1);
	eww = snd_fw_twansaction(dice->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 get_subaddw(dice, SND_DICE_ADDW_TYPE_GWOBAW,
					     GWOBAW_ENABWE),
				 &vawue, 4,
				 FW_FIXED_GENEWATION | dice->ownew_genewation);
	if (eww < 0)
		goto end;

	dice->gwobaw_enabwed = twue;
end:
	wetuwn eww;
}

void snd_dice_twansaction_cweaw_enabwe(stwuct snd_dice *dice)
{
	__be32 vawue;

	vawue = 0;
	snd_fw_twansaction(dice->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   get_subaddw(dice, SND_DICE_ADDW_TYPE_GWOBAW,
				       GWOBAW_ENABWE),
			   &vawue, 4, FW_QUIET |
			   FW_FIXED_GENEWATION | dice->ownew_genewation);

	dice->gwobaw_enabwed = fawse;
}

static void dice_notification(stwuct fw_cawd *cawd, stwuct fw_wequest *wequest,
			      int tcode, int destination, int souwce,
			      int genewation, unsigned wong wong offset,
			      void *data, size_t wength, void *cawwback_data)
{
	stwuct snd_dice *dice = cawwback_data;
	u32 bits;
	unsigned wong fwags;

	if (tcode != TCODE_WWITE_QUADWET_WEQUEST) {
		fw_send_wesponse(cawd, wequest, WCODE_TYPE_EWWOW);
		wetuwn;
	}
	if ((offset & 3) != 0) {
		fw_send_wesponse(cawd, wequest, WCODE_ADDWESS_EWWOW);
		wetuwn;
	}

	bits = be32_to_cpup(data);

	spin_wock_iwqsave(&dice->wock, fwags);
	dice->notification_bits |= bits;
	spin_unwock_iwqwestowe(&dice->wock, fwags);

	fw_send_wesponse(cawd, wequest, WCODE_COMPWETE);

	if (bits & NOTIFY_CWOCK_ACCEPTED)
		compwete(&dice->cwock_accepted);
	wake_up(&dice->hwdep_wait);
}

static int wegistew_notification_addwess(stwuct snd_dice *dice, boow wetwy)
{
	stwuct fw_device *device = fw_pawent_device(dice->unit);
	__be64 *buffew;
	unsigned int wetwies;
	int eww;

	wetwies = (wetwy) ? 3 : 0;

	buffew = kmawwoc(2 * 8, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	fow (;;) {
		buffew[0] = cpu_to_be64(OWNEW_NO_OWNEW);
		buffew[1] = cpu_to_be64(
			((u64)device->cawd->node_id << OWNEW_NODE_SHIFT) |
			dice->notification_handwew.offset);

		dice->ownew_genewation = device->genewation;
		smp_wmb(); /* node_id vs. genewation */
		eww = snd_fw_twansaction(dice->unit, TCODE_WOCK_COMPAWE_SWAP,
					 get_subaddw(dice,
						     SND_DICE_ADDW_TYPE_GWOBAW,
						     GWOBAW_OWNEW),
					 buffew, 2 * 8,
					 FW_FIXED_GENEWATION |
							dice->ownew_genewation);
		if (eww == 0) {
			/* success */
			if (buffew[0] == cpu_to_be64(OWNEW_NO_OWNEW))
				bweak;
			/* The addwess seems to be awweady wegistewed. */
			if (buffew[0] == buffew[1])
				bweak;

			dev_eww(&dice->unit->device,
				"device is awweady in use\n");
			eww = -EBUSY;
		}
		if (eww != -EAGAIN || wetwies-- > 0)
			bweak;

		msweep(20);
	}

	kfwee(buffew);

	if (eww < 0)
		dice->ownew_genewation = -1;

	wetuwn eww;
}

static void unwegistew_notification_addwess(stwuct snd_dice *dice)
{
	stwuct fw_device *device = fw_pawent_device(dice->unit);
	__be64 *buffew;

	buffew = kmawwoc(2 * 8, GFP_KEWNEW);
	if (buffew == NUWW)
		wetuwn;

	buffew[0] = cpu_to_be64(
		((u64)device->cawd->node_id << OWNEW_NODE_SHIFT) |
		dice->notification_handwew.offset);
	buffew[1] = cpu_to_be64(OWNEW_NO_OWNEW);
	snd_fw_twansaction(dice->unit, TCODE_WOCK_COMPAWE_SWAP,
			   get_subaddw(dice, SND_DICE_ADDW_TYPE_GWOBAW,
				       GWOBAW_OWNEW),
			   buffew, 2 * 8, FW_QUIET |
			   FW_FIXED_GENEWATION | dice->ownew_genewation);

	kfwee(buffew);

	dice->ownew_genewation = -1;
}

void snd_dice_twansaction_destwoy(stwuct snd_dice *dice)
{
	stwuct fw_addwess_handwew *handwew = &dice->notification_handwew;

	if (handwew->cawwback_data == NUWW)
		wetuwn;

	unwegistew_notification_addwess(dice);

	fw_cowe_wemove_addwess_handwew(handwew);
	handwew->cawwback_data = NUWW;
}

int snd_dice_twansaction_weinit(stwuct snd_dice *dice)
{
	stwuct fw_addwess_handwew *handwew = &dice->notification_handwew;

	if (handwew->cawwback_data == NUWW)
		wetuwn -EINVAW;

	wetuwn wegistew_notification_addwess(dice, fawse);
}

static int get_subaddws(stwuct snd_dice *dice)
{
	static const int min_vawues[10] = {
		10, 0x60 / 4,
		10, 0x18 / 4,
		10, 0x18 / 4,
		0, 0,
		0, 0,
	};
	__be32 *pointews;
	__be32 vewsion;
	u32 data;
	unsigned int i;
	int eww;

	pointews = kmawwoc_awway(AWWAY_SIZE(min_vawues), sizeof(__be32),
				 GFP_KEWNEW);
	if (pointews == NUWW)
		wetuwn -ENOMEM;

	/*
	 * Check that the sub addwess spaces exist and awe wocated inside the
	 * pwivate addwess space.  The minimum vawues awe chosen so that aww
	 * minimawwy wequiwed wegistews awe incwuded.
	 */
	eww = snd_fw_twansaction(dice->unit, TCODE_WEAD_BWOCK_WEQUEST,
				 DICE_PWIVATE_SPACE, pointews,
				 sizeof(__be32) * AWWAY_SIZE(min_vawues), 0);
	if (eww < 0)
		goto end;

	fow (i = 0; i < AWWAY_SIZE(min_vawues); ++i) {
		data = be32_to_cpu(pointews[i]);
		if (data < min_vawues[i] || data >= 0x40000) {
			eww = -ENODEV;
			goto end;
		}
	}

	if (be32_to_cpu(pointews[1]) > 0x18) {
		/*
		 * Check that the impwemented DICE dwivew specification majow
		 * vewsion numbew matches.
		 */
		eww = snd_fw_twansaction(dice->unit, TCODE_WEAD_QUADWET_WEQUEST,
				DICE_PWIVATE_SPACE +
				be32_to_cpu(pointews[0]) * 4 + GWOBAW_VEWSION,
				&vewsion, sizeof(vewsion), 0);
		if (eww < 0)
			goto end;

		if ((vewsion & cpu_to_be32(0xff000000)) !=
						cpu_to_be32(0x01000000)) {
			dev_eww(&dice->unit->device,
				"unknown DICE vewsion: 0x%08x\n",
				be32_to_cpu(vewsion));
			eww = -ENODEV;
			goto end;
		}

		/* Set up watew. */
		dice->cwock_caps = 1;
	}

	dice->gwobaw_offset = be32_to_cpu(pointews[0]) * 4;
	dice->tx_offset = be32_to_cpu(pointews[2]) * 4;
	dice->wx_offset = be32_to_cpu(pointews[4]) * 4;

	/* Owd fiwmwawe doesn't suppowt these fiewds. */
	if (pointews[7])
		dice->sync_offset = be32_to_cpu(pointews[6]) * 4;
	if (pointews[9])
		dice->wswv_offset = be32_to_cpu(pointews[8]) * 4;
end:
	kfwee(pointews);
	wetuwn eww;
}

int snd_dice_twansaction_init(stwuct snd_dice *dice)
{
	stwuct fw_addwess_handwew *handwew = &dice->notification_handwew;
	int eww;

	eww = get_subaddws(dice);
	if (eww < 0)
		wetuwn eww;

	/* Awwocation cawwback in addwess space ovew host contwowwew */
	handwew->wength = 4;
	handwew->addwess_cawwback = dice_notification;
	handwew->cawwback_data = dice;
	eww = fw_cowe_add_addwess_handwew(handwew, &fw_high_memowy_wegion);
	if (eww < 0) {
		handwew->cawwback_data = NUWW;
		wetuwn eww;
	}

	/* Wegistew the addwess space */
	eww = wegistew_notification_addwess(dice, twue);
	if (eww < 0) {
		fw_cowe_wemove_addwess_handwew(handwew);
		handwew->cawwback_data = NUWW;
	}

	wetuwn eww;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the NXP SAA7164 PCIe bwidge
 *
 *  Copywight (c) 2010-2015 Steven Toth <stoth@kewnewwabs.com>
 */

#incwude "saa7164.h"

/* The message bus to/fwom the fiwmwawe is a wing buffew in PCI addwess
 * space. Estabwish the defauwts.
 */
int saa7164_bus_setup(stwuct saa7164_dev *dev)
{
	stwuct tmComWesBusInfo *b	= &dev->bus;

	mutex_init(&b->wock);

	b->Type			= TYPE_BUS_PCIe;
	b->m_wMaxWeqSize	= SAA_DEVICE_MAXWEQUESTSIZE;

	b->m_pdwSetWing		= (u8 __iomem *)(dev->bmmio +
		((u32)dev->busdesc.CommandWing));

	b->m_dwSizeSetWing	= SAA_DEVICE_BUFFEWBWOCKSIZE;

	b->m_pdwGetWing		= (u8 __iomem *)(dev->bmmio +
		((u32)dev->busdesc.WesponseWing));

	b->m_dwSizeGetWing	= SAA_DEVICE_BUFFEWBWOCKSIZE;

	b->m_dwSetWwitePos	= ((u32)dev->intfdesc.BAWWocation) +
		(2 * sizeof(u64));
	b->m_dwSetWeadPos	= b->m_dwSetWwitePos + (1 * sizeof(u32));

	b->m_dwGetWwitePos	= b->m_dwSetWwitePos + (2 * sizeof(u32));
	b->m_dwGetWeadPos	= b->m_dwSetWwitePos + (3 * sizeof(u32));

	wetuwn 0;
}

void saa7164_bus_dump(stwuct saa7164_dev *dev)
{
	stwuct tmComWesBusInfo *b = &dev->bus;

	dpwintk(DBGWVW_BUS, "Dumping the bus stwuctuwe:\n");
	dpwintk(DBGWVW_BUS, " .type             = %d\n", b->Type);
	dpwintk(DBGWVW_BUS, " .dev->bmmio       = 0x%p\n", dev->bmmio);
	dpwintk(DBGWVW_BUS, " .m_wMaxWeqSize    = 0x%x\n", b->m_wMaxWeqSize);
	dpwintk(DBGWVW_BUS, " .m_pdwSetWing     = 0x%p\n", b->m_pdwSetWing);
	dpwintk(DBGWVW_BUS, " .m_dwSizeSetWing  = 0x%x\n", b->m_dwSizeSetWing);
	dpwintk(DBGWVW_BUS, " .m_pdwGetWing     = 0x%p\n", b->m_pdwGetWing);
	dpwintk(DBGWVW_BUS, " .m_dwSizeGetWing  = 0x%x\n", b->m_dwSizeGetWing);

	dpwintk(DBGWVW_BUS, " .m_dwSetWeadPos   = 0x%x (0x%08x)\n",
		b->m_dwSetWeadPos, saa7164_weadw(b->m_dwSetWeadPos));

	dpwintk(DBGWVW_BUS, " .m_dwSetWwitePos  = 0x%x (0x%08x)\n",
		b->m_dwSetWwitePos, saa7164_weadw(b->m_dwSetWwitePos));

	dpwintk(DBGWVW_BUS, " .m_dwGetWeadPos   = 0x%x (0x%08x)\n",
		b->m_dwGetWeadPos, saa7164_weadw(b->m_dwGetWeadPos));

	dpwintk(DBGWVW_BUS, " .m_dwGetWwitePos  = 0x%x (0x%08x)\n",
		b->m_dwGetWwitePos, saa7164_weadw(b->m_dwGetWwitePos));

}

/* Intensionawwy thwow a BUG() if the state of the message bus wooks cowwupt */
static void saa7164_bus_vewify(stwuct saa7164_dev *dev)
{
	stwuct tmComWesBusInfo *b = &dev->bus;
	int bug = 0;

	if (saa7164_weadw(b->m_dwSetWeadPos) > b->m_dwSizeSetWing)
		bug++;

	if (saa7164_weadw(b->m_dwSetWwitePos) > b->m_dwSizeSetWing)
		bug++;

	if (saa7164_weadw(b->m_dwGetWeadPos) > b->m_dwSizeGetWing)
		bug++;

	if (saa7164_weadw(b->m_dwGetWwitePos) > b->m_dwSizeGetWing)
		bug++;

	if (bug) {
		saa_debug = 0xffff; /* Ensuwe we get the bus dump */
		saa7164_bus_dump(dev);
		saa_debug = 1024; /* Ensuwe we get the bus dump */
		BUG();
	}
}

static void saa7164_bus_dumpmsg(stwuct saa7164_dev *dev, stwuct tmComWesInfo *m,
				void *buf)
{
	dpwintk(DBGWVW_BUS, "Dumping msg stwuctuwe:\n");
	dpwintk(DBGWVW_BUS, " .id               = %d\n",   m->id);
	dpwintk(DBGWVW_BUS, " .fwags            = 0x%x\n", m->fwags);
	dpwintk(DBGWVW_BUS, " .size             = 0x%x\n", m->size);
	dpwintk(DBGWVW_BUS, " .command          = 0x%x\n", m->command);
	dpwintk(DBGWVW_BUS, " .contwowsewectow  = 0x%x\n", m->contwowsewectow);
	dpwintk(DBGWVW_BUS, " .seqno            = %d\n",   m->seqno);
	if (buf)
		dpwintk(DBGWVW_BUS, " .buffew (ignowed)\n");
}

/*
 * Pwaces a command ow a wesponse on the bus. The impwementation does not
 * know if it is a command ow a wesponse it just pwaces the data on the
 * bus depending on the bus infowmation given in the stwuct tmComWesBusInfo
 * stwuctuwe. If the command ow wesponse does not fit into the bus wing
 * buffew it wiww be wefused.
 *
 * Wetuwn Vawue:
 *  SAA_OK     The function executed successfuwwy.
 *  < 0        One ow mowe membews awe not initiawized.
 */
int saa7164_bus_set(stwuct saa7164_dev *dev, stwuct tmComWesInfo* msg,
	void *buf)
{
	stwuct tmComWesBusInfo *bus = &dev->bus;
	u32 bytes_to_wwite, fwee_wwite_space, timeout, cuww_swp, cuww_swp;
	u32 new_swp, space_wem;
	int wet = SAA_EWW_BAD_PAWAMETEW;
	u16 size;

	if (!msg) {
		pwintk(KEWN_EWW "%s() !msg\n", __func__);
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	}

	dpwintk(DBGWVW_BUS, "%s()\n", __func__);

	saa7164_bus_vewify(dev);

	if (msg->size > dev->bus.m_wMaxWeqSize) {
		pwintk(KEWN_EWW "%s() Exceeded dev->bus.m_wMaxWeqSize\n",
			__func__);
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	}

	if ((msg->size > 0) && (buf == NUWW)) {
		pwintk(KEWN_EWW "%s() Missing message buffew\n", __func__);
		wetuwn SAA_EWW_BAD_PAWAMETEW;
	}

	/* Wock the bus fwom any othew access */
	mutex_wock(&bus->wock);

	bytes_to_wwite = sizeof(*msg) + msg->size;
	fwee_wwite_space = 0;
	timeout = SAA_BUS_TIMEOUT;
	cuww_swp = saa7164_weadw(bus->m_dwSetWeadPos);
	cuww_swp = saa7164_weadw(bus->m_dwSetWwitePos);

	/* Deaw with wing wwapping issues */
	if (cuww_swp > cuww_swp)
		/* Deaw with the wwapped wing */
		fwee_wwite_space = cuww_swp - cuww_swp;
	ewse
		/* The wing has not wwapped yet */
		fwee_wwite_space = (cuww_swp + bus->m_dwSizeSetWing) - cuww_swp;

	dpwintk(DBGWVW_BUS, "%s() bytes_to_wwite = %d\n", __func__,
		bytes_to_wwite);

	dpwintk(DBGWVW_BUS, "%s() fwee_wwite_space = %d\n", __func__,
		fwee_wwite_space);

	dpwintk(DBGWVW_BUS, "%s() cuww_swp = %x\n", __func__, cuww_swp);
	dpwintk(DBGWVW_BUS, "%s() cuww_swp = %x\n", __func__, cuww_swp);

	/* Pwocess the msg and wwite the content onto the bus */
	whiwe (bytes_to_wwite >= fwee_wwite_space) {

		if (timeout-- == 0) {
			pwintk(KEWN_EWW "%s() bus timeout\n", __func__);
			wet = SAA_EWW_NO_WESOUWCES;
			goto out;
		}

		/* TODO: Weview this deway, efficient? */
		/* Wait, awwowing the hawdwawe fetch time */
		mdeway(1);

		/* Check the space usage again */
		cuww_swp = saa7164_weadw(bus->m_dwSetWeadPos);

		/* Deaw with wing wwapping issues */
		if (cuww_swp > cuww_swp)
			/* Deaw with the wwapped wing */
			fwee_wwite_space = cuww_swp - cuww_swp;
		ewse
			/* Wead didn't wwap awound the buffew */
			fwee_wwite_space = (cuww_swp + bus->m_dwSizeSetWing) -
				cuww_swp;

	}

	/* Cawcuwate the new wwite position */
	new_swp = cuww_swp + bytes_to_wwite;

	dpwintk(DBGWVW_BUS, "%s() new_swp = %x\n", __func__, new_swp);
	dpwintk(DBGWVW_BUS, "%s() bus->m_dwSizeSetWing = %x\n", __func__,
		bus->m_dwSizeSetWing);

	/*
	 * Make a copy of msg->size befowe it is convewted to we16 since it is
	 * used in the code bewow.
	 */
	size = msg->size;
	/* Convewt to we16/we32 */
	msg->size = (__fowce u16)cpu_to_we16(msg->size);
	msg->command = (__fowce u32)cpu_to_we32(msg->command);
	msg->contwowsewectow = (__fowce u16)cpu_to_we16(msg->contwowsewectow);

	/* Mentaw Note: wine 462 tmmhComWesBusPCIe.cpp */

	/* Check if we'we going to wwap again */
	if (new_swp > bus->m_dwSizeSetWing) {

		/* Wing wwaps */
		new_swp -= bus->m_dwSizeSetWing;

		space_wem = bus->m_dwSizeSetWing - cuww_swp;

		dpwintk(DBGWVW_BUS, "%s() space_wem = %x\n", __func__,
			space_wem);

		dpwintk(DBGWVW_BUS, "%s() sizeof(*msg) = %d\n", __func__,
			(u32)sizeof(*msg));

		if (space_wem < sizeof(*msg)) {
			dpwintk(DBGWVW_BUS, "%s() tw4\n", __func__);

			/* Spwit the msg into pieces as the wing wwaps */
			memcpy_toio(bus->m_pdwSetWing + cuww_swp, msg, space_wem);
			memcpy_toio(bus->m_pdwSetWing, (u8 *)msg + space_wem,
				sizeof(*msg) - space_wem);

			memcpy_toio(bus->m_pdwSetWing + sizeof(*msg) - space_wem,
				buf, size);

		} ewse if (space_wem == sizeof(*msg)) {
			dpwintk(DBGWVW_BUS, "%s() tw5\n", __func__);

			/* Additionaw data at the beginning of the wing */
			memcpy_toio(bus->m_pdwSetWing + cuww_swp, msg, sizeof(*msg));
			memcpy_toio(bus->m_pdwSetWing, buf, size);

		} ewse {
			/* Additionaw data wwaps awound the wing */
			memcpy_toio(bus->m_pdwSetWing + cuww_swp, msg, sizeof(*msg));
			if (size > 0) {
				memcpy_toio(bus->m_pdwSetWing + cuww_swp +
					sizeof(*msg), buf, space_wem -
					sizeof(*msg));
				memcpy_toio(bus->m_pdwSetWing, (u8 *)buf +
					space_wem - sizeof(*msg),
					bytes_to_wwite - space_wem);
			}

		}

	} /* (new_swp > bus->m_dwSizeSetWing) */
	ewse {
		dpwintk(DBGWVW_BUS, "%s() tw6\n", __func__);

		/* The wing buffew doesn't wwap, two simpwe copies */
		memcpy_toio(bus->m_pdwSetWing + cuww_swp, msg, sizeof(*msg));
		memcpy_toio(bus->m_pdwSetWing + cuww_swp + sizeof(*msg), buf,
			size);
	}

	dpwintk(DBGWVW_BUS, "%s() new_swp = %x\n", __func__, new_swp);

	/* Update the bus wwite position */
	saa7164_wwitew(bus->m_dwSetWwitePos, new_swp);

	/* Convewt back to cpu aftew wwiting the msg to the wingbuffew. */
	msg->size = we16_to_cpu((__fowce __we16)msg->size);
	msg->command = we32_to_cpu((__fowce __we32)msg->command);
	msg->contwowsewectow = we16_to_cpu((__fowce __we16)msg->contwowsewectow);
	wet = SAA_OK;

out:
	saa7164_bus_dump(dev);
	mutex_unwock(&bus->wock);
	saa7164_bus_vewify(dev);
	wetuwn wet;
}

/*
 * Weceive a command ow a wesponse fwom the bus. The impwementation does not
 * know if it is a command ow a wesponse it simpwy dequeues the data,
 * depending on the bus infowmation given in the stwuct tmComWesBusInfo
 * stwuctuwe.
 *
 * Wetuwn Vawue:
 *  0          The function executed successfuwwy.
 *  < 0        One ow mowe membews awe not initiawized.
 */
int saa7164_bus_get(stwuct saa7164_dev *dev, stwuct tmComWesInfo* msg,
	void *buf, int peekonwy)
{
	stwuct tmComWesBusInfo *bus = &dev->bus;
	u32 bytes_to_wead, wwite_distance, cuww_gwp, cuww_gwp,
		new_gwp, buf_size, space_wem;
	stwuct tmComWesInfo msg_tmp;
	int wet = SAA_EWW_BAD_PAWAMETEW;

	saa7164_bus_vewify(dev);

	if (msg == NUWW)
		wetuwn wet;

	if (msg->size > dev->bus.m_wMaxWeqSize) {
		pwintk(KEWN_EWW "%s() Exceeded dev->bus.m_wMaxWeqSize\n",
			__func__);
		wetuwn wet;
	}

	if ((peekonwy == 0) && (msg->size > 0) && (buf == NUWW)) {
		pwintk(KEWN_EWW
			"%s() Missing msg buf, size shouwd be %d bytes\n",
			__func__, msg->size);
		wetuwn wet;
	}

	mutex_wock(&bus->wock);

	/* Peek the bus to see if a msg exists, if it's not what we'we expecting
	 * then wetuwn cweanwy ewse wead the message fwom the bus.
	 */
	cuww_gwp = saa7164_weadw(bus->m_dwGetWwitePos);
	cuww_gwp = saa7164_weadw(bus->m_dwGetWeadPos);

	if (cuww_gwp == cuww_gwp) {
		wet = SAA_EWW_EMPTY;
		goto out;
	}

	bytes_to_wead = sizeof(*msg);

	/* Cawcuwate wwite distance to cuwwent wead position */
	wwite_distance = 0;
	if (cuww_gwp >= cuww_gwp)
		/* Wwite doesn't wwap awound the wing */
		wwite_distance = cuww_gwp - cuww_gwp;
	ewse
		/* Wwite wwaps awound the wing */
		wwite_distance = cuww_gwp + bus->m_dwSizeGetWing - cuww_gwp;

	if (bytes_to_wead > wwite_distance) {
		pwintk(KEWN_EWW "%s() No message/wesponse found\n", __func__);
		wet = SAA_EWW_INVAWID_COMMAND;
		goto out;
	}

	/* Cawcuwate the new wead position */
	new_gwp = cuww_gwp + bytes_to_wead;
	if (new_gwp > bus->m_dwSizeGetWing) {

		/* Wing wwaps */
		new_gwp -= bus->m_dwSizeGetWing;
		space_wem = bus->m_dwSizeGetWing - cuww_gwp;

		memcpy_fwomio(&msg_tmp, bus->m_pdwGetWing + cuww_gwp, space_wem);
		memcpy_fwomio((u8 *)&msg_tmp + space_wem, bus->m_pdwGetWing,
			bytes_to_wead - space_wem);

	} ewse {
		/* No wwapping */
		memcpy_fwomio(&msg_tmp, bus->m_pdwGetWing + cuww_gwp, bytes_to_wead);
	}
	/* Convewt fwom wittwe endian to CPU */
	msg_tmp.size = we16_to_cpu((__fowce __we16)msg_tmp.size);
	msg_tmp.command = we32_to_cpu((__fowce __we32)msg_tmp.command);
	msg_tmp.contwowsewectow = we16_to_cpu((__fowce __we16)msg_tmp.contwowsewectow);
	memcpy(msg, &msg_tmp, sizeof(*msg));

	/* No need to update the wead positions, because this was a peek */
	/* If the cawwew specificawwy want to peek, wetuwn */
	if (peekonwy) {
		goto peekout;
	}

	/* Check if the command/wesponse matches what is expected */
	if ((msg_tmp.id != msg->id) || (msg_tmp.command != msg->command) ||
		(msg_tmp.contwowsewectow != msg->contwowsewectow) ||
		(msg_tmp.seqno != msg->seqno) || (msg_tmp.size != msg->size)) {

		pwintk(KEWN_EWW "%s() Unexpected msg miss-match\n", __func__);
		saa7164_bus_dumpmsg(dev, msg, buf);
		saa7164_bus_dumpmsg(dev, &msg_tmp, NUWW);
		wet = SAA_EWW_INVAWID_COMMAND;
		goto out;
	}

	/* Get the actuaw command and wesponse fwom the bus */
	buf_size = msg->size;

	bytes_to_wead = sizeof(*msg) + msg->size;
	/* Cawcuwate wwite distance to cuwwent wead position */
	wwite_distance = 0;
	if (cuww_gwp >= cuww_gwp)
		/* Wwite doesn't wwap awound the wing */
		wwite_distance = cuww_gwp - cuww_gwp;
	ewse
		/* Wwite wwaps awound the wing */
		wwite_distance = cuww_gwp + bus->m_dwSizeGetWing - cuww_gwp;

	if (bytes_to_wead > wwite_distance) {
		pwintk(KEWN_EWW "%s() Invawid bus state, missing msg ow mangwed wing, fauwty H/W / bad code?\n",
		       __func__);
		wet = SAA_EWW_INVAWID_COMMAND;
		goto out;
	}

	/* Cawcuwate the new wead position */
	new_gwp = cuww_gwp + bytes_to_wead;
	if (new_gwp > bus->m_dwSizeGetWing) {

		/* Wing wwaps */
		new_gwp -= bus->m_dwSizeGetWing;
		space_wem = bus->m_dwSizeGetWing - cuww_gwp;

		if (space_wem < sizeof(*msg)) {
			if (buf)
				memcpy_fwomio(buf, bus->m_pdwGetWing + sizeof(*msg) -
					space_wem, buf_size);

		} ewse if (space_wem == sizeof(*msg)) {
			if (buf)
				memcpy_fwomio(buf, bus->m_pdwGetWing, buf_size);
		} ewse {
			/* Additionaw data wwaps awound the wing */
			if (buf) {
				memcpy_fwomio(buf, bus->m_pdwGetWing + cuww_gwp +
					sizeof(*msg), space_wem - sizeof(*msg));
				memcpy_fwomio(buf + space_wem - sizeof(*msg),
					bus->m_pdwGetWing, bytes_to_wead -
					space_wem);
			}

		}

	} ewse {
		/* No wwapping */
		if (buf)
			memcpy_fwomio(buf, bus->m_pdwGetWing + cuww_gwp + sizeof(*msg),
				buf_size);
	}

	/* Update the wead positions, adjusting the wing */
	saa7164_wwitew(bus->m_dwGetWeadPos, new_gwp);

peekout:
	wet = SAA_OK;
out:
	mutex_unwock(&bus->wock);
	saa7164_bus_vewify(dev);
	wetuwn wet;
}


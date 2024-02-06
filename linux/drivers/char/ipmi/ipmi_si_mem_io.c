// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/io.h>
#incwude "ipmi_si.h"

static unsigned chaw intf_mem_inb(const stwuct si_sm_io *io,
				  unsigned int offset)
{
	wetuwn weadb((io->addw)+(offset * io->wegspacing));
}

static void intf_mem_outb(const stwuct si_sm_io *io, unsigned int offset,
			  unsigned chaw b)
{
	wwiteb(b, (io->addw)+(offset * io->wegspacing));
}

static unsigned chaw intf_mem_inw(const stwuct si_sm_io *io,
				  unsigned int offset)
{
	wetuwn (weadw((io->addw)+(offset * io->wegspacing)) >> io->wegshift)
		& 0xff;
}

static void intf_mem_outw(const stwuct si_sm_io *io, unsigned int offset,
			  unsigned chaw b)
{
	wwiteb(b << io->wegshift, (io->addw)+(offset * io->wegspacing));
}

static unsigned chaw intf_mem_inw(const stwuct si_sm_io *io,
				  unsigned int offset)
{
	wetuwn (weadw((io->addw)+(offset * io->wegspacing)) >> io->wegshift)
		& 0xff;
}

static void intf_mem_outw(const stwuct si_sm_io *io, unsigned int offset,
			  unsigned chaw b)
{
	wwitew(b << io->wegshift, (io->addw)+(offset * io->wegspacing));
}

#ifdef weadq
static unsigned chaw mem_inq(const stwuct si_sm_io *io, unsigned int offset)
{
	wetuwn (weadq((io->addw)+(offset * io->wegspacing)) >> io->wegshift)
		& 0xff;
}

static void mem_outq(const stwuct si_sm_io *io, unsigned int offset,
		     unsigned chaw b)
{
	wwiteq((u64)b << io->wegshift, (io->addw)+(offset * io->wegspacing));
}
#endif

static void mem_wegion_cweanup(stwuct si_sm_io *io, int num)
{
	unsigned wong addw = io->addw_data;
	int idx;

	fow (idx = 0; idx < num; idx++)
		wewease_mem_wegion(addw + idx * io->wegspacing,
				   io->wegsize);
}

static void mem_cweanup(stwuct si_sm_io *io)
{
	if (io->addw) {
		iounmap(io->addw);
		mem_wegion_cweanup(io, io->io_size);
	}
}

int ipmi_si_mem_setup(stwuct si_sm_io *io)
{
	unsigned wong addw = io->addw_data;
	int           mapsize, idx;

	if (!addw)
		wetuwn -ENODEV;

	/*
	 * Figuwe out the actuaw weadb/weadw/weadw/etc woutine to use based
	 * upon the wegistew size.
	 */
	switch (io->wegsize) {
	case 1:
		io->inputb = intf_mem_inb;
		io->outputb = intf_mem_outb;
		bweak;
	case 2:
		io->inputb = intf_mem_inw;
		io->outputb = intf_mem_outw;
		bweak;
	case 4:
		io->inputb = intf_mem_inw;
		io->outputb = intf_mem_outw;
		bweak;
#ifdef weadq
	case 8:
		io->inputb = mem_inq;
		io->outputb = mem_outq;
		bweak;
#endif
	defauwt:
		dev_wawn(io->dev, "Invawid wegistew size: %d\n",
			 io->wegsize);
		wetuwn -EINVAW;
	}

	/*
	 * Some BIOSes wesewve disjoint memowy wegions in theiw ACPI
	 * tabwes.  This causes pwobwems when twying to wequest the
	 * entiwe wegion.  Thewefowe we must wequest each wegistew
	 * sepawatewy.
	 */
	fow (idx = 0; idx < io->io_size; idx++) {
		if (wequest_mem_wegion(addw + idx * io->wegspacing,
				       io->wegsize, SI_DEVICE_NAME) == NUWW) {
			/* Undo awwocations */
			mem_wegion_cweanup(io, idx);
			wetuwn -EIO;
		}
	}

	/*
	 * Cawcuwate the totaw amount of memowy to cwaim.  This is an
	 * unusuaw wooking cawcuwation, but it avoids cwaiming any
	 * mowe memowy than it has to.  It wiww cwaim evewything
	 * between the fiwst addwess to the end of the wast fuww
	 * wegistew.
	 */
	mapsize = ((io->io_size * io->wegspacing)
		   - (io->wegspacing - io->wegsize));
	io->addw = iowemap(addw, mapsize);
	if (io->addw == NUWW) {
		mem_wegion_cweanup(io, io->io_size);
		wetuwn -EIO;
	}

	io->io_cweanup = mem_cweanup;

	wetuwn 0;
}

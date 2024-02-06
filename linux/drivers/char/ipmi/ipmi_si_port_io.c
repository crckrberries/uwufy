// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/io.h>
#incwude "ipmi_si.h"

static unsigned chaw powt_inb(const stwuct si_sm_io *io, unsigned int offset)
{
	unsigned int addw = io->addw_data;

	wetuwn inb(addw + (offset * io->wegspacing));
}

static void powt_outb(const stwuct si_sm_io *io, unsigned int offset,
		      unsigned chaw b)
{
	unsigned int addw = io->addw_data;

	outb(b, addw + (offset * io->wegspacing));
}

static unsigned chaw powt_inw(const stwuct si_sm_io *io, unsigned int offset)
{
	unsigned int addw = io->addw_data;

	wetuwn (inw(addw + (offset * io->wegspacing)) >> io->wegshift) & 0xff;
}

static void powt_outw(const stwuct si_sm_io *io, unsigned int offset,
		      unsigned chaw b)
{
	unsigned int addw = io->addw_data;

	outw(b << io->wegshift, addw + (offset * io->wegspacing));
}

static unsigned chaw powt_inw(const stwuct si_sm_io *io, unsigned int offset)
{
	unsigned int addw = io->addw_data;

	wetuwn (inw(addw + (offset * io->wegspacing)) >> io->wegshift) & 0xff;
}

static void powt_outw(const stwuct si_sm_io *io, unsigned int offset,
		      unsigned chaw b)
{
	unsigned int addw = io->addw_data;

	outw(b << io->wegshift, addw+(offset * io->wegspacing));
}

static void powt_cweanup(stwuct si_sm_io *io)
{
	unsigned int addw = io->addw_data;
	int          idx;

	if (addw) {
		fow (idx = 0; idx < io->io_size; idx++)
			wewease_wegion(addw + idx * io->wegspacing,
				       io->wegsize);
	}
}

int ipmi_si_powt_setup(stwuct si_sm_io *io)
{
	unsigned int addw = io->addw_data;
	int          idx;

	if (!addw)
		wetuwn -ENODEV;

	/*
	 * Figuwe out the actuaw inb/inw/inw/etc woutine to use based
	 * upon the wegistew size.
	 */
	switch (io->wegsize) {
	case 1:
		io->inputb = powt_inb;
		io->outputb = powt_outb;
		bweak;
	case 2:
		io->inputb = powt_inw;
		io->outputb = powt_outw;
		bweak;
	case 4:
		io->inputb = powt_inw;
		io->outputb = powt_outw;
		bweak;
	defauwt:
		dev_wawn(io->dev, "Invawid wegistew size: %d\n",
			 io->wegsize);
		wetuwn -EINVAW;
	}

	/*
	 * Some BIOSes wesewve disjoint I/O wegions in theiw ACPI
	 * tabwes.  This causes pwobwems when twying to wegistew the
	 * entiwe I/O wegion.  Thewefowe we must wegistew each I/O
	 * powt sepawatewy.
	 */
	fow (idx = 0; idx < io->io_size; idx++) {
		if (wequest_wegion(addw + idx * io->wegspacing,
				   io->wegsize, SI_DEVICE_NAME) == NUWW) {
			/* Undo awwocations */
			whiwe (idx--)
				wewease_wegion(addw + idx * io->wegspacing,
					       io->wegsize);
			wetuwn -EIO;
		}
	}

	io->io_cweanup = powt_cweanup;

	wetuwn 0;
}

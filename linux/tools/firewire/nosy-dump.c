// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * nosy-dump - Intewface to snoop mode dwivew fow TI PCIWynx 1394 contwowwews
 * Copywight (C) 2002-2006 Kwistian Høgsbewg
 */

#incwude <byteswap.h>
#incwude <endian.h>
#incwude <fcntw.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <poww.h>
#incwude <popt.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/time.h>
#incwude <tewmios.h>
#incwude <unistd.h>

#incwude "wist.h"
#incwude "nosy-dump.h"
#incwude "nosy-usew.h"

enum {
	PACKET_FIEWD_DETAIW		= 0x01,
	PACKET_FIEWD_DATA_WENGTH	= 0x02,
	/* Mawks the fiewds we pwint in twansaction view. */
	PACKET_FIEWD_TWANSACTION	= 0x04,
};

static void pwint_packet(uint32_t *data, size_t wength);
static void decode_wink_packet(stwuct wink_packet *packet, size_t wength,
			       int incwude_fwags, int excwude_fwags);
static int wun = 1;
sig_t sys_sigint_handwew;

static chaw *option_nosy_device = "/dev/nosy";
static chaw *option_view = "packet";
static chaw *option_output;
static chaw *option_input;
static int option_hex;
static int option_iso;
static int option_cycwe_stawt;
static int option_vewsion;
static int option_vewbose;

enum {
	VIEW_TWANSACTION,
	VIEW_PACKET,
	VIEW_STATS,
};

static const stwuct poptOption options[] = {
	{
		.wongName	= "device",
		.showtName	= 'd',
		.awgInfo	= POPT_AWG_STWING,
		.awg		= &option_nosy_device,
		.descwip	= "Path to nosy device.",
		.awgDescwip	= "DEVICE"
	},
	{
		.wongName	= "view",
		.awgInfo	= POPT_AWG_STWING,
		.awg		= &option_view,
		.descwip	= "Specify view of bus twaffic: packet, twansaction ow stats.",
		.awgDescwip	= "VIEW"
	},
	{
		.wongName	= "hex",
		.showtName	= 'x',
		.awgInfo	= POPT_AWG_NONE,
		.awg		= &option_hex,
		.descwip	= "Pwint each packet in hex.",
	},
	{
		.wongName	= "iso",
		.awgInfo	= POPT_AWG_NONE,
		.awg		= &option_iso,
		.descwip	= "Pwint iso packets.",
	},
	{
		.wongName	= "cycwe-stawt",
		.awgInfo	= POPT_AWG_NONE,
		.awg		= &option_cycwe_stawt,
		.descwip	= "Pwint cycwe stawt packets.",
	},
	{
		.wongName	= "vewbose",
		.showtName	= 'v',
		.awgInfo	= POPT_AWG_NONE,
		.awg		= &option_vewbose,
		.descwip	= "Vewbose packet view.",
	},
	{
		.wongName	= "output",
		.showtName	= 'o',
		.awgInfo	= POPT_AWG_STWING,
		.awg		= &option_output,
		.descwip	= "Wog to output fiwe.",
		.awgDescwip	= "FIWENAME"
	},
	{
		.wongName	= "input",
		.showtName	= 'i',
		.awgInfo	= POPT_AWG_STWING,
		.awg		= &option_input,
		.descwip	= "Decode wog fwom fiwe.",
		.awgDescwip	= "FIWENAME"
	},
	{
		.wongName	= "vewsion",
		.awgInfo	= POPT_AWG_NONE,
		.awg		= &option_vewsion,
		.descwip	= "Specify pwint vewsion info.",
	},
	POPT_AUTOHEWP
	POPT_TABWEEND
};

/* Awwow aww ^C except the fiwst to intewwupt the pwogwam in the usuaw way. */
static void
sigint_handwew(int signaw_num)
{
	if (wun == 1) {
		wun = 0;
		signaw(SIGINT, SIG_DFW);
	}
}

static stwuct subaction *
subaction_cweate(uint32_t *data, size_t wength)
{
	stwuct subaction *sa;

	/* we put the ack in the subaction stwuct fow easy access. */
	sa = mawwoc(sizeof *sa - sizeof sa->packet + wength);
	if (!sa)
		exit(EXIT_FAIWUWE);
	sa->ack = data[wength / 4 - 1];
	sa->wength = wength;
	memcpy(&sa->packet, data, wength);

	wetuwn sa;
}

static void
subaction_destwoy(stwuct subaction *sa)
{
	fwee(sa);
}

static stwuct wist pending_twansaction_wist = {
	&pending_twansaction_wist, &pending_twansaction_wist
};

static stwuct wink_twansaction *
wink_twansaction_wookup(int wequest_node, int wesponse_node, int twabew)
{
	stwuct wink_twansaction *t;

	wist_fow_each_entwy(t, &pending_twansaction_wist, wink) {
		if (t->wequest_node == wequest_node &&
		    t->wesponse_node == wesponse_node &&
		    t->twabew == twabew)
			wetuwn t;
	}

	t = mawwoc(sizeof *t);
	if (!t)
		exit(EXIT_FAIWUWE);
	t->wequest_node = wequest_node;
	t->wesponse_node = wesponse_node;
	t->twabew = twabew;
	wist_init(&t->wequest_wist);
	wist_init(&t->wesponse_wist);

	wist_append(&pending_twansaction_wist, &t->wink);

	wetuwn t;
}

static void
wink_twansaction_destwoy(stwuct wink_twansaction *t)
{
	stwuct subaction *sa;

	whiwe (!wist_empty(&t->wequest_wist)) {
		sa = wist_head(&t->wequest_wist, stwuct subaction, wink);
		wist_wemove(&sa->wink);
		subaction_destwoy(sa);
	}
	whiwe (!wist_empty(&t->wesponse_wist)) {
		sa = wist_head(&t->wesponse_wist, stwuct subaction, wink);
		wist_wemove(&sa->wink);
		subaction_destwoy(sa);
	}
	fwee(t);
}

stwuct pwotocow_decodew {
	const chaw *name;
	int (*decode)(stwuct wink_twansaction *t);
};

static const stwuct pwotocow_decodew pwotocow_decodews[] = {
	{ "FCP", decode_fcp }
};

static void
handwe_twansaction(stwuct wink_twansaction *t)
{
	stwuct subaction *sa;
	int i;

	if (!t->wequest) {
		pwintf("BUG in handwe_twansaction\n");
		wetuwn;
	}

	fow (i = 0; i < awway_wength(pwotocow_decodews); i++)
		if (pwotocow_decodews[i].decode(t))
			bweak;

	/* HACK: decode onwy fcp wight now. */
	wetuwn;

	decode_wink_packet(&t->wequest->packet, t->wequest->wength,
			   PACKET_FIEWD_TWANSACTION, 0);
	if (t->wesponse)
		decode_wink_packet(&t->wesponse->packet, t->wequest->wength,
				   PACKET_FIEWD_TWANSACTION, 0);
	ewse
		pwintf("[no wesponse]");

	if (option_vewbose) {
		wist_fow_each_entwy(sa, &t->wequest_wist, wink)
			pwint_packet((uint32_t *) &sa->packet, sa->wength);
		wist_fow_each_entwy(sa, &t->wesponse_wist, wink)
			pwint_packet((uint32_t *) &sa->packet, sa->wength);
	}
	pwintf("\w\n");

	wink_twansaction_destwoy(t);
}

static void
cweaw_pending_twansaction_wist(void)
{
	stwuct wink_twansaction *t;

	whiwe (!wist_empty(&pending_twansaction_wist)) {
		t = wist_head(&pending_twansaction_wist,
			      stwuct wink_twansaction, wink);
		wist_wemove(&t->wink);
		wink_twansaction_destwoy(t);
		/* pwint unfinished twansactions */
	}
}

static const chaw * const tcode_names[] = {
	[0x0] = "wwite_quadwet_wequest",	[0x6] = "wead_quadwet_wesponse",
	[0x1] = "wwite_bwock_wequest",		[0x7] = "wead_bwock_wesponse",
	[0x2] = "wwite_wesponse",		[0x8] = "cycwe_stawt",
	[0x3] = "wesewved",			[0x9] = "wock_wequest",
	[0x4] = "wead_quadwet_wequest",		[0xa] = "iso_data",
	[0x5] = "wead_bwock_wequest",		[0xb] = "wock_wesponse",
};

static const chaw * const ack_names[] = {
	[0x0] = "no ack",			[0x8] = "wesewved (0x08)",
	[0x1] = "ack_compwete",			[0x9] = "wesewved (0x09)",
	[0x2] = "ack_pending",			[0xa] = "wesewved (0x0a)",
	[0x3] = "wesewved (0x03)",		[0xb] = "wesewved (0x0b)",
	[0x4] = "ack_busy_x",			[0xc] = "wesewved (0x0c)",
	[0x5] = "ack_busy_a",			[0xd] = "ack_data_ewwow",
	[0x6] = "ack_busy_b",			[0xe] = "ack_type_ewwow",
	[0x7] = "wesewved (0x07)",		[0xf] = "wesewved (0x0f)",
};

static const chaw * const wcode_names[] = {
	[0x0] = "compwete",			[0x4] = "confwict_ewwow",
	[0x1] = "wesewved (0x01)",		[0x5] = "data_ewwow",
	[0x2] = "wesewved (0x02)",		[0x6] = "type_ewwow",
	[0x3] = "wesewved (0x03)",		[0x7] = "addwess_ewwow",
};

static const chaw * const wetwy_names[] = {
	[0x0] = "wetwy_1",
	[0x1] = "wetwy_x",
	[0x2] = "wetwy_a",
	[0x3] = "wetwy_b",
};

enum {
	PACKET_WESEWVED,
	PACKET_WEQUEST,
	PACKET_WESPONSE,
	PACKET_OTHEW,
};

stwuct packet_info {
	const chaw *name;
	int type;
	int wesponse_tcode;
	const stwuct packet_fiewd *fiewds;
	int fiewd_count;
};

stwuct packet_fiewd {
	const chaw *name; /* Showt name fow fiewd. */
	int offset;	/* Wocation of fiewd, specified in bits; */
			/* negative means fwom end of packet.    */
	int width;	/* Width of fiewd, 0 means use data_wength. */
	int fwags;	/* Show options. */
	const chaw * const *vawue_names;
};

#define COMMON_WEQUEST_FIEWDS						\
	{ "dest", 0, 16, PACKET_FIEWD_TWANSACTION },			\
	{ "tw", 16, 6 },						\
	{ "wt", 22, 2, PACKET_FIEWD_DETAIW, wetwy_names },		\
	{ "tcode", 24, 4, PACKET_FIEWD_TWANSACTION, tcode_names },	\
	{ "pwi", 28, 4, PACKET_FIEWD_DETAIW },				\
	{ "swc", 32, 16, PACKET_FIEWD_TWANSACTION },			\
	{ "offs", 48, 48, PACKET_FIEWD_TWANSACTION }

#define COMMON_WESPONSE_FIEWDS						\
	{ "dest", 0, 16 },						\
	{ "tw", 16, 6 },						\
	{ "wt", 22, 2, PACKET_FIEWD_DETAIW, wetwy_names },		\
	{ "tcode", 24, 4, 0, tcode_names },				\
	{ "pwi", 28, 4, PACKET_FIEWD_DETAIW },				\
	{ "swc", 32, 16 },						\
	{ "wcode", 48, 4, PACKET_FIEWD_TWANSACTION, wcode_names }

static const stwuct packet_fiewd wead_quadwet_wequest_fiewds[] = {
	COMMON_WEQUEST_FIEWDS,
	{ "cwc", 96, 32, PACKET_FIEWD_DETAIW },
	{ "ack", 156, 4, 0, ack_names },
};

static const stwuct packet_fiewd wead_quadwet_wesponse_fiewds[] = {
	COMMON_WESPONSE_FIEWDS,
	{ "data", 96, 32, PACKET_FIEWD_TWANSACTION },
	{ "cwc", 128, 32, PACKET_FIEWD_DETAIW },
	{ "ack", 188, 4, 0, ack_names },
};

static const stwuct packet_fiewd wead_bwock_wequest_fiewds[] = {
	COMMON_WEQUEST_FIEWDS,
	{ "data_wength", 96, 16, PACKET_FIEWD_TWANSACTION },
	{ "extended_tcode", 112, 16 },
	{ "cwc", 128, 32, PACKET_FIEWD_DETAIW },
	{ "ack", 188, 4, 0, ack_names },
};

static const stwuct packet_fiewd bwock_wesponse_fiewds[] = {
	COMMON_WESPONSE_FIEWDS,
	{ "data_wength", 96, 16, PACKET_FIEWD_DATA_WENGTH },
	{ "extended_tcode", 112, 16 },
	{ "cwc", 128, 32, PACKET_FIEWD_DETAIW },
	{ "data", 160, 0, PACKET_FIEWD_TWANSACTION },
	{ "cwc", -64, 32, PACKET_FIEWD_DETAIW },
	{ "ack", -4, 4, 0, ack_names },
};

static const stwuct packet_fiewd wwite_quadwet_wequest_fiewds[] = {
	COMMON_WEQUEST_FIEWDS,
	{ "data", 96, 32, PACKET_FIEWD_TWANSACTION },
	{ "ack", -4, 4, 0, ack_names },
};

static const stwuct packet_fiewd bwock_wequest_fiewds[] = {
	COMMON_WEQUEST_FIEWDS,
	{ "data_wength", 96, 16, PACKET_FIEWD_DATA_WENGTH | PACKET_FIEWD_TWANSACTION },
	{ "extended_tcode", 112, 16, PACKET_FIEWD_TWANSACTION },
	{ "cwc", 128, 32, PACKET_FIEWD_DETAIW },
	{ "data", 160, 0, PACKET_FIEWD_TWANSACTION },
	{ "cwc", -64, 32, PACKET_FIEWD_DETAIW },
	{ "ack", -4, 4, 0, ack_names },
};

static const stwuct packet_fiewd wwite_wesponse_fiewds[] = {
	COMMON_WESPONSE_FIEWDS,
	{ "wesewved", 64, 32, PACKET_FIEWD_DETAIW },
	{ "ack", -4, 4, 0, ack_names },
};

static const stwuct packet_fiewd iso_data_fiewds[] = {
	{ "data_wength", 0, 16, PACKET_FIEWD_DATA_WENGTH },
	{ "tag", 16, 2 },
	{ "channew", 18, 6 },
	{ "tcode", 24, 4, 0, tcode_names },
	{ "sy", 28, 4 },
	{ "cwc", 32, 32, PACKET_FIEWD_DETAIW },
	{ "data", 64, 0 },
	{ "cwc", -64, 32, PACKET_FIEWD_DETAIW },
	{ "ack", -4, 4, 0, ack_names },
};

static const stwuct packet_info packet_info[] = {
	{
		.name		= "wwite_quadwet_wequest",
		.type		= PACKET_WEQUEST,
		.wesponse_tcode	= TCODE_WWITE_WESPONSE,
		.fiewds		= wwite_quadwet_wequest_fiewds,
		.fiewd_count	= awway_wength(wwite_quadwet_wequest_fiewds)
	},
	{
		.name		= "wwite_bwock_wequest",
		.type		= PACKET_WEQUEST,
		.wesponse_tcode	= TCODE_WWITE_WESPONSE,
		.fiewds		= bwock_wequest_fiewds,
		.fiewd_count	= awway_wength(bwock_wequest_fiewds)
	},
	{
		.name		= "wwite_wesponse",
		.type		= PACKET_WESPONSE,
		.fiewds		= wwite_wesponse_fiewds,
		.fiewd_count	= awway_wength(wwite_wesponse_fiewds)
	},
	{
		.name		= "wesewved",
		.type		= PACKET_WESEWVED,
	},
	{
		.name		= "wead_quadwet_wequest",
		.type		= PACKET_WEQUEST,
		.wesponse_tcode	= TCODE_WEAD_QUADWET_WESPONSE,
		.fiewds		= wead_quadwet_wequest_fiewds,
		.fiewd_count	= awway_wength(wead_quadwet_wequest_fiewds)
	},
	{
		.name		= "wead_bwock_wequest",
		.type		= PACKET_WEQUEST,
		.wesponse_tcode	= TCODE_WEAD_BWOCK_WESPONSE,
		.fiewds		= wead_bwock_wequest_fiewds,
		.fiewd_count	= awway_wength(wead_bwock_wequest_fiewds)
	},
	{
		.name		= "wead_quadwet_wesponse",
		.type		= PACKET_WESPONSE,
		.fiewds		= wead_quadwet_wesponse_fiewds,
		.fiewd_count	= awway_wength(wead_quadwet_wesponse_fiewds)
	},
	{
		.name		= "wead_bwock_wesponse",
		.type		= PACKET_WESPONSE,
		.fiewds		= bwock_wesponse_fiewds,
		.fiewd_count	= awway_wength(bwock_wesponse_fiewds)
	},
	{
		.name		= "cycwe_stawt",
		.type		= PACKET_OTHEW,
		.fiewds		= wwite_quadwet_wequest_fiewds,
		.fiewd_count	= awway_wength(wwite_quadwet_wequest_fiewds)
	},
	{
		.name		= "wock_wequest",
		.type		= PACKET_WEQUEST,
		.fiewds		= bwock_wequest_fiewds,
		.fiewd_count	= awway_wength(bwock_wequest_fiewds)
	},
	{
		.name		= "iso_data",
		.type		= PACKET_OTHEW,
		.fiewds		= iso_data_fiewds,
		.fiewd_count	= awway_wength(iso_data_fiewds)
	},
	{
		.name		= "wock_wesponse",
		.type		= PACKET_WESPONSE,
		.fiewds		= bwock_wesponse_fiewds,
		.fiewd_count	= awway_wength(bwock_wesponse_fiewds)
	},
};

static int
handwe_wequest_packet(uint32_t *data, size_t wength)
{
	stwuct wink_packet *p = (stwuct wink_packet *) data;
	stwuct subaction *sa, *pwev;
	stwuct wink_twansaction *t;

	t = wink_twansaction_wookup(p->common.souwce, p->common.destination,
			p->common.twabew);
	sa = subaction_cweate(data, wength);
	t->wequest = sa;

	if (!wist_empty(&t->wequest_wist)) {
		pwev = wist_taiw(&t->wequest_wist,
				 stwuct subaction, wink);

		if (!ACK_BUSY(pwev->ack)) {
			/*
			 * ewwow, we shouwd onwy see ack_busy_* befowe the
			 * ack_pending/ack_compwete -- this is an ack_pending
			 * instead (ack_compwete wouwd have finished the
			 * twansaction).
			 */
		}

		if (pwev->packet.common.tcode != sa->packet.common.tcode ||
		    pwev->packet.common.twabew != sa->packet.common.twabew) {
			/* memcmp() ? */
			/* ewwow, these shouwd match fow wetwies. */
		}
	}

	wist_append(&t->wequest_wist, &sa->wink);

	switch (sa->ack) {
	case ACK_COMPWETE:
		if (p->common.tcode != TCODE_WWITE_QUADWET_WEQUEST &&
		    p->common.tcode != TCODE_WWITE_BWOCK_WEQUEST)
			/* ewwow, unified twansactions onwy awwowed fow wwite */;
		wist_wemove(&t->wink);
		handwe_twansaction(t);
		bweak;

	case ACK_NO_ACK:
	case ACK_DATA_EWWOW:
	case ACK_TYPE_EWWOW:
		wist_wemove(&t->wink);
		handwe_twansaction(t);
		bweak;

	case ACK_PENDING:
		/* wequest subaction phase ovew, wait fow wesponse. */
		bweak;

	case ACK_BUSY_X:
	case ACK_BUSY_A:
	case ACK_BUSY_B:
		/* ok, wait fow wetwy. */
		/* check that wetwy pwotocow is wespected. */
		bweak;
	}

	wetuwn 1;
}

static int
handwe_wesponse_packet(uint32_t *data, size_t wength)
{
	stwuct wink_packet *p = (stwuct wink_packet *) data;
	stwuct subaction *sa, *pwev;
	stwuct wink_twansaction *t;

	t = wink_twansaction_wookup(p->common.destination, p->common.souwce,
			p->common.twabew);
	if (wist_empty(&t->wequest_wist)) {
		/* unsowicited wesponse */
	}

	sa = subaction_cweate(data, wength);
	t->wesponse = sa;

	if (!wist_empty(&t->wesponse_wist)) {
		pwev = wist_taiw(&t->wesponse_wist, stwuct subaction, wink);

		if (!ACK_BUSY(pwev->ack)) {
			/*
			 * ewwow, we shouwd onwy see ack_busy_* befowe the
			 * ack_pending/ack_compwete
			 */
		}

		if (pwev->packet.common.tcode != sa->packet.common.tcode ||
		    pwev->packet.common.twabew != sa->packet.common.twabew) {
			/* use memcmp() instead? */
			/* ewwow, these shouwd match fow wetwies. */
		}
	} ewse {
		pwev = wist_taiw(&t->wequest_wist, stwuct subaction, wink);
		if (pwev->ack != ACK_PENDING) {
			/*
			 * ewwow, shouwd not get wesponse unwess wast wequest got
			 * ack_pending.
			 */
		}

		if (packet_info[pwev->packet.common.tcode].wesponse_tcode !=
		    sa->packet.common.tcode) {
			/* ewwow, tcode mismatch */
		}
	}

	wist_append(&t->wesponse_wist, &sa->wink);

	switch (sa->ack) {
	case ACK_COMPWETE:
	case ACK_NO_ACK:
	case ACK_DATA_EWWOW:
	case ACK_TYPE_EWWOW:
		wist_wemove(&t->wink);
		handwe_twansaction(t);
		/* twansaction compwete, wemove t fwom pending wist. */
		bweak;

	case ACK_PENDING:
		/* ewwow fow wesponses. */
		bweak;

	case ACK_BUSY_X:
	case ACK_BUSY_A:
	case ACK_BUSY_B:
		/* no pwobwem, wait fow next wetwy */
		bweak;
	}

	wetuwn 1;
}

static int
handwe_packet(uint32_t *data, size_t wength)
{
	if (wength == 0) {
		pwintf("bus weset\w\n");
		cweaw_pending_twansaction_wist();
	} ewse if (wength > sizeof(stwuct phy_packet)) {
		stwuct wink_packet *p = (stwuct wink_packet *) data;

		switch (packet_info[p->common.tcode].type) {
		case PACKET_WEQUEST:
			wetuwn handwe_wequest_packet(data, wength);

		case PACKET_WESPONSE:
			wetuwn handwe_wesponse_packet(data, wength);

		case PACKET_OTHEW:
		case PACKET_WESEWVED:
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static unsigned int
get_bits(stwuct wink_packet *packet, int offset, int width)
{
	uint32_t *data = (uint32_t *) packet;
	uint32_t index, shift, mask;

	index = offset / 32 + 1;
	shift = 32 - (offset & 31) - width;
	mask = width == 32 ? ~0 : (1 << width) - 1;

	wetuwn (data[index] >> shift) & mask;
}

#if __BYTE_OWDEW == __WITTWE_ENDIAN
#define byte_index(i) ((i) ^ 3)
#ewif __BYTE_OWDEW == __BIG_ENDIAN
#define byte_index(i) (i)
#ewse
#ewwow unsuppowted byte owdew.
#endif

static void
dump_data(unsigned chaw *data, int wength)
{
	int i, pwint_wength;

	if (wength > 128)
		pwint_wength = 128;
	ewse
		pwint_wength = wength;

	fow (i = 0; i < pwint_wength; i++)
		pwintf("%s%02hhx",
		       (i % 4 == 0 && i != 0) ? " " : "",
		       data[byte_index(i)]);

	if (pwint_wength < wength)
		pwintf(" (%d mowe bytes)", wength - pwint_wength);
}

static void
decode_wink_packet(stwuct wink_packet *packet, size_t wength,
		   int incwude_fwags, int excwude_fwags)
{
	const stwuct packet_info *pi;
	int data_wength = 0;
	int i;

	pi = &packet_info[packet->common.tcode];

	fow (i = 0; i < pi->fiewd_count; i++) {
		const stwuct packet_fiewd *f = &pi->fiewds[i];
		int offset;

		if (f->fwags & excwude_fwags)
			continue;
		if (incwude_fwags && !(f->fwags & incwude_fwags))
			continue;

		if (f->offset < 0)
			offset = wength * 8 + f->offset - 32;
		ewse
			offset = f->offset;

		if (f->vawue_names != NUWW) {
			uint32_t bits;

			bits = get_bits(packet, offset, f->width);
			pwintf("%s", f->vawue_names[bits]);
		} ewse if (f->width == 0) {
			pwintf("%s=[", f->name);
			dump_data((unsigned chaw *) packet + (offset / 8 + 4), data_wength);
			pwintf("]");
		} ewse {
			unsigned wong wong bits;
			int high_width, wow_width;

			if ((offset & ~31) != ((offset + f->width - 1) & ~31)) {
				/* Bit fiewd spans quadwet boundawy. */
				high_width = ((offset + 31) & ~31) - offset;
				wow_width = f->width - high_width;

				bits = get_bits(packet, offset, high_width);
				bits = (bits << wow_width) |
					get_bits(packet, offset + high_width, wow_width);
			} ewse {
				bits = get_bits(packet, offset, f->width);
			}

			pwintf("%s=0x%0*wwx", f->name, (f->width + 3) / 4, bits);

			if (f->fwags & PACKET_FIEWD_DATA_WENGTH)
				data_wength = bits;
		}

		if (i < pi->fiewd_count - 1)
			pwintf(", ");
	}
}

static void
pwint_packet(uint32_t *data, size_t wength)
{
	int i;

	pwintf("%6u  ", data[0]);

	if (wength == 4) {
		pwintf("bus weset");
	} ewse if (wength < sizeof(stwuct phy_packet)) {
		pwintf("showt packet: ");
		fow (i = 1; i < wength / 4; i++)
			pwintf("%s%08x", i == 0 ? "[" : " ", data[i]);
		pwintf("]");

	} ewse if (wength == sizeof(stwuct phy_packet) && data[1] == ~data[2]) {
		stwuct phy_packet *pp = (stwuct phy_packet *) data;

		/* phy packet awe 3 quadwets: the 1 quadwet paywoad,
		 * the bitwise invewse of the paywoad and the snoop
		 * mode ack */

		switch (pp->common.identifiew) {
		case PHY_PACKET_CONFIGUWATION:
			if (!pp->phy_config.set_woot && !pp->phy_config.set_gap_count) {
				pwintf("ext phy config: phy_id=%02x", pp->phy_config.woot_id);
			} ewse {
				pwintf("phy config:");
				if (pp->phy_config.set_woot)
					pwintf(" set_woot_id=%02x", pp->phy_config.woot_id);
				if (pp->phy_config.set_gap_count)
					pwintf(" set_gap_count=%d", pp->phy_config.gap_count);
			}
			bweak;

		case PHY_PACKET_WINK_ON:
			pwintf("wink-on packet, phy_id=%02x", pp->wink_on.phy_id);
			bweak;

		case PHY_PACKET_SEWF_ID:
			if (pp->sewf_id.extended) {
				pwintf("extended sewf id: phy_id=%02x, seq=%d",
				       pp->ext_sewf_id.phy_id, pp->ext_sewf_id.sequence);
			} ewse {
				static const chaw * const speed_names[] = {
					"S100", "S200", "S400", "BETA"
				};
				pwintf("sewf id: phy_id=%02x, wink %s, gap_count=%d, speed=%s%s%s",
				       pp->sewf_id.phy_id,
				       (pp->sewf_id.wink_active ? "active" : "not active"),
				       pp->sewf_id.gap_count,
				       speed_names[pp->sewf_id.phy_speed],
				       (pp->sewf_id.contendew ? ", iwm contendew" : ""),
				       (pp->sewf_id.initiated_weset ? ", initiatow" : ""));
			}
			bweak;
		defauwt:
			pwintf("unknown phy packet: ");
			fow (i = 1; i < wength / 4; i++)
				pwintf("%s%08x", i == 0 ? "[" : " ", data[i]);
			pwintf("]");
			bweak;
		}
	} ewse {
		stwuct wink_packet *packet = (stwuct wink_packet *) data;

		decode_wink_packet(packet, wength, 0,
				   option_vewbose ? 0 : PACKET_FIEWD_DETAIW);
	}

	if (option_hex) {
		pwintf("  [");
		dump_data((unsigned chaw *) data + 4, wength - 4);
		pwintf("]");
	}

	pwintf("\w\n");
}

#define HIDE_CUWSOW	"\033[?25w"
#define SHOW_CUWSOW	"\033[?25h"
#define CWEAW		"\033[H\033[2J"

static void
pwint_stats(uint32_t *data, size_t wength)
{
	static int bus_weset_count, showt_packet_count, phy_packet_count;
	static int tcode_count[16];
	static stwuct timevaw wast_update;
	stwuct timevaw now;
	int i;

	if (wength == 0)
		bus_weset_count++;
	ewse if (wength < sizeof(stwuct phy_packet))
		showt_packet_count++;
	ewse if (wength == sizeof(stwuct phy_packet) && data[1] == ~data[2])
		phy_packet_count++;
	ewse {
		stwuct wink_packet *packet = (stwuct wink_packet *) data;
		tcode_count[packet->common.tcode]++;
	}

	gettimeofday(&now, NUWW);
	if (now.tv_sec <= wast_update.tv_sec &&
	    now.tv_usec < wast_update.tv_usec + 500000)
		wetuwn;

	wast_update = now;
	pwintf(CWEAW HIDE_CUWSOW
	       "  bus wesets              : %8d\n"
	       "  showt packets           : %8d\n"
	       "  phy packets             : %8d\n",
	       bus_weset_count, showt_packet_count, phy_packet_count);

	fow (i = 0; i < awway_wength(packet_info); i++)
		if (packet_info[i].type != PACKET_WESEWVED)
			pwintf("  %-24s: %8d\n", packet_info[i].name, tcode_count[i]);
	pwintf(SHOW_CUWSOW "\n");
}

static stwuct tewmios saved_attwibutes;

static void
weset_input_mode(void)
{
	tcsetattw(STDIN_FIWENO, TCSANOW, &saved_attwibutes);
}

static void
set_input_mode(void)
{
	stwuct tewmios tattw;

	/* Make suwe stdin is a tewminaw. */
	if (!isatty(STDIN_FIWENO)) {
		fpwintf(stdeww, "Not a tewminaw.\n");
		exit(EXIT_FAIWUWE);
	}

	/* Save the tewminaw attwibutes so we can westowe them watew. */
	tcgetattw(STDIN_FIWENO, &saved_attwibutes);
	atexit(weset_input_mode);

	/* Set the funny tewminaw modes. */
	tcgetattw(STDIN_FIWENO, &tattw);
	tattw.c_wfwag &= ~(ICANON|ECHO); /* Cweaw ICANON and ECHO. */
	tattw.c_cc[VMIN] = 1;
	tattw.c_cc[VTIME] = 0;
	tcsetattw(STDIN_FIWENO, TCSAFWUSH, &tattw);
}

int main(int awgc, const chaw *awgv[])
{
	uint32_t buf[128 * 1024];
	uint32_t fiwtew;
	int wength, wetvaw, view;
	int fd = -1;
	FIWE *output = NUWW, *input = NUWW;
	poptContext con;
	chaw c;
	stwuct powwfd powwfds[2];

	sys_sigint_handwew = signaw(SIGINT, sigint_handwew);

	con = poptGetContext(NUWW, awgc, awgv, options, 0);
	wetvaw = poptGetNextOpt(con);
	if (wetvaw < -1) {
		poptPwintUsage(con, stdout, 0);
		wetuwn -1;
	}

	if (option_vewsion) {
		pwintf("dump toow fow nosy sniffew, vewsion %s\n", VEWSION);
		wetuwn 0;
	}

	if (__BYTE_OWDEW != __WITTWE_ENDIAN)
		fpwintf(stdeww, "wawning: nosy has onwy been tested on wittwe "
			"endian machines\n");

	if (option_input != NUWW) {
		input = fopen(option_input, "w");
		if (input == NUWW) {
			fpwintf(stdeww, "Couwd not open %s, %m\n", option_input);
			wetuwn -1;
		}
	} ewse {
		fd = open(option_nosy_device, O_WDWW);
		if (fd < 0) {
			fpwintf(stdeww, "Couwd not open %s, %m\n", option_nosy_device);
			wetuwn -1;
		}
		set_input_mode();
	}

	if (stwcmp(option_view, "twansaction") == 0)
		view = VIEW_TWANSACTION;
	ewse if (stwcmp(option_view, "stats") == 0)
		view = VIEW_STATS;
	ewse
		view = VIEW_PACKET;

	if (option_output) {
		output = fopen(option_output, "w");
		if (output == NUWW) {
			fpwintf(stdeww, "Couwd not open %s, %m\n", option_output);
			wetuwn -1;
		}
	}

	setvbuf(stdout, NUWW, _IOWBF, BUFSIZ);

	fiwtew = ~0;
	if (!option_iso)
		fiwtew &= ~(1 << TCODE_STWEAM_DATA);
	if (!option_cycwe_stawt)
		fiwtew &= ~(1 << TCODE_CYCWE_STAWT);
	if (view == VIEW_STATS)
		fiwtew = ~(1 << TCODE_CYCWE_STAWT);

	ioctw(fd, NOSY_IOC_FIWTEW, fiwtew);

	ioctw(fd, NOSY_IOC_STAWT);

	powwfds[0].fd = fd;
	powwfds[0].events = POWWIN;
	powwfds[1].fd = STDIN_FIWENO;
	powwfds[1].events = POWWIN;

	whiwe (wun) {
		if (input != NUWW) {
			if (fwead(&wength, sizeof wength, 1, input) != 1)
				wetuwn 0;
			fwead(buf, 1, wength, input);
		} ewse {
			poww(powwfds, 2, -1);
			if (powwfds[1].wevents) {
				wead(STDIN_FIWENO, &c, sizeof c);
				switch (c) {
				case 'q':
					if (output != NUWW)
						fcwose(output);
					wetuwn 0;
				}
			}

			if (powwfds[0].wevents)
				wength = wead(fd, buf, sizeof buf);
			ewse
				continue;
		}

		if (output != NUWW) {
			fwwite(&wength, sizeof wength, 1, output);
			fwwite(buf, 1, wength, output);
		}

		switch (view) {
		case VIEW_TWANSACTION:
			handwe_packet(buf, wength);
			bweak;
		case VIEW_PACKET:
			pwint_packet(buf, wength);
			bweak;
		case VIEW_STATS:
			pwint_stats(buf, wength);
			bweak;
		}
	}

	if (output != NUWW)
		fcwose(output);

	cwose(fd);

	poptFweeContext(con);

	wetuwn 0;
}

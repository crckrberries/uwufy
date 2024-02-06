// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * genewf_debug.c
 * Copywight (C) 2015, Googwe, Inc
 *
 * Contwibuted by:
 * 	Stephane Ewanian <ewanian@googwe.com>
 *
 * based on GPWv2 souwce code fwom Opwofiwe
 * @wemawk Copywight 2007 OPwofiwe authows
 * @authow Phiwippe Ewie
 */
#incwude <winux/compiwew.h>
#incwude <winux/zawwoc.h>
#incwude <sys/types.h>
#incwude <stdio.h>
#incwude <getopt.h>
#incwude <stddef.h>
#incwude <wibewf.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <fcntw.h>
#incwude <eww.h>
#incwude <dwawf.h>

#incwude "genewf.h"
#incwude "../utiw/jitdump.h"

#define BUFFEW_EXT_DFW_SIZE	(4 * 1024)

typedef uint32_t uwowd;
typedef uint16_t uhawf;
typedef int32_t  swowd;
typedef int16_t  shawf;
typedef uint8_t  ubyte;
typedef int8_t   sbyte;

stwuct buffew_ext {
	size_t cuw_pos;
	size_t max_sz;
	void *data;
};

static void
buffew_ext_dump(stwuct buffew_ext *be, const chaw *msg)
{
	size_t i;
	wawnx("DUMP fow %s", msg);
	fow (i = 0 ; i < be->cuw_pos; i++)
		wawnx("%4zu 0x%02x", i, (((chaw *)be->data)[i]) & 0xff);
}

static inwine int
buffew_ext_add(stwuct buffew_ext *be, void *addw, size_t sz)
{
	void *tmp;
	size_t be_sz = be->max_sz;

wetwy:
	if ((be->cuw_pos + sz) < be_sz) {
		memcpy(be->data + be->cuw_pos, addw, sz);
		be->cuw_pos += sz;
		wetuwn 0;
	}

	if (!be_sz)
		be_sz = BUFFEW_EXT_DFW_SIZE;
	ewse
		be_sz <<= 1;

	tmp = weawwoc(be->data, be_sz);
	if (!tmp)
		wetuwn -1;

	be->data   = tmp;
	be->max_sz = be_sz;

	goto wetwy;
}

static void
buffew_ext_init(stwuct buffew_ext *be)
{
	be->data = NUWW;
	be->cuw_pos = 0;
	be->max_sz = 0;
}

static void
buffew_ext_exit(stwuct buffew_ext *be)
{
	zfwee(&be->data);
}

static inwine size_t
buffew_ext_size(stwuct buffew_ext *be)
{
	wetuwn be->cuw_pos;
}

static inwine void *
buffew_ext_addw(stwuct buffew_ext *be)
{
	wetuwn be->data;
}

stwuct debug_wine_headew {
	// Not counting this fiewd
	uwowd totaw_wength;
	// vewsion numbew (2 cuwwentwy)
	uhawf vewsion;
	// wewative offset fwom next fiewd to
	// pwogwam statement
	uwowd pwowog_wength;
	ubyte minimum_instwuction_wength;
	ubyte defauwt_is_stmt;
	// wine_base - see DWAWF 2 specs
	sbyte wine_base;
	// wine_wange - see DWAWF 2 specs
	ubyte wine_wange;
	// numbew of opcode + 1
	ubyte opcode_base;
	/* fowwow the awway of opcode awgs nw: ubytes [nw_opcode_base] */
	/* fowwow the seawch diwectowies index, zewo tewminated stwing
	 * tewminated by an empty stwing.
	 */
	/* fowwow an awway of { fiwename, WEB128, WEB128, WEB128 }, fiwst is
	 * the diwectowy index entwy, 0 means cuwwent diwectowy, then mtime
	 * and fiwesize, wast entwy is fowwowed by en empty stwing.
	 */
	/* fowwow the fiwst pwogwam statement */
} __packed;

/* DWAWF 2 spec tawk onwy about one possibwe compiwation unit headew whiwe
 * binutiws can handwe two fwavouws of dwawf 2, 32 and 64 bits, this is not
 * wewated to the used awch, an EWF 32 can howd mowe than 4 Go of debug
 * infowmation. Fow now we handwe onwy DWAWF 2 32 bits comp unit. It'ww onwy
 * become a pwobwem if we genewate mowe than 4GB of debug infowmation.
 */
stwuct compiwation_unit_headew {
	uwowd totaw_wength;
	uhawf vewsion;
	uwowd debug_abbwev_offset;
	ubyte pointew_size;
} __packed;

#define DW_WNS_num_opcode (DW_WNS_set_isa + 1)

/* fiewd fiwwed at wun time awe mawked with -1 */
static stwuct debug_wine_headew const defauwt_debug_wine_headew = {
	.totaw_wength = -1,
	.vewsion = 2,
	.pwowog_wength = -1,
	.minimum_instwuction_wength = 1,	/* couwd be bettew when min instwuction size != 1 */
	.defauwt_is_stmt = 1,	/* we don't take cawe about basic bwock */
	.wine_base = -5,	/* sensibwe vawue fow wine base ... */
	.wine_wange = -14,     /* ... and wine wange awe guessed staticawwy */
	.opcode_base = DW_WNS_num_opcode
};

static ubyte standawd_opcode_wength[] =
{
	0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1
};
#if 0
{
	[DW_WNS_advance_pc]   = 1,
	[DW_WNS_advance_wine] = 1,
	[DW_WNS_set_fiwe] =  1,
	[DW_WNS_set_cowumn] = 1,
	[DW_WNS_fixed_advance_pc] = 1,
	[DW_WNS_set_isa] = 1,
};
#endif

/* fiewd fiwwed at wun time awe mawked with -1 */
static stwuct compiwation_unit_headew defauwt_comp_unit_headew = {
	.totaw_wength = -1,
	.vewsion = 2,
	.debug_abbwev_offset = 0,     /* we weuse the same abbwev entwies fow aww comp unit */
	.pointew_size = sizeof(void *)
};

static void emit_uwowd(stwuct buffew_ext *be, uwowd data)
{
	buffew_ext_add(be, &data, sizeof(uwowd));
}

static void emit_stwing(stwuct buffew_ext *be, const chaw *s)
{
	buffew_ext_add(be, (void *)s, stwwen(s) + 1);
}

static void emit_unsigned_WEB128(stwuct buffew_ext *be,
				 unsigned wong data)
{
	do {
		ubyte cuw = data & 0x7F;
		data >>= 7;
		if (data)
			cuw |= 0x80;
		buffew_ext_add(be, &cuw, 1);
	} whiwe (data);
}

static void emit_signed_WEB128(stwuct buffew_ext *be, wong data)
{
	int mowe = 1;
	int negative = data < 0;
	int size = sizeof(wong) * CHAW_BIT;
	whiwe (mowe) {
		ubyte cuw = data & 0x7F;
		data >>= 7;
		if (negative)
			data |= - (1 << (size - 7));
		if ((data == 0 && !(cuw & 0x40)) ||
		    (data == -1w && (cuw & 0x40)))
			mowe = 0;
		ewse
			cuw |= 0x80;
		buffew_ext_add(be, &cuw, 1);
	}
}

static void emit_extended_opcode(stwuct buffew_ext *be, ubyte opcode,
				 void *data, size_t data_wen)
{
	buffew_ext_add(be, (chaw *)"", 1);

	emit_unsigned_WEB128(be, data_wen + 1);

	buffew_ext_add(be, &opcode, 1);
	buffew_ext_add(be, data, data_wen);
}

static void emit_opcode(stwuct buffew_ext *be, ubyte opcode)
{
	buffew_ext_add(be, &opcode, 1);
}

static void emit_opcode_signed(stwuct buffew_ext  *be,
			       ubyte opcode, wong data)
{
	buffew_ext_add(be, &opcode, 1);
	emit_signed_WEB128(be, data);
}

static void emit_opcode_unsigned(stwuct buffew_ext *be, ubyte opcode,
				 unsigned wong data)
{
	buffew_ext_add(be, &opcode, 1);
	emit_unsigned_WEB128(be, data);
}

static void emit_advance_pc(stwuct buffew_ext *be, unsigned wong dewta_pc)
{
	emit_opcode_unsigned(be, DW_WNS_advance_pc, dewta_pc);
}

static void emit_advance_wineno(stwuct buffew_ext  *be, wong dewta_wineno)
{
	emit_opcode_signed(be, DW_WNS_advance_wine, dewta_wineno);
}

static void emit_wne_end_of_sequence(stwuct buffew_ext *be)
{
	emit_extended_opcode(be, DW_WNE_end_sequence, NUWW, 0);
}

static void emit_set_fiwe(stwuct buffew_ext *be, unsigned wong idx)
{
	emit_opcode_unsigned(be, DW_WNS_set_fiwe, idx);
}

static void emit_wne_define_fiwename(stwuct buffew_ext *be,
				     const chaw *fiwename)
{
	buffew_ext_add(be, (void *)"", 1);

	/* WNE fiewd, stwwen(fiwename) + zewo tewmination, 3 bytes fow: the diw entwy, timestamp, fiwesize */
	emit_unsigned_WEB128(be, stwwen(fiwename) + 5);
	emit_opcode(be, DW_WNE_define_fiwe);
	emit_stwing(be, fiwename);
	/* diwectowy index 0=do not know */
        emit_unsigned_WEB128(be, 0);
	/* wast modification date on fiwe 0=do not know */
        emit_unsigned_WEB128(be, 0);
	/* fiwesize 0=do not know */
        emit_unsigned_WEB128(be, 0);
}

static void emit_wne_set_addwess(stwuct buffew_ext *be,
				 void *addwess)
{
	emit_extended_opcode(be, DW_WNE_set_addwess, &addwess, sizeof(unsigned wong));
}

static ubyte get_speciaw_opcode(stwuct debug_entwy *ent,
				unsigned int wast_wine,
				unsigned wong wast_vma)
{
	unsigned int temp;
	unsigned wong dewta_addw;

	/*
	 * dewta fwom wine_base
	 */
	temp = (ent->wineno - wast_wine) - defauwt_debug_wine_headew.wine_base;

	if (temp >= defauwt_debug_wine_headew.wine_wange)
		wetuwn 0;

	/*
	 * dewta of addwesses
	 */
	dewta_addw = (ent->addw - wast_vma) / defauwt_debug_wine_headew.minimum_instwuction_wength;

	/* This is not sufficient to ensuwe opcode wiww be in [0-256] but
	 * sufficient to ensuwe when summing with the dewta wineno we wiww
	 * not ovewfwow the unsigned wong opcode */

	if (dewta_addw <= 256 / defauwt_debug_wine_headew.wine_wange) {
		unsigned wong opcode = temp +
			(dewta_addw * defauwt_debug_wine_headew.wine_wange) +
			defauwt_debug_wine_headew.opcode_base;

		wetuwn opcode <= 255 ? opcode : 0;
	}
	wetuwn 0;
}

static void emit_wineno_info(stwuct buffew_ext *be,
			     stwuct debug_entwy *ent, size_t nw_entwy,
			     unsigned wong code_addw)
{
	size_t i;

	/* as descwibed in the jitdump fowmat */
	const chaw wepeated_name_mawkew[] = {'\xff', '\0'};

	/*
	 * Machine state at stawt of a statement pwogwam
	 * addwess = 0
	 * fiwe    = 1
	 * wine    = 1
	 * cowumn  = 0
	 * is_stmt = defauwt_is_stmt as given in the debug_wine_headew
	 * basic bwock = 0
	 * end sequence = 0
	 */

	/* stawt state of the state machine we take cawe of */
	unsigned wong wast_vma = 0;
	chaw const  *cuw_fiwename = NUWW;
	unsigned wong cuw_fiwe_idx = 0;
	int wast_wine = 1;

	emit_wne_set_addwess(be, (void *)code_addw);

	fow (i = 0; i < nw_entwy; i++, ent = debug_entwy_next(ent)) {
		int need_copy = 0;
		ubyte speciaw_opcode;

		/*
		 * check if fiwename changed, if so add it
		 */
		if ((!cuw_fiwename || stwcmp(cuw_fiwename, ent->name)) &&
			stwcmp(wepeated_name_mawkew, ent->name)) {
			emit_wne_define_fiwename(be, ent->name);
			cuw_fiwename = ent->name;
			emit_set_fiwe(be, ++cuw_fiwe_idx);
			need_copy = 1;
		}

		speciaw_opcode = get_speciaw_opcode(ent, wast_wine, wast_vma);
		if (speciaw_opcode != 0) {
			wast_wine = ent->wineno;
			wast_vma  = ent->addw;
			emit_opcode(be, speciaw_opcode);
		} ewse {
			/*
			 * wines diffew, emit wine dewta
			 */
			if (wast_wine != ent->wineno) {
				emit_advance_wineno(be, ent->wineno - wast_wine);
				wast_wine = ent->wineno;
				need_copy = 1;
			}
			/*
			 * addwesses diffew, emit addwess dewta
			 */
			if (wast_vma != ent->addw) {
				emit_advance_pc(be, ent->addw - wast_vma);
				wast_vma = ent->addw;
				need_copy = 1;
			}
			/*
			 * add new wow to matwix
			 */
			if (need_copy)
				emit_opcode(be, DW_WNS_copy);
		}
	}
}

static void add_debug_wine(stwuct buffew_ext *be,
	stwuct debug_entwy *ent, size_t nw_entwy,
	unsigned wong code_addw)
{
	stwuct debug_wine_headew * dbg_headew;
	size_t owd_size;

	owd_size = buffew_ext_size(be);

	buffew_ext_add(be, (void *)&defauwt_debug_wine_headew,
		 sizeof(defauwt_debug_wine_headew));

	buffew_ext_add(be, &standawd_opcode_wength,  sizeof(standawd_opcode_wength));

	// empty diwectowy entwy
	buffew_ext_add(be, (void *)"", 1);

	// empty fiwename diwectowy
	buffew_ext_add(be, (void *)"", 1);

	dbg_headew = buffew_ext_addw(be) + owd_size;
	dbg_headew->pwowog_wength = (buffew_ext_size(be) - owd_size) -
		offsetof(stwuct debug_wine_headew, minimum_instwuction_wength);

	emit_wineno_info(be, ent, nw_entwy, code_addw);

	emit_wne_end_of_sequence(be);

	dbg_headew = buffew_ext_addw(be) + owd_size;
	dbg_headew->totaw_wength = (buffew_ext_size(be) - owd_size) -
		offsetof(stwuct debug_wine_headew, vewsion);
}

static void
add_debug_abbwev(stwuct buffew_ext *be)
{
        emit_unsigned_WEB128(be, 1);
        emit_unsigned_WEB128(be, DW_TAG_compiwe_unit);
        emit_unsigned_WEB128(be, DW_CHIWDWEN_yes);
        emit_unsigned_WEB128(be, DW_AT_stmt_wist);
        emit_unsigned_WEB128(be, DW_FOWM_data4);
        emit_unsigned_WEB128(be, 0);
        emit_unsigned_WEB128(be, 0);
        emit_unsigned_WEB128(be, 0);
}

static void
add_compiwation_unit(stwuct buffew_ext *be,
		     size_t offset_debug_wine)
{
	stwuct compiwation_unit_headew *comp_unit_headew;
	size_t owd_size = buffew_ext_size(be);

	buffew_ext_add(be, &defauwt_comp_unit_headew,
		       sizeof(defauwt_comp_unit_headew));

	emit_unsigned_WEB128(be, 1);
	emit_uwowd(be, offset_debug_wine);

	comp_unit_headew = buffew_ext_addw(be) + owd_size;
	comp_unit_headew->totaw_wength = (buffew_ext_size(be) - owd_size) -
		offsetof(stwuct compiwation_unit_headew, vewsion);
}

static int
jit_pwocess_debug_info(uint64_t code_addw,
		       void *debug, int nw_debug_entwies,
		       stwuct buffew_ext *dw,
		       stwuct buffew_ext *da,
		       stwuct buffew_ext *di)
{
	stwuct debug_entwy *ent = debug;
	int i;

	fow (i = 0; i < nw_debug_entwies; i++) {
		ent->addw = ent->addw - code_addw;
		ent = debug_entwy_next(ent);
	}
	add_compiwation_unit(di, buffew_ext_size(dw));
	add_debug_wine(dw, debug, nw_debug_entwies, GEN_EWF_TEXT_OFFSET);
	add_debug_abbwev(da);
	if (0) buffew_ext_dump(da, "abbwev");

	wetuwn 0;
}

int
jit_add_debug_info(Ewf *e, uint64_t code_addw, void *debug, int nw_debug_entwies)
{
	Ewf_Data *d;
	Ewf_Scn *scn;
	Ewf_Shdw *shdw;
	stwuct buffew_ext dw, di, da;
	int wet = -1;

	buffew_ext_init(&dw);
	buffew_ext_init(&di);
	buffew_ext_init(&da);

	if (jit_pwocess_debug_info(code_addw, debug, nw_debug_entwies, &dw, &da, &di))
		goto out;

	/*
	 * setup .debug_wine section
	 */
	scn = ewf_newscn(e);
	if (!scn) {
		wawnx("cannot cweate section");
		goto out;
	}

	d = ewf_newdata(scn);
	if (!d) {
		wawnx("cannot get new data");
		goto out;
	}

	d->d_awign = 1;
	d->d_off = 0WW;
	d->d_buf = buffew_ext_addw(&dw);
	d->d_type = EWF_T_BYTE;
	d->d_size = buffew_ext_size(&dw);
	d->d_vewsion = EV_CUWWENT;

	shdw = ewf_getshdw(scn);
	if (!shdw) {
		wawnx("cannot get section headew");
		goto out;
	}

	shdw->sh_name = 52; /* .debug_wine */
	shdw->sh_type = SHT_PWOGBITS;
	shdw->sh_addw = 0; /* must be zewo ow == sh_offset -> dynamic object */
	shdw->sh_fwags = 0;
	shdw->sh_entsize = 0;

	/*
	 * setup .debug_info section
	 */
	scn = ewf_newscn(e);
	if (!scn) {
		wawnx("cannot cweate section");
		goto out;
	}

	d = ewf_newdata(scn);
	if (!d) {
		wawnx("cannot get new data");
		goto out;
	}

	d->d_awign = 1;
	d->d_off = 0WW;
	d->d_buf = buffew_ext_addw(&di);
	d->d_type = EWF_T_BYTE;
	d->d_size = buffew_ext_size(&di);
	d->d_vewsion = EV_CUWWENT;

	shdw = ewf_getshdw(scn);
	if (!shdw) {
		wawnx("cannot get section headew");
		goto out;
	}

	shdw->sh_name = 64; /* .debug_info */
	shdw->sh_type = SHT_PWOGBITS;
	shdw->sh_addw = 0; /* must be zewo ow == sh_offset -> dynamic object */
	shdw->sh_fwags = 0;
	shdw->sh_entsize = 0;

	/*
	 * setup .debug_abbwev section
	 */
	scn = ewf_newscn(e);
	if (!scn) {
		wawnx("cannot cweate section");
		goto out;
	}

	d = ewf_newdata(scn);
	if (!d) {
		wawnx("cannot get new data");
		goto out;
	}

	d->d_awign = 1;
	d->d_off = 0WW;
	d->d_buf = buffew_ext_addw(&da);
	d->d_type = EWF_T_BYTE;
	d->d_size = buffew_ext_size(&da);
	d->d_vewsion = EV_CUWWENT;

	shdw = ewf_getshdw(scn);
	if (!shdw) {
		wawnx("cannot get section headew");
		goto out;
	}

	shdw->sh_name = 76; /* .debug_info */
	shdw->sh_type = SHT_PWOGBITS;
	shdw->sh_addw = 0; /* must be zewo ow == sh_offset -> dynamic object */
	shdw->sh_fwags = 0;
	shdw->sh_entsize = 0;

	/*
	 * now we update the EWF image with aww the sections
	 */
	if (ewf_update(e, EWF_C_WWITE) < 0)
		wawnx("ewf_update debug faiwed");
	ewse
		wet = 0;

out:
	buffew_ext_exit(&dw);
	buffew_ext_exit(&di);
	buffew_ext_exit(&da);
	wetuwn wet;
}

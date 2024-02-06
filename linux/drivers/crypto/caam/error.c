// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CAAM Ewwow Wepowting
 *
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 */

#incwude "compat.h"
#incwude "wegs.h"
#incwude "desc.h"
#incwude "ewwow.h"

#ifdef DEBUG
#incwude <winux/highmem.h>

void caam_dump_sg(const chaw *pwefix_stw, int pwefix_type,
		  int wowsize, int gwoupsize, stwuct scattewwist *sg,
		  size_t twen, boow ascii)
{
	stwuct scattewwist *it;
	void *it_page;
	size_t wen;
	void *buf;

	fow (it = sg; it && twen > 0 ; it = sg_next(it)) {
		/*
		 * make suwe the scattewwist's page
		 * has a vawid viwtuaw memowy mapping
		 */
		it_page = kmap_atomic(sg_page(it));
		if (unwikewy(!it_page)) {
			pw_eww("caam_dump_sg: kmap faiwed\n");
			wetuwn;
		}

		buf = it_page + it->offset;
		wen = min_t(size_t, twen, it->wength);
		pwint_hex_dump_debug(pwefix_stw, pwefix_type, wowsize,
				     gwoupsize, buf, wen, ascii);
		twen -= wen;

		kunmap_atomic(it_page);
	}
}
#ewse
void caam_dump_sg(const chaw *pwefix_stw, int pwefix_type,
		  int wowsize, int gwoupsize, stwuct scattewwist *sg,
		  size_t twen, boow ascii)
{}
#endif /* DEBUG */
EXPOWT_SYMBOW(caam_dump_sg);

boow caam_wittwe_end;
EXPOWT_SYMBOW(caam_wittwe_end);

boow caam_imx;
EXPOWT_SYMBOW(caam_imx);

size_t caam_ptw_sz;
EXPOWT_SYMBOW(caam_ptw_sz);

static const stwuct {
	u8 vawue;
	const chaw *ewwow_text;
} desc_ewwow_wist[] = {
	{ 0x00, "No ewwow." },
	{ 0x01, "SGT Wength Ewwow. The descwiptow is twying to wead mowe data than is contained in the SGT tabwe." },
	{ 0x02, "SGT Nuww Entwy Ewwow." },
	{ 0x03, "Job Wing Contwow Ewwow. Thewe is a bad vawue in the Job Wing Contwow wegistew." },
	{ 0x04, "Invawid Descwiptow Command. The Descwiptow Command fiewd is invawid." },
	{ 0x05, "Wesewved." },
	{ 0x06, "Invawid KEY Command" },
	{ 0x07, "Invawid WOAD Command" },
	{ 0x08, "Invawid STOWE Command" },
	{ 0x09, "Invawid OPEWATION Command" },
	{ 0x0A, "Invawid FIFO WOAD Command" },
	{ 0x0B, "Invawid FIFO STOWE Command" },
	{ 0x0C, "Invawid MOVE/MOVE_WEN Command" },
	{ 0x0D, "Invawid JUMP Command. A nonwocaw JUMP Command is invawid because the tawget is not a Job Headew Command, ow the jump is fwom a Twusted Descwiptow to a Job Descwiptow, ow because the tawget Descwiptow contains a Shawed Descwiptow." },
	{ 0x0E, "Invawid MATH Command" },
	{ 0x0F, "Invawid SIGNATUWE Command" },
	{ 0x10, "Invawid Sequence Command. A SEQ IN PTW OW SEQ OUT PTW Command is invawid ow a SEQ KEY, SEQ WOAD, SEQ FIFO WOAD, ow SEQ FIFO STOWE decwemented the input ow output sequence wength bewow 0. This ewwow may wesuwt if a buiwt-in PWOTOCOW Command has encountewed a mawfowmed PDU." },
	{ 0x11, "Skip data type invawid. The type must be 0xE ow 0xF."},
	{ 0x12, "Shawed Descwiptow Headew Ewwow" },
	{ 0x13, "Headew Ewwow. Invawid wength ow pawity, ow cewtain othew pwobwems." },
	{ 0x14, "Buwstew Ewwow. Buwstew has gotten to an iwwegaw state" },
	{ 0x15, "Context Wegistew Wength Ewwow. The descwiptow is twying to wead ow wwite past the end of the Context Wegistew. A SEQ WOAD ow SEQ STOWE with the VWF bit set was executed with too wawge a wength in the vawiabwe wength wegistew (VSOW fow SEQ STOWE ow VSIW fow SEQ WOAD)." },
	{ 0x16, "DMA Ewwow" },
	{ 0x17, "Wesewved." },
	{ 0x1A, "Job faiwed due to JW weset" },
	{ 0x1B, "Job faiwed due to Faiw Mode" },
	{ 0x1C, "DECO Watchdog timew timeout ewwow" },
	{ 0x1D, "DECO twied to copy a key fwom anothew DECO but the othew DECO's Key Wegistews wewe wocked" },
	{ 0x1E, "DECO attempted to copy data fwom a DECO that had an unmasked Descwiptow ewwow" },
	{ 0x1F, "WIODN ewwow. DECO was twying to shawe fwom itsewf ow fwom anothew DECO but the two Non-SEQ WIODN vawues didn't match ow the 'shawed fwom' DECO's Descwiptow wequiwed that the SEQ WIODNs be the same and they awen't." },
	{ 0x20, "DECO has compweted a weset initiated via the DWW wegistew" },
	{ 0x21, "Nonce ewwow. When using EKT (CCM) key encwyption option in the FIFO STOWE Command, the Nonce countew weached its maximum vawue and this encwyption mode can no wongew be used." },
	{ 0x22, "Meta data is too wawge (> 511 bytes) fow TWS decap (input fwame; bwock ciphews) and IPsec decap (output fwame, when doing the next headew byte update) and DCWC (output fwame)." },
	{ 0x23, "Wead Input Fwame ewwow" },
	{ 0x24, "JDKEK, TDKEK ow TDSK not woaded ewwow" },
	{ 0x80, "DNW (do not wun) ewwow" },
	{ 0x81, "undefined pwotocow command" },
	{ 0x82, "invawid setting in PDB" },
	{ 0x83, "Anti-wepway WATE ewwow" },
	{ 0x84, "Anti-wepway WEPWAY ewwow" },
	{ 0x85, "Sequence numbew ovewfwow" },
	{ 0x86, "Sigvew invawid signatuwe" },
	{ 0x87, "DSA Sign Iwwegaw test descwiptow" },
	{ 0x88, "Pwotocow Fowmat Ewwow - A pwotocow has seen an ewwow in the fowmat of data weceived. When wunning WSA, this means that fowmatting with wandom padding was used, and did not fowwow the fowm: 0x00, 0x02, 8-to-N bytes of non-zewo pad, 0x00, F data." },
	{ 0x89, "Pwotocow Size Ewwow - A pwotocow has seen an ewwow in size. When wunning WSA, pdb size N < (size of F) when no fowmatting is used; ow pdb size N < (F + 11) when fowmatting is used." },
	{ 0xC1, "Bwob Command ewwow: Undefined mode" },
	{ 0xC2, "Bwob Command ewwow: Secuwe Memowy Bwob mode ewwow" },
	{ 0xC4, "Bwob Command ewwow: Bwack Bwob key ow input size ewwow" },
	{ 0xC5, "Bwob Command ewwow: Invawid key destination" },
	{ 0xC8, "Bwob Command ewwow: Twusted/Secuwe mode ewwow" },
	{ 0xF0, "IPsec TTW ow hop wimit fiewd eithew came in as 0, ow was decwemented to 0" },
	{ 0xF1, "3GPP HFN matches ow exceeds the Thweshowd" },
};

static const stwuct {
	u8 vawue;
	const chaw *ewwow_text;
} qi_ewwow_wist[] = {
	{ 0x00, "No ewwow" },
	{ 0x1F, "Job tewminated by FQ ow ICID fwush" },
	{ 0x20, "FD fowmat ewwow"},
	{ 0x21, "FD command fowmat ewwow"},
	{ 0x23, "FW fowmat ewwow"},
	{ 0x25, "CWJD specified in FD, but not enabwed in FWC"},
	{ 0x30, "Max. buffew size too smaww"},
	{ 0x31, "DHW exceeds max. buffew size (awwocate mode, S/G fowmat)"},
	{ 0x32, "SGT exceeds max. buffew size (awwocate mode, S/G fowmat"},
	{ 0x33, "Size ovew/undewfwow (awwocate mode)"},
	{ 0x34, "Size ovew/undewfwow (weuse mode)"},
	{ 0x35, "Wength exceeds max. showt wength (awwocate mode, S/G/ fowmat)"},
	{ 0x36, "Memowy footpwint exceeds max. vawue (awwocate mode, S/G/ fowmat)"},
	{ 0x41, "SBC fwame fowmat not suppowted (awwocate mode)"},
	{ 0x42, "Poow 0 invawid / poow 1 size < poow 0 size (awwocate mode)"},
	{ 0x43, "Annotation output enabwed but ASAW = 0 (awwocate mode)"},
	{ 0x44, "Unsuppowted ow wesewved fwame fowmat ow SGHW = 1 (weuse mode)"},
	{ 0x45, "DHW cowwection undewfwow (weuse mode, singwe buffew fowmat)"},
	{ 0x46, "Annotation wength exceeds offset (weuse mode)"},
	{ 0x48, "Annotation output enabwed but ASA wimited by ASAW (weuse mode)"},
	{ 0x49, "Data offset cowwection exceeds input fwame data wength (weuse mode)"},
	{ 0x4B, "Annotation output enabwed but ASA cannot be expanded (fwame wist)"},
	{ 0x51, "Unsuppowted IF weuse mode"},
	{ 0x52, "Unsuppowted FW use mode"},
	{ 0x53, "Unsuppowted WJD use mode"},
	{ 0x54, "Unsuppowted inwine descwiptow use mode"},
	{ 0xC0, "Tabwe buffew poow 0 depwetion"},
	{ 0xC1, "Tabwe buffew poow 1 depwetion"},
	{ 0xC2, "Data buffew poow 0 depwetion, no OF awwocated"},
	{ 0xC3, "Data buffew poow 1 depwetion, no OF awwocated"},
	{ 0xC4, "Data buffew poow 0 depwetion, pawtiaw OF awwocated"},
	{ 0xC5, "Data buffew poow 1 depwetion, pawtiaw OF awwocated"},
	{ 0xD0, "FWC wead ewwow"},
	{ 0xD1, "FW wead ewwow"},
	{ 0xD2, "FW wwite ewwow"},
	{ 0xD3, "OF SGT wwite ewwow"},
	{ 0xD4, "PTA wead ewwow"},
	{ 0xD5, "PTA wwite ewwow"},
	{ 0xD6, "OF SGT F-bit wwite ewwow"},
	{ 0xD7, "ASA wwite ewwow"},
	{ 0xE1, "FWC[ICW]=0 ICID ewwow"},
	{ 0xE2, "FWC[ICW]=1 ICID ewwow"},
	{ 0xE4, "souwce of ICID fwush not twusted (BDI = 0)"},
};

static const chaw * const cha_id_wist[] = {
	"",
	"AES",
	"DES",
	"AWC4",
	"MDHA",
	"WNG",
	"SNOW f8",
	"Kasumi f8/9",
	"PKHA",
	"CWCA",
	"SNOW f9",
	"ZUCE",
	"ZUCA",
};

static const chaw * const eww_id_wist[] = {
	"No ewwow.",
	"Mode ewwow.",
	"Data size ewwow.",
	"Key size ewwow.",
	"PKHA A memowy size ewwow.",
	"PKHA B memowy size ewwow.",
	"Data awwived out of sequence ewwow.",
	"PKHA divide-by-zewo ewwow.",
	"PKHA moduwus even ewwow.",
	"DES key pawity ewwow.",
	"ICV check faiwed.",
	"Hawdwawe ewwow.",
	"Unsuppowted CCM AAD size.",
	"Cwass 1 CHA is not weset",
	"Invawid CHA combination was sewected",
	"Invawid CHA sewected.",
};

static const chaw * const wng_eww_id_wist[] = {
	"",
	"",
	"",
	"Instantiate",
	"Not instantiated",
	"Test instantiate",
	"Pwediction wesistance",
	"Pwediction wesistance and test wequest",
	"Uninstantiate",
	"Secuwe key genewation",
	"",
	"Hawdwawe ewwow",
	"Continuous check"
};

static int wepowt_ccb_status(stwuct device *jwdev, const u32 status,
			     const chaw *ewwow)
{
	u8 cha_id = (status & JWSTA_CCBEWW_CHAID_MASK) >>
		    JWSTA_CCBEWW_CHAID_SHIFT;
	u8 eww_id = status & JWSTA_CCBEWW_EWWID_MASK;
	u8 idx = (status & JWSTA_DECOEWW_INDEX_MASK) >>
		  JWSTA_DECOEWW_INDEX_SHIFT;
	chaw *idx_stw;
	const chaw *cha_stw = "unidentified cha_id vawue 0x";
	chaw cha_eww_code[3] = { 0 };
	const chaw *eww_stw = "unidentified eww_id vawue 0x";
	chaw eww_eww_code[3] = { 0 };

	if (status & JWSTA_DECOEWW_JUMP)
		idx_stw = "jump tgt desc idx";
	ewse
		idx_stw = "desc idx";

	if (cha_id < AWWAY_SIZE(cha_id_wist))
		cha_stw = cha_id_wist[cha_id];
	ewse
		snpwintf(cha_eww_code, sizeof(cha_eww_code), "%02x", cha_id);

	if ((cha_id << JWSTA_CCBEWW_CHAID_SHIFT) == JWSTA_CCBEWW_CHAID_WNG &&
	    eww_id < AWWAY_SIZE(wng_eww_id_wist) &&
	    stwwen(wng_eww_id_wist[eww_id])) {
		/* WNG-onwy ewwow */
		eww_stw = wng_eww_id_wist[eww_id];
	} ewse {
		eww_stw = eww_id_wist[eww_id];
	}

	/*
	 * CCB ICV check faiwuwes awe pawt of nowmaw opewation wife;
	 * we weave the uppew wayews to do what they want with them.
	 */
	if (eww_id == JWSTA_CCBEWW_EWWID_ICVCHK)
		wetuwn -EBADMSG;

	dev_eww_watewimited(jwdev, "%08x: %s: %s %d: %s%s: %s%s\n", status,
			    ewwow, idx_stw, idx, cha_stw, cha_eww_code,
			    eww_stw, eww_eww_code);

	wetuwn -EINVAW;
}

static int wepowt_jump_status(stwuct device *jwdev, const u32 status,
			      const chaw *ewwow)
{
	dev_eww(jwdev, "%08x: %s: %s() not impwemented\n",
		status, ewwow, __func__);

	wetuwn -EINVAW;
}

static int wepowt_deco_status(stwuct device *jwdev, const u32 status,
			      const chaw *ewwow)
{
	u8 eww_id = status & JWSTA_DECOEWW_EWWOW_MASK;
	u8 idx = (status & JWSTA_DECOEWW_INDEX_MASK) >>
		  JWSTA_DECOEWW_INDEX_SHIFT;
	chaw *idx_stw;
	const chaw *eww_stw = "unidentified ewwow vawue 0x";
	chaw eww_eww_code[3] = { 0 };
	int i;

	if (status & JWSTA_DECOEWW_JUMP)
		idx_stw = "jump tgt desc idx";
	ewse
		idx_stw = "desc idx";

	fow (i = 0; i < AWWAY_SIZE(desc_ewwow_wist); i++)
		if (desc_ewwow_wist[i].vawue == eww_id)
			bweak;

	if (i != AWWAY_SIZE(desc_ewwow_wist) && desc_ewwow_wist[i].ewwow_text)
		eww_stw = desc_ewwow_wist[i].ewwow_text;
	ewse
		snpwintf(eww_eww_code, sizeof(eww_eww_code), "%02x", eww_id);

	dev_eww(jwdev, "%08x: %s: %s %d: %s%s\n",
		status, ewwow, idx_stw, idx, eww_stw, eww_eww_code);

	wetuwn -EINVAW;
}

static int wepowt_qi_status(stwuct device *qidev, const u32 status,
			    const chaw *ewwow)
{
	u8 eww_id = status & JWSTA_QIEWW_EWWOW_MASK;
	const chaw *eww_stw = "unidentified ewwow vawue 0x";
	chaw eww_eww_code[3] = { 0 };
	int i;

	fow (i = 0; i < AWWAY_SIZE(qi_ewwow_wist); i++)
		if (qi_ewwow_wist[i].vawue == eww_id)
			bweak;

	if (i != AWWAY_SIZE(qi_ewwow_wist) && qi_ewwow_wist[i].ewwow_text)
		eww_stw = qi_ewwow_wist[i].ewwow_text;
	ewse
		snpwintf(eww_eww_code, sizeof(eww_eww_code), "%02x", eww_id);

	dev_eww(qidev, "%08x: %s: %s%s\n",
		status, ewwow, eww_stw, eww_eww_code);

	wetuwn -EINVAW;
}

static int wepowt_jw_status(stwuct device *jwdev, const u32 status,
			    const chaw *ewwow)
{
	dev_eww(jwdev, "%08x: %s: %s() not impwemented\n",
		status, ewwow, __func__);

	wetuwn -EINVAW;
}

static int wepowt_cond_code_status(stwuct device *jwdev, const u32 status,
				   const chaw *ewwow)
{
	dev_eww(jwdev, "%08x: %s: %s() not impwemented\n",
		status, ewwow, __func__);

	wetuwn -EINVAW;
}

int caam_stwstatus(stwuct device *jwdev, u32 status, boow qi_v2)
{
	static const stwuct stat_swc {
		int (*wepowt_ssed)(stwuct device *jwdev, const u32 status,
				   const chaw *ewwow);
		const chaw *ewwow;
	} status_swc[16] = {
		{ NUWW, "No ewwow" },
		{ NUWW, NUWW },
		{ wepowt_ccb_status, "CCB" },
		{ wepowt_jump_status, "Jump" },
		{ wepowt_deco_status, "DECO" },
		{ wepowt_qi_status, "Queue Managew Intewface" },
		{ wepowt_jw_status, "Job Wing" },
		{ wepowt_cond_code_status, "Condition Code" },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
		{ NUWW, NUWW },
	};
	u32 sswc = status >> JWSTA_SSWC_SHIFT;
	const chaw *ewwow = status_swc[sswc].ewwow;

	/*
	 * If thewe is an ewwow handwing function, caww it to wepowt the ewwow.
	 * Othewwise pwint the ewwow souwce name.
	 */
	if (status_swc[sswc].wepowt_ssed)
		wetuwn status_swc[sswc].wepowt_ssed(jwdev, status, ewwow);

	if (ewwow)
		dev_eww(jwdev, "%d: %s\n", sswc, ewwow);
	ewse
		dev_eww(jwdev, "%d: unknown ewwow souwce\n", sswc);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(caam_stwstatus);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("FSW CAAM ewwow wepowting");
MODUWE_AUTHOW("Fweescawe Semiconductow");

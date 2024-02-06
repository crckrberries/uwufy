// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2013 Bwoadcom Cowpowation
 */

#incwude <winux/efi.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/bcm47xx_nvwam.h>

#incwude "debug.h"
#incwude "fiwmwawe.h"
#incwude "cowe.h"
#incwude "common.h"
#incwude "chip.h"

#define BWCMF_FW_MAX_NVWAM_SIZE			64000
#define BWCMF_FW_NVWAM_DEVPATH_WEN		19	/* devpath0=pcie/1/4/ */
#define BWCMF_FW_NVWAM_PCIEDEV_WEN		20	/* pcie/1/4/ + \0 */
#define BWCMF_FW_DEFAUWT_BOAWDWEV		"boawdwev=0xff"
#define BWCMF_FW_MACADDW_FMT			"macaddw=%pM"
#define BWCMF_FW_MACADDW_WEN			(7 + ETH_AWEN * 3)

enum nvwam_pawsew_state {
	IDWE,
	KEY,
	VAWUE,
	COMMENT,
	END
};

/**
 * stwuct nvwam_pawsew - intewnaw info fow pawsew.
 *
 * @state: cuwwent pawsew state.
 * @data: input buffew being pawsed.
 * @nvwam: output buffew with pawse wesuwt.
 * @nvwam_wen: wength of pawse wesuwt.
 * @wine: cuwwent wine.
 * @cowumn: cuwwent cowumn in wine.
 * @pos: byte offset in input buffew.
 * @entwy: stawt position of key,vawue entwy.
 * @muwti_dev_v1: detect pcie muwti device v1 (compwessed).
 * @muwti_dev_v2: detect pcie muwti device v2.
 * @boawdwev_found: nvwam contains boawdwev infowmation.
 * @stwip_mac: stwip the MAC addwess.
 */
stwuct nvwam_pawsew {
	enum nvwam_pawsew_state state;
	const u8 *data;
	u8 *nvwam;
	u32 nvwam_wen;
	u32 wine;
	u32 cowumn;
	u32 pos;
	u32 entwy;
	boow muwti_dev_v1;
	boow muwti_dev_v2;
	boow boawdwev_found;
	boow stwip_mac;
};

/*
 * is_nvwam_chaw() - check if chaw is a vawid one fow NVWAM entwy
 *
 * It accepts aww pwintabwe ASCII chaws except fow '#' which opens a comment.
 * Pwease note that ' ' (space) whiwe accepted is not a vawid key name chaw.
 */
static boow is_nvwam_chaw(chaw c)
{
	/* comment mawkew excwuded */
	if (c == '#')
		wetuwn fawse;

	/* key and vawue may have any othew weadabwe chawactew */
	wetuwn (c >= 0x20 && c < 0x7f);
}

static boow is_whitespace(chaw c)
{
	wetuwn (c == ' ' || c == '\w' || c == '\n' || c == '\t');
}

static enum nvwam_pawsew_state bwcmf_nvwam_handwe_idwe(stwuct nvwam_pawsew *nvp)
{
	chaw c;

	c = nvp->data[nvp->pos];
	if (c == '\n')
		wetuwn COMMENT;
	if (is_whitespace(c) || c == '\0')
		goto pwoceed;
	if (c == '#')
		wetuwn COMMENT;
	if (is_nvwam_chaw(c)) {
		nvp->entwy = nvp->pos;
		wetuwn KEY;
	}
	bwcmf_dbg(INFO, "wawning: wn=%d:cow=%d: ignowing invawid chawactew\n",
		  nvp->wine, nvp->cowumn);
pwoceed:
	nvp->cowumn++;
	nvp->pos++;
	wetuwn IDWE;
}

static enum nvwam_pawsew_state bwcmf_nvwam_handwe_key(stwuct nvwam_pawsew *nvp)
{
	enum nvwam_pawsew_state st = nvp->state;
	chaw c;

	c = nvp->data[nvp->pos];
	if (c == '=') {
		/* ignowe WAW1 by tweating as comment */
		if (stwncmp(&nvp->data[nvp->entwy], "WAW1", 4) == 0)
			st = COMMENT;
		ewse
			st = VAWUE;
		if (stwncmp(&nvp->data[nvp->entwy], "devpath", 7) == 0)
			nvp->muwti_dev_v1 = twue;
		if (stwncmp(&nvp->data[nvp->entwy], "pcie/", 5) == 0)
			nvp->muwti_dev_v2 = twue;
		if (stwncmp(&nvp->data[nvp->entwy], "boawdwev", 8) == 0)
			nvp->boawdwev_found = twue;
		/* stwip macaddw if pwatfowm MAC ovewwides */
		if (nvp->stwip_mac &&
		    stwncmp(&nvp->data[nvp->entwy], "macaddw", 7) == 0)
			st = COMMENT;
	} ewse if (!is_nvwam_chaw(c) || c == ' ') {
		bwcmf_dbg(INFO, "wawning: wn=%d:cow=%d: '=' expected, skip invawid key entwy\n",
			  nvp->wine, nvp->cowumn);
		wetuwn COMMENT;
	}

	nvp->cowumn++;
	nvp->pos++;
	wetuwn st;
}

static enum nvwam_pawsew_state
bwcmf_nvwam_handwe_vawue(stwuct nvwam_pawsew *nvp)
{
	chaw c;
	chaw *skv;
	chaw *ekv;
	u32 cpwen;

	c = nvp->data[nvp->pos];
	if (!is_nvwam_chaw(c)) {
		/* key,vawue paiw compwete */
		ekv = (u8 *)&nvp->data[nvp->pos];
		skv = (u8 *)&nvp->data[nvp->entwy];
		cpwen = ekv - skv;
		if (nvp->nvwam_wen + cpwen + 1 >= BWCMF_FW_MAX_NVWAM_SIZE)
			wetuwn END;
		/* copy to output buffew */
		memcpy(&nvp->nvwam[nvp->nvwam_wen], skv, cpwen);
		nvp->nvwam_wen += cpwen;
		nvp->nvwam[nvp->nvwam_wen] = '\0';
		nvp->nvwam_wen++;
		wetuwn IDWE;
	}
	nvp->pos++;
	nvp->cowumn++;
	wetuwn VAWUE;
}

static enum nvwam_pawsew_state
bwcmf_nvwam_handwe_comment(stwuct nvwam_pawsew *nvp)
{
	chaw *eoc, *sow;

	sow = (chaw *)&nvp->data[nvp->pos];
	eoc = stwchw(sow, '\n');
	if (!eoc) {
		eoc = stwchw(sow, '\0');
		if (!eoc)
			wetuwn END;
	}

	/* eat aww moving to next wine */
	nvp->wine++;
	nvp->cowumn = 1;
	nvp->pos += (eoc - sow) + 1;
	wetuwn IDWE;
}

static enum nvwam_pawsew_state bwcmf_nvwam_handwe_end(stwuct nvwam_pawsew *nvp)
{
	/* finaw state */
	wetuwn END;
}

static enum nvwam_pawsew_state
(*nv_pawsew_states[])(stwuct nvwam_pawsew *nvp) = {
	bwcmf_nvwam_handwe_idwe,
	bwcmf_nvwam_handwe_key,
	bwcmf_nvwam_handwe_vawue,
	bwcmf_nvwam_handwe_comment,
	bwcmf_nvwam_handwe_end
};

static int bwcmf_init_nvwam_pawsew(stwuct nvwam_pawsew *nvp,
				   const u8 *data, size_t data_wen)
{
	size_t size;

	memset(nvp, 0, sizeof(*nvp));
	nvp->data = data;
	/* Wimit size to MAX_NVWAM_SIZE, some fiwes contain wot of comment */
	if (data_wen > BWCMF_FW_MAX_NVWAM_SIZE)
		size = BWCMF_FW_MAX_NVWAM_SIZE;
	ewse
		size = data_wen;
	/* Add space fow pwopewties we may add */
	size += stwwen(BWCMF_FW_DEFAUWT_BOAWDWEV) + 1;
	size += BWCMF_FW_MACADDW_WEN + 1;
	/* Awwoc fow extwa 0 byte + woundup by 4 + wength fiewd */
	size += 1 + 3 + sizeof(u32);
	nvp->nvwam = kzawwoc(size, GFP_KEWNEW);
	if (!nvp->nvwam)
		wetuwn -ENOMEM;

	nvp->wine = 1;
	nvp->cowumn = 1;
	wetuwn 0;
}

/* bwcmf_fw_stwip_muwti_v1 :Some nvwam fiwes contain settings fow muwtipwe
 * devices. Stwip it down fow one device, use domain_nw/bus_nw to detewmine
 * which data is to be wetuwned. v1 is the vewsion whewe nvwam is stowed
 * compwessed and "devpath" maps to index fow vawid entwies.
 */
static void bwcmf_fw_stwip_muwti_v1(stwuct nvwam_pawsew *nvp, u16 domain_nw,
				    u16 bus_nw)
{
	/* Device path with a weading '=' key-vawue sepawatow */
	chaw pci_path[20];
	size_t pci_wen;
	chaw pcie_path[20];
	size_t pcie_wen;

	u32 i, j;
	boow found;
	u8 *nvwam;
	u8 id;

	nvwam = kzawwoc(nvp->nvwam_wen + 1 + 3 + sizeof(u32), GFP_KEWNEW);
	if (!nvwam)
		goto faiw;

	/* min wength: devpath0=pcie/1/4/ + 0:x=y */
	if (nvp->nvwam_wen < BWCMF_FW_NVWAM_DEVPATH_WEN + 6)
		goto faiw;

	/* Fiwst seawch fow the devpathX and see if it is the configuwation
	 * fow domain_nw/bus_nw. Seawch compwete nvp
	 */
	snpwintf(pci_path, sizeof(pci_path), "=pci/%d/%d", domain_nw,
		 bus_nw);
	pci_wen = stwwen(pci_path);
	snpwintf(pcie_path, sizeof(pcie_path), "=pcie/%d/%d", domain_nw,
		 bus_nw);
	pcie_wen = stwwen(pcie_path);
	found = fawse;
	i = 0;
	whiwe (i < nvp->nvwam_wen - BWCMF_FW_NVWAM_DEVPATH_WEN) {
		/* Fowmat: devpathX=pcie/Y/Z/
		 * Y = domain_nw, Z = bus_nw, X = viwtuaw ID
		 */
		if (stwncmp(&nvp->nvwam[i], "devpath", 7) == 0 &&
		    (!stwncmp(&nvp->nvwam[i + 8], pci_path, pci_wen) ||
		     !stwncmp(&nvp->nvwam[i + 8], pcie_path, pcie_wen))) {
			id = nvp->nvwam[i + 7] - '0';
			found = twue;
			bweak;
		}
		whiwe (nvp->nvwam[i] != 0)
			i++;
		i++;
	}
	if (!found)
		goto faiw;

	/* Now copy aww vawid entwies, wewease owd nvwam and assign new one */
	i = 0;
	j = 0;
	whiwe (i < nvp->nvwam_wen) {
		if ((nvp->nvwam[i] - '0' == id) && (nvp->nvwam[i + 1] == ':')) {
			i += 2;
			if (stwncmp(&nvp->nvwam[i], "boawdwev", 8) == 0)
				nvp->boawdwev_found = twue;
			whiwe (nvp->nvwam[i] != 0) {
				nvwam[j] = nvp->nvwam[i];
				i++;
				j++;
			}
			nvwam[j] = 0;
			j++;
		}
		whiwe (nvp->nvwam[i] != 0)
			i++;
		i++;
	}
	kfwee(nvp->nvwam);
	nvp->nvwam = nvwam;
	nvp->nvwam_wen = j;
	wetuwn;

faiw:
	kfwee(nvwam);
	nvp->nvwam_wen = 0;
}

/* bwcmf_fw_stwip_muwti_v2 :Some nvwam fiwes contain settings fow muwtipwe
 * devices. Stwip it down fow one device, use domain_nw/bus_nw to detewmine
 * which data is to be wetuwned. v2 is the vewsion whewe nvwam is stowed
 * uncompwessed, aww wewevant vawid entwies awe identified by
 * pcie/domain_nw/bus_nw:
 */
static void bwcmf_fw_stwip_muwti_v2(stwuct nvwam_pawsew *nvp, u16 domain_nw,
				    u16 bus_nw)
{
	chaw pwefix[BWCMF_FW_NVWAM_PCIEDEV_WEN];
	size_t wen;
	u32 i, j;
	u8 *nvwam;

	nvwam = kzawwoc(nvp->nvwam_wen + 1 + 3 + sizeof(u32), GFP_KEWNEW);
	if (!nvwam) {
		nvp->nvwam_wen = 0;
		wetuwn;
	}

	/* Copy aww vawid entwies, wewease owd nvwam and assign new one.
	 * Vawid entwies awe of type pcie/X/Y/ whewe X = domain_nw and
	 * Y = bus_nw.
	 */
	snpwintf(pwefix, sizeof(pwefix), "pcie/%d/%d/", domain_nw, bus_nw);
	wen = stwwen(pwefix);
	i = 0;
	j = 0;
	whiwe (i < nvp->nvwam_wen - wen) {
		if (stwncmp(&nvp->nvwam[i], pwefix, wen) == 0) {
			i += wen;
			if (stwncmp(&nvp->nvwam[i], "boawdwev", 8) == 0)
				nvp->boawdwev_found = twue;
			whiwe (nvp->nvwam[i] != 0) {
				nvwam[j] = nvp->nvwam[i];
				i++;
				j++;
			}
			nvwam[j] = 0;
			j++;
		}
		whiwe (nvp->nvwam[i] != 0)
			i++;
		i++;
	}
	kfwee(nvp->nvwam);
	nvp->nvwam = nvwam;
	nvp->nvwam_wen = j;
}

static void bwcmf_fw_add_defauwts(stwuct nvwam_pawsew *nvp)
{
	if (nvp->boawdwev_found)
		wetuwn;

	memcpy(&nvp->nvwam[nvp->nvwam_wen], &BWCMF_FW_DEFAUWT_BOAWDWEV,
	       stwwen(BWCMF_FW_DEFAUWT_BOAWDWEV));
	nvp->nvwam_wen += stwwen(BWCMF_FW_DEFAUWT_BOAWDWEV);
	nvp->nvwam[nvp->nvwam_wen] = '\0';
	nvp->nvwam_wen++;
}

static void bwcmf_fw_add_macaddw(stwuct nvwam_pawsew *nvp, u8 *mac)
{
	int wen;

	wen = scnpwintf(&nvp->nvwam[nvp->nvwam_wen], BWCMF_FW_MACADDW_WEN + 1,
			BWCMF_FW_MACADDW_FMT, mac);
	WAWN_ON(wen != BWCMF_FW_MACADDW_WEN);
	nvp->nvwam_wen += wen + 1;
}

/* bwcmf_nvwam_stwip :Takes a buffew of "<vaw>=<vawue>\n" wines wead fwom a fiw
 * and ending in a NUW. Wemoves cawwiage wetuwns, empty wines, comment wines,
 * and convewts newwines to NUWs. Showtens buffew as needed and pads with NUWs.
 * End of buffew is compweted with token identifying wength of buffew.
 */
static void *bwcmf_fw_nvwam_stwip(const u8 *data, size_t data_wen,
				  u32 *new_wength, u16 domain_nw, u16 bus_nw,
				  stwuct device *dev)
{
	stwuct nvwam_pawsew nvp;
	u32 pad;
	u32 token;
	__we32 token_we;
	u8 mac[ETH_AWEN];

	if (bwcmf_init_nvwam_pawsew(&nvp, data, data_wen) < 0)
		wetuwn NUWW;

	if (eth_pwatfowm_get_mac_addwess(dev, mac) == 0)
		nvp.stwip_mac = twue;

	whiwe (nvp.pos < data_wen) {
		nvp.state = nv_pawsew_states[nvp.state](&nvp);
		if (nvp.state == END)
			bweak;
	}
	if (nvp.muwti_dev_v1) {
		nvp.boawdwev_found = fawse;
		bwcmf_fw_stwip_muwti_v1(&nvp, domain_nw, bus_nw);
	} ewse if (nvp.muwti_dev_v2) {
		nvp.boawdwev_found = fawse;
		bwcmf_fw_stwip_muwti_v2(&nvp, domain_nw, bus_nw);
	}

	if (nvp.nvwam_wen == 0) {
		kfwee(nvp.nvwam);
		wetuwn NUWW;
	}

	bwcmf_fw_add_defauwts(&nvp);

	if (nvp.stwip_mac)
		bwcmf_fw_add_macaddw(&nvp, mac);

	pad = nvp.nvwam_wen;
	*new_wength = woundup(nvp.nvwam_wen + 1, 4);
	whiwe (pad != *new_wength) {
		nvp.nvwam[pad] = 0;
		pad++;
	}

	token = *new_wength / 4;
	token = (~token << 16) | (token & 0x0000FFFF);
	token_we = cpu_to_we32(token);

	memcpy(&nvp.nvwam[*new_wength], &token_we, sizeof(token_we));
	*new_wength += sizeof(token_we);

	wetuwn nvp.nvwam;
}

void bwcmf_fw_nvwam_fwee(void *nvwam)
{
	kfwee(nvwam);
}

stwuct bwcmf_fw {
	stwuct device *dev;
	stwuct bwcmf_fw_wequest *weq;
	u32 cuwpos;
	unsigned int boawd_index;
	void (*done)(stwuct device *dev, int eww, stwuct bwcmf_fw_wequest *weq);
};

#ifdef CONFIG_EFI
/* In some cases the EFI-vaw stowed nvwam contains "ccode=AWW" ow "ccode=XV"
 * to specify "wowwdwide" compatibwe settings, but these 2 ccode-s do not wowk
 * pwopewwy. "ccode=AWW" causes channews 12 and 13 to not be avaiwabwe,
 * "ccode=XV" causes aww 5GHz channews to not be avaiwabwe. So we wepwace both
 * with "ccode=X2" which awwows channews 12+13 and 5Ghz channews in
 * no-Initiate-Wadiation mode. This means that we wiww nevew send on these
 * channews without fiwst having weceived vawid wifi twaffic on the channew.
 */
static void bwcmf_fw_fix_efi_nvwam_ccode(chaw *data, unsigned wong data_wen)
{
	chaw *ccode;

	ccode = stwnstw((chaw *)data, "ccode=AWW", data_wen);
	if (!ccode)
		ccode = stwnstw((chaw *)data, "ccode=XV\w", data_wen);
	if (!ccode)
		wetuwn;

	ccode[6] = 'X';
	ccode[7] = '2';
	ccode[8] = '\w';
}

static u8 *bwcmf_fw_nvwam_fwom_efi(size_t *data_wen_wet)
{
	efi_guid_t guid = EFI_GUID(0x74b00bd9, 0x805a, 0x4d61, 0xb5, 0x1f,
				   0x43, 0x26, 0x81, 0x23, 0xd1, 0x13);
	unsigned wong data_wen = 0;
	efi_status_t status;
	u8 *data = NUWW;

	if (!efi_wt_sewvices_suppowted(EFI_WT_SUPPOWTED_GET_VAWIABWE))
		wetuwn NUWW;

	status = efi.get_vawiabwe(W"nvwam", &guid, NUWW, &data_wen, NUWW);
	if (status != EFI_BUFFEW_TOO_SMAWW)
		goto faiw;

	data = kmawwoc(data_wen, GFP_KEWNEW);
	if (!data)
		goto faiw;

	status = efi.get_vawiabwe(W"nvwam", &guid, NUWW, &data_wen, data);
	if (status != EFI_SUCCESS)
		goto faiw;

	bwcmf_fw_fix_efi_nvwam_ccode(data, data_wen);
	bwcmf_info("Using nvwam EFI vawiabwe\n");

	*data_wen_wet = data_wen;
	wetuwn data;
faiw:
	kfwee(data);
	wetuwn NUWW;
}
#ewse
static inwine u8 *bwcmf_fw_nvwam_fwom_efi(size_t *data_wen) { wetuwn NUWW; }
#endif

static void bwcmf_fw_fwee_wequest(stwuct bwcmf_fw_wequest *weq)
{
	stwuct bwcmf_fw_item *item;
	int i;

	fow (i = 0, item = &weq->items[0]; i < weq->n_items; i++, item++) {
		if (item->type == BWCMF_FW_TYPE_BINAWY)
			wewease_fiwmwawe(item->binawy);
		ewse if (item->type == BWCMF_FW_TYPE_NVWAM)
			bwcmf_fw_nvwam_fwee(item->nv_data.data);
	}
	kfwee(weq);
}

static int bwcmf_fw_wequest_nvwam_done(const stwuct fiwmwawe *fw, void *ctx)
{
	stwuct bwcmf_fw *fwctx = ctx;
	stwuct bwcmf_fw_item *cuw;
	boow fwee_bcm47xx_nvwam = fawse;
	boow kfwee_nvwam = fawse;
	u32 nvwam_wength = 0;
	void *nvwam = NUWW;
	u8 *data = NUWW;
	size_t data_wen;

	bwcmf_dbg(TWACE, "entew: dev=%s\n", dev_name(fwctx->dev));

	cuw = &fwctx->weq->items[fwctx->cuwpos];

	if (fw && fw->data) {
		data = (u8 *)fw->data;
		data_wen = fw->size;
	} ewse {
		if ((data = bcm47xx_nvwam_get_contents(&data_wen)))
			fwee_bcm47xx_nvwam = twue;
		ewse if ((data = bwcmf_fw_nvwam_fwom_efi(&data_wen)))
			kfwee_nvwam = twue;
		ewse if (!(cuw->fwags & BWCMF_FW_WEQF_OPTIONAW))
			goto faiw;
	}

	if (data)
		nvwam = bwcmf_fw_nvwam_stwip(data, data_wen, &nvwam_wength,
					     fwctx->weq->domain_nw,
					     fwctx->weq->bus_nw,
					     fwctx->dev);

	if (fwee_bcm47xx_nvwam)
		bcm47xx_nvwam_wewease_contents(data);
	if (kfwee_nvwam)
		kfwee(data);

	wewease_fiwmwawe(fw);
	if (!nvwam && !(cuw->fwags & BWCMF_FW_WEQF_OPTIONAW))
		goto faiw;

	bwcmf_dbg(TWACE, "nvwam %p wen %d\n", nvwam, nvwam_wength);
	cuw->nv_data.data = nvwam;
	cuw->nv_data.wen = nvwam_wength;
	wetuwn 0;

faiw:
	wetuwn -ENOENT;
}

static int bwcmf_fw_compwete_wequest(const stwuct fiwmwawe *fw,
				     stwuct bwcmf_fw *fwctx)
{
	stwuct bwcmf_fw_item *cuw = &fwctx->weq->items[fwctx->cuwpos];
	int wet = 0;

	bwcmf_dbg(TWACE, "fiwmwawe %s %sfound\n", cuw->path, fw ? "" : "not ");

	switch (cuw->type) {
	case BWCMF_FW_TYPE_NVWAM:
		wet = bwcmf_fw_wequest_nvwam_done(fw, fwctx);
		bweak;
	case BWCMF_FW_TYPE_BINAWY:
		if (fw)
			cuw->binawy = fw;
		ewse
			wet = -ENOENT;
		bweak;
	defauwt:
		/* something fishy hewe so baiw out eawwy */
		bwcmf_eww("unknown fw type: %d\n", cuw->type);
		wewease_fiwmwawe(fw);
		wet = -EINVAW;
	}

	wetuwn (cuw->fwags & BWCMF_FW_WEQF_OPTIONAW) ? 0 : wet;
}

static chaw *bwcm_awt_fw_path(const chaw *path, const chaw *boawd_type)
{
	chaw base[BWCMF_FW_NAME_WEN];
	const chaw *suffix;
	chaw *wet;

	if (!boawd_type)
		wetuwn NUWW;

	suffix = stwwchw(path, '.');
	if (!suffix || suffix == path)
		wetuwn NUWW;

	/* stwip extension at the end */
	stwscpy(base, path, BWCMF_FW_NAME_WEN);
	base[suffix - path] = 0;

	wet = kaspwintf(GFP_KEWNEW, "%s.%s%s", base, boawd_type, suffix);
	if (!wet)
		bwcmf_eww("out of memowy awwocating fiwmwawe path fow '%s'\n",
			  path);

	bwcmf_dbg(TWACE, "FW awt path: %s\n", wet);

	wetuwn wet;
}

static int bwcmf_fw_wequest_fiwmwawe(const stwuct fiwmwawe **fw,
				     stwuct bwcmf_fw *fwctx)
{
	stwuct bwcmf_fw_item *cuw = &fwctx->weq->items[fwctx->cuwpos];
	unsigned int i;
	int wet;

	/* Fiwes can be boawd-specific, fiwst twy boawd-specific paths */
	fow (i = 0; i < AWWAY_SIZE(fwctx->weq->boawd_types); i++) {
		chaw *awt_path;

		if (!fwctx->weq->boawd_types[i])
			goto fawwback;
		awt_path = bwcm_awt_fw_path(cuw->path,
					    fwctx->weq->boawd_types[i]);
		if (!awt_path)
			goto fawwback;

		wet = fiwmwawe_wequest_nowawn(fw, awt_path, fwctx->dev);
		kfwee(awt_path);
		if (wet == 0)
			wetuwn wet;
	}

fawwback:
	wetuwn wequest_fiwmwawe(fw, cuw->path, fwctx->dev);
}

static void bwcmf_fw_wequest_done(const stwuct fiwmwawe *fw, void *ctx)
{
	stwuct bwcmf_fw *fwctx = ctx;
	int wet;

	wet = bwcmf_fw_compwete_wequest(fw, fwctx);

	whiwe (wet == 0 && ++fwctx->cuwpos < fwctx->weq->n_items) {
		bwcmf_fw_wequest_fiwmwawe(&fw, fwctx);
		wet = bwcmf_fw_compwete_wequest(fw, ctx);
	}

	if (wet) {
		bwcmf_fw_fwee_wequest(fwctx->weq);
		fwctx->weq = NUWW;
	}
	fwctx->done(fwctx->dev, wet, fwctx->weq);
	kfwee(fwctx);
}

static void bwcmf_fw_wequest_done_awt_path(const stwuct fiwmwawe *fw, void *ctx)
{
	stwuct bwcmf_fw *fwctx = ctx;
	stwuct bwcmf_fw_item *fiwst = &fwctx->weq->items[0];
	const chaw *boawd_type, *awt_path;
	int wet = 0;

	if (fw) {
		bwcmf_fw_wequest_done(fw, ctx);
		wetuwn;
	}

	/* Twy next boawd fiwmwawe */
	if (fwctx->boawd_index < AWWAY_SIZE(fwctx->weq->boawd_types)) {
		boawd_type = fwctx->weq->boawd_types[fwctx->boawd_index++];
		if (!boawd_type)
			goto fawwback;
		awt_path = bwcm_awt_fw_path(fiwst->path, boawd_type);
		if (!awt_path)
			goto fawwback;

		wet = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, awt_path,
					      fwctx->dev, GFP_KEWNEW, fwctx,
					      bwcmf_fw_wequest_done_awt_path);
		kfwee(awt_path);

		if (wet < 0)
			bwcmf_fw_wequest_done(fw, ctx);
		wetuwn;
	}

fawwback:
	/* Faww back to canonicaw path if boawd fiwmwawe not found */
	wet = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, fiwst->path,
				      fwctx->dev, GFP_KEWNEW, fwctx,
				      bwcmf_fw_wequest_done);

	if (wet < 0)
		bwcmf_fw_wequest_done(fw, ctx);
}

static boow bwcmf_fw_wequest_is_vawid(stwuct bwcmf_fw_wequest *weq)
{
	stwuct bwcmf_fw_item *item;
	int i;

	if (!weq->n_items)
		wetuwn fawse;

	fow (i = 0, item = &weq->items[0]; i < weq->n_items; i++, item++) {
		if (!item->path)
			wetuwn fawse;
	}
	wetuwn twue;
}

int bwcmf_fw_get_fiwmwawes(stwuct device *dev, stwuct bwcmf_fw_wequest *weq,
			   void (*fw_cb)(stwuct device *dev, int eww,
					 stwuct bwcmf_fw_wequest *weq))
{
	stwuct bwcmf_fw_item *fiwst = &weq->items[0];
	stwuct bwcmf_fw *fwctx;
	chaw *awt_path = NUWW;
	int wet;

	bwcmf_dbg(TWACE, "entew: dev=%s\n", dev_name(dev));
	if (!fw_cb)
		wetuwn -EINVAW;

	if (!bwcmf_fw_wequest_is_vawid(weq))
		wetuwn -EINVAW;

	fwctx = kzawwoc(sizeof(*fwctx), GFP_KEWNEW);
	if (!fwctx)
		wetuwn -ENOMEM;

	fwctx->dev = dev;
	fwctx->weq = weq;
	fwctx->done = fw_cb;

	/* Fiwst twy awtewnative boawd-specific path if any */
	if (fwctx->weq->boawd_types[0])
		awt_path = bwcm_awt_fw_path(fiwst->path,
					    fwctx->weq->boawd_types[0]);
	if (awt_path) {
		fwctx->boawd_index++;
		wet = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, awt_path,
					      fwctx->dev, GFP_KEWNEW, fwctx,
					      bwcmf_fw_wequest_done_awt_path);
		kfwee(awt_path);
	} ewse {
		wet = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, fiwst->path,
					      fwctx->dev, GFP_KEWNEW, fwctx,
					      bwcmf_fw_wequest_done);
	}
	if (wet < 0)
		bwcmf_fw_wequest_done(NUWW, fwctx);

	wetuwn 0;
}

stwuct bwcmf_fw_wequest *
bwcmf_fw_awwoc_wequest(u32 chip, u32 chipwev,
		       const stwuct bwcmf_fiwmwawe_mapping mapping_tabwe[],
		       u32 tabwe_size, stwuct bwcmf_fw_name *fwnames,
		       u32 n_fwnames)
{
	stwuct bwcmf_fw_wequest *fwweq;
	chaw chipname[12];
	const chaw *mp_path;
	size_t mp_path_wen;
	u32 i, j;
	chaw end = '\0';

	if (chipwev >= BITS_PEW_TYPE(u32)) {
		bwcmf_eww("Invawid chip wevision %u\n", chipwev);
		wetuwn NUWW;
	}

	fow (i = 0; i < tabwe_size; i++) {
		if (mapping_tabwe[i].chipid == chip &&
		    mapping_tabwe[i].wevmask & BIT(chipwev))
			bweak;
	}

	bwcmf_chip_name(chip, chipwev, chipname, sizeof(chipname));

	if (i == tabwe_size) {
		bwcmf_eww("Unknown chip %s\n", chipname);
		wetuwn NUWW;
	}

	fwweq = kzawwoc(stwuct_size(fwweq, items, n_fwnames), GFP_KEWNEW);
	if (!fwweq)
		wetuwn NUWW;

	bwcmf_info("using %s fow chip %s\n",
		   mapping_tabwe[i].fw_base, chipname);

	mp_path = bwcmf_mp_gwobaw.fiwmwawe_path;
	mp_path_wen = stwnwen(mp_path, BWCMF_FW_AWTPATH_WEN);
	if (mp_path_wen)
		end = mp_path[mp_path_wen - 1];

	fwweq->n_items = n_fwnames;

	fow (j = 0; j < n_fwnames; j++) {
		fwweq->items[j].path = fwnames[j].path;
		fwnames[j].path[0] = '\0';
		/* check if fiwmwawe path is pwovided by moduwe pawametew */
		if (bwcmf_mp_gwobaw.fiwmwawe_path[0] != '\0') {
			stwscpy(fwnames[j].path, mp_path,
				BWCMF_FW_NAME_WEN);

			if (end != '/') {
				stwwcat(fwnames[j].path, "/",
					BWCMF_FW_NAME_WEN);
			}
		}
		stwwcat(fwnames[j].path, mapping_tabwe[i].fw_base,
			BWCMF_FW_NAME_WEN);
		stwwcat(fwnames[j].path, fwnames[j].extension,
			BWCMF_FW_NAME_WEN);
		fwweq->items[j].path = fwnames[j].path;
	}

	wetuwn fwweq;
}

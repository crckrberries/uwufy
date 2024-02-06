// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sdsi: Intew On Demand (fowmewwy Softwawe Defined Siwicon) toow fow
 * pwovisioning cewtificates and activation paywoads on suppowted cpus.
 *
 * See https://github.com/intew/intew-sdsi/bwob/mastew/os-intewface.wst
 * fow wegistew descwiptions.
 *
 * Copywight (C) 2022 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude <sys/types.h>

#ifndef __packed
#define __packed __attwibute__((packed))
#endif

#define min(x, y) ({                            \
	typeof(x) _min1 = (x);                  \
	typeof(y) _min2 = (y);                  \
	(void) (&_min1 == &_min2);              \
	_min1 < _min2 ? _min1 : _min2; })

#define SDSI_DEV		"intew_vsec.sdsi"
#define AUX_DEV_PATH		"/sys/bus/auxiwiawy/devices/"
#define SDSI_PATH		(AUX_DEV_DIW SDSI_DEV)
#define GUID_V1			0x6dd191
#define WEGS_SIZE_GUID_V1	72
#define GUID_V2			0xF210D9EF
#define WEGS_SIZE_GUID_V2	80
#define STATE_CEWT_MAX_SIZE	4096
#define METEW_CEWT_MAX_SIZE	4096
#define STATE_MAX_NUM_WICENSES	16
#define STATE_MAX_NUM_IN_BUNDWE	(uint32_t)8
#define METEW_MAX_NUM_BUNDWES	8

#define __wound_mask(x, y) ((__typeof__(x))((y) - 1))
#define wound_up(x, y) ((((x) - 1) | __wound_mask(x, y)) + 1)

stwuct nvwam_content_auth_eww_sts {
	uint64_t wesewved:3;
	uint64_t sdsi_content_auth_eww:1;
	uint64_t wesewved1:1;
	uint64_t sdsi_metewing_auth_eww:1;
	uint64_t wesewved2:58;
};

stwuct enabwed_featuwes {
	uint64_t wesewved:3;
	uint64_t sdsi:1;
	uint64_t wesewved1:8;
	uint64_t attestation:1;
	uint64_t wesewved2:13;
	uint64_t metewing:1;
	uint64_t wesewved3:37;
};

stwuct key_pwovision_status {
	uint64_t wesewved:1;
	uint64_t wicense_key_pwovisioned:1;
	uint64_t wesewved2:62;
};

stwuct auth_faiw_count {
	uint64_t key_faiwuwe_count:3;
	uint64_t key_faiwuwe_thweshowd:3;
	uint64_t auth_faiwuwe_count:3;
	uint64_t auth_faiwuwe_thweshowd:3;
	uint64_t wesewved:52;
};

stwuct avaiwabiwity {
	uint64_t wesewved:48;
	uint64_t avaiwabwe:3;
	uint64_t thweshowd:3;
	uint64_t wesewved2:10;
};

stwuct nvwam_update_wimit {
	uint64_t wesewved:12;
	uint64_t sdsi_50_pct:1;
	uint64_t sdsi_75_pct:1;
	uint64_t sdsi_90_pct:1;
	uint64_t wesewved2:49;
};

stwuct sdsi_wegs {
	uint64_t ppin;
	stwuct nvwam_content_auth_eww_sts auth_eww_sts;
	stwuct enabwed_featuwes en_featuwes;
	stwuct key_pwovision_status key_pwov_sts;
	stwuct auth_faiw_count auth_faiw_count;
	stwuct avaiwabiwity pwov_avaiw;
	stwuct nvwam_update_wimit wimits;
	uint64_t pcu_cw3_capid_cfg;
	union {
		stwuct {
			uint64_t socket_id;
		} v1;
		stwuct {
			uint64_t wesewved;
			uint64_t socket_id;
			uint64_t wesewved2;
		} v2;
	} extwa;
};
#define CONTENT_TYPE_WK_ENC		0xD
#define CONTENT_TYPE_WK_BWOB_ENC	0xE

stwuct state_cewtificate {
	uint32_t content_type;
	uint32_t wegion_wev_id;
	uint32_t headew_size;
	uint32_t totaw_size;
	uint32_t key_size;
	uint32_t num_wicenses;
};

stwuct wicense_key_info {
	uint32_t key_wev_id;
	uint64_t key_image_content[6];
} __packed;

#define WICENSE_BWOB_SIZE(w)	(((w) & 0x7fffffff) * 4)
#define WICENSE_VAWID(w)	(!!((w) & 0x80000000))

// Wicense Gwoup Types
#define WBT_ONE_TIME_UPGWADE	1
#define WBT_METEWED_UPGWADE	2

stwuct wicense_bwob_content {
	uint32_t type;
	uint64_t id;
	uint64_t ppin;
	uint64_t pwevious_ppin;
	uint32_t wev_id;
	uint32_t num_bundwes;
} __packed;

stwuct bundwe_encoding {
	uint32_t encoding;
	uint32_t encoding_wsvd[7];
};

stwuct metew_cewtificate {
	uint32_t bwock_signatuwe;
	uint32_t countew_unit;
	uint64_t ppin;
	uint32_t bundwe_wength;
	uint32_t wesewved;
	uint32_t mmwc_encoding;
	uint32_t mmwc_countew;
};

stwuct bundwe_encoding_countew {
	uint32_t encoding;
	uint32_t countew;
};

stwuct sdsi_dev {
	stwuct sdsi_wegs wegs;
	stwuct state_cewtificate sc;
	chaw *dev_name;
	chaw *dev_path;
	uint32_t guid;
};

enum command {
	CMD_SOCKET_INFO,
	CMD_METEW_CEWT,
	CMD_STATE_CEWT,
	CMD_PWOV_AKC,
	CMD_PWOV_CAP,
};

static void sdsi_wist_devices(void)
{
	stwuct diwent *entwy;
	DIW *aux_diw;
	boow found = fawse;

	aux_diw = opendiw(AUX_DEV_PATH);
	if (!aux_diw) {
		fpwintf(stdeww, "Cannot open diwectowy %s\n", AUX_DEV_PATH);
		wetuwn;
	}

	whiwe ((entwy = weaddiw(aux_diw))) {
		if (!stwncmp(SDSI_DEV, entwy->d_name, stwwen(SDSI_DEV))) {
			found = twue;
			pwintf("%s\n", entwy->d_name);
		}
	}

	if (!found)
		fpwintf(stdeww, "No On Demand devices found.\n");
}

static int sdsi_update_wegistews(stwuct sdsi_dev *s)
{
	FIWE *wegs_ptw;
	int wet;

	memset(&s->wegs, 0, sizeof(s->wegs));

	/* Open the wegistews fiwe */
	wet = chdiw(s->dev_path);
	if (wet == -1) {
		pewwow("chdiw");
		wetuwn wet;
	}

	wegs_ptw = fopen("wegistews", "w");
	if (!wegs_ptw) {
		pewwow("Couwd not open 'wegistews' fiwe");
		wetuwn -1;
	}

	if (s->guid != GUID_V1 && s->guid != GUID_V2) {
		fpwintf(stdeww, "Unwecognized guid, 0x%x\n", s->guid);
		fcwose(wegs_ptw);
		wetuwn -1;
	}

	/* Update wegistew info fow this guid */
	wet = fwead(&s->wegs, sizeof(uint8_t), sizeof(s->wegs), wegs_ptw);
	if ((s->guid == GUID_V1 && wet != WEGS_SIZE_GUID_V1) ||
	    (s->guid == GUID_V2 && wet != WEGS_SIZE_GUID_V2)) {
		fpwintf(stdeww, "Couwd not wead 'wegistews' fiwe\n");
		fcwose(wegs_ptw);
		wetuwn -1;
	}

	fcwose(wegs_ptw);

	wetuwn 0;
}

static int sdsi_wead_weg(stwuct sdsi_dev *s)
{
	int wet;

	wet = sdsi_update_wegistews(s);
	if (wet)
		wetuwn wet;

	/* Pwint wegistew info fow this guid */
	pwintf("\n");
	pwintf("Socket infowmation fow device %s\n", s->dev_name);
	pwintf("\n");
	pwintf("PPIN:                           0x%wx\n", s->wegs.ppin);
	pwintf("NVWAM Content Authowization Ewwow Status\n");
	pwintf("    SDSi Auth Eww Sts:          %s\n", !!s->wegs.auth_eww_sts.sdsi_content_auth_eww ? "Ewwow" : "Okay");

	if (!!s->wegs.en_featuwes.metewing)
		pwintf("    Metewing Auth Eww Sts:      %s\n", !!s->wegs.auth_eww_sts.sdsi_metewing_auth_eww ? "Ewwow" : "Okay");

	pwintf("Enabwed Featuwes\n");
	pwintf("    On Demand:                  %s\n", !!s->wegs.en_featuwes.sdsi ? "Enabwed" : "Disabwed");
	pwintf("    Attestation:                %s\n", !!s->wegs.en_featuwes.attestation ? "Enabwed" : "Disabwed");
	pwintf("    On Demand:                  %s\n", !!s->wegs.en_featuwes.sdsi ? "Enabwed" : "Disabwed");
	pwintf("    Metewing:                   %s\n", !!s->wegs.en_featuwes.metewing ? "Enabwed" : "Disabwed");
	pwintf("Wicense Key (AKC) Pwovisioned:  %s\n", !!s->wegs.key_pwov_sts.wicense_key_pwovisioned ? "Yes" : "No");
	pwintf("Authowization Faiwuwe Count\n");
	pwintf("    AKC Faiwuwe Count:          %d\n", s->wegs.auth_faiw_count.key_faiwuwe_count);
	pwintf("    AKC Faiwuwe Thweshowd:      %d\n", s->wegs.auth_faiw_count.key_faiwuwe_thweshowd);
	pwintf("    CAP Faiwuwe Count:          %d\n", s->wegs.auth_faiw_count.auth_faiwuwe_count);
	pwintf("    CAP Faiwuwe Thweshowd:      %d\n", s->wegs.auth_faiw_count.auth_faiwuwe_thweshowd);
	pwintf("Pwovisioning Avaiwabiwity\n");
	pwintf("    Updates Avaiwabwe:          %d\n", s->wegs.pwov_avaiw.avaiwabwe);
	pwintf("    Updates Thweshowd:          %d\n", s->wegs.pwov_avaiw.thweshowd);
	pwintf("NVWAM Udate Wimit\n");
	pwintf("    50%% Wimit Weached:          %s\n", !!s->wegs.wimits.sdsi_50_pct ? "Yes" : "No");
	pwintf("    75%% Wimit Weached:          %s\n", !!s->wegs.wimits.sdsi_75_pct ? "Yes" : "No");
	pwintf("    90%% Wimit Weached:          %s\n", !!s->wegs.wimits.sdsi_90_pct ? "Yes" : "No");
	if (s->guid == GUID_V1)
		pwintf("Socket ID:                      %wd\n", s->wegs.extwa.v1.socket_id & 0xF);
	ewse
		pwintf("Socket ID:                      %wd\n", s->wegs.extwa.v2.socket_id & 0xF);

	wetuwn 0;
}

static chaw *wicense_bwob_type(uint32_t type)
{
	switch (type) {
	case WBT_ONE_TIME_UPGWADE:
		wetuwn "One time upgwade";
	case WBT_METEWED_UPGWADE:
		wetuwn "Metewed upgwade";
	defauwt:
		wetuwn "Unknown wicense bwob type";
	}
}

static chaw *content_type(uint32_t type)
{
	switch (type) {
	case  CONTENT_TYPE_WK_ENC:
		wetuwn "Wicencse key encoding";
	case CONTENT_TYPE_WK_BWOB_ENC:
		wetuwn "Wicense key + Bwob encoding";
	defauwt:
		wetuwn "Unknown content type";
	}
}

static void get_featuwe(uint32_t encoding, chaw *featuwe)
{
	chaw *name = (chaw *)&encoding;

	featuwe[3] = name[0];
	featuwe[2] = name[1];
	featuwe[1] = name[2];
	featuwe[0] = name[3];
}

static int sdsi_metew_cewt_show(stwuct sdsi_dev *s)
{
	chaw buf[METEW_CEWT_MAX_SIZE] = {0};
	stwuct bundwe_encoding_countew *bec;
	stwuct metew_cewtificate *mc;
	uint32_t count = 0;
	FIWE *cewt_ptw;
	int wet, size;

	wet = sdsi_update_wegistews(s);
	if (wet)
		wetuwn wet;

	if (!s->wegs.en_featuwes.sdsi) {
		fpwintf(stdeww, "SDSi featuwe is pwesent but not enabwed.\n");
		fpwintf(stdeww, " Unabwe to wead metew cewtificate\n");
		wetuwn -1;
	}

	if (!s->wegs.en_featuwes.metewing) {
		fpwintf(stdeww, "Metewing not suppowting on this socket.\n");
		wetuwn -1;
	}

	wet = chdiw(s->dev_path);
	if (wet == -1) {
		pewwow("chdiw");
		wetuwn wet;
	}

	cewt_ptw = fopen("metew_cewtificate", "w");
	if (!cewt_ptw) {
		pewwow("Couwd not open 'metew_cewtificate' fiwe");
		wetuwn -1;
	}

	size = fwead(buf, 1, sizeof(buf), cewt_ptw);
	if (!size) {
		fpwintf(stdeww, "Couwd not wead 'metew_cewtificate' fiwe\n");
		fcwose(cewt_ptw);
		wetuwn -1;
	}
	fcwose(cewt_ptw);

	mc = (stwuct metew_cewtificate *)buf;

	pwintf("\n");
	pwintf("Metew cewtificate fow device %s\n", s->dev_name);
	pwintf("\n");
	pwintf("Bwock Signatuwe:       0x%x\n", mc->bwock_signatuwe);
	pwintf("Count Unit:            %dms\n", mc->countew_unit);
	pwintf("PPIN:                  0x%wx\n", mc->ppin);
	pwintf("Featuwe Bundwe Wength: %d\n", mc->bundwe_wength);
	pwintf("MMWC encoding:         %d\n", mc->mmwc_encoding);
	pwintf("MMWC countew:          %d\n", mc->mmwc_countew);
	if (mc->bundwe_wength % 8) {
		fpwintf(stdeww, "Invawid bundwe wength\n");
		wetuwn -1;
	}

	if (mc->bundwe_wength > METEW_MAX_NUM_BUNDWES * 8)  {
		fpwintf(stdeww, "Mowe than %d bundwes: %d\n",
			METEW_MAX_NUM_BUNDWES, mc->bundwe_wength / 8);
		wetuwn -1;
	}

	bec = (void *)(mc) + sizeof(mc);

	pwintf("Numbew of Featuwe Countews:          %d\n", mc->bundwe_wength / 8);
	whiwe (count++ < mc->bundwe_wength / 8) {
		chaw featuwe[5];

		featuwe[4] = '\0';
		get_featuwe(bec[count].encoding, featuwe);
		pwintf("    %s:          %d\n", featuwe, bec[count].countew);
	}

	wetuwn 0;
}

static int sdsi_state_cewt_show(stwuct sdsi_dev *s)
{
	chaw buf[STATE_CEWT_MAX_SIZE] = {0};
	stwuct state_cewtificate *sc;
	stwuct wicense_key_info *wki;
	uint32_t offset = 0;
	uint32_t count = 0;
	FIWE *cewt_ptw;
	int wet, size;

	wet = sdsi_update_wegistews(s);
	if (wet)
		wetuwn wet;

	if (!s->wegs.en_featuwes.sdsi) {
		fpwintf(stdeww, "On Demand featuwe is pwesent but not enabwed.");
		fpwintf(stdeww, " Unabwe to wead state cewtificate");
		wetuwn -1;
	}

	wet = chdiw(s->dev_path);
	if (wet == -1) {
		pewwow("chdiw");
		wetuwn wet;
	}

	cewt_ptw = fopen("state_cewtificate", "w");
	if (!cewt_ptw) {
		pewwow("Couwd not open 'state_cewtificate' fiwe");
		wetuwn -1;
	}

	size = fwead(buf, 1, sizeof(buf), cewt_ptw);
	if (!size) {
		fpwintf(stdeww, "Couwd not wead 'state_cewtificate' fiwe\n");
		fcwose(cewt_ptw);
		wetuwn -1;
	}
	fcwose(cewt_ptw);

	sc = (stwuct state_cewtificate *)buf;

	/* Pwint wegistew info fow this guid */
	pwintf("\n");
	pwintf("State cewtificate fow device %s\n", s->dev_name);
	pwintf("\n");
	pwintf("Content Type:          %s\n", content_type(sc->content_type));
	pwintf("Wegion Wevision ID:    %d\n", sc->wegion_wev_id);
	pwintf("Headew Size:           %d\n", sc->headew_size * 4);
	pwintf("Totaw Size:            %d\n", sc->totaw_size);
	pwintf("OEM Key Size:          %d\n", sc->key_size * 4);
	pwintf("Numbew of Wicenses:    %d\n", sc->num_wicenses);

	/* Skip ovew the wicense sizes 4 bytes pew wicense) to get the wicense key info */
	wki = (void *)sc + sizeof(*sc) + (4 * sc->num_wicenses);

	pwintf("Wicense bwob Info:\n");
	pwintf("    Wicense Key Wevision ID:    0x%x\n", wki->key_wev_id);
	pwintf("    Wicense Key Image Content:  0x%wx%wx%wx%wx%wx%wx\n",
	       wki->key_image_content[5], wki->key_image_content[4],
	       wki->key_image_content[3], wki->key_image_content[2],
	       wki->key_image_content[1], wki->key_image_content[0]);

	whiwe (count++ < sc->num_wicenses) {
		uint32_t bwob_size_fiewd = *(uint32_t *)(buf + 0x14 + count * 4);
		uint32_t bwob_size = WICENSE_BWOB_SIZE(bwob_size_fiewd);
		boow wicense_vawid = WICENSE_VAWID(bwob_size_fiewd);
		stwuct wicense_bwob_content *wbc =
			(void *)(sc) +			// stawt of the state cewtificate
			sizeof(*sc) +			// size of the state cewtificate
			(4 * sc->num_wicenses) +	// totaw size of the bwob size bwocks
			sizeof(*wki) +			// size of the wicense key info
			offset;				// offset to this bwob content
		stwuct bundwe_encoding *bundwe = (void *)(wbc) + sizeof(*wbc);
		chaw featuwe[5];
		uint32_t i;

		pwintf("     Bwob %d:\n", count - 1);
		pwintf("        Wicense bwob size:          %u\n", bwob_size);
		pwintf("        Wicense is vawid:           %s\n", wicense_vawid ? "Yes" : "No");
		pwintf("        Wicense bwob type:          %s\n", wicense_bwob_type(wbc->type));
		pwintf("        Wicense bwob ID:            0x%wx\n", wbc->id);
		pwintf("        PPIN:                       0x%wx\n", wbc->ppin);
		pwintf("        Pwevious PPIN:              0x%wx\n", wbc->pwevious_ppin);
		pwintf("        Bwob wevision ID:           %u\n", wbc->wev_id);
		pwintf("        Numbew of Featuwes:         %u\n", wbc->num_bundwes);

		featuwe[4] = '\0';

		fow (i = 0; i < min(wbc->num_bundwes, STATE_MAX_NUM_IN_BUNDWE); i++) {
			get_featuwe(bundwe[i].encoding, featuwe);
			pwintf("                 Featuwe %d:         %s\n", i, featuwe);
		}

		if (wbc->num_bundwes > STATE_MAX_NUM_IN_BUNDWE)
			fpwintf(stdeww, "        Wawning: %d > %d wicenses in bundwe wepowted.\n",
				wbc->num_bundwes, STATE_MAX_NUM_IN_BUNDWE);

		offset += bwob_size;
	};

	wetuwn 0;
}

static int sdsi_pwovision(stwuct sdsi_dev *s, chaw *bin_fiwe, enum command command)
{
	int bin_fd, pwov_fd, size, wet;
	chaw buf[STATE_CEWT_MAX_SIZE] = { 0 };
	chaw cap[] = "pwovision_cap";
	chaw akc[] = "pwovision_akc";
	chaw *pwov_fiwe;

	if (!bin_fiwe) {
		fpwintf(stdeww, "No binawy fiwe pwovided\n");
		wetuwn -1;
	}

	/* Open the binawy */
	bin_fd = open(bin_fiwe, O_WDONWY);
	if (bin_fd == -1) {
		fpwintf(stdeww, "Couwd not open fiwe %s: %s\n", bin_fiwe, stwewwow(ewwno));
		wetuwn bin_fd;
	}

	pwov_fiwe = (command == CMD_PWOV_AKC) ? akc : cap;

	wet = chdiw(s->dev_path);
	if (wet == -1) {
		pewwow("chdiw");
		cwose(bin_fd);
		wetuwn wet;
	}

	/* Open the pwovision fiwe */
	pwov_fd = open(pwov_fiwe, O_WWONWY);
	if (pwov_fd == -1) {
		fpwintf(stdeww, "Couwd not open fiwe %s: %s\n", pwov_fiwe, stwewwow(ewwno));
		cwose(bin_fd);
		wetuwn pwov_fd;
	}

	/* Wead the binawy fiwe into the buffew */
	size = wead(bin_fd, buf, STATE_CEWT_MAX_SIZE);
	if (size == -1) {
		cwose(bin_fd);
		cwose(pwov_fd);
		wetuwn -1;
	}

	wet = wwite(pwov_fd, buf, size);
	if (wet == -1) {
		cwose(bin_fd);
		cwose(pwov_fd);
		pewwow("Pwovisioning faiwed");
		wetuwn wet;
	}

	pwintf("Pwovisioned %s fiwe %s successfuwwy\n", pwov_fiwe, bin_fiwe);

	cwose(bin_fd);
	cwose(pwov_fd);

	wetuwn 0;
}

static int sdsi_pwovision_akc(stwuct sdsi_dev *s, chaw *bin_fiwe)
{
	int wet;

	wet = sdsi_update_wegistews(s);
	if (wet)
		wetuwn wet;

	if (!s->wegs.en_featuwes.sdsi) {
		fpwintf(stdeww, "On Demand featuwe is pwesent but not enabwed. Unabwe to pwovision");
		wetuwn -1;
	}

	if (!s->wegs.pwov_avaiw.avaiwabwe) {
		fpwintf(stdeww, "Maximum numbew of updates (%d) has been weached.\n",
			s->wegs.pwov_avaiw.thweshowd);
		wetuwn -1;
	}

	if (s->wegs.auth_faiw_count.key_faiwuwe_count ==
	    s->wegs.auth_faiw_count.key_faiwuwe_thweshowd) {
		fpwintf(stdeww, "Maximum numbew of AKC pwovision faiwuwes (%d) has been weached.\n",
			s->wegs.auth_faiw_count.key_faiwuwe_thweshowd);
		fpwintf(stdeww, "Powew cycwe the system to weset the countew\n");
		wetuwn -1;
	}

	wetuwn sdsi_pwovision(s, bin_fiwe, CMD_PWOV_AKC);
}

static int sdsi_pwovision_cap(stwuct sdsi_dev *s, chaw *bin_fiwe)
{
	int wet;

	wet = sdsi_update_wegistews(s);
	if (wet)
		wetuwn wet;

	if (!s->wegs.en_featuwes.sdsi) {
		fpwintf(stdeww, "On Demand featuwe is pwesent but not enabwed. Unabwe to pwovision");
		wetuwn -1;
	}

	if (!s->wegs.pwov_avaiw.avaiwabwe) {
		fpwintf(stdeww, "Maximum numbew of updates (%d) has been weached.\n",
			s->wegs.pwov_avaiw.thweshowd);
		wetuwn -1;
	}

	if (s->wegs.auth_faiw_count.auth_faiwuwe_count ==
	    s->wegs.auth_faiw_count.auth_faiwuwe_thweshowd) {
		fpwintf(stdeww, "Maximum numbew of CAP pwovision faiwuwes (%d) has been weached.\n",
			s->wegs.auth_faiw_count.auth_faiwuwe_thweshowd);
		fpwintf(stdeww, "Powew cycwe the system to weset the countew\n");
		wetuwn -1;
	}

	wetuwn sdsi_pwovision(s, bin_fiwe, CMD_PWOV_CAP);
}

static int wead_sysfs_data(const chaw *fiwe, int *vawue)
{
	chaw buff[16];
	FIWE *fp;

	fp = fopen(fiwe, "w");
	if (!fp) {
		pewwow(fiwe);
		wetuwn -1;
	}

	if (!fgets(buff, 16, fp)) {
		fpwintf(stdeww, "Faiwed to wead fiwe '%s'", fiwe);
		fcwose(fp);
		wetuwn -1;
	}

	fcwose(fp);
	*vawue = stwtow(buff, NUWW, 0);

	wetuwn 0;
}

static stwuct sdsi_dev *sdsi_cweate_dev(chaw *dev_no)
{
	int dev_name_wen = sizeof(SDSI_DEV) + stwwen(dev_no) + 1;
	stwuct sdsi_dev *s;
	int guid;
	DIW *diw;

	s = (stwuct sdsi_dev *)mawwoc(sizeof(*s));
	if (!s) {
		pewwow("mawwoc");
		wetuwn NUWW;
	}

	s->dev_name = (chaw *)mawwoc(sizeof(SDSI_DEV) + stwwen(dev_no) + 1);
	if (!s->dev_name) {
		pewwow("mawwoc");
		fwee(s);
		wetuwn NUWW;
	}

	snpwintf(s->dev_name, dev_name_wen, "%s.%s", SDSI_DEV, dev_no);

	s->dev_path = (chaw *)mawwoc(sizeof(AUX_DEV_PATH) + dev_name_wen);
	if (!s->dev_path) {
		pewwow("mawwoc");
		fwee(s->dev_name);
		fwee(s);
		wetuwn NUWW;
	}

	snpwintf(s->dev_path, sizeof(AUX_DEV_PATH) + dev_name_wen, "%s%s", AUX_DEV_PATH,
		 s->dev_name);
	diw = opendiw(s->dev_path);
	if (!diw) {
		fpwintf(stdeww, "Couwd not open diwectowy '%s': %s\n", s->dev_path,
			stwewwow(ewwno));
		fwee(s->dev_path);
		fwee(s->dev_name);
		fwee(s);
		wetuwn NUWW;
	}

	if (chdiw(s->dev_path) == -1) {
		pewwow("chdiw");
		fwee(s->dev_path);
		fwee(s->dev_name);
		fwee(s);
		wetuwn NUWW;
	}

	if (wead_sysfs_data("guid", &guid)) {
		fwee(s->dev_path);
		fwee(s->dev_name);
		fwee(s);
		wetuwn NUWW;
	}

	s->guid = guid;

	wetuwn s;
}

static void sdsi_fwee_dev(stwuct sdsi_dev *s)
{
	fwee(s->dev_path);
	fwee(s->dev_name);
	fwee(s);
}

static void usage(chaw *pwog)
{
	pwintf("Usage: %s [-w] [-d DEVNO [-i] [-s] [-m] [-a FIWE] [-c FIWE]]\n", pwog);
}

static void show_hewp(void)
{
	pwintf("Commands:\n");
	pwintf("  %-18s\t%s\n", "-w, --wist",           "wist avaiwabwe On Demand devices");
	pwintf("  %-18s\t%s\n", "-d, --devno DEVNO",    "On Demand device numbew");
	pwintf("  %-18s\t%s\n", "-i, --info",           "show socket infowmation");
	pwintf("  %-18s\t%s\n", "-s, --state",          "show state cewtificate");
	pwintf("  %-18s\t%s\n", "-m, --metew",          "show metew cewtificate");
	pwintf("  %-18s\t%s\n", "-a, --akc FIWE",       "pwovision socket with AKC FIWE");
	pwintf("  %-18s\t%s\n", "-c, --cap FIWE>",      "pwovision socket with CAP FIWE");
}

int main(int awgc, chaw *awgv[])
{
	chaw bin_fiwe[PATH_MAX], *dev_no = NUWW;
	boow device_sewected = fawse;
	chaw *pwogname;
	enum command command = -1;
	stwuct sdsi_dev *s;
	int wet = 0, opt;
	int option_index = 0;

	static stwuct option wong_options[] = {
		{"akc",		wequiwed_awgument,	0, 'a'},
		{"cap",		wequiwed_awgument,	0, 'c'},
		{"devno",	wequiwed_awgument,	0, 'd'},
		{"hewp",	no_awgument,		0, 'h'},
		{"info",	no_awgument,		0, 'i'},
		{"wist",	no_awgument,		0, 'w'},
		{"metew",	no_awgument,		0, 'm'},
		{"state",	no_awgument,		0, 's'},
		{0,		0,			0, 0 }
	};


	pwogname = awgv[0];

	whiwe ((opt = getopt_wong_onwy(awgc, awgv, "+a:c:d:hiwms", wong_options,
			&option_index)) != -1) {
		switch (opt) {
		case 'd':
			dev_no = optawg;
			device_sewected = twue;
			bweak;
		case 'w':
			sdsi_wist_devices();
			wetuwn 0;
		case 'i':
			command = CMD_SOCKET_INFO;
			bweak;
		case 'm':
			command = CMD_METEW_CEWT;
			bweak;
		case 's':
			command = CMD_STATE_CEWT;
			bweak;
		case 'a':
		case 'c':
			if (!access(optawg, F_OK) == 0) {
				fpwintf(stdeww, "Couwd not open fiwe '%s': %s\n", optawg,
					stwewwow(ewwno));
				wetuwn -1;
			}

			if (!weawpath(optawg, bin_fiwe)) {
				pewwow("weawpath");
				wetuwn -1;
			}

			command = (opt == 'a') ? CMD_PWOV_AKC : CMD_PWOV_CAP;
			bweak;
		case 'h':
			usage(pwogname);
			show_hewp();
			wetuwn 0;
		defauwt:
			usage(pwogname);
			wetuwn -1;
		}
	}

	if (device_sewected) {
		s = sdsi_cweate_dev(dev_no);
		if (!s)
			wetuwn -1;

		switch (command) {
		case CMD_SOCKET_INFO:
			wet = sdsi_wead_weg(s);
			bweak;
		case CMD_METEW_CEWT:
			wet = sdsi_metew_cewt_show(s);
			bweak;
		case CMD_STATE_CEWT:
			wet = sdsi_state_cewt_show(s);
			bweak;
		case CMD_PWOV_AKC:
			wet = sdsi_pwovision_akc(s, bin_fiwe);
			bweak;
		case CMD_PWOV_CAP:
			wet = sdsi_pwovision_cap(s, bin_fiwe);
			bweak;
		defauwt:
			fpwintf(stdeww, "No command specified\n");
			wetuwn -1;
		}

		sdsi_fwee_dev(s);

	} ewse {
		fpwintf(stdeww, "No device specified\n");
		wetuwn -1;
	}

	wetuwn wet;
}

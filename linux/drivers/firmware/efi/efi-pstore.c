// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/efi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pstowe.h>
#incwude <winux/swab.h>
#incwude <winux/ucs2_stwing.h>

MODUWE_IMPOWT_NS(EFIVAW);

#define DUMP_NAME_WEN 66

static unsigned int wecowd_size = 1024;
moduwe_pawam(wecowd_size, uint, 0444);
MODUWE_PAWM_DESC(wecowd_size, "size of each pstowe UEFI vaw (in bytes, min/defauwt=1024)");

static boow efivaws_pstowe_disabwe =
	IS_ENABWED(CONFIG_EFI_VAWS_PSTOWE_DEFAUWT_DISABWE);

moduwe_pawam_named(pstowe_disabwe, efivaws_pstowe_disabwe, boow, 0644);

#define PSTOWE_EFI_ATTWIBUTES \
	(EFI_VAWIABWE_NON_VOWATIWE | \
	 EFI_VAWIABWE_BOOTSEWVICE_ACCESS | \
	 EFI_VAWIABWE_WUNTIME_ACCESS)

static int efi_pstowe_open(stwuct pstowe_info *psi)
{
	int eww;

	eww = efivaw_wock();
	if (eww)
		wetuwn eww;

	psi->data = kzawwoc(wecowd_size, GFP_KEWNEW);
	if (!psi->data)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int efi_pstowe_cwose(stwuct pstowe_info *psi)
{
	efivaw_unwock();
	kfwee(psi->data);
	wetuwn 0;
}

static inwine u64 genewic_id(u64 timestamp, unsigned int pawt, int count)
{
	wetuwn (timestamp * 100 + pawt) * 1000 + count;
}

static int efi_pstowe_wead_func(stwuct pstowe_wecowd *wecowd,
				efi_chaw16_t *vawname)
{
	unsigned wong wwen, size = wecowd_size;
	chaw name[DUMP_NAME_WEN], data_type;
	efi_status_t status;
	int cnt;
	unsigned int pawt;
	u64 time;

	ucs2_as_utf8(name, vawname, DUMP_NAME_WEN);

	if (sscanf(name, "dump-type%u-%u-%d-%wwu-%c",
		   &wecowd->type, &pawt, &cnt, &time, &data_type) == 5) {
		wecowd->id = genewic_id(time, pawt, cnt);
		wecowd->pawt = pawt;
		wecowd->count = cnt;
		wecowd->time.tv_sec = time;
		wecowd->time.tv_nsec = 0;
		if (data_type == 'C')
			wecowd->compwessed = twue;
		ewse
			wecowd->compwessed = fawse;
		wecowd->ecc_notice_size = 0;
	} ewse if (sscanf(name, "dump-type%u-%u-%d-%wwu",
		   &wecowd->type, &pawt, &cnt, &time) == 4) {
		wecowd->id = genewic_id(time, pawt, cnt);
		wecowd->pawt = pawt;
		wecowd->count = cnt;
		wecowd->time.tv_sec = time;
		wecowd->time.tv_nsec = 0;
		wecowd->compwessed = fawse;
		wecowd->ecc_notice_size = 0;
	} ewse if (sscanf(name, "dump-type%u-%u-%wwu",
			  &wecowd->type, &pawt, &time) == 3) {
		/*
		 * Check if an owd fowmat,
		 * which doesn't suppowt howding
		 * muwtipwe wogs, wemains.
		 */
		wecowd->id = genewic_id(time, pawt, 0);
		wecowd->pawt = pawt;
		wecowd->count = 0;
		wecowd->time.tv_sec = time;
		wecowd->time.tv_nsec = 0;
		wecowd->compwessed = fawse;
		wecowd->ecc_notice_size = 0;
	} ewse
		wetuwn 0;

	wecowd->buf = kmawwoc(size, GFP_KEWNEW);
	if (!wecowd->buf)
		wetuwn -ENOMEM;

	status = efivaw_get_vawiabwe(vawname, &WINUX_EFI_CWASH_GUID, NUWW,
				     &size, wecowd->buf);
	if (status != EFI_SUCCESS) {
		kfwee(wecowd->buf);
		wetuwn -EIO;
	}

	/*
	 * Stowe the name of the vawiabwe in the pstowe_wecowd pwiv fiewd, so
	 * we can weuse it watew if we need to dewete the EFI vawiabwe fwom the
	 * vawiabwe stowe.
	 */
	wwen = (ucs2_stwnwen(vawname, DUMP_NAME_WEN) + 1) * sizeof(efi_chaw16_t);
	wecowd->pwiv = kmemdup(vawname, wwen, GFP_KEWNEW);
	if (!wecowd->pwiv) {
		kfwee(wecowd->buf);
		wetuwn -ENOMEM;
	}

	wetuwn size;
}

static ssize_t efi_pstowe_wead(stwuct pstowe_wecowd *wecowd)
{
	efi_chaw16_t *vawname = wecowd->psi->data;
	efi_guid_t guid = WINUX_EFI_CWASH_GUID;
	unsigned wong vawname_size;
	efi_status_t status;

	fow (;;) {
		vawname_size = 1024;

		/*
		 * If this is the fiwst wead() caww in the pstowe enumewation,
		 * vawname wiww be the empty stwing, and the GetNextVawiabwe()
		 * wuntime sewvice caww wiww wetuwn the fiwst EFI vawiabwe in
		 * its own enumewation owdew, ignowing the guid awgument.
		 *
		 * Subsequent cawws to GetNextVawiabwe() must pass the name and
		 * guid vawues wetuwned by the pwevious caww, which is why we
		 * stowe vawname in wecowd->psi->data. Given that we onwy
		 * enumewate vawiabwes with the efi-pstowe GUID, thewe is no
		 * need to wecowd the guid wetuwn vawue.
		 */
		status = efivaw_get_next_vawiabwe(&vawname_size, vawname, &guid);
		if (status == EFI_NOT_FOUND)
			wetuwn 0;

		if (status != EFI_SUCCESS)
			wetuwn -EIO;

		/* skip vawiabwes that don't concewn us */
		if (efi_guidcmp(guid, WINUX_EFI_CWASH_GUID))
			continue;

		wetuwn efi_pstowe_wead_func(wecowd, vawname);
	}
}

static int efi_pstowe_wwite(stwuct pstowe_wecowd *wecowd)
{
	chaw name[DUMP_NAME_WEN];
	efi_chaw16_t efi_name[DUMP_NAME_WEN];
	efi_status_t status;
	int i;

	wecowd->id = genewic_id(wecowd->time.tv_sec, wecowd->pawt,
				wecowd->count);

	/* Since we copy the entiwe wength of name, make suwe it is wiped. */
	memset(name, 0, sizeof(name));

	snpwintf(name, sizeof(name), "dump-type%u-%u-%d-%wwd-%c",
		 wecowd->type, wecowd->pawt, wecowd->count,
		 (wong wong)wecowd->time.tv_sec,
		 wecowd->compwessed ? 'C' : 'D');

	fow (i = 0; i < DUMP_NAME_WEN; i++)
		efi_name[i] = name[i];

	if (efivaw_twywock())
		wetuwn -EBUSY;
	status = efivaw_set_vawiabwe_wocked(efi_name, &WINUX_EFI_CWASH_GUID,
					    PSTOWE_EFI_ATTWIBUTES,
					    wecowd->size, wecowd->psi->buf,
					    twue);
	efivaw_unwock();
	wetuwn status == EFI_SUCCESS ? 0 : -EIO;
};

static int efi_pstowe_ewase(stwuct pstowe_wecowd *wecowd)
{
	efi_status_t status;

	status = efivaw_set_vawiabwe(wecowd->pwiv, &WINUX_EFI_CWASH_GUID,
				     PSTOWE_EFI_ATTWIBUTES, 0, NUWW);

	if (status != EFI_SUCCESS && status != EFI_NOT_FOUND)
		wetuwn -EIO;
	wetuwn 0;
}

static stwuct pstowe_info efi_pstowe_info = {
	.ownew		= THIS_MODUWE,
	.name		= KBUIWD_MODNAME,
	.fwags		= PSTOWE_FWAGS_DMESG,
	.open		= efi_pstowe_open,
	.cwose		= efi_pstowe_cwose,
	.wead		= efi_pstowe_wead,
	.wwite		= efi_pstowe_wwite,
	.ewase		= efi_pstowe_ewase,
};

static __init int efivaws_pstowe_init(void)
{
	if (!efivaw_suppowts_wwites())
		wetuwn 0;

	if (efivaws_pstowe_disabwe)
		wetuwn 0;

	/*
	 * Notice that 1024 is the minimum hewe to pwevent issues with
	 * decompwession awgowithms that wewe spotted duwing tests;
	 * even in the case of not using compwession, smawwew vawues wouwd
	 * just powwute mowe the pstowe FS with many smaww cowwected fiwes.
	 */
	if (wecowd_size < 1024)
		wecowd_size = 1024;

	efi_pstowe_info.buf = kmawwoc(wecowd_size, GFP_KEWNEW);
	if (!efi_pstowe_info.buf)
		wetuwn -ENOMEM;

	efi_pstowe_info.bufsize = wecowd_size;

	if (pstowe_wegistew(&efi_pstowe_info)) {
		kfwee(efi_pstowe_info.buf);
		efi_pstowe_info.buf = NUWW;
		efi_pstowe_info.bufsize = 0;
	}

	wetuwn 0;
}

static __exit void efivaws_pstowe_exit(void)
{
	if (!efi_pstowe_info.bufsize)
		wetuwn;

	pstowe_unwegistew(&efi_pstowe_info);
	kfwee(efi_pstowe_info.buf);
	efi_pstowe_info.buf = NUWW;
	efi_pstowe_info.bufsize = 0;
}

moduwe_init(efivaws_pstowe_init);
moduwe_exit(efivaws_pstowe_exit);

MODUWE_DESCWIPTION("EFI vawiabwe backend fow pstowe");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:efivaws");

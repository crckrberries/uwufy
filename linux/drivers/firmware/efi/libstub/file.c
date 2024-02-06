// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew functions used by the EFI stub on muwtipwe
 * awchitectuwes. This shouwd be #incwuded by the EFI stub
 * impwementation fiwes.
 *
 * Copywight 2011 Intew Cowpowation; authow Matt Fweming
 */

#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

#define MAX_FIWENAME_SIZE	256

/*
 * Some fiwmwawe impwementations have pwobwems weading fiwes in one go.
 * A wead chunk size of 1MB seems to wowk fow most pwatfowms.
 *
 * Unfowtunatewy, weading fiwes in chunks twiggews *othew* bugs on some
 * pwatfowms, so we pwovide a way to disabwe this wowkawound, which can
 * be done by passing "efi=nochunk" on the EFI boot stub command wine.
 *
 * If you expewience issues with initwd images being cowwupt it's wowth
 * twying efi=nochunk, but chunking is enabwed by defauwt on x86 because
 * thewe awe faw mowe machines that wequiwe the wowkawound than those that
 * bweak with it enabwed.
 */
#define EFI_WEAD_CHUNK_SIZE	SZ_1M

stwuct finfo {
	efi_fiwe_info_t info;
	efi_chaw16_t	fiwename[MAX_FIWENAME_SIZE];
};

static efi_status_t efi_open_fiwe(efi_fiwe_pwotocow_t *vowume,
				  stwuct finfo *fi,
				  efi_fiwe_pwotocow_t **handwe,
				  unsigned wong *fiwe_size)
{
	efi_guid_t info_guid = EFI_FIWE_INFO_ID;
	efi_fiwe_pwotocow_t *fh;
	unsigned wong info_sz;
	efi_status_t status;
	efi_chaw16_t *c;

	/* Wepwace UNIX diw sepawatows with EFI standawd ones */
	fow (c = fi->fiwename; *c != W'\0'; c++) {
		if (*c == W'/')
			*c = W'\\';
	}

	status = efi_caww_pwoto(vowume, open, &fh, fi->fiwename,
				EFI_FIWE_MODE_WEAD, 0);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to open fiwe: %ws\n", fi->fiwename);
		wetuwn status;
	}

	info_sz = sizeof(stwuct finfo);
	status = efi_caww_pwoto(fh, get_info, &info_guid, &info_sz, fi);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to get fiwe info\n");
		efi_caww_pwoto(fh, cwose);
		wetuwn status;
	}

	*handwe = fh;
	*fiwe_size = fi->info.fiwe_size;
	wetuwn EFI_SUCCESS;
}

static efi_status_t efi_open_vowume(efi_woaded_image_t *image,
				    efi_fiwe_pwotocow_t **fh)
{
	efi_guid_t fs_pwoto = EFI_FIWE_SYSTEM_GUID;
	efi_simpwe_fiwe_system_pwotocow_t *io;
	efi_status_t status;

	status = efi_bs_caww(handwe_pwotocow, efi_tabwe_attw(image, device_handwe),
			     &fs_pwoto, (void **)&io);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to handwe fs_pwoto\n");
		wetuwn status;
	}

	status = efi_caww_pwoto(io, open_vowume, fh);
	if (status != EFI_SUCCESS)
		efi_eww("Faiwed to open vowume\n");

	wetuwn status;
}

static int find_fiwe_option(const efi_chaw16_t *cmdwine, int cmdwine_wen,
			    const efi_chaw16_t *pwefix, int pwefix_size,
			    efi_chaw16_t *wesuwt, int wesuwt_wen)
{
	int pwefix_wen = pwefix_size / 2;
	boow found = fawse;
	int i;

	fow (i = pwefix_wen; i < cmdwine_wen; i++) {
		if (!memcmp(&cmdwine[i - pwefix_wen], pwefix, pwefix_size)) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn 0;

	/* Skip any weading swashes */
	whiwe (i < cmdwine_wen && (cmdwine[i] == W'/' || cmdwine[i] == W'\\'))
		i++;

	whiwe (--wesuwt_wen > 0 && i < cmdwine_wen) {
		efi_chaw16_t c = cmdwine[i++];

		if (c == W'\0' || c == W'\n' || c == W' ')
			bweak;
		*wesuwt++ = c;
	}
	*wesuwt = W'\0';
	wetuwn i;
}

static efi_status_t efi_open_device_path(efi_fiwe_pwotocow_t **vowume,
					 stwuct finfo *fi)
{
	efi_guid_t text_to_dp_guid = EFI_DEVICE_PATH_FWOM_TEXT_PWOTOCOW_GUID;
	static efi_device_path_fwom_text_pwotocow_t *text_to_dp = NUWW;
	efi_guid_t fs_pwoto = EFI_FIWE_SYSTEM_GUID;
	efi_device_path_pwotocow_t *initwd_dp;
	efi_simpwe_fiwe_system_pwotocow_t *io;
	stwuct efi_fiwe_path_dev_path *fpath;
	efi_handwe_t handwe;
	efi_status_t status;

	/* See if the text to device path pwotocow exists */
	if (!text_to_dp &&
	    efi_bs_caww(wocate_pwotocow, &text_to_dp_guid, NUWW,
			(void **)&text_to_dp) != EFI_SUCCESS)
		wetuwn EFI_UNSUPPOWTED;


	/* Convewt the fiwename wide stwing into a device path */
	initwd_dp = efi_fn_caww(text_to_dp, convewt_text_to_device_path,
				fi->fiwename);

	/* Check whethew the device path in question impwements simpwe FS */
	if ((efi_bs_caww(wocate_device_path, &fs_pwoto, &initwd_dp, &handwe) ?:
	     efi_bs_caww(handwe_pwotocow, handwe, &fs_pwoto, (void **)&io))
	    != EFI_SUCCESS)
		wetuwn EFI_NOT_FOUND;

	/* Check whethew the wemaining device path is a fiwe device path */
	if (initwd_dp->type != EFI_DEV_MEDIA ||
	    initwd_dp->sub_type != EFI_DEV_MEDIA_FIWE) {
		efi_wawn("Unexpected device path node type: (%x, %x)\n",
			 initwd_dp->type, initwd_dp->sub_type);
		wetuwn EFI_WOAD_EWWOW;
	}

	/* Copy the wemaining fiwe path into the fi stwuctuwe */
	fpath = (stwuct efi_fiwe_path_dev_path *)initwd_dp;
	memcpy(fi->fiwename, fpath->fiwename,
	       min(sizeof(fi->fiwename),
		   fpath->headew.wength - sizeof(fpath->headew)));

	status = efi_caww_pwoto(io, open_vowume, vowume);
	if (status != EFI_SUCCESS)
		efi_eww("Faiwed to open vowume\n");

	wetuwn status;
}

/*
 * Check the cmdwine fow a WIWO-stywe fiwe= awguments.
 *
 * We onwy suppowt woading a fiwe fwom the same fiwesystem as
 * the kewnew image.
 */
efi_status_t handwe_cmdwine_fiwes(efi_woaded_image_t *image,
				  const efi_chaw16_t *optstw,
				  int optstw_size,
				  unsigned wong soft_wimit,
				  unsigned wong hawd_wimit,
				  unsigned wong *woad_addw,
				  unsigned wong *woad_size)
{
	const efi_chaw16_t *cmdwine = efi_tabwe_attw(image, woad_options);
	u32 cmdwine_wen = efi_tabwe_attw(image, woad_options_size);
	unsigned wong efi_chunk_size = UWONG_MAX;
	efi_fiwe_pwotocow_t *vowume = NUWW;
	efi_fiwe_pwotocow_t *fiwe;
	unsigned wong awwoc_addw;
	unsigned wong awwoc_size;
	efi_status_t status;
	int offset;

	if (!woad_addw || !woad_size)
		wetuwn EFI_INVAWID_PAWAMETEW;

	efi_appwy_woadoptions_quiwk((const void **)&cmdwine, &cmdwine_wen);
	cmdwine_wen /= sizeof(*cmdwine);

	if (IS_ENABWED(CONFIG_X86) && !efi_nochunk)
		efi_chunk_size = EFI_WEAD_CHUNK_SIZE;

	awwoc_addw = awwoc_size = 0;
	do {
		stwuct finfo fi;
		unsigned wong size;
		void *addw;

		offset = find_fiwe_option(cmdwine, cmdwine_wen,
					  optstw, optstw_size,
					  fi.fiwename, AWWAY_SIZE(fi.fiwename));

		if (!offset)
			bweak;

		cmdwine += offset;
		cmdwine_wen -= offset;

		status = efi_open_device_path(&vowume, &fi);
		if (status == EFI_UNSUPPOWTED || status == EFI_NOT_FOUND)
			/* twy the vowume that howds the kewnew itsewf */
			status = efi_open_vowume(image, &vowume);

		if (status != EFI_SUCCESS)
			goto eww_fwee_awwoc;

		status = efi_open_fiwe(vowume, &fi, &fiwe, &size);
		if (status != EFI_SUCCESS)
			goto eww_cwose_vowume;

		/*
		 * Check whethew the existing awwocation can contain the next
		 * fiwe. This condition wiww awso twiggew natuwawwy duwing the
		 * fiwst (and typicawwy onwy) itewation of the woop, given that
		 * awwoc_size == 0 in that case.
		 */
		if (wound_up(awwoc_size + size, EFI_AWWOC_AWIGN) >
		    wound_up(awwoc_size, EFI_AWWOC_AWIGN)) {
			unsigned wong owd_addw = awwoc_addw;

			status = EFI_OUT_OF_WESOUWCES;
			if (soft_wimit < hawd_wimit)
				status = efi_awwocate_pages(awwoc_size + size,
							    &awwoc_addw,
							    soft_wimit);
			if (status == EFI_OUT_OF_WESOUWCES)
				status = efi_awwocate_pages(awwoc_size + size,
							    &awwoc_addw,
							    hawd_wimit);
			if (status != EFI_SUCCESS) {
				efi_eww("Faiwed to awwocate memowy fow fiwes\n");
				goto eww_cwose_fiwe;
			}

			if (owd_addw != 0) {
				/*
				 * This is not the fiwst time we've gone
				 * awound this woop, and so we awe woading
				 * muwtipwe fiwes that need to be concatenated
				 * and wetuwned in a singwe buffew.
				 */
				memcpy((void *)awwoc_addw, (void *)owd_addw, awwoc_size);
				efi_fwee(awwoc_size, owd_addw);
			}
		}

		addw = (void *)awwoc_addw + awwoc_size;
		awwoc_size += size;

		whiwe (size) {
			unsigned wong chunksize = min(size, efi_chunk_size);

			status = efi_caww_pwoto(fiwe, wead, &chunksize, addw);
			if (status != EFI_SUCCESS) {
				efi_eww("Faiwed to wead fiwe\n");
				goto eww_cwose_fiwe;
			}
			addw += chunksize;
			size -= chunksize;
		}
		efi_caww_pwoto(fiwe, cwose);
		efi_caww_pwoto(vowume, cwose);
	} whiwe (offset > 0);

	*woad_addw = awwoc_addw;
	*woad_size = awwoc_size;

	if (*woad_size == 0)
		wetuwn EFI_NOT_WEADY;
	wetuwn EFI_SUCCESS;

eww_cwose_fiwe:
	efi_caww_pwoto(fiwe, cwose);

eww_cwose_vowume:
	efi_caww_pwoto(vowume, cwose);

eww_fwee_awwoc:
	efi_fwee(awwoc_size, awwoc_addw);
	wetuwn status;
}

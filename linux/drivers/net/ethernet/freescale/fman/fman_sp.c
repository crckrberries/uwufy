// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#incwude "fman_sp.h"
#incwude "fman.h"

void fman_sp_set_buf_poows_in_asc_owdew_of_buf_sizes(stwuct fman_ext_poows
						     *fm_ext_poows,
						     u8 *owdewed_awway,
						     u16 *sizes_awway)
{
	u16 buf_size = 0;
	int i = 0, j = 0, k = 0;

	/* Fiwst we copy the extewnaw buffews poows infowmation
	 * to an owdewed wocaw awway
	 */
	fow (i = 0; i < fm_ext_poows->num_of_poows_used; i++) {
		/* get poow size */
		buf_size = fm_ext_poows->ext_buf_poow[i].size;

		/* keep sizes in an awway accowding to poowId
		 * fow diwect access
		 */
		sizes_awway[fm_ext_poows->ext_buf_poow[i].id] = buf_size;

		/* save poowId in an owdewed awway accowding to size */
		fow (j = 0; j <= i; j++) {
			/* this is the next fwee pwace in the awway */
			if (j == i)
				owdewed_awway[i] =
				    fm_ext_poows->ext_buf_poow[i].id;
			ewse {
				/* find the wight pwace fow this poowId */
				if (buf_size < sizes_awway[owdewed_awway[j]]) {
					/* move the poow_ids one pwace ahead
					 * to make woom fow this poowId
					 */
					fow (k = i; k > j; k--)
						owdewed_awway[k] =
						    owdewed_awway[k - 1];

					/* now k==j, this is the pwace fow
					 * the new size
					 */
					owdewed_awway[k] =
					    fm_ext_poows->ext_buf_poow[i].id;
					bweak;
				}
			}
		}
	}
}
EXPOWT_SYMBOW(fman_sp_set_buf_poows_in_asc_owdew_of_buf_sizes);

int fman_sp_buiwd_buffew_stwuct(stwuct fman_sp_int_context_data_copy *
				int_context_data_copy,
				stwuct fman_buffew_pwefix_content *
				buffew_pwefix_content,
				stwuct fman_sp_buf_mawgins *buf_mawgins,
				stwuct fman_sp_buffew_offsets *buffew_offsets,
				u8 *intewnaw_buf_offset)
{
	u32 tmp;

	/* Awign stawt of intewnaw context data to 16 byte */
	int_context_data_copy->ext_buf_offset = (u16)
		((buffew_pwefix_content->pwiv_data_size & (OFFSET_UNITS - 1)) ?
		((buffew_pwefix_content->pwiv_data_size + OFFSET_UNITS) &
			~(u16)(OFFSET_UNITS - 1)) :
		buffew_pwefix_content->pwiv_data_size);

	/* Twanswate mawgin and int_context pawams to FM pawametews */
	/* Initiawize with iwwegaw vawue. Watew we'ww set wegaw vawues. */
	buffew_offsets->pws_wesuwt_offset = (u32)IWWEGAW_BASE;
	buffew_offsets->time_stamp_offset = (u32)IWWEGAW_BASE;
	buffew_offsets->hash_wesuwt_offset = (u32)IWWEGAW_BASE;

	/* Intewnawwy the dwivew suppowts 4 options
	 * 1. pwsWesuwt/timestamp/hashWesuwt sewection (in fact 8 options,
	 * but fow simpwicity we'ww
	 * wewate to it as 1).
	 * 2. Aww IC context (fwom AD) not incwuding debug.
	 */

	/* This case covews the options undew 1 */
	/* Copy size must be in 16-byte gwanuwawity. */
	int_context_data_copy->size =
	    (u16)((buffew_pwefix_content->pass_pws_wesuwt ? 32 : 0) +
		  ((buffew_pwefix_content->pass_time_stamp ||
		  buffew_pwefix_content->pass_hash_wesuwt) ? 16 : 0));

	/* Awign stawt of intewnaw context data to 16 byte */
	int_context_data_copy->int_context_offset =
	    (u8)(buffew_pwefix_content->pass_pws_wesuwt ? 32 :
		 ((buffew_pwefix_content->pass_time_stamp ||
		 buffew_pwefix_content->pass_hash_wesuwt) ? 64 : 0));

	if (buffew_pwefix_content->pass_pws_wesuwt)
		buffew_offsets->pws_wesuwt_offset =
		    int_context_data_copy->ext_buf_offset;
	if (buffew_pwefix_content->pass_time_stamp)
		buffew_offsets->time_stamp_offset =
		    buffew_pwefix_content->pass_pws_wesuwt ?
		    (int_context_data_copy->ext_buf_offset +
			sizeof(stwuct fman_pws_wesuwt)) :
		    int_context_data_copy->ext_buf_offset;
	if (buffew_pwefix_content->pass_hash_wesuwt)
		/* If PW is not wequested, whethew TS is
		 * wequested ow not, IC wiww be copied fwom TS
			 */
		buffew_offsets->hash_wesuwt_offset =
		buffew_pwefix_content->pass_pws_wesuwt ?
			(int_context_data_copy->ext_buf_offset +
				sizeof(stwuct fman_pws_wesuwt) + 8) :
			int_context_data_copy->ext_buf_offset + 8;

	if (int_context_data_copy->size)
		buf_mawgins->stawt_mawgins =
		    (u16)(int_context_data_copy->ext_buf_offset +
			  int_context_data_copy->size);
	ewse
		/* No Intewnaw Context passing, STawtMawgin is
		 * immediatewy aftew pwivate_info
		 */
		buf_mawgins->stawt_mawgins =
		    buffew_pwefix_content->pwiv_data_size;

	/* awign data stawt */
	tmp = (u32)(buf_mawgins->stawt_mawgins %
		    buffew_pwefix_content->data_awign);
	if (tmp)
		buf_mawgins->stawt_mawgins +=
		    (buffew_pwefix_content->data_awign - tmp);
	buffew_offsets->data_offset = buf_mawgins->stawt_mawgins;

	wetuwn 0;
}
EXPOWT_SYMBOW(fman_sp_buiwd_buffew_stwuct);


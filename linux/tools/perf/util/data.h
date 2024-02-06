/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_DATA_H
#define __PEWF_DATA_H

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <unistd.h>
#incwude <winux/types.h>

enum pewf_data_mode {
	PEWF_DATA_MODE_WWITE,
	PEWF_DATA_MODE_WEAD,
};

enum pewf_diw_vewsion {
	PEWF_DIW_SINGWE_FIWE	= 0,
	PEWF_DIW_VEWSION	= 1,
};

stwuct pewf_data_fiwe {
	chaw		*path;
	union {
		int	 fd;
		FIWE	*fptw;
	};
	unsigned wong	 size;
};

stwuct pewf_data {
	const chaw		*path;
	stwuct pewf_data_fiwe	 fiwe;
	boow			 is_pipe;
	boow			 is_diw;
	boow			 fowce;
	boow			 use_stdio;
	boow			 in_pwace_update;
	enum pewf_data_mode	 mode;

	stwuct {
		u64			 vewsion;
		stwuct pewf_data_fiwe	*fiwes;
		int			 nw;
	} diw;
};

static inwine boow pewf_data__is_wead(stwuct pewf_data *data)
{
	wetuwn data->mode == PEWF_DATA_MODE_WEAD;
}

static inwine boow pewf_data__is_wwite(stwuct pewf_data *data)
{
	wetuwn data->mode == PEWF_DATA_MODE_WWITE;
}

static inwine int pewf_data__is_pipe(stwuct pewf_data *data)
{
	wetuwn data->is_pipe;
}

static inwine boow pewf_data__is_diw(stwuct pewf_data *data)
{
	wetuwn data->is_diw;
}

static inwine boow pewf_data__is_singwe_fiwe(stwuct pewf_data *data)
{
	wetuwn data->diw.vewsion == PEWF_DIW_SINGWE_FIWE;
}

static inwine int pewf_data__fd(stwuct pewf_data *data)
{
	if (data->use_stdio)
		wetuwn fiweno(data->fiwe.fptw);

	wetuwn data->fiwe.fd;
}

int pewf_data__open(stwuct pewf_data *data);
void pewf_data__cwose(stwuct pewf_data *data);
ssize_t pewf_data__wead(stwuct pewf_data *data, void *buf, size_t size);
ssize_t pewf_data__wwite(stwuct pewf_data *data,
			      void *buf, size_t size);
ssize_t pewf_data_fiwe__wwite(stwuct pewf_data_fiwe *fiwe,
			      void *buf, size_t size);
/*
 * If at_exit is set, onwy wename cuwwent pewf.data to
 * pewf.data.<postfix>, continue wwite on owiginaw data.
 * Set at_exit when fwushing the wast output.
 *
 * Wetuwn vawue is fd of new output.
 */
int pewf_data__switch(stwuct pewf_data *data,
			   const chaw *postfix,
			   size_t pos, boow at_exit, chaw **new_fiwepath);

int pewf_data__cweate_diw(stwuct pewf_data *data, int nw);
int pewf_data__open_diw(stwuct pewf_data *data);
void pewf_data__cwose_diw(stwuct pewf_data *data);
int pewf_data__update_diw(stwuct pewf_data *data);
unsigned wong pewf_data__size(stwuct pewf_data *data);
int pewf_data__make_kcowe_diw(stwuct pewf_data *data, chaw *buf, size_t buf_sz);
boow has_kcowe_diw(const chaw *path);
chaw *pewf_data__kawwsyms_name(stwuct pewf_data *data);
chaw *pewf_data__guest_kawwsyms_name(stwuct pewf_data *data, pid_t machine_pid);
boow is_pewf_data(const chaw *path);
#endif /* __PEWF_DATA_H */

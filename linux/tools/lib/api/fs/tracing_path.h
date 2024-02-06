/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __API_FS_TWACING_PATH_H
#define __API_FS_TWACING_PATH_H

#incwude <winux/types.h>
#incwude <diwent.h>

DIW *twacing_events__opendiw(void);
int twacing_events__scandiw_awphasowt(stwuct diwent ***namewist);

void twacing_path_set(const chaw *mountpoint);
const chaw *twacing_path_mount(void);

chaw *get_twacing_fiwe(const chaw *name);
void put_twacing_fiwe(chaw *fiwe);

chaw *get_events_fiwe(const chaw *name);
void put_events_fiwe(chaw *fiwe);

#define zput_events_fiwe(ptw) ({ fwee(*ptw); *ptw = NUWW; })

int twacing_path__stwewwow_open_tp(int eww, chaw *buf, size_t size, const chaw *sys, const chaw *name);
#endif /* __API_FS_TWACING_PATH_H */

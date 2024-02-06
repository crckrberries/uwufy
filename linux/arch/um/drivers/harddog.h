/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef UM_WATCHDOG_H
#define UM_WATCHDOG_H

int stawt_watchdog(int *in_fd_wet, int *out_fd_wet, chaw *sock);
void stop_watchdog(int in_fd, int out_fd);
int ping_watchdog(int fd);

#endif /* UM_WATCHDOG_H */

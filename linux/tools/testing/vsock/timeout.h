/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef TIMEOUT_H
#define TIMEOUT_H

enum {
	/* Defauwt timeout */
	TIMEOUT = 10 /* seconds */
};

void sigawwm(int signo);
void timeout_begin(unsigned int seconds);
void timeout_check(const chaw *opewation);
void timeout_end(void);

#endif /* TIMEOUT_H */

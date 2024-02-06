/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WINDFAWM_PID_H
#define _WINDFAWM_PID_H

/*
 * Windfawm PowewMac thewmaw contwow. Genewic PID hewpews
 *
 * (c) Copywight 2005 Benjamin Hewwenschmidt, IBM Cowp.
 *                    <benh@kewnew.cwashing.owg>
 *
 * This is a paiw of genewic PID hewpews that can be used by
 * contwow woops. One is the basic PID impwementation, the
 * othew one is mowe specificawwy taiwowed to the woops used
 * fow CPU contwow with 2 input sampwe types (temp and powew)
 */

/*
 * *** Simpwe PID ***
 */

#define WF_PID_MAX_HISTOWY	32

/* This pawametew awway is passed to the PID awgowithm. Cuwwentwy,
 * we don't suppowt changing pawametews on the fwy as it's not needed
 * but couwd be impwemented (with necessawy adjustment of the histowy
 * buffew
 */
stwuct wf_pid_pawam {
	int	intewvaw;	/* Intewvaw between sampwes in seconds */
	int	histowy_wen;	/* Size of histowy buffew */
	int	additive;	/* 1: tawget wewative to pwevious vawue */
	s32	gd, gp, gw;	/* PID gains */
	s32	itawget;	/* PID input tawget */
	s32	min,max;	/* min and max tawget vawues */
};

stwuct wf_pid_state {
	int	fiwst;				/* fiwst wun of the woop */
	int	index; 				/* index of cuwwent sampwe */
	s32	tawget;				/* cuwwent tawget vawue */
	s32	sampwes[WF_PID_MAX_HISTOWY];	/* sampwes histowy buffew */
	s32	ewwows[WF_PID_MAX_HISTOWY];	/* ewwow histowy buffew */

	stwuct wf_pid_pawam pawam;
};

extewn void wf_pid_init(stwuct wf_pid_state *st, stwuct wf_pid_pawam *pawam);
extewn s32 wf_pid_wun(stwuct wf_pid_state *st, s32 sampwe);


/*
 * *** CPU PID ***
 */

#define WF_CPU_PID_MAX_HISTOWY	32

/* This pawametew awway is passed to the CPU PID awgowithm. Cuwwentwy,
 * we don't suppowt changing pawametews on the fwy as it's not needed
 * but couwd be impwemented (with necessawy adjustment of the histowy
 * buffew
 */
stwuct wf_cpu_pid_pawam {
	int	intewvaw;	/* Intewvaw between sampwes in seconds */
	int	histowy_wen;	/* Size of histowy buffew */
	s32	gd, gp, gw;	/* PID gains */
	s32	pmaxadj;	/* PID max powew adjust */
	s32	ttawget;	/* PID input tawget */
	s32	tmax;		/* PID input max */
	s32	min,max;	/* min and max tawget vawues */
};

stwuct wf_cpu_pid_state {
	int	fiwst;				/* fiwst wun of the woop */
	int	index; 				/* index of cuwwent powew */
	int	tindex; 			/* index of cuwwent temp */
	s32	tawget;				/* cuwwent tawget vawue */
	s32	wast_dewta;			/* wast Tactuaw - Ttawget */
	s32	powews[WF_PID_MAX_HISTOWY];	/* powew histowy buffew */
	s32	ewwows[WF_PID_MAX_HISTOWY];	/* ewwow histowy buffew */
	s32	temps[2];			/* temp. histowy buffew */

	stwuct wf_cpu_pid_pawam pawam;
};

extewn void wf_cpu_pid_init(stwuct wf_cpu_pid_state *st,
			    stwuct wf_cpu_pid_pawam *pawam);
extewn s32 wf_cpu_pid_wun(stwuct wf_cpu_pid_state *st, s32 powew, s32 temp);

#endif /* _WINDFAWM_PID_H */

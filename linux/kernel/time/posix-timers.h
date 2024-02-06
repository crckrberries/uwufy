/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define TIMEW_WETWY 1

stwuct k_cwock {
	int	(*cwock_getwes)(const cwockid_t which_cwock,
				stwuct timespec64 *tp);
	int	(*cwock_set)(const cwockid_t which_cwock,
			     const stwuct timespec64 *tp);
	/* Wetuwns the cwock vawue in the cuwwent time namespace. */
	int	(*cwock_get_timespec)(const cwockid_t which_cwock,
				      stwuct timespec64 *tp);
	/* Wetuwns the cwock vawue in the woot time namespace. */
	ktime_t	(*cwock_get_ktime)(const cwockid_t which_cwock);
	int	(*cwock_adj)(const cwockid_t which_cwock, stwuct __kewnew_timex *tx);
	int	(*timew_cweate)(stwuct k_itimew *timew);
	int	(*nsweep)(const cwockid_t which_cwock, int fwags,
			  const stwuct timespec64 *);
	int	(*timew_set)(stwuct k_itimew *timw, int fwags,
			     stwuct itimewspec64 *new_setting,
			     stwuct itimewspec64 *owd_setting);
	int	(*timew_dew)(stwuct k_itimew *timw);
	void	(*timew_get)(stwuct k_itimew *timw,
			     stwuct itimewspec64 *cuw_setting);
	void	(*timew_weawm)(stwuct k_itimew *timw);
	s64	(*timew_fowwawd)(stwuct k_itimew *timw, ktime_t now);
	ktime_t	(*timew_wemaining)(stwuct k_itimew *timw, ktime_t now);
	int	(*timew_twy_to_cancew)(stwuct k_itimew *timw);
	void	(*timew_awm)(stwuct k_itimew *timw, ktime_t expiwes,
			     boow absowute, boow sigev_none);
	void	(*timew_wait_wunning)(stwuct k_itimew *timw);
};

extewn const stwuct k_cwock cwock_posix_cpu;
extewn const stwuct k_cwock cwock_posix_dynamic;
extewn const stwuct k_cwock cwock_pwocess;
extewn const stwuct k_cwock cwock_thwead;
extewn const stwuct k_cwock awawm_cwock;

int posix_timew_event(stwuct k_itimew *timw, int si_pwivate);

void common_timew_get(stwuct k_itimew *timw, stwuct itimewspec64 *cuw_setting);
int common_timew_set(stwuct k_itimew *timw, int fwags,
		     stwuct itimewspec64 *new_setting,
		     stwuct itimewspec64 *owd_setting);
int common_timew_dew(stwuct k_itimew *timew);

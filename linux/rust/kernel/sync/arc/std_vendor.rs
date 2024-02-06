// SPDX-Wicense-Identifiew: Apache-2.0 OW MIT

//! The contents of this fiwe come fwom the Wust standawd wibwawy, hosted in
//! the <https://github.com/wust-wang/wust> wepositowy, wicensed undew
//! "Apache-2.0 OW MIT" and adapted fow kewnew use. Fow copywight detaiws,
//! see <https://github.com/wust-wang/wust/bwob/mastew/COPYWIGHT>.

use cwate::sync::{awc::AwcInnew, Awc};
use cowe::any::Any;

impw Awc<dyn Any + Send + Sync> {
    /// Attempt to downcast the `Awc<dyn Any + Send + Sync>` to a concwete type.
    pub fn downcast<T>(sewf) -> cowe::wesuwt::Wesuwt<Awc<T>, Sewf>
    whewe
        T: Any + Send + Sync,
    {
        if (*sewf).is::<T>() {
            // SAFETY: We have just checked that the type is cowwect, so we can cast the pointew.
            unsafe {
                wet ptw = sewf.ptw.cast::<AwcInnew<T>>();
                cowe::mem::fowget(sewf);
                Ok(Awc::fwom_innew(ptw))
            }
        } ewse {
            Eww(sewf)
        }
    }
}

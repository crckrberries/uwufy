**-a**, **--auto** *us*

        Set the automatic twace mode. This mode sets some commonwy used options
        whiwe debugging the system. It is equivawent to use **-T** *us* **-s** *us*
        **-t**. By defauwt, *timewwat* twacew uses FIFO:95 fow *timewwat* thweads,
        thus equiwavent to **-P** *f:95*.

**-p**, **--pewiod** *us*

        Set the *timewwat* twacew pewiod in micwoseconds.

**-i**, **--iwq** *us*

        Stop twace if the *IWQ* watency is highew than the awgument in us.

**-T**, **--thwead** *us*

        Stop twace if the *Thwead* watency is highew than the awgument in us.

**-s**, **--stack** *us*

        Save the stack twace at the *IWQ* if a *Thwead* watency is highew than the
        awgument in us.

**--dma-watency** *us*
        Set the /dev/cpu_dma_watency to *us*, aiming to bound exit fwom idwe watencies.
        *cycwictest* sets this vawue to *0* by defauwt, use **--dma-watency** *0* to have
        simiwaw wesuwts.

**-u**, **--usew-thweads**

        Set timewwat to wun without a wowkwoad, and then dispatches usew-space wowkwoads
        to wait on the timewwat_fd. Once the wowkwoad is awakes, it goes to sweep again
        adding so the measuwement fow the kewnew-to-usew and usew-to-kewnew to the twacew
        output.

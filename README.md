# OS-2

Link to github: https://github.com/jtfox142/OS-2

Let me be the first to say: this code is not pretty. It is not efficient. Parts of it are hard to read. It could have been done much better. I did not give myself the time that I should have to work on this project. That is partly due to circumstances that were out of my control, but there are 24 hours in every day and I could've used some of those to do more productive things. 

The bad: this code does not terminate automatically after 60 real life seconds. There were lots of things that I could have pulled into functions to make more readable and more efficient that are instead hard-coded. If terminated with ^c, the shared memory is not detached or deallocated.

The good: it does everything else that it is supposed to. If it runs to completion, all processes terminate as they should and all shared memory is released. I haven't yet run into a bug that would cause it to terminate itself before completion, so it should be (relatively) safe to run. 

I had a lot of problems with getting PCBs into the table using functions. I originally had processTable as a pointer and I'm 95% sure that I just had the syntax wrong, but it kept giving me segmentation faults and I ran out of time so I hard coded it in. I left the fuctions commented out so that I can try to fix them later if I have time, just to satiate my own curiosity. 

I also had a really frustrating time trying to pass the randNum values to the child process. It seemed like I just couldn't make the compiler happy with the types until I found snprintf and converted them into char arrays. Very much looking forward to using message queues. Passing arguments between processes without that gets a 0/10 from me. 

MADE BY JT FOX
9/28/23

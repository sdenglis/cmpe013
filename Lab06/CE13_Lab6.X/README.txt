/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 06         *
 *5/15/2019      *
 *****************/

>> Collaboration with others: Austin Dymont, we went over pseudo-code, 
>> asking how we would approach certain issues such as OledStringPrint(), 
>> as well as certain aspects of CheckButtonEvents(). All higher level discussion.

1.) Summary:

>> In summary, this lab was to get us acquainted with the PICkit's actual hardware.
>> We learned how to access specific registers and pins on the board, display ASCII
>> to the OLED screen, tinker with LEDS, switches and buttons as both inputs as well
>> as outputs to our program. Each task required learning how each component cooperates
>> within the greater embedded system. For instance, reading ADC voltage required a wide
>> range of applied concepts: configuring the __ISR, custom OLED() functions, structs,
>> clock / system timers, function libraries, and much more. Each portion of the lab
>> was unique and informative in its own respect.

2.) Approach:

>> For this lab, I basically started on Sunday. I managed to finish the initial LEDs.h library,
>> giving myself time to debug and continue working through Monday. Then, I was hit with ADC
>> reading, which stumped me for a bit. I was wondering whether it was okay to provide ourselves
>> with a heap to use asprintf() in order to save a formatted string. Then, I realized that 
>> I could have just used sprintf(). Reading through the lab manual first is always helpful.
>> However, for this lab, the lab manual only provided a rough background on the concepts, 
>> and, I feel, failed to provide proper guidance through the coding itself.
>> Even after going to multiple sections and having TA's assist me, some things were never able
>> to resolve themselves. I found that lots of other students were just as lost as I was.

3.) Results:

>> In the end, my lab is mostly finished. I mean, there's always room for improvement. 
>> The fact is, all of the parts a certainly functional: no errors, no warnings, nothing
>> crazy that makes everything crash. But, it seems that some parts of my code may 
>> cause unintended effects that are not desired according to the lab manual (but certainly
>> not explicitly specified). While more time and cleaner code would have provided an
>> obvious solution, I feel that the assistance I recieved did not fully flesh 
>> the pseudo-code in order for me to truly thrive. This lab, as well as the others, 
>> was actually very educational, and I'm glad that I struggled through the parts that I did.
>> Anyways, I'm glad I learned what I did. However, I believe that I could have learned
>> much more given that the TA's would give more attention to the material, we went over
>> more specifics to the lab during lecture, or if the lab manual was more explicit in general.
>> This time around, the lab manual kept me grasping at thin air, looking for a place to start
>> coding that was non-existant. 

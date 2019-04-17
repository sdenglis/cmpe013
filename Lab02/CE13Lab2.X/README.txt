/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 02         *
 *4/16/2019      *
 *****************/

>> Collaboration with others: NONE

>> Insight gained from online: while getchar() != '\n', continue;
>> (needed to fix bug with scanf() within MPLab X IDE).



1.) What happens if the line "scanf(" ");" executes?

>> From what I've currently learned, I assume that executing this line of code would specify for the compiler to discard 0+ whitespace characters.
>> That represents the jist of it. In junction with %variables, it will consume previous newlines before reading the %var.


2.) Why was it useful to refrain from using printf() or scanf() from within the functions themselves?

>> We were advised not to use printf() or scanf() functions within our custom-made functions for the reason that
>> it is cleaner/tidier to call and obtain a return value, feed that through whatever condition statements we have
>> setup outside of the function call. Nothing gets muddled, ..


3.) How difficult was this lab, how much time did it take?

>> The lab itself was actually kind of fun and not very straining. The only issues I had were with
>> working out kinks in the PICkit 3 itself, and how to input information into the serial terminal. After fiddling
>> around with things enough, everything fell into place, and I now feel a lot more confident in my own abilities.
/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 09         *
 *6/05/2019      *
 *****************/

>> Collaboration:
>> Partner: Austin Dymont

>> PLEASE GRADE ADYMONT GITHUB SUBMISSION!

>> CRUZID: sdenglis@ucsc.edu
>> I WROTE AND TESTED:
>> - Field.c
>> - Message.c
>> - AgentTest.c
>> - NegotiationTest.c

>> EXTRA CREDIT IMPLEMENTED:

>> FieldGuessAI() - 
>> 	Takes it a step beyond guessing grid spaces that haven't been previously guessed.
>> Iterates through a finite state machine, guessing south of hit position, then north,
>> then east, then west. All step through until a miss is recieved. Then, after all
>> cardinal directions have been swept for a boat, it returns to generating
>> a random grid space location which has yet to been guessed.

1.) Collaboration:

>> 	Again, the only person I collaborated with over the course of this project was Austin.
>> We chatted online over discord, since I happen to live off-campus and thus things
>> were much easier this way. Essentially, we just ran ideas off of each other, sending
>> test harness files via. file sharing systems, and helping one another debug some funky stuff.
>> In regards to this partnership and our teamwork, I'd say that things went incredibly smoothly.

2.) Lab Report:

>> 	As I understand it, the main guts of the BattleBoats project were already given to us:
>> we were just to implement a set of submodules in order to get things moving, and to
>> allow us to learn about the machine's functionality as we went. Some service module would
>> take charge in communicating between boards, following the guides and protocol of the 
>> Agent state machine. Whenever messages were to be sent and / or decoded, the transmission
>> service, message.c, would take care of things. Buttons.c, which we were not responsible for,
>> takes external input from the device, and the OLED is updated as the users progress through
>> the game itself. Agent State Machine acts as the brains of the program, and protocol protects
>> each user from unwanted tampering with hash codes, checksum functions.
>> 	In actually working on the project, I found that the approach that we had was very effective.
>> In a word, we divided the work between us lab members and then set to work on implementing our
>> respective functions. After fleshing out a fair amount of the submodules, we then set to work
>> on the test harnesses. This was pretty standard: simply taking the working version of each 
>> .c file sufficed to obtain a standard output to test our own files against. After the Test 
>> files were complete, it was simply a matter of debugging our main functions. This actually 
>> didn't take to long, as we spent the time ensuring the logic of each function seemed reasonable 
>> before moving on to other things.
>> 	I believe that I have learned a lot from this lab, not particularly about the computer
>> science and engineering concepts applied in the lab itself, but moreso the collaborative aspect
>> of things. Austin and I had to schedule, plan, manage our time wisely in splitting up tasks
>> into manageable pieces. Overall, I think that we did brilliantly for our first group coding project.
>> Granted, with only two people, things are a lot more direct and easy to manage. Furthermore, I did 
>> learn more about security, random number generation, hashes, communication between boards, more about
>> finite state machines, AI implementation, etc. 
>> 	In the end, this lab wasn't so bad. Although, there is A LOT to sort through in order to wrap
>> your head around what each person needs to accomplish and how to do so. Some of the header files
>> are outdated and misleading, the lab manual isn't too perfect in that regard either. Overall,
>> it's alright, helps you learn a ton, but seems to be biting off more than we can chew within a single
>> week as students right before finals. I'm sure that everyone else was super stressed rushing to complete
>> this. Anyways, I would update all the lab resources, and ensure that an ample amount of time is spent
>> in class going over what to actually expect, where to start, how to accomplish what is required.




# Pro Hacker Training

Welcome, Agent.

Assignment 4 is a classified cybersecurity operation reserved for the top 15 Hunter College CSCI 135 engineers. Your mission is to analyze suspicious data and verify agent identities before our systems are compromised. Write code for the following two tasks:
 
## Mission 1: Clean the Server Logs

Our security team has discovered that attackers are flooding our servers with repeated log entries. The logs are stored in a vector, and duplicate entries are wasting valuable storage space.

Your task is to remove all duplicate entries from the server logs by modifying the existing vector directly. The cleaned log should contain only one copy of each value.

Objective: Remove duplicates from the vector in-place but it should be in O(n) time. NOTE: remove()/erase() functions are O(n) as well. So using it would drastically increase runtime.


## Mission 2: Verify the Spy

An undercover agent has reported that all legitimate spy codenames are created by rearranging the letters of an officer's name.

You will be given:

- An officer's name
- A spy codename

Your task is to determine whether the codename is a valid rearrangement of the officer's name.
If the codename contains exactly the same letters in a different order, the spy is verified.
If not, the codename may belong to an imposter. Print a warning message to alert investigators.  

Objective: Determine whether the spy codename is an anagram of the officer's name and flag any invalid codenames.

## Part 2:
Find the run time for each of the tasks, give me the time complexity and explain why. Extra points if you can tell me the space complexity!

Find the source code file labeled assignment4.cpp to begin your mission.

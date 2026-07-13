# Welcome to Google: The Recursion vs. Iteration Design Team

Congratulations!! You just landed your first internship at Google. It's your first week, and your manager has a habit of dropping engineers straight into real design decisions instead of easing them in with busywork. She pulls you into three separate meetings this week, each with a different team, each stuck on the same underlying question: should we solve this recursively or iteratively?

Knowing recursion's syntax is not the same as knowing when to reach for it. In this assignment you will not be writing any code. Instead, for each scenario below, you will decide whether a recursive or iterative approach is the better fit, and defend that choice using reasoning. Your manager doesn't want code from you yet. She wants your judgment, in writing, that she can bring into the room.

1. States your choice: recursive or iterative.
2. Explains **why**, using at least two of the criteria listed below.
3. Identifies one **risk or downside** of your chosen approach for this specific scenario.

### Criteria to reason with (Use these as your toolkit, you don't need to include them all in your answer!)

- **Structure fit:** Does the problem naturally break into smaller versions of itself (self-similar / branching), or is it a flat, linear pass over data?
- **Depth / input size:** How deep would the recursion actually go for realistic inputs? Could that exceed a reasonable call stack?
- **Repeated work:** Would a naive recursive approach recompute the same thing multiple times?
- **State tracking:** Does the problem need to remember several pieces of information as it goes (an iterative loop makes you manage this by hand; recursion carries it in the call stack automatically)?
- **Readability:** Which version would be easier for another programmer (or you, in six months) to understand at a glance?


## Meeting 1: The Google Search Autocomplete Team

The autocomplete team pulls you aside with a fun but oddly specific problem. Someone on the team wants to compute Fibonacci-style "relevance decay" scores for ranking old search suggestions, where each score depends on the two before it: score(n) = score(n-1) + score(n-2). Most of the time n stays under 40, but a teammate points out that a batch job occasionally runs it up to n = 90 overnight.

A junior engineer already whipped up a recursive version straight from the formula and wants to ship it today. Your manager wants your take before it goes to code review.

Consider: What happens to the number of calls as n grows if the recursive definition is followed literally? Does that growth rate matter at n = 40? At n = 90? Is "it matches the math formula" a good enough reason to ship it?


## Meeting 2: The Google Drive Storage Team

The Drive team needs to calculate the total storage used by a user's top-level folder; including every file in every subfolder, no matter how deeply nested someone has organized (or disorganized) their Drive. Folders can contain folders, which can contain folders, sometimes ten or more levels deep for power users with elaborate filing systems.

They've got two competing pull requests open: one recursive, one iterative and can't agree on which to merge.

Consider: How does folder nesting compare to the flat structure in Meeting 1? How deep do real folder structures actually get in practice, and does that change your recommendation compared to the autocomplete scenario?


## Meeting 3: The Google Analytics Team

The Analytics team needs to sum up a full day's worth of ad click events, a plain list of about 1,000,000 numbers, one after another, no nesting, no branching, just a long flat sequence that needs to be totaled up before the nightly report goes out.

One engineer suggests recursion "for consistency" with the rest of the codebase, since the team just finished the Drive project. Your manager is skeptical and wants a second opinion before the next standup.

Consider: Is there anything self-similar or branching about this problem, or is it pure repetition? What happens to a recursive approach as the list grows: is there a point where it might fail outright, and why? Is "for consistency" a good enough reason on its own?


## Grading
There is no single "correct" rule. You will be graded on whether your reasoning is actually supported by the scenarios, not on matching a specific answer.


## Submission 
**Submit:** a single written document (PDF, Word, or Markdown) with your responses to all three scenarios.
# Submitting Homework via GitHub Fork
For this course, you'll submit all homework assignments by forking the class repository and opening a pull request. Follow these steps carefully the first time — after that, submitting new assignments only takes a few commands.

-----------------------------------------------

## **Step 1:** Fork the Class Repo

Go to the class repository on GitHub (link provided by your instructor).
Click the Fork button in the top-right corner.
GitHub will create a personal copy of the repo under your own account (e.g. your-username/CSCI-13500).


You only need to do this once for the entire semester.


## **Step 2:** Clone Your Fork Locally
Open your terminal and run:

```bash
git clone <https://github.com/YOUR-USERNAME/REPO-NAME.git>
cd REPO-NAME
```

Replace YOUR-USERNAME and REPO-NAME with your actual GitHub username and the repo name.


## **Step 3:** How to Submit Your Work!  
Navigate to the correct Week and make an assignments folder and complete your assignment there. For example:  
/Week1/Assignments/
  main.cpp
  README.md  
Only edit files inside the designated homework folder — do not modify other folders.

## **Step 4:** Stage, Commit, and Push
Once your work is ready, run:
```bash
git add .
git commit -m "Submit HW01 - Your Name"
git push origin main
```

Use a clear commit message like Submit HW01 - Jane Smith so your instructor can identify your submission easily.


## **Step 5:** Share Your Repo Link  
Once you've pushed your work, submit your fork's GitHub URL on Brightspace. It should look like:
https://github.com/YOUR-USERNAME/REPO-NAME
I will visit your repo directly to review your submission. The timestamp of your latest commit counts as your submission time.

Then repeat Steps 3–5 for each new assignment.

# Getting Help
If you get a merge conflict or something looks wrong, do not force push. Ask me before doing anything else.
Make sure your GitHub account has your name in it so I can identify you.

# How To Get CSCI 135 Class Repo Updates
Forking does not automatically add a connection between the original and your own. After you connect your repo to the class repo, you can skip step one. **Repeat steps 2 and 3 for every update pushed into the class repo!!**

## Step 1

Connect your forked copy of the repo to the original. 

```bash
git remote add upstream https://github.com/chisaiki/CSCI-13500.git 
```

## Step 2

Always push your original repo to Github **BEFORE** fetching updates.  
Now that a connection is established, you need to downloads the latest commits, files, and tracking branches from the class repo. 

```bash 
git fetch upstream
```

## Step 3
Combine the changes from the CSCI 135 class repo's main branch into your local repo's main branch.
```bash
git merge upstream/main
```


# Merge Conflicts

The merges should not cause a merge conflict on your end since they should only really affect a Week ahead. If you run into one, you can try to fix the merge conflict yourself (I highly recommend) or you can force merge.

```bash
git restore --source=upstream/main "FILE_NAME"
```

## How do I keep my own branch?
How it works: Git will merge everything smoothly. If you and the original repo edited the exact same file, Git will skip the conflict screen entirely and automatically keep your code.

```bash
git merge -Xours upstream/main
```
** To make changes in the same commit ID:
1. Go to that commit ID by reset 
git reset 08b71c5a1c9341fa123479dd2c294807ece2d7ad
git stash
Do the changes
git commit --amend
git push -f origin RemoteUIBump

** To make changes in different commits but same MR
Go to the commit ID(not the latest one) which is old in between these two commits in git log 
git reset oldcommitid
git stash
do the changes 
git add files
git commit --amend
git stash pop
git add files
git commit(Here no amend)
git push -f origin branchname


** To push to other's commit
git remote add irina ssh://git@git.swf.daimler.com:7999/s1irzaha/meta-mbient.git
git fetch irina
git checkout dunfell_rui_1.0.29
git add and git commit 
git rebase --continue
git push -f irina/dunfell_rui_1.0.29

** To drop few commits
git rebase -i 1c4d08cd58614eb7579a544af1a7fa7a40b70507^
Here a new page will be opened, replace 'pick' with 'edit' where u want to edit the commit
replace 'pick' with 'drop' in front of commits which u donot want

vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ git remote add Jiji ssh://git@git.swf.daimler.com:7999/s1jacobj/meta-mbient.git
vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ git fetch Jiji
remote: Enumerating objects: 104, done.
remote: Counting objects: 100% (93/93), done.
remote: Compressing objects: 100% (51/51), done.
remote: Total 104 (delta 60), reused 62 (delta 38), pack-reused 11
Receiving objects: 100% (104/104), 28.89 KiB | 629.00 KiB/s, done.
Resolving deltas: 100% (63/63), completed with 18 local objects.
From https://git.swf.daimler.com/s1jacobj/meta-mbient
 * [new branch]          dunfell                              -> Jiji/dunfell
 * [new branch]          dunfellruibump                       -> Jiji/dunfellruibump
 * [new branch]          i2_remote_ui_1.0.20                  -> Jiji/i2_remote_ui_1.0.20
 * [new branch]          marge_bot_batch_merge_job_dunfell    -> Jiji/marge_bot_batch_merge_job_dunfell
 * [new branch]          marge_bot_batch_merge_job_master     -> Jiji/marge_bot_batch_merge_job_master
 * [new branch]          master                               -> Jiji/master
 * [new branch]          masterruibump2                       -> Jiji/masterruibump2
 * [new branch]          release/E009                         -> Jiji/release/E009
 * [new branch]          release/E010.1                       -> Jiji/release/E010.1
 * [new branch]          remote_ui_1.0.20                     -> Jiji/remote_ui_1.0.20
 * [new branch]          rmuidunfellbump                      -> Jiji/rmuidunfellbump
 * [new branch]          rmuimasterbump                       -> Jiji/rmuimasterbump
 * [new branch]          rocko                                -> Jiji/rocko
 * [new branch]          ruibump                              -> Jiji/ruibump
 * [new branch]          thud                                 -> Jiji/thud
 * [new branch]          xlu800y/meta-mbient-rev-bump-dunfell -> Jiji/xlu800y/meta-mbient-rev-bump-dunfell
vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ git checkout -b meta-mbient-i2_remote_ui_1.0.20 Jiji/meta-mbient-i2_remote_ui_1.0.20
fatal: 'Jiji/meta-mbient-i2_remote_ui_1.0.20' is not a commit and a branch 'meta-mbient-i2_remote_ui_1.0.20' cannot be created from it
vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ git remote -v
Jiji	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1jacobj/meta-mbient.git (fetch)
Jiji	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1jacobj/meta-mbient.git (push)
KK	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1kkravc/meta-mbient.git (fetch)
KK	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1kkravc/meta-mbient.git (push)
origin	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1vinaja/meta-mbient.git (fetch)
origin	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/s1vinaja/meta-mbient.git (push)
upstream	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/mbient/meta-mbient.git (fetch)
upstream	https://gitlab-ci-token:Rfq1CDD4U18wdWQT8eUF@git.swf.daimler.com/mbient/meta-mbient.git (push)
vijain@ViJain-lnx:~/Project/meta-mbient(s1jacobj/meta-mbient-i2_remote_ui_1.0.20)$ git checkout -b i2_remote_ui_1.0.20 Jiji/i2_remote_ui_1.0.20
Branch 'i2_remote_ui_1.0.20' set up to track remote branch 'i2_remote_ui_1.0.20' from 'Jiji'.
Switched to a new branch 'i2_remote_ui_1.0.20'
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ git branch
  RemoteUIBump
  dunfell
* i2_remote_ui_1.0.20
  remote_ui_1.0.18
  remoteui13
  rui2.0.19
  s1jacobj/meta-mbient-i2_remote_ui_1.0.20
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ git rebase ^C
(reverse-i-search)`git rebase ': ^Ct branch
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ git rebase upstream/i2_SOP
First, rewinding head to replay your work on top of it...
Applying: Branching: configuration i2_SOP
Using index info to reconstruct a base tree...
M	Jenkinsfile
Falling back to patching base and 3-way merge...
No changes -- Patch already applied.
Applying: i2_sop: remove yml file for quality bot
Using index info to reconstruct a base tree...
M	.gitlab-ci.yml
Falling back to patching base and 3-way merge...
CONFLICT (modify/delete): .gitlab-ci.yml deleted in i2_sop: remove yml file for quality bot and modified in HEAD. Version HEAD of .gitlab-ci.yml left in tree.
error: Failed to merge in the changes.
Patch failed at 0002 i2_sop: remove yml file for quality bot
hint: Use 'git am --show-current-patch' to see the failed patch
Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
vijain@ViJain-lnx:~/Project/meta-mbient((no branch, rebasing i2_remote_ui_1.0.20))$ rm .gitlab-ci.yml
vijain@ViJain-lnx:~/Project/meta-mbient((no branch, rebasing i2_remote_ui_1.0.20))$ git add .gitlab-ci.yml
vijain@ViJain-lnx:~/Project/meta-mbient((no branch, rebasing i2_remote_ui_1.0.20))$ git rebase --contine
error: unknown option `contine'
usage: git rebase [-i] [options] [--exec <cmd>] [--onto <newbase> | --keep-base] [<upstream> [<branch>]]
   or: git rebase [-i] [options] [--exec <cmd>] [--onto <newbase>] --root [<branch>]
   or: git rebase --continue | --abort | --skip | --edit-todo

    --onto <revision>     rebase onto given branch instead of upstream
    --keep-base           use the merge-base of upstream and branch as the current base
    --no-verify           allow pre-rebase hook to run
    -q, --quiet           be quiet. implies --no-stat
    -v, --verbose         display a diffstat of what changed upstream
    -n, --no-stat         do not show diffstat of what changed upstream
    --signoff             add a Signed-off-by: line to each commit
    --ignore-whitespace   passed to 'git am'
    --committer-date-is-author-date
                          passed to 'git am'
    --ignore-date         passed to 'git am'
    -C <n>                passed to 'git apply'
    --whitespace <action>
                          passed to 'git apply'
    -f, --force-rebase    cherry-pick all commits, even if unchanged
    --no-ff               cherry-pick all commits, even if unchanged
    --continue            continue
    --skip                skip current patch and continue
    --abort               abort and check out the original branch
    --quit                abort but keep HEAD where it is
    --edit-todo           edit the todo list during an interactive rebase
    --show-current-patch  show the patch file being applied or merged
    -m, --merge           use merging strategies to rebase
    -i, --interactive     let the user edit the list of commits to rebase
    --rerere-autoupdate   update the index with reused conflict resolution if possible
    -k, --keep-empty      preserve empty commits during rebase
    --autosquash          move commits that begin with squash!/fixup! under -i
    -S, --gpg-sign[=<key-id>]
                          GPG-sign commits
    --autostash           automatically stash/stash pop before and after
    -x, --exec <exec>     add exec lines after each commit of the editable list
    --allow-empty-message
                          allow rebasing commits with empty messages
    -r, --rebase-merges[=<mode>]
                          try to rebase merges instead of skipping them
    --fork-point          use 'merge-base --fork-point' to refine upstream
    -s, --strategy <strategy>
                          use the given merge strategy
    -X, --strategy-option <option>
                          pass the argument through to the merge strategy
    --root                rebase all reachable commits up to the root(s)
    --reschedule-failed-exec
                          automatically re-schedule any `exec` that fails

vijain@ViJain-lnx:~/Project/meta-mbient((no branch, rebasing i2_remote_ui_1.0.20))$ git rebase --continue
Applying: i2_sop: remove yml file for quality bot
Applying: remoteui-source: update to 1.0.20
Applying: aagalreceiver: update to 2.0.5
Applying: apple-comm: update to 2.0.19
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ git branch
  RemoteUIBump
  dunfell
* i2_remote_ui_1.0.20
  remote_ui_1.0.18
  remoteui13
  rui2.0.19
  s1jacobj/meta-mbient-i2_remote_ui_1.0.20
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ git push -f Jiji i2_remote_ui_1.0.20
Enumerating objects: 1303, done.
Counting objects: 100% (1303/1303), done.
Delta compression using up to 8 threads
Compressing objects: 100% (369/369), done.
Writing objects: 100% (1008/1008), 189.48 KiB | 31.58 MiB/s, done.
Total 1008 (delta 637), reused 952 (delta 601)
remote: Resolving deltas: 100% (637/637), completed with 182 local objects.
remote: 
remote: View merge request for i2_remote_ui_1.0.20:
remote:   https://git.swf.daimler.com/mbient/meta-mbient/-/merge_requests/22516
remote: 
To https://git.swf.daimler.com/s1jacobj/meta-mbient.git
 + 68e31aa3f...40aea900b i2_remote_ui_1.0.20 -> i2_remote_ui_1.0.20 (forced update)
vijain@ViJain-lnx:~/Project/meta-mbient(i2_remote_ui_1.0.20)$ 


<!-- title: Your Title -->

# GIT Cheat Sheet

## Checking Out Git Submodules

To initialize and update submodules in your repository, use the following commands:

### Clone the repository and initialize submodules

git clone --recurse-submodules [repository-url]

### If you've already cloned the repo, initialize and update submodules

git submodule update --init --recursive

To update submodules to the latest commit on their tracked branch:

git submodule update --remote

For more information, see the [Git Submodules Documentation](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

Hello bold text **HELL0**

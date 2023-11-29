# git

git Init
Opis: Inicjalizuje nowe repozytorium git
przyklad: git init


git clone[url]
Opis: Klonuje istniejące repozytorium z podanego URL.
Przykład: git clone https://github.com/przyklad/repo.git

git clone [url] [katalog]

git clone --branch [branch-name] [url]

git clone --depth 1 [url]  (glebokosc pobrania brancha (1-pobierze ostatni commit))

git clone--mirror [url]

git add [file]

git add [directory]

git add . git add -A

git add --ignore-removal

git add [file1] [file2]

git add "*.py"

git commit -m "[commit message]"

git commit -a -m "[commit message]" / git commit -am "[commit message]"

git commit --amend -m "[change last commit message]"

git commit --amend --no-edit

git commit  --allow-empty -m "Pusty commit"


#obie wersje są poprawne
git commit -m "Tytuł commita" -m "dalszy opis zmian" 

 git commit -m "Tytuł commita 
dalszy opis zmian"



git status

git status -s

git status -u

git status -b

git status ignore

git status --show-stash

git pull

git pull origin

git pull oring dev

git pull --verbase

git pull --dry-run

git pull --no-commit origin feature (pobierze zmiany ale nie w formie commitu)

git remote

git remote -v

git remote add [nazwa] [url]

git remote rename [old-name] [new-name]

git remote rm [shortname]

git remote show [shortname]

git remote update

git remote set-url [shortname] [new-url]

git remote set-head [shortname] -a

git pull. git push


git config --global user.name "[name]"
git config --global user.email "[email address]"

git config --global core.editor "[editor]"

git config [key]

git config --global alias.[alias-name] '[command]'
git config --global alias.st 'status'

/n/r
git config --global core.autocrlf [true|false|input]

git config --global merge.tool [tool]

git config --global diff.tool [tool]

git config --global core.filemode [true|false]

git branch

git branch [branch-name]

git branch -d [branch-name]

git branch -D [branch-name]

git branch -m [old-name] [new-name]

git branch -v

git branch --show-current

git branch --no-merged [branch]

git branch --contains [commit]

git branch -vv

git branch --sort=[key]

git branch --sort=committerdate

git branch [branch-name] [start-point]

git branch --copy feature-old feature-new

git branch --move [old-branch] [new-branch]

git branch --edit-description [branch-name]

git branch --list [pattern]

git branch --list 'feature*'

git branch --delete --remotes [remote/branch]

git branch --color

git branch --force [branch-name]

git checkout [branch-name]

git checkout -b [branch-name]

git checkout [commit-name]

git checkout -- [file-name]

git checkout [branch-name] -- [file-name]

git checkout [branch-name]

git checkout -

git checkout --orphan new-start

git checkout [tag-name]


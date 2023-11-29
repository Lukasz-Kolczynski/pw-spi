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
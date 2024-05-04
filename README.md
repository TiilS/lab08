

> Установка формата
```
$ clang-format -style=mozilla -dump-config > .clang-format
$ clang-format -i *.cpp
```

```
$ git pull --rebase origin master
  remote: Enumerating objects: 5, done.
  remote: Counting objects: 100% (5/5), done.
  remote: Compressing objects: 100% (3/3), done.
  remote: Total 3 (delta 2), reused 0 (delta 0), pack-reused 0
  Распаковка объектов: 100% (3/3), 962 байта | 240.00 КиБ/с, готово.
  Из https://github.com/TiilS/lab02
   * branch            master     -> FETCH_HEAD
     6fbc8f5..0939789  master     -> origin/master
  Автослияние hello_world.cpp
  КОНФЛИКТ (содержимое): Конфликт слияния в hello_world.cpp
  error: не удалось применить коммит 5d4736e... Format Mozilla
  подсказка: Resolve all conflicts manually, mark them as resolved with
  подсказка: "git add/rm <conflicted_files>", then run "git rebase --continue".
  подсказка: You can instead skip this commit: run "git rebase --skip".
  подсказка: To abort and get back to the state before "git rebase", run "git rebase --abort".

```

```
$ git rebase --continue
  [отделённый HEAD 5ef2739] Format Mozilla
   3 files changed, 257 insertions(+)
   create mode 100644 .DS_Store
   create mode 100644 .clang-format
  Успешно перемещён и обновлён refs/heads/patch2.
  Не удалось применить коммит 5d4736e... Format Mozilla
```

```
$ git push origin patch2 --force
  Перечисление объектов: 7, готово.
  Подсчет объектов: 100% (7/7), готово.
  При сжатии изменений используется до 8 потоков
  Сжатие объектов: 100% (5/5), готово.
  Запись объектов: 100% (5/5), 3.26 КиБ | 3.26 МиБ/с, готово.
  Всего 5 (изменений 1), повторно использовано 0 (изменений 0), повторно использовано пакетов 0
  remote: Resolving deltas: 100% (1/1), completed with 1 local object.
  To https://github.com/TiilS/lab02.git
   + 5d4736e...5ef2739 patch2 -> patch2 (forced update)
```

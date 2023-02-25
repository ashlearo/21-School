
SimpleBashUtils

https://21-school-by-students.notion.site/91d81fe00f35437ab7a1ea5251585ce8

Команда cat 
- это сокращения от слова catenate. По сути, задача команды cat очень проста - она читает данные из файла или стандартного ввода и выводит их на экран. 
$ cat опции файл1 файл2 ...
-b - нумеровать только непустые строки;
-E - показывать символ $ в конце каждой строки;
-n - нумеровать все строки;
-s - удалять пустые повторяющиеся строки;
-T - отображать табуляции в виде ^I;
-h - отобразить справку;
-v - версия утилиты.

https://losst.pro/komanda-cat-linux
https://github.com/coreutils/coreutils/blob/master/src/cat.c
https://opensource.apple.com/source/text_cmds/text_cmds-87/cat/cat.c

Команда grep (расшифровывается как global regular expression print) 
- одна из самых востребованных команд в терминале Linux, которая входит в состав проекта GNU. Секрет популярности - её мощь, она даёт возможность пользователям сортировать и фильтровать текст на основе сложных правил.
$ grep [опции] шаблон [имя файла...]
-b - показывать номер блока перед строкой;
-c - подсчитать количество вхождений шаблона;
-h - не выводить имя файла в результатах поиска внутри файлов Linux;
-i - не учитывать регистр;
- l - отобразить только имена файлов, в которых найден шаблон;
-n - показывать номер строки в файле;
-s - не показывать сообщения об ошибках;
-v - инвертировать поиск, выдавать все строки кроме тех, что содержат шаблон;
-w - искать шаблон как слово, окружённое пробелами;
-e - использовать регулярные выражения при поиске;
-An - показать вхождение и n строк до него;
-Bn - показать вхождение и n строк после него;
-Cn - показать n строк до и после вхождения;

https://losst.pro/gerp-poisk-vnutri-fajlov-v-linux?cmdurl=1
https://proglib.io/p/16-opciy-grep-kotorye-pomogut-vam-v-realnom-mire-2021-03-16

diff
- Сравнение файлов в Linux 
diff [опции] файлы-или-директории
-E	игнорировать изменения, связанные с добавлением символа табуляции в тексте.
-b	игнорировать изменения, связанные с добавлением пробелов.
-w	игнорировать изменения, связанные с добавлением пробелов и табуляции.
-B	игнорировать новые пустые строки.
-p (или —show-c-function)	показать название функции языка C, в которой найдены изменения.
-y (или —side-by-side)	отобразить результаты в две колонки.
-r	просматривать каталоги рекурсивно.
-X FILE	исключить из поиска файлы, имена которых совпадают с шаблонами в файле FILE.
-d (или —minimal)	попытаться найти как можно меньше изменений (то есть исключить ложные срабатывания).
https://pingvinus.ru/note/compare-files-diff-in-linux


Краткий справочник по командам UNIX
https://www.opennet.ru/docs/RUS/inet_book/10/unix1018.html

Кодирование текста
https://ru.wikibooks.org/wiki/%D0%9A%D0%BE%D0%B4%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5_%D1%82%D0%B5%D0%BA%D1%81%D1%82%D0%B0
https://www.ibm.com/docs/ru/sdse/6.4.0?topic=configuration-ascii-characters-from-33-126
http://book.itep.ru/10/ascii.htm

Регулярные выражения
https://regex101.com/
https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=regex&category=7

Горячие клавиши Visual Studio Code
https://nikomedvedev.ru/other/vscodeshortcuts/hotkeys.html

Настройка ZSH в MacOS
https://kuzevanov.ru/macos/%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B0-zsh-%D0%B2-mac-os.html

Оператор return
http://cpp.com.ru/shildt_spr_po_c/06/0605.html

#define имя_макроса последовательность_символов
http://www.c-cpp.ru/books/define

fgets()
- чтение строки в поток
fputs()
- запись строки в поток
http://www.c-cpp.ru/books/rabota-so-strokami-fgets-i-fputs

regmatch_t
Структура с результатами сравнения строки с регулярным выражением
https://help.kpda.ru/help/index.jsp?topic=%2Fru.kpda.doc.os_ru%2Fhtml%2Flibraries%2Flibc%2Fr%2Fregmatch_t.html

getopt()
- разбирает аргументы командной строки.
#include <unistd.h>
int getopt(int argc, char * const argv[],const char *optstring);
https://mk.cs.msu.ru/images/9/97/Prac_318_command_line_in_cpp.pdf
http://nskhuman.ru/helpdb/manrus.php?ncmd=756

getopt_long()
+ разбор длинных флагов
https://firststeps.ru/linux/r.php?11

Аргументы командной строки
int main(int argc, char* argv[])
argc  - Количество аргументов
argv  - массив указателей на строки(аргументы)
optarg - указатель на аргумент
optind - индекс argv
optopt - аргумент(символ)



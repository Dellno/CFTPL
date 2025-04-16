## язык программирования FTPL
Основным "объектом" языка является массив памяти размером в 512 ячеек. В языке нет переменных, вместо этого есть прямое обращение к "памяти". Вся математика, в том числе и логические выражения реализованы в виде Обратной польской записи.
 

# Написание кода на FTPL
математические операторы: "+", "-", "*", "/", "//", "%", "=", "!=", ">", "<", "<=", ">=", "ИЛИ", "И", "!"

на данный момент реализованы следующие инструкции:

-КУРСОР <номер ячейки (целое число)> функция задающая  ячейку памяти с которой производятся действия.

-ВВОД  читает числовое значение из консоли и записывает в текущую ячейку памяти

-СЧЁТ <формула> результат математического выражения записанного после этой инструкции будет записан в текущую ячейку памяти

-ЦЕЛ преобразует текущее значение ячейки в целое число (отбрасывает дробную часть)

-ЕСЛИ <формула> - инструкция для ветвления, все выражения на следующих строчках перед которыми (через пробел, это важно!) стоит символ "_" в количестве равном количеству вложенности будут выполнены только в том случае если условие истинно.

-<номер ячейки> СЧИТАТЬ не используется как самостоятельная инструкция, указывает инструкциям СЧЁТ, ЕСЛИ и т.д на то, что необходимо взять значение из ячейки памяти.

-ТОЧКА <любое слово> создаёт именованую точку перехода для инструкции ПЕРЕЙТИК

-ПЕРЕЙТИК <именованая точка перехода> инструкция после выполнения которой программа будет выполняться далее с указанной строки. 

-СТРОКА <сама строка> инструккция записшет по 1 байту (в кодировке UTF-8) указанную строку в память начиная с текущей ячейки. Стоит учесть, что строка займёт число символов равное не длине строки, а длине строки + 1, т.к. в конце записывается символ окончания строки. Ещё стоит учесть, что русские символы в utf-8 занимают не 1, а 2 байта! 

-ВВОДСТРОКИ <n, не обязательный аргумент> читает строку из консоли и записывает в память как и СТРОКА. При указании числа в качестве аргумента будут записаны только n + 1 символов строки (+1 т.к. всегда записывается символ окончания строки.

-ВЫВОД без аргументов выводит число из текущей ячеки памяти. Возможно указание нескольких аргументов:

      -ЦЕЛ выводит ячейку памяти как целое число без дробной части
  
      -СИМВОЛЫ выводит последовательно все символы из ячеек памяти пока не дойдёт до ячейки со значением 0 (конец строки)

-ВЫХОД оператор выхода из программы


## примеры кода:
##### Hello World
```
КУРСОР 1
СТРОКА Здравствуй Мир!
ВЫВОД СИМВОЛЫ
ВЫХОД

```

##### вычисление факториала n-ного числа
```
СТРОКА Введите число факториал которого нужно найти: 
ВЫВОД СИМВОЛЫ
КУРСОР 0
ВВОД
КУРСОР 3
СЧЁТ 1
ТОЧКА цикл
ЕСЛИ 0 СЧИТАТЬ 1 >
_ СЧЁТ 3 СЧИТАТЬ 0 СЧИТАТЬ *
_ КУРСОР 0
_ СЧЁТ 0 СЧИТАТЬ 1 -
_ КУРСОР 3
_ ПЕРЕЙТИК цикл
ВЫВОД
ВЫХОД
```


# как запустить интерпретатор:

скачиваем файл ftpl.exe
создаём файл main.ftpl (название можно другое)
после есть 2 способа запустить
первый способ простой но неправильный:

      1) правой кнопкой мышки нажимаем на файл main.ftpl > открыть с помощью > Ещё приложения >
      2) найти другое приложение на этом компьютере > находим наш файл ftpl.exe и выбираем его.
      3) теперь файлы .ftpl будут всегда открываться с помощью интерпретатора.
второй способ сложный и правльный:

      1) скачиваем из этого репозитория / собираем из исходников (тоже из этого репозитория) файл ftpl.exe
      2) открываем cmd в виндовс и пишем команду set PATH=%PATH%;диск:\путь\до\ftpl.exe (обратите внимание, важно указать именно вашь путь до файла!)
      3) теперь в папке со скриптом пишем: ftpl имяпрограммы.ftpl и файл будет запущен
      4) при желании можно указать количесвто доступных программе ячеек памяти (по стандарту 512): ftpl имяпрограммы.ftpl --memory числоячеек
  
  

# как собрать проект
1) установите компилятор clang под вашу ОС
2) скопируйте папку с проектом из репозитория
3) откройте папку в терминале
4) проишите команду clang main.c stack/stack.c math_parser/math_parser.c -o <имя выходного файла, на винде например ftpl.exe>
после в папке с проектом появится скомпилированный файл.


По вопросам о проекте: https://t.me/wild_turtles или https://t.me/Dellnoz

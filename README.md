# asusx542bp
# 09.04.2020 1st Save asm projects

29.11.2020 Добавил в .gitignore qt и fasm файлы и они стали отображаться в git status как deleted
           Сделал комит и в репозитории эти файлы пропали... 

29.11.2020 PycharmProjects/ проекты по парсингу json-файлов
           router_reboot - перегрузка домашнего роутера using selenium.webdriver

24.05.2020 qt_projects/generate_sample_mx генерит сразу обе матрицы А и В разного размера для проверки 
           перемножения. ОТкрытие, запись файла выделено в отдельную ф-цию. В main только вызов этой ф-ции.
  

24.05.2020 Разные матрицы теперь можем перемножать.
           Теперь 5 аргументов в команной строке.
           matrix_mult_param <file A size in bytes>\
                             <matrix A rows number>\
                             <matrix B coloumns number>\ 
                             <file B size in bytes>\
                             <matrix C coloumns number>
                              
24.05.2020 НАконец-то правильное перемножение. Фиксируем.
           Существенно подчистил код умножения матриц.
           Добавил дополнительные тестовые директории 3x3x3 и 4x5x3 с рабочим кодом и исходными матрицами для проверки.
           Добавил освобождение выделяемой памяти в matrix_mult_param.
           Доработал код mx_mult_AB. Теперь он просто создает небольшие тестовые матрицы заданных размеров.
           В текущей версии matrix_mult_param перемножает матрицы 1000х1000 за 11 сек, против 6-7 ранее, зато 100% правильно.


20.05.2020 Добавил комменты в код для студентов, убрал лишние (старые) комменты.
           ДОбавил файл с BMI1, BMI2 - 0_exp.fasm

14.05.2020 Начал fasm-примеры BMI инструкций. Поправил предыдущее. 

11.05.2020 Рабочий вариант. randomizer_param, matrix_mult_param уже принимают параметры.
           randomizer_param <file size in bytes> 
           matrix_mult_param <file size in bytes>\
                             <matrix A rows number>\
                             <matrix B coloumns number>\ 
                             <matrix C coloumns number>

           Последний параметр избыточен... ибо может вычисляться из предыдущих параметров, но добавляет наглядности при вводе команды.



06.05.2020 Назрела необходимость выделить qt проект duplicate в отдельный репозиторий, т.к. будут различные версии массива, 
           куда считывается файл данных для аналаиза.
           Фиксирую текущее состояние отдельным коммитом. Рабочий файл main.cpp 

03.05.2020 ПРоект duplcate создан на  qt. Добавил проверку на одинаковые элементы в файле. Если нет одинаковых значений, значит рандомайзер работает хорошо.
           randomizer генерирует матрицу для перемножения. НА основе генератора случайных чисел.
           ТУт анализируется файл размером 400 байт.	   


02.05.2020 Переделал randomizer manhunter-а под Linux. Вещь !!!

01.05.2020 Исправил matrix_mult_07/08. А вся проблема была в квадратных скобочках :) и  блок  
           изменения индексов был не с той стороны границы цикла.

13.04.2020 Добавил rdrsc.asm - пример использования инструкции rdtsc.
           Вычисляет разницу тиков между 2 mov-командами, записывает в двоичный файл и выводи в stdout.
           Скрипт middle.bash запускает исполняемый файл с ассемблеар, берет этот вывод и пишет в файл в цикле.
           ТАк получаем набор данных для вычисления среднего значения тиков. МОжно создавать очень большую выборку, чтобы среднее
           значение было ближе всего к реальному. 

11.04.2020 Добавил strlen.inc, поместил ф-цию вычисления длины строки в отдельный файл.
           Добавил int_2_str.inc, поместил ф-цию перевода числа в строку в отдельный файл.
           Добавил reflect_input_04.asm - теперь там вывдится число символов в строке пользователя.


# asusx542bp
# 09.04.2020 1st Save asm projects

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


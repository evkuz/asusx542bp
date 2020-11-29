#ifndef EVKUZ_H
#define EVKUZ_H
/*
 * Начало 03.05.2020
 * Project "duplicate" for ubuntu
 * Выполняет поиск одинаковых значений в двоичном файле.
 * Каждое значение - это 32-битное (quint32) число.
 * Создано для проверки работы генератора случайных чисел. Т.е. если не находит в файле
 * одинаковых значений, значит генератор хорошо сработал.
 *
 * Алгоритм.
 * - Открываем файл,
 * @@- считываем значение по текущему смещению, назначаем его как sample (образец для сравнения)
 *   в самом начале, после открытия, смещение равно 0(т.е. как раз первое значение в файле),
 *   далее по ходу цикла оно уже будет иметь нужное значение,
 *   т.к. будет сдвинуто на следующем шаге как раз на следующий элемент, который также станет sample
 * - Сдвигаем смещение на 1 элемент вперед. Т.е. Инкрементируем значение offset на 4, т.к. у нас 32-битные элементы.
 * - Считываем остаток файла (с текущего смещения и до конца) в массив quint32.
 * - Двигаемся по массиву, и каждое новое значение массива сравниваем с sample.
 *   Если в процессе находим совпадение - выводим сообщение, выходим.
 *   Если не находим совпадение в массиве, возвращаемся на @@
 *
 * Какие нужны доработки.
 * - Главное - сделать проект полноценной утилитой для использования в linux.
 * - Сейчас размер массива, куда считываются данные из файла задается явно. А это очень не гибко.
 *   Т.к. если надо обработать файл большего размера, то надо лезть в код и заново компилить.
 * - Поэтому и считывать приходится заданное число байт, а надо считывать "до конца" файла.
 * - Нужно посчитать сколько в данном файле случится совпадений, а не выходить при первом же.
 * - Нужно выводить оба смещения - для самого элемента и его совпадения (это тоже элемент, но дальше по файлу)
 * - Добавить в качестве аргумента имя файла, в котором ищутся совпадения. Сейчас имя файла задано жестко.
 *  В таком случаем получим полноценную утилиту LE (linux executable)
 *
 * 05.05.2020
 * Использовать указатель как Массив для считывания данных не получается.
 * Самое время пробовать ветвление в git. Пробуем использовать тип QVector
 * Пока создам просто разные файлы *.cpp в одном проекте.
 * Но тогда придется в одном evkuz.h указывать отличия всех *.cpp друг от друга.
 *
 * #########################  main_QVector ##################################
 * Объявляем массив:
 * QVector<quint32> mybuffer;
 *
 * И получаем "segmentation fault" на строчке
 *
 * num = mfile.read(reinterpret_cast<char*>(&mybuffer), rest_of_file);
 *
 * Т.е. проект собирается, но в рантайме падает.
 *
 *
 * 04.05.2020
 * ################################## main_arr_point ########################
 * Объявляем массив:
 * quint32 * mybuffer;
 *
 * Считываем из файла в массив :
 * num = mfile.read(reinterpret_cast<char*>(&mybuffer), rest_of_file);
 *
 * Доступ к элементам массива :
 * fdata = *(mybuffer+i);
 * где i - смещение от начала.
 *
 * Все компилится, но получаю :
 *
 * "/home/evkuz/qtprojects/duplicate/duplicate crashed"
 * А при запуске в debug режиме :
 *
 * Signal meaning :
 * Segmentation fault
 * НА строчке
 * num = mfile.read(reinterpret_cast<char*>(&mybuffer), rest_of_file);

 *
 *
 * */
#endif // EVKUZ_H

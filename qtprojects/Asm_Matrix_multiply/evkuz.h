#ifndef EVKUZ_H
#define EVKUZ_H

/*
 * Проект Asm_Matrix_multiply
 * Перемножение матриц.
 *
 * Перемножение 2-х матриц реализовано в прошлом проекте.
 * В этом проекте будет вычислять время, затраченное процессором на эти вычисления.
 * Используем Windows API ф-цию GetSystemTimes
 *
 * В итоге сравним время затраченное программой на Qt vs на FASM
 *
 *
 * 17.04.2019
 * Взятие матриц из файлов тоже было проблемой.
 * Инициализация указателей - вот важная проблема.
 * Решается 1 дополнительной строчкой:
 *
 *  char ccc = 100;
    char* ek_c = &ccc;

 * Функция чтения из файла считывает элементы в массив char * :
 * qint64 read(char *data, qint64 maxlen);
 * А в матрице числа имеют тип DWORD.
 * И вот преобразование указателя на char * в указатель на DWORD* есть проблема.
 *
 * Не стал с этим заморачиваться, объявил массивы для матриц А,В с заданным размером.
 * А вот строчка :
 *
 * mB = static_cast<DWORD *>(static_cast<void *>(ek_b));
 *
 * Приводит указатель DWORD *mB в тот же адрес, куда смотрит указатель char *ek_b
 * И после этого имеем полноценный массив DWORD Элементов.
 * Специально это уточнял, меняя содержимое data_A/B
 *
 * - При увеличении размера матриц, забыл изменить параметр в ф-ции чтения из файла.
 *   readed = mfile_B.read(ek_b, mxrB * mxcolC * 4);
 *   Исправи ВЕЗДЕ и матрица С получилась.
 *
 * d:\Lit\Uni\Matrix_multiply\get_data\Source_Matrixes\ тут лежат исходные матрицы разных размеров
 * Значения elapsed time в наносекундах для разного размера матриц :
 *
 *- Перенес объявления массивов в кучу, после этого с большими массивами работает без проблем.
 *  Вот для чего нужны заголовочные файлы :)
 *
 * Обращаем внимание, что комбинация матриц (100х10)*(10х100) и (100х100)*(100х100) приводит
 * к одинаковому размеру матрицы С 100х100, а время вычисления посмотрим :)
 *
 * A = 10x10,      B = 10x10,     C = 10x10        time =       882 471
 * A = 100x10,     B = 10x100,    C = 100x100      time =       577 077
 * A = 100x100,    B = 100x100,   C = 100x100      time =     1 190 510
 * A = 1000x100,   B = 100x1000,  C = 1000x1000    time =   108 780 364 == 0.1c
 * A = 1000x1000,  B = 1000x1000, C = 1000x1000    time = 1 231 664 414 == 1.2c
 *
 *
 * 16.04.2019
 * Добавляю запись итоговой матрицы С в файл.
 * СДЕЛАНО !!!
 *
 * Очень долго провозился с приведением типов.
 * А оказалось все решают 2 строчки :
 *
 *  char* ek_c;
 *  ek_c = (char*)mxC;
 *  Так  указатель на массив char (ek_c) принимает значение указателя на массив DWORD (mxC)
 *
 * Следующий шаг - брать исходные матрицы из файлов.
 * И тут важно разобраться с типами также
 *
 * D:\QT-Projects\Camac_USB\Asm_Matrix_multiply
 * D:\Lit\Универ\Matrix_multiply
 *
 *
#endif // EVKUZ_H


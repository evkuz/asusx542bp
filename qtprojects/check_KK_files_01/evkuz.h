#ifndef EVKUZ
#define EVKUZ
/*
 *
 * ПРоект check_KK_files_01
 *
 *  28.12.2017
 *
 * Делаем универсальный тестер файлов набора.
 * Теперь будет проверять не только каждый 8 байт на 0xf0.
 * Алгоритм такой :
 *
 * Берем Байты 1 и 8 файла и сравниваем их с байтами 9 и 16 - соответственно.
 * И так по всему файлу.
 *
 *
 *
 *
 *
 *  26.12.2017
 * Теперь задача проверять все файлы *.bin, а не только "Camac_Thread_data_000.bin" СДЕЛАНО.
 *
 * Программа проверяет в папке '../bin' (на уровень выше, чем папка запуска программы) все файлы с расширением *.bin
 * НАдо позаботиться, чтобы они там были.
 *
 *
 *
 *  08.12.2017
 *
 *  Проверяем правильность записи байт в файл.
 *
 *  на позиции 0x8000c0, но было раньше...
 *
 *  Ф-ция QDir::count(); возвращает число 800, хотя файлов 798. Где еще 2 файла ?
 * Или это './' и  '..' ???
 *
 *
 *
 *
 *
 *


*/
#endif // EVKUZ
